/**
 * @file chat_manager.c
 * @brief 好友聊天管理模块实现：负责好友列表与最近聊天记录的本地缓存。
 */
#include "chat_manager.h"

#include "app_config.h"

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include "os/os_api.h"
#include "generic/log.h"
#include "cJSON.h"
#include "websocket_client.h"
#include "fs/fs.h"
#include "http/http_cli.h"
#include "storage_device.h"

#if defined(CONFIG_UI_STYLE_LY_ENABLE)
#include "lvgl_v8_ui_app/style_LY/custom/chat_friend_history.h"
#endif

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif
extern uint32_t sys_timer_get_ms(void);
#ifdef __cplusplus
}
#endif

#ifndef CHAT_MANAGER_LOG_TAG
#define CHAT_MANAGER_LOG_TAG "[CHAT]"
#endif

/**
 * @brief 好友槽位结构体：包含好友信息和对应的 20 条消息环形缓冲。
 */
struct chat_friend_slot {
    struct chat_friend_entry info;                                     /**< 好友基本信息，直接映射 downGetChatUserList。 */
    struct chat_message_record messages[CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND]; /**< 最近消息环形缓存，固定容量 CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND。 */
    uint8_t write_index;                                               /**< 环形缓冲写指针，指向下一条要写入的槽位。 */
    uint8_t count;                                                     /**< 当前缓存的有效消息条数，<= CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND。 */
};

static OS_MUTEX s_chat_lock;                                           /**< 线程安全互斥锁。 */
static bool s_chat_lock_ready;                                         /**< 互斥锁是否创建成功。 */
static struct chat_friend_slot s_friend_slots[CHAT_MANAGER_MAX_FRIENDS]; /**< 好友槽位数组。 */
static uint64_t s_last_group_list_timestamp_ms;                        /**< 最近一次好友列表更新时间戳。 */

#define CHAT_MANAGER_VOICE_DIR_NAME              "/chat_voice"
#define CHAT_MANAGER_VOICE_DIR_PATH              CONFIG_ROOT_PATH "chat_voice/"
#define CHAT_MANAGER_VOICE_DOWNLOAD_THREAD_PRIO   11
#define CHAT_MANAGER_VOICE_DOWNLOAD_THREAD_STACK  2048
#define CHAT_MANAGER_VOICE_DOWNLOAD_TIMEOUT_MS    15000
#define CHAT_MANAGER_VOICE_HTTP_RECV_BUF          2048
#define CHAT_MANAGER_MAX_FILE_EXT_LEN             8
#define CHAT_MANAGER_STORAGE_WAIT_TOTAL_MS        5000
#define CHAT_MANAGER_STORAGE_WAIT_SLICE_TICKS     2
#define CHAT_MANAGER_VOICE_DIR_MAX_RETRY          5

struct chat_voice_download_task {
    char group_id[CHAT_MANAGER_MAX_GROUP_ID_LEN];
    char message_id[CHAT_MANAGER_MAX_MESSAGE_ID_LEN];
    char url[CHAT_MANAGER_MAX_URL_LEN];
    char file_path[CHAT_MANAGER_MAX_MEDIA_PATH_LEN];
    uint32_t expected_size;
};

struct chat_http_download_ctx {
    FILE *fp;
    size_t written_bytes;
    int status;
};

static void chat_manager_voice_download_thread(void *priv);
static int chat_manager_find_slot_by_group(const char *group_id);
static int chat_manager_http_download_cb(void *http_ctx,
                                         void *buf,
                                         unsigned int size,
                                         void *priv,
                                         httpin_status status);

/**
 * @brief 释放单条消息中动态申请的媒体缓冲区。
 */
static void chat_manager_release_message(struct chat_message_record *record)
{
    if (!record) {
        return;
    }
    if (record->media_buffer) {
        free(record->media_buffer);
        record->media_buffer = NULL;
    }
    record->media_buffer_len = 0;
}

/** 加锁封装，避免重复判断互斥锁状态。 */
static void chat_manager_lock(void)
{
    if (s_chat_lock_ready) {
        printf("%s lock pend\n", CHAT_MANAGER_LOG_TAG);
        os_mutex_pend(&s_chat_lock, 0);
    }
}

/** 解锁封装。 */
static void chat_manager_unlock(void)
{
    if (s_chat_lock_ready) {
        printf("%s lock post\n", CHAT_MANAGER_LOG_TAG);
        os_mutex_post(&s_chat_lock);
    }
}

/** 将好友槽位恢复为初始状态。 */
static void chat_manager_reset_slot(struct chat_friend_slot *slot)
{
    if (!slot) {
        printf("%s reset slot skipped (null)\n", CHAT_MANAGER_LOG_TAG);
        return;
    }
    printf("%s reset slot for group=%s\n", CHAT_MANAGER_LOG_TAG,
           slot->info.group_id[0] ? slot->info.group_id : "<empty>");
    for (size_t i = 0; i < CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND; ++i) {
        chat_manager_release_message(&slot->messages[i]);
    }
    memset(slot, 0, sizeof(*slot));
}

/**
 * @brief 安全复制字符串，确保目标缓冲区以 '\0' 结尾。
 */
static void chat_manager_copy_string(char *dst, size_t dst_len, const char *src)
{
    if (!dst || !dst_len) {
        return;
    }
    if (!src) {
        dst[0] = '\0';
        return;
    }
    snprintf(dst, dst_len, "%s", src);
    dst[dst_len - 1] = '\0';
}

static bool chat_manager_is_http_url(const char *path)
{
    if (!path) {
        return false;
    }
    size_t len = strlen(path);
    if (len < 7) {
        return false;
    }
    if ((path[0] == 'h' || path[0] == 'H') &&
        (path[1] == 't' || path[1] == 'T') &&
        (path[2] == 't' || path[2] == 'T') &&
        (path[3] == 'p' || path[3] == 'P')) {
        size_t offset = 4;
        if (len > offset && (path[offset] == 's' || path[offset] == 'S')) {
            offset++;
        }
        if (len > offset + 2 &&
            path[offset] == ':' &&
            path[offset + 1] == '/' &&
            path[offset + 2] == '/') {
            return true;
        }
    }
    return false;
}

static void chat_manager_make_safe_filename(const char *src, char *dst, size_t dst_len)
{
    if (!dst || dst_len == 0) {
        return;
    }
    dst[0] = '\0';
    size_t idx = 0;
    if (src) {
        for (const char *p = src; *p && idx + 1 < dst_len; ++p) {
            char ch = *p;
            if (isalnum((unsigned char)ch) || ch == '-' || ch == '_') {
                dst[idx++] = ch;
            } else {
                dst[idx++] = '_';
            }
        }
    }
    if (idx == 0) {
        uint64_t stamp = (uint64_t)sys_timer_get_ms();
        snprintf(dst, dst_len, "voice_%llu", (unsigned long long)stamp);
        dst[dst_len - 1] = '\0';
    } else {
        dst[idx] = '\0';
    }
}

