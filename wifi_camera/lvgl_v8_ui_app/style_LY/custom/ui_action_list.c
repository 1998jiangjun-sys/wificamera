#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
// #if !LV_USE_GUIBUILDER_SIMULATOR
// #include "app_config.h"
// #include "ui.h"
// #include "custom.h"
// #include <stdbool.h>
// #include <stddef.h>
// #include <stdint.h>
// #include "fs/fs.h"
// #include "video_dec_server.h"
// #include "video_dec.h"
// #include "asm/jpeg_codec.h"
// #include "asm/hwi.h"
// #include "system/includes.h"
// #include "fs/fs.h"
// #include "os/os_api.h"
// #include "video_ioctl.h"
// #include "video.h"
// #include "pipeline_core.h"
// #include "video/fb.h"
// #include "asm/jldma2d.h"
// // 动态展示部分
// #define interval_dir_x 210
// #define interval_dir_y 170

// #define PIPELINE_STOP       0
// #define PIPELINE_EXIT       1
// #define PIPELINE_RUNING     2
// #define PIPELINE_IDLE       3

// void video_dir_screen_load(void);
// void video_file_screen_load(void);
// int storage_device_available();
// void video_dir_cb_event_handler(lv_event_t *e);

// static void jpeg2yuv_pipeline_uninit(void);
// static int jpeg2yuv_pipeline_init(struct video_format *f);
// static int jpeg2yuv_with_pipeline(const char *path, u8 *img_buf, int dst_w, int dst_h);
// static u8 pipeline_state;
// static pipe_core_t *pipe_core;
// static OS_SEM sem;

// #define USE_DMA2D_CONVERT 1

// #define VIDEO_DIR_THUMB_TASK_NAME    "thumb_decode"
// #define VIDEO_DIR_THUMB_THREAD_PRIO  10
// #define VIDEO_DIR_THUMB_STACK_SIZE   1024
// #define VIDEO_DIR_THUMB_QUEUE_SIZE   512

// //公版800*480屏幕
// #define SCALE_FACTOR_W (LCD_W / 800.0)
// #define SCALE_FACTOR_H (LCD_H / 480.0)

// //公版800*480 图片资源尺寸
// // 文件页面
// #define IMG_CONT_W_BASE 192
// #define IMG_CONT_H_BASE 205
// #define IMG_CONT_COL_SPACE_BASE 20
// #define IMG_CONT_ROW_SPACE_BASE 10
// #define EXTRA_SPACE_BASE 30
// #define IMG_W_BASE 192
// #define IMG_H_BASE 160
// //文件夹页面
// #define VIDEO_FILE_IMG_W_BASE 32
// #define VIDEO_FILE_IMG_H_BASE 32
// #define DIR_CONT_W_BASE  192
// #define DIR_CONT_H_BASE  190
// #define DIR_IMG_W_BASE  160
// #define DIR_IMG_H_BASE  160
// #define CHECK_BOX_W_BASE 45
// #define CHECK_BOX_H_BASE 45
// #define LOCK_IMG_W_BASE 24
// #define LOCK_IMG_H_BASE 24



// // 默认使用基础值
// #define IMG_CONT_W IMG_CONT_W_BASE
// #define IMG_CONT_H IMG_CONT_H_BASE
// #define IMG_CONT_COL_SPACE IMG_CONT_COL_SPACE_BASE
// #define IMG_CONT_ROW_SPACE IMG_CONT_ROW_SPACE_BASE
// #define EXTRA_SPACE EXTRA_SPACE_BASE
// #define IMG_W IMG_W_BASE
// #define IMG_H IMG_H_BASE
// #define LOCK_IMG_W LOCK_IMG_W_BASE
// #define LOCK_IMG_H LOCK_IMG_H_BASE


// #define VIDEO_FILE_IMG_W VIDEO_FILE_IMG_W_BASE
// #define VIDEO_FILE_IMG_H VIDEO_FILE_IMG_H_BASE
// #define DIR_CONT_W DIR_CONT_W_BASE
// #define DIR_CONT_H DIR_CONT_H_BASE
// #define DIR_IMG_W DIR_IMG_W_BASE
// #define DIR_IMG_H DIR_IMG_H_BASE
// #define CHECK_BOX_W CHECK_BOX_W_BASE
// #define CHECK_BOX_H CHECK_BOX_H_BASE

// #define ONE_PAGE_MAX_NUM 60
// #define SCREEN_MAX_DISP_NUM 6
// #define IMG_BUF_NUM 9

// #if THREE_WAY_ENABLE

// #define ALIGN_16(x) (((x) + 15) & ~15)

// // 根据缩放系数重新定义
// #undef IMG_CONT_H
// #undef IMG_CONT_COL_SPACE
// #undef IMG_CONT_ROW_SPACE
// #undef EXTRA_SPACE
// #undef IMG_W
// #undef IMG_H

// #undef VIDEO_FILE_IMG_W
// #undef VIDEO_FILE_IMG_H
// #undef DIR_CONT_W
// #undef DIR_CONT_H
// #undef DIR_IMG_W
// #undef DIR_IMG_H
// #undef CHECK_BOX_W
// #undef CHECK_BOX_H
// #undef LOCK_IMG_W
// #undef LOCK_IMG_H

// #define IMG_CONT_W (IMG_CONT_W_BASE * SCALE_FACTOR_W)
// #define IMG_CONT_H (IMG_CONT_H_BASE * SCALE_FACTOR_H)
// #define IMG_CONT_COL_SPACE (IMG_CONT_COL_SPACE_BASE * SCALE_FACTOR_W)
// #define IMG_CONT_ROW_SPACE (IMG_CONT_ROW_SPACE_BASE * SCALE_FACTOR_H)
// #define EXTRA_SPACE (EXTRA_SPACE_BASE * SCALE_FACTOR_H)

// #define IMG_W ALIGN_16((int)(IMG_W_BASE * SCALE_FACTOR_W))
// #define IMG_H ALIGN_16((int)(IMG_H_BASE * SCALE_FACTOR_H))

// #define VIDEO_FILE_IMG_W (VIDEO_FILE_IMG_W_BASE * SCALE_FACTOR_W)
// #define VIDEO_FILE_IMG_H (VIDEO_FILE_IMG_H_BASE * SCALE_FACTOR_H)
// #define DIR_CONT_W (DIR_CONT_W_BASE * SCALE_FACTOR_W)
// #define DIR_CONT_H (DIR_CONT_H_BASE * SCALE_FACTOR_H)
// #define DIR_IMG_W (DIR_IMG_W_BASE * SCALE_FACTOR_W)
// #define DIR_IMG_H (DIR_IMG_H_BASE * SCALE_FACTOR_H)
// #define CHECK_BOX_W (CHECK_BOX_W_BASE * SCALE_FACTOR_W)
// #define CHECK_BOX_H (CHECK_BOX_H_BASE * SCALE_FACTOR_H)
// #define LOCK_IMG_W (LOCK_IMG_W_BASE * SCALE_FACTOR_W)
// #define LOCK_IMG_H (LOCK_IMG_H_BASE * SCALE_FACTOR_H)



// #endif

// #define FILE_DISP_REVERSE_ORDER 1
// #define DECODE_TASK_NAME "img_decode_task"
// static int task_pid;

// static void create_page(int page);
// static void update_img_text(int start_index, int end_index, u8 dir);
// static struct vfscan *fs_file = NULL;
// static int jpeg_decode_scale(const char *path, u8 *img_buf, u16 dst_w, u16 dst_h);
// static lv_img_dsc_t image_dsc_list[IMG_BUF_NUM];
// static u8 *img_buf_list[IMG_BUF_NUM];

// #define LATEST_PREVIEW_WIDTH 480
// #define LATEST_PREVIEW_HEIGHT 640
// #define LATEST_PREVIEW_PATH_MAX 512
// #define LATEST_PREVIEW_SCAN_OPTS "-tMOVJPGAVI -st -r"

// static const char *const latest_preview_paths[] = {
//     CONFIG_DEC_PATH_1,
//     CONFIG_DEC_PATH_2,
//     CONFIG_DEC_PATH_3,
//     CONFIG_DEC_PATH_4,
//     CONFIG_DEC_PATH_5,
// };

// static lv_img_dsc_t latest_preview_dsc;
// static u8 *latest_preview_buf;

// #define VIDEO_DIR_THUMB_WIDTH       80  // 缩略图宽度（像素）
// #define VIDEO_DIR_THUMB_HEIGHT      64  // 缩略图高度（像素）
// #define VIDEO_DIR_THUMB_MAX         1000  // 最大缩略图数量
// #define VIDEO_DIR_THUMB_PAD         15  // 缩略图容器内边距
// #define VIDEO_DIR_THUMB_GAP         15  // 缩略图间距
// #define VIDEO_DIR_THUMB_PRELOAD_COUNT 6   // 预加载数量

// typedef struct {
//     char path[LATEST_PREVIEW_PATH_MAX];
//     char dir[LATEST_PREVIEW_PATH_MAX];
//     char name[128];
// } video_dir_media_entry_t;

// typedef struct {
//     lv_obj_t *placeholder;
//     lv_img_dsc_t dsc;
//     u8 *buf;
//     char path[LATEST_PREVIEW_PATH_MAX];
//     size_t index;
//     bool pending;
//     bool ready;
//     bool active;
// } video_dir_thumb_slot_t;

// static video_dir_thumb_slot_t s_video_dir_thumbs[VIDEO_DIR_THUMB_MAX];
// static size_t s_video_dir_thumb_count;
// static char s_video_dir_active_path[LATEST_PREVIEW_PATH_MAX];
// static int s_video_dir_thumb_task_pid;
// static OS_MUTEX s_video_dir_pipeline_mutex;
// static bool s_video_dir_pipeline_mutex_ready;
// static video_dir_media_entry_t *s_video_dir_media_entries;
// static size_t s_video_dir_media_count;
// static size_t s_video_dir_active_index;
// static bool s_video_dir_active_valid;

// static void video_dir_thumb_task(void *priv);
// static void video_dir_thumb_task_start(void);
// static void video_dir_thumb_task_stop(void);
// static bool video_dir_thumb_task_pause(void);
// static void video_dir_thumb_task_resume(bool resume_needed);
// static void video_dir_thumb_queue_request(video_dir_thumb_slot_t *slot, int remaining);
// static void video_dir_thumb_update_cb(int slot_ptr);
// static bool video_dir_pipeline_lock(void);
// static void video_dir_pipeline_unlock(bool locked);
// static void video_dir_media_entries_clear(void);
// static int video_dir_media_entries_set(const video_dir_media_entry_t *entries, size_t count);
// static const video_dir_media_entry_t *video_dir_media_get_entry(size_t index);
// static int video_dir_media_find_index_by_path(const char *path);
// static void video_dir_set_active_index(size_t index);
// static void video_dir_clear_active_selection(void);
// static int video_dir_show_preview_by_index(size_t index, bool broadcast_dir);
// static void video_dir_update_thumbnail_highlight_by_index(size_t active_index);
// static void video_dir_update_counter_label_for_index(size_t index);
// static void video_dir_update_counter_label_active(void);

// static char video_dir_ascii_toupper(char ch)
// {
//     if ((ch >= 'a') && (ch <= 'z')) {
//         return ch - ('a' - 'A');
//     }
//     return ch;
// }

// static int video_dir_path_is_jpeg(const char *path)
// {
//     if (!path) {
//         return 0;
//     }

//     const char *ext = strrchr(path, '.');
//     if (!ext || !ext[1]) {
//         return 0;
//     }

//     ext += 1;
//     size_t ext_len = strlen(ext);

//     if (ext_len == 3) {
//         return (video_dir_ascii_toupper(ext[0]) == 'J') &&
//                (video_dir_ascii_toupper(ext[1]) == 'P') &&
//                (video_dir_ascii_toupper(ext[2]) == 'G');
//     }

//     if (ext_len == 4) {
//         return (video_dir_ascii_toupper(ext[0]) == 'J') &&
//                (video_dir_ascii_toupper(ext[1]) == 'P') &&
//                (video_dir_ascii_toupper(ext[2]) == 'E') &&
//                (video_dir_ascii_toupper(ext[3]) == 'G');
//     }

//     return 0;
// }

// static bool video_dir_pipeline_lock(void)
// {
//     if (!s_video_dir_pipeline_mutex_ready) {
//         if (os_mutex_create(&s_video_dir_pipeline_mutex)) {
//             printf("video_dir: mutex create fail\n");
//             return false;
//         }
//         s_video_dir_pipeline_mutex_ready = true;
//     }

//     os_mutex_pend(&s_video_dir_pipeline_mutex, 0);
//     return true;
// }

// static void video_dir_pipeline_unlock(bool locked)
// {
//     if (locked && s_video_dir_pipeline_mutex_ready) {
//         os_mutex_post(&s_video_dir_pipeline_mutex);
//     }
// }

// static void video_dir_clear_active_selection(void)
// {
//     s_video_dir_active_valid = false;
//     s_video_dir_active_index = 0;
//     s_video_dir_active_path[0] = '\0';
// }

// static void video_dir_media_entries_clear(void)
// {
//     if (s_video_dir_media_entries) {
//         free(s_video_dir_media_entries);
//         s_video_dir_media_entries = NULL;
//     }
//     s_video_dir_media_count = 0;
//     video_dir_clear_active_selection();
// }

// static int video_dir_media_entries_set(const video_dir_media_entry_t *entries, size_t count)
// {
//     video_dir_media_entries_clear();

//     if (!entries || !count) {
//         return 0;
//     }

//     size_t alloc_len = count * sizeof(video_dir_media_entry_t);
//     video_dir_media_entry_t *copy = malloc(alloc_len);
//     if (!copy) {
//         printf("video_dir: media entries alloc fail count=%u\n", (unsigned)count);
//         return -1;
//     }

//     memcpy(copy, entries, alloc_len);
//     s_video_dir_media_entries = copy;
//     s_video_dir_media_count = count;
//     return 0;
// }

// static const video_dir_media_entry_t *video_dir_media_get_entry(size_t index)
// {
//     if (!s_video_dir_media_entries || index >= s_video_dir_media_count) {
//         return NULL;
//     }
//     return &s_video_dir_media_entries[index];
// }

// static int video_dir_media_find_index_by_path(const char *path)
// {
//     if (!path || !s_video_dir_media_entries) {
//         return -1;
//     }

//     for (size_t i = 0; i < s_video_dir_media_count; ++i) {
//         if (strcmp(s_video_dir_media_entries[i].path, path) == 0) {
//             return (int)i;
//         }
//     }

//     return -1;
// }

// static void video_dir_set_active_index(size_t index)
// {
//     if (!s_video_dir_media_entries || index >= s_video_dir_media_count) {
//         video_dir_clear_active_selection();
//         video_dir_update_thumbnail_highlight_by_index(SIZE_MAX);
//         video_dir_update_counter_label_active();
//         return;
//     }

