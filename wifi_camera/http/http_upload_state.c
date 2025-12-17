#include "app_config.h"

#if defined(CONFIG_NET_ENABLE)

#include "http_upload_state.h"

#include "generic/log.h"
#include "fs/fs.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define HTTP_UPLOAD_STATE_MAGIC_JSON    "#HTTP_UPLOAD_STATE_JSON_V1"

static void http_upload_state_trim_newline(char *line);

#ifndef CONFIG_WIFI_CAMERA_HTTP_STORAGE_ROOT
#if defined(CONFIG_ROOT_PATH)
#define CONFIG_WIFI_CAMERA_HTTP_STORAGE_ROOT     CONFIG_ROOT_PATH
#elif defined(CONFIG_STORAGE_PATH)
#define CONFIG_WIFI_CAMERA_HTTP_STORAGE_ROOT     CONFIG_STORAGE_PATH
#else
#define CONFIG_WIFI_CAMERA_HTTP_STORAGE_ROOT     "storage/sd0/C/"
#endif
#endif

/**
 * @brief 将内存中的上传记录清零，恢复到初始状态。
 */
static void http_upload_state_reset(struct http_upload_state *state)
{
    state->count = 0;
    state->next_index = 0;
    for (unsigned int i = 0; i < HTTP_UPLOAD_STATE_MAX_ENTRIES; ++i) {
        state->entries[i].path[0] = '\0';
        state->entries[i].size = 0;
        state->entries[i].timestamp = 0;
    }
}

/**
 * @brief 将外部提供的记录内容复制到状态条目中。
 */
static void http_upload_state_copy_entry(struct http_upload_state_entry *dst,
                                         const char *path,
                                         u32 size,
                                         u32 timestamp)
{
    strncpy(dst->path, path, sizeof(dst->path) - 1);
    dst->path[sizeof(dst->path) - 1] = '\0';
    dst->size = size;
    dst->timestamp = timestamp;
}

/**
 * @brief 查找指定路径对应的记录索引，未命中返回 -1。
 */
static int http_upload_state_find_index(struct http_upload_state *state,
                                        const char *path)
{
    for (unsigned int i = 0; i < state->count; ++i) {
        if (state->entries[i].path[0] == '\0') {
            continue;
        }
        if (strncmp(state->entries[i].path, path, sizeof(state->entries[i].path)) == 0) {
            return (int)i;
        }
    }
    return -1;
}

/**
 * @brief 在持锁的情况下更新或插入一条记录。
 */
static int http_upload_state_upsert_locked(struct http_upload_state *state,
                                           const char *path,
                                           u32 size,
                                           u32 timestamp)
{
    int index = http_upload_state_find_index(state, path);
    if (index >= 0) {
        http_upload_state_copy_entry(&state->entries[index], path, size, timestamp);
        return 0;
    }

    if (state->count < HTTP_UPLOAD_STATE_MAX_ENTRIES) {
        index = (int)state->count;
        state->count++;
    } else {
        index = (int)state->next_index;
        state->next_index = (state->next_index + 1) % HTTP_UPLOAD_STATE_MAX_ENTRIES;
    }

    http_upload_state_copy_entry(&state->entries[index], path, size, timestamp);
    if (state->count == HTTP_UPLOAD_STATE_MAX_ENTRIES) {
        state->next_index %= HTTP_UPLOAD_STATE_MAX_ENTRIES;
    }
    return 0;
}

/**
 * @brief 写入单行文本并追加换行符。
 */
static int http_upload_state_write_line(FILE *fp, const char *line)
{
    if (!fp || !line) {
        return -EINVAL;
    }

    size_t len = strlen(line);
    if (!len) {
        return 0;
    }

    if (fwrite((void *)line, 1, len, fp) != (int)len) {
        return -EIO;
    }
    if (fwrite("\n", 1, 1, fp) != 1) {
        return -EIO;
    }
    return 0;
}