static void chat_manager_extract_extension(const char *url, char *ext_buf, size_t ext_buf_len)
{
    if (!ext_buf || ext_buf_len == 0) {
        return;
    }
    ext_buf[0] = '\0';
    if (!url || !url[0]) {
        return;
    }
    size_t url_len = strlen(url);
    size_t limit = strcspn(url, "?#");
    if (limit < url_len) {
        url_len = limit;
    }
    const char *dot = NULL;
    for (size_t i = 0; i < url_len; ++i) {
        char ch = url[i];
        if (ch == '.' && i + 1 < url_len) {
            dot = &url[i];
        } else if (ch == '/' || ch == '\\') {
            dot = NULL;
        }
    }
    if (!dot || dot >= url + url_len - 1) {
        return;
    }
    size_t ext_len = url_len - (size_t)(dot - url) - 1;
    if (ext_len + 1 > ext_buf_len) {
        ext_len = ext_buf_len - 1;
    }
    for (size_t i = 0; i < ext_len; ++i) {
        ext_buf[i] = (char)tolower((unsigned char)dot[1 + i]);
    }
    ext_buf[ext_len] = '\0';
}

static void chat_manager_generate_voice_file_path(const char *message_id,
                                                  const char *ext,
                                                  char *out_path,
                                                  size_t out_len)
{
    if (!out_path || out_len == 0) {
        return;
    }
    char safe_id[CHAT_MANAGER_MAX_MESSAGE_ID_LEN];
    chat_manager_make_safe_filename(message_id, safe_id, sizeof(safe_id));
    const char *final_ext = (ext && ext[0]) ? ext : "amr";
    snprintf(out_path, out_len, "%s%s.%s", CHAT_MANAGER_VOICE_DIR_PATH, safe_id, final_ext);
    out_path[out_len - 1] = '\0';
}

static bool chat_manager_trim_root_path(char *out, size_t out_len)
{
    if (!out || out_len == 0) {
        return false;
    }
    if (!CONFIG_ROOT_PATH[0]) {
        out[0] = '\0';
        return false;
    }
    snprintf(out, out_len, "%s", CONFIG_ROOT_PATH);
    out[out_len - 1] = '\0';
    size_t len = strlen(out);
    while (len > 0 && out[len - 1] == '/') {
        out[--len] = '\0';
    }
    return len > 0;
}

static bool chat_manager_voice_dir_exists(void)
{
    char dir_path[CHAT_MANAGER_MAX_MEDIA_PATH_LEN] = {0};
    snprintf(dir_path, sizeof(dir_path), "%s", CHAT_MANAGER_VOICE_DIR_PATH);
    dir_path[sizeof(dir_path) - 1] = '\0';

    if (dir_path[0] && fdir_exist(dir_path)) {
        return true;
    }

    size_t len = strlen(dir_path);
    while (len > 0 && (dir_path[len - 1] == '/' || dir_path[len - 1] == '\\')) {
        dir_path[--len] = '\0';
    }

    if (len > 0 && fdir_exist(dir_path)) {
        return true;
    }

    return false;
}

static bool chat_manager_ensure_voice_dir(void)
{
    static bool s_voice_dir_ready = false;
    if (s_voice_dir_ready) {
        return true;
    }
    if (!storage_device_ready()) {
        printf("%s voice dir wait storage ready\n", CHAT_MANAGER_LOG_TAG);
        return false;
    }

    if (chat_manager_voice_dir_exists()) {
        s_voice_dir_ready = true;
        printf("%s voice dir reuse existing path=%s\n",
               CHAT_MANAGER_LOG_TAG,
               CHAT_MANAGER_VOICE_DIR_PATH);
        return true;
    }

    int ret = fmk_dir(CONFIG_ROOT_PATH, CHAT_MANAGER_VOICE_DIR_NAME, 0);

    if (ret != 0 && ret != -EEXIST) {
        char root_path[CHAT_MANAGER_MAX_MEDIA_PATH_LEN] = {0};
        if (chat_manager_trim_root_path(root_path, sizeof(root_path))) {
            ret = fmk_dir(root_path, CHAT_MANAGER_VOICE_DIR_NAME, 0);
            if (ret != 0 && ret != -EEXIST) {
                char alt_folder[] = "chat_voice";
                ret = fmk_dir(root_path, alt_folder, 0);
            }
        }
    }

    if (ret != 0 && ret != -EEXIST) {
        char alt_folder[] = "chat_voice";
        ret = fmk_dir(CONFIG_ROOT_PATH, alt_folder, 0);
    }

    if (ret != 0 && ret != -EEXIST && chat_manager_voice_dir_exists()) {
        ret = 0;
    }

    if (ret == 0 || ret == -EEXIST) {
        s_voice_dir_ready = true;
        printf("%s voice dir ready path=%s\n", CHAT_MANAGER_LOG_TAG, CHAT_MANAGER_VOICE_DIR_PATH);
        return true;
    } else {
        printf("%s voice dir create failed ret=%d\n", CHAT_MANAGER_LOG_TAG, ret);
        return false;
    }
}

static bool chat_manager_should_download_voice(const struct chat_message_record *record)
{
    return record &&
           record->content_type == CHAT_MESSAGE_CONTENT_VOICE &&
           record->direction == CHAT_MESSAGE_DIRECTION_INCOMING &&
           record->media_path[0] &&
           chat_manager_is_http_url(record->media_path);
}

static void chat_manager_ensure_message_id(struct chat_message_record *record)
{
    if (!record) {
        return;
    }
    if (!record->message_id[0]) {
        uint64_t stamp = record->timestamp_ms ? record->timestamp_ms : (uint64_t)sys_timer_get_ms();
        snprintf(record->message_id,
                 sizeof(record->message_id),
                 "auto_%llu",
                 (unsigned long long)stamp);
        record->message_id[sizeof(record->message_id) - 1] = '\0';
    }
}

static bool chat_manager_prepare_incoming_voice_record(struct chat_message_record *record,
                                                       char *out_local_path,
                                                       size_t local_path_len,
                                                       char *out_ext,
                                                       size_t ext_len)
{
    if (!record || !chat_manager_should_download_voice(record)) {
        return false;
    }
    if (out_ext && ext_len) {
        chat_manager_extract_extension(record->media_path, out_ext, ext_len);
    }
    if (out_local_path && local_path_len) {
        const char *ext = (out_ext && out_ext[0]) ? out_ext : NULL;
        chat_manager_generate_voice_file_path(record->message_id,
                                              ext,
                                              out_local_path,
                                              local_path_len);
        FILE *existing = fopen(out_local_path, "r");
        if (existing) {
            size_t file_size = (size_t)flen(existing);
            fclose(existing);
            chat_manager_copy_string(record->media_path,
                                     sizeof(record->media_path),
                                     out_local_path);
            if (file_size > 0 && file_size <= UINT32_MAX) {
                record->size_bytes = (uint32_t)file_size;
            }
            printf("%s voice reuse local file msg=%s path=%s\n",
                   CHAT_MANAGER_LOG_TAG,
                   record->message_id[0] ? record->message_id : "<unknown>",
                   out_local_path);
            return false;
        }
    }
    return true;
}

