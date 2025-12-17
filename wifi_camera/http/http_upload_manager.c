#include "app_config.h"

#if defined(CONFIG_NET_ENABLE)

#include "http_upload_state.h"

#include "generic/log.h"
#include "fs/fs.h"
#include "os/os_api.h"
#include "system/sys_time.h"

#include <errno.h>
#include <stdbool.h>
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern int wifi_camera_http_upload_remote_image(const char *file_path,
                                                const char *display_path,
                                                struct http_upload_state *state);
extern u8 lvgl_ui_is_suspended(void);
extern u32 timer_get_ms(void);

#ifndef CONFIG_WIFI_CAMERA_HTTP_UPLOAD_THREAD_PRIO
#define CONFIG_WIFI_CAMERA_HTTP_UPLOAD_THREAD_PRIO         22
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_UPLOAD_THREAD_STACK
#define CONFIG_WIFI_CAMERA_HTTP_UPLOAD_THREAD_STACK        (2 * 1024)
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_SCAN_INTERVAL_MS
#define CONFIG_WIFI_CAMERA_HTTP_SCAN_INTERVAL_MS           (5 * 60 * 1000U)
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN
#define CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN                  16U
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_PATH_MAX
#define CONFIG_WIFI_CAMERA_HTTP_PATH_MAX                   256U
#endif

#ifndef CONFIG_STORAGE_PATH
#define CONFIG_STORAGE_PATH                                 "storage/sd0"
#endif

#ifndef CONFIG_ROOT_PATH
#define CONFIG_ROOT_PATH                                    CONFIG_STORAGE_PATH"/C/"
#endif

#ifndef CONFIG_WIFI_CAMERA_HTTP_STATE_FILE
#define CONFIG_WIFI_CAMERA_HTTP_STATE_FILE                 CONFIG_ROOT_PATH"wearai_http_state.txt"
#endif

struct http_upload_task {
    char full_path[CONFIG_WIFI_CAMERA_HTTP_PATH_MAX];
    char display_path[CONFIG_WIFI_CAMERA_HTTP_PATH_MAX];
};

struct http_upload_manager_ctx {
    OS_MUTEX lock;
    OS_SEM sem;
    u8 lock_ready;
    u8 sem_ready;
    u8 thread_running;
    u8 initialized;
    u8 network_online;
    u8 storage_ready;
    u8 ui_busy;
    u8 scan_requested;
    u8 stop_requested;

    unsigned int scan_timer_hdl;

    struct http_upload_task queue[CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN];
    unsigned int queue_head;
    unsigned int queue_count;

    struct http_upload_state state;
};

static struct http_upload_manager_ctx s_http_mgr = {0};

static const char *const s_http_scan_paths[] = {
#ifdef CONFIG_REC_PATH_0
    CONFIG_REC_PATH_0,
#endif
#ifdef CONFIG_REC_PATH_1
    CONFIG_REC_PATH_1,
#endif
#ifdef CONFIG_REC_PATH_2
    CONFIG_REC_PATH_2,
#endif
#ifdef CONFIG_REC_PATH_4
    CONFIG_REC_PATH_4,
#endif
#ifdef CONFIG_REC_PATH_5
    CONFIG_REC_PATH_5,
#endif
};

static const size_t s_http_scan_path_count = sizeof(s_http_scan_paths) / sizeof(s_http_scan_paths[0]);

/**
 * @brief 获取管理上下文的互斥锁，必要时自动创建。
 */
static int http_upload_manager_lock(void)
{
    if (!s_http_mgr.lock_ready) {
        if (os_mutex_create(&s_http_mgr.lock)) {
            return -ENOMEM;
        }
        s_http_mgr.lock_ready = 1;
    }
    return os_mutex_pend(&s_http_mgr.lock, 0);
}

/**
 * @brief 释放管理上下文的互斥锁。
 */
static void http_upload_manager_unlock(void)
{
    if (s_http_mgr.lock_ready) {
        os_mutex_post(&s_http_mgr.lock);
    }
}

/**
 * @brief 唤醒后台线程处理任务，必要时自动创建信号量。
 */
static void http_upload_manager_notify(void)
{
    if (!s_http_mgr.sem_ready) {
        if (!os_sem_create(&s_http_mgr.sem, 0)) {
            s_http_mgr.sem_ready = 1;
        }
    }
    if (s_http_mgr.sem_ready) {
        os_sem_post(&s_http_mgr.sem);
    }
}

/**
 * @brief 等待信号量唤醒，支持超时，必要时自动创建。
 */
static int http_upload_manager_wait_sem(unsigned int timeout_ms)
{
    if (!s_http_mgr.sem_ready) {
        if (os_sem_create(&s_http_mgr.sem, 0)) {
            return -ENOMEM;
        }
        s_http_mgr.sem_ready = 1;
    }
    return os_sem_pend(&s_http_mgr.sem, timeout_ms);
}