// 将字符串中的特殊字符转义为 JSON 格式。
static void http_upload_state_escape_json_string(const char *input,
                                                 char *output,
                                                 size_t out_len)
{
    if (!output || !out_len) {
        return;
    }

    if (!input) {
        output[0] = '\0';
        return;
    }

    size_t out_idx = 0;
    for (const char *p = input; *p && out_idx + 1 < out_len; ++p) {
        unsigned char ch = (unsigned char)(*p);
        if (ch == '"' || ch == '\\') {
            if (out_idx + 2 >= out_len) {
                break;
            }
            output[out_idx++] = '\\';
            output[out_idx++] = (char)ch;
        } else if (ch <= 0x1F) {
            if (out_idx + 6 >= out_len) {
                break;
            }
            static const char hex_digits[] = "0123456789ABCDEF";
            output[out_idx++] = '\\';
            output[out_idx++] = 'u';
            output[out_idx++] = '0';
            output[out_idx++] = '0';
            output[out_idx++] = hex_digits[(ch >> 4) & 0xF];
            output[out_idx++] = hex_digits[ch & 0xF];
        } else {
            output[out_idx++] = (char)ch;
        }
    }

    output[out_idx] = '\0';
}

// 将单个十六进制字符转换为对应的数值，失败返回 -1。
static int http_upload_state_hex_digit(char ch)
{
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }
    if (ch >= 'a' && ch <= 'f') {
        return 10 + (ch - 'a');
    }
    if (ch >= 'A' && ch <= 'F') {
        return 10 + (ch - 'A');
    }
    return -1;
}

// 将 JSON 字符串中的转义字符还原为原始字符。
static void http_upload_state_unescape_json_string(const char *input,
                                                   char *output,
                                                   size_t out_len)
{
    if (!output || !out_len) {
        return;
    }

    if (!input) {
        output[0] = '\0';
        return;
    }

    size_t out_idx = 0;
    size_t in_len = strlen(input);
    for (size_t i = 0; i < in_len && out_idx + 1 < out_len; ++i) {
        char ch = input[i];
        if (ch == '\\' && (i + 1) < in_len) {
            char next = input[++i];
            switch (next) {
            case '\"':
                ch = '\"';
                break;
            case '\\':
                ch = '\\';
                break;
            case '/':
                ch = '/';
                break;
            case 'b':
                ch = '\b';
                break;
            case 'f':
                ch = '\f';
                break;
            case 'n':
                ch = '\n';
                break;
            case 'r':
                ch = '\r';
                break;
            case 't':
                ch = '\t';
                break;
            case 'u':
                if (i + 4 < in_len) {
                    int h1 = http_upload_state_hex_digit(input[i + 1]);
                    int h2 = http_upload_state_hex_digit(input[i + 2]);
                    int h3 = http_upload_state_hex_digit(input[i + 3]);
                    int h4 = http_upload_state_hex_digit(input[i + 4]);
                    if (h1 >= 0 && h2 >= 0 && h3 >= 0 && h4 >= 0) {
                        unsigned int code = (unsigned int)((h1 << 12) | (h2 << 8) | (h3 << 4) | h4);
                        if (code <= 0x7F) {
                            ch = (char)code;
                        } else {
                            ch = '?';
                        }
                        i += 4;
                        break;
                    }
                }
                /* Fall through if \u is invalid. */
                ch = 'u';
                break;
            default:
                ch = next;
                break;
            }
        }
        output[out_idx++] = ch;
    }

    output[out_idx] = '\0';
}

// 跳过字符串开头的空白字符，返回第一个非空白字符的位置。
static const char *http_upload_state_skip_ws(const char *p)
{
    if (!p) {
        return NULL;
    }

    while (*p && isspace((unsigned char)*p)) {
        ++p;
    }
    return p;
}