static int chat_manager_schedule_voice_download(const char *group_id,
                                                const struct chat_message_record *record,
                                                const char *local_path_hint,
                                                const char *ext_hint)
{
    if (!group_id || !group_id[0] || !record) {
        return -EINVAL;
    }
    if (!chat_manager_should_download_voice(record)) {
        return 0;
    }
    struct chat_voice_download_task *task =
        (struct chat_voice_download_task *)malloc(sizeof(struct chat_voice_download_task));
    if (!task) {
        printf("%s voice download malloc fail group=%s msg=%s\n",
               CHAT_MANAGER_LOG_TAG,
               group_id,
               record->message_id[0] ? record->message_id : "<none>");
        return -ENOMEM;
    }
    memset(task, 0, sizeof(*task));
    chat_manager_copy_string(task->group_id, sizeof(task->group_id), group_id);
    chat_manager_copy_string(task->message_id, sizeof(task->message_id), record->message_id);
    chat_manager_copy_string(task->url, sizeof(task->url), record->media_path);

    if (local_path_hint && local_path_hint[0]) {
        chat_manager_copy_string(task->file_path, sizeof(task->file_path), local_path_hint);
    } else {
        char ext_buf[CHAT_MANAGER_MAX_FILE_EXT_LEN] = {0};
        if (ext_hint && ext_hint[0]) {
            chat_manager_copy_string(ext_buf, sizeof(ext_buf), ext_hint);
        } else {
            chat_manager_extract_extension(record->media_path, ext_buf, sizeof(ext_buf));
        }
        chat_manager_generate_voice_file_path(record->message_id,
                                              ext_buf[0] ? ext_buf : NULL,
                                              task->file_path,
                                              sizeof(task->file_path));
    }

    task->expected_size = record->size_bytes;

    int ret = thread_fork("chat_voice_dl",
                          CHAT_MANAGER_VOICE_DOWNLOAD_THREAD_PRIO,
                          CHAT_MANAGER_VOICE_DOWNLOAD_THREAD_STACK,
                          0,
                          NULL,
                          chat_manager_voice_download_thread,
                          task);
    if (ret) {
        printf("%s voice download thread start fail group=%s msg=%s ret=%d\n",
               CHAT_MANAGER_LOG_TAG,
               task->group_id,
               task->message_id[0] ? task->message_id : "<none>",
               ret);
        free(task);
        return ret;
    }

    printf("%s voice download scheduled group=%s msg=%s url=%s dest=%s\n",
           CHAT_MANAGER_LOG_TAG,
           task->group_id,
           task->message_id[0] ? task->message_id : "<none>",
           task->url,
           task->file_path);
    return 0;
}

/**
 * @brief 按 groupId 查找已有的好友槽位。
 */
static void chat_manager_on_voice_download_finish(const struct chat_voice_download_task *task,
                                                  int status,
                                                  size_t written_bytes)
{
    if (!task) {
        return;
    }

    if (status == 0) {
        chat_manager_lock();
        int slot_index = chat_manager_find_slot_by_group(task->group_id);
        if (slot_index >= 0) {
            struct chat_friend_slot *slot = &s_friend_slots[slot_index];
            for (size_t i = 0; i < CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND; ++i) {
                struct chat_message_record *msg = &slot->messages[i];
                if (msg->content_type != CHAT_MESSAGE_CONTENT_VOICE) {
                    continue;
                }
                if (msg->direction != CHAT_MESSAGE_DIRECTION_INCOMING) {
                    continue;
                }
                if (!msg->message_id[0]) {
                    continue;
                }
                if (strcmp(msg->message_id, task->message_id) == 0) {
                    chat_manager_copy_string(msg->media_path,
                                             sizeof(msg->media_path),
                                             task->file_path);
                    if (written_bytes > 0 && written_bytes <= UINT32_MAX) {
                        msg->size_bytes = (uint32_t)written_bytes;
                    }
              printf("%s voice record updated group=%s slot=%u msg=%s dir=%d new_path=%s size=%u\n",
                  CHAT_MANAGER_LOG_TAG,
                  task->group_id,
                  (unsigned int)i,
                  msg->message_id[0] ? msg->message_id : "<empty>",
                  (int)msg->direction,
                  msg->media_path[0] ? msg->media_path : "<empty>",
                  (unsigned int)msg->size_bytes);
                    break;
                }
            }
        }
        chat_manager_unlock();

#if defined(CONFIG_UI_STYLE_LY_ENABLE)
        chat_friend_history_notify_data_changed(task->group_id, false);
#endif

        printf("%s voice download success group=%s msg=%s bytes=%u path=%s\n",
               CHAT_MANAGER_LOG_TAG,
               task->group_id,
               task->message_id[0] ? task->message_id : "<none>",
               (unsigned int)written_bytes,
               task->file_path);
    } else {
        printf("%s voice download failed group=%s msg=%s status=%d\n",
               CHAT_MANAGER_LOG_TAG,
               task->group_id && task->group_id[0] ? task->group_id : "<none>",
               task->message_id && task->message_id[0] ? task->message_id : "<none>",
               status);
    }
}

static int chat_manager_http_download_cb(void *http_ctx,
                                               void *buf,
                                               unsigned int size,
                                               void *priv,
                                               httpin_status status)
{
    struct chat_http_download_ctx *ctx = (struct chat_http_download_ctx *)priv;
    if (!ctx) {
        return -1;
    }

    switch (status) {
    case HTTPIN_HEADER:
        ctx->written_bytes = 0;
        ctx->status = 0;
        if (ctx->fp) {
            fseek(ctx->fp, 0, SEEK_SET);
        }
        break;

    case HTTPIN_PROGRESS:
        if (size > 0 && ctx->fp && buf) {
            size_t wrote = fwrite(buf, 1, size, ctx->fp);
            if (wrote != size) {
                ctx->status = -EIO;
                return -1;
            }
            ctx->written_bytes += wrote;
        }
        break;

    case HTTPIN_FINISHED:
        ctx->status = 0;
        break;

    case HTTPIN_ABORT:
        ctx->status = -ECONNABORTED;
        break;

    case HTTPIN_ERROR:
        ctx->status = -EIO;
        break;

    default:
        break;
    }

    return 0;
}

