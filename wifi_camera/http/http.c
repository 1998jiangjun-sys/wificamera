#include "app_config.h"

#if defined(CONFIG_NET_ENABLE)

#include "http_upload_state.h"
#include "wifi_camera_http.h"

#include "generic/log.h"
#include "http/http_cli.h"
#include "fs/fs.h"
#include "os/os_api.h"

#include "chat_manager.h"
#include "cJSON.h"

#include <mbedtls/md5.h>

#include <ctype.h>
#include <errno.h>
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef CONFIG_WIFI_CAMERA_HTTP_UPLOAD_URL
#define CONFIG_WIFI_CAMERA_HTTP_UPLOAD_URL        "http://htcpovs.kidxin.com:16610/send/remoteimage"
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_GROUPMSG_URL
#define CONFIG_WIFI_CAMERA_HTTP_GROUPMSG_URL       "http://htcpovs.kidxin.com:16610/send/groupmsg"
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_DEVICE_IMEI
#ifdef CONFIG_WIFI_CAMERA_HTTP_DEVICE_ID
#define CONFIG_WIFI_CAMERA_HTTP_DEVICE_IMEI       CONFIG_WIFI_CAMERA_HTTP_DEVICE_ID
#else
#define CONFIG_WIFI_CAMERA_HTTP_DEVICE_IMEI       "865028000000307"
#endif
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_SIGN_KEY
#define CONFIG_WIFI_CAMERA_HTTP_SIGN_KEY          "C4CA4238A0B923820DCC509A6F75849B"
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_HEADER_AUTHORIZATION
#define CONFIG_WIFI_CAMERA_HTTP_HEADER_AUTHORIZATION  ""
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_HEADER_CHANNEL
#define CONFIG_WIFI_CAMERA_HTTP_HEADER_CHANNEL     ""
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_HEADER_DEVICE
#define CONFIG_WIFI_CAMERA_HTTP_HEADER_DEVICE      ""
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_HEADER_SYSTEM_OS
#define CONFIG_WIFI_CAMERA_HTTP_HEADER_SYSTEM_OS   ""
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_HEADER_USER_AGENT
#define CONFIG_WIFI_CAMERA_HTTP_HEADER_USER_AGENT  "wifi-camera-http/1.0"
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_HEADER_EXTRA
#define CONFIG_WIFI_CAMERA_HTTP_HEADER_EXTRA       ""
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_TIMEOUT_MS
#define CONFIG_WIFI_CAMERA_HTTP_TIMEOUT_MS        15000U
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_RESPONSE_MAX_LEN
#define CONFIG_WIFI_CAMERA_HTTP_RESPONSE_MAX_LEN  1024U
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_MAX_FILE_SIZE
#define CONFIG_WIFI_CAMERA_HTTP_MAX_FILE_SIZE     (2 * 1024 * 1024UL)
#endif

extern u32 timer_get_ms(void);

struct wifi_camera_http_request {
    const char *file_path;
    const char *display_path;
    struct http_upload_state *state;
};

struct wifi_camera_http_sign_entry {
    const char *key;
    const char *value;
};

struct wifi_camera_http_form_field {
    const char *name;
    const char *value;
};

static OS_MUTEX s_http_lock;
static int s_http_lock_ready = 0;
static const unsigned char s_http_empty_payload = 0;

/**
 * @brief 获取 HTTP 上传的全局互斥锁，必要时自动创建。
 */
static int wifi_camera_http_lock(void)
{
    if (!s_http_lock_ready) {
        if (os_mutex_create(&s_http_lock)) {
            return -ENOMEM;
        }
        s_http_lock_ready = 1;
    }
    return os_mutex_pend(&s_http_lock, 0);
}

/**
 * @brief 释放 HTTP 上传的全局互斥锁。
 */
static void wifi_camera_http_unlock(void)
{
    if (s_http_lock_ready) {
        os_mutex_post(&s_http_lock);
    }
}

/**
 * @brief 忽略大小写比较两个字符串。
 */