// 解析 JSON 格式的单行记录，成功返回 0 并填充输出参数，失败返回负错误码。
static int http_upload_state_parse_json_record(const char *line,
                                               char *path_out,
                                               size_t path_len,
                                               u32 *size_out,
                                               u32 *timestamp_out)
{
    printf("[HTTP][STATE] parse line: %s\n", line ? line : "(null)");
    const char *fail_reason = NULL;
    if (!line || !path_out || !path_len || !size_out || !timestamp_out) {
        fail_reason = "invalid args";
        goto fail;
    }

    const char *cursor = strstr(line, "\"path\"");
    if (!cursor) {
        fail_reason = "missing path field";
        goto fail;
    }

    cursor = strchr(cursor, ':');
    if (!cursor) {
        fail_reason = "missing path colon";
        goto fail;
    }
    cursor = http_upload_state_skip_ws(cursor + 1);
    if (!cursor || *cursor != '"') {
        fail_reason = "path value not string";
        goto fail;
    }

    ++cursor;
    const char *path_start = cursor;
    while (*cursor) {
        if (*cursor == '"' && (cursor == path_start || cursor[-1] != '\\')) {
            break;
        }
        if (*cursor == '\\' && cursor[1] != '\0') {
            ++cursor;
        }
        ++cursor;
    }
    if (!*cursor) {
        fail_reason = "unterminated path string";
        goto fail;
    }

    size_t raw_len = (size_t)(cursor - path_start);
    char raw_path[HTTP_UPLOAD_STATE_PATH_MAX * 2];
    if (raw_len >= sizeof(raw_path)) {
        printf("[HTTP][STATE] parse warn raw path truncated raw_len=%u line=%s\n",
               (unsigned int)raw_len,
               line);
        raw_len = sizeof(raw_path) - 1;
    }
    memcpy(raw_path, path_start, raw_len);
    raw_path[raw_len] = '\0';

    const char *after_path = cursor + 1;
    const char *size_ptr = strstr(after_path, "\"size\"");
    if (!size_ptr) {
        fail_reason = "missing size field";
        goto fail;
    }
    size_ptr = strchr(size_ptr, ':');
    if (!size_ptr) {
        fail_reason = "missing size colon";
        goto fail;
    }
    size_ptr = http_upload_state_skip_ws(size_ptr + 1);
    if (!size_ptr || !*size_ptr) {
        fail_reason = "empty size value";
        goto fail;
    }

    errno = 0;
    char *endptr = NULL;
    unsigned long size_val = strtoul(size_ptr, &endptr, 10);
    if (size_ptr == endptr || errno == ERANGE) {
        fail_reason = "invalid size value";
        goto fail;
    }
    if (size_val > 0xFFFFFFFFUL) {
        fail_reason = "size overflow";
        goto fail;
    }

    const char *ts_ptr = strstr(endptr, "\"ts\"");
    if (!ts_ptr) {
        fail_reason = "missing ts field";
        goto fail;
    }
    ts_ptr = strchr(ts_ptr, ':');
    if (!ts_ptr) {
        fail_reason = "missing ts colon";
        goto fail;
    }
    ts_ptr = http_upload_state_skip_ws(ts_ptr + 1);
    if (!ts_ptr || !*ts_ptr) {
        fail_reason = "empty ts value";
        goto fail;
    }

    errno = 0;
    char *ts_end = NULL;
    unsigned long ts_val = strtoul(ts_ptr, &ts_end, 10);
    if (ts_ptr == ts_end || errno == ERANGE) {
        fail_reason = "invalid ts value";
        goto fail;
    }
    if (ts_val > 0xFFFFFFFFUL) {
        fail_reason = "ts overflow";
        goto fail;
    }

    char unescaped_path[HTTP_UPLOAD_STATE_PATH_MAX];
    http_upload_state_unescape_json_string(raw_path, unescaped_path, sizeof(unescaped_path));

    strncpy(path_out, unescaped_path, path_len - 1);
    path_out[path_len - 1] = '\0';
    *size_out = (u32)size_val;
    *timestamp_out = (u32)ts_val;

    printf("[HTTP][STATE] parse ok path=%s size=%lu ts=%lu\n",
           unescaped_path,
           size_val,
           ts_val);

    return 0;

fail:
    if (fail_reason) {
        printf("[HTTP][STATE] parse fail: %s line=%s\n", fail_reason, line ? line : "(null)");
    } else {
        printf("[HTTP][STATE] parse fail: unknown reason line=%s\n", line ? line : "(null)");
    }
    return -EINVAL;
}

/**
 * @brief 将当前状态写入磁盘持久化文件。
 */