static void chat_manager_voice_download_thread(void *priv)
{
    struct chat_voice_download_task *task = (struct chat_voice_download_task *)priv;
    if (!task) {
        printf("%s voice download thread exit, task null\n", CHAT_MANAGER_LOG_TAG);
        return;
    }

    int status = 0;
    size_t written_bytes = 0;

    printf("%s voice download start group=%s msg=%s url=%s -> %s\n",
           CHAT_MANAGER_LOG_TAG,
           task->group_id,
           task->message_id[0] ? task->message_id : "<none>",
           task->url,
           task->file_path);

    u32 waited_ms = 0;
    while (!storage_device_ready() && waited_ms < CHAT_MANAGER_STORAGE_WAIT_TOTAL_MS) {
        os_time_dly(CHAT_MANAGER_STORAGE_WAIT_SLICE_TICKS);
        waited_ms += (u32)CHAT_MANAGER_STORAGE_WAIT_SLICE_TICKS * 10;
    }

    if (!storage_device_ready()) {
        status = -ENODEV;
        printf("%s voice download storage not ready after wait\n", CHAT_MANAGER_LOG_TAG);
        goto exit;
    }

    bool dir_ready = false;
    for (int attempt = 0; attempt < CHAT_MANAGER_VOICE_DIR_MAX_RETRY && !dir_ready; ++attempt) {
        dir_ready = chat_manager_ensure_voice_dir();
        if (!dir_ready) {
            os_time_dly(CHAT_MANAGER_STORAGE_WAIT_SLICE_TICKS);
        }
    }

    if (!dir_ready) {
        status = -EIO;
        printf("%s voice download give up ensure dir\n", CHAT_MANAGER_LOG_TAG);
        goto exit;
    }

    FILE *fp = fopen(task->file_path, "w+b");
    if (!fp) {
        status = -EIO;
        printf("%s voice download fopen fail path=%s errno=%d\n",
               CHAT_MANAGER_LOG_TAG,
               task->file_path,
               errno);
        goto exit;
    }

    struct chat_http_download_ctx cb_ctx = {
        .fp = fp,
        .written_bytes = 0,
        .status = 0,
    };

    httpcli_ctx ctx = {0};
    ctx.url = task->url;
    ctx.timeout_millsec = CHAT_MANAGER_VOICE_DOWNLOAD_TIMEOUT_MS;
    ctx.connection = "close";
    ctx.cb = chat_manager_http_download_cb;
    ctx.priv = &cb_ctx;

    httpin_error err = httpcli_get(&ctx);
    fclose(fp);

    if (err != HERROR_OK || cb_ctx.status) {
        status = cb_ctx.status ? cb_ctx.status : err;
        if (!status) {
            status = -EIO;
        }
        printf("%s voice download http fail err=%d status=%d\n",
               CHAT_MANAGER_LOG_TAG,
               err,
               cb_ctx.status);
        fdelete_by_name(task->file_path);
        goto exit;
    }

    written_bytes = cb_ctx.written_bytes;
    if (task->expected_size && written_bytes != task->expected_size) {
        printf("%s voice download size mismatch expect=%u actual=%u\n",
               CHAT_MANAGER_LOG_TAG,
               (unsigned int)task->expected_size,
               (unsigned int)written_bytes);
    }

exit:
    chat_manager_on_voice_download_finish(task, status, written_bytes);
    free(task);
}

static int chat_manager_find_slot_by_group(const char *group_id)
{
    if (!group_id || !group_id[0]) {
        printf("%s find slot failed invalid group_id\n", CHAT_MANAGER_LOG_TAG);
        return -1;
    }
    for (int i = 0; i < CHAT_MANAGER_MAX_FRIENDS; ++i) {
        if (s_friend_slots[i].info.in_use && strcmp(s_friend_slots[i].info.group_id, group_id) == 0) {
            printf("%s find slot group=%s index=%d\n", CHAT_MANAGER_LOG_TAG, group_id, i);
            return i;
        }
    }
    printf("%s find slot miss group=%s\n", CHAT_MANAGER_LOG_TAG, group_id);
    return -1;
}

/**
 * @brief 为新好友分配槽位，若已满返回 -1。
 */
static int chat_manager_alloc_slot(const char *group_id)
{
    for (int i = 0; i < CHAT_MANAGER_MAX_FRIENDS; ++i) {
        if (!s_friend_slots[i].info.in_use) {
            chat_manager_reset_slot(&s_friend_slots[i]);
            s_friend_slots[i].info.in_use = true;
            chat_manager_copy_string(s_friend_slots[i].info.group_id,
                                     sizeof(s_friend_slots[i].info.group_id),
                                     group_id);
            printf("%s alloc slot group=%s index=%d\n", CHAT_MANAGER_LOG_TAG,
                   group_id ? group_id : "<null>", i);
            return i;
        }
    }
    printf("%s alloc slot failed group=%s\n", CHAT_MANAGER_LOG_TAG,
           group_id ? group_id : "<null>");
    return -1;
}

/**
 * @brief 将服务器返回的好友字段写入缓存结构。
 */
static void chat_manager_apply_friend_fields(struct chat_friend_entry *entry,
                                             int group_type,
                                             const char *group_name,
                                             const char *group_image,
                                             int relationship_image_id,
                                             const char *call_openid,
                                             int can_video)
{
    if (!entry) {
        printf("%s apply friend fields skipped entry null\n", CHAT_MANAGER_LOG_TAG);
        return;
    }
    printf("%s apply friend fields group=%s type=%d name=%s image=%s rel_img=%d openid=%s can_video=%d\n",
           CHAT_MANAGER_LOG_TAG,
           entry->group_id,
           group_type,
           group_name ? group_name : "",
           group_image ? group_image : "",
           relationship_image_id,
           call_openid ? call_openid : "",
           can_video);
    entry->group_type = group_type;
    entry->relationship_image_id = relationship_image_id;
    entry->can_video = (can_video != 0);
    if (group_name) {
        chat_manager_copy_string(entry->group_name, sizeof(entry->group_name), group_name);
    }
    if (group_image) {
        chat_manager_copy_string(entry->group_image, sizeof(entry->group_image), group_image);
    }
    if (call_openid) {
        chat_manager_copy_string(entry->call_openid, sizeof(entry->call_openid), call_openid);
    }
}

/**
 * @brief 将单条消息写入好友的环形缓存。
 */
static void chat_manager_append_message(struct chat_friend_slot *slot,
                                        const struct chat_message_record *record)
{
    if (!slot || !record) {
        printf("%s append msg skipped slot=%p record=%p\n", CHAT_MANAGER_LOG_TAG, slot, record);
        return;
    }
    printf("%s append msg group=%s dir=%u id=%s type=%u timestamp=%llu\n",
           CHAT_MANAGER_LOG_TAG,
           slot->info.group_id,
        (unsigned int)record->direction,
           record->message_id[0] ? record->message_id : "<none>",
           (unsigned int)record->content_type,
           (unsigned long long)record->timestamp_ms);
    struct chat_message_record *target = &slot->messages[slot->write_index];
    chat_manager_release_message(target);
    *target = *record;
    chat_manager_ensure_message_id(target);

    bool schedule_download = false;
    char download_path[CHAT_MANAGER_MAX_MEDIA_PATH_LEN] = {0};
    char download_ext[CHAT_MANAGER_MAX_FILE_EXT_LEN] = {0};
    if (chat_manager_should_download_voice(target)) {
        schedule_download = chat_manager_prepare_incoming_voice_record(target,
                                                                       download_path,
                                                                       sizeof(download_path),
                                                                       download_ext,
                                                                       sizeof(download_ext));
    }
    slot->write_index = (uint8_t)((slot->write_index + 1) % CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND);
    if (slot->count < CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND) {
        slot->count++;
    }
#if defined(CONFIG_UI_STYLE_LY_ENABLE)
    chat_friend_history_notify_data_changed(slot->info.group_id, true);
#endif
    if (schedule_download) {
        int dl_ret = chat_manager_schedule_voice_download(slot->info.group_id,
                                                          target,
                                                          download_path,
                                                          download_ext);
        if (dl_ret) {
            printf("%s schedule voice download failed group=%s msg=%s ret=%d\n",
                   CHAT_MANAGER_LOG_TAG,
                   slot->info.group_id,
                   target->message_id[0] ? target->message_id : "<none>",
                   dl_ret);
        }
    }
}

void chat_manager_init(void)
{
    printf("%s init start\n", CHAT_MANAGER_LOG_TAG);
    if (!s_chat_lock_ready) {
        if (os_mutex_create(&s_chat_lock) == 0) {
            s_chat_lock_ready = true;
            printf("%s mutex created\n", CHAT_MANAGER_LOG_TAG);
        }
    }

    chat_manager_lock();
    memset(s_friend_slots, 0, sizeof(s_friend_slots));
    s_last_group_list_timestamp_ms = 0;
    chat_manager_unlock();
    printf("%s init done\n", CHAT_MANAGER_LOG_TAG);
}