//     s_video_dir_active_index = index;
//     s_video_dir_active_valid = true;

//     const video_dir_media_entry_t *entry = &s_video_dir_media_entries[index];
//     strncpy(s_video_dir_active_path, entry->path, sizeof(s_video_dir_active_path) - 1);
//     s_video_dir_active_path[sizeof(s_video_dir_active_path) - 1] = '\0';

//     video_dir_update_thumbnail_highlight_by_index(index);
//     video_dir_update_counter_label_for_index(index);
// }

// static u32 cur_page = 1;
// static u32 total_file_num = 0;
// static u32 total_file_page = 0;
// static u32 to_play_video_page = 0;
// static int cur_scroll_val = 0;
// static int create_num;
// static u32 line;
// static u32 last_line;
// static char *dir_path;
// u8 deleting_flag = 0;

// static void send_msg2file_num(void)
// {
//     char *num = lvgl_module_msg_get_ptr(GUI_MODEL_MSG_ID_FILE_NUM, 24);
//     int cur_file = line * 3 + (cur_page - 1) * ONE_PAGE_MAX_NUM + SCREEN_MAX_DISP_NUM;
//     cur_file = cur_file < total_file_num ? cur_file : total_file_num;
//     sprintf(num, "%d\n/\n%d", cur_file, total_file_num);
//     lvgl_module_msg_send_ptr(num, 0);
// }

// static int ensure_latest_preview_buffer(void)
// {
//     if (latest_preview_buf) {
//         return 0;
//     }

//     latest_preview_buf = malloc(LATEST_PREVIEW_WIDTH * LATEST_PREVIEW_HEIGHT * 2);
//     if (!latest_preview_buf) {
//         printf("video_dir: alloc preview buf fail\n");
//         return -1;
//     }

//     memset(latest_preview_buf, 0, LATEST_PREVIEW_WIDTH * LATEST_PREVIEW_HEIGHT * 2);
//     latest_preview_dsc.header.always_zero = 0;
//     latest_preview_dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
//     latest_preview_dsc.header.w = LATEST_PREVIEW_WIDTH;
//     latest_preview_dsc.header.h = LATEST_PREVIEW_HEIGHT;
//     latest_preview_dsc.data_size = LATEST_PREVIEW_WIDTH * LATEST_PREVIEW_HEIGHT * 2;
//     latest_preview_dsc.data = latest_preview_buf;
//     return 0;
// }

// // static void video_dir_hide_folder_widgets(lv_ui_video_dir *ui_scr)
// // {
// //     if (!ui_scr) {
// //         return;
// //     }

// //     if (lv_obj_is_valid(ui_scr->video_dir_view_1)) {
// //         lv_obj_add_flag(ui_scr->video_dir_view_1, LV_OBJ_FLAG_HIDDEN);
// //     }

// //     // if (lv_obj_is_valid(ui_scr->video_dir_lbl_path)) {
// //     //     lv_obj_add_flag(ui_scr->video_dir_lbl_path, LV_OBJ_FLAG_HIDDEN);
// //     // }
// // }

// static void video_dir_extract_directory_from_path(const char *path, char *dir_buf, size_t dir_len)
// {
//     if (!dir_buf || dir_len == 0) {
//         return;
//     }

//     dir_buf[0] = '\0';

//     if (!path || !path[0]) {
//         return;
//     }

//     strncpy(dir_buf, path, dir_len - 1);
//     dir_buf[dir_len - 1] = '\0';

//     char *slash = strrchr(dir_buf, '/');
//     char *bslash = strrchr(dir_buf, '\\');
//     char *sep = slash;
//     if (!sep || (bslash && bslash > sep)) {
//         sep = bslash;
//     }
//     if (sep) {
//         *(sep + 1) = '\0';
//     } else {
//         dir_buf[0] = '\0';
//     }
// }

// static void video_dir_send_directory_message(const char *dir)
// {
//     if (!dir || !dir[0]) {
//         return;
//     }

//     size_t dir_len = strlen(dir) + 1;
//     char *dir_msg = lvgl_module_msg_get_ptr(GUI_MODEL_MSG_ID_FILE_PATH, dir_len);
//     if (dir_msg) {
//         memcpy(dir_msg, dir, dir_len);
//         lvgl_module_msg_send_ptr(dir_msg, 0);
//     }
// }

// static size_t video_dir_collect_recent_media(video_dir_media_entry_t *entries, size_t max_entries)
// {
//     if (!entries || max_entries == 0) {
//         return 0;
//     }

//     memset(entries, 0, sizeof(video_dir_media_entry_t) * max_entries);

//     size_t count = 0;
//     size_t inspected = 0;
//     u8 printed_missing = 0;

//     for (size_t i = 0; i < ARRAY_SIZE(latest_preview_paths); ++i) {
//         const char *scan_path = latest_preview_paths[i];

//         if (!scan_path || !scan_path[0]) {
//             continue;
//         }

//         if (!fdir_exist(scan_path)) {
//             if (!printed_missing) {
//                 printf("video_dir: gallery dir missing %s\n", scan_path);
//                 printed_missing = 1;
//             }
//             continue;
//         }

//         struct vfscan *fs = fscan(scan_path, LATEST_PREVIEW_SCAN_OPTS, 3);
//         if (!fs) {
//             printf("video_dir: scan %s fail\n", scan_path);
//             continue;
//         }

//         printf("video_dir: scan %s success, file_number=%u\n", scan_path, fs->file_number);

//         FILE *file = fselect(fs, FSEL_FIRST_FILE, 0);
//         while (file) {
//             char candidate_path[LATEST_PREVIEW_PATH_MAX] = {0};
//             int ret = fget_path(file, fs, (u8 *)candidate_path, sizeof(candidate_path), 0);

//             if (ret <= 0) {
//                 char name_buf[128] = {0};
//                 if (fget_name(file, name_buf, sizeof(name_buf)) > 0) {
//                     size_t base_len = strlen(scan_path);
//                     const char *sep = (base_len && (scan_path[base_len - 1] == '/' || scan_path[base_len - 1] == '\\')) ? "" : "/";
//                     ret = snprintf(candidate_path, sizeof(candidate_path), "%s%s%s", scan_path, sep, name_buf);
//                     if (ret >= (int)sizeof(candidate_path)) {
//                         candidate_path[sizeof(candidate_path) - 1] = '\0';
//                     }
//                 } else {
//                     candidate_path[0] = '\0';
//                 }
//             } else {
//                 size_t copy_len = (ret < (int)sizeof(candidate_path)) ? (size_t)ret : (sizeof(candidate_path) - 1);
//                 candidate_path[copy_len] = '\0';
//             }

//             fclose(file);

//             size_t log_idx = inspected++;

//             if (candidate_path[0]) {
//                 int is_jpeg = video_dir_path_is_jpeg(candidate_path);

//                 if (log_idx < 10) {
//                     printf("video_dir: preview candidate[%u] %s is_jpeg=%d\n", (unsigned)log_idx, candidate_path, is_jpeg);
//                 } else if (log_idx == 10) {
//                     printf("video_dir: preview candidate logging truncated...\n");
//                 }

//                 if (is_jpeg) {
//                     const char *candidate_name = strrchr(candidate_path, '/');
//                     if (!candidate_name) {
//                         candidate_name = strrchr(candidate_path, '\\');
//                     }
//                     candidate_name = candidate_name ? (candidate_name + 1) : candidate_path;

//                     video_dir_media_entry_t candidate = {0};
//                     strncpy(candidate.path, candidate_path, sizeof(candidate.path) - 1);
//                     candidate.path[sizeof(candidate.path) - 1] = '\0';
//                     strncpy(candidate.name, candidate_name, sizeof(candidate.name) - 1);
//                     candidate.name[sizeof(candidate.name) - 1] = '\0';
//                     video_dir_extract_directory_from_path(candidate.path, candidate.dir, sizeof(candidate.dir));

//                     size_t insert_pos = 0;
//                     while (insert_pos < count) {
//                         int cmp = strcmp(candidate.name, entries[insert_pos].name);
//                         if (cmp > 0 || (cmp == 0 && strcmp(candidate.path, entries[insert_pos].path) > 0)) {
//                             break;
//                         }
//                         insert_pos++;
//                     }

//                     if (count < max_entries) {
//                         for (size_t move = count; move > insert_pos; --move) {
//                             entries[move] = entries[move - 1];
//                         }
//                         entries[insert_pos] = candidate;
//                         count++;
//                     } else if (insert_pos < max_entries) {
//                         for (size_t move = max_entries - 1; move > insert_pos; --move) {
//                             entries[move] = entries[move - 1];
//                         }
//                         entries[insert_pos] = candidate;
//                     }
//                 }
//             } else {
//                 if (log_idx < 10) {
//                     printf("video_dir: preview candidate[%u] missing path\n", (unsigned)log_idx);
//                 }
//             }

//             file = fselect(fs, FSEL_NEXT_FILE, 0);
//         }

//         fscan_release(fs);
//     }

//     return count;
// }

// static int video_dir_decode_to_buffer(const char *path, u16 width, u16 height, u8 *buf)
// {
//     if (!path || !buf) {
//         return -1;
//     }

//     uintptr_t addr = (uintptr_t)path;
//     if (addr < 0x1000) {
//         printf("video_dir: decode skip invalid path addr=0x%x\n", (unsigned)addr);
//         return -1;
//     }

//     if (!path[0]) {
//         return -1;
//     }

//     bool locked = video_dir_pipeline_lock();
//     int err = jpeg2yuv_with_pipeline(path, buf, width, height);
//     pipeline_state = err ? PIPELINE_STOP : PIPELINE_IDLE;
//     video_dir_pipeline_unlock(locked);
//     return err;
// }

// static void video_dir_thumb_lazy_load(lv_event_t *e);

// static void video_dir_thumb_update_cb(int slot_ptr)
// {
//     video_dir_thumb_slot_t *slot = (video_dir_thumb_slot_t *)slot_ptr;
//     if (!slot || !slot->placeholder || !lv_obj_is_valid(slot->placeholder)) {
//         return;
//     }

//     lv_img_set_src(slot->placeholder, &slot->dsc);
//     lv_obj_invalidate(slot->placeholder);
// }

// static void video_dir_thumb_task_start(void)
// {
//     if (s_video_dir_thumb_task_pid) {
//         return;
//     }

//     thread_fork(VIDEO_DIR_THUMB_TASK_NAME,
//                 VIDEO_DIR_THUMB_THREAD_PRIO,
//                 VIDEO_DIR_THUMB_STACK_SIZE,
//                 VIDEO_DIR_THUMB_QUEUE_SIZE,
//                 &s_video_dir_thumb_task_pid,
//                 video_dir_thumb_task,
//                 NULL);
// }

// static void video_dir_thumb_task_stop(void)
// {
// 			printf("------>%s()----->%d\n", __func__, __LINE__);

//     if (!s_video_dir_thumb_task_pid) {
//         return;
//     }
// 			printf("------>%s()----->%d\n", __func__, __LINE__);


//     int msg = 1;
//     os_taskq_post_type(VIDEO_DIR_THUMB_TASK_NAME, Q_USER, 1, &msg);
//     thread_kill(&s_video_dir_thumb_task_pid, KILL_WAIT);
//     s_video_dir_thumb_task_pid = 0;
// 			printf("------>%s()----->%d\n", __func__, __LINE__);

//     for (size_t i = 0; i < ARRAY_SIZE(s_video_dir_thumbs); ++i) {
//         s_video_dir_thumbs[i].pending = false;
//     }
// }

// static bool video_dir_thumb_task_pause(void)
// {
//     if (!s_video_dir_thumb_task_pid) {
//         return false;
//     }

//     video_dir_thumb_task_stop();
//     return true;
// }

// static void video_dir_thumb_task_resume(bool resume_needed)
// {
//     if (!resume_needed) {
//         return;
//     }

//     video_dir_thumb_task_start();
//     video_dir_thumb_lazy_load(NULL);
// }

// static void video_dir_thumb_queue_request(video_dir_thumb_slot_t *slot, int remaining)
// {
//     if (!slot || !slot->buf) {
//         return;
//     }

//     if (!slot->path[0]) {
//         return;
//     }

//     if (slot->pending) {
//         return;
//     }

//     int msg[2];
//     msg[0] = (int)slot;
//     msg[1] = remaining;

//     int err = os_taskq_post_type(VIDEO_DIR_THUMB_TASK_NAME, Q_MSG, ARRAY_SIZE(msg), msg);
//     if (err) {
//         return;
//     }

//     slot->pending = true;
//     slot->ready = false;
// }

// static void video_dir_thumb_task(void *priv)
// {
//     (void)priv;
//     int res;
//     int msg[8];
//     int kill_flag = 0;
//     bool pipeline_ready = false;

//     while (1) {
//         res = os_task_pend("taskq", msg, ARRAY_SIZE(msg));

//         if (res == OS_TASKQ) {
//             switch (msg[0]) {
//             case Q_MSG: {
//                 video_dir_thumb_slot_t *slot = (video_dir_thumb_slot_t *)msg[1];
//                 int remaining = msg[2];
//                 const char *path = (slot ? slot->path : NULL);

//                 if (!slot) {
//                     break;
//                 }

//                 if (!slot->buf || !path || !path[0]) {
//                     slot->pending = false;
//                     slot->ready = false;
//                     break;
//                 }

//                 if (!pipeline_ready || pipeline_state == PIPELINE_STOP) {
//                     pipeline_state = PIPELINE_STOP;
//                     pipeline_ready = true;
//                 }

//                 int err = video_dir_decode_to_buffer(path, VIDEO_DIR_THUMB_WIDTH, VIDEO_DIR_THUMB_HEIGHT, slot->buf);
//                 slot->ready = (err == 0);
//                 slot->pending = false;

//                 if (!err) {
//                     lvgl_rpc_post_func(video_dir_thumb_update_cb, 1, (int)slot);
//                 }

//                 if (!err && remaining == 0) {
//                     bool lock = video_dir_pipeline_lock();
//                     jpeg2yuv_pipeline_uninit();
//                     pipeline_state = PIPELINE_STOP;
//                     video_dir_pipeline_unlock(lock);
//                     pipeline_ready = false;
//                 }
//                 break;
//             }
//             case Q_USER:
//                 kill_flag = msg[1];
//                 break;
//             default:
//                 break;
//             }
//         }

//         if (kill_flag) {
//             break;
//         }
//     }

//     if (pipeline_ready) {
//         jpeg2yuv_pipeline_uninit();
//         pipeline_state = PIPELINE_STOP;
//     }
// }

// static void video_dir_update_counter_label(size_t total, size_t current_index)
// {
//     // lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
//     // if (!ui_scr || !lv_obj_is_valid(ui_scr->video_dir_lbl_6)) {
//     //     return;
//     // }

//     // lv_obj_clear_flag(ui_scr->video_dir_lbl_6, LV_OBJ_FLAG_HIDDEN);

