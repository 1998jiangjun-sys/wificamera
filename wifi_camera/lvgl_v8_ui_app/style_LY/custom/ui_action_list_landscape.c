#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
#include "lvgl.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_config.h"
#include "ui.h"
#include "custom.h"
#include "../generated/gui_res/res_common.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "fs/fs.h"
#include "video_dec_server.h"
#include "video_dec.h"
#include "asm/jpeg_codec.h"
#include "asm/hwi.h"
#include "system/includes.h"
#include "fs/fs.h"
#include "os/os_api.h"
#include "video_ioctl.h"
#include "video.h"
#include "pipeline_core.h"
#include "video/fb.h"
#include "asm/jldma2d.h"
#include "key_event.h"
#include "app_msg.h"

/* 管线状态定义 */
#define PIPELINE_STOP       0   // 管线处于停止状态
#define PIPELINE_EXIT       1   // 管线已退出
#define PIPELINE_RUNING     2   // 管线正在运行
#define PIPELINE_IDLE       3   // 管线空闲等待

/* 预览图相关配置 */
#define LATEST_PREVIEW_WIDTH 640      // 预览图宽度
#define LATEST_PREVIEW_HEIGHT 480     // 预览图高度
#define LATEST_PREVIEW_PATH_MAX 512   // 预览路径最大长度
#define LATEST_PREVIEW_SCAN_OPTS "-tMOVJPGAVI -st -r" // 文件扫描参数

/* 扫描目录列表 */
static const char *const s_video_dir_landscape_paths[] = {
    CONFIG_DEC_PATH_1,
    CONFIG_DEC_PATH_2,
    CONFIG_DEC_PATH_3,
    CONFIG_DEC_PATH_4,
    CONFIG_DEC_PATH_5,
};

/* 缩略图显示配置 */
#define VIDEO_DIR_LANDSCAPE_THUMB_WIDTH       80   // 缩略图宽度
#define VIDEO_DIR_LANDSCAPE_THUMB_HEIGHT      64   // 缩略图高度
#define VIDEO_DIR_LANDSCAPE_THUMB_MAX         1000 // 最大缩略图数量
#define VIDEO_DIR_LANDSCAPE_THUMB_PAD         19   // 缩略图内边距
#define VIDEO_DIR_LANDSCAPE_THUMB_GAP         16   // 缩略图间距
#define VIDEO_DIR_LANDSCAPE_THUMB_PRELOAD_COUNT 6  // 懒加载预取数量

#define VIDEO_DIR_LANDSCAPE_THUMB_TASK_NAME    "land_thumb_decode"
#define VIDEO_DIR_LANDSCAPE_THUMB_THREAD_PRIO  10
#define VIDEO_DIR_LANDSCAPE_THUMB_STACK_SIZE   1024
#define VIDEO_DIR_LANDSCAPE_THUMB_QUEUE_SIZE   512

#define USE_DMA2D_CONVERT 1                      // 是否启用DMA2D转换

typedef struct {
    char path[LATEST_PREVIEW_PATH_MAX];
    char dir[LATEST_PREVIEW_PATH_MAX];
    char name[128];
    bool is_video;
} video_dir_landscape_media_entry_t;

typedef struct {
    lv_obj_t *placeholder;
    lv_obj_t *video_flag;
    lv_img_dsc_t dsc;
    u8 *buf;
    char path[LATEST_PREVIEW_PATH_MAX];
    size_t index;
    bool pending;
    bool ready;
    bool active;
    bool is_video;
} video_dir_landscape_thumb_slot_t;

static video_dir_landscape_media_entry_t *s_landscape_media_entries;
static size_t s_landscape_media_count;

static video_dir_landscape_thumb_slot_t s_landscape_thumbs[VIDEO_DIR_LANDSCAPE_THUMB_MAX];
static size_t s_landscape_thumb_count;
static int s_landscape_thumb_task_pid;
static bool s_landscape_click_in_progress;
static lv_obj_t *s_landscape_loading_parent;
static lv_coord_t s_landscape_loading_parent_x;
static lv_coord_t s_landscape_loading_parent_y;
static bool s_landscape_loading_on_layer_top;

static lv_img_dsc_t s_landscape_preview_dsc;
static u8 *s_landscape_preview_buf;
static size_t s_landscape_active_index;
static bool s_landscape_active_valid;
static char s_landscape_active_path[LATEST_PREVIEW_PATH_MAX];
static u8 *s_landscape_rgb_tmp;
static size_t s_landscape_rgb_tmp_size;

static OS_MUTEX s_landscape_pipeline_mutex;
static bool s_landscape_pipeline_mutex_ready;
static u8 s_landscape_pipeline_state;
static pipe_core_t *s_landscape_pipe_core;
static OS_SEM s_landscape_sem;

extern int storage_device_ready(void);
extern lv_ui guider_ui;
extern void cfun_dec_ok(void);

static void video_dir_landscape_thumb_task(void *priv);
static void video_dir_landscape_thumb_task_start(void);
static void video_dir_landscape_thumb_task_stop(void);
static bool video_dir_landscape_thumb_task_pause(void);
static void video_dir_landscape_thumb_task_resume(bool resume_needed);
static void video_dir_landscape_thumb_queue_request(video_dir_landscape_thumb_slot_t *slot, int remaining);
static void video_dir_landscape_thumb_update_cb(int slot_ptr);
static void video_dir_landscape_thumb_lazy_load(lv_event_t *e);
static void video_dir_landscape_thumb_slots_clear(lv_obj_t *strip);
static void video_dir_landscape_update_thumbnail_highlight_by_index(size_t active_index);
static void video_dir_landscape_build_thumbnails(lv_ui_video_dir_landscape_mode *ui_scr);
static int video_dir_landscape_show_preview_decode(const char *path, bool broadcast_dir);
static int video_dir_landscape_show_preview_from_path(const char *path, bool broadcast_dir);
static int video_dir_landscape_show_preview_by_index(size_t index, bool broadcast_dir);
static void video_dir_landscape_set_loading_visible(bool visible);
static void video_dir_landscape_process_thumb_click_async(void *user_data);

static char video_dir_landscape_ascii_toupper(char ch)
{
    if ((ch >= 'a') && (ch <= 'z')) {
        return ch - ('a' - 'A');
    }
    return ch;
}

static int video_dir_landscape_path_is_jpeg(const char *path)
{
    if (!path) {
        return 0;
    }

    const char *ext = strrchr(path, '.');
    if (!ext || !ext[1]) {
        return 0;
    }

    ext += 1;
    size_t ext_len = strlen(ext);

    if (ext_len == 3) {
        return (video_dir_landscape_ascii_toupper(ext[0]) == 'J') &&
               (video_dir_landscape_ascii_toupper(ext[1]) == 'P') &&
               (video_dir_landscape_ascii_toupper(ext[2]) == 'G');
    }

    if (ext_len == 4) {
        return (video_dir_landscape_ascii_toupper(ext[0]) == 'J') &&
               (video_dir_landscape_ascii_toupper(ext[1]) == 'P') &&
               (video_dir_landscape_ascii_toupper(ext[2]) == 'E') &&
               (video_dir_landscape_ascii_toupper(ext[3]) == 'G');
    }

    return 0;
}

static bool video_dir_landscape_path_is_video(const char *path)
{
    if (!path) {
        return false;
    }

    const char *ext = strrchr(path, '.');
    if (!ext || !ext[1]) {
        return false;
    }

    ext += 1;

    static const char *const video_exts[] = {
        "AVI",
        "MOV"
    };

    for (size_t i = 0; i < ARRAY_SIZE(video_exts); ++i) {
        const char *target = video_exts[i];
        size_t j = 0;
        while (target[j]) {
            if (!ext[j]) {
                break;
            }
            if (video_dir_landscape_ascii_toupper(ext[j]) != target[j]) {
                break;
            }
            ++j;
        }

        if (!target[j] && !ext[j]) {
            return true;
        }
    }

    return false;
}

static bool video_dir_landscape_pipeline_lock(void)
{
    if (!s_landscape_pipeline_mutex_ready) {
        if (os_mutex_create(&s_landscape_pipeline_mutex)) {
            printf("video_dir_landscape: mutex create fail\n");
            return false;
        }
        s_landscape_pipeline_mutex_ready = true;
    }

    os_mutex_pend(&s_landscape_pipeline_mutex, 0);
    return true;
}

