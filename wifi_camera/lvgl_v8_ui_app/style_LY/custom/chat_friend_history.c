#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 

/**
 * @file chat_friend_history.c
 * @brief 聊天页面消息气泡面板实现。
 */
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include "../generated/gui_fonts/gui_fonts.h"

#include "chat_friend_history.h"

#include "lv_conf.h"
#include "os/os_api.h"
#include "fs/fs.h"
#include "media/audio_def.h"
#include "vir_dev_player.h"

#ifndef CONFIG_VIRTUAL_PLAYER_FILE_SOURCE
#define CONFIG_VIRTUAL_PLAYER_FILE_SOURCE 1
#endif

#define CHAT_HISTORY_LOG_TAG "[CHAT][UI]"

#define CHAT_HISTORY_TOP_OFFSET        120  // 聊天历史面板距顶部偏移
#define CHAT_HISTORY_BOTTOM_OFFSET     120  // 聊天历史面板距底部预留
#define CHAT_HISTORY_SIDE_PADDING      16   // 面板左右内边距
#define CHAT_HISTORY_CONTENT_WIDTH_MARGIN (CHAT_HISTORY_SIDE_PADDING * 2) // 内容宽度需要扣除的边距
#define CHAT_HISTORY_MIN_HEIGHT        200  // 面板允许的最小高度
#define CHAT_HISTORY_BUBBLE_MAX_WIDTH  340  // 气泡最大显示宽度
#define CHAT_HISTORY_BUBBLE_RADIUS     18   // 气泡圆角半径
#define CHAT_HISTORY_BUBBLE_PADDING    12   // 气泡内部填充
#define CHAT_HISTORY_ROW_GAP           6    // 不同方向消息之间的间距
#define CHAT_HISTORY_ROW_GAP_SAME_DIRECTION 2 // 同一方向连续消息之间的最小间距

struct chat_friend_history_ctx {
    lv_obj_t *parent;
    lv_obj_t *panel;
    lv_obj_t *list;
    lv_obj_t *empty_label;
    bool initialized;
    char active_group_id[CHAT_MANAGER_MAX_GROUP_ID_LEN];
};

static struct chat_friend_history_ctx s_history_ctx = {0};

struct chat_friend_voice_userdata {
    struct chat_friend_voice_info info;
};

static bool chat_friend_history_is_http_url(const char *path)
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

static u32 chat_friend_history_guess_codec(const char *path)
{
#if defined(CONFIG_HOME_PAGE_AI_VOICE_CODEC)
    u32 default_codec = CONFIG_HOME_PAGE_AI_VOICE_CODEC;
#else
    u32 default_codec = AUDIO_CODING_AMR;
#endif

    if (!path || !path[0]) {
        return default_codec;
    }

    const char *dot = strrchr(path, '.');
    if (!dot || !dot[1]) {
        return default_codec;
    }

    char ext[8] = {0};
    size_t len = strlen(dot + 1);
    if (len >= sizeof(ext)) {
        len = sizeof(ext) - 1;
    }
    for (size_t i = 0; i < len; ++i) {
        ext[i] = (char)tolower((unsigned char)dot[1 + i]);
    }
    ext[len] = '\0';

    if (strcmp(ext, "amr") == 0) {
        return AUDIO_CODING_AMR;
    }
#ifdef AUDIO_CODING_OPUS
    if (strcmp(ext, "opus") == 0 || strcmp(ext, "opu") == 0) {
        return AUDIO_CODING_OPUS;
    }
#endif
#ifdef AUDIO_CODING_WAV
    if (strcmp(ext, "wav") == 0) {
        return AUDIO_CODING_WAV;
    }
#endif

    return default_codec;
}

static bool chat_friend_history_play_voice_file(const struct chat_friend_voice_info *info)
{
    if (!info || !info->media_path[0]) {
        return false;
    }

    int play_ret = virtual_test(info->media_path);
    if (play_ret) {
        printf("%s voice playback failed path=%s err=%d\n",
               CHAT_HISTORY_LOG_TAG,
               info->media_path,
               play_ret);
        return false;
    }

    printf("%s voice playback file path=%s\n",
           CHAT_HISTORY_LOG_TAG,
           info->media_path);
    return true;
}