static int http_upload_state_persist_locked(struct http_upload_state *state)
{
    printf("[HTTP][STATE] persist to %s\n", state->persist_path);
    FILE *fp = fopen(state->persist_path, "w");
    if (!fp) {
        printf("[HTTP][STATE] persist open fail (%s): %d\n", state->persist_path, errno);
        return -errno;
    }

    int err = http_upload_state_write_line(fp, HTTP_UPLOAD_STATE_MAGIC_JSON);
    if (err) {
        printf("[HTTP][STATE] persist write magic fail (%d)\n", err);
        fclose(fp);
        return err;
    }

    for (unsigned int i = 0; i < state->count; ++i) {
        const struct http_upload_state_entry *entry = &state->entries[i];
        if (entry->path[0] == '\0') {
            continue;
        }

        char escaped_path[HTTP_UPLOAD_STATE_PATH_MAX * 2];
        http_upload_state_escape_json_string(entry->path,
                                             escaped_path,
                                             sizeof(escaped_path));

        char line_buf[HTTP_UPLOAD_STATE_PATH_MAX * 2 + 96];
        int written = snprintf(line_buf,
                               sizeof(line_buf),
                               "{\"path\":\"%s\",\"size\":%u,\"ts\":%u}",
                               escaped_path,
                               entry->size,
                               entry->timestamp);
        if (written <= 0 || (size_t)written >= sizeof(line_buf)) {
            printf("[HTTP][STATE] persist json format fail (written=%d)\n", written);
            fclose(fp);
            return -EINVAL;
        }

        err = http_upload_state_write_line(fp, line_buf);
        if (err) {
            printf("[HTTP][STATE] persist write entry fail (%d)\n", err);
            fclose(fp);
            return err;
        }
    }

    if (fclose(fp)) {
        printf("[HTTP][STATE] persist close fail (%d)\n", errno);
        return -errno;
    }

    const char *flush_root = CONFIG_WIFI_CAMERA_HTTP_STORAGE_ROOT;

    int flush_ret = f_free_cache(flush_root);
    if (flush_ret) {
        printf("[HTTP][STATE] persist flush fail (%d), root=%s\n", flush_ret, flush_root);
        return flush_ret;
    }

    printf("[HTTP][STATE] persist done, record_count=%u\n", state->count);
    return 0;
}

/**
 * @brief 去除行末尾的换行符，方便解析文本行。
 */
static void http_upload_state_trim_newline(char *line)
{
    char *newline = strpbrk(line, "\r\n");
    if (newline) {
        *newline = '\0';
    }
}

static int http_upload_state_read_line(FILE *fp,
                                       char *line,
                                       size_t line_len,
                                       size_t *out_len,
                                       int *errno_out,
                                       bool *truncated_out)
{
    printf("[HTTP][STATE][read_line] begin line_len=%u\n", (unsigned int)line_len);
    if (out_len) {
        *out_len = 0;
    }
    if (errno_out) {
        *errno_out = 0;
    }
    if (truncated_out) {
        *truncated_out = false;
    }

    if (!fp || !line || line_len < 2) {
        printf("[HTTP][STATE][read_line] invalid args fp=%p line=%p line_len=%u\n",
               fp,
               line,
               (unsigned int)line_len);
        if (errno_out) {
            *errno_out = EINVAL;
        }
        return -EINVAL;
    }

    size_t total = 0;
    bool newline_found = false;

    while (total + 1 < line_len) {
        unsigned char ch = 0;
        errno = 0;
        size_t read_bytes = fread(&ch, 1, 1, fp);
        if (read_bytes != 1) {
            int read_err = errno;
            if (errno_out) {
                *errno_out = read_err;
            }
            printf("[HTTP][STATE][read_line] read stop total=%u errno=%d\n",
                   (unsigned int)total,
                   read_err);
            break;
        }

        line[total++] = (char)ch;
        // printf("[HTTP][STATE][read_line] got byte idx=%u char=0x%02X (%c)\n",
        //        (unsigned int)(total - 1),
        //        (unsigned int)ch,
        //        (ch >= 0x20 && ch <= 0x7E) ? ch : '.');
        if (ch == '\n') {
            newline_found = true;
            break;
        }
    }

    if (total == line_len - 1 && !newline_found) {
        printf("[HTTP][STATE][read_line] line truncated total=%u\n", (unsigned int)total);
        if (truncated_out) {
            *truncated_out = true;
        }
        unsigned char discard = 0;
        while (1) {
            errno = 0;
            size_t read_bytes = fread(&discard, 1, 1, fp);
            if (read_bytes != 1) {
                if (errno_out && !*errno_out) {
                    *errno_out = errno;
                }
                printf("[HTTP][STATE][read_line] discard stop errno=%d\n", errno);
                break;
            }
            printf("[HTTP][STATE][read_line] discard char=0x%02X (%c)\n",
                   (unsigned int)discard,
                   (discard >= 0x20 && discard <= 0x7E) ? discard : '.');
            if (discard == '\n') {
                break;
            }
        }
    }

    line[total] = '\0';
    printf("[HTTP][STATE][read_line] end total=%u newline=%d line=%s\n",
           (unsigned int)total,
           newline_found ? 1 : 0,
           line);
    if (out_len) {
        *out_len = total;
    }

    if (total == 0 && !newline_found) {
        printf("[HTTP][STATE][read_line] eof reached\n");
        return 1;
    }

    return 0;
}