//     // char counter_text[32];
//     // if (total == 0) {
//     //     snprintf(counter_text, sizeof(counter_text), "0/0");
//     //     lv_label_set_text(ui_scr->video_dir_lbl_6, counter_text);
//     //     return;
//     // }

//     // if (current_index >= total) {
//     //     current_index = total - 1;
//     // }

//     // unsigned int position = (unsigned int)(current_index + 1);
//     // unsigned int total_count = (unsigned int)total;
//     // snprintf(counter_text, sizeof(counter_text), "%u/%u", position, total_count);
//     // lv_label_set_text(ui_scr->video_dir_lbl_6, counter_text);
// }

// static void video_dir_update_counter_label_for_index(size_t index)
// {
//     size_t total = s_video_dir_media_count;
//     if (total == 0) {
//         video_dir_update_counter_label(0, 0);
//         return;
//     }

//     if (index >= total) {
//         index = total - 1;
//     }

//     video_dir_update_counter_label(total, index);
// }

// static void video_dir_update_counter_label_active(void)
// {
//     if (s_video_dir_active_valid) {
//         video_dir_update_counter_label_for_index(s_video_dir_active_index);
//     } else if (s_video_dir_media_count > 0) {
//         video_dir_update_counter_label(s_video_dir_media_count, 0);
//     } else {
//         video_dir_update_counter_label(0, 0);
//     }
// }

// static void video_dir_thumb_slots_clear(lv_obj_t *strip)
// {
//     video_dir_thumb_task_stop();

//     for (size_t i = 0; i < VIDEO_DIR_THUMB_MAX; ++i) {
//         if (s_video_dir_thumbs[i].buf) {
//             printf("video_dir: freeing thumb buffer for slot %d\n", i);
//             free(s_video_dir_thumbs[i].buf);
//         }
//         memset(&s_video_dir_thumbs[i], 0, sizeof(s_video_dir_thumbs[i]));
//         s_video_dir_thumbs[i].index = SIZE_MAX;
//     }
//     s_video_dir_thumb_count = 0;

//     video_dir_update_counter_label(0, 0);

//     if (strip && lv_obj_is_valid(strip)) {
//         lv_obj_clean(strip);
//     }
// }

// static void video_dir_update_thumbnail_highlight_by_index(size_t active_index)
// {
//     if (active_index == SIZE_MAX) {
//         printf("video_dir: updating thumbnail highlight, active index: none\n");
//     } else {
//         printf("video_dir: updating thumbnail highlight, active index: %u\n", (unsigned)active_index);
//     }
//     for (size_t i = 0; i < s_video_dir_thumb_count; ++i) {
//         video_dir_thumb_slot_t *slot = &s_video_dir_thumbs[i];
//         if (!slot->placeholder || !lv_obj_is_valid(slot->placeholder)) {
//             continue;
//         }

//         bool active = (active_index != SIZE_MAX) && (slot->index == active_index) && (active_index < s_video_dir_media_count);
//         slot->active = active;
//         if (active) {
//             printf("video_dir: highlighting slot %d\n", i);
//             lv_obj_set_style_outline_color(slot->placeholder, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//             lv_obj_set_style_outline_width(slot->placeholder, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
//             lv_obj_set_style_outline_opa(slot->placeholder, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//         } else {
//             lv_obj_set_style_outline_width(slot->placeholder, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//             lv_obj_set_style_outline_opa(slot->placeholder, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         }
//     }
// }

// static int video_dir_show_preview_from_path(const char *path, bool broadcast_dir);
// static void video_dir_thumbnail_event_handler(lv_event_t *e);

// // static void video_dir_build_thumbnail_strip(lv_ui_video_dir *ui_scr, size_t active_index)
// // {
// //     size_t count = s_video_dir_media_count;
// //     const video_dir_media_entry_t *entries = s_video_dir_media_entries;
// //     printf("video_dir: building thumbnail strip, count=%u, active_index=%u\n", (unsigned)count, (unsigned)active_index);
// //     if (!ui_scr) {
// //         return;
// //     }

// //     lv_obj_t *strip = ui_scr->video_dir_view_4;
// //     if (!lv_obj_is_valid(strip)) {
// //         return;
// //     }

// //     video_dir_thumb_slots_clear(strip);

// //     if (!entries || count == 0) {
// //         lv_obj_add_flag(strip, LV_OBJ_FLAG_HIDDEN);
// //         video_dir_thumb_task_stop();
// //         video_dir_update_counter_label_active();
// //         video_dir_update_thumbnail_highlight_by_index(SIZE_MAX);
// //         return;
// //     }

// //     lv_obj_clear_flag(strip, LV_OBJ_FLAG_HIDDEN);
// //     lv_obj_add_flag(strip, LV_OBJ_FLAG_SCROLLABLE);
// //     lv_obj_set_scroll_dir(strip, LV_DIR_HOR);
// //     lv_obj_clear_flag(strip, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
// //     lv_obj_set_style_pad_all(strip, VIDEO_DIR_THUMB_PAD, 0);
// //     lv_obj_set_style_pad_row(strip, 0, 0);
// //     lv_obj_set_style_pad_column(strip, VIDEO_DIR_THUMB_GAP, 0);
// //     lv_obj_set_flex_flow(strip, LV_FLEX_FLOW_ROW);
// //     lv_obj_set_flex_align(strip, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
// //     lv_obj_add_event_cb(strip, video_dir_thumb_lazy_load, LV_EVENT_SCROLL, NULL);

// //     size_t target = count < VIDEO_DIR_THUMB_MAX ? count : VIDEO_DIR_THUMB_MAX;

// //     video_dir_thumb_task_start();

// //     for (size_t i = 0; i < target; ++i) {
// //         video_dir_thumb_slot_t *slot = &s_video_dir_thumbs[i];
// //         const video_dir_media_entry_t *entry = &entries[i];

// //         slot->index = i;
// //         strncpy(slot->path, entry->path, sizeof(slot->path) - 1);
// //         slot->path[sizeof(slot->path) - 1] = '\0';

// //         slot->placeholder = lv_img_create(strip);
// //         if (!slot->placeholder) {
// //             printf("video_dir: placeholder create fail index=%u\n", (unsigned)i);
// //             slot->index = SIZE_MAX;
// //             continue;
// //         }

// //         lv_obj_set_size(slot->placeholder, VIDEO_DIR_THUMB_WIDTH, VIDEO_DIR_THUMB_HEIGHT);
// //         lv_obj_add_flag(slot->placeholder, LV_OBJ_FLAG_CLICKABLE);
// //         lv_obj_set_style_radius(slot->placeholder, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
// //         lv_obj_set_style_bg_color(slot->placeholder, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN | LV_STATE_DEFAULT);
// //         lv_obj_set_style_bg_opa(slot->placeholder, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
// //         lv_obj_add_event_cb(slot->placeholder, video_dir_thumbnail_event_handler, LV_EVENT_ALL, slot);
// //     }

// //     s_video_dir_thumb_count = target;

// //     if (s_video_dir_thumb_count == 0) {
// //         lv_obj_add_flag(strip, LV_OBJ_FLAG_HIDDEN);
// //         video_dir_thumb_task_stop();
// //         video_dir_update_thumbnail_highlight_by_index(SIZE_MAX);
// //         video_dir_update_counter_label_active();
// //         return;
// //     }

// //     video_dir_update_thumbnail_highlight_by_index(s_video_dir_active_valid ? s_video_dir_active_index : SIZE_MAX);
// //     video_dir_update_counter_label_active();
// //     lv_obj_update_layout(strip);

// //     // Manually trigger lazy load for the initial view
// //     video_dir_thumb_lazy_load(NULL);
// // }

// static void video_dir_thumb_lazy_load(lv_event_t *e)
// {
// //     lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
// //     if (!ui_scr) {
// //         return;
// //     }
// //     lv_obj_t *strip = ui_scr->video_dir_view_4;
// //     if (!strip || !lv_obj_is_valid(strip)) {
// //         return;
// //     }

// //     lv_coord_t view_x1 = lv_obj_get_scroll_x(strip);
// //     lv_coord_t view_w = lv_obj_get_width(strip);
// //     lv_coord_t view_x2 = view_x1 + view_w;

// //     // 计算预加载区域
// //     lv_coord_t preload_offset = (VIDEO_DIR_THUMB_WIDTH + VIDEO_DIR_THUMB_GAP) * VIDEO_DIR_THUMB_PRELOAD_COUNT;
// //     lv_coord_t load_x1 = view_x1 - preload_offset;
// //     lv_coord_t load_x2 = view_x2 + preload_offset;

// //     printf("lazy_load: scroll_x=%d, width=%d, preload_offset=%d, load_zone=[%d, %d]\n", 
// //            view_x1, view_w, preload_offset, load_x1, load_x2);

// //     for (size_t i = 0; i < s_video_dir_thumb_count; ++i) {
// //         video_dir_thumb_slot_t *slot = &s_video_dir_thumbs[i];
// //         if (!slot->placeholder || !lv_obj_is_valid(slot->placeholder)) {
// //             continue;
// //         }

// //         lv_coord_t placeholder_x1 = lv_obj_get_x(slot->placeholder);
// //         lv_coord_t placeholder_x2 = placeholder_x1 + lv_obj_get_width(slot->placeholder);

// //         bool should_be_loaded = (placeholder_x1 < load_x2 && placeholder_x2 > load_x1);

// //         if (should_be_loaded) {
// //             if (!slot->buf && !slot->pending) {
// //                 printf("lazy_load: loading slot %d (pos: %d) into load zone\n", i, placeholder_x1);
// //                 size_t buf_size = VIDEO_DIR_THUMB_WIDTH * VIDEO_DIR_THUMB_HEIGHT * 2;
// //                 slot->buf = malloc(buf_size);
// //                 if (!slot->buf) {
// //                     printf("video_dir: thumb buffer alloc fail index=%u\n", (unsigned)i);
// //                     continue;
// //                 }
// //                 memset(slot->buf, 0, buf_size);

// //                 slot->dsc.header.always_zero = 0;
// //                 slot->dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
// //                 slot->dsc.header.w = VIDEO_DIR_THUMB_WIDTH;
// //                 slot->dsc.header.h = VIDEO_DIR_THUMB_HEIGHT;
// //                 slot->dsc.data_size = buf_size;
// //                 slot->dsc.data = slot->buf;

// //                 video_dir_thumb_queue_request(slot, 0);
// //             } else if (slot->buf && !slot->ready && !slot->pending) {
// //                 printf("lazy_load: requeue slot %d (pos: %d) for decode\n", i, placeholder_x1);
// //                 video_dir_thumb_queue_request(slot, 0);
// //             }
// //         } else {
// //             if (slot->buf) {
// //                 if (slot->pending) {
// //                     printf("lazy_load: slot %d (pos: %d) is pending, cannot unload now\n", i, placeholder_x1);
// //                 } else {
// //                     printf("lazy_load: unloading slot %d (pos: %d) from outside load zone\n", i, placeholder_x1);
// //                     free(slot->buf);
// //                     slot->buf = NULL;
// //                     slot->ready = false;
// //                     // Restore placeholder appearance
// //                     lv_img_set_src(slot->placeholder, NULL);
// //                     lv_obj_set_style_bg_color(slot->placeholder, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN | LV_STATE_DEFAULT);
// //                     lv_obj_set_style_bg_opa(slot->placeholder, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
// //                     lv_obj_invalidate(slot->placeholder);
// //                 }
// //             }
// //         }
// //     }
// }

// static int video_dir_show_preview_decode(const char *path, bool broadcast_dir)
// {
//     if (!path || !path[0]) {
//         return -1;
//     }

//     if (storage_device_ready() == 0) {
//         video_dec_post_msg("noCard", 1);
//         return -1;
//     }

//     lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
//     if (!ui_scr) {
//         return -1;
//     }

//     //video_dir_hide_folder_widgets(ui_scr);

//     if (lv_obj_is_valid(ui_scr->video_dir_img_6)) {
//         lv_obj_clear_flag(ui_scr->video_dir_img_6, LV_OBJ_FLAG_HIDDEN);
//         lv_obj_set_pos(ui_scr->video_dir_img_6, 0, 0);
//         lv_obj_set_size(ui_scr->video_dir_img_6, LATEST_PREVIEW_WIDTH, LATEST_PREVIEW_HEIGHT);
//         lv_obj_move_background(ui_scr->video_dir_img_6);
//     }

//     if (video_dir_decode_latest_to_buffer(path)) {
//         return -1;
//     }

//     if (lv_obj_is_valid(ui_scr->video_dir_img_6)) {
//         lv_img_set_src(ui_scr->video_dir_img_6, &latest_preview_dsc);
//         lv_obj_invalidate(ui_scr->video_dir_img_6);
//     }

//     if (broadcast_dir) {
//         char dir_buf[LATEST_PREVIEW_PATH_MAX] = {0};
//         video_dir_extract_directory_from_path(path, dir_buf, sizeof(dir_buf));
//         if (dir_buf[0]) {
//             video_dir_send_directory_message(dir_buf);
//             // if (lv_obj_is_valid(ui_scr->video_dir_lbl_path)) {
//             //     lv_label_set_text(ui_scr->video_dir_lbl_path, dir_buf);
//             //     lv_obj_clear_flag(ui_scr->video_dir_lbl_path, LV_OBJ_FLAG_HIDDEN);
//             // }
//         }
//     }

//     return 0;
// }

// static int video_dir_show_preview_from_path(const char *path, bool broadcast_dir)
// {
//     if (video_dir_show_preview_decode(path, broadcast_dir)) {
//         return -1;
//     }

//     int index = video_dir_media_find_index_by_path(path);
//     if (index >= 0) {
//         video_dir_set_active_index((size_t)index);
//     } else {
//         strncpy(s_video_dir_active_path, path, sizeof(s_video_dir_active_path) - 1);
//         s_video_dir_active_path[sizeof(s_video_dir_active_path) - 1] = '\0';
//         s_video_dir_active_valid = false;
//         video_dir_update_thumbnail_highlight_by_index(SIZE_MAX);
//         video_dir_update_counter_label_active();
//     }

//     return 0;
// }

// static int video_dir_show_preview_by_index(size_t index, bool broadcast_dir)
// {
//     const video_dir_media_entry_t *entry = video_dir_media_get_entry(index);
//     if (!entry) {
//         return -1;
//     }

//     if (video_dir_show_preview_decode(entry->path, broadcast_dir)) {
//         return -1;
//     }

//     video_dir_set_active_index(index);
//     return 0;
// }

// static void video_dir_thumbnail_event_handler(lv_event_t *e)
// {
//     if (!e) {
//         return;
//     }

//     lv_event_code_t code = lv_event_get_code(e);
//     if (code != LV_EVENT_CLICKED) {
//         return;
//     }

//     video_dir_thumb_slot_t *slot = (video_dir_thumb_slot_t *)lv_event_get_user_data(e);
//     if (!slot) {
//         return;
//     }