static bool chat_friend_history_reload_voice_info(struct chat_friend_voice_info *info)
{
    if (!info) {
        return false;
    }
    if (!info->group_id[0]) {
        printf("%s reload voice skipped missing group\n", CHAT_HISTORY_LOG_TAG);
        return false;
    }

    struct chat_message_record records[CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND] = {0};
    size_t count = chat_manager_get_friend_messages(info->group_id,
                                                    records,
                                                    CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND);
    if (!count) {
        printf("%s reload voice no records group=%s\n",
               CHAT_HISTORY_LOG_TAG,
               info->group_id);
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        const struct chat_message_record *record = &records[i];
        if (record->content_type != CHAT_MESSAGE_CONTENT_VOICE) {
            continue;
        }
        if (info->message_id[0]) {
            if (!record->message_id[0] || strcmp(record->message_id, info->message_id) != 0) {
                continue;
            }
        } else if (record->message_id[0]) {
            snprintf(info->message_id,
                     sizeof(info->message_id),
                     "%s",
                     record->message_id);
            info->message_id[sizeof(info->message_id) - 1] = '\0';
        }

        info->direction = (enum chat_message_direction)record->direction;
        info->duration = record->duration;
        info->size_bytes = record->size_bytes;
        info->timestamp_ms = record->timestamp_ms;
        info->media_buffer = record->media_buffer;
        info->media_buffer_len = record->media_buffer_len;

        if (record->media_path[0]) {
            snprintf(info->media_path,
                     sizeof(info->media_path),
                     "%s",
                     record->media_path);
            info->media_path[sizeof(info->media_path) - 1] = '\0';
        } else {
            info->media_path[0] = '\0';
        }

        printf("%s reload voice info group=%s msg=%s path=%s\n",
               CHAT_HISTORY_LOG_TAG,
               info->group_id,
               info->message_id[0] ? info->message_id : "<none>",
               info->media_path[0] ? info->media_path : "<empty>");
        return true;
    }

    printf("%s reload voice miss group=%s msg=%s\n",
           CHAT_HISTORY_LOG_TAG,
           info->group_id,
           info->message_id[0] ? info->message_id : "<none>");
    return false;
}

static void chat_friend_history_wakeup_lvgl_task(void)
{
    printf("%s wake request posting UI_MSG_TIMER_TIMEOUT\n", CHAT_HISTORY_LOG_TAG);
    int msg[2];
    msg[0] = UI_MSG_TIMER_TIMEOUT;
    msg[1] = 0;

    int err = task_queue_post_event(LVGL_TASK_NAME, msg, (int)(sizeof(msg) / sizeof(msg[0])));
    if (err != 0) {
        printf("%s wake lvgl failed err=%d\n", CHAT_HISTORY_LOG_TAG, err);
    } else {
        printf("%s wake lvgl success\n", CHAT_HISTORY_LOG_TAG);
    }
}

static void chat_friend_history_scroll_to_bottom(lv_obj_t *target, bool animate);
static void chat_friend_history_clear_list(void);
static lv_obj_t *chat_friend_history_render_messages(const struct chat_message_record *records,
                                                     size_t count);
static lv_obj_t *chat_friend_history_append_record(const struct chat_message_record *record,
                                                   const struct chat_message_record *prev_record);
static void chat_friend_history_update_empty_placeholder(bool list_empty);
static void chat_friend_history_voice_bubble_event_cb(lv_event_t *e);
static lv_color_t chat_friend_history_get_bubble_color(enum chat_message_direction direction);
static lv_color_t chat_friend_history_get_text_color(enum chat_message_direction direction);
static void chat_friend_history_apply_bubble_style(lv_obj_t *bubble,
                                                   enum chat_message_direction direction);