static void video_dir_landscape_pipeline_unlock(bool locked)
{
    if (locked && s_landscape_pipeline_mutex_ready) {
        os_mutex_post(&s_landscape_pipeline_mutex);
    }
}

static u8 *video_dir_landscape_rgb_tmp_acquire(size_t needed)
{
    if (needed == 0) {
        return NULL;
    }

    if (s_landscape_rgb_tmp_size < needed) {
        u8 *new_buf = realloc(s_landscape_rgb_tmp, needed);
        if (!new_buf) {
            return NULL;
        }
        s_landscape_rgb_tmp = new_buf;
        s_landscape_rgb_tmp_size = needed;
    }

    return s_landscape_rgb_tmp;
}

static void video_dir_landscape_rgb_tmp_release(void)
{
    if (s_landscape_rgb_tmp) {
        free(s_landscape_rgb_tmp);
        s_landscape_rgb_tmp = NULL;
        s_landscape_rgb_tmp_size = 0;
    }
}

static void video_dir_landscape_clear_active_selection(void)
{
    s_landscape_active_valid = false;
    s_landscape_active_index = 0;
    s_landscape_active_path[0] = '\0';
    video_dir_landscape_update_thumbnail_highlight_by_index(SIZE_MAX);
}

static void video_dir_landscape_media_entries_clear(void)
{
    if (s_landscape_media_entries) {
        free(s_landscape_media_entries);
        s_landscape_media_entries = NULL;
    }
    s_landscape_media_count = 0;
    video_dir_landscape_clear_active_selection();
}

static int video_dir_landscape_media_entries_set(const video_dir_landscape_media_entry_t *entries, size_t count)
{
    video_dir_landscape_media_entries_clear();

    if (!entries || !count) {
        return 0;
    }

    size_t alloc_len = count * sizeof(video_dir_landscape_media_entry_t);
    video_dir_landscape_media_entry_t *copy = malloc(alloc_len);
    if (!copy) {
        printf("video_dir_landscape: media entries alloc fail count=%u\n", (unsigned)count);
        return -1;
    }

    memcpy(copy, entries, alloc_len);
    s_landscape_media_entries = copy;
    s_landscape_media_count = count;
    return 0;
}

static const video_dir_landscape_media_entry_t *video_dir_landscape_media_get_entry(size_t index)
{
    if (!s_landscape_media_entries || index >= s_landscape_media_count) {
        return NULL;
    }
    return &s_landscape_media_entries[index];
}

static int video_dir_landscape_media_find_index_by_path(const char *path)
{
    if (!path || !s_landscape_media_entries) {
        return -1;
    }

    for (size_t i = 0; i < s_landscape_media_count; ++i) {
        if (strcmp(s_landscape_media_entries[i].path, path) == 0) {
            return (int)i;
        }
    }

    return -1;
}

static void video_dir_landscape_set_active_index(size_t index)
{
    if (!s_landscape_media_entries || index >= s_landscape_media_count) {
        video_dir_landscape_clear_active_selection();
        video_dir_landscape_update_thumbnail_highlight_by_index(SIZE_MAX);
        return;
    }

    const video_dir_landscape_media_entry_t *entry = &s_landscape_media_entries[index];
    s_landscape_active_index = index;
    s_landscape_active_valid = true;
    strncpy(s_landscape_active_path, entry->path, sizeof(s_landscape_active_path) - 1);
    s_landscape_active_path[sizeof(s_landscape_active_path) - 1] = '\0';

    video_dir_landscape_update_thumbnail_highlight_by_index(index);
}