//     bool resume_needed = video_dir_thumb_task_pause();

//     bool handled = false;
//     if (slot->index != SIZE_MAX && slot->index < s_video_dir_media_count) {
//         handled = (video_dir_show_preview_by_index(slot->index, true) == 0);
//     }

//     if (!handled && slot->path[0]) {
//         handled = (video_dir_show_preview_from_path(slot->path, true) == 0);
//     }

//     if (!handled) {
//         printf("video_dir: thumbnail click fallback failed index=%u path=%s\n", (unsigned)slot->index, slot->path);
//     }

//     video_dir_thumb_task_resume(resume_needed);
// }

// static int video_dir_fetch_latest_media_path(char *path_buf, size_t buf_len, char *dir_buf, size_t dir_len)
// {
//     if (!path_buf || buf_len == 0) {
//         return -1;
//     }

//     video_dir_media_entry_t entry = {0};
//     size_t count = video_dir_collect_recent_media(&entry, 1);
//     if (count == 0) {
//         printf("video_dir: no jpg found in configured paths\n");
//         return -1;
//     }

//     strncpy(path_buf, entry.path, buf_len - 1);
//     path_buf[buf_len - 1] = '\0';

//     if (dir_buf && dir_len) {
//         strncpy(dir_buf, entry.dir, dir_len - 1);
//         dir_buf[dir_len - 1] = '\0';
//     }

//     printf("video_dir: best candidate %s\n", path_buf);
//     return 0;
// }

// static int video_dir_decode_latest_to_buffer(const char *path)
// {
//     if (!path || !path[0]) {
//         return -1;
//     }

//     if (ensure_latest_preview_buffer()) {
//         return -1;
//     }

//     pipeline_state = PIPELINE_STOP;
//     bool locked = video_dir_pipeline_lock();
//     int err = jpeg2yuv_with_pipeline(path, latest_preview_buf, LATEST_PREVIEW_WIDTH, LATEST_PREVIEW_HEIGHT);
//     jpeg2yuv_pipeline_uninit();
//     pipeline_state = err ? PIPELINE_STOP : PIPELINE_IDLE;
//     video_dir_pipeline_unlock(locked);

//     if (err) {
//         printf("video_dir: decode latest media fail %s\n", path);
//         return -1;
//     }

//     return 0;
// }

// int video_dir_show_latest_preview(void)
// {
//     printf("----->%s()-------: %d\n", __func__, __LINE__);

// #if LV_USE_GUIBUILDER_SIMULATOR
//     return -1;
// #else
//     if (storage_device_ready() == 0) {
//         video_dec_post_msg("noCard", 1);
//         return -1;
//     }
//         printf("----->%s()-------: %d\n", __func__, __LINE__);

//     lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
//     if (!ui_scr) {
//         return -1;
//     }
//         printf("----->%s()-------: %d\n", __func__, __LINE__);

//     video_dir_media_entry_t *entries = malloc(sizeof(video_dir_media_entry_t) * VIDEO_DIR_THUMB_MAX);
//     if (!entries) {
//         printf("video_dir: failed to allocate memory for media entries\n");
//         return -1;
//     }
    
//     size_t entry_count = video_dir_collect_recent_media(entries, VIDEO_DIR_THUMB_MAX);
//     if (entry_count == 0) {
//         video_dec_post_msg("noFile", 1);
//         video_dir_thumb_slots_clear(ui_scr->video_dir_view_4);
//         if (lv_obj_is_valid(ui_scr->video_dir_view_4)) {
//             lv_obj_add_flag(ui_scr->video_dir_view_4, LV_OBJ_FLAG_HIDDEN);
//         }
//         video_dir_media_entries_clear();
//         free(entries);
//         return -1;
//     }
//         printf("----->%s()-------: %d\n", __func__, __LINE__);

//     if (video_dir_media_entries_set(entries, entry_count)) {
//         free(entries);
//         return -1;
//     }
//     free(entries);

//     size_t initial_index = 0;
//     if (video_dir_show_preview_by_index(initial_index, true)) {
//         const video_dir_media_entry_t *entry = video_dir_media_get_entry(initial_index);
//         if (!entry || video_dir_show_preview_from_path(entry->path, true)) {
//             video_dir_media_entries_clear();
//             return -1;
//         }
//     }

//     //video_dir_build_thumbnail_strip(ui_scr, s_video_dir_active_valid ? s_video_dir_active_index : initial_index);
//         printf("----->%s()-------: %d\n", __func__, __LINE__);

//     return 0;
// #endif
// }

// int video_dir_delete_active_media(void)
// {
// #if LV_USE_GUIBUILDER_SIMULATOR
//     return -1;
// #else
//     if (storage_device_ready() == 0) {
//         video_dec_post_msg("noCard", 1);
//         return -1;
//     }

//     if (!s_video_dir_active_path[0]) {
//         printf("video_dir: delete skip, no active selection\n");
//         return -1;
//     }

//     video_dir_thumb_task_stop();

//     char delete_path[LATEST_PREVIEW_PATH_MAX];
//     strncpy(delete_path, s_video_dir_active_path, sizeof(delete_path) - 1);
//     delete_path[sizeof(delete_path) - 1] = '\0';

//     int current_index = video_dir_media_find_index_by_path(delete_path);

//     int err = fdelete_by_name(delete_path);
//     if (err) {
//         printf("video_dir: delete fail path=%s err=%d\n", delete_path, err);
//         return -1;
//     }

//     lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
//     if (!ui_scr) {
//         s_video_dir_active_path[0] = '\0';
//         return 0;
//     }

//     video_dir_thumb_slots_clear(ui_scr->video_dir_view_4);

//     video_dir_media_entry_t *entries = malloc(sizeof(video_dir_media_entry_t) * VIDEO_DIR_THUMB_MAX);
//     if (!entries) {
//         printf("video_dir: delete alloc fail\n");
//         return -1;
//     }

//     size_t entry_count = video_dir_collect_recent_media(entries, VIDEO_DIR_THUMB_MAX);

//     if (video_dir_media_entries_set(entries, entry_count)) {
//         free(entries);
//         return -1;
//     }

//     free(entries);

//     if (entry_count > 0) {
//         size_t next_index = 0;
//         if (current_index >= 0) {
//             if ((size_t)current_index < entry_count) {
//                 next_index = (size_t)current_index;
//             } else if (entry_count > 0) {
//                 next_index = entry_count - 1;
//             }
//         }

//         if (video_dir_show_preview_by_index(next_index, true)) {
//             const video_dir_media_entry_t *entry = video_dir_media_get_entry(next_index);
//             if (entry) {
//                 if (video_dir_show_preview_from_path(entry->path, true)) {
//                     printf("video_dir: failed to show preview after delete, path=%s\n", entry->path);
//                 }
//             }
//         }

//         //video_dir_build_thumbnail_strip(ui_scr, s_video_dir_active_valid ? s_video_dir_active_index : next_index);
//     } else {
//         if (lv_obj_is_valid(ui_scr->video_dir_view_4)) {
//             lv_obj_add_flag(ui_scr->video_dir_view_4, LV_OBJ_FLAG_HIDDEN);
//         }
//         if (lv_obj_is_valid(ui_scr->video_dir_img_6)) {
//             lv_img_set_src(ui_scr->video_dir_img_6, NULL);
//             lv_obj_add_flag(ui_scr->video_dir_img_6, LV_OBJ_FLAG_HIDDEN);
//         }
//         video_dir_clear_active_selection();
//         video_dir_update_counter_label_active();
//         video_dir_update_thumbnail_highlight_by_index(SIZE_MAX);
//     }
//     return 0;
// #endif
// }


// static void dec_no_card_return(int dir)
// {
// #if 1
//     gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
//     if (screen == NULL) {
//         screen = gui_scr_create(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE,
//                                 "video_dir_landscape_mode",
//                                 guider_ui.video_dir_landscape_mode,
//                                 (gui_scr_setup_cb_t)setup_scr_video_dir_landscape_mode,
//                                 (gui_scr_unload_cb_t)unload_scr_video_dir_landscape_mode);
//     }

//     if (screen == NULL) {
//         return;
//     }

//     lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
//     if (ui_scr && ui_scr->video_dir_landscape_mode_view_1 && lv_obj_is_valid(ui_scr->video_dir_landscape_mode_view_1)) {
//         lv_obj_add_flag(ui_scr->video_dir_landscape_mode_view_1, LV_OBJ_FLAG_HIDDEN);
//     }

//     if (gui_scr_get_act() != screen) {
//         ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
//     }
// #endif
// }


// static int dec_no_card_handler(const char *type, u32 arg)
// {
//     printf("----->%s()------->arg: %d\n", __func__, arg);
//     extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
//     lvgl_rpc_post_func(dec_no_card_return, 1, arg);
//     lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 3000, (void *)_("nosd"));
//     return 0;
// }

// static int dec_no_file_handler(const char *type, u32 arg)
// {
//     extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
//     lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 1000, (void *)_("nofile"));
//     return 0;
// }

// static int dec_card_in_handler(const char *type, u32 arg)
// {
//     lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
//     if (!ui_scr) {
//         return -1;
//     }

//     if (ui_scr->video_dir_landscape_mode_del == false) {
//         if (ui_scr->video_dir_landscape_mode_view_1 &&
//             lv_obj_is_valid(ui_scr->video_dir_landscape_mode_view_1) &&
//             lv_obj_has_flag(ui_scr->video_dir_landscape_mode_view_1, LV_OBJ_FLAG_HIDDEN)) {
//             lv_obj_clear_flag(ui_scr->video_dir_landscape_mode_view_1, LV_OBJ_FLAG_HIDDEN);
//         }

//         video_dir_landscape_show_latest_preview();
//     }

//     return 0;
// }
// /*
// *	模式post消息给UI，执行UI动作
// *
// */
// #ifdef CONFIG_FILE_PREVIEW_ENABLE
// void video_dec_post_msg(const char *msg, ...)
// {
// #ifdef USE_LVGL_V8_UI_DEMO
//     va_list argptr;

//     printf("[chili] %s %s   \n", __func__, msg);

//     va_start(argptr, msg);

//     if (strstr(msg, "noCard")) {
//         dec_no_card_handler(msg, va_arg(argptr, int));
//     } else if (strstr(msg, "cardIn")) {
//         lvgl_rpc_post_func(dec_card_in_handler, 2, msg, va_arg(argptr, int));
//     } else if (strstr(msg, "noFile")) {
//         dec_no_file_handler(msg, va_arg(argptr, int));
//     } else if (strstr(msg, "fileErr")) {
//         dec_file_err_handler(msg, 0);
//     } else if (strstr(msg, "end") || strstr(msg, "pause")) {
//         lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_VIDEO_PAUSE, LV_STATE_DEFAULT, 0);
//     } else if (strstr(msg, "play")) {
//         lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_VIDEO_PAUSE, LV_STATE_CHECKED, 0);
//     } else if (strstr(msg, "plyTime")) {
//         dec_play_time_handler(msg, va_arg(argptr, int));
//     } else if (strstr(msg, "fname")) {
//         dec_file_name_handler(msg, va_arg(argptr, int));
//     } else {
//         printf("[chili] %s your msg [%s] no callback! \n", __func__, msg, __LINE__);
//     }

//     va_end(argptr);

// #endif

// }
// #endif /* CONFIG_FILE_PREVIEW_ENABLE */
// static void video_dir_view_9_event_handler(lv_event_t *e)  //文件夹回调
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
//     lv_obj_t *src = lv_event_get_target(e);
//     switch (code) {
//     case LV_EVENT_CLICKED: {
//         //custom code video_file
//         {
//             lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
//             if (!ui_scr) {
//                 return;
//             }
//             printf("------>%s()----->%d\n", __func__, __LINE__);
//             lv_obj_t *dest = ui_scr->video_dir;
//             lv_obj_t *label = lv_obj_get_child(src, 2);
//             if (!label) {
//                 lv_obj_t *parent = lv_obj_get_parent(src);
//                 label = lv_obj_get_child(parent, 2);
//             }
//             const char *text1 = lv_label_get_text(label); //文件夹
//             const char *base_path = CONFIG_DEC_ROOT_PATH;
//             printf("base_path: %s %s:%d\n", base_path, __func__, __LINE__);
//             printf("text1: %s %s:%d\n", text1, __func__, __LINE__);

//             size_t folder_len = strlen(text1);
//             size_t base_len = strlen(base_path);
//             char *full_path = lvgl_module_msg_get_ptr(GUI_MODEL_MSG_ID_FILE_PATH, base_len + folder_len + 2);
//             if (!full_path) {
//                 printf("full_path buf get err\n");
//                 return;
//             }
//             printf("base_path buf addr: %p %s:%d\n", base_path, __func__, __LINE__);
//             printf("full_path buf addr: %p %s:%d\n", full_path, __func__, __LINE__);

//             strcpy(full_path, base_path);
//             if (base_len > 0 && full_path[base_len - 1] != '/') {
//                 full_path[base_len] = '/';
//                 full_path[base_len + 1] = '\0';
//             }
//             strcat(full_path, text1);
//             size_t len = strlen(full_path);
//             if (len > 0 && full_path[len - 1] != '/') {
//                 full_path[len] = '/';
//                 full_path[len + 1] = '\0';
//             }

//             printf("full_path: %s  %s:%d\n", full_path, __func__, __LINE__);
//             //发送路径给模块
//             if (dir_path) {
//                 free(dir_path);
//                 dir_path = NULL;
//             }

//             size_t full_len = strlen(full_path);
//             dir_path = malloc(full_len + 1);
//             if (!dir_path) {
//                 printf("dir_path malloc err \n");
//                 return;
//             }
//             memcpy(dir_path, full_path, full_len + 1);
//             printf("cur path: %s\n", full_path);
// #if LV_USE_GUIBUILDER_SIMULATOR
// #else
//             lvgl_module_msg_send_ptr(full_path, 0);
// #endif
//         }
//         gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_FILE);
//         if (screen == NULL) {
//             printf("------>%s()----->%d\n", __func__, __LINE__);
//             screen = gui_scr_create(GUI_SCREEN_VIDEO_FILE, "video_file", guider_ui.video_file, (gui_scr_setup_cb_t)setup_scr_video_file, (gui_scr_unload_cb_t)unload_scr_video_file);
//         }
//         ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true, true, false);

//     }
//     break;
//     default:
//         break;
//     }
// }

// void create_dir(int index, char *dir_name)
// {
//     lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
//     if (!ui_scr) {
//         return;
//     }
//     lv_group_t *def_group = lv_group_get_default();
//     //Write codes video_dir_view_9
//     lv_obj_t *video_dir_view_new = lv_obj_create(ui_scr->video_dir_view_1);
//     //Set style for video_dir_view_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
//     lv_obj_set_style_radius(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(video_dir_view_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_shadow_width(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_width(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_left(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_right(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_top(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_bottom(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