__attribute__((weak)) void chat_friend_history_play_voice(const struct chat_friend_voice_info *info)
{

    if (!info) {
        printf("[CHAT][UI] voice playback skip: info null\n");
        return;
    }

    struct chat_friend_voice_info voice_ctx;
    memcpy(&voice_ctx, info, sizeof(voice_ctx));

    printf("[CHAT][UI] voice playback request group=%s msg=%s dir=%d path=%s buffer_len=%lu duration=%.2f size=%u\n",
           voice_ctx.group_id[0] ? voice_ctx.group_id : "<none>",
           voice_ctx.message_id[0] ? voice_ctx.message_id : "<none>",
           (int)voice_ctx.direction,
           voice_ctx.media_path[0] ? voice_ctx.media_path : "<empty>",
        (unsigned long)voice_ctx.media_buffer_len,
           voice_ctx.duration,
           (unsigned int)voice_ctx.size_bytes);

    bool is_local_voice = (voice_ctx.direction == CHAT_MESSAGE_DIRECTION_OUTGOING);
    bool has_inline_buffer = (voice_ctx.media_buffer && voice_ctx.media_buffer_len > 0);

#if CONFIG_VIRTUAL_PLAYER_STREAM_BUFFER
    if (is_local_voice && has_inline_buffer) {
        if (voice_ctx.media_buffer_len > (size_t)INT_MAX) {
            printf("[CHAT][UI] voice playback skip: buffer too large (%lu)\n",
                   (unsigned long)voice_ctx.media_buffer_len);
            return;
        }

#if defined(CONFIG_HOME_PAGE_AI_VOICE_CODEC)
        const u32 coding_type = CONFIG_HOME_PAGE_AI_VOICE_CODEC;
#else
        const u32 coding_type = AUDIO_CODING_AMR;
#endif

        int play_ret = virtual_dev_play_stream_buffer(voice_ctx.media_buffer,
                                                      (int)voice_ctx.media_buffer_len,
                                                      coding_type);
        if (play_ret) {
            printf("[CHAT][UI] voice playback failed group=%s msg=%s err=%d\n",
                   voice_ctx.group_id,
                   voice_ctx.message_id,
                   play_ret);
        } else {
         printf("[CHAT][UI] voice playback start group=%s msg=%s len=%lu codec=%u\n",
                   voice_ctx.group_id,
                   voice_ctx.message_id,
             (unsigned long)voice_ctx.media_buffer_len,
                   (unsigned int)coding_type);
        }
        return;
    }
#else
    (void)is_local_voice;
    (void)has_inline_buffer;
#endif

    bool has_media_path = (voice_ctx.media_path[0] != '\0');
    bool media_path_is_http = has_media_path && chat_friend_history_is_http_url(voice_ctx.media_path);

    printf("[CHAT][UI] voice playback state before reload: has_path=%d is_http=%d has_buffer=%d\n",
           has_media_path,
           media_path_is_http,
           has_inline_buffer);

    if ((!has_media_path || media_path_is_http) && voice_ctx.group_id[0]) {
        if (chat_friend_history_reload_voice_info(&voice_ctx)) {
            is_local_voice = (voice_ctx.direction == CHAT_MESSAGE_DIRECTION_OUTGOING);
            has_inline_buffer = (voice_ctx.media_buffer && voice_ctx.media_buffer_len > 0);
            has_media_path = (voice_ctx.media_path[0] != '\0');
            media_path_is_http = has_media_path && chat_friend_history_is_http_url(voice_ctx.media_path);

            printf("[CHAT][UI] voice playback state after reload: dir=%d path=%s has_path=%d is_http=%d has_buffer=%d size=%u\n",
                   (int)voice_ctx.direction,
                   voice_ctx.media_path[0] ? voice_ctx.media_path : "<empty>",
                   has_media_path,
                   media_path_is_http,
                   has_inline_buffer,
                   (unsigned int)voice_ctx.size_bytes);
        }
    }

#if CONFIG_VIRTUAL_PLAYER_FILE_SOURCE
    if (has_media_path && !media_path_is_http) {
        FILE *probe = fopen(voice_ctx.media_path, "r");
        if (!probe) {
            printf("[CHAT][UI] voice playback file probe failed path=%s err=%d\n",
                   voice_ctx.media_path,
                   errno);
        } else {
         size_t file_len = (size_t)flen(probe);
            fclose(probe);
         printf("[CHAT][UI] voice playback file probe success path=%s len=%lu codec_guess=%u\n",
             voice_ctx.media_path,
             (unsigned long)file_len,
                   (unsigned int)chat_friend_history_guess_codec(voice_ctx.media_path));
        }
        if (chat_friend_history_play_voice_file(&voice_ctx)) {
            return;
        }
        printf("[CHAT][UI] voice playback failed from file path=%s group=%s msg=%s\n",
               voice_ctx.media_path,
               voice_ctx.group_id,
               voice_ctx.message_id);
    }
#endif

    if (media_path_is_http) {
        printf("[CHAT][UI] voice playback pending download path=%s group=%s msg=%s\n",
               voice_ctx.media_path,
               voice_ctx.group_id,
               voice_ctx.message_id);
        return;
    }

    if (!has_inline_buffer && !has_media_path) {
        printf("[CHAT][UI] voice playback missing media group=%s msg=%s\n",
               voice_ctx.group_id,
               voice_ctx.message_id);
    } else {
        printf("[CHAT][UI] voice playback unsupported: group=%s msg=%s direction=%d\n",
               voice_ctx.group_id,
               voice_ctx.message_id,
               (int)voice_ctx.direction);
    }
}