/**
 * @brief 从持久化文件加载历史记录到内存缓存。
 */
static int http_upload_state_load_locked(struct http_upload_state *state)
{
    printf("[HTTP][STATE] load from %s\n", state->persist_path);
    errno = 0;
    FILE *fp = fopen(state->persist_path, "r");
    if (!fp) {
        int err = errno ? -errno : -ENOENT;
        if (errno == ENOENT || err == -ENOENT) {
            printf("[HTTP][STATE] state file not found (%s)\n", state->persist_path);
            http_upload_state_reset(state);
            return err;
        }

        printf("[HTTP][STATE] state file open fail (%s): %d\n", state->persist_path, errno);
        http_upload_state_reset(state);
        return err;
    }

    long file_size = -1;
    do {
        if (fseek(fp, 0, SEEK_END) == 0) {
            file_size = ftell(fp);
            if (file_size < 0) {
                printf("[HTTP][STATE] ftell fail errno=%d\n", errno);
            }
        } else {
            printf("[HTTP][STATE] fseek fail errno=%d\n", errno);
        }
    } while (0);

    if (file_size >= 0) {
        printf("[HTTP][STATE] file size=%ld bytes\n", file_size);
    }

    errno = 0;
    if (fseek(fp, 0, SEEK_SET) != 0) {
        int rewind_err = errno ? -errno : -EIO;
        printf("[HTTP][STATE] rewind after size fail (%d)\n", errno);
        fclose(fp);
        http_upload_state_reset(state);
        return rewind_err;
    }

    char line[HTTP_UPLOAD_STATE_PATH_MAX * 2 + 128];
    unsigned int line_no = 0;
    int err = 0;
    bool payload_line_read = false;
    int last_read_errno = 0;

    http_upload_state_reset(state);

    for (;;) {
        size_t read_len = 0;
        int read_errno = 0;
        bool line_truncated = false;
        int read_status = http_upload_state_read_line(fp,
                                                      line,
                                                      sizeof(line),
                                                      &read_len,
                                                      &read_errno,
                                                      &line_truncated);
        if (read_status != 0) {
            last_read_errno = read_errno;
            if (read_status < 0) {
                err = read_status;
            }
            break;
        }

        ++line_no;
        if (line_truncated) {
            printf("[HTTP][STATE] warn line%u truncated (len=%u)\n",
                   line_no,
                   (unsigned int)read_len);
        }

        http_upload_state_trim_newline(line);

        if (line_no == 1) {
            if (strcmp(line, HTTP_UPLOAD_STATE_MAGIC_JSON) != 0) {
                printf("[HTTP][STATE] invalid magic in %s\n", state->persist_path);
                err = -EINVAL;
                goto out;
            }
            continue;
        }

        if (line[0] == '\0' || line[0] == '#') {
            printf("[HTTP][STATE] skip line%u: %s\n", line_no, line);
            continue;
        }

        printf("[HTTP][STATE] load line%u: %s\n", line_no, line);
        char path_buf[HTTP_UPLOAD_STATE_PATH_MAX];
        u32 size = 0;
        u32 timestamp = 0;
        if (http_upload_state_parse_json_record(line,
                                                path_buf,
                                                sizeof(path_buf),
                                                &size,
                                                &timestamp)) {
            printf("[HTTP][STATE] json parse fail line%u: %s\n", line_no, line);
            continue;
        }

        payload_line_read = true;

        printf("[HTTP][STATE] load entry #%u path=%s size=%u ts=%u\n",
               state->count,
               path_buf,
               size,
               timestamp);

        http_upload_state_upsert_locked(state,
                                        path_buf,
                                        size,
                                        timestamp);
    }

out:
    if (!payload_line_read) {
        errno = 0;
        long final_pos = ftell(fp);
        int final_pos_errno = (final_pos < 0) ? errno : 0;
        long file_size_logged = (file_size >= 0) ? file_size : -1;

        if (line_no <= 1) {
            printf("[HTTP][STATE] load no payload lines (line_no=%u, last_errno=%d, final_pos=%ld/%ld, final_pos_errno=%d)\n",
                   line_no,
                   last_read_errno,
                   final_pos,
                   file_size_logged,
                   final_pos_errno);
        } else {
            printf("[HTTP][STATE] load payload lines missing despite header (line_no=%u, last_errno=%d, final_pos=%ld/%ld, final_pos_errno=%d)\n",
                   line_no,
                   last_read_errno,
                   final_pos,
                   file_size_logged,
                   final_pos_errno);
        }

        if (file_size > 0) {
            errno = 0;
            if (fseek(fp, 0, SEEK_SET) == 0) {
                char sample_buf[128];
                size_t sample_len = fread(sample_buf, 1, sizeof(sample_buf) - 1, fp);
                if (sample_len > 0) {
                    sample_buf[sample_len] = '\0';
                    for (size_t i = 0; i < sample_len; ++i) {
                        unsigned char ch = (unsigned char)sample_buf[i];
                        if (ch < 0x20 && ch != '\n' && ch != '\r' && ch != '\t') {
                            sample_buf[i] = '.';
                        }
                    }

                    char sample_hex[sizeof(sample_buf) * 3];
                    size_t hex_pos = 0;
                    for (size_t i = 0; i < sample_len && hex_pos + 4 < sizeof(sample_hex); ++i) {
                        int written = snprintf(&sample_hex[hex_pos],
                                               sizeof(sample_hex) - hex_pos,
                                               "%02X ",
                                               (unsigned int)(unsigned char)sample_buf[i]);
                        if (written <= 0) {
                            break;
                        }
                        hex_pos += (size_t)written;
                    }
                    if (hex_pos < sizeof(sample_hex)) {
                        sample_hex[hex_pos] = '\0';
                    } else {
                        sample_hex[sizeof(sample_hex) - 1] = '\0';
                    }

                    printf("[HTTP][STATE] payload sample text: %s\n", sample_buf);
                    printf("[HTTP][STATE] payload sample hex: %s (len=%u)\n",
                           sample_hex,
                           (unsigned int)sample_len);
                } else {
                    printf("[HTTP][STATE] payload sample read empty (errno=%d)\n", errno);
                }
                if (fseek(fp, 0, SEEK_END) != 0) {
                    printf("[HTTP][STATE] payload sample seek end fail (errno=%d)\n", errno);
                }
            } else {
                printf("[HTTP][STATE] payload sample seek start fail (errno=%d)\n", errno);
            }
        }
    }
    printf("[HTTP][STATE] load finished, entry_count=%u err=%d\n", state->count, err);
    if (fclose(fp)) {
        printf("[HTTP][STATE] load close fail (%d)\n", errno);
        if (!err) {
            err = -errno;
        }
    }
    return err;
}