int chat_manager_request_group_list(void)
{
    printf("%s request group list\n", CHAT_MANAGER_LOG_TAG);
    int err = wifi_camera_ws_send_get_chat_user_list();
    if (err) {
        printf("%s request group list failed:%d\n", CHAT_MANAGER_LOG_TAG, err);
    } else {
        printf("%s request group list success\n", CHAT_MANAGER_LOG_TAG);
    }
    return err;
}

int chat_manager_request_sync_friend(void)
{
    printf("%s request sync friend\n", CHAT_MANAGER_LOG_TAG);
    int err = wifi_camera_ws_send_sync_friend_request();
    if (err) {
        printf("%s request sync friend failed:%d\n", CHAT_MANAGER_LOG_TAG, err);
    } else {
        printf("%s request sync friend success\n", CHAT_MANAGER_LOG_TAG);
    }
    return err;
}

int chat_manager_handle_group_list_json(const struct cJSON *root)
{
    printf("%s handle group list enter root=%p\n", CHAT_MANAGER_LOG_TAG, root);
    if (!root) {
        printf("%s handle group list fail root null\n", CHAT_MANAGER_LOG_TAG);
        return -EINVAL;
    }

    /*
     * 服务器回复可能包裹在 { "data": { ... } } 中，优先尝试解析 data 节点。
     */
    const cJSON *payload = root;
    const cJSON *maybe_data = cJSON_GetObjectItemCaseSensitive(root, "data");
    if (maybe_data && cJSON_IsObject(maybe_data)) {
        const cJSON *maybe_group_list = cJSON_GetObjectItemCaseSensitive(maybe_data, "groupList");
        if (maybe_group_list) {
            payload = maybe_data;
            printf("%s handle group list use data node\n", CHAT_MANAGER_LOG_TAG);
        }
    }

    const cJSON *timestamp_item = cJSON_GetObjectItemCaseSensitive(payload, "timestamp");
    uint64_t timestamp_ms = 0;
    if (cJSON_IsNumber(timestamp_item) && timestamp_item->valuedouble > 0) {
        timestamp_ms = (uint64_t)(timestamp_item->valuedouble + 0.5);
        printf("%s handle group list timestamp=%llu\n", CHAT_MANAGER_LOG_TAG,
               (unsigned long long)timestamp_ms);
    }

    const cJSON *group_list = cJSON_GetObjectItemCaseSensitive(payload, "groupList");
    if (!cJSON_IsArray(group_list)) {
        printf("%s handle group list fail groupList missing\n", CHAT_MANAGER_LOG_TAG);
        return -EINVAL;
    }

    chat_manager_lock();

    for (int i = 0; i < CHAT_MANAGER_MAX_FRIENDS; ++i) {
        if (s_friend_slots[i].info.in_use) {
            s_friend_slots[i].info.source_mask &= (uint8_t)~CHAT_MANAGER_FRIEND_SOURCE_GROUP_LIST;
        }
    }

    size_t processed = 0;
    cJSON *mutable_group_list = (cJSON *)group_list;
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, mutable_group_list) {
        if (processed >= CHAT_MANAGER_MAX_FRIENDS) {
            break;
        }
        const cJSON *group_id_item = cJSON_GetObjectItemCaseSensitive(item, "groupId");
        if (!cJSON_IsString(group_id_item) || !group_id_item->valuestring || !group_id_item->valuestring[0]) {
            printf("%s handle group list skip entry missing id\n", CHAT_MANAGER_LOG_TAG);
            continue;
        }

        const char *group_id = group_id_item->valuestring;
        const cJSON *group_type_item = cJSON_GetObjectItemCaseSensitive(item, "groupType");
        const cJSON *group_name_item = cJSON_GetObjectItemCaseSensitive(item, "groupName");
        const cJSON *group_image_item = cJSON_GetObjectItemCaseSensitive(item, "groupImage");
        const cJSON *relationship_image_id_item = cJSON_GetObjectItemCaseSensitive(item, "relationship_image_id");
        const cJSON *call_openid_item = cJSON_GetObjectItemCaseSensitive(item, "callOpenid");
        const cJSON *can_video_item = cJSON_GetObjectItemCaseSensitive(item, "canVideo");

        int group_type = cJSON_IsNumber(group_type_item) ? (int)(group_type_item->valuedouble + 0.5f) : 0;
        int relationship_image_id = cJSON_IsNumber(relationship_image_id_item) ? (int)(relationship_image_id_item->valuedouble + 0.5f) : 0;
        int can_video = cJSON_IsNumber(can_video_item) ? (int)(can_video_item->valuedouble + 0.5f) : 0;

        int slot_index = chat_manager_find_slot_by_group(group_id);
        if (slot_index < 0) {
            slot_index = chat_manager_alloc_slot(group_id);
        }
        if (slot_index < 0) {
            printf("%s no slot for group %s\n", CHAT_MANAGER_LOG_TAG, group_id);
            continue;
        }

        struct chat_friend_slot *slot = &s_friend_slots[slot_index];
        slot->info.in_use = true;
        slot->info.source_mask |= CHAT_MANAGER_FRIEND_SOURCE_GROUP_LIST;
        chat_manager_apply_friend_fields(&slot->info,
                                         group_type,
                                         cJSON_IsString(group_name_item) ? group_name_item->valuestring : "",
                                         cJSON_IsString(group_image_item) ? group_image_item->valuestring : "",
                                         relationship_image_id,
                                         cJSON_IsString(call_openid_item) ? call_openid_item->valuestring : "",
                                         can_video);
        processed++;
        printf("%s handle group list updated group=%s slot=%d count=%zu\n",
               CHAT_MANAGER_LOG_TAG, group_id, slot_index, processed);
    }

    for (int i = 0; i < CHAT_MANAGER_MAX_FRIENDS; ++i) {
        if (s_friend_slots[i].info.in_use && s_friend_slots[i].info.source_mask == 0) {
            chat_manager_reset_slot(&s_friend_slots[i]);
        }
    }

    if (timestamp_ms) {
        s_last_group_list_timestamp_ms = timestamp_ms;
    }

    chat_manager_unlock();
    printf("%s handle group list finish processed=%zu\n", CHAT_MANAGER_LOG_TAG, processed);
    return 0;
}