//     //Set style for video_dir_view_dir. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
//     lv_obj_set_style_radius(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_bg_color(video_dir_view_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_bg_opa(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_shadow_width(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_border_width(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_outline_color(video_dir_view_new, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_outline_width(video_dir_view_new, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_outline_opa(video_dir_view_new, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_outline_pad(video_dir_view_new, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_pad_left(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_pad_right(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_pad_top(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//     lv_obj_set_style_pad_bottom(video_dir_view_new, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

//     lv_obj_set_pos(video_dir_view_new, SCALE_FACTOR_W * (91 + index  % 3 * interval_dir_x),
//                    SCALE_FACTOR_H * (90 + index  / 3 * interval_dir_y));
//     lv_obj_set_size(video_dir_view_new, DIR_CONT_W, DIR_CONT_H);
//     lv_obj_set_scrollbar_mode(video_dir_view_new, LV_SCROLLBAR_MODE_OFF);
//     lv_group_add_obj(def_group, video_dir_view_new);
//     // lv_obj_add_flag(video_dir_view_new, LV_OBJ_FLAG_EVENT_BUBBLE);
//     //Write codes video_dir_cb_1
//     lv_obj_t *video_dir_cb_new = lv_checkbox_create(video_dir_view_new);
//     lv_checkbox_set_text(video_dir_cb_new, "checkbox");

//     //Set style for video_dir_cb_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
//     lv_obj_set_style_radius(video_dir_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(video_dir_cb_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(video_dir_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_shadow_width(video_dir_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_color(video_dir_cb_new, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_width(video_dir_cb_new, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_opa(video_dir_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_side(video_dir_cb_new, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_color(video_dir_cb_new, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
// #if THREE_WAY_ENABLE && (LCD_W < 800)
//     //三路小屏幕简单处理,如更换其他屏幕且缩放了UI,请自行更换字体
//     //这里字体对应公版640*360 UI工程
//     //lv_obj_set_style_text_font(video_dir_cb_new, &lv_font_montserratMedium_17, LV_PART_MAIN | LV_STATE_DEFAULT);
// #else
//     lv_obj_set_style_text_font(video_dir_cb_new, &lv_font_montserratMedium_22, LV_PART_MAIN | LV_STATE_DEFAULT);
// #endif
//     lv_obj_set_style_text_letter_space(video_dir_cb_new, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

//     //Set style for video_dir_cb_1. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
//     lv_obj_set_style_radius(video_dir_cb_new, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(video_dir_cb_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(video_dir_cb_new, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_color(video_dir_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_width(video_dir_cb_new, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_opa(video_dir_cb_new, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_side(video_dir_cb_new, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR | LV_STATE_DEFAULT);

//     //Set style for video_dir_cb_1. Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED
//     lv_obj_set_style_radius(video_dir_cb_new, 20, LV_PART_INDICATOR | LV_STATE_CHECKED);
//     lv_obj_set_style_bg_color(video_dir_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_CHECKED);
//     lv_obj_set_style_bg_opa(video_dir_cb_new, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
//     lv_obj_set_style_border_color(video_dir_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_CHECKED);
//     lv_obj_set_style_border_width(video_dir_cb_new, 3, LV_PART_INDICATOR | LV_STATE_CHECKED);
//     lv_obj_set_style_border_opa(video_dir_cb_new, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
//     lv_obj_set_style_border_side(video_dir_cb_new, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR | LV_STATE_CHECKED);
//     lv_obj_set_size(video_dir_cb_new, CHECK_BOX_W, CHECK_BOX_H);
//     lv_obj_set_align(video_dir_cb_new, LV_ALIGN_OUT_TOP_RIGHT);
//     lv_obj_set_scrollbar_mode(video_dir_cb_new, LV_SCROLLBAR_MODE_OFF);
//     lv_obj_add_flag(video_dir_cb_new, LV_OBJ_FLAG_HIDDEN);
//     /*lv_obj_add_event_cb(video_dir_cb_new, video_dir_cb_event_handler, LV_EVENT_ALL, &guider_ui);*/

//     //Write codes video_dir_img_19
//     lv_obj_t *video_dir_img_new = lv_img_create(video_dir_view_new);

//     //Set style for video_dir_img_19. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
//     lv_obj_set_style_radius(video_dir_img_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_clip_corner(video_dir_img_new, true, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(video_dir_img_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(video_dir_img_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_recolor(video_dir_img_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_recolor_opa(video_dir_img_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_opa(video_dir_img_new, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_size(video_dir_img_new, DIR_IMG_W, DIR_IMG_H);
//     lv_obj_set_align(video_dir_img_new, LV_ALIGN_TOP_MID);
//     lv_obj_set_scrollbar_mode(video_dir_img_new, LV_SCROLLBAR_MODE_OFF);
//     lv_obj_add_flag(video_dir_img_new, LV_OBJ_FLAG_CLICKABLE);
// #if LV_USE_GUIBUILDER_SIMULATOR
//     lv_img_set_src(video_dir_img_new, "A:\\wl83_411\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\file_dir.png");
// #else
//     //lv_img_set_src(video_dir_img_new, gui_get_res_path(RES_FILE_DIR));
// #endif
//     lv_img_set_pivot(video_dir_img_new, 0, 0);
//     lv_img_set_angle(video_dir_img_new, 0);
//     lv_img_set_zoom(video_dir_img_new, 256);
//     lv_obj_add_flag(video_dir_img_new, LV_OBJ_FLAG_EVENT_BUBBLE);
//     lv_obj_add_flag(video_dir_img_new, LV_OBJ_FLAG_CLICKABLE);
//     //Write codes video_dir_lbl_9
//     lv_obj_t *video_dir_lbl_new = lv_label_create(video_dir_view_new);
//     lv_label_set_text(video_dir_lbl_new, dir_name);
//     lv_label_set_long_mode(video_dir_lbl_new, LV_LABEL_LONG_WRAP);

//     //Set style for video_dir_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
//     lv_obj_set_style_radius(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(video_dir_lbl_new, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_shadow_width(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_width(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_color(video_dir_lbl_new, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
// #if THREE_WAY_ENABLE && (LCD_W < 800)
//     //三路小屏幕简单处理,如更换其他屏幕且缩放了UI,请自行更换字体
//     //这里字体对应公版640*360 UI工程
//     lv_obj_set_style_text_font(video_dir_lbl_new, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
// #else
//     lv_obj_set_style_text_font(video_dir_lbl_new, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
// #endif
//     lv_obj_set_style_text_letter_space(video_dir_lbl_new, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_line_space(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_align(video_dir_lbl_new, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_left(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_right(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_top(video_dir_lbl_new, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_bottom(video_dir_lbl_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_size(video_dir_lbl_new, DIR_CONT_W, DIR_CONT_H - DIR_IMG_H - 5);
//     lv_obj_align_to(video_dir_lbl_new, video_dir_img_new,
//                     LV_ALIGN_OUT_BOTTOM_MID, -5, 0);
//     lv_obj_set_scrollbar_mode(video_dir_lbl_new, LV_SCROLLBAR_MODE_OFF);
//     lv_obj_add_flag(video_dir_lbl_new, LV_OBJ_FLAG_EVENT_BUBBLE);

//     lv_obj_add_event_cb(video_dir_view_new, video_dir_view_9_event_handler, LV_EVENT_ALL, &guider_ui);
// }

// static void video_file_view_1_event_handler(lv_event_t *e)  //录像文件控件回调
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
//     lv_obj_t *src = lv_event_get_target(e);
//     switch (code) {
//     case LV_EVENT_CLICKED: {  //进入video_play页面
//         lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//         if (!ui_scr) {
//             return;
//         }
//         if (pipeline_state == PIPELINE_RUNING) {
//             return;
//         } else if (pipeline_state == PIPELINE_IDLE) {
//             pipeline_state = PIPELINE_EXIT;
//             jpeg2yuv_pipeline_uninit();
//         }
//         //记录当前页面和滚动条值
//         to_play_video_page = cur_page;
//         lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
//         cur_scroll_val = lv_obj_get_scroll_y(contain);

//         extern void get_focused_file_idx(lv_obj_t *focused_obj);
//         get_focused_file_idx(src);

//         extern int browser_open_file(void *file, char *path, char *name);
//         lv_obj_t *label = lv_obj_get_child(src, 2);
//         if (!label) {
//             lv_obj_t *parent = lv_obj_get_parent(src);
//             label = lv_obj_get_child(parent, 2);
//         }
//         const char *text1 = lv_label_get_text(label); //文件名
//         const char *text2 = lv_label_get_text(ui_scr->video_file_lbl_path); //路径
//         char *file_path;
//         asprintf(&file_path, "%s%s", text2, text1);
//         printf("cur path: %s\n", file_path);
// #if LV_USE_GUIBUILDER_SIMULATOR
// #else
//         FILE *fd = NULL;//文件句柄指针
//         fd = fopen(file_path, "r");
//         if (fd) {
//             browser_open_file(fd, text2, text1);
//         }
//         free(file_path);
//         /*fclose(fd);   */
// #endif
//         gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_PLAY);
//         if (screen == NULL) {
//             screen = gui_scr_create(GUI_SCREEN_VIDEO_PLAY, "video_play", guider_ui.video_play, (gui_scr_setup_cb_t)setup_scr_video_play, (gui_scr_unload_cb_t)unload_scr_video_play);
//         }
//         ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, true, true, false);

//     }
//     break;
//     default:
//         break;
//     }

// }

// static void reset_scroll_and_line(lv_obj_t *contain)
// {
//     int max_line;
//     lv_obj_update_layout(contain);
//     int  max_scroll_y = lv_obj_get_scroll_bottom(contain);

//     if (cur_scroll_val > max_scroll_y) {
//         cur_scroll_val = max_scroll_y;
//         cur_scroll_val = cur_scroll_val < 0 ? 0 : cur_scroll_val;
//         line = cur_scroll_val / (IMG_CONT_H + IMG_CONT_ROW_SPACE);
//         max_line = ceil((float)create_num / 3) - 3;
//         if (line > max_line) {
//             line  = max_line;
//         }
//         last_line = line;
//     }
// }


// static void next_page(void)
// {
//     int start, end, remain;
//     lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//     if (!ui_scr) {
//         return;
//     }
//     cur_page++;
//     printf("cur Page %d\n", cur_page);
//     if (cur_page > total_file_page) {
//         cur_page = total_file_page;
//         return;
//     }
//     line = 0;
//     last_line = line;
//     lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
//     lv_obj_clean(contain);
//     create_page(cur_page);

//     start = (line * 3) + (cur_page - 1) * ONE_PAGE_MAX_NUM;
//     remain = create_num + (cur_page - 1) * ONE_PAGE_MAX_NUM - start;
//     remain = remain > 9 ? 9 : remain;
//     end = start + remain;
//     update_img_text(start, end, 0);
//     dec_list_cur_page(cur_page); //保存当前页数在结构体
// }

// static void prev_page(void)
// {
//     int start, remain, end;
//     int line_h, max_scroll_val;
//     int max_line;
//     cur_page--;
//     printf("cur Page %d\n", cur_page);
//     if (cur_page < 1) {
//         cur_page = 1;
//         return;
//     }
//     lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//     if (!ui_scr) {
//         return;
//     }
//     lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
//     lv_obj_clean(contain);
//     create_page(cur_page);
//     //上一页的底部
//     max_line = ceil((float)create_num / 3) - 3;
//     line = max_line;
//     last_line = line;
//     line_h = IMG_CONT_H + IMG_CONT_ROW_SPACE;
//     max_scroll_val = (line_h * ceil((float)create_num / 3) - line_h * 2);
//     lv_obj_scroll_to_y(contain, max_scroll_val, LV_ANIM_OFF);

//     start = (line * 3) + (cur_page - 1) * ONE_PAGE_MAX_NUM;
//     remain = create_num + (cur_page - 1) * ONE_PAGE_MAX_NUM - start;
//     remain = remain > 9 ? 9 : remain;
//     end = start + remain;
//     update_img_text(start, end, 0);
//     dec_list_cur_page(cur_page); //保存当前页数在结构体

// }

// static void add_img_text(lv_obj_t *obj)
// {
//     //img
//     lv_obj_t *video_file_img_new_src_1 = lv_img_create(obj);
//     lv_obj_set_style_radius(video_file_img_new_src_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_clip_corner(video_file_img_new_src_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(video_file_img_new_src_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(video_file_img_new_src_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_recolor(video_file_img_new_src_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_recolor_opa(video_file_img_new_src_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_opa(video_file_img_new_src_1, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_pos(video_file_img_new_src_1, 0, 0);
//     lv_obj_set_size(video_file_img_new_src_1, IMG_W, IMG_H);
//     lv_obj_set_scrollbar_mode(video_file_img_new_src_1, LV_SCROLLBAR_MODE_OFF);
//     lv_obj_clear_flag(video_file_img_new_src_1, LV_OBJ_FLAG_SCROLLABLE);

//     //path
//     lv_obj_t *video_file_lbl_new_path_1 = lv_label_create(obj);
//     lv_label_set_long_mode(video_file_lbl_new_path_1, LV_LABEL_LONG_WRAP);
//     lv_obj_set_style_radius(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(video_file_lbl_new_path_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_shadow_width(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_border_width(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_color(video_file_lbl_new_path_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
// #if THREE_WAY_ENABLE && (LCD_W < 800)
//     //三路小屏幕简单处理,如更换其他屏幕且缩放了UI,请自行更换字体
//     //这里字体对应公版640*360 UI工程
//     lv_obj_set_style_text_font(video_file_lbl_new_path_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
// #else
//     lv_obj_set_style_text_font(video_file_lbl_new_path_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
// #endif
//     lv_obj_set_style_text_letter_space(video_file_lbl_new_path_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_line_space(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_text_align(video_file_lbl_new_path_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_left(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_right(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_top(video_file_lbl_new_path_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_bottom(video_file_lbl_new_path_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_size(video_file_lbl_new_path_1, IMG_W, IMG_CONT_H - IMG_H - 5);
//     lv_obj_align_to(video_file_lbl_new_path_1, video_file_img_new_src_1,
//                     LV_ALIGN_OUT_BOTTOM_LEFT, -5, 0);
//     lv_label_set_long_mode(video_file_lbl_new_path_1, LV_LABEL_LONG_WRAP);
//     lv_obj_set_scrollbar_mode(video_file_lbl_new_path_1, LV_SCROLLBAR_MODE_OFF);