static int wifi_camera_http_stricmp(const char *a, const char *b)
{
    if (!a || !b) {
        return (a == b) ? 0 : (a ? 1 : -1);
    }

    while (*a && *b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) {
            return ca - cb;
        }
        ++a;
        ++b;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

static const char *wifi_camera_http_default_filename(enum wifi_camera_chat_content_type content_type)
{
    switch (content_type) {
    case WIFI_CAMERA_CHAT_CONTENT_IMAGE:
        return "message.jpg";
    case WIFI_CAMERA_CHAT_CONTENT_VOICE:
        return "message.amr";
    case WIFI_CAMERA_CHAT_CONTENT_EMOJI:
        return "emoji.dat";
    case WIFI_CAMERA_CHAT_CONTENT_TEXT:
    default:
        return "message.txt";
    }
}

static enum chat_message_content_type wifi_camera_http_to_chat_content(enum wifi_camera_chat_content_type type)
{
    switch (type) {
    case WIFI_CAMERA_CHAT_CONTENT_IMAGE:
        return CHAT_MESSAGE_CONTENT_IMAGE;
    case WIFI_CAMERA_CHAT_CONTENT_VOICE:
        return CHAT_MESSAGE_CONTENT_VOICE;
    case WIFI_CAMERA_CHAT_CONTENT_EMOJI:
        return CHAT_MESSAGE_CONTENT_EMOJI;
    case WIFI_CAMERA_CHAT_CONTENT_TEXT:
    default:
        return CHAT_MESSAGE_CONTENT_TEXT;
    }
}

static int wifi_camera_http_content_type_to_server(enum wifi_camera_chat_content_type type)
{
    switch (type) {
    case WIFI_CAMERA_CHAT_CONTENT_VOICE:
        return 0;
    case WIFI_CAMERA_CHAT_CONTENT_IMAGE:
        return 1;
    case WIFI_CAMERA_CHAT_CONTENT_EMOJI:
        return 2;
    case WIFI_CAMERA_CHAT_CONTENT_TEXT:
    default:
        return 3;
    }
}

/**
 * @brief 根据文件扩展名粗略推断 MIME 类型。
 */
static const char *wifi_camera_http_guess_mime(const char *filename)
{
    const char *ext = strrchr(filename, '.');
    if (!ext) {
        return "application/octet-stream";
    }
    ext++;
    if (!ext[0]) {
        return "application/octet-stream";
    }

    if (!wifi_camera_http_stricmp(ext, "jpg") || !wifi_camera_http_stricmp(ext, "jpeg")) {
        return "image/jpeg";
    } else if (!wifi_camera_http_stricmp(ext, "png")) {
        return "image/png";
    } else if (!wifi_camera_http_stricmp(ext, "bmp")) {
        return "image/bmp";
    } else if (!wifi_camera_http_stricmp(ext, "gif")) {
        return "image/gif";
    }
    return "application/octet-stream";
}

/**
 * @brief 从 URL 中提取 host 与 path，供自定义 HTTP 头使用。
 */
static int wifi_camera_http_extract_host_path(const char *url,
                                              char *host_buf,
                                              size_t host_len,
                                              char *path_buf,
                                              size_t path_len)
{
    if (!url || !host_buf || !path_buf || host_len == 0 || path_len == 0) {
        return -EINVAL;
    }

    const char *scheme_end = strstr(url, "://");
    const char *host_start = scheme_end ? scheme_end + 3 : url;
    if (!*host_start) {
        return -EINVAL;
    }

    const char *path_start = strchr(host_start, '/');
    size_t host_part_len = path_start ? (size_t)(path_start - host_start) : strlen(host_start);
    if (host_part_len == 0 || host_part_len >= host_len) {
        return -ENOSPC;
    }

    memcpy(host_buf, host_start, host_part_len);
    host_buf[host_part_len] = '\0';

    const char *path_part = path_start ? path_start : "/";
    size_t path_part_len = strlen(path_part);
    if (path_part_len == 0) {
        path_part = "/";
        path_part_len = 1;
    }

    if (path_part_len >= path_len) {
        return -ENOSPC;
    }

    memcpy(path_buf, path_part, path_part_len + 1);
    return 0;
}

/**
 * @brief 创建自定义 HTTP 头部字符串，包含鉴权相关字段。
 */
static int wifi_camera_http_build_header(const char *host,
                                         const char *path,
                                         const char *content_type,
                                         size_t content_length,
                                         char **out_header)
{
    if (!host || !path || !content_type || !out_header) {
        return -EINVAL;
    }

    const char *authorization = CONFIG_WIFI_CAMERA_HTTP_HEADER_AUTHORIZATION;
    const char *channel = CONFIG_WIFI_CAMERA_HTTP_HEADER_CHANNEL;
    const char *device = CONFIG_WIFI_CAMERA_HTTP_HEADER_DEVICE;
    const char *system_os = CONFIG_WIFI_CAMERA_HTTP_HEADER_SYSTEM_OS;
    const char *user_agent = CONFIG_WIFI_CAMERA_HTTP_HEADER_USER_AGENT;
    const char *extra = CONFIG_WIFI_CAMERA_HTTP_HEADER_EXTRA;

    size_t optional_len = 0;
    if (authorization && authorization[0]) {
        optional_len += snprintf(NULL, 0, "Authorization: %s\r\n", authorization);
    }
    if (channel && channel[0]) {
        optional_len += snprintf(NULL, 0, "Channel: %s\r\n", channel);
    }
    if (device && device[0]) {
        optional_len += snprintf(NULL, 0, "Device: %s\r\n", device);
    }
    if (system_os && system_os[0]) {
        optional_len += snprintf(NULL, 0, "System-Os: %s\r\n", system_os);
    }
    if (extra && extra[0]) {
        size_t extra_len = strlen(extra);
        optional_len += extra_len;
        if (extra[extra_len - 1] != '\n') {
            optional_len += 2; // 确保额外字段以 CRLF 结束
        }
    }

    size_t base_len = snprintf(NULL,
                               0,
                               "POST %s HTTP/1.1\r\n"
                               "Host: %s\r\n"
                               "User-Agent: %s\r\n"
                               "Accept: */*\r\n"
                               "Connection: close\r\n"
                               "Content-Type: %s\r\n"
                               "Content-Length: %u\r\n",
                               path,
                               host,
                               user_agent ? user_agent : "wifi-camera-http/1.0",
                               content_type,
                               (unsigned int)content_length);

    size_t total_len = base_len + optional_len + 2; // 额外的 CRLF 结束符
    char *header = malloc(total_len + 1);
    if (!header) {
        return -ENOMEM;
    }

    size_t offset = 0;
    int written = snprintf(header,
                           total_len + 1,
                           "POST %s HTTP/1.1\r\n"
                           "Host: %s\r\n"
                           "User-Agent: %s\r\n"
                           "Accept: */*\r\n"
                           "Connection: close\r\n"
                           "Content-Type: %s\r\n"
                           "Content-Length: %u\r\n",
                           path,
                           host,
                           user_agent ? user_agent : "wifi-camera-http/1.0",
                           content_type,
                           (unsigned int)content_length);
    if (written < 0) {
        free(header);
        return -EIO;
    }
    offset = (size_t)written;

    if (authorization && authorization[0]) {
        written = snprintf(header + offset,
                           total_len + 1 - offset,
                           "Authorization: %s\r\n",
                           authorization);
        if (written < 0) {
            free(header);
            return -EIO;
        }
        offset += (size_t)written;
    }

    if (channel && channel[0]) {
        written = snprintf(header + offset,
                           total_len + 1 - offset,
                           "Channel: %s\r\n",
                           channel);
        if (written < 0) {
            free(header);
            return -EIO;
        }
        offset += (size_t)written;
    }

    if (device && device[0]) {
        written = snprintf(header + offset,
                           total_len + 1 - offset,
                           "Device: %s\r\n",
                           device);
        if (written < 0) {
            free(header);
            return -EIO;
        }
        offset += (size_t)written;
    }

    if (system_os && system_os[0]) {
        written = snprintf(header + offset,
                           total_len + 1 - offset,
                           "System-Os: %s\r\n",
                           system_os);
        if (written < 0) {
            free(header);
            return -EIO;
        }
        offset += (size_t)written;
    }

    if (extra && extra[0]) {
        size_t extra_len = strlen(extra);
        memcpy(header + offset, extra, extra_len);
        offset += extra_len;
        if (extra[extra_len - 1] != '\n') {
            memcpy(header + offset, "\r\n", 2);
            offset += 2;
        }
    }

    memcpy(header + offset, "\r\n", 2);
    offset += 2;
    header[offset] = '\0';

    *out_header = header;
    return 0;
}

static u32 wifi_camera_http_sys_time_to_epoch(const struct sys_time *t)
{
    if (!t || !t->year || !t->month || !t->day) {
        return 0;
    }

    struct tm tm_time;
    memset(&tm_time, 0, sizeof(tm_time));
    tm_time.tm_year = (int)t->year - 1900;
    tm_time.tm_mon = (int)t->month - 1;
    tm_time.tm_mday = t->day;
    tm_time.tm_hour = t->hour;
    tm_time.tm_min = t->min;
    tm_time.tm_sec = t->sec;

    time_t epoch = mktime(&tm_time);
    if (epoch < 0) {
        return 0;
    }
    return (u32)epoch;
}

/**
 * @brief 读取文件内容到内存并返回文件大小及修改时间。
 */
static int wifi_camera_http_prepare_file(const char *file_path,
                                         unsigned char **out_buf,
                                         size_t *out_size,
                                         u32 *out_mtime)
{
    if (!file_path || !out_buf || !out_size) {
        return -EINVAL;
    }

    FILE *fp = fopen(file_path, "rb");
    if (!fp) {
        printf("[HTTP][UPLOAD] open %s fail (%d)\n", file_path, errno);
        return -errno;
    }

    struct vfs_attr attr = {0};
    if (fget_attrs(fp, &attr) == 0) {
        if (out_mtime) {
            *out_mtime = wifi_camera_http_sys_time_to_epoch(&attr.wrt_time);
        }
    }

    if (fseek(fp, 0, SEEK_END)) {
        printf("[HTTP][UPLOAD] fseek end fail (%d)\n", errno);
        fclose(fp);
        return -errno;
    }

    long file_size = ftell(fp);
    if (file_size < 0) {
        printf("[HTTP][UPLOAD] ftell fail (%d)\n", errno);
        fclose(fp);
        return -errno;
    }
    if ((unsigned long)file_size > CONFIG_WIFI_CAMERA_HTTP_MAX_FILE_SIZE) {
        printf("[HTTP][UPLOAD] file too large %ld > %lu\n",
               file_size,
               (unsigned long)CONFIG_WIFI_CAMERA_HTTP_MAX_FILE_SIZE);
        fclose(fp);
        return -EFBIG;
    }

    if (fseek(fp, 0, SEEK_SET)) {
        printf("[HTTP][UPLOAD] fseek start fail (%d)\n", errno);
        fclose(fp);
        return -errno;
    }

    unsigned char *buf = malloc((size_t)file_size);
    if (!buf) {
        printf("[HTTP][UPLOAD] malloc %ld fail\n", file_size);
        fclose(fp);
        return -ENOMEM;
    }

    size_t read_len = fread(buf, 1, (size_t)file_size, fp);
    if (read_len != (size_t)file_size) {
        printf("[HTTP][UPLOAD] fread len mismatch %zu/%ld\n", read_len, file_size);
        free(buf);
        fclose(fp);
        return -EIO;
    }

    fclose(fp);

    *out_buf = buf;
    *out_size = (size_t)file_size;
    return 0;
}

/**
 * @brief 组装 multipart/form-data 数据体并返回内容类型。
 */
static int wifi_camera_http_build_payload(const struct wifi_camera_http_form_field *fields,
                                          size_t field_count,
                                          const unsigned char *file_buf,
                                          size_t file_size,
                                          const char *file_name,
                                          const char *mime_type,
                                          char **out_data,
                                          size_t *out_len,
                                          char *out_content_type,
                                          size_t content_type_len)
{
    if ((!file_buf && file_size > 0) || !file_name || !mime_type ||
        !out_data || !out_len || !out_content_type) {
        return -EINVAL;
    }

    char boundary[64];
    snprintf(boundary, sizeof(boundary), "----WIFI-CAMERA-%08X", (unsigned int)timer_get_ms());

    int ct_written = snprintf(out_content_type,
                              content_type_len,
                              "multipart/form-data; boundary=%s",
                              boundary);
    if (ct_written < 0 || (size_t)ct_written >= content_type_len) {
        return -ENOMEM;
    }

    size_t total_len = 0;
    const char *text_fmt =
        "--%s\r\n"
        "Content-Disposition: form-data; name=\"%s\"\r\n\r\n"
        "%s\r\n";

    for (size_t i = 0; i < field_count; ++i) {
        const char *name = fields[i].name;
        const char *value = fields[i].value;
        if (!name || !name[0] || !value) {
            continue;
        }

        int len = snprintf(NULL, 0, text_fmt, boundary, name, value ? value : "");
        if (len < 0) {
            return -EINVAL;
        }
        total_len += (size_t)len;
    }

    const char *file_fmt =
        "--%s\r\n"
        "Content-Disposition: form-data; name=\"content\"; filename=\"%s\"\r\n"
        "Content-Type: %s\r\n\r\n";

    int file_header_len = snprintf(NULL, 0, file_fmt, boundary, file_name, mime_type);
    if (file_header_len < 0) {
        return -EINVAL;
    }

    int footer_len = snprintf(NULL, 0, "\r\n--%s--\r\n", boundary);
    if (footer_len < 0) {
        return -EINVAL;
    }

    total_len += (size_t)file_header_len;
    total_len += file_size;
    total_len += (size_t)footer_len;

    char *payload = malloc(total_len + 1);
    if (!payload) {
        return -ENOMEM;
    }

    size_t offset = 0;
    for (size_t i = 0; i < field_count; ++i) {
        const char *name = fields[i].name;
        const char *value = fields[i].value;
        if (!name || !name[0] || !value) {
            continue;
        }

        int len = snprintf(payload + offset,
                           total_len + 1 - offset,
                           text_fmt,
                           boundary,
                           name,
                           value ? value : "");
        if (len < 0 || (size_t)len >= total_len + 1 - offset) {
            free(payload);
            return -EIO;
        }
        offset += (size_t)len;
    }

    int written = snprintf(payload + offset,
                           total_len + 1 - offset,
                           file_fmt,
                           boundary,
                           file_name,
                           mime_type);
    if (written < 0 || (size_t)written >= total_len + 1 - offset) {
        free(payload);
        return -EIO;
    }
    offset += (size_t)written;

    if (file_size > 0 && file_buf) {
        memcpy(payload + offset, file_buf, file_size);
    }
    offset += file_size;

    written = snprintf(payload + offset,
                       total_len + 1 - offset,
                       "\r\n--%s--\r\n",
                       boundary);
    if (written < 0 || (size_t)written >= total_len + 1 - offset) {
        free(payload);
        return -EIO;
    }

    offset += (size_t)written;
    payload[offset] = '\0';

    *out_data = payload;
    *out_len = offset;
    return 0;
}

static void wifi_camera_http_md5_hex_upper(const unsigned char *input,
                                           size_t len,
                                           char out_hex[33])
{
    unsigned char digest[16];
    memset(digest, 0, sizeof(digest));
    mbedtls_md5(input, len, digest);

    static const char hex_table[] = "0123456789ABCDEF";
    for (size_t i = 0; i < sizeof(digest); ++i) {
        out_hex[i * 2]     = hex_table[(digest[i] >> 4) & 0x0F];
        out_hex[i * 2 + 1] = hex_table[digest[i] & 0x0F];
    }
    out_hex[32] = '\0';
}


static int wifi_camera_http_sign_entry_cmp(const void *a, const void *b)
{
    const struct wifi_camera_http_sign_entry *ea = a;
    const struct wifi_camera_http_sign_entry *eb = b;

    if (!ea->key || !eb->key) {
        if (ea->key == eb->key) {
            return 0;
        }
        return ea->key ? -1 : 1;
    }

    return strcmp(ea->key, eb->key);
}

static int wifi_camera_http_build_sign(char out_hex[33],
                                       const struct wifi_camera_http_sign_entry *entries,
                                       size_t entry_count)
{
    if (!out_hex || !entries || !entry_count) {
        return -EINVAL;
    }

    struct wifi_camera_http_sign_entry *sorted = malloc(entry_count * sizeof(*sorted));
    if (!sorted) {
        return -ENOMEM;
    }

    memcpy(sorted, entries, entry_count * sizeof(*sorted));
    qsort(sorted, entry_count, sizeof(*sorted), wifi_camera_http_sign_entry_cmp);

    char joined[512];
    size_t offset = 0;
    size_t valid_count = 0;

    for (size_t i = 0; i < entry_count; ++i) {
        const char *key = sorted[i].key;
        const char *value = sorted[i].value;
        if (!key || !value) {
            continue;
        }

        int written = snprintf(joined + offset,
                               sizeof(joined) - offset,
                               "%s:%s:",
                               key,
                               value);
        if (written < 0 || (size_t)written >= sizeof(joined) - offset) {
            free(sorted);
            return -ENOMEM;
        }
        offset += (size_t)written;
        ++valid_count;
    }

    free(sorted);

    if (!valid_count) {
        return -EINVAL;
    }

    size_t key_len = strlen(CONFIG_WIFI_CAMERA_HTTP_SIGN_KEY);
    if (offset + key_len >= sizeof(joined)) {
        return -ENOMEM;
    }
    memcpy(joined + offset, CONFIG_WIFI_CAMERA_HTTP_SIGN_KEY, key_len);
    offset += key_len;

    wifi_camera_http_md5_hex_upper((const unsigned char *)joined, offset, out_hex);
    return 0;
}

/**
 * @brief 发送 HTTP POST 请求，返回 httpcli_post 的结果码。
 */
static int wifi_camera_http_send_payload_to(const char *url,
                                            const char *payload,
                                            size_t payload_len,
                                            const char *content_type,
                                            http_body_obj *body)
{
    char host[128];
    char path[256];
    int ret = wifi_camera_http_extract_host_path(url,
                                                 host,
                                                 sizeof(host),
                                                 path,
                                                 sizeof(path));
    if (ret) {
        printf("[HTTP][UPLOAD] parse url fail (%d)\n", ret);
        return ret;
    }

    char *header = NULL;
    ret = wifi_camera_http_build_header(host,
                                        path,
                                        content_type,
                                        payload_len,
                                        &header);
    if (ret) {
        printf("[HTTP][UPLOAD] build header fail (%d)\n", ret);
        return ret;
    }

    httpcli_ctx ctx = {0};

    ctx.url = url;
    ctx.timeout_millsec = CONFIG_WIFI_CAMERA_HTTP_TIMEOUT_MS;
    ctx.connection = "close";
    ctx.post_data = payload;
    ctx.data_len = payload_len;
    ctx.data_format = content_type;
    ctx.priv = body;
    ctx.user_http_header = header;

    ret = httpcli_post(&ctx);
    httpcli_close(&ctx);

    free(header);
    return ret;
}

static int wifi_camera_http_send_payload(const char *payload,
                                         size_t payload_len,
                                         const char *content_type,
                                         http_body_obj *body)
{
    return wifi_camera_http_send_payload_to(CONFIG_WIFI_CAMERA_HTTP_UPLOAD_URL,
                                            payload,
                                            payload_len,
                                            content_type,
                                            body);
}

/**
 * @brief 打印服务器返回的响应数据，便于排查问题。
 */
static void wifi_camera_http_dump_response(const http_body_obj *body)
{
    if (!body || !body->p || body->recv_len == 0) {
        return;
    }

    printf("[HTTP][UPLOAD] response (%u bytes): %.*s\n",
           body->recv_len,
           (int)body->recv_len,
           body->p);
}

/**
 * @brief 核心流程：构建签名、打包并上传指定图片到服务器。
 */
int wifi_camera_http_upload_remote_image(const char *file_path,
                                         const char *display_path,
                                         struct http_upload_state *state)
{
    if (!file_path) {
        return -EINVAL;
    }

    printf("[HTTP][UPLOAD] start upload file=%s display=%s\n",
           file_path,
           display_path ? display_path : "");

    int lock_err = wifi_camera_http_lock();
    if (lock_err) {
        return lock_err;
    }

    int ret = 0;
    unsigned char *file_buf = NULL;
    size_t file_size = 0;
    u32 file_mtime = 0;

    ret = wifi_camera_http_prepare_file(file_path, &file_buf, &file_size, &file_mtime);
    if (ret) {
        wifi_camera_http_unlock();
        return ret;
    }

    const char *file_name = NULL;
    const char *basename = strrchr(file_path, '/');
    file_name = basename ? basename + 1 : file_path;

    const char *track_key = (display_path && display_path[0]) ? display_path : file_name;

    if (state && http_upload_state_is_duplicate(state, track_key, (u32)file_size, file_mtime)) {
        printf("[HTTP][UPLOAD] skip duplicate %s\n", track_key);
        free(file_buf);
        wifi_camera_http_unlock();
        return 0;
    }

    u64 request_timestamp_ms = (u64)time(NULL) * 1000ULL;
    if (request_timestamp_ms == 0) {
        request_timestamp_ms = timer_get_ms();
    }

    char timestamp_str[24];
    snprintf(timestamp_str,
             sizeof(timestamp_str),
             "%llu",
             (unsigned long long)request_timestamp_ms);

    char size_str[16];
    snprintf(size_str, sizeof(size_str), "%u", (unsigned int)file_size);

    unsigned int ident_num = (unsigned int)(rand() % 900000U) + 100000U;
    char ident_str[16];
    snprintf(ident_str, sizeof(ident_str), "%06u", ident_num);

    struct wifi_camera_http_sign_entry sign_entries[] = {
        {"ident", ident_str},
        {"imei", CONFIG_WIFI_CAMERA_HTTP_DEVICE_IMEI},
        {"size", size_str},
        {"timestamp", timestamp_str},
    };

    char sign_hex[33];
    ret = wifi_camera_http_build_sign(sign_hex,
                                      sign_entries,
                                      sizeof(sign_entries) / sizeof(sign_entries[0]));
    if (ret) {
        printf("[HTTP][UPLOAD] build sign fail (%d)\n", ret);
        free(file_buf);
        wifi_camera_http_unlock();
        return ret;
    }

    printf("[HTTP][UPLOAD] ident=%s timestamp=%s size=%s sign=%s\n",
           ident_str,
           timestamp_str,
           size_str,
           sign_hex);

    struct wifi_camera_http_form_field fields[] = {
        {"imei", CONFIG_WIFI_CAMERA_HTTP_DEVICE_IMEI},
        {"size", size_str},
        {"timestamp", timestamp_str},
        {"ident", ident_str},
        {"sign", sign_hex},
    };

    char content_type[96];
    char *payload = NULL;
    size_t payload_len = 0;
    ret = wifi_camera_http_build_payload(fields,
                                         sizeof(fields) / sizeof(fields[0]),
                                         file_buf,
                                         file_size,
                                         file_name,
                                         wifi_camera_http_guess_mime(file_name),
                                         &payload,
                                         &payload_len,
                                         content_type,
                                         sizeof(content_type));
    if (ret) {
        printf("[HTTP][UPLOAD] build payload fail (%d)\n", ret);
        free(file_buf);
        wifi_camera_http_unlock();
        return ret;
    }

    http_body_obj body = {0};
    body.buf_len = CONFIG_WIFI_CAMERA_HTTP_RESPONSE_MAX_LEN;
    body.buf_count = 1;
    body.p = malloc(body.buf_len);
    if (!body.p) {
        printf("[HTTP][UPLOAD] resp malloc fail\n");
        free(payload);
        free(file_buf);
        wifi_camera_http_unlock();
        return -ENOMEM;
    }

    int http_ret = wifi_camera_http_send_payload(payload, payload_len, content_type, &body);
    if (http_ret != HERROR_OK) {
        printf("[HTTP][UPLOAD] httpcli_post fail (%d)\n", http_ret);
        ret = -EIO;
    } else {
        wifi_camera_http_dump_response(&body);
        printf("[HTTP][UPLOAD] upload success: %s\n", track_key);
        if (state) {
            int state_ret = http_upload_state_record_success(state,
                                                             track_key,
                                                             (u32)file_size,
                                                             file_mtime);
            if (state_ret) {
                printf("[HTTP][UPLOAD] state record fail (%d)\n", state_ret);
            }
        }
    }

    free(body.p);
    free(payload);
    free(file_buf);

    wifi_camera_http_unlock();
    return ret;
}

int wifi_camera_http_send_group_message(const struct wifi_camera_chat_message_params *params)
{
    if (!params || !params->group_id || !params->group_id[0]) {
        return -EINVAL;
    }

    if (params->group_type < 0) {
        return -EINVAL;
    }

    printf("[HTTP][CHAT] send groupId=%s groupType=%d contentType=%d returnUrl=%d\n",
           params->group_id,
           params->group_type,
           (int)params->content_type,
           params->request_return_url ? 1 : 0);

    int lock_err = wifi_camera_http_lock();
    if (lock_err) {
        return lock_err;
    }

    int ret = 0;
    unsigned char *file_buf_alloc = NULL;
    const unsigned char *file_buf = NULL;
    size_t file_size = 0;
    const char *file_name = params->upload_file_name;
    char derived_filename[64];
    char mime_buf[48];
    const char *mime_type = params->mime_type;
    char *payload = NULL;
    size_t payload_len = 0;
    http_body_obj body = {0};

    if (params->buffer && params->buffer_size > 0) {
        file_buf = params->buffer;
        file_size = params->buffer_size;
    } else if (params->file_path && params->file_path[0]) {
        ret = wifi_camera_http_prepare_file(params->file_path,
                                            &file_buf_alloc,
                                            &file_size,
                                            NULL);
        if (ret) {
            printf("[HTTP][CHAT] prepare file %s fail (%d)\n", params->file_path, ret);
            goto cleanup;
        }
        file_buf = file_buf_alloc;
        if (!file_name || !file_name[0]) {
            const char *basename = strrchr(params->file_path, '/');
            if (!basename) {
                basename = strrchr(params->file_path, '\\');
            }
            file_name = basename ? basename + 1 : params->file_path;
        }
    } else if (params->content_text) {
        file_buf = (const unsigned char *)params->content_text;
        file_size = strlen(params->content_text);
    } else {
        file_buf = NULL;
        file_size = 0;
    }

    if (!file_name || !file_name[0]) {
        if (params->content_type == WIFI_CAMERA_CHAT_CONTENT_VOICE &&
            params->audio_type && params->audio_type[0]) {
            snprintf(derived_filename,
                     sizeof(derived_filename),
                     "voice.%s",
                     params->audio_type);
            file_name = derived_filename;
        } else if (mime_type && mime_type[0]) {
            const char *slash = strchr(mime_type, '/');
            if (slash && slash[1]) {
                snprintf(derived_filename,
                         sizeof(derived_filename),
                         "message.%s",
                         slash + 1);
                file_name = derived_filename;
            }
        }
        if (!file_name || !file_name[0]) {
            const char *fallback = wifi_camera_http_default_filename(params->content_type);
            strncpy(derived_filename, fallback, sizeof(derived_filename) - 1);
            derived_filename[sizeof(derived_filename) - 1] = '\0';
            file_name = derived_filename;
        }
    }

    if (!file_buf && file_size == 0) {
        file_buf = &s_http_empty_payload;
    }

    if (!mime_type || !mime_type[0]) {
        if (params->content_type == WIFI_CAMERA_CHAT_CONTENT_TEXT) {
            mime_type = "text/plain; charset=utf-8";
        } else if (params->content_type == WIFI_CAMERA_CHAT_CONTENT_VOICE &&
                   params->audio_type && params->audio_type[0]) {
            snprintf(mime_buf, sizeof(mime_buf), "audio/%s", params->audio_type);
            mime_type = mime_buf;
        } else if (file_name) {
            mime_type = wifi_camera_http_guess_mime(file_name);
        } else {
            mime_type = "application/octet-stream";
        }
    }

    u64 request_timestamp_ms = params->timestamp_ms;
    if (!request_timestamp_ms) {
        request_timestamp_ms = (u64)time(NULL) * 1000ULL;
        if (!request_timestamp_ms) {
            request_timestamp_ms = timer_get_ms();
        }
    }

    char timestamp_str[24];
    snprintf(timestamp_str,
             sizeof(timestamp_str),
             "%llu",
             (unsigned long long)request_timestamp_ms);

    char group_type_str[8];
    snprintf(group_type_str, sizeof(group_type_str), "%d", params->group_type);

    int server_content_type = wifi_camera_http_content_type_to_server(params->content_type);
    char content_type_str[8];
    snprintf(content_type_str, sizeof(content_type_str), "%d", server_content_type);

    char size_str[16];
    unsigned int size_field = (file_size > 0xFFFFFFFFULL) ? 0xFFFFFFFFU : (unsigned int)file_size;
    snprintf(size_str, sizeof(size_str), "%u", size_field);

    unsigned int ident_num = (unsigned int)(rand() % 900000U) + 100000U;
    char ident_str[16];
    snprintf(ident_str, sizeof(ident_str), "%06u", ident_num);

    char audio_duration_str[16];
    unsigned int audio_duration_sec = 0;
    if (params->audio_duration_ms) {
        audio_duration_sec = (params->audio_duration_ms + 500U) / 1000U;
        if (audio_duration_sec == 0) {
            audio_duration_sec = 1;
        }
        snprintf(audio_duration_str, sizeof(audio_duration_str), "%u", audio_duration_sec);
    }

    const char *return_url_value = params->request_return_url ? "1" : NULL;

    struct wifi_camera_http_sign_entry sign_entries[16];
    size_t sign_count = 0;

#define ADD_SIGN_ENTRY(k, v)                                                     \
    do {                                                                         \
        if ((v) && sign_count < sizeof(sign_entries) / sizeof(sign_entries[0])) { \
            sign_entries[sign_count].key = (k);                                   \
            sign_entries[sign_count].value = (v);                                 \
            ++sign_count;                                                        \
        }                                                                         \
    } while (0)

    ADD_SIGN_ENTRY("contentType", content_type_str);
    ADD_SIGN_ENTRY("groupId", params->group_id);
    ADD_SIGN_ENTRY("groupType", group_type_str);
    ADD_SIGN_ENTRY("ident", ident_str);
    ADD_SIGN_ENTRY("imei", CONFIG_WIFI_CAMERA_HTTP_DEVICE_IMEI);
    ADD_SIGN_ENTRY("size", size_str);
    ADD_SIGN_ENTRY("timestamp", timestamp_str);
    ADD_SIGN_ENTRY("returnUrl", return_url_value);
    ADD_SIGN_ENTRY("audioDuration", params->audio_duration_ms ? audio_duration_str : NULL);
    ADD_SIGN_ENTRY("audioType", (params->audio_type && params->audio_type[0]) ? params->audio_type : NULL);
    ADD_SIGN_ENTRY("bqId", (params->bq_id && params->bq_id[0]) ? params->bq_id : NULL);

#undef ADD_SIGN_ENTRY

    char sign_hex[33];
    ret = wifi_camera_http_build_sign(sign_hex, sign_entries, sign_count);
    if (ret) {
        printf("[HTTP][CHAT] build sign fail (%d)\n", ret);
        goto cleanup;
    }

    struct wifi_camera_http_form_field fields[20];
    size_t field_count = 0;

#define ADD_FIELD(n, v)                                                          \
    do {                                                                         \
        if ((v) && field_count < sizeof(fields) / sizeof(fields[0])) {           \
            fields[field_count].name = (n);                                      \
            fields[field_count].value = (v);                                     \
            ++field_count;                                                      \
        }                                                                         \
    } while (0)

    ADD_FIELD("imei", CONFIG_WIFI_CAMERA_HTTP_DEVICE_IMEI);
    ADD_FIELD("timestamp", timestamp_str);
    ADD_FIELD("groupId", params->group_id);
    ADD_FIELD("groupType", group_type_str);
    ADD_FIELD("contentType", content_type_str);
    ADD_FIELD("size", size_str);
    ADD_FIELD("ident", ident_str);
    ADD_FIELD("returnUrl", return_url_value);
    ADD_FIELD("audioDuration", params->audio_duration_ms ? audio_duration_str : NULL);
    ADD_FIELD("audioType", (params->audio_type && params->audio_type[0]) ? params->audio_type : NULL);
    ADD_FIELD("bqId", (params->bq_id && params->bq_id[0]) ? params->bq_id : NULL);
    ADD_FIELD("sign", sign_hex);

#undef ADD_FIELD

    char content_type_header[96];
    ret = wifi_camera_http_build_payload(fields,
                                         field_count,
                                         file_buf,
                                         file_size,
                                         file_name,
                                         mime_type,
                                         &payload,
                                         &payload_len,
                                         content_type_header,
                                         sizeof(content_type_header));
    if (ret) {
        printf("[HTTP][CHAT] build payload fail (%d)\n", ret);
        goto cleanup;
    }

    body.buf_len = CONFIG_WIFI_CAMERA_HTTP_RESPONSE_MAX_LEN;
    body.buf_count = 1;
    body.p = malloc(body.buf_len);
    if (!body.p) {
        printf("[HTTP][CHAT] resp malloc fail\n");
        ret = -ENOMEM;
        goto cleanup;
    }
    memset(body.p, 0, body.buf_len);

    int http_ret = wifi_camera_http_send_payload_to(CONFIG_WIFI_CAMERA_HTTP_GROUPMSG_URL,
                                                    payload,
                                                    payload_len,
                                                    content_type_header,
                                                    &body);
    if (http_ret != HERROR_OK) {
        printf("[HTTP][CHAT] httpcli_post fail (%d)\n", http_ret);
        ret = -EIO;
        goto cleanup;
    }

    wifi_camera_http_dump_response(&body);

    bool success = false;
    char remote_url_buf[CONFIG_WIFI_CAMERA_HTTP_RESPONSE_MAX_LEN];
    memset(remote_url_buf, 0, sizeof(remote_url_buf));

    if (body.p && body.recv_len > 0 && ((unsigned char *)body.p)[0] == '{') {
        cJSON *root = cJSON_ParseWithLength((const char *)body.p, body.recv_len);
        if (root) {
            const cJSON *code = cJSON_GetObjectItemCaseSensitive(root, "code");
            if (cJSON_IsNumber(code)) {
                success = (code->valueint == 0);
            } else if (cJSON_IsString(code) && code->valuestring) {
                success = (atoi(code->valuestring) == 0);
            }

            if (success) {
                const cJSON *url_item = cJSON_GetObjectItemCaseSensitive(root, "url");
                if (cJSON_IsString(url_item) && url_item->valuestring) {
                    strncpy(remote_url_buf,
                            url_item->valuestring,
                            sizeof(remote_url_buf) - 1);
                    remote_url_buf[sizeof(remote_url_buf) - 1] = '\0';
                }
            } else {
                const cJSON *msg_item = cJSON_GetObjectItemCaseSensitive(root, "message");
                if (cJSON_IsString(msg_item) && msg_item->valuestring) {
                    printf("[HTTP][CHAT] server message: %s\n", msg_item->valuestring);
                }
            }
            cJSON_Delete(root);
        } else {
            printf("[HTTP][CHAT] parse json fail\n");
        }
    } else {
        if (!body.p || body.recv_len == 0) {
            success = true;
        } else {
            size_t start = 0;
            while (start < body.recv_len && isspace((unsigned char)body.p[start])) {
                ++start;
            }
            size_t end = body.recv_len;
            while (end > start && isspace((unsigned char)body.p[end - 1])) {
                --end;
            }
            size_t trimmed_len = end > start ? (end - start) : 0;
            if (trimmed_len) {
                char word[16];
                size_t copy_len = trimmed_len < sizeof(word) - 1 ? trimmed_len : sizeof(word) - 1;
                memcpy(word, (unsigned char *)body.p + start, copy_len);
                word[copy_len] = '\0';
                if (!wifi_camera_http_stricmp(word, "success")) {
                    success = true;
                }
            } else {
                success = true;
            }
        }
    }

    if (!success) {
        ret = -EIO;
        goto cleanup;
    }

    if (params->out_remote_url && params->out_remote_url_len > 0) {
        if (remote_url_buf[0]) {
            strncpy(params->out_remote_url,
                    remote_url_buf,
                    params->out_remote_url_len - 1);
            params->out_remote_url[params->out_remote_url_len - 1] = '\0';
        } else {
            params->out_remote_url[0] = '\0';
        }
    }

    const char *record_content = params->content_text;
    char content_fallback[64];
    if (!record_content || !record_content[0]) {
        if (params->bq_id && params->bq_id[0]) {
            record_content = params->bq_id;
        } else if (file_name && file_name[0]) {
            strncpy(content_fallback, file_name, sizeof(content_fallback) - 1);
            content_fallback[sizeof(content_fallback) - 1] = '\0';
            record_content = content_fallback;
        } else {
            record_content = "";
        }
    }

    const char *record_media_path = params->media_path_override;
    if (!record_media_path || !record_media_path[0]) {
        if (remote_url_buf[0]) {
            record_media_path = remote_url_buf;
        } else if (params->file_path && params->file_path[0]) {
            record_media_path = params->file_path;
        } else {
            record_media_path = "";
        }
    }

    const char *record_message_id =
        (params->message_id && params->message_id[0]) ? params->message_id : ident_str;

    const char *display_name =
        (params->display_name && params->display_name[0]) ? params->display_name : "我";

    const unsigned char *record_media_buffer = NULL;
    size_t record_media_buffer_len = 0;
    if (params->content_type == WIFI_CAMERA_CHAT_CONTENT_VOICE && file_buf && file_size > 0) {
        record_media_buffer = file_buf;
        record_media_buffer_len = file_size;
    }

    float duration_sec = 0.0f;
    if (params->audio_duration_ms) {
        duration_sec = params->audio_duration_ms / 1000.0f;
        if (duration_sec < 0.001f && params->audio_duration_ms) {
            duration_sec = 0.001f;
        }
    }

    uint64_t record_timestamp = params->timestamp_ms ? params->timestamp_ms : request_timestamp_ms;
    uint32_t record_size = (file_size > 0xFFFFFFFFULL) ? 0xFFFFFFFFU : (uint32_t)file_size;

    int record_ret = chat_manager_record_local_message(params->group_id,
                                                       wifi_camera_http_to_chat_content(params->content_type),
                                                       record_content,
                                                       record_message_id,
                                                       record_timestamp,
                                                       record_media_path,
                                                       record_size,
                                                       duration_sec,
                                                       display_name,
                                                       record_media_buffer,
                                                       record_media_buffer_len);
    if (record_ret) {
        printf("[HTTP][CHAT] record local message fail (%d)\n", record_ret);
    }

    printf("[HTTP][CHAT] send success ident=%s url=%s\n",
           ident_str,
           remote_url_buf[0] ? remote_url_buf : "");

    ret = 0;

cleanup:
    if (body.p) {
        free(body.p);
    }
    if (payload) {
        free(payload);
    }
    if (file_buf_alloc) {
        free(file_buf_alloc);
    }

    wifi_camera_http_unlock();
    return ret;
}

#endif /* CONFIG_NET_ENABLE */