static void video_dir_landscape_set_play_icon_visible(bool visible)
{
    lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
    if (!ui_scr) {
        return;
    }

    lv_obj_t *icon = ui_scr->video_dir_landscape_mode_img_15;
    if (!icon || !lv_obj_is_valid(icon)) {
        return;
    }

    if (visible) {
        lv_obj_clear_flag(icon, LV_OBJ_FLAG_HIDDEN);
    } else if (!lv_obj_has_flag(icon, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_add_flag(icon, LV_OBJ_FLAG_HIDDEN);
    }
}

static void video_dir_landscape_extract_directory_from_path(const char *path, char *dir_buf, size_t dir_len)
{
    if (!dir_buf || dir_len == 0) {
        return;
    }

    dir_buf[0] = '\0';

    if (!path || !path[0]) {
        return;
    }

    strncpy(dir_buf, path, dir_len - 1);
    dir_buf[dir_len - 1] = '\0';

    char *slash = strrchr(dir_buf, '/');
    char *bslash = strrchr(dir_buf, '\\');
    char *sep = slash;
    if (!sep || (bslash && bslash > sep)) {
        sep = bslash;
    }
    if (sep) {
        *(sep + 1) = '\0';
    } else {
        dir_buf[0] = '\0';
    }
}

static void video_dir_landscape_send_directory_message(const char *dir)
{
    if (!dir || !dir[0]) {
        return;
    }

    size_t dir_len = strlen(dir) + 1;
    char *dir_msg = lvgl_module_msg_get_ptr(GUI_MODEL_MSG_ID_FILE_PATH, dir_len);
    if (dir_msg) {
        memcpy(dir_msg, dir, dir_len);
        lvgl_module_msg_send_ptr(dir_msg, 0);
    }
}

static void video_dir_landscape_set_loading_visible(bool visible)
{
    lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
    if (!ui_scr) {
        return;
    }

    lv_obj_t *loading = ui_scr->video_dir_landscape_mode_img_13;
    if (!loading || !lv_obj_is_valid(loading)) {
        return;
    }

    if (!s_landscape_loading_parent || !lv_obj_is_valid(s_landscape_loading_parent)) {
        s_landscape_loading_parent = lv_obj_get_parent(loading);
        if (s_landscape_loading_parent && lv_obj_is_valid(s_landscape_loading_parent)) {
            s_landscape_loading_parent_x = lv_obj_get_x(loading);
            s_landscape_loading_parent_y = lv_obj_get_y(loading);
        }
    }

    if (visible) {
        lv_obj_clear_flag(loading, LV_OBJ_FLAG_HIDDEN);

        lv_obj_t *top = lv_layer_top();
        if (top && lv_obj_get_parent(loading) != top) {
            if (lv_obj_is_valid(lv_obj_get_parent(loading))) {
                s_landscape_loading_parent = lv_obj_get_parent(loading);
                s_landscape_loading_parent_x = lv_obj_get_x(loading);
                s_landscape_loading_parent_y = lv_obj_get_y(loading);
            }
            lv_obj_set_parent(loading, top);
            s_landscape_loading_on_layer_top = true;
        }

        lv_obj_move_foreground(loading);
        lv_obj_center(loading);
        lv_obj_invalidate(loading);

        lv_disp_t *disp = lv_obj_get_disp(loading);
        if (disp) {
            lv_refr_now(disp);
        }
    } else {
        lv_obj_add_flag(loading, LV_OBJ_FLAG_HIDDEN);

        if (s_landscape_loading_on_layer_top && s_landscape_loading_parent && lv_obj_is_valid(s_landscape_loading_parent)) {
            lv_obj_set_parent(loading, s_landscape_loading_parent);
            lv_obj_set_pos(loading, s_landscape_loading_parent_x, s_landscape_loading_parent_y);
        }

        s_landscape_loading_on_layer_top = false;
        lv_obj_invalidate(loading);
    }
    printf("Loading %s ！！！\n", visible ? "started" : "stopped");
}

static u8 *find_jpg_thumbnails(u8 *stream, int len, int *thm_len)
{
    u8 marker;
    int chunk_len = 0;
    int offset = 0;

    if (!stream || len < 4 || !thm_len) {
        return NULL;
    }

    if ((stream[0] != 0xFF) || (stream[1] != 0xD8)) {
        return NULL;
    }

    stream += 2;
    while (1) {
        if (*stream++ != 0xFF) {
            return NULL;
        }

        while (*stream == 0xFF) {
            stream++;
        }

        marker = *stream++;
        chunk_len = (u16)(stream[0] << 8) | stream[1];
        if (marker == 0xE1) {
            stream += 2;
            while (1) {
                if ((stream[offset] == 0xFF) && (stream[offset + 1] == 0xD8)) {
                    break;
                }

                if (++offset > (chunk_len - 2)) {
                    return NULL;
                }
            }

            *thm_len = chunk_len - 2 - offset;
            return stream + offset;
        }
        stream += chunk_len;
    }

    return NULL;
}

static int check_fourcc(u8 *buf, const char *fourcc)
{
    return memcmp(buf, fourcc, 4) == 0;
}

static int read_fourcc_and_size(FILE *fd, u8 *fourcc, u32 *size)
{
    if (fread(fourcc, 4, 1, fd) != 4) {
        return -1;
    }
    if (fread(size, 4, 1, fd) != 4) {
        return -1;
    }
    return 0;
}

static u8 *get_avi_first_frame(FILE *fd, u32 *jpeg_size)
{
    static int read_times = 0;
    char fourcc[4];
    u32 size;

    fseek(fd, 0, SEEK_SET);

    if (read_fourcc_and_size(fd, (u8 *)fourcc, &size) != 0 ||
        !check_fourcc((u8 *)fourcc, "RIFF")) {
        printf("invalid RIFF header");
        return NULL;
    }
    if (read_fourcc_and_size(fd, (u8 *)fourcc, &size) != 0 ||
        !check_fourcc((u8 *)fourcc, "AVI ")) {
        printf("invalid AVI header");
        return NULL;
    }

    while (read_fourcc_and_size(fd, (u8 *)fourcc, &size) == 0) {
        if (check_fourcc((u8 *)fourcc, "LIST")) {
            char list_type[4];
            if (fread(list_type, 1, 4, fd) != 4) {
                printf("invalid LIST type\n");
                return NULL;
            }
            if (check_fourcc((u8 *)list_type, "movi")) {
                break;
            } else {
                fseek(fd, size - 4, SEEK_CUR);
            }
        } else {
            fseek(fd, size, SEEK_CUR);
        }
    }

    while (read_fourcc_and_size(fd, (u8 *)fourcc, &size) == 0) {
        if (read_times++ > 4) {
            read_times = 0;
            break;
        }

        if (check_fourcc((u8 *)fourcc, "00dc")) {
            read_times = 0;
            *jpeg_size = size;
            u8 *jpeg_buf = malloc(size);
            if (!jpeg_buf) {
                printf("jpeg_buf malloc fail\n");
                return NULL;
            }
            if (fread(jpeg_buf, size, 1, fd) != size) {
                printf("jpeg fread err\n");
                free(jpeg_buf);
                return NULL;
            }
            return jpeg_buf;
        } else {
            fseek(fd, size, SEEK_CUR);
        }
    }
    printf("not found jpeg frame\n");
    return NULL;
}

static u8 *get_frame_buf(const char *path, u32 *size)
{
    FILE *fd = NULL;
    u8 *file_buf = NULL;
    u32 file_len;

    fd = fopen(path, "rb");
    if (fd == NULL) {
        printf("no file name : %s\n", path);
        goto err;
    }

    if ((strcmp(lv_fs_get_ext(path), "jpg") == 0) || (strcmp(lv_fs_get_ext(path), "JPG") == 0)) {
        file_len = flen(fd);
        file_buf = malloc(file_len);
        if (!file_buf) {
            printf("buf malloc err ...\n");
            goto err;
        }
        if (fread(file_buf, 1, file_len, fd) != file_len) {
            printf("read file lenth err ...\n");
            goto err;
        }
    } else {
        file_buf = get_avi_first_frame(fd, &file_len);
        if (!file_buf) {
            printf("get_frame_buf err");
            goto err;
        }
    }

    fclose(fd);

    *size = file_len;
    return file_buf;

err:
    if (fd) {
        fclose(fd);
    }
    if (file_buf) {
        free(file_buf);
    }
    return NULL;
}

static bool video_dir_landscape_media_has_valid_thumb(const char *path, bool is_video)
{
    if (!path || !path[0]) {
        return false;
    }

    if (!is_video) {
        return true;
    }

    u32 frame_len = 0;
    u8 *frame_buf = get_frame_buf(path, &frame_len);
    if (!frame_buf || frame_len == 0) {
        if (frame_buf) {
            free(frame_buf);
        }
        printf("video_dir_landscape: skip invalid video %s\n", path);
        return false;
    }

    free(frame_buf);
    return true;
}

static int yuyv2rgb16_dma2d(u8 *yuv_buf, u8 *rgb_buf, int width, int height)
{
    int err;

    u32 in_format = JLDMA2D_FORMAT_YUV422_BT709;
    u32 out_format = JLDMA2D_FORMAT_RGB565;
    u32 dest_stride = width * dma2d_get_format_bpp(out_format) / 8;
    u32 src_stride = width * dma2d_get_format_bpp(in_format) / 8;
    err = jldma2d_format(rgb_buf,
                         yuv_buf,
                         dest_stride,
                         src_stride,
                         in_format,
                         out_format,
                         width,
                         height,
                         0,
                         0);
    return err;
}

static void video_dir_landscape_soft_uyvy_to_rgb16(u8 *uyvy, u16 *rgb, int width, int height)
{
    int x, y;
    u8 u, y1, v, y2;
    int c, d, e;
    int r, g, b;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x += 2) {
            u  = uyvy[0];
            y1 = uyvy[1];
            v  = uyvy[2];
            y2 = uyvy[3];

            uyvy += 4;

            c = y1 - 16;
            d = u - 128;
            e = v - 128;

            r = (298 * c + 409 * e + 128) >> 8;
            g = (298 * c - 100 * d - 208 * e + 128) >> 8;
            b = (298 * c + 516 * d + 128) >> 8;

            r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
            g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
            b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

            rgb[0] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);

            c = y2 - 16;
            r = (298 * c + 409 * e + 128) >> 8;
            g = (298 * c - 100 * d - 208 * e + 128) >> 8;
            b = (298 * c + 516 * d + 128) >> 8;

            r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
            g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
            b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

            rgb[1] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);

            rgb += 2;
        }
    }
}

static void rotate_rgb565_clockwise(uint16_t *dst, const uint16_t *src, int src_w, int src_h)
{
    int dst_w = src_h;
    int dst_h = src_w;

    for (int y = 0; y < src_h; ++y) {
        const uint16_t *src_row = src + y * src_w;
        for (int x = 0; x < src_w; ++x) {
            int new_x = dst_w - 1 - y;
            int new_y = x;
            dst[new_y * dst_w + new_x] = src_row[x];
        }
    }
}

static void video_dir_landscape_on_event(const char *name, int type, void *arg)
{
    OS_SEM *sem = (OS_SEM *)arg;
    switch (type) {
    case EVENT_FRAME_DONE:
        if (!strncmp(name, "yuv", 3)) {
            os_sem_post(sem);
        }
        break;
    case EVENT_PREPARE_DONE:
        printf("PREPARE %s done", name);
        break;

    case EVENT_START_DONE:
        printf("START %s done", name);
        break;

    case EVENT_STOP_DONE:
        printf("STOP %s done", name);
        break;
    case EVENT_RESET_DONE:
        printf("RESET %s done", name);
        break;
    case EVENT_BW_FULL:
    case EVENT_BUFFER_FULL:
    case EVENT_SPEED_FULL:
    case EVENT_OSD_ERR:
    case EVENT_LINE_ERR:
        printf("err %s ", name);
        break;
    }
}