//     // img label
//     lv_obj_t *video_file_img_new_flag_1 = lv_img_create(obj);
//     lv_obj_set_style_radius(video_file_img_new_flag_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_clip_corner(video_file_img_new_flag_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(video_file_img_new_flag_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(video_file_img_new_flag_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_recolor(video_file_img_new_flag_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_recolor_opa(video_file_img_new_flag_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_opa(video_file_img_new_flag_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_center(video_file_img_new_flag_1);
//     lv_obj_set_size(video_file_img_new_flag_1, VIDEO_FILE_IMG_W, VIDEO_FILE_IMG_H);
//     lv_obj_set_scrollbar_mode(video_file_img_new_flag_1, LV_SCROLLBAR_MODE_OFF);
//     lv_obj_add_flag(video_file_img_new_flag_1, LV_OBJ_FLAG_CLICKABLE);
// #if LV_USE_GUIBUILDER_SIMULATOR
//     lv_img_set_src(video_file_img_new_flag_1, "A:\\wl83_411\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\play_s.png");
// #else
//     //lv_img_set_src(video_file_img_new_flag_1, gui_get_res_path(RES_PLAY));
// #endif
//     lv_img_set_pivot(video_file_img_new_flag_1, 0, 0);
//     lv_img_set_angle(video_file_img_new_flag_1, 0);
//     lv_img_set_zoom(video_file_img_new_flag_1, 256);
//     lv_obj_clear_flag(video_file_img_new_flag_1, LV_OBJ_FLAG_SCROLLABLE);
//     lv_obj_add_flag(video_file_img_new_flag_1, LV_OBJ_FLAG_EVENT_BUBBLE);

//     //add lock_flag
//     lv_obj_t *video_file_img_lock = lv_img_create(obj);

//     //Set style for video_file_img_lock. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
//     lv_obj_set_style_radius(video_file_img_lock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_clip_corner(video_file_img_lock, true, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(video_file_img_lock, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(video_file_img_lock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_recolor(video_file_img_lock, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_recolor_opa(video_file_img_lock, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_style_img_opa(video_file_img_lock, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_set_align(video_file_img_lock, LV_ALIGN_TOP_RIGHT);
//     lv_obj_set_size(video_file_img_lock, LOCK_IMG_W, LOCK_IMG_H);
//     lv_obj_set_scrollbar_mode(video_file_img_lock, LV_SCROLLBAR_MODE_OFF);
//     lv_obj_add_flag(video_file_img_lock, LV_OBJ_FLAG_CLICKABLE);
// #if LV_USE_GUIBUILDER_SIMULATOR
//     lv_img_set_src(video_file_img_lock, "A:\\wl83_723\\wifi_video_master\\ui_prj\\Application1\\import\\image\\lock88.png");
// #else
//     //lv_img_set_src(video_file_img_lock, gui_get_res_path(RES_LOCK_FLAG));
// #endif
//     lv_img_set_pivot(video_file_img_lock, 0, 0);
//     lv_img_set_angle(video_file_img_lock, 0);
//     lv_img_set_zoom(video_file_img_lock, 256);

// }


// static void update_img_text(int start_index, int end_index, u8 dir)
// {
//     static int img_index = 0;
//     static int last_img_index = 0;
//     static  u8 last_dir = 0;
//     FILE *fp;
//     char name[50];
//     char *full_name;
//     int update_num = end_index - start_index;

//     if (dir != last_dir) {
//         img_index = last_img_index;
//     }
//     last_dir = dir;
//     lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//     if (!ui_scr) {
//         return;
//     }
//     lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
//     while (start_index < end_index) {
//         lv_obj_t *img_cont = lv_obj_get_child(contain, start_index % ONE_PAGE_MAX_NUM);
//         add_img_text(img_cont);

//         lv_obj_t *img = lv_obj_get_child(img_cont, 1);
//         lv_obj_t *text = lv_obj_get_child(img_cont, 2);
//         lv_obj_t *img_label = lv_obj_get_child(img_cont, 3);
//         lv_obj_t *img_lock_flag = lv_obj_get_child(img_cont, 4); //文件是否加锁标志
// #if FILE_DISP_REVERSE_ORDER
//         //反序显示
//         fp = fselect(fs_file, FSEL_BY_NUMBER, total_file_num - start_index);
// #else
//         //正序显示
//         fp = fselect(fs_file, FSEL_BY_NUMBER, start_index + 1);
// #endif
//         if (!fp) {
//             return;
//         }
//         fget_name(fp, name, sizeof(name));
//         lv_label_set_text(text, name);
//         int attr;
//         fget_attr(fp, &attr);
//         if (attr & F_ATTR_RO) {
//         } else if (!(attr & F_ATTR_RO)) {
//             lv_obj_add_flag(img_lock_flag, LV_OBJ_FLAG_HIDDEN);  //文件未加锁，去掉加锁标识
//         }
//         fclose(fp);
//         asprintf(&full_name, "%s%s", dir_path, name);
//         //缩略图
//         if (strcmp(lv_fs_get_ext(name), "jpg") == 0 || strcmp(lv_fs_get_ext(name), "JPG") == 0) {
//             lv_obj_add_flag(img_label, LV_OBJ_FLAG_HIDDEN);
//         }

//         int msg[3];
//         msg[0] = (int)full_name;
//         msg[1] = img_index;
//         msg[2] = --update_num;
//         int err = os_taskq_post_type(DECODE_TASK_NAME, Q_MSG, 3, msg);
//         lv_img_set_src(img, &image_dsc_list[img_index]);

//         start_index++;

//         last_img_index = img_index;
//         if (dir == 0) {
//             img_index = (img_index + 1) % IMG_BUF_NUM;
//         } else {
//             img_index = (img_index - 1 + IMG_BUF_NUM) % IMG_BUF_NUM;
//         }

//     }

//     //确保每次操作buf数量正确
//     while (end_index % 3) {
//         last_img_index = img_index;
//         if (dir == 0) {
//             img_index = (img_index + 1) % IMG_BUF_NUM;
//         } else {
//             img_index = (img_index - 1 + IMG_BUF_NUM) % IMG_BUF_NUM;
//         }
//         end_index++;
//     }

//     //清空不显示的容器
//     if (dir == 0) {
//         for (int i = last_line * 3; i < line * 3; i++) {
//             lv_obj_t *clean_cont = lv_obj_get_child(contain, i);
//             lv_obj_t *child = lv_obj_get_child(clean_cont, 1);
//             while (child) {
//                 lv_obj_del(child);
//                 child = lv_obj_get_child(clean_cont, 1);
//             }
//         }
//     } else {
//         for (int i = line * 3 + SCREEN_MAX_DISP_NUM + 3; i < last_line * 3 + SCREEN_MAX_DISP_NUM + 3; i++) {
//             if (i > create_num - 1) {
//                 continue;
//             }
//             lv_obj_t *clean_cont = lv_obj_get_child(contain, i);
//             lv_obj_t *child = lv_obj_get_child(clean_cont, 1);
//             while (child) {
//                 lv_obj_del(child);
//                 child = lv_obj_get_child(clean_cont, 1);
//             }
//         }
//     }

//     send_msg2file_num();
// }

// void scroll_update_position(int scroll_val)
// {
//     if (deleting_flag) {
//         //正在执行删除操作，防止进入scroll事件
//         return;
//     }
//     int start, end, remain;
//     int max_line;
//     int dir;
//     if (scroll_val < -EXTRA_SPACE) {
//         prev_page();
//         return;
//     }

//     if (scroll_val > (ONE_PAGE_MAX_NUM - SCREEN_MAX_DISP_NUM) / 3 * (IMG_CONT_H + IMG_CONT_ROW_SPACE) +  EXTRA_SPACE) {
//         next_page();
//         return;
//     }

//     line = scroll_val / (IMG_CONT_H + IMG_CONT_ROW_SPACE);
//     max_line = ceil((float)create_num / 3) - 3;
//     if (line > max_line) {
//         line  = max_line;
//     }

//     //刷新图片
//     if (line != last_line) {
//         dir = line > last_line ? 0 : 1;
//         if (dir == 0) {
//             start = ((last_line + 1) * 3 + SCREEN_MAX_DISP_NUM) + (cur_page - 1) * ONE_PAGE_MAX_NUM;
//             remain = create_num + (cur_page - 1) * ONE_PAGE_MAX_NUM - start;
//             remain = remain > (line - last_line) * 3 ? (line - last_line) * 3 : remain;
//             end = start + remain;
//             update_img_text(start, end, dir);
//         } else {
//             start = (line * 3) + (cur_page - 1) * ONE_PAGE_MAX_NUM;
//             end = start + (last_line - line) * 3;
//             update_img_text(start, end, dir);
//         }
//     }
//     last_line = line;
// }

// void file_list_up(void)
// {
//     lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//     if (!ui_scr) {
//         return;
//     }
//     lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);

//     int cur_scroll_val = lv_obj_get_scroll_y(contain);
//     int line_h = IMG_CONT_H + IMG_CONT_ROW_SPACE;
//     int set_val = cur_scroll_val - line_h;
//     int min_scroll_val = 0;
//     if (set_val < min_scroll_val) {
//         set_val = min_scroll_val;
//         lv_obj_scroll_to_y(contain, set_val, LV_ANIM_OFF);
//         prev_page();
//     } else {
//         lv_obj_scroll_to_y(contain, set_val, LV_ANIM_OFF);
//     }
// }

// void file_list_down(void)
// {
//     lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//     if (!ui_scr) {
//         return;
//     }
//     lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);

//     int cur_scroll_val = lv_obj_get_scroll_y(contain);
//     int line_h = IMG_CONT_H + IMG_CONT_ROW_SPACE;
//     int set_val = cur_scroll_val + line_h;

//     int max_scroll_val = (line_h * ceil((float)create_num / 3) - line_h * 2);
//     if (set_val > max_scroll_val) {
//         set_val = max_scroll_val;
//         lv_obj_scroll_to_y(contain, set_val, LV_ANIM_OFF);
//         next_page();
//     } else {
//         lv_obj_scroll_to_y(contain, set_val, LV_ANIM_OFF);
//     }
// }



// //页面加载
// void video_dir_screen_load(void)
// {
//     lv_ui_video_dir *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_DIR);
//     if (!ui_scr) {
//         return;
//     }
//     if (storage_device_ready() == 0) {
//         //sd卡未挂載
//         printf("-NOT SD \n");
//         sys_prompt_show_ctl(3000, (void *)_("nosd"));
//         if (lv_obj_is_valid(ui_scr->video_dir_view_1)) {
//             lv_obj_add_flag(ui_scr->video_dir_view_1, LV_OBJ_FLAG_HIDDEN);
//         }
//         return;
//     }
//     if (dir_path) {
//         free(dir_path);
//         dir_path = NULL;
//     }
//     u8 name[128];
//     struct vfscan *fs = NULL;
//     fs = fscan(CONFIG_DEC_ROOT_PATH, "-d -tPNGBINAVITTLDAT -sn", 2);
//     if (!fs || fs->file_number == 0) {
//         printf("fscan err!!");
//         video_dec_post_msg("noFile", 1);
//     } else {
//         void *dir = fselect(fs, FSEL_FIRST_FILE, 0);
//         for (int i = 0; i < fs->file_number; i++) {
//             fget_name(dir, name, sizeof(name));
//             printf("name %s\n", name);
//             fclose((FILE *)dir);
//             create_dir(i, name);
//             dir = fselect(fs, FSEL_NEXT_FILE, 0);
//         }
//         fscan_release(fs);
//         lv_obj_update_layout(ui_scr->video_dir);
//     }
// }

// static void create_page(int page)
// {
//     if (page < total_file_page) {
//         create_num = total_file_num < ONE_PAGE_MAX_NUM ? total_file_num : ONE_PAGE_MAX_NUM;
//     } else {
//         create_num = total_file_num - ONE_PAGE_MAX_NUM * (page - 1);
//     }
//     printf("------>%s()------>create_num: %d\n", __func__, create_num);
//     lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//     if (!ui_scr) {
//         return;
//     }
//     lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
//     lv_group_t *def_group = lv_group_get_default();
//     for (int i = 0; i < create_num; i++) {
//         lv_obj_t *img_cont = lv_obj_create(contain);  //创建录像文件控件
//         lv_obj_set_style_radius(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_bg_color(img_cont, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_bg_opa(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_shadow_width(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_color(img_cont, lv_color_make(0x2F, 0x63, 0x8F), LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_width(img_cont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_opa(img_cont, LV_OPA_50, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_side(img_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_pad_left(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_pad_right(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_pad_top(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_pad_bottom(img_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

//         //Set style for img_cont. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
//         lv_obj_set_style_radius(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_bg_color(img_cont, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_bg_opa(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_shadow_width(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_border_width(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_outline_color(img_cont, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_outline_width(img_cont, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_outline_opa(img_cont, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_outline_pad(img_cont, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_pad_left(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_pad_right(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_pad_top(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_style_pad_bottom(img_cont, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
//         lv_obj_set_size(img_cont, IMG_CONT_W, IMG_CONT_H);
//         lv_obj_clear_flag(img_cont, LV_OBJ_FLAG_SCROLLABLE);
//         lv_obj_set_scrollbar_mode(img_cont, LV_SCROLLBAR_MODE_OFF);
//         lv_group_add_obj(def_group, img_cont);
//         lv_obj_add_event_cb(img_cont, video_file_view_1_event_handler, LV_EVENT_ALL, &guider_ui);

//         lv_obj_t *video_file_cb_new = lv_checkbox_create(img_cont);
//         lv_checkbox_set_text(video_file_cb_new, "checkbox");

//         //Set style for video_file_cb_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
//         lv_obj_set_style_radius(video_file_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_bg_color(video_file_cb_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_bg_opa(video_file_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_shadow_width(video_file_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_color(video_file_cb_new, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_width(video_file_cb_new, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_opa(video_file_cb_new, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_side(video_file_cb_new, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_text_color(video_file_cb_new, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
// #if THREE_WAY_ENABLE && (LCD_W < 800)
//         //三路小屏幕简单处理,如更换其他屏幕且缩放了UI,请自行更换字体
//         //这里字体对应公版640*360 UI工程
//         //lv_obj_set_style_text_font(video_file_cb_new, &lv_font_montserratMedium_17, LV_PART_MAIN | LV_STATE_DEFAULT);
// #else
//         lv_obj_set_style_text_font(video_file_cb_new, &lv_font_montserratMedium_22, LV_PART_MAIN | LV_STATE_DEFAULT);
// #endif
//         lv_obj_set_style_text_letter_space(video_file_cb_new, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

//         //Set style for video_dir_cb_1. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
//         lv_obj_set_style_radius(video_file_cb_new, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//         lv_obj_set_style_bg_color(video_file_cb_new, lv_color_make(0xff, 0xff, 0xff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
//         lv_obj_set_style_bg_opa(video_file_cb_new, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_color(video_file_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_width(video_file_cb_new, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_opa(video_file_cb_new, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
//         lv_obj_set_style_border_side(video_file_cb_new, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR | LV_STATE_DEFAULT);