int chat_manager_handle_sync_friend_json(const struct cJSON *root)
{
    printf("%s handle sync friend enter root=%p\n", CHAT_MANAGER_LOG_TAG, root);
    if (!root) {
        printf("%s handle sync friend fail root null\n", CHAT_MANAGER_LOG_TAG);
        return -EINVAL;
    }

    const cJSON *payload = root;
    const cJSON *maybe_data = cJSON_GetObjectItemCaseSensitive(root, "data");
    if (maybe_data && cJSON_IsObject(maybe_data)) {
        const cJSON *maybe_array = cJSON_GetObjectItemCaseSensitive(maybe_data, "syncfriends");
        if (maybe_array) {
            payload = maybe_data;
            printf("%s handle sync friend use data node\n", CHAT_MANAGER_LOG_TAG);
        }
    }

    const cJSON *syncfriends = cJSON_GetObjectItemCaseSensitive(payload, "syncfriends");
    if (!cJSON_IsArray(syncfriends)) {
        printf("%s handle sync friend fail list missing\n", CHAT_MANAGER_LOG_TAG);
        return -EINVAL;
    }

    chat_manager_lock();
    for (int i = 0; i < CHAT_MANAGER_MAX_FRIENDS; ++i) {
        if (s_friend_slots[i].info.in_use) {
            s_friend_slots[i].info.source_mask &= (uint8_t)~CHAT_MANAGER_FRIEND_SOURCE_SYNC_FRIEND;
        }
    }
    chat_manager_unlock();

    size_t processed = 0;
    cJSON *mutable_array = (cJSON *)syncfriends;
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, mutable_array) {
        const cJSON *imei_item = cJSON_GetObjectItemCaseSensitive(item, "imei");
        if (!cJSON_IsString(imei_item) || !imei_item->valuestring || !imei_item->valuestring[0]) {
            printf("%s handle sync friend skip invalid imei\n", CHAT_MANAGER_LOG_TAG);
            continue;
        }
        const char *imei = imei_item->valuestring;

        const cJSON *name_item = cJSON_GetObjectItemCaseSensitive(item, "name");
        const cJSON *image_item = cJSON_GetObjectItemCaseSensitive(item, "image");
        const char *name = (cJSON_IsString(name_item) && name_item->valuestring) ? name_item->valuestring : "";
        const char *image_url = (cJSON_IsString(image_item) && image_item->valuestring) ? image_item->valuestring : "";

        chat_manager_lock();
        int slot_index = chat_manager_find_slot_by_group(imei);
        if (slot_index < 0) {
            slot_index = chat_manager_alloc_slot(imei);
        }
        if (slot_index >= 0) {
            struct chat_friend_slot *slot = &s_friend_slots[slot_index];
            slot->info.in_use = true;
            slot->info.source_mask |= CHAT_MANAGER_FRIEND_SOURCE_SYNC_FRIEND;
            chat_manager_apply_friend_fields(&slot->info,
                                             1,
                                             name,
                                             image_url,
                                             0,
                                             NULL,
                                             0);
            processed++;
            printf("%s sync friend updated imei=%s slot=%d name=%s\n",
                   CHAT_MANAGER_LOG_TAG,
                   imei,
                   slot_index,
                   name);
        } else {
            printf("%s sync friend no slot imei=%s\n", CHAT_MANAGER_LOG_TAG, imei);
        }
        chat_manager_unlock();
    }

    chat_manager_lock();
    for (int i = 0; i < CHAT_MANAGER_MAX_FRIENDS; ++i) {
        if (s_friend_slots[i].info.in_use && s_friend_slots[i].info.source_mask == 0) {
            chat_manager_reset_slot(&s_friend_slots[i]);
        }
    }
    chat_manager_unlock();

    printf("%s handle sync friend finish processed=%zu\n", CHAT_MANAGER_LOG_TAG, processed);
    return 0;
}

int chat_manager_handle_down_chat_voice(const struct cJSON *root)
{
    printf("%s handle down chat voice enter root=%p\n", CHAT_MANAGER_LOG_TAG, root);
    if (!root) {
        printf("%s handle down chat voice fail root null\n", CHAT_MANAGER_LOG_TAG);
        return -EINVAL;
    }

    /*
     * 消息下发结构与好友列表类似，也可能有 data 包裹层。
     * 这里优先尝试解析 data ，否则退回最外层。
     */
    const cJSON *payload = root;
    const cJSON *maybe_data = cJSON_GetObjectItemCaseSensitive(root, "data");
    if (maybe_data && cJSON_IsObject(maybe_data)) {
        const cJSON *maybe_group_id = cJSON_GetObjectItemCaseSensitive(maybe_data, "groupId");
        if (maybe_group_id) {
            payload = maybe_data;
            printf("%s handle down chat voice use data node\n", CHAT_MANAGER_LOG_TAG);
        }
    }

    const cJSON *group_id_item = cJSON_GetObjectItemCaseSensitive(payload, "groupId");
    if (!cJSON_IsString(group_id_item) || !group_id_item->valuestring) {
        printf("%s handle down chat voice fail groupId missing\n", CHAT_MANAGER_LOG_TAG);
        return -EINVAL;
    }
    const char *group_id = group_id_item->valuestring;
    printf("%s handle down chat voice group=%s\n", CHAT_MANAGER_LOG_TAG, group_id);

    const cJSON *group_type_item = cJSON_GetObjectItemCaseSensitive(payload, "groupType");
    const cJSON *relationship_item = cJSON_GetObjectItemCaseSensitive(payload, "relationship");
    const cJSON *relationship_image_id_item = cJSON_GetObjectItemCaseSensitive(payload, "relationship_image_id");
    const cJSON *call_openid_item = cJSON_GetObjectItemCaseSensitive(payload, "callOpenid");
    const cJSON *can_video_item = cJSON_GetObjectItemCaseSensitive(payload, "canVideo");
    const cJSON *sender_avatar_item = cJSON_GetObjectItemCaseSensitive(payload, "senderAvatar");
    const cJSON *content_type_item = cJSON_GetObjectItemCaseSensitive(payload, "contentType");
    const cJSON *content_item = cJSON_GetObjectItemCaseSensitive(payload, "content");
    const cJSON *url_item = cJSON_GetObjectItemCaseSensitive(payload, "url");
    const cJSON *duration_item = cJSON_GetObjectItemCaseSensitive(payload, "duration");
    const cJSON *size_item = cJSON_GetObjectItemCaseSensitive(payload, "size");
    const cJSON *id_item = cJSON_GetObjectItemCaseSensitive(payload, "id");
    const cJSON *timestamp_item = cJSON_GetObjectItemCaseSensitive(payload, "timestamp");
    const cJSON *bq_id_item = cJSON_GetObjectItemCaseSensitive(payload, "bqId");

    int group_type = cJSON_IsNumber(group_type_item) ? (int)(group_type_item->valuedouble + 0.5f) : -1;
    int relationship_image_id = cJSON_IsNumber(relationship_image_id_item) ? (int)(relationship_image_id_item->valuedouble + 0.5f) : -1;
    int can_video = cJSON_IsNumber(can_video_item) ? (int)(can_video_item->valuedouble + 0.5f) : -1;
    int content_type = cJSON_IsNumber(content_type_item) ? (int)(content_type_item->valuedouble + 0.5f) : CHAT_MESSAGE_CONTENT_TEXT;

    struct chat_message_record record;
    memset(&record, 0, sizeof(record));
    record.content_type = (uint8_t)content_type;
    record.direction = CHAT_MESSAGE_DIRECTION_INCOMING;
    record.duration = cJSON_IsNumber(duration_item) ? (float)duration_item->valuedouble : 0.0f;
    record.size_bytes = cJSON_IsNumber(size_item) ? (uint32_t)(size_item->valuedouble + 0.5f) : 0U;
    record.timestamp_ms = cJSON_IsNumber(timestamp_item) ? (uint64_t)(timestamp_item->valuedouble + 0.5) : 0;
    printf("%s parsed message type=%d duration=%.2f size=%u timestamp=%llu\n",
        CHAT_MANAGER_LOG_TAG,
        content_type,
        record.duration,
        (unsigned int)record.size_bytes,
        (unsigned long long)record.timestamp_ms);

    if (cJSON_IsString(relationship_item) && relationship_item->valuestring) {
        chat_manager_copy_string(record.relationship, sizeof(record.relationship), relationship_item->valuestring);
    }

    if (cJSON_IsString(id_item) && id_item->valuestring) {
        chat_manager_copy_string(record.message_id, sizeof(record.message_id), id_item->valuestring);
    }

    if (record.content_type == CHAT_MESSAGE_CONTENT_TEXT) {
        if (cJSON_IsString(content_item) && content_item->valuestring) {
            chat_manager_copy_string(record.content, sizeof(record.content), content_item->valuestring);
            printf("%s parsed message content=%s\n", CHAT_MANAGER_LOG_TAG, record.content);
            record.size_bytes = (uint32_t)strlen(record.content);
        }
    } else if (record.content_type == CHAT_MESSAGE_CONTENT_EMOJI) {
        if (cJSON_IsString(bq_id_item) && bq_id_item->valuestring) {
            chat_manager_copy_string(record.content, sizeof(record.content), bq_id_item->valuestring);
        }
    }

    if (cJSON_IsString(url_item) && url_item->valuestring) {
        chat_manager_copy_string(record.media_path, sizeof(record.media_path), url_item->valuestring);
    }

    /* 将消息写入本地缓存，需要持锁保护好友槽位。 */
    chat_manager_lock();

    int slot_index = chat_manager_find_slot_by_group(group_id);
    if (slot_index < 0) {
        slot_index = chat_manager_alloc_slot(group_id);
    }
    if (slot_index < 0) {
        chat_manager_unlock();
        printf("%s no available slot for group %s\n", CHAT_MANAGER_LOG_TAG, group_id);
        return -ENOSPC;
    }

    struct chat_friend_slot *slot = &s_friend_slots[slot_index];
    slot->info.in_use = true;
    slot->info.source_mask |= CHAT_MANAGER_FRIEND_SOURCE_PP_MESSAGE;
    const char *new_name = NULL;
    if (cJSON_IsString(relationship_item) && relationship_item->valuestring) {
        new_name = relationship_item->valuestring;
    }
    const char *new_image = NULL;
    const char *new_openid = NULL;
    if (cJSON_IsString(call_openid_item) && call_openid_item->valuestring) {
        new_openid = call_openid_item->valuestring;
    }
    if (cJSON_IsString(sender_avatar_item) && sender_avatar_item->valuestring) {
        new_image = sender_avatar_item->valuestring;
    }
    int resolved_group_type = (group_type >= 0) ? group_type : slot->info.group_type;
    int resolved_relationship_image_id = (relationship_image_id >= 0) ? relationship_image_id : slot->info.relationship_image_id;
    int resolved_can_video = (can_video >= 0) ? can_video : slot->info.can_video;
    chat_manager_apply_friend_fields(&slot->info,
                                     resolved_group_type,
                                     new_name,
                                     new_image,
                                     resolved_relationship_image_id,
                                     new_openid,
                                     resolved_can_video);

    chat_manager_append_message(slot, &record);

    chat_manager_unlock();
    printf("%s handle down chat voice finish group=%s slot=%d\n", CHAT_MANAGER_LOG_TAG, group_id, slot_index);
    return 0;
}