static int video_dir_landscape_jpeg2yuv_pipeline_init(struct video_format *f)
{
    pipe_filter_t *jpeg_dec_filter, *imc_filter, *rep_filter, *yuv_filter, *virtual_filter;
    os_sem_create(&s_landscape_sem, 0);
    s_landscape_pipe_core = pipeline_init(video_dir_landscape_on_event, &s_landscape_sem);
    if (!s_landscape_pipe_core) {
        printf("pipeline init err\n");
        return -1;
    }

    char *source_name = plugin_factory_find("virtual");
    s_landscape_pipe_core->channel = plugin_source_to_channel(source_name);
    virtual_filter = pipeline_filter_add(s_landscape_pipe_core, source_name);
    jpeg_dec_filter = pipeline_filter_add(s_landscape_pipe_core, plugin_factory_find("jpeg_dec"));
    rep_filter = pipeline_filter_add(s_landscape_pipe_core, "rep1");
    imc_filter = pipeline_filter_add(s_landscape_pipe_core, "imc3");
    yuv_filter = pipeline_filter_add(s_landscape_pipe_core, plugin_factory_find("yuv"));

    pipeline_param_set(s_landscape_pipe_core, NULL, PIPELINE_SET_FORMAT, f);

    int out_format = FORMAT_YUV422_UYVY;
    pipeline_param_set(s_landscape_pipe_core, NULL, PIPELINE_SET_SINK_OUT_FORMAT, (int)&out_format);

    int line_cnt = 16;
    pipeline_param_set(s_landscape_pipe_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

    pipeline_filter_link(virtual_filter, jpeg_dec_filter);
    pipeline_filter_link(jpeg_dec_filter, rep_filter);
    pipeline_filter_link(rep_filter, imc_filter);
    pipeline_filter_link(imc_filter, yuv_filter);

    pipeline_prepare(s_landscape_pipe_core);
    pipeline_start(s_landscape_pipe_core);
    return 0;
}

static void video_dir_landscape_jpeg2yuv_pipeline_uninit(void)
{
    if (s_landscape_pipe_core) {
        pipeline_stop(s_landscape_pipe_core);
        pipeline_reset(s_landscape_pipe_core);
        pipeline_uninit(s_landscape_pipe_core);

        os_sem_del(&s_landscape_sem, 0);
        s_landscape_pipe_core = NULL;
    }

    video_dir_landscape_rgb_tmp_release();
}

static int video_dir_landscape_jpeg2yuv_with_pipeline(const char *path, u8 *img_buf, int dst_w, int dst_h)
{
    int err = 0;
    u8 *frame_buf = NULL;
    int frame_len;
    u8 *dec_buf = NULL;
    int dec_len;
    u8 *yuv_buf;
    u8 *rgb_tmp = NULL;
    static int last_width, last_height, last_format;
    static int last_dst_w, last_dst_h;

    if (s_landscape_pipeline_state == PIPELINE_EXIT) {
        return 0;
    }

    frame_buf = get_frame_buf(path, &frame_len);
    if (!frame_buf) {
        printf("get decode data fail");
        err = -EFAULT;
        goto exit;
    }

    dec_buf = find_jpg_thumbnails(frame_buf, frame_len, &dec_len);
    if (!dec_buf) {
        dec_buf = frame_buf;
        dec_len = frame_len;
    }

    struct jpeg_image_info info = {0};
    struct video_format f  = {0};
    int fmt = 0;
    info.input.data.buf = dec_buf;
    info.input.data.len = dec_len;
    err = jpeg_decode_image_info(&info);
    if (err) {
        printf("jpeg_decode_image_info err %s\n", path);
        goto exit;
    }
    printf("thumb jpeg info: %d x %d len=%d\n", info.width, info.height, dec_len);
    switch (info.sample_fmt) {
    case JPG_SAMP_FMT_YUV444:
        fmt = VIDEO_PIX_FMT_YUV444;
        break;
    case JPG_SAMP_FMT_YUV422:
        fmt = VIDEO_PIX_FMT_YUV422;
        break;
    case JPG_SAMP_FMT_YUV420:
        fmt = VIDEO_PIX_FMT_YUV420;
        break;
    default:
        printf("err fmt\n");
        break;
    }
    f.src_width = info.width;
    f.src_height = info.height;
    f.win.width = dst_w;
    f.win.height = dst_h;
    f.type = VIDEO_BUF_TYPE_VIDEO_PLAY;
    f.pixelformat = VIDEO_PIX_FMT_JPEG | fmt;
    f.private_data = "fb5";

    if ((last_height != info.height) || (last_width != info.width)
        || (last_format != fmt) || (last_dst_w != dst_w) || (last_dst_h != dst_h)
        || (s_landscape_pipeline_state == PIPELINE_STOP)) {

        video_dir_landscape_jpeg2yuv_pipeline_uninit();
        if (video_dir_landscape_jpeg2yuv_pipeline_init(&f)) {
            err = -EFAULT;
            goto exit;
        }
    }
    s_landscape_pipeline_state = PIPELINE_RUNING;

    last_width = info.width;
    last_height = info.height;
    last_format = fmt;
    last_dst_w = dst_w;
    last_dst_h = dst_h;

    struct video_cap_buffer buffer;
    buffer.size = dec_len;
    buffer.buf = dec_buf;
    pipeline_param_set(s_landscape_pipe_core, NULL, VIDIOC_RDBUF, &buffer);

    err = os_sem_pend(&s_landscape_sem, 200);
    if (err) {
        log_e("jpeg2yuv timeout\n");
        goto exit;
    }
    printf("jpeg2yuv ok\n");

    pipeline_param_get(s_landscape_pipe_core, NULL, PIPELINE_GET_YUV_BUF, &yuv_buf);
    if (!yuv_buf) {
        printf("get yuv buf err\n");
        err = -EFAULT;
        goto exit;
    }

    size_t rgb_tmp_len = (size_t)dst_w * dst_h * 2;
    rgb_tmp = video_dir_landscape_rgb_tmp_acquire(rgb_tmp_len);
    if (!rgb_tmp) {
        printf("rgb tmp alloc fail\n");
        err = -ENOMEM;
        goto exit;
    }

#if USE_DMA2D_CONVERT
    if (yuyv2rgb16_dma2d(yuv_buf, rgb_tmp, dst_w, dst_h)) {
        printf("dma2d convert fail\n");
        err = -EFAULT;
        goto exit;
    }
#else
    video_dir_landscape_soft_uyvy_to_rgb16(yuv_buf, (u16 *)rgb_tmp, dst_w, dst_h);
#endif

    rotate_rgb565_clockwise((uint16_t *)img_buf, (const uint16_t *)rgb_tmp, dst_w, dst_h);

exit:
    if (err) {
        memset(img_buf, 0x00, dst_w * dst_h * 2);
    }
    if (frame_buf) {
        free(frame_buf);
        frame_buf = NULL;
    }
    return err;
}

static int video_dir_landscape_decode_to_buffer(const char *path, u16 width, u16 height, lv_img_dsc_t *dsc, u8 **buf)
{
    if (!path || !path[0] || !dsc || !buf) {
        return -1;
    }

    if (!*buf) {
        size_t size = (size_t)width * height * 2;
        *buf = malloc(size);
        if (!*buf) {
            printf("video_dir_landscape: alloc buf fail\n");
            return -1;
        }
        memset(*buf, 0, size);
    }

    bool locked = video_dir_landscape_pipeline_lock();
    int err = video_dir_landscape_jpeg2yuv_with_pipeline(path, *buf, width, height);
    s_landscape_pipeline_state = err ? PIPELINE_STOP : PIPELINE_IDLE;
    video_dir_landscape_pipeline_unlock(locked);

    if (err) {
        return -1;
    }

    dsc->header.always_zero = 0;
    dsc->header.cf = LV_IMG_CF_TRUE_COLOR;
    dsc->header.w = height;
    dsc->header.h = width;
    dsc->data_size = (uint32_t)width * height * 2;
    dsc->data = *buf;
    return 0;
}

static void video_dir_landscape_update_thumbnail_highlight_by_index(size_t active_index)
{
    if (active_index == SIZE_MAX) {
        printf("video_dir_landscape: thumbnail highlight cleared\n");
    } else {
        printf("video_dir_landscape: thumbnail highlight index=%u\n", (unsigned)active_index);
    }

    bool show_play_icon = false;
    const video_dir_landscape_media_entry_t *active_entry = NULL;
    if (active_index != SIZE_MAX && active_index < s_landscape_media_count) {
        active_entry = video_dir_landscape_media_get_entry(active_index);
        if (active_entry && active_entry->is_video) {
            show_play_icon = true;
        }
    }

    for (size_t i = 0; i < s_landscape_thumb_count; ++i) {
        video_dir_landscape_thumb_slot_t *slot = &s_landscape_thumbs[i];
        if (!slot->placeholder || !lv_obj_is_valid(slot->placeholder)) {
            continue;
        }

        bool active = (active_index != SIZE_MAX) && (slot->index == active_index) && (active_index < s_landscape_media_count);
        slot->active = active;

        if (active) {
            lv_obj_set_style_outline_color(slot->placeholder, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(slot->placeholder, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(slot->placeholder, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
        } else {
            lv_obj_set_style_outline_width(slot->placeholder, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(slot->placeholder, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }

    video_dir_landscape_set_play_icon_visible(show_play_icon);
}

static void video_dir_landscape_thumb_slots_clear(lv_obj_t *strip)
{
    video_dir_landscape_thumb_task_stop();

    for (size_t i = 0; i < VIDEO_DIR_LANDSCAPE_THUMB_MAX; ++i) {
        video_dir_landscape_thumb_slot_t *slot = &s_landscape_thumbs[i];
        if (slot->buf) {
            free(slot->buf);
        }
        if (slot->video_flag && lv_obj_is_valid(slot->video_flag)) {
            lv_obj_del(slot->video_flag);
        }
        if (slot->placeholder && lv_obj_is_valid(slot->placeholder)) {
            lv_img_set_src(slot->placeholder, NULL);
            lv_obj_set_style_bg_color(slot->placeholder, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(slot->placeholder, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(slot->placeholder, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(slot->placeholder, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(slot->placeholder, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(slot->placeholder, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        memset(slot, 0, sizeof(*slot));
        slot->index = SIZE_MAX;
    }

    s_landscape_thumb_count = 0;

    if (strip && lv_obj_is_valid(strip)) {
        while (lv_obj_remove_event_cb(strip, video_dir_landscape_thumb_lazy_load));
        lv_obj_clean(strip);
    }

    video_dir_landscape_update_thumbnail_highlight_by_index(SIZE_MAX);
}

static void video_dir_landscape_thumb_update_cb(int slot_ptr)
{
    video_dir_landscape_thumb_slot_t *slot = (video_dir_landscape_thumb_slot_t *)slot_ptr;
    if (!slot || !slot->placeholder || !lv_obj_is_valid(slot->placeholder)) {
        return;
    }

    lv_img_set_src(slot->placeholder, &slot->dsc);
    lv_obj_set_size(slot->placeholder, slot->dsc.header.w, slot->dsc.header.h);
    if (slot->video_flag && lv_obj_is_valid(slot->video_flag)) {
        lv_obj_align(slot->video_flag, LV_ALIGN_BOTTOM_LEFT, 4, -4);
        lv_obj_move_foreground(slot->video_flag);
    }
    lv_obj_invalidate(slot->placeholder);
}

static void video_dir_landscape_thumb_task_start(void)
{
    if (s_landscape_thumb_task_pid) {
        return;
    }

    thread_fork(VIDEO_DIR_LANDSCAPE_THUMB_TASK_NAME,
                VIDEO_DIR_LANDSCAPE_THUMB_THREAD_PRIO,
                VIDEO_DIR_LANDSCAPE_THUMB_STACK_SIZE,
                VIDEO_DIR_LANDSCAPE_THUMB_QUEUE_SIZE,
                &s_landscape_thumb_task_pid,
                video_dir_landscape_thumb_task,
                NULL);
}

static void video_dir_landscape_thumb_task_stop(void)
{
    if (!s_landscape_thumb_task_pid) {
        return;
    }

    int msg = 1;
    os_taskq_post_type(VIDEO_DIR_LANDSCAPE_THUMB_TASK_NAME, Q_USER, 1, &msg);
    thread_kill(&s_landscape_thumb_task_pid, KILL_WAIT);
    s_landscape_thumb_task_pid = 0;

    for (size_t i = 0; i < VIDEO_DIR_LANDSCAPE_THUMB_MAX; ++i) {
        s_landscape_thumbs[i].pending = false;
    }
}

static bool video_dir_landscape_thumb_task_pause(void)
{
    if (!s_landscape_thumb_task_pid) {
        return false;
    }

    video_dir_landscape_thumb_task_stop();
    return true;
}

static void video_dir_landscape_thumb_task_resume(bool resume_needed)
{
    if (!resume_needed) {
        return;
    }

    video_dir_landscape_thumb_task_start();
    video_dir_landscape_thumb_lazy_load(NULL);
}

static void video_dir_landscape_thumb_queue_request(video_dir_landscape_thumb_slot_t *slot, int remaining)
{
    if (!slot || !slot->buf) {
        return;
    }

    if (!slot->path[0]) {
        return;
    }

    if (slot->pending) {
        return;
    }

    int msg[2];
    msg[0] = (int)slot;
    msg[1] = remaining;

    if (os_taskq_post_type(VIDEO_DIR_LANDSCAPE_THUMB_TASK_NAME, Q_MSG, ARRAY_SIZE(msg), msg)) {
        return;
    }

    slot->pending = true;
    slot->ready = false;
}

static void video_dir_landscape_thumb_task(void *priv)
{
    (void)priv;
    int res;
    int msg[8];
    int kill_flag = 0;

    while (1) {
        res = os_task_pend("taskq", msg, ARRAY_SIZE(msg));

        if (res == OS_TASKQ) {
            switch (msg[0]) {
            case Q_MSG: {
                video_dir_landscape_thumb_slot_t *slot = (video_dir_landscape_thumb_slot_t *)msg[1];
                int remaining = msg[2];
                (void)remaining;
                const char *path = (slot ? slot->path : NULL);

                if (!slot) {
                    break;
                }

                if (!slot->buf || !path || !path[0]) {
                    slot->pending = false;
                    slot->ready = false;
                    break;
                }

                int err = video_dir_landscape_decode_to_buffer(path,
                                                                VIDEO_DIR_LANDSCAPE_THUMB_WIDTH,
                                                                VIDEO_DIR_LANDSCAPE_THUMB_HEIGHT,
                                                                &slot->dsc,
                                                                &slot->buf);
                slot->ready = (err == 0);
                slot->pending = false;

                if (!err) {
                    lvgl_rpc_post_func(video_dir_landscape_thumb_update_cb, 1, (int)slot);
                }
                break;
            }
            case Q_USER:
                kill_flag = msg[1];
                break;
            default:
                break;
            }
        }

        if (kill_flag) {
            break;
        }
    }

    bool lock = video_dir_landscape_pipeline_lock();
    video_dir_landscape_jpeg2yuv_pipeline_uninit();
    s_landscape_pipeline_state = PIPELINE_STOP;
    video_dir_landscape_pipeline_unlock(lock);
}

static void video_dir_landscape_thumb_lazy_load(lv_event_t *e)
{
    lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
    if (!ui_scr) {
        return;
    }

    lv_obj_t *strip = ui_scr->video_dir_landscape_mode_view_4;
    if (!strip || !lv_obj_is_valid(strip)) {
        return;
    }

    lv_coord_t view_y1 = lv_obj_get_scroll_y(strip);
    lv_coord_t view_h = lv_obj_get_height(strip);
    lv_coord_t view_y2 = view_y1 + view_h;

    lv_coord_t item_span = VIDEO_DIR_LANDSCAPE_THUMB_WIDTH + VIDEO_DIR_LANDSCAPE_THUMB_GAP;
    lv_coord_t preload_offset = item_span * VIDEO_DIR_LANDSCAPE_THUMB_PRELOAD_COUNT;
    lv_coord_t load_y1 = view_y1 - preload_offset;
    lv_coord_t load_y2 = view_y2 + preload_offset;

    for (size_t i = 0; i < s_landscape_thumb_count; ++i) {
        video_dir_landscape_thumb_slot_t *slot = &s_landscape_thumbs[i];
        if (!slot->placeholder || !lv_obj_is_valid(slot->placeholder)) {
            continue;
        }

        lv_coord_t ph_y1 = lv_obj_get_y(slot->placeholder);
        lv_coord_t ph_height = lv_obj_get_height(slot->placeholder);
        lv_coord_t ph_y2 = ph_y1 + ph_height;

        bool should_be_loaded = (ph_y1 < load_y2) && (ph_y2 > load_y1);

        if (should_be_loaded) {
            if (!slot->buf && !slot->pending) {
                printf("landscape lazy_load: slot %u in view, allocate buffer\n", (unsigned)i);
                size_t buf_size = VIDEO_DIR_LANDSCAPE_THUMB_WIDTH * VIDEO_DIR_LANDSCAPE_THUMB_HEIGHT * 2;
                slot->buf = malloc(buf_size);
                if (!slot->buf) {
                    printf("video_dir_landscape: thumb buffer alloc fail index=%u\n", (unsigned)i);
                    continue;
                }
                memset(slot->buf, 0, buf_size);

                slot->dsc.header.always_zero = 0;
                slot->dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
                slot->dsc.header.w = VIDEO_DIR_LANDSCAPE_THUMB_HEIGHT;
                slot->dsc.header.h = VIDEO_DIR_LANDSCAPE_THUMB_WIDTH;
                slot->dsc.data_size = buf_size;
                slot->dsc.data = slot->buf;

                video_dir_landscape_thumb_queue_request(slot, 0);
            } else if (slot->buf && !slot->ready && !slot->pending) {
                printf("landscape lazy_load: requeue slot %u\n", (unsigned)i);
                video_dir_landscape_thumb_queue_request(slot, 0);
            }
        } else {
            if (slot->buf && !slot->pending) {
                printf("landscape lazy_load: release slot %u\n", (unsigned)i);
                free(slot->buf);
                slot->buf = NULL;
                slot->ready = false;
                slot->dsc.data = NULL;
                slot->dsc.data_size = 0;
                lv_img_set_src(slot->placeholder, NULL);
                lv_obj_set_style_bg_color(slot->placeholder, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(slot->placeholder, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_invalidate(slot->placeholder);
            }
        }
    }
}

static int video_dir_landscape_show_preview_decode(const char *path, bool broadcast_dir)
{
    if (!path || !path[0]) {
        return -1;
    }

    if (storage_device_ready() == 0) {
        video_dec_post_msg("noCard", 1);
        return -1;
    }

    if (video_dir_landscape_decode_to_buffer(path,
                                             LATEST_PREVIEW_WIDTH,
                                             LATEST_PREVIEW_HEIGHT,
                                             &s_landscape_preview_dsc,
                                             &s_landscape_preview_buf)) {
        return -1;
    }

    lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
    if (!ui_scr) {
        return -1;
    }

    lv_obj_t *img = ui_scr->video_dir_landscape_mode_img_6;
    if (img && lv_obj_is_valid(img)) {
        lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
        lv_img_set_src(img, &s_landscape_preview_dsc);
        lv_img_set_angle(img, 0);
        lv_obj_set_size(img, s_landscape_preview_dsc.header.w, s_landscape_preview_dsc.header.h);
        lv_obj_set_pos(img, 0, 0);
        lv_obj_invalidate(img);
    }

    if (broadcast_dir) {
        char dir_buf[LATEST_PREVIEW_PATH_MAX] = {0};
        video_dir_landscape_extract_directory_from_path(path, dir_buf, sizeof(dir_buf));
        if (dir_buf[0]) {
            video_dir_landscape_send_directory_message(dir_buf);
        }
    }

    return 0;
}

static int video_dir_landscape_show_preview_from_path(const char *path, bool broadcast_dir)
{
    if (video_dir_landscape_show_preview_decode(path, broadcast_dir)) {
        return -1;
    }

    int index = video_dir_landscape_media_find_index_by_path(path);
    if (index >= 0) {
        video_dir_landscape_set_active_index((size_t)index);
    } else {
        strncpy(s_landscape_active_path, path, sizeof(s_landscape_active_path) - 1);
        s_landscape_active_path[sizeof(s_landscape_active_path) - 1] = '\0';
        s_landscape_active_valid = false;
        video_dir_landscape_update_thumbnail_highlight_by_index(SIZE_MAX);
    }

    return 0;
}

static int video_dir_landscape_show_preview_by_index(size_t index, bool broadcast_dir)
{
    const video_dir_landscape_media_entry_t *entry = video_dir_landscape_media_get_entry(index);
    if (!entry) {
        return -1;
    }

    if (video_dir_landscape_show_preview_decode(entry->path, broadcast_dir)) {
        return -1;
    }

    video_dir_landscape_set_active_index(index);
    return 0;
}

static void video_dir_landscape_thumb_event_handler(lv_event_t *e)
{
    if (!e) {
        return;
    }

    if (lv_event_get_code(e) != LV_EVENT_CLICKED) {
        return;
    }

    video_dir_landscape_thumb_slot_t *slot = (video_dir_landscape_thumb_slot_t *)lv_event_get_user_data(e);
    if (!slot) {
        return;
    }

    if (s_landscape_click_in_progress) {
        printf("video_dir_landscape: click ignored, operation in progress\n");
        return;
    }

    //video_dir_landscape_set_loading_visible(true);
    s_landscape_click_in_progress = true;
    if (lv_async_call(video_dir_landscape_process_thumb_click_async, slot) != LV_RES_OK) {
        printf("video_dir_landscape: async schedule failed\n");
        s_landscape_click_in_progress = false;
        //video_dir_landscape_set_loading_visible(false);
    }
}

static void video_dir_landscape_process_thumb_click_async(void *user_data)
{
    video_dir_landscape_thumb_slot_t *slot = (video_dir_landscape_thumb_slot_t *)user_data;
    bool handled = false;

    if (slot) {
        bool resume_needed = video_dir_landscape_thumb_task_pause();

        if (slot->index != SIZE_MAX && slot->index < s_landscape_media_count) {
            handled = (video_dir_landscape_show_preview_by_index(slot->index, true) == 0);
        }

        if (!handled && slot->path[0]) {
            handled = (video_dir_landscape_show_preview_from_path(slot->path, true) == 0);
        }

        if (!handled) {
            printf("video_dir_landscape: thumbnail click fallback failed index=%u path=%s\n", (unsigned)(slot ? slot->index : 0), slot ? slot->path : "<null>");
        }

        video_dir_landscape_thumb_task_resume(resume_needed);
    }

    //video_dir_landscape_set_loading_visible(false);
    s_landscape_click_in_progress = false;
}

static void video_dir_landscape_build_thumbnails(lv_ui_video_dir_landscape_mode *ui_scr)
{
    if (!ui_scr) {
        return;
    }

    lv_obj_t *strip = ui_scr->video_dir_landscape_mode_view_4;
    if (!strip || !lv_obj_is_valid(strip)) {
        return;
    }

    video_dir_landscape_thumb_slots_clear(strip);

    if (s_landscape_media_count == 0) {
        lv_obj_add_flag(strip, LV_OBJ_FLAG_HIDDEN);
        video_dir_landscape_update_thumbnail_highlight_by_index(SIZE_MAX);
        return;
    }
 
    lv_obj_clear_flag(strip, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(strip, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scroll_dir(strip, LV_DIR_VER);
    lv_coord_t strip_width = lv_obj_get_width(strip);
    lv_coord_t thumb_width = VIDEO_DIR_LANDSCAPE_THUMB_HEIGHT;
    lv_coord_t left_pad = 0;
    lv_coord_t right_pad = 0;

    if (strip_width > thumb_width) {
        lv_coord_t diff = strip_width - thumb_width;
        left_pad = diff / 2;
        right_pad = diff - left_pad;
    }

    lv_obj_set_style_pad_left(strip, left_pad, 0);
    lv_obj_set_style_pad_right(strip, right_pad, 0);
    lv_obj_set_style_pad_top(strip, VIDEO_DIR_LANDSCAPE_THUMB_PAD, 0);
    lv_obj_set_style_pad_bottom(strip, VIDEO_DIR_LANDSCAPE_THUMB_PAD, 0);
    lv_obj_set_style_pad_row(strip, VIDEO_DIR_LANDSCAPE_THUMB_GAP, 0);
    lv_obj_set_style_pad_column(strip, 0, 0);
    lv_obj_set_flex_flow(strip, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(strip, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

    size_t target = s_landscape_media_count < VIDEO_DIR_LANDSCAPE_THUMB_MAX ?
                    s_landscape_media_count : VIDEO_DIR_LANDSCAPE_THUMB_MAX;

    video_dir_landscape_thumb_task_start();

    for (size_t i = 0; i < target; ++i) {
        video_dir_landscape_thumb_slot_t *slot = &s_landscape_thumbs[i];
        const video_dir_landscape_media_entry_t *entry = video_dir_landscape_media_get_entry(i);

        if (!entry) {
            slot->index = SIZE_MAX;
            continue;
        }

        slot->index = i;
        strncpy(slot->path, entry->path, sizeof(slot->path) - 1);
        slot->path[sizeof(slot->path) - 1] = '\0';
        slot->pending = false;
        slot->ready = false;
        slot->active = false;
        slot->is_video = entry->is_video;

        slot->placeholder = lv_img_create(strip);
        if (!slot->placeholder) {
            printf("video_dir_landscape: placeholder create fail index=%u\n", (unsigned)i);
            slot->index = SIZE_MAX;
            continue;
        }

        lv_obj_set_size(slot->placeholder, VIDEO_DIR_LANDSCAPE_THUMB_HEIGHT, VIDEO_DIR_LANDSCAPE_THUMB_WIDTH);
        lv_obj_add_flag(slot->placeholder, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_radius(slot->placeholder, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(slot->placeholder, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(slot->placeholder, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(slot->placeholder, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(slot->placeholder, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_outline_width(slot->placeholder, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_outline_opa(slot->placeholder, LV_OPA_TRANSP, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_event_cb(slot->placeholder, video_dir_landscape_thumb_event_handler, LV_EVENT_CLICKED, slot);

        slot->video_flag = NULL;
        if (slot->is_video) {
            slot->video_flag = lv_img_create(slot->placeholder);
            if (slot->video_flag) {
                lv_img_set_src(slot->video_flag, gui_get_res_path(RES_VIDEO));
                lv_obj_add_flag(slot->video_flag, LV_OBJ_FLAG_IGNORE_LAYOUT);
                lv_obj_align(slot->video_flag, LV_ALIGN_BOTTOM_LEFT, 4, -4);
                lv_obj_move_foreground(slot->video_flag);
            }
        }
    }

    s_landscape_thumb_count = target;
    lv_obj_add_event_cb(strip, video_dir_landscape_thumb_lazy_load, LV_EVENT_SCROLL, NULL);
    lv_obj_update_layout(strip);

    if (s_landscape_active_valid) {
        video_dir_landscape_update_thumbnail_highlight_by_index(s_landscape_active_index);
    } else {
        video_dir_landscape_update_thumbnail_highlight_by_index(SIZE_MAX);
    }

    video_dir_landscape_thumb_lazy_load(NULL);
}

static size_t video_dir_landscape_collect_recent_media(video_dir_landscape_media_entry_t *entries, size_t max_entries)
{
    if (!entries || max_entries == 0) {
        return 0;
    }

    memset(entries, 0, sizeof(video_dir_landscape_media_entry_t) * max_entries);

    size_t count = 0;
    size_t inspected = 0;
    u8 printed_missing = 0;

    for (size_t i = 0; i < ARRAY_SIZE(s_video_dir_landscape_paths); ++i) {
        const char *scan_path = s_video_dir_landscape_paths[i];

        if (!scan_path || !scan_path[0]) {
            continue;
        }

        if (!fdir_exist(scan_path)) {
            if (!printed_missing) {
                printf("video_dir_landscape: gallery dir missing %s\n", scan_path);
                printed_missing = 1;
            }
            continue;
        }

        struct vfscan *fs = fscan(scan_path, LATEST_PREVIEW_SCAN_OPTS, 3);
        if (!fs) {
            printf("video_dir_landscape: scan %s fail\n", scan_path);
            continue;
        }

        printf("video_dir_landscape: scan %s success, file_number=%u\n", scan_path, fs->file_number);

        FILE *file = fselect(fs, FSEL_FIRST_FILE, 0);
        while (file) {
            char candidate_path[LATEST_PREVIEW_PATH_MAX] = {0};
            int ret = fget_path(file, fs, (u8 *)candidate_path, sizeof(candidate_path), 0);

            if (ret <= 0) {
                char name_buf[128] = {0};
                if (fget_name(file, name_buf, sizeof(name_buf)) > 0) {
                    size_t base_len = strlen(scan_path);
                    const char *sep = (base_len && (scan_path[base_len - 1] == '/' || scan_path[base_len - 1] == '\\')) ? "" : "/";
                    ret = snprintf(candidate_path, sizeof(candidate_path), "%s%s%s", scan_path, sep, name_buf);
                    if (ret >= (int)sizeof(candidate_path)) {
                        candidate_path[sizeof(candidate_path) - 1] = '\0';
                    }
                } else {
                    candidate_path[0] = '\0';
                }
            } else {
                size_t copy_len = (ret < (int)sizeof(candidate_path)) ? (size_t)ret : (sizeof(candidate_path) - 1);
                candidate_path[copy_len] = '\0';
            }

            fclose(file);

            size_t log_idx = inspected++;

            if (candidate_path[0]) {
                bool is_jpeg = video_dir_landscape_path_is_jpeg(candidate_path);
                bool is_video = video_dir_landscape_path_is_video(candidate_path);

                if (log_idx < 10) {
                    printf("video_dir_landscape: preview candidate[%u] %s is_jpeg=%d is_video=%d\n",
                           (unsigned)log_idx, candidate_path, is_jpeg, is_video);
                } else if (log_idx == 10) {
                    printf("video_dir_landscape: preview candidate logging truncated...\n");
                }

                if (is_jpeg || is_video) {
                    const char *candidate_name = strrchr(candidate_path, '/');
                    if (!candidate_name) {
                        candidate_name = strrchr(candidate_path, '\\');
                    }
                    candidate_name = candidate_name ? (candidate_name + 1) : candidate_path;

                    video_dir_landscape_media_entry_t candidate = {0};
                    strncpy(candidate.path, candidate_path, sizeof(candidate.path) - 1);
                    candidate.path[sizeof(candidate.path) - 1] = '\0';
                    strncpy(candidate.name, candidate_name, sizeof(candidate.name) - 1);
                    candidate.name[sizeof(candidate.name) - 1] = '\0';
                    video_dir_landscape_extract_directory_from_path(candidate.path, candidate.dir, sizeof(candidate.dir));
                    candidate.is_video = is_video;

                    if (!video_dir_landscape_media_has_valid_thumb(candidate.path, candidate.is_video)) {
                        continue;
                    }

                    size_t insert_pos = 0;
                    while (insert_pos < count) {
                        int cmp = strcmp(candidate.name, entries[insert_pos].name);
                        if (cmp > 0 || (cmp == 0 && strcmp(candidate.path, entries[insert_pos].path) > 0)) {
                            break;
                        }
                        insert_pos++;
                    }

                    if (count < max_entries) {
                        for (size_t move = count; move > insert_pos; --move) {
                            entries[move] = entries[move - 1];
                        }
                        entries[insert_pos] = candidate;
                        count++;
                    } else if (insert_pos < max_entries) {
                        for (size_t move = max_entries - 1; move > insert_pos; --move) {
                            entries[move] = entries[move - 1];
                        }
                        entries[insert_pos] = candidate;
                    }
                }
            } else {
                if (log_idx < 10) {
                    printf("video_dir_landscape: preview candidate[%u] missing path\n", (unsigned)log_idx);
                }
            }

            file = fselect(fs, FSEL_NEXT_FILE, 0);
        }

        fscan_release(fs);
    }

    return count;
}

int video_dir_landscape_play_active_video(void)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    printf("video_dir_landscape: play active video skipped in simulator\n");
    return -1;
#else
    if (!s_landscape_active_valid) {
        printf("video_dir_landscape: play skip, no active selection\n");
        return -1;
    }

    const video_dir_landscape_media_entry_t *entry = video_dir_landscape_media_get_entry(s_landscape_active_index);
    if (!entry) {
        printf("video_dir_landscape: play skip, entry missing index=%u\n", (unsigned)s_landscape_active_index);
        return -1;
    }

    if (!entry->is_video) {
        printf("video_dir_landscape: play skip, selection is not video\n");
        return -1;
    }

    if (storage_device_ready() == 0) {
        video_dec_post_msg("noCard", 1);
        return -1;
    }

    video_dir_landscape_thumb_task_pause();
    video_dir_landscape_jpeg2yuv_pipeline_uninit();
    s_landscape_pipeline_state = PIPELINE_EXIT;

    FILE *fd = fopen(entry->path, "r");
    if (!fd) {
        printf("video_dir_landscape: play open fail path=%s\n", entry->path);
        return -1;
    }

    extern int browser_open_file(void *p, char *path, char *name);
    browser_open_file(fd, (char *)entry->dir, (char *)entry->name);

    gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_PLAY);
    if (screen == NULL) {
        screen = gui_scr_create(GUI_SCREEN_VIDEO_PLAY,
                                "video_play",
                                guider_ui.video_play,
                                (gui_scr_setup_cb_t)setup_scr_video_play,
                                (gui_scr_unload_cb_t)unload_scr_video_play);
    }

    if (screen) {
        ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true, true, false);
    }

    return 0;
#endif
}

int video_dir_landscape_delete_active_media(void)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    return -1;
#else
    if (storage_device_ready() == 0) {
        video_dec_post_msg("noCard", 1);
        return -1;
    }

    if (!s_landscape_active_path[0]) {
        printf("video_dir_landscape: delete skip, no active selection\n");
        return -1;
    }

    video_dir_landscape_thumb_task_stop();

    char delete_path[LATEST_PREVIEW_PATH_MAX];
    strncpy(delete_path, s_landscape_active_path, sizeof(delete_path) - 1);
    delete_path[sizeof(delete_path) - 1] = '\0';

    int current_index = video_dir_landscape_media_find_index_by_path(delete_path);

    int err = fdelete_by_name(delete_path);
    if (err) {
        printf("video_dir_landscape: delete fail path=%s err=%d\n", delete_path, err);
        return -1;
    }

    lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
    if (!ui_scr) {
        s_landscape_active_path[0] = '\0';
        return 0;
    }

    video_dir_landscape_thumb_slots_clear(ui_scr->video_dir_landscape_mode_view_4);

    video_dir_landscape_media_entry_t *entries = malloc(sizeof(video_dir_landscape_media_entry_t) * VIDEO_DIR_LANDSCAPE_THUMB_MAX);
    if (!entries) {
        printf("video_dir_landscape: delete alloc fail\n");
        return -1;
    }

    size_t entry_count = video_dir_landscape_collect_recent_media(entries, VIDEO_DIR_LANDSCAPE_THUMB_MAX);

    if (video_dir_landscape_media_entries_set(entries, entry_count)) {
        free(entries);
        return -1;
    }

    free(entries);

    if (entry_count > 0) {
        size_t next_index = 0;
        if (current_index >= 0) {
            if ((size_t)current_index < entry_count) {
                next_index = (size_t)current_index;
            } else if (entry_count > 0) {
                next_index = entry_count - 1;
            }
        }

        if (video_dir_landscape_show_preview_by_index(next_index, true)) {
            const video_dir_landscape_media_entry_t *entry = video_dir_landscape_media_get_entry(next_index);
            if (entry) {
                if (video_dir_landscape_show_preview_from_path(entry->path, true)) {
                    printf("video_dir_landscape: failed to show preview after delete, path=%s\n", entry->path);
                }
            }
        }

        video_dir_landscape_build_thumbnails(ui_scr);
    } else {
        if (ui_scr->video_dir_landscape_mode_view_4 && lv_obj_is_valid(ui_scr->video_dir_landscape_mode_view_4)) {
            lv_obj_add_flag(ui_scr->video_dir_landscape_mode_view_4, LV_OBJ_FLAG_HIDDEN);
        }
        if (ui_scr->video_dir_landscape_mode_img_6 && lv_obj_is_valid(ui_scr->video_dir_landscape_mode_img_6)) {
            lv_img_set_src(ui_scr->video_dir_landscape_mode_img_6, NULL);
            lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_6, LV_OBJ_FLAG_HIDDEN);
        }
        video_dir_landscape_clear_active_selection();
        video_dir_landscape_update_thumbnail_highlight_by_index(SIZE_MAX);
    }

    return 0;
#endif
}

int video_dir_landscape_show_latest_preview(void)
{
    if (storage_device_ready() == 0) {
        video_dec_post_msg("noCard", 1);
        return -1;
    }

    lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
    if (!ui_scr) {
        return -1;
    }

    video_dir_landscape_thumb_slots_clear(ui_scr->video_dir_landscape_mode_view_4);

    video_dir_landscape_media_entry_t *entries = malloc(sizeof(video_dir_landscape_media_entry_t) * VIDEO_DIR_LANDSCAPE_THUMB_MAX);
    if (!entries) {
        printf("video_dir_landscape: failed to allocate media list\n");
        return -1;
    }

    size_t entry_count = video_dir_landscape_collect_recent_media(entries, VIDEO_DIR_LANDSCAPE_THUMB_MAX);
    if (entry_count == 0) {
        video_dec_post_msg("noFile", 1);
        if (ui_scr->video_dir_landscape_mode_view_4 && lv_obj_is_valid(ui_scr->video_dir_landscape_mode_view_4)) {
            lv_obj_add_flag(ui_scr->video_dir_landscape_mode_view_4, LV_OBJ_FLAG_HIDDEN);
        }
        if (ui_scr->video_dir_landscape_mode_img_6 && lv_obj_is_valid(ui_scr->video_dir_landscape_mode_img_6)) {
            lv_img_set_src(ui_scr->video_dir_landscape_mode_img_6, NULL);
            lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_6, LV_OBJ_FLAG_HIDDEN);
        }
        video_dir_landscape_media_entries_clear();
        free(entries);
        return -1;
    }

    if (video_dir_landscape_media_entries_set(entries, entry_count)) {
        free(entries);
        return -1;
    }

    free(entries);

    if (video_dir_landscape_show_preview_by_index(0, true)) {
        printf("video_dir_landscape: failed to show initial preview\n");
        video_dir_landscape_media_entries_clear();
        return -1;
    }

    video_dir_landscape_build_thumbnails(ui_scr);
    return 0;
}

const char *video_dir_landscape_get_active_path(void)
{
    if (!s_landscape_active_path[0]) {
        return NULL;
    }

    return s_landscape_active_path;
}

bool video_dir_landscape_active_is_image(void)
{
    if (!s_landscape_active_path[0]) {
        return false;
    }

    if (s_landscape_active_valid && s_landscape_active_index < s_landscape_media_count) {
        const video_dir_landscape_media_entry_t *entry = video_dir_landscape_media_get_entry(s_landscape_active_index);
        if (entry) {
            return !entry->is_video;
        }
    }

    return video_dir_landscape_path_is_jpeg(s_landscape_active_path);
}

const lv_img_dsc_t *video_dir_landscape_get_active_preview_dsc(void)
{
    if (!s_landscape_active_path[0]) {
        return NULL;
    }

    if (!s_landscape_preview_buf || !s_landscape_preview_dsc.data) {
        return NULL;
    }

    return &s_landscape_preview_dsc;
}

const lv_img_dsc_t *video_dir_landscape_get_active_thumbnail_dsc(void)
{
    if (!s_landscape_active_valid) {
        return NULL;
    }

    for (size_t i = 0; i < s_landscape_thumb_count; ++i) {
        video_dir_landscape_thumb_slot_t *slot = &s_landscape_thumbs[i];
        if (slot->index != s_landscape_active_index) {
            continue;
        }

        if (!slot->ready || !slot->dsc.data || slot->dsc.data_size == 0) {
            return NULL;
        }

        return &slot->dsc;
    }

    return NULL;
}

void video_dir_landscape_cleanup_on_exit(void)
{
    lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
    if (!ui_scr) {
        return;
    }

    video_dir_landscape_thumb_slots_clear(ui_scr->video_dir_landscape_mode_view_4);
}

int gui_scr_action_video_dir_landscape_mode_cb(int action)
{
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD: {
        lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
        if (!ui_scr) {
            return -1;
        }
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(ui_scr->video_dir_landscape_mode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(ui_scr->video_dir_landscape_mode, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        key_event_disable();
        app_mode_change_replace(APP_MODE_DEC);
        app_send_message(APP_MSG_DEC_MAIN, 0);
        key_event_enable();
        break;
    }
    case GUI_SCREEN_ACTION_UNLOAD:
        video_dir_landscape_cleanup_on_exit();
        break;
    default:
        break;
    }

    return 0;
}

REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE)
.onchange = gui_scr_action_video_dir_landscape_mode_cb,
};

#else

int video_dir_landscape_show_latest_preview(void)
{
    return -1;
}

const char *video_dir_landscape_get_active_path(void)
{
    return NULL;
}

bool video_dir_landscape_active_is_image(void)
{
    return false;
}

const lv_img_dsc_t *video_dir_landscape_get_active_preview_dsc(void)
{
    return NULL;
}

void video_dir_landscape_cleanup_on_exit(void)
{
    /* simulator build: nothing to clean */
}

#endif

#endif