/**
 * @brief 初始化状态管理器，负责加载历史记录并创建互斥锁。
 */
int http_upload_state_init(struct http_upload_state *state, const char *persist_path)
{
    if (!state || !persist_path || persist_path[0] == '\0') {
        return -EINVAL;
    }

    printf("[HTTP][STATE] init begin, file=%s\n", persist_path);

    memset(state, 0, sizeof(*state));
    http_upload_state_reset(state);

    strncpy(state->persist_path, persist_path, sizeof(state->persist_path) - 1);
    state->persist_path[sizeof(state->persist_path) - 1] = '\0';
    state->persist_loaded = false;
    state->pending_reload = false;

    if (os_mutex_create(&state->lock)) {
        printf("[HTTP][STATE] mutex create fail\n");
        return -ENOMEM;
    }

    int err = os_mutex_pend(&state->lock, 0);
    if (err) {
        printf("[HTTP][STATE] mutex pend fail (%d)\n", err);
        return err;
    }

    err = http_upload_state_load_locked(state);
    os_mutex_post(&state->lock);

    if (err == -ENOENT) {
        state->pending_reload = true;
        err = 0;
    }

    if (err) {
        printf("[HTTP][STATE] load fail (%d)\n", err);
        http_upload_state_reset(state);
    } else {
        if (!state->pending_reload) {
            state->persist_loaded = true;
        }
        printf("[HTTP][STATE] init done, record_count=%u\n", state->count);
    }

    state->initialized = true;
    return 0;
}