bool chat_friend_history_init(lv_obj_t *parent)
{
    if (s_history_ctx.initialized) {
        printf("%s init skipped already initialized\n", CHAT_HISTORY_LOG_TAG);
        return true;
    }
    if (!parent) {
        printf("%s init failed parent null\n", CHAT_HISTORY_LOG_TAG);
        return false;
    }

    lv_coord_t parent_width = lv_obj_get_width(parent);
    lv_coord_t parent_height = lv_obj_get_height(parent);
    if (parent_width <= 0) {
        parent_width = 480;
    }
    if (parent_height <= 0) {
        parent_height = 640;
    }

    lv_coord_t panel_width = parent_width - CHAT_HISTORY_CONTENT_WIDTH_MARGIN;
    if (panel_width <= 0) {
        panel_width = parent_width;
    }

    lv_coord_t panel_height = parent_height - CHAT_HISTORY_TOP_OFFSET - CHAT_HISTORY_BOTTOM_OFFSET;
    if (panel_height < CHAT_HISTORY_MIN_HEIGHT) {
        panel_height = parent_height / 2;
    }

    lv_obj_t *panel = lv_obj_create(parent);
    if (!panel) {
        printf("%s init failed create panel\n", CHAT_HISTORY_LOG_TAG);
        return false;
    }

    lv_obj_remove_style_all(panel);
    lv_obj_set_size(panel, panel_width, panel_height);
    lv_obj_set_pos(panel, CHAT_HISTORY_SIDE_PADDING, CHAT_HISTORY_TOP_OFFSET);
    lv_obj_set_scrollbar_mode(panel, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_set_scroll_dir(panel, LV_DIR_VER);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLL_MOMENTUM);
    lv_obj_set_style_bg_opa(panel, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(panel, 0, LV_PART_MAIN);

    lv_obj_t *list = lv_obj_create(panel);
    if (!list) {
        lv_obj_del(panel);
        printf("%s init failed create list\n", CHAT_HISTORY_LOG_TAG);
        return false;
    }

    lv_obj_remove_style_all(list);
    lv_obj_set_width(list, lv_pct(100));
    lv_obj_set_height(list, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(list, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(list, 0, LV_PART_MAIN);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(list,
                          LV_FLEX_ALIGN_START,
                          LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(list, 0, LV_PART_MAIN);

    s_history_ctx.parent = parent;
    s_history_ctx.panel = panel;
    s_history_ctx.list = list;
    s_history_ctx.empty_label = NULL;
    s_history_ctx.initialized = true;
    s_history_ctx.active_group_id[0] = '\0';

    printf("%s init done panel=%p list=%p size=(%d,%d)\n",
           CHAT_HISTORY_LOG_TAG,
           s_history_ctx.panel,
           s_history_ctx.list,
           (int)panel_width,
           (int)panel_height);
    chat_friend_history_update_empty_placeholder(true);
    return true;
}

bool chat_friend_history_is_ready(void)
{
    return s_history_ctx.initialized && s_history_ctx.panel && s_history_ctx.list;
}

void chat_friend_history_deinit(void)
{
    if (!s_history_ctx.initialized) {
        printf("%s deinit skipped not initialized\n", CHAT_HISTORY_LOG_TAG);
        return;
    }
    memset(&s_history_ctx, 0, sizeof(s_history_ctx));
    printf("%s deinit completed\n", CHAT_HISTORY_LOG_TAG);
}

void chat_friend_history_set_active_group(const char *group_id)
{
    if (!chat_friend_history_is_ready()) {
        printf("%s set active skipped not ready group=%s\n",
               CHAT_HISTORY_LOG_TAG,
               group_id ? group_id : "<null>");
        return;
    }

    printf("%s set active group=%s current=%s\n",
           CHAT_HISTORY_LOG_TAG,
           group_id ? group_id : "<null>",
           s_history_ctx.active_group_id[0] ? s_history_ctx.active_group_id : "<none>");
    if (!group_id || !group_id[0]) {
        s_history_ctx.active_group_id[0] = '\0';
        chat_friend_history_clear_list();
        chat_friend_history_update_empty_placeholder(true);
        return;
    }

    if (strcmp(s_history_ctx.active_group_id, group_id) != 0) {
        snprintf(s_history_ctx.active_group_id,
                 sizeof(s_history_ctx.active_group_id),
                 "%s",
                 group_id);
        s_history_ctx.active_group_id[sizeof(s_history_ctx.active_group_id) - 1] = '\0';
        printf("%s active group updated to %s\n",
               CHAT_HISTORY_LOG_TAG,
               s_history_ctx.active_group_id);
    }

    chat_friend_history_refresh_active(true);
}

void chat_friend_history_refresh_active(bool scroll_to_end)
{
    if (!chat_friend_history_is_ready()) {
        printf("%s refresh skipped not ready\n", CHAT_HISTORY_LOG_TAG);
        return;
    }

    if (!s_history_ctx.active_group_id[0]) {
        chat_friend_history_clear_list();
        chat_friend_history_update_empty_placeholder(true);
        printf("%s refresh skipped no active group\n", CHAT_HISTORY_LOG_TAG);
        return;
    }

    struct chat_message_record records[CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND] = {0};
    size_t count = chat_manager_get_friend_messages(s_history_ctx.active_group_id,
                                                    records,
                                                    CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND);
    printf("%s refresh group=%s message_count=%u scroll=%d\n",
           CHAT_HISTORY_LOG_TAG,
           s_history_ctx.active_group_id,
           (unsigned int)count,
           scroll_to_end);
    lv_obj_t *last_row = chat_friend_history_render_messages(records, count);

    if (scroll_to_end) {
        chat_friend_history_scroll_to_bottom(last_row, true);
        printf("%s refresh scrolled to bottom\n", CHAT_HISTORY_LOG_TAG);
    }
}

struct chat_history_async_request {
    char group_id[CHAT_MANAGER_MAX_GROUP_ID_LEN];
    bool scroll_to_end;
};

static void chat_friend_history_async_refresh_cb(void *user_data)
{
    struct chat_history_async_request *req = (struct chat_history_async_request *)user_data;
    if (!req) {
        printf("%s async cb received null request\n", CHAT_HISTORY_LOG_TAG);
        return;
    }

    printf("%s async cb group=%s scroll=%d active=%s\n",
           CHAT_HISTORY_LOG_TAG,
           req->group_id[0] ? req->group_id : "<null>",
           req->scroll_to_end,
           s_history_ctx.active_group_id[0] ? s_history_ctx.active_group_id : "<none>");
    if (chat_friend_history_is_ready()) {
        if (!req->group_id[0] || strcmp(req->group_id, s_history_ctx.active_group_id) == 0) {
            chat_friend_history_refresh_active(req->scroll_to_end);
        } else {
            printf("%s async cb skip refresh unmatched active\n", CHAT_HISTORY_LOG_TAG);
        }
    } else {
        printf("%s async cb skipped UI not ready\n", CHAT_HISTORY_LOG_TAG);
    }
    free(req);
}

void chat_friend_history_notify_data_changed(const char *group_id, bool scroll_to_end)
{
    printf("%s notify data changed group=%s scroll=%d ready=%d\n",
           CHAT_HISTORY_LOG_TAG,
           group_id ? group_id : "<null>",
           scroll_to_end,
           chat_friend_history_is_ready());
    if (!group_id || !group_id[0]) {
        printf("%s notify skipped invalid group\n", CHAT_HISTORY_LOG_TAG);
        return;
    }

    if (!chat_friend_history_is_ready()) {
        printf("%s notify skipped UI not ready\n", CHAT_HISTORY_LOG_TAG);
        return;
    }

    struct chat_history_async_request *req =
        (struct chat_history_async_request *)malloc(sizeof(struct chat_history_async_request));
    if (!req) {
        printf("%s notify malloc request failed\n", CHAT_HISTORY_LOG_TAG);
        return;
    }

    snprintf(req->group_id, sizeof(req->group_id), "%s", group_id);
    req->group_id[sizeof(req->group_id) - 1] = '\0';
    req->scroll_to_end = scroll_to_end;

    lv_res_t res = lv_async_call(chat_friend_history_async_refresh_cb, req);
    if (res != LV_RES_OK) {
        printf("%s notify lv_async_call failed res=%d\n", CHAT_HISTORY_LOG_TAG, res);
        free(req);
    } else {
        printf("%s notify lv_async_call queued res=%d\n", CHAT_HISTORY_LOG_TAG, res);
        chat_friend_history_wakeup_lvgl_task();
    }
}

static void chat_friend_history_scroll_to_bottom(lv_obj_t *target, bool animate)
{
    if (!chat_friend_history_is_ready()) {
        printf("%s scroll skipped not ready\n", CHAT_HISTORY_LOG_TAG);
        return;
    }
    lv_obj_update_layout(s_history_ctx.list);
    lv_obj_update_layout(s_history_ctx.panel);
    lv_coord_t bottom = lv_obj_get_scroll_bottom(s_history_ctx.panel);
    if (bottom > 0) {
        lv_obj_scroll_by(s_history_ctx.panel, 0, -bottom, animate ? LV_ANIM_ON : LV_ANIM_OFF);
    } else if (target && lv_obj_is_valid(target)) {
        lv_obj_scroll_to_view(target, animate ? LV_ANIM_ON : LV_ANIM_OFF);
    }
}

static void chat_friend_history_clear_list(void)
{
    if (!chat_friend_history_is_ready()) {
        printf("%s clear skipped not ready\n", CHAT_HISTORY_LOG_TAG);
        return;
    }
    lv_obj_clean(s_history_ctx.list);
    s_history_ctx.empty_label = NULL;
    printf("%s clear list done\n", CHAT_HISTORY_LOG_TAG);
}

static lv_obj_t *chat_friend_history_render_messages(const struct chat_message_record *records,
                                                     size_t count)
{
    chat_friend_history_clear_list();

    if (!records || count == 0) {
        chat_friend_history_update_empty_placeholder(true);
        printf("%s render messages empty\n", CHAT_HISTORY_LOG_TAG);
        return NULL;
    }

    lv_obj_t *last_row = NULL;
    for (size_t i = 0; i < count; ++i) {
        const struct chat_message_record *prev_record = (i > 0) ? &records[i - 1] : NULL;
        last_row = chat_friend_history_append_record(&records[i], prev_record);
        printf("%s render appended index=%u direction=%u type=%u id=%s ts=%llu\n",
               CHAT_HISTORY_LOG_TAG,
               (unsigned int)i,
               (unsigned int)records[i].direction,
               (unsigned int)records[i].content_type,
               records[i].message_id[0] ? records[i].message_id : "<none>",
               (unsigned long long)records[i].timestamp_ms);
    }
    chat_friend_history_update_empty_placeholder(false);
    printf("%s render finished total=%u\n", CHAT_HISTORY_LOG_TAG, (unsigned int)count);
    return last_row;
}

static lv_color_t chat_friend_history_get_bubble_color(enum chat_message_direction direction)
{
    if (direction == CHAT_MESSAGE_DIRECTION_OUTGOING) {
        return lv_color_make(0x5F, 0x93, 0xE8);
    }
    return lv_color_make(0xE5, 0xE5, 0xEA);
}

static lv_color_t chat_friend_history_get_text_color(enum chat_message_direction direction)
{
    if (direction == CHAT_MESSAGE_DIRECTION_OUTGOING) {
        return lv_color_white();
    }
    return lv_color_black();
}

static void chat_friend_history_apply_bubble_style(lv_obj_t *bubble,
                                                   enum chat_message_direction direction)
{
    lv_obj_set_width(bubble, LV_SIZE_CONTENT);
    lv_obj_set_height(bubble, LV_SIZE_CONTENT);
    lv_obj_set_style_radius(bubble, CHAT_HISTORY_BUBBLE_RADIUS, LV_PART_MAIN);
    lv_obj_set_style_bg_color(bubble,
                              chat_friend_history_get_bubble_color(direction),
                              LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bubble, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(bubble, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(bubble, CHAT_HISTORY_BUBBLE_PADDING, LV_PART_MAIN);
    lv_obj_set_style_max_width(bubble, CHAT_HISTORY_BUBBLE_MAX_WIDTH, LV_PART_MAIN);
}

static lv_obj_t *chat_friend_history_append_record(const struct chat_message_record *record,
                                                   const struct chat_message_record *prev_record)
{
    if (!chat_friend_history_is_ready() || !record) {
        printf("%s append skipped ready=%d record=%p\n",
               CHAT_HISTORY_LOG_TAG,
               chat_friend_history_is_ready(),
               record);
        return NULL;
    }

    lv_obj_t *row = lv_obj_create(s_history_ctx.list);
    lv_obj_remove_style_all(row);
    lv_obj_set_width(row, LV_PCT(100));
    lv_obj_set_height(row, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(row, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(row, 0, LV_PART_MAIN);
    lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);

    lv_coord_t row_top_pad = 0;
    if (prev_record) {
        bool same_direction = (prev_record->direction == record->direction);
        row_top_pad = same_direction ? CHAT_HISTORY_ROW_GAP_SAME_DIRECTION : CHAT_HISTORY_ROW_GAP;
    }

    lv_obj_set_style_pad_top(row, row_top_pad, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(row, 0, LV_PART_MAIN);

    if (record->direction == CHAT_MESSAGE_DIRECTION_OUTGOING) {
        lv_obj_set_flex_align(row,
                              LV_FLEX_ALIGN_END,
                              LV_FLEX_ALIGN_CENTER,
                              LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_pad_left(row, 48, LV_PART_MAIN);
    } else {
        lv_obj_set_flex_align(row,
                              LV_FLEX_ALIGN_START,
                              LV_FLEX_ALIGN_CENTER,
                              LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_pad_right(row, 48, LV_PART_MAIN);
    }

    lv_obj_t *bubble = lv_obj_create(row);
    chat_friend_history_apply_bubble_style(bubble, record->direction);
    lv_obj_clear_flag(bubble, LV_OBJ_FLAG_SCROLLABLE);

    if (record->content_type == CHAT_MESSAGE_CONTENT_TEXT) {
        const char *text = record->content[0] ? record->content : "(空消息)";
        lv_obj_t *label = lv_label_create(bubble);
        lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
        lv_coord_t label_max_width = CHAT_HISTORY_BUBBLE_MAX_WIDTH - (CHAT_HISTORY_BUBBLE_PADDING * 2);
        if (record->direction == CHAT_MESSAGE_DIRECTION_OUTGOING) {
            lv_obj_set_width(label, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);
        } else {
            lv_obj_set_width(label, label_max_width);
            lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
        }
        lv_obj_set_style_max_width(label,
                                   label_max_width,
                                   LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(label, text);
        lv_obj_set_style_text_color(label,
                                    chat_friend_history_get_text_color(record->direction),
                                    LV_PART_MAIN);
        lv_obj_set_style_text_font(label, &lv_font_simsun_32, LV_PART_MAIN);
    } else if (record->content_type == CHAT_MESSAGE_CONTENT_VOICE) {
        lv_obj_t *label = lv_label_create(bubble);
        lv_label_set_text(label, "语音");
        lv_obj_set_style_text_color(label,
                                    chat_friend_history_get_text_color(record->direction),
                                    LV_PART_MAIN);
        lv_obj_set_style_text_font(label, &lv_font_simsun_32, LV_PART_MAIN);
        lv_obj_add_flag(bubble, LV_OBJ_FLAG_CLICKABLE);

        struct chat_friend_voice_userdata *userdata =
            (struct chat_friend_voice_userdata *)malloc(sizeof(struct chat_friend_voice_userdata));
        if (userdata) {
            memset(&userdata->info, 0, sizeof(userdata->info));
            if (s_history_ctx.active_group_id[0]) {
                snprintf(userdata->info.group_id,
                         sizeof(userdata->info.group_id),
                         "%s",
                         s_history_ctx.active_group_id);
                userdata->info.group_id[sizeof(userdata->info.group_id) - 1] = '\0';
            }
            if (record->message_id[0]) {
                snprintf(userdata->info.message_id,
                         sizeof(userdata->info.message_id),
                         "%s",
                         record->message_id);
                userdata->info.message_id[sizeof(userdata->info.message_id) - 1] = '\0';
            }
            if (record->media_path[0]) {
                snprintf(userdata->info.media_path,
                         sizeof(userdata->info.media_path),
                         "%s",
                         record->media_path);
                userdata->info.media_path[sizeof(userdata->info.media_path) - 1] = '\0';
            }
            userdata->info.media_buffer = record->media_buffer;
            userdata->info.media_buffer_len = record->media_buffer_len;
            userdata->info.duration = record->duration;
            userdata->info.size_bytes = record->size_bytes;
            userdata->info.timestamp_ms = record->timestamp_ms;
            userdata->info.direction = (enum chat_message_direction)record->direction;

            lv_obj_add_event_cb(bubble, chat_friend_history_voice_bubble_event_cb, LV_EVENT_ALL, userdata);
        }
    } else {
        const char *text = record->content[0] ? record->content : "(暂不支持的消息类型)";
        lv_obj_t *label = lv_label_create(bubble);
        lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
        lv_label_set_text(label, text);
        lv_obj_set_style_text_color(label,
                                    chat_friend_history_get_text_color(record->direction),
                                    LV_PART_MAIN);
        lv_obj_set_style_text_font(label, &lv_font_simsun_32, LV_PART_MAIN);
    }

    return row;
}

static void chat_friend_history_voice_bubble_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    struct chat_friend_voice_userdata *userdata =
        (struct chat_friend_voice_userdata *)lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED) {
        if (userdata) {
            chat_friend_history_play_voice(&userdata->info);
        }
    } else if (code == LV_EVENT_DELETE) {
        if (userdata) {
            free(userdata);
        }
        lv_obj_t *target = lv_event_get_current_target(e);
        if (target) {
            lv_obj_remove_event_cb(target, chat_friend_history_voice_bubble_event_cb);
        }
    }
}

static void chat_friend_history_update_empty_placeholder(bool list_empty)
{
    if (!chat_friend_history_is_ready()) {
        printf("%s placeholder skipped not ready\n", CHAT_HISTORY_LOG_TAG);
        return;
    }

    if (list_empty) {
        if (!s_history_ctx.empty_label) {
            s_history_ctx.empty_label = lv_label_create(s_history_ctx.list);
            lv_label_set_text(s_history_ctx.empty_label, "暂无聊天记录");
            lv_obj_set_style_text_color(s_history_ctx.empty_label,
                                        lv_color_make(0x99, 0x99, 0x99),
                                        LV_PART_MAIN);
            lv_obj_set_style_text_font(s_history_ctx.empty_label,
                                       &lv_font_simsun_32,
                                       LV_PART_MAIN);
        }
        lv_obj_align(s_history_ctx.empty_label, LV_ALIGN_CENTER, 0, 0);
        lv_obj_clear_flag(s_history_ctx.empty_label, LV_OBJ_FLAG_HIDDEN);
        printf("%s placeholder show empty\n", CHAT_HISTORY_LOG_TAG);
    } else if (s_history_ctx.empty_label) {
        lv_obj_add_flag(s_history_ctx.empty_label, LV_OBJ_FLAG_HIDDEN);
        printf("%s placeholder hide\n", CHAT_HISTORY_LOG_TAG);
    }
}

#endif