int chat_manager_handle_down_pp_message(const struct cJSON *root)
{
    printf("%s handle down pp message enter root=%p\n", CHAT_MANAGER_LOG_TAG, root);
    if (!root) {
        printf("%s handle down pp message fail root null\n", CHAT_MANAGER_LOG_TAG);
        return -EINVAL;
    }

    const cJSON *payload = root;
    const cJSON *maybe_data = cJSON_GetObjectItemCaseSensitive(root, "data");
    if (maybe_data && cJSON_IsObject(maybe_data)) {
        const cJSON *maybe_friend = cJSON_GetObjectItemCaseSensitive(maybe_data, "friendimei");
        if (maybe_friend) {
            payload = maybe_data;
            printf("%s handle down pp message use data node\n", CHAT_MANAGER_LOG_TAG);
        }
    }

    const cJSON *friend_imei_item = cJSON_GetObjectItemCaseSensitive(payload, "friendimei");
    if (!cJSON_IsString(friend_imei_item) || !friend_imei_item->valuestring || !friend_imei_item->valuestring[0]) {
        printf("%s handle down pp message fail friendimei missing\n", CHAT_MANAGER_LOG_TAG);
        return -EINVAL;
    }
    const char *group_id = friend_imei_item->valuestring;
    printf("%s handle down pp message group=%s\n", CHAT_MANAGER_LOG_TAG, group_id);

    const cJSON *duration_item = cJSON_GetObjectItemCaseSensitive(payload, "duration");
    const cJSON *size_item = cJSON_GetObjectItemCaseSensitive(payload, "size");
    const cJSON *url_item = cJSON_GetObjectItemCaseSensitive(payload, "messageurl");
    if (!url_item) {
        url_item = cJSON_GetObjectItemCaseSensitive(payload, "url");
    }
    const cJSON *timestamp_item = cJSON_GetObjectItemCaseSensitive(payload, "timestamp");
    const cJSON *ident_item = cJSON_GetObjectItemCaseSensitive(payload, "ident");
    if (!ident_item) {
        ident_item = cJSON_GetObjectItemCaseSensitive(root, "ident");
    }
    const cJSON *friend_name_item = cJSON_GetObjectItemCaseSensitive(payload, "friendname");
    if (!friend_name_item) {
        friend_name_item = cJSON_GetObjectItemCaseSensitive(payload, "friendName");
    }

    struct chat_message_record record;
    memset(&record, 0, sizeof(record));
    record.content_type = CHAT_MESSAGE_CONTENT_VOICE;
    record.direction = CHAT_MESSAGE_DIRECTION_INCOMING;
    record.duration = cJSON_IsNumber(duration_item) ? (float)duration_item->valuedouble : 0.0f;
    record.size_bytes = cJSON_IsNumber(size_item) ? (uint32_t)(size_item->valuedouble + 0.5f) : 0U;
    record.timestamp_ms = cJSON_IsNumber(timestamp_item) ? (uint64_t)(timestamp_item->valuedouble + 0.5) : 0ULL;

    if (cJSON_IsString(url_item) && url_item->valuestring) {
        chat_manager_copy_string(record.media_path, sizeof(record.media_path), url_item->valuestring);
    }

    if (cJSON_IsNumber(ident_item) && ident_item->valuedouble > 0) {
        uint64_t ident = (uint64_t)(ident_item->valuedouble + 0.5);
        snprintf(record.message_id,
                 sizeof(record.message_id),
                 "pp_%llu",
                 (unsigned long long)ident);
        record.message_id[sizeof(record.message_id) - 1] = '\0';
    }

    if (cJSON_IsString(friend_name_item) && friend_name_item->valuestring) {
        chat_manager_copy_string(record.relationship,
                                 sizeof(record.relationship),
                                 friend_name_item->valuestring);
    }

    chat_manager_lock();

    int slot_index = chat_manager_find_slot_by_group(group_id);
    if (slot_index < 0) {
        slot_index = chat_manager_alloc_slot(group_id);
    }
    if (slot_index < 0) {
        chat_manager_unlock();
        printf("%s handle down pp message no slot for group=%s\n",
               CHAT_MANAGER_LOG_TAG,
               group_id);
        return -ENOSPC;
    }

    struct chat_friend_slot *slot = &s_friend_slots[slot_index];
    slot->info.in_use = true;

    if (cJSON_IsString(friend_name_item) && friend_name_item->valuestring) {
        chat_manager_copy_string(slot->info.group_name,
                                 sizeof(slot->info.group_name),
                                 friend_name_item->valuestring);
    }
    if (!slot->info.group_name[0]) {
        chat_manager_copy_string(slot->info.group_name,
                                 sizeof(slot->info.group_name),
                                 group_id);
    }

    if (!record.relationship[0] && slot->info.group_name[0]) {
        chat_manager_copy_string(record.relationship,
                                 sizeof(record.relationship),
                                 slot->info.group_name);
    }
    if (!record.relationship[0]) {
        chat_manager_copy_string(record.relationship,
                                 sizeof(record.relationship),
                                 group_id);
    }

    chat_manager_append_message(slot, &record);

    chat_manager_unlock();
    printf("%s handle down pp message finish group=%s slot=%d\n",
           CHAT_MANAGER_LOG_TAG,
           group_id,
           slot_index);
    return 0;
}