//         //Set style for video_dir_cb_1. Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED
//         lv_obj_set_style_radius(video_file_cb_new, 20, LV_PART_INDICATOR | LV_STATE_CHECKED);
//         lv_obj_set_style_bg_color(video_file_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_CHECKED);
//         lv_obj_set_style_bg_opa(video_file_cb_new, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
//         lv_obj_set_style_border_color(video_file_cb_new, lv_color_make(0xCE, 0xC2, 0x63), LV_PART_INDICATOR | LV_STATE_CHECKED);
//         lv_obj_set_style_border_width(video_file_cb_new, 3, LV_PART_INDICATOR | LV_STATE_CHECKED);
//         lv_obj_set_style_border_opa(video_file_cb_new, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
//         lv_obj_set_style_border_side(video_file_cb_new, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR | LV_STATE_CHECKED);
//         lv_obj_set_size(video_file_cb_new, CHECK_BOX_W, CHECK_BOX_H);
//         lv_obj_set_align(video_file_cb_new, LV_ALIGN_OUT_TOP_LEFT);
//         lv_obj_set_scrollbar_mode(video_file_cb_new, LV_SCROLLBAR_MODE_OFF);
//         lv_obj_add_flag(video_file_cb_new, LV_OBJ_FLAG_HIDDEN);
//         lv_obj_add_event_cb(video_file_cb_new, video_dir_cb_event_handler, LV_EVENT_ALL, &guider_ui);

//     }
// }

// static void post_func_flush_img(void)
// {
//     lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//     if (!ui_scr) {
//         return;
//     }
//     if (lv_obj_is_valid(ui_scr->video_file)) {
//         lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
//         if (lv_obj_is_valid(contain)) {
//             lv_obj_invalidate(contain);
//         }
//     }
// }

// static void dec_img_task(void)
// {
//     int res;
//     int kill_flag = 0;
//     int msg[8];

//     while (1) {
//         res = os_task_pend("taskq", msg, ARRAY_SIZE(msg));

//         switch (res) {
//         case OS_TASKQ:
//             switch (msg[0]) {
//             case Q_EVENT:
//                 break;
//             case Q_MSG:
//                 char *full_name = (char *)msg[1];
//                 int img_index = msg[2];
//                 int update_num = msg[3];

//                 jpeg2yuv_with_pipeline(full_name, img_buf_list[img_index], IMG_W, IMG_H);
//                 free(full_name);
//                 if (!update_num) {
//                     pipeline_state = PIPELINE_IDLE;
//                     //刷新UI
//                     lvgl_rpc_post_func(post_func_flush_img, 0);
//                 }
//                 break;
//             case Q_USER:
//                 pipeline_state = PIPELINE_STOP;
//                 kill_flag = msg[1];
//                 break;
//             default:
//                 break;
//             }
//             break;
//         case OS_TIMER:
//             break;
//         case OS_TIMEOUT:
//             break;
//         }

//         if (kill_flag) {
//             jpeg2yuv_pipeline_uninit();
//             printf("kill task:%s \n", DECODE_TASK_NAME);
//             break;
//         }
//     }

// }

// void video_file_screen_load(void)
// {
//     int start, end, remain;

//     if (storage_device_ready() == 0) {
//         //sd卡未挂載 b
//         printf("-NOT SD \n");
//         video_dec_post_msg("noCard", 0);
//         return;
//     }
//     printf("----%d---%s\n", __LINE__, __func__);
//     lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//     if (!ui_scr) {
//         return;
//     }

//     const char *scan_opts = "-tAVI -sn";

//     if (!dir_path) {
//         const char *selected_dir = NULL;
//         const char *first_existing_dir = NULL;

//         for (size_t i = 0; i < ARRAY_SIZE(latest_preview_paths); ++i) {
//             const char *candidate = latest_preview_paths[i];

//             if (!candidate || !candidate[0]) {
//                 continue;
//             }

//             if (!fdir_exist(candidate)) {
//                 continue;
//             }

//             if (!first_existing_dir) {
//                 first_existing_dir = candidate;
//             }

//             struct vfscan *candidate_scan = fscan(candidate, scan_opts, 3);
//             if (!candidate_scan) {
//                 continue;
//             }

//             if (candidate_scan->file_number > 0) {
//                 selected_dir = candidate;
//                 fscan_release(candidate_scan);
//                 break;
//             }

//             fscan_release(candidate_scan);
//         }

//         if (!selected_dir) {
//             selected_dir = first_existing_dir ? first_existing_dir : CONFIG_DEC_PATH_1;
//         }

//         size_t default_len = strlen(selected_dir);
//         size_t alloc_len = default_len + 2;

//         dir_path = malloc(alloc_len);
//         if (!dir_path) {
//             printf("dir_path malloc err \n");
//             video_dec_post_msg("noFile", 0);
//             return;
//         }

//         memcpy(dir_path, selected_dir, default_len);
//         size_t write_pos = default_len;
//         if (write_pos == 0 || dir_path[write_pos - 1] != '/') {
//             dir_path[write_pos++] = '/';
//         }
//         dir_path[write_pos] = '\0';

//         printf("video_dir: default scan dir %s\n", dir_path);
//     }

//     if (dir_path) {
//         video_dir_send_directory_message(dir_path);
//     }

//     lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
//     lv_obj_set_style_pad_column(contain, IMG_CONT_COL_SPACE, 0);  // 设置列间距
//     lv_obj_set_style_pad_row(contain, IMG_CONT_ROW_SPACE, 0);     // 设置行间距
//     lv_obj_clear_flag(contain, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
//     lv_obj_set_scroll_dir(contain, LV_DIR_VER);

//     lv_obj_set_style_pad_all(contain, 0, 0);                  // 设置所有内边距为0
//     lv_obj_set_style_base_dir(contain, LV_BASE_DIR_LTR, 0);   // 设置基础方向为从左到右
//     lv_obj_set_flex_flow(contain, LV_FLEX_FLOW_ROW_WRAP);     // 设置Flex流动方向为行包裹

//     thread_fork(DECODE_TASK_NAME, 10, 1024, 1024, &task_pid, dec_img_task, NULL);
//     fs_file = fscan(dir_path, scan_opts, 3);
//     if (!fs_file) {
//         printf("fscan err !!!");
//         video_dec_post_msg("noCard", 0);
//         return;
//     } else if (fs_file->file_number == 0) {
//         printf("file number is 0 !!");
//         video_dec_post_msg("noFile", 0);
//         total_file_num = fs_file->file_number;
//         total_file_page  = ceil((float)total_file_num / ONE_PAGE_MAX_NUM);
//         dec_list_tol_page(total_file_page); //保存总页数在结构体
//         dec_list_file_num(total_file_num); //保存文件总数在结构体
//         line = 0;
//     } else {
//         total_file_num = fs_file->file_number;
//         total_file_page  = ceil((float)total_file_num / ONE_PAGE_MAX_NUM);
//         dec_list_tol_page(total_file_page); //保存总页数在结构体
//         dec_list_file_num(total_file_num); //保存文件总数在结构体
//         printf("total file:%d total page: %d\n", total_file_num, total_file_page);
//         printf("----%d---%s\n", __LINE__, __func__);

//         for (int i = 0; i < IMG_BUF_NUM; i++) {
//             printf("----%d---%s\n", __LINE__, __func__);
//             u32 size = IMG_W * IMG_H * 2;
//             img_buf_list[i] = malloc(size);
//             if (img_buf_list[i] == NULL) {
//                 printf("img_buf_list[%d] malloc fail \n", i);
//                 break;
//             }
//             printf("----%d---%s\n", __LINE__, __func__);
//             memset(img_buf_list[i], 0x00, size);
//             image_dsc_list[i].header.always_zero = 0;
//             image_dsc_list[i].header.w = IMG_W;
//             image_dsc_list[i].header.h = IMG_H;
//             image_dsc_list[i].data_size = IMG_W * IMG_H * 2;
//             image_dsc_list[i].header.cf = LV_IMG_CF_TRUE_COLOR;
//             image_dsc_list[i].data = img_buf_list[i];
//         }

//         if (to_play_video_page) {
//             cur_page = to_play_video_page > total_file_page ? total_file_page : to_play_video_page;
//             dec_list_cur_page(cur_page); //保存当前页数在结构体
//             create_page(cur_page);
//             //文件删除后需要判断一下滚动条值是c过当前最大值
//             reset_scroll_and_line(contain);

//             lv_obj_scroll_to_y(contain, cur_scroll_val, LV_ANIM_OFF);
//             start = line * 3  + (cur_page - 1) * ONE_PAGE_MAX_NUM;
//             remain = create_num + (cur_page - 1) * ONE_PAGE_MAX_NUM - start;
//             remain = remain > 9 ? 9 : remain;
//             end = start + remain;
//             update_img_text(start, end, 0);
//             to_play_video_page = 0;
//         } else {
//             printf("----%d---%s\n", __LINE__, __func__);
//             cur_page = 1;
//             line = 0;
//             last_line = 0;
//             create_page(cur_page);
//             start = line * 3  + (cur_page - 1) * ONE_PAGE_MAX_NUM;
//             remain = create_num + (cur_page - 1) * ONE_PAGE_MAX_NUM - start;
//             remain = remain > 9 ? 9 : remain;
//             end = start + remain;
//             update_img_text(start, end, 0);
//         }
//         extern void focus_video_file(void);
//         focus_video_file();
//     }
//     printf("----%d---%s\n", __LINE__, __func__);

//     send_msg2file_num();
// }

// void video_file_screen_unload(void)
// {
//     if (deleting_flag) {
//         to_play_video_page = cur_page;
//         lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//         if (!ui_scr) {
//             return;
//         }
//         lv_obj_t *contain = lv_obj_get_child(ui_scr->video_file, 3);
//         cur_scroll_val = lv_obj_get_scroll_y(contain);

//         if (lv_obj_is_valid(ui_scr->video_file_view_3)) {
//             lv_obj_clean(ui_scr->video_file_view_3);
//         }
//         deleting_flag = 0;
//     }

//     int msg = 1;
//     os_taskq_post_type(DECODE_TASK_NAME, Q_USER, 1, &msg);
//     thread_kill(&task_pid, KILL_WAIT);
//     task_pid = 0;

//     if (fs_file) {
//         fscan_release(fs_file);
//         fs_file = NULL;
//     }
//     for (int i = 0; i < IMG_BUF_NUM; i++) {
//         if (img_buf_list[i]) {
//             free(img_buf_list[i]);
//             img_buf_list[i] = NULL;
//         }
//     }
// }


// /**************************************************************************************************************/
// /**************************************************************************************************************/
// //取出缩略图
// static u8 *find_jpg_thumbnails(u8 *stream, int len, int *thm_len)
// {
//     u8  marker;
//     int chunk_len = 0;
//     int offset = 0;

//     if ((stream[0] != 0xFF) || (stream[1] != 0xD8)) {
//         return NULL;
//     }

//     stream += 2;
//     while (1) {
//         if (*stream++ != 0xFF) {
//             return NULL;
//         }

//         while (*stream == 0xFF) {
//             stream++;
//         }

//         marker = *stream++;
//         chunk_len = (u16)(stream[0] << 8) | stream[1];
//         if (marker == 0xE1) {
//             stream += 2;
//             while (1) {
//                 if ((stream[offset] == 0xFF) && (stream[offset + 1] == 0xD8)) {
//                     break;
//                 }

//                 if (++offset > (chunk_len - 2)) {
//                     return NULL;
//                 }
//             }

//             *thm_len = chunk_len - 2 - offset;
//             return stream + offset;
//         }
//         stream += chunk_len;
//     }

//     return NULL;
// }
// static int check_fourcc(u8 *buf, const char *fourcc)
// {
//     return memcmp(buf, fourcc, 4) == 0;
// }

// static int read_fourcc_and_size(FILE *fd, u8 *fourcc, u32 *size)
// {
//     if (fread(fourcc, 4, 1, fd) != 4) {
//         return -1;
//     }
//     if (fread(size, 4, 1, fd) != 4) {
//         return -1;
//     }
//     return 0;
// }

// //获取AVI文件的第一帧
// static u8 *get_avi_first_frame(FILE *fd, u32 *jpeg_size)
// {
//     static int read_times = 0;
//     char fourcc[4];
//     u32 size;

//     fseek(fd, 0, SEEK_SET);

//     if (read_fourcc_and_size(fd, fourcc, &size) != 0  || !check_fourcc(fourcc, "RIFF")) {
//         printf("invalid RIFF header");
//         return NULL;
//     }
//     if (read_fourcc_and_size(fd, fourcc, &size) != 0  || !check_fourcc(fourcc, "AVI ")) {
//         printf("invalid AVI header");
//         return NULL;
//     }


//     while (read_fourcc_and_size(fd, fourcc, &size) == 0) {
//         if (check_fourcc(fourcc, "LIST")) {
//             char list_type[4];
//             if (fread(list_type, 1, 4, fd) != 4) {
//                 printf("invalid LIST type\n");
//                 return NULL;
//             }
//             if (check_fourcc(list_type, "movi")) {
//                 break;
//             } else {
//                 fseek(fd, size - 4, SEEK_CUR);
//             }
//         } else {
//             fseek(fd, size, SEEK_CUR);
//         }
//     }

//     while (read_fourcc_and_size(fd, fourcc, &size) == 0) {
//         if (read_times++ > 4) {
//             //避免读太久,直接退出
//             read_times = 0;
//             break;
//         }

//         if (check_fourcc(fourcc, "00dc")) {
//             read_times = 0;
//             *jpeg_size = size;
//             u8 *jpeg_buf = malloc(size);
//             if (!jpeg_buf) {
//                 printf("jpeg_buf malloc fail\n");
//                 return NULL;
//             }
//             if (fread(jpeg_buf, size, 1, fd) != size) {
//                 printf("jpeg fread err\n");
//                 free(jpeg_buf);
//                 return NULL;
//             }
//             return jpeg_buf;
//         } else {
//             //跳过当前块
//             fseek(fd, size, SEEK_CUR);
//         }

//     }
//     printf("not found jpeg frame\n");
//     return NULL;
// }

// static u8 *get_frame_buf(const char *path, u32 *size)
// {
//     FILE *fd = NULL;
//     u8 *file_buf = NULL;
//     u32 file_len;

//     fd = fopen(path, "rb");
//     if (fd == NULL) {
//         printf("no file name : %s\n", path);
//         goto err;
//     }

//     if (strcmp(lv_fs_get_ext(path), "jpg") == 0 || strcmp(lv_fs_get_ext(path), "JPG") == 0) {
//         file_len = flen(fd);
//         file_buf = malloc(file_len);
//         if (!file_buf) {
//             printf("buf malloc err ...\n");
//             goto err;
//         }
//         if (fread(file_buf, 1, file_len, fd) != file_len) {
//             printf("read file lenth err ...\n");
//             goto err;
//         }
//     } else {
//         file_buf = get_avi_first_frame(fd, &file_len);
//         if (!file_buf) {
//             printf("get_avi_first_frame err");
//             goto err;
//         }
//     }

//     fclose(fd);

//     *size = file_len;
//     return file_buf;