/**
 * @brief 在持锁的情况下将任务加入环形队列，自动去重旧条目。
 */
static void http_upload_manager_queue_push_locked(const char *full_path, const char *display_path)
{
    if (!full_path || !display_path) {
        return;
    }

    for (unsigned int i = 0, idx = s_http_mgr.queue_head; i < s_http_mgr.queue_count; ++i) {
        const struct http_upload_task *task = &s_http_mgr.queue[idx];
        if (strncmp(task->display_path, display_path, sizeof(task->display_path)) == 0) {
            return;
        }
        idx = (idx + 1) % CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN;
    }

    unsigned int insert_pos;
    if (s_http_mgr.queue_count < CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN) {
        insert_pos = (s_http_mgr.queue_head + s_http_mgr.queue_count) % CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN;
        s_http_mgr.queue_count++;
    } else {
        insert_pos = s_http_mgr.queue_head;
        s_http_mgr.queue_head = (s_http_mgr.queue_head + 1) % CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN;
    }

    struct http_upload_task *slot = &s_http_mgr.queue[insert_pos];
    strncpy(slot->full_path, full_path, sizeof(slot->full_path) - 1);
    slot->full_path[sizeof(slot->full_path) - 1] = '\0';
    strncpy(slot->display_path, display_path, sizeof(slot->display_path) - 1);
    slot->display_path[sizeof(slot->display_path) - 1] = '\0';
}

/**
 * @brief 从队列头部弹出一条任务，失败时返回负值。
 */
static int http_upload_manager_queue_pop(struct http_upload_task *out_task)
{
    if (!out_task) {
        return -EINVAL;
    }

    int err = http_upload_manager_lock();
    if (err) {
        return err;
    }

    if (!s_http_mgr.queue_count) {
        http_upload_manager_unlock();
        return -ENOENT;
    }

    struct http_upload_task *task = &s_http_mgr.queue[s_http_mgr.queue_head];
    *out_task = *task;
    memset(task, 0, sizeof(*task));

    s_http_mgr.queue_head = (s_http_mgr.queue_head + 1) % CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN;
    s_http_mgr.queue_count--;

    http_upload_manager_unlock();
    return 0;
}

/**
 * @brief 将任务重新放回队列头部，用于上传失败后的重试。
 */
static void http_upload_manager_queue_requeue_front(const struct http_upload_task *task)
{
    if (!task) {
        return;
    }

    if (http_upload_manager_lock()) {
        return;
    }

    if (s_http_mgr.queue_count < CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN) {
        s_http_mgr.queue_head = (s_http_mgr.queue_head == 0)
                                ? (CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN - 1)
                                : (s_http_mgr.queue_head - 1);
        s_http_mgr.queue_count++;
    } else {
        s_http_mgr.queue_head = (s_http_mgr.queue_head == 0)
                                ? (CONFIG_WIFI_CAMERA_HTTP_QUEUE_LEN - 1)
                                : (s_http_mgr.queue_head - 1);
    }

    struct http_upload_task *slot = &s_http_mgr.queue[s_http_mgr.queue_head];
    *slot = *task;

    http_upload_manager_unlock();
}

/**
 * @brief 将全路径转换为展示路径（剥离根目录前缀）。
 */
static void http_upload_manager_make_display_path(const char *full_path,
                                                  char *out,
                                                  size_t out_len)
{
    if (!full_path || !out || !out_len) {
        return;
    }

    const char *root = CONFIG_ROOT_PATH;
    size_t root_len = strlen(root);
    if (strncmp(full_path, root, root_len) == 0) {
        strncpy(out, full_path + root_len, out_len - 1);
    } else {
        strncpy(out, full_path, out_len - 1);
    }
    out[out_len - 1] = '\0';
}

/**
 * @brief 将系统时间结构转换为 UNIX Epoch 秒。
 */