/**
 * @brief 检查给定文件是否已存在于历史上传记录中。
 */
bool http_upload_state_is_duplicate(struct http_upload_state *state,
                                    const char *path,
                                    u32 size,
                                    u32 timestamp)
{
    if (!state || !state->initialized || !path) {
        printf("[HTTP][STATE] is_duplicate invalid args\n");
        return false;
    }

    if (os_mutex_pend(&state->lock, 0)) {
        return false;
    }

    bool duplicate = false;
    for (unsigned int i = 0; i < state->count; ++i) {
        const struct http_upload_state_entry *entry = &state->entries[i];
        if (entry->path[0] == '\0') {
            continue;
        }
        if (strncmp(entry->path, path, sizeof(entry->path)) == 0) {
            bool size_known_entry = entry->size != 0U;
            bool size_known_input = size != 0U;
            bool size_match = (!size_known_entry || !size_known_input) || (entry->size == size);

            bool ts_known_entry = entry->timestamp != 0U;
            bool ts_known_input = timestamp != 0U;
            bool ts_match = false;
            if (!ts_known_entry || !ts_known_input) {
                ts_match = true;
            } else {
                unsigned int diff = (unsigned int)abs((int)entry->timestamp - (int)timestamp);
                ts_match = (diff <= 2U);
            }

            if (size_match && ts_match) {
                duplicate = true;
                break;
            }
            if (!size_match || !ts_match) {
                printf("[HTTP][STATE] path collision but metadata mismatch: %s (size %u vs %u, ts %u vs %u)\n",
                       entry->path,
                       entry->size,
                       size,
                       entry->timestamp,
                       timestamp);
            }
        }
    }

    os_mutex_post(&state->lock);
    return duplicate;
}

/**
 * @brief 记录上传成功的文件信息并同步到磁盘。
 */
int http_upload_state_record_success(struct http_upload_state *state,
                                     const char *path,
                                     u32 size,
                                     u32 timestamp)
{
    if (!state || !state->initialized || !path) {
        printf("[HTTP][STATE] record_success invalid args\n");
        return -EINVAL;
    }

    int err = os_mutex_pend(&state->lock, 0);
    if (err) {
        printf("[HTTP][STATE] record_success mutex pend fail (%d)\n", err);
        return err;
    }

    http_upload_state_upsert_locked(state, path, size, timestamp);
    err = http_upload_state_persist_locked(state);
    if (!err) {
        state->persist_loaded = true;
        state->pending_reload = false;
    }

    os_mutex_post(&state->lock);
    printf("[HTTP][STATE] record_success done\n");
    return err;
}

// 在存储介质就绪后重新从磁盘加载历史记录。
int http_upload_state_reload(struct http_upload_state *state)
{
    printf("[HTTP][STATE] reload\n");
    if (!state || !state->initialized) {
        return -EINVAL;
    }

    int err = os_mutex_pend(&state->lock, 0);
    if (err) {
        return err;
    }

    err = http_upload_state_load_locked(state);
    if (err == -ENOENT) {
        /*
         * 持久化文件不存在时视为“空状态”并允许后续流程运行。
         * 这种情况通常发生在首次启动或尚未产生上传记录时。
         */
        state->pending_reload = false;
        state->persist_loaded = true;
        err = 0;
    } else if (err) {
        state->pending_reload = true;
        state->persist_loaded = false;
    } else {
        state->pending_reload = false;
        state->persist_loaded = true;
    }

    os_mutex_post(&state->lock);
    return err;
}

void http_upload_state_set_pending_reload(struct http_upload_state *state, bool pending)
{
    if (!state || !state->initialized) {
        return;
    }

    if (os_mutex_pend(&state->lock, 0)) {
        return;
    }

    state->pending_reload = pending;

    os_mutex_post(&state->lock);
}

#endif /* CONFIG_NET_ENABLE */