// err:
//     if (fd) {
//         fclose(fd);
//     }
//     if (file_buf) {
//         free(file_buf);
//     }
//     return NULL;
// }

// static int yuyv2rgb16_dma2d(u8 *yuv_buf, u8 *rgb_buf, int width, int height)
// {
//     int err;

//     u32 in_format = JLDMA2D_FORMAT_YUV422_BT709;
//     u32 out_format = JLDMA2D_FORMAT_RGB565;
//     u32 dest_stride = width * dma2d_get_format_bpp(out_format) / 8;
//     u32 src_stride = width * dma2d_get_format_bpp(in_format) / 8;
//     err = jldma2d_format(rgb_buf, \
//                          yuv_buf, \
//                          dest_stride, \
//                          src_stride, \
//                          in_format, \
//                          out_format, \
//                          width, \
//                          height, \
//                          0, \
//                          0);
//     return err;
// }

// static void soft_uyvy_to_rgb16(u8 *uyvy, u16 *rgb, int width, int height)
// {
//     int x, y;
//     u8 u, y1, v, y2;
//     int c, d, e;
//     int r, g, b;

//     for (y = 0; y < height; y++) {
//         for (x = 0; x < width; x += 2) {
//             u  = uyvy[0];
//             y1 = uyvy[1];
//             v  = uyvy[2];
//             y2 = uyvy[3];

//             uyvy += 4;

//             c = y1 - 16;
//             d = u - 128;
//             e = v - 128;

//             r = (298 * c + 409 * e + 128) >> 8;
//             g = (298 * c - 100 * d - 208 * e + 128) >> 8;
//             b = (298 * c + 516 * d + 128) >> 8;

//             r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
//             g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
//             b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

//             rgb[0] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);

//             c = y2 - 16;
//             r = (298 * c + 409 * e + 128) >> 8;
//             g = (298 * c - 100 * d - 208 * e + 128) >> 8;
//             b = (298 * c + 516 * d + 128) >> 8;

//             r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
//             g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
//             b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

//             rgb[1] = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);

//             rgb += 2;
//         }
//     }
// }

// static void on_event2(const char *name, int type, void *arg)
// {
//     OS_SEM *sem = (OS_SEM *)arg;
//     switch (type) {
//     case EVENT_FRAME_DONE:
//         if (!strncmp(name, "yuv", 3)) {
//             os_sem_post(sem);
//         }
//         break;
//     case EVENT_PREPARE_DONE:
//         printf("PREPARE %s done", name);
//         break;

//     case EVENT_START_DONE:
//         printf("START %s done", name);
//         break;

//     case EVENT_STOP_DONE:
//         printf("STOP %s done", name);
//         break;
//     case EVENT_RESET_DONE:
//         printf("RESET %s done", name);
//         break;
//     case EVENT_BW_FULL:
//     case EVENT_BUFFER_FULL:
//     case EVENT_SPEED_FULL:
//     case EVENT_OSD_ERR:
//     case EVENT_LINE_ERR:
//         printf("err %s ", name);
//         break;
//     }

// }

// static int jpeg2yuv_pipeline_init(struct video_format *f)
// {
//     pipe_filter_t *jpeg_dec_filter, *imc_filter, *rep_filter, *yuv_filter, *virtual_filter;
//     os_sem_create(&sem, 0);
//     pipe_core = pipeline_init(on_event2, &sem);
//     if (!pipe_core) {
//         printf("pipeline init err\n");
//         return -1;
//     }


//     char *source_name = plugin_factory_find("virtual");
//     pipe_core->channel = plugin_source_to_channel(source_name);
//     virtual_filter = pipeline_filter_add(pipe_core, source_name);
//     jpeg_dec_filter = pipeline_filter_add(pipe_core, plugin_factory_find("jpeg_dec"));
//     rep_filter = pipeline_filter_add(pipe_core, "rep1");
//     imc_filter = pipeline_filter_add(pipe_core, "imc3");
//     yuv_filter = pipeline_filter_add(pipe_core, plugin_factory_find("yuv"));

//     pipeline_param_set(pipe_core, NULL, PIPELINE_SET_FORMAT, f);

//     int out_format = FORMAT_YUV422_UYVY;
//     pipeline_param_set(pipe_core, NULL, PIPELINE_SET_SINK_OUT_FORMAT, (int)&out_format);

//     int line_cnt = 16;
//     pipeline_param_set(pipe_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

//     pipeline_filter_link(virtual_filter, jpeg_dec_filter);

//     pipeline_filter_link(jpeg_dec_filter, rep_filter);

//     pipeline_filter_link(rep_filter, imc_filter);

//     pipeline_filter_link(imc_filter, yuv_filter);

//     pipeline_prepare(pipe_core);

//     pipeline_start(pipe_core);
// }

// static void jpeg2yuv_pipeline_uninit(void)
// {
//     if (!pipe_core) {
//         return;
//     }

//     pipeline_stop(pipe_core);

//     pipeline_reset(pipe_core);

//     pipeline_uninit(pipe_core);

//     os_sem_del(&sem, 0);
//     pipe_core = NULL;
// }


// static int jpeg2yuv_with_pipeline(const char *path, u8 *img_buf, int dst_w, int dst_h)
// {
//     int err = 0;
//     u8 *frame_buf = NULL;
//     int frame_len;
//     u8 *dec_buf = NULL;
//     int dec_len;
//     u8 *yuv_buf;
//     static int last_width, last_height, last_format;

//     if (pipeline_state == PIPELINE_EXIT) {
//         return 0;
//     }

//     frame_buf = get_frame_buf(path, &frame_len);
//     if (!frame_buf) {
//         printf("get decode data fail");
//         err = -EFAULT;
//         goto exit;
//     }

//     //缩略图
//     dec_buf = find_jpg_thumbnails(frame_buf, frame_len, &dec_len);
//     if (!dec_buf) {
//         dec_buf = frame_buf;
//         dec_len = frame_len;
//     }

//     struct jpeg_image_info info = {0};
//     struct video_format f  = {0};
//     int fmt;
//     info.input.data.buf = dec_buf;
//     info.input.data.len = dec_len;
//     err = jpeg_decode_image_info(&info);
//     if (err) {
//         printf("jpeg_decode_image_info err %s\n", path);
//         goto exit;
//     }
//     printf("thumb jpeg info: %d x %d len=%d\n", info.width, info.height, dec_len);
//     switch (info.sample_fmt) {
//     case JPG_SAMP_FMT_YUV444:
//         fmt = VIDEO_PIX_FMT_YUV444;
//         break;
//     case JPG_SAMP_FMT_YUV422:
//         fmt = VIDEO_PIX_FMT_YUV422;
//         break;
//     case JPG_SAMP_FMT_YUV420:
//         fmt = VIDEO_PIX_FMT_YUV420;
//         break;
//     default:
//         printf("err fmt\n");
//         break;
//     }
//     f.src_width = info.width;
//     f.src_height = info.height;
//     f.win.width = dst_w;
//     f.win.height = dst_h;
//     f.type = VIDEO_BUF_TYPE_VIDEO_PLAY;
//     f.pixelformat = VIDEO_PIX_FMT_JPEG | fmt;
//     f.private_data = "fb5";

//     if ((last_height != info.height) || (last_width != info.width)
//         || (last_format != fmt) || (pipeline_state == PIPELINE_STOP)) {

//         jpeg2yuv_pipeline_uninit();
//         jpeg2yuv_pipeline_init(&f);
//     }
//     pipeline_state = PIPELINE_RUNING;

//     last_width = info.width;
//     last_height = info.height;
//     last_format = fmt;

//     //JPEG
//     struct video_cap_buffer buffer ;
//     buffer.size = dec_len;
//     buffer.buf = dec_buf;
//     pipeline_param_set(pipe_core, NULL, VIDIOC_RDBUF, &buffer);

//     err = os_sem_pend(&sem, 200);
//     if (err) {
//         log_e("jpeg2yuv timeout\n");
//         goto exit;
//     }
//     printf("jpeg2yuv ok\n");

//     //获取YUV
//     pipeline_param_get(pipe_core, NULL, PIPELINE_GET_YUV_BUF, &yuv_buf);
//     if (!yuv_buf) {
//         printf("get yuv buf err\n");
//         err = -EFAULT;
//         goto exit;
//     }

// #if USE_DMA2D_CONVERT
//     yuyv2rgb16_dma2d(yuv_buf, img_buf, dst_w, dst_h);
// #else
//     soft_uyvy_to_rgb16(yuv_buf, img_buf, dst_w, dst_h);
// #endif

// exit:
//     if (err) {
//         memset(img_buf, 0x00, dst_w * dst_h * 2);
//     }
//     if (frame_buf) {
//         free(frame_buf);
//         frame_buf = NULL;
//     }
//     return err;
// }

// /* video_dir页面的按键事件回调处理 */
// int video_dir_key_handler(struct key_event *key)
// {
//     printf("---->%s()----->key action: %d, value: %d\n", __func__, key->action, key->value);
//     switch (key->action) {
//     case KEY_EVENT_CLICK:
//         switch (key->value) {
//         case KEY_MODE: { //mode键返回video_rec页面
//             video_dir_thumb_task_stop();
//             gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_REC);
//             if (screen == NULL) {
//                 printf("[chili]: %s %d\n", __func__, __LINE__);
//                 screen = gui_scr_create(GUI_SCREEN_VIDEO_REC, "video_rec", guider_ui.video_rec, (gui_scr_setup_cb_t)setup_scr_video_rec, (gui_scr_unload_cb_t)unload_scr_video_rec);
//             }
//             ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
//         }
//         break;
//         default:
//             break;
//         }
//         break;
//     default:
//         break;
//     }

//     return 0;  //按键消息不传到792 app_core
// }
// REGISTER_UI_KEY_EVENT_HANDLER(GUI_SCREEN_VIDEO_DIR)
// .key_onchange = video_dir_key_handler,
// };


// static int file_idx = 0;
// static u8 dec_menu = 0;
// void enter_dec_setting_menu(void)
// {
//     dec_menu = 1;

//     extern int get_focused_file(void);
//     file_idx = get_focused_file();  //获取当前聚焦的录像文件
//     printf(">>>>>%s----->file idx: %d\n", __func__, file_idx);
//     lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//     if (!ui_scr) {
//         return;
//     }
//     //隐藏九宫格UI
//     lv_obj_add_flag(ui_scr->video_file_view_1, LV_OBJ_FLAG_HIDDEN);
//     lv_obj_add_flag(ui_scr->video_file_view_8, LV_OBJ_FLAG_HIDDEN);
//     lv_obj_add_flag(ui_scr->video_file_view_3, LV_OBJ_FLAG_HIDDEN);

//     //显示dec设置菜单
//     lv_obj_clear_flag(ui_scr->video_file_view_menu_b, LV_OBJ_FLAG_HIDDEN);

//     //聚焦dec菜单的第一项
//     lv_group_focus_obj(ui_scr->video_file_view_del);
// }

// void exit_dec_setting_menu(void)
// {
//     lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//     if (!ui_scr) {
//         return;
//     }
//     dec_menu = 0;
//     lv_obj_add_flag(ui_scr->video_file_view_menu_b, LV_OBJ_FLAG_HIDDEN);

//     lv_obj_clear_flag(ui_scr->video_file_view_1, LV_OBJ_FLAG_HIDDEN);
//     lv_obj_clear_flag(ui_scr->video_file_view_8, LV_OBJ_FLAG_HIDDEN);
//     lv_obj_clear_flag(ui_scr->video_file_view_3, LV_OBJ_FLAG_HIDDEN);
//     printf(">>>>>%s----->file idx: %d\n", __func__, file_idx);

//     //高亮进入设置时的那个文件
//     lv_obj_t *focuse_file_obj = lv_obj_get_child(ui_scr->video_file_view_3, file_idx);
//     if (focuse_file_obj) {
//         lv_group_focus_obj(focuse_file_obj);
//     } else {
//         lv_group_focus_obj(ui_scr->video_file_view_3);
//     }
//     file_idx = 0;
// }

// int video_file_key_handler(struct key_event *key)
// {
//     printf("---->%s()----->key value: %d\n", __func__, key->value);
//     switch (key->action) {
//     case KEY_EVENT_CLICK:
//         switch (key->value) {
//         case KEY_MENU: {
//             if (get_dec_submenu_flag()) {
//                 set_dec_submenu_flag(0);
//                 break;
//             }
//             lv_ui_video_file *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_FILE);
//             if (!ui_scr) {
//                 return -1;
//             }
//             if (lv_obj_is_valid(ui_scr->video_file_view_menu_b)) {
//                 if (!dec_menu) { //进入dec设置菜单
//                     enter_dec_setting_menu();
//                 } else {  //返回九宫格页面
//                     exit_dec_setting_menu();
//                 }
//             }
//         }
//         break;
//         case KEY_MODE: { //mode键返回video_dir页面
//             if (dec_menu) {
//                 break;
//             }
//             extern void set_file_idx(int idx);
//             set_file_idx(0);
//             gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
//             if (screen == NULL) {
//                 printf("[chili]: %s %d\n", __func__, __LINE__);
//                 screen = gui_scr_create(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE,
//                                          "video_dir_landscape_mode",
//                                          guider_ui.video_dir_landscape_mode,
//                                          (gui_scr_setup_cb_t)setup_scr_video_dir_landscape_mode,
//                                          (gui_scr_unload_cb_t)unload_scr_video_dir_landscape_mode);
//             }
//             ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
//         }
//         break;
//         default:
//             break;
//         }
//         break;
//     default:
//         break;
//     }

//     return 0;
// }
// REGISTER_UI_KEY_EVENT_HANDLER(GUI_SCREEN_VIDEO_FILE)
// .key_onchange = video_file_key_handler,
// };

// int video_play_key_handler(struct key_event *key)
// {
//     printf("---->%s()----->key value: %d\n", __func__, key->value);
//     switch (key->action) {
//     case KEY_EVENT_CLICK:
//         switch (key->value) {
//         case KEY_MENU:
//             break;
//         case KEY_MODE: { //mode键返回video_file页面
//             cfun_dec_ok();
//             cfun_dec_return();

//             gui_scr_t *screen = gui_scr_get(GUI_SCREEN_VIDEO_FILE);
//             if (screen == NULL) {
//                 printf("[chili]: %s %d\n", __func__, __LINE__);
//                 screen = gui_scr_create(GUI_SCREEN_VIDEO_FILE, "video_file", guider_ui.video_file, (gui_scr_setup_cb_t)setup_scr_video_file, (gui_scr_unload_cb_t)unload_scr_video_file);
//             }
//             ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
//         }
//         break;
//         default:
//             break;
//         }
//         break;
//     default:
//         break;
//     }

//     return 0;
// }
// REGISTER_UI_KEY_EVENT_HANDLER(GUI_SCREEN_VIDEO_PLAY)
// .key_onchange = video_play_key_handler,
// };





// #endif
#endif