static u32 http_upload_manager_sys_time_to_epoch(const struct sys_time *t)
{
    if (!t || !t->year || !t->month || !t->day) {
        return 0;
    }

    struct tm tm_time = {0};
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
 * @brief 扫描指定目录下的 JPEG 图片并入队上传任务。
 */
static void http_upload_manager_scan_path(const char *base_path)
{
    if (!base_path) {
        return;
    }

    struct vfscan *fs = fscan(base_path, "-tJPG -sn", 5);
    if (!fs) {
        return;
    }

    FILE *file = fselect(fs, FSEL_FIRST_FILE, 0);
    unsigned int added = 0;
    while (file) {
        char namebuf[CONFIG_WIFI_CAMERA_HTTP_PATH_MAX];
        if (fget_name(file, (u8 *)namebuf, sizeof(namebuf)) > 0) {
            char full_path[CONFIG_WIFI_CAMERA_HTTP_PATH_MAX];
            snprintf(full_path, sizeof(full_path), "%s%s", base_path, namebuf);

            struct vfs_attr attr = {0};
            u32 file_mtime = 0;
            u32 file_size = 0;
            if (fget_attrs(file, &attr) == 0) {
                file_size = attr.fsize;
                file_mtime = http_upload_manager_sys_time_to_epoch(&attr.wrt_time);
            }

            if ((!file_size || !file_mtime) && full_path[0] != '\0') {
                FILE *meta_fp = fopen(full_path, "rb");
                if (meta_fp) {
                    struct vfs_attr meta_attr = {0};
                    if (fget_attrs(meta_fp, &meta_attr) == 0) {
                        if (!file_size) {
                            file_size = meta_attr.fsize;
                        }
                        if (!file_mtime) {
                            file_mtime = http_upload_manager_sys_time_to_epoch(&meta_attr.wrt_time);
                        }
                    }

                    if (!file_size) {
                        if (!fseek(meta_fp, 0, SEEK_END)) {
                            long end_pos = ftell(meta_fp);
                            if (end_pos >= 0) {
                                file_size = (u32)end_pos;
                            }
                            fseek(meta_fp, 0, SEEK_SET);
                        }
                    }
                    fclose(meta_fp);
                }
            }

            char display_path[CONFIG_WIFI_CAMERA_HTTP_PATH_MAX];
            http_upload_manager_make_display_path(full_path, display_path, sizeof(display_path));

            if (!http_upload_state_is_duplicate(&s_http_mgr.state,
                                                display_path,
                                                file_size,
                                                file_mtime)) {
                if (!http_upload_manager_lock()) {
                    http_upload_manager_queue_push_locked(full_path, display_path);
                    added++;
                    http_upload_manager_unlock();
                    http_upload_manager_notify();
                }
            }
        }

        fclose(file);
        file = fselect(fs, FSEL_NEXT_FILE, 0);
    }

    fscan_release(fs);

    if (added) {
        printf("[HTTP][MANAGER] scan %s add %u file(s)\n", base_path, added);
    } else {
        printf("[HTTP][MANAGER] scan %s no new file\n", base_path);
    }
}

/**
 * @brief 遍历预设目录列表执行文件扫描。
 */
static void http_upload_manager_perform_scan(void)
{
    if (!s_http_scan_path_count) {
        return;
    }

    if (!s_http_mgr.state.persist_loaded) {
        printf("[HTTP][MANAGER] skip scan: state not loaded (pending=%d)\n",
               s_http_mgr.state.pending_reload ? 1 : 0);
        return;
    }

    printf("[HTTP][MANAGER] perform scan, path_count=%u\n", (unsigned int)s_http_scan_path_count);
    for (size_t i = 0; i < s_http_scan_path_count; ++i) {
        http_upload_manager_scan_path(s_http_scan_paths[i]);
    }
}

/**
 * @brief 上传管理后台线程，负责调度扫描和实际上传。
 */
static void http_upload_manager_thread(void *priv)
{
    (void)priv;
    s_http_mgr.thread_running = 1;
    printf("[HTTP][MANAGER] thread started\n");
    while (!s_http_mgr.stop_requested) {
        if (!s_http_mgr.network_online || !s_http_mgr.storage_ready) {
            http_upload_manager_wait_sem(50);
            continue;
        }

        if (s_http_mgr.ui_busy || lvgl_ui_is_suspended()) {
            os_time_dly(10);
            continue;
        }

        if (s_http_mgr.scan_requested || time_lapse(&s_http_mgr.scan_timer_hdl, CONFIG_WIFI_CAMERA_HTTP_SCAN_INTERVAL_MS)) {
            s_http_mgr.scan_requested = 0;
            http_upload_manager_perform_scan();
            continue;
        }

        struct http_upload_task task = {0};
        int pop_ret = http_upload_manager_queue_pop(&task);
        if (pop_ret == -ENOENT) {
            http_upload_manager_wait_sem(100);
            continue;
        } else if (pop_ret) {
            os_time_dly(5);
            continue;
        }

        int ret = wifi_camera_http_upload_remote_image(task.full_path,
                                                       task.display_path,
                                                       &s_http_mgr.state);
        if (ret) {
            printf("[HTTP][MANAGER] upload %s fail (%d)\n", task.display_path, ret);
            http_upload_manager_queue_requeue_front(&task);
            os_time_dly(200);
        } else {
            os_time_dly(10);
        }
    }

    s_http_mgr.thread_running = 0;
    printf("[HTTP][MANAGER] thread stopped\n");
}

/**
 * @brief 主动将指定文件加入上传队列，display_path 为空时自动转换。
 */
int http_upload_manager_enqueue(const char *full_path, const char *display_path)
{
    if (!full_path) {
        return -EINVAL;
    }

    char disp_buf[CONFIG_WIFI_CAMERA_HTTP_PATH_MAX];
    if (!display_path || !display_path[0]) {
        http_upload_manager_make_display_path(full_path, disp_buf, sizeof(disp_buf));
        display_path = disp_buf;
    }

    int err = http_upload_manager_lock();
    if (err) {
        return err;
    }

    http_upload_manager_queue_push_locked(full_path, display_path);

    http_upload_manager_unlock();
    http_upload_manager_notify();
    return 0;
}

/**
 * @brief 提醒后台线程立即执行一次目录扫描。
 */
int http_upload_manager_request_scan(void)
{
    printf("[HTTP][MANAGER] request scan\n");
    if (!s_http_mgr.initialized) {
        return -EINVAL;
    }

    s_http_mgr.scan_requested = 1;
    http_upload_manager_notify();
    return 0;
}

/**
 * @brief 设置网络是否在线，在线时立即唤醒后台线程。
 */
void http_upload_manager_set_network_online(bool online)
{
    printf("[HTTP][MANAGER] set network online: %d\n", online ? 1 : 0);
    s_http_mgr.network_online = online ? 1 : 0;
    if (online) {
        http_upload_manager_notify();
    }
}

/**
 * @brief 设置存储是否就绪，准备好后通知后台线程。
 */
void http_upload_manager_set_storage_ready(bool ready)
{
    printf("[HTTP][MANAGER] set storage ready: %d\n", ready ? 1 : 0);
    if (!ready) {
        s_http_mgr.storage_ready = 0;
        http_upload_state_set_pending_reload(&s_http_mgr.state, true);
        return;
    }

    int reload_err = 0;
    bool need_reload = (!s_http_mgr.state.persist_loaded) || s_http_mgr.state.pending_reload;
    if (need_reload) {
        reload_err = http_upload_state_reload(&s_http_mgr.state);
        if (reload_err) {
            printf("[HTTP][MANAGER] state reload fail (%d)\n", reload_err);
            http_upload_state_set_pending_reload(&s_http_mgr.state, true);
            s_http_mgr.storage_ready = 0;
            return;
        }
        printf("[HTTP][MANAGER] state reload ok, record_count=%u\n", s_http_mgr.state.count);
    } else {
        printf("[HTTP][MANAGER] state already loaded, record_count=%u\n", s_http_mgr.state.count);
    }

    s_http_mgr.storage_ready = 1;
    http_upload_state_set_pending_reload(&s_http_mgr.state, false);
    http_upload_manager_notify();
}

/**
 * @brief 设置 UI 是否繁忙，空闲时可以继续上传任务。
 */
void http_upload_manager_set_ui_busy(bool busy)
{
    printf("[HTTP][MANAGER] set UI busy: %d\n", busy ? 1 : 0);
    s_http_mgr.ui_busy = busy ? 1 : 0;
    if (!busy) {
        http_upload_manager_notify();
    }
}

/**
 * @brief 初始化上传管理器并启动后台线程。
 */
int http_upload_manager_init(void)
{
    if (s_http_mgr.initialized) {
        return 0;
    }
    printf("[HTTP][MANAGER] init\n");

    memset(&s_http_mgr, 0, sizeof(s_http_mgr));

    int err = http_upload_state_init(&s_http_mgr.state, CONFIG_WIFI_CAMERA_HTTP_STATE_FILE);
    if (err) {
        printf("[HTTP][MANAGER] state init fail (%d)\n", err);
    }

    if (thread_fork("http_upload", CONFIG_WIFI_CAMERA_HTTP_UPLOAD_THREAD_PRIO,
                    CONFIG_WIFI_CAMERA_HTTP_UPLOAD_THREAD_STACK, 0,
                    NULL, http_upload_manager_thread, NULL)) {
        printf("[HTTP][MANAGER] thread start fail\n");
        return -ENOMEM;
    }

    s_http_mgr.initialized = 1;
    s_http_mgr.network_online = 0;
    s_http_mgr.storage_ready = 0;
    s_http_mgr.ui_busy = 0;
    s_http_mgr.scan_requested = 1;

    http_upload_manager_notify();
    printf("[HTTP][MANAGER] init done\n"); 
    return 0;
}

/**
 * @brief 对外接口：启动 HTTP 上传子系统。
 */
int wifi_camera_http_start(void)
{
    return http_upload_manager_init();
}

/**
 * @brief 对外接口：停止 HTTP 上传子系统。
 */
void wifi_camera_http_stop(void)
{
    s_http_mgr.stop_requested = 1;
    http_upload_manager_notify();
}

/**
 * @brief 对外接口：触发一次目录扫描操作。
 */
void wifi_camera_http_trigger_scan(void)
{
    http_upload_manager_request_scan();
}

#endif /* CONFIG_NET_ENABLE */