int chat_manager_record_local_message(const char *group_id,
                                      enum chat_message_content_type content_type,
                                      const char *content,
                                      const char *message_id,
                                      uint64_t timestamp_ms,
                                      const char *media_path,
                                      uint32_t size_bytes,
                                      float duration,
                                      const char *display_name,
                                      const unsigned char *media_buffer,
                                      size_t media_buffer_len)
{
    printf("%s record local message group=%s type=%d\n",
           CHAT_MANAGER_LOG_TAG,
           group_id ? group_id : "<null>",
           (int)content_type);

    if (!group_id || !group_id[0]) {
        printf("%s record local message failed invalid group id\n", CHAT_MANAGER_LOG_TAG);
        return -EINVAL;
    }

    uint64_t final_timestamp = timestamp_ms;
    if (final_timestamp == 0) {
        final_timestamp = (uint64_t)sys_timer_get_ms();
    }

    int ret = 0;
    struct chat_message_record record;
    memset(&record, 0, sizeof(record));
    record.content_type = (uint8_t)content_type;
    record.direction = CHAT_MESSAGE_DIRECTION_OUTGOING;
    record.timestamp_ms = final_timestamp;
    record.size_bytes = size_bytes;
    record.duration = duration;

    if (media_buffer && media_buffer_len > 0) {
        unsigned char *dup = (unsigned char *)malloc(media_buffer_len);
        if (!dup) {
            printf("%s record local message failed: no memory for media buffer (len=%zu)\n",
                   CHAT_MANAGER_LOG_TAG,
                   media_buffer_len);
            return -ENOMEM;
        }
        memcpy(dup, media_buffer, media_buffer_len);
        record.media_buffer = dup;
        record.media_buffer_len = media_buffer_len;
    }

    if (content) {
        chat_manager_copy_string(record.content, sizeof(record.content), content);
    }
    if (message_id) {
        chat_manager_copy_string(record.message_id, sizeof(record.message_id), message_id);
    }
    if (media_path) {
        chat_manager_copy_string(record.media_path, sizeof(record.media_path), media_path);
    }
    if (display_name && display_name[0]) {
        chat_manager_copy_string(record.relationship, sizeof(record.relationship), display_name);
    } else {
        chat_manager_copy_string(record.relationship, sizeof(record.relationship), "我");
    }

    chat_manager_lock();

    int slot_index = chat_manager_find_slot_by_group(group_id);
    if (slot_index < 0) {
        slot_index = chat_manager_alloc_slot(group_id);
    }
    if (slot_index < 0) {
        chat_manager_unlock();
        printf("%s record local message no slot for group %s\n", CHAT_MANAGER_LOG_TAG, group_id);
        ret = -ENOSPC;
        goto cleanup;
    }

    struct chat_friend_slot *slot = &s_friend_slots[slot_index];
    slot->info.in_use = true;

    chat_manager_append_message(slot, &record);
    record.media_buffer = NULL;
    record.media_buffer_len = 0;

    chat_manager_unlock();
    printf("%s record local message success group=%s slot=%d\n", CHAT_MANAGER_LOG_TAG, group_id, slot_index);
    return 0;

cleanup:
    if (record.media_buffer) {
        free(record.media_buffer);
        record.media_buffer = NULL;
        record.media_buffer_len = 0;
    }
    return ret;
}

/**
 * @brief 统计当前缓存中的好友数量。
 */
size_t chat_manager_get_friend_count(void)
{
    printf("%s get friend count\n", CHAT_MANAGER_LOG_TAG);
    size_t count = 0;
    chat_manager_lock();
    for (int i = 0; i < CHAT_MANAGER_MAX_FRIENDS; ++i) {
        if (s_friend_slots[i].info.in_use) {
            count++;
        }
    }
    chat_manager_unlock();
    printf("%s friend count=%zu\n", CHAT_MANAGER_LOG_TAG, count);
    return count;
}

/**
 * @brief 按数组索引获取好友信息，主要用于 UI 层遍历显示。
 */
const struct chat_friend_entry *chat_manager_get_friend(size_t index)
{
    printf("%s get friend index=%zu\n", CHAT_MANAGER_LOG_TAG, index);
    const struct chat_friend_entry *result = NULL;
    chat_manager_lock();
    if (index < CHAT_MANAGER_MAX_FRIENDS && s_friend_slots[index].info.in_use) {
        result = &s_friend_slots[index].info;
    }
    chat_manager_unlock();
    printf("%s get friend index=%zu result=%p\n", CHAT_MANAGER_LOG_TAG, index, result);
    return result;
}

/**
 * @brief 获取指定好友的最近聊天记录。
 *
 * 使用环形缓存策略，默认返回最新消息；若提供 out_records 则会拷贝到调用方缓冲区。
 */
size_t chat_manager_get_friend_messages(const char *group_id,
                                        struct chat_message_record *out_records,
                                        size_t max_records)
{
    printf("%s get friend messages group=%s max=%zu out=%p\n",
           CHAT_MANAGER_LOG_TAG,
           group_id ? group_id : "<null>",
           max_records,
           out_records);
    if (!group_id || !group_id[0]) {
        printf("%s get friend messages skip invalid group\n", CHAT_MANAGER_LOG_TAG);
        return 0;
    }
    size_t copied = 0;
    chat_manager_lock();
    int slot_index = chat_manager_find_slot_by_group(group_id);
    if (slot_index >= 0) {
        struct chat_friend_slot *slot = &s_friend_slots[slot_index];
        size_t available = slot->count;
        if (available > 0) {
            size_t count = available;
            if (max_records && count > max_records) {
                count = max_records;
            }
            size_t start = (slot->write_index + CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND - available) % CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND;
            size_t offset = available - count;
            for (size_t i = 0; i < count; ++i) {
                size_t src_index = (start + offset + i) % CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND;
                if (out_records) {
                    out_records[i] = slot->messages[src_index];
                }
                copied++;
            }
        }
    }
    chat_manager_unlock();
    printf("%s get friend messages group=%s copied=%zu\n", CHAT_MANAGER_LOG_TAG, group_id, copied);
    return copied;
}
