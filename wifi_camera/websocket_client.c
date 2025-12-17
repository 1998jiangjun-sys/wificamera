#include "app_config.h"

#if defined(CONFIG_WIFI_CAMERA_WEBSOCKET_ENABLE) && defined(CONFIG_NET_ENABLE)

#include "websocket_client.h"

#include "web_socket/websocket_api.h"
#include "wifi/wifi_connect.h"
#include "system/includes.h"
#include "asm/cpu.h"
#include "os/os_api.h"
#include "generic/log.h"
#include <cJSON.h>

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

extern u32 sys_timer_get_ms(void);
extern u32 timer_get_ms(void);
extern int adc_get_battery_level_percent(void);
extern int adc_get_charging_state(void);

/* -------------------- 运行时参数 -------------------- */
#define WIFI_CAMERA_WS_URL_MAX_LEN        128   /* URL 最大缓存长度，包含协议/端口/路径 */
#define WIFI_CAMERA_WS_ORIGIN_MAX_LEN      64   /* HTTP Origin 默认字符串长度 */
#define WIFI_CAMERA_WS_HEART_TASK_PRIO     20   /* 心跳线程优先级，优先低于收包 */
#define WIFI_CAMERA_WS_RECV_TASK_PRIO      19   /* 收包线程优先级 */
#define WIFI_CAMERA_WS_HEART_TASK_STACK   1024  /* 心跳线程栈空间（字节） */
#define WIFI_CAMERA_WS_RECV_TASK_STACK    2048  /* 收包线程栈空间（字节） */
#define WIFI_CAMERA_WS_AUTOSTART_STACK    2048  /* 自动连接线程栈空间，需覆盖 JSON 组帧 */
#define WIFI_CAMERA_WS_HEARTBEAT_TASK_PRIO 21   /* 业务心跳线程优先级（低于协议心跳） */
#define WIFI_CAMERA_WS_HEARTBEAT_TASK_STACK 1024 /* 业务心跳线程栈空间（字节） */
#define WIFI_CAMERA_WS_HEARTBEAT_SLEEP_SLICE_MS 200U /* 心跳休眠切片，便于响应线程退出 */
#define WIFI_CAMERA_WS_NET_WAIT_MS      0U   /* 等待联网超时时间；0 表示一直等待 */
#define WIFI_CAMERA_WS_LOGIN_PAYLOAD_MAX_LEN 1024
#define WIFI_CAMERA_WS_REQUEST_REF      "w:update"
#define WIFI_CAMERA_WS_LOCATION_WIFI_MIN_COUNT          5U
#define WIFI_CAMERA_WS_LOCATION_WIFI_MAX_COUNT         10U
#define WIFI_CAMERA_WS_LOCATION_SCAN_MAX_ATTEMPTS      10
#define WIFI_CAMERA_WS_LOCATION_SCAN_WAIT_TICKS         5
#define WIFI_CAMERA_WS_LOCATION_ASYNC_SCAN_MIN_INTERVAL_MS 30000U
#define WIFI_CAMERA_WS_LOCATION_SYNC_SCAN_MIN_INTERVAL_MS 60000U
#define WIFI_CAMERA_WS_LOCATION_CACHE_MAX_AGE_MS       120000U
#define WIFI_CAMERA_WS_LOCATION_ASYNC_DEFER_AFTER_FALLBACK_MS 20000U
#define WIFI_CAMERA_WS_LOCATION_ASYNC_DEFER_AFTER_STALE_MS    10000U

#ifndef WIFI_CAMERA_WS_DOWNCHATVOICE_ACK_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_DOWNCHATVOICE_ACK_PAYLOAD_MAX_LEN       512U
#endif
#ifndef WIFI_CAMERA_WS_RESTART_ACK_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_RESTART_ACK_PAYLOAD_MAX_LEN              256U
#endif
#ifndef WIFI_CAMERA_WS_POWEROFF_ACK_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_POWEROFF_ACK_PAYLOAD_MAX_LEN             256U
#endif
#ifndef WIFI_CAMERA_WS_BATTERY_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_BATTERY_PAYLOAD_MAX_LEN                  256U
#endif
#ifndef WIFI_CAMERA_WS_SHUTDOWN_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_SHUTDOWN_PAYLOAD_MAX_LEN                 256U
#endif
#ifndef WIFI_CAMERA_WS_FIND_ACK_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_FIND_ACK_PAYLOAD_MAX_LEN                  256U
#endif
#ifndef WIFI_CAMERA_WS_FIND_ACK_IMEI
#define WIFI_CAMERA_WS_FIND_ACK_IMEI                             WIFI_CAMERA_WS_LOGIN_IMEI
#endif

/*
 * 全局 WebSocket 客户端上下文，仅维护一个会话：
 * - ws              : 底层协议栈实例（库定义的 struct websocket_struct）
 * - handlers        : 上层注册的事件/消息回调
 * - url/origin      : 运行期可修改的服务器地址与 HTTP Origin
 * - mode/timeout    : 连接模式（ws/wss）与接收超时
 * - running         : 当前会话是否已经建立
 * - lock            : 保护配置与状态的互斥量；lock_ready 标记是否已经创建
 * - starter_thread  : 自动启动线程的 PID，防止重复创建
 */
struct wifi_camera_ws_context {
    struct websocket_struct ws;
    struct wifi_camera_ws_handlers handlers;
    char url[WIFI_CAMERA_WS_URL_MAX_LEN];
    char origin[WIFI_CAMERA_WS_ORIGIN_MAX_LEN];
    enum wifi_camera_ws_mode mode;
    u32 recv_timeout_ms;
    bool running;
    u8 lock_ready;
    OS_MUTEX lock;
    int starter_thread_pid;
    int heartbeat_thread_pid;
    u32 heartbeat_interval_ms;
    int reconnect_thread_pid;
    u32 reconnect_delay_ms;
    bool auto_reconnect_enabled;
    bool manual_close;
};

static struct wifi_camera_ws_context s_ws_ctx;
static struct wifi_camera_ws_handlers s_registered_handlers;
static bool s_registered_handlers_valid;
static s64 s_ws_time_offset_ms;
static bool s_ws_time_offset_valid;
static bool s_ws_time_fallback_logged;

static int wifi_camera_ws_lock(void);
static void wifi_camera_ws_unlock(void);
static u64 wifi_camera_ws_monotonic_ms(void);

struct wifi_camera_ws_cached_scan {
    bool valid;
    size_t count;
    struct wifi_scan_ssid_info entries[WIFI_CAMERA_WS_LOCATION_WIFI_MAX_COUNT];
    u64 timestamp_ms;
};

static struct wifi_camera_ws_cached_scan s_ws_cached_scan;

struct wifi_camera_ws_scan_ratelimit {
    u64 last_async_request_ms;
    u64 last_sync_request_ms;
    u64 deferred_async_until_ms;
};

static struct wifi_camera_ws_scan_ratelimit s_ws_scan_ratelimit;

/**
 * @brief 获取当前已连接 AP 的基础信息。
 *
 * @param out_entry 输出参数，填充 SSID、MAC、信号强度等信息。
 *
 * @return 若成功取得连接信息返回 true，否则返回 false。
 */
static bool wifi_camera_ws_fill_connected_ap_entry(struct wifi_scan_ssid_info *out_entry)
{
    if (!out_entry) {
        return false;
    }

    if (!wifi_is_on()) {
        return false;
    }

    enum wifi_sta_connect_state connect_state = wifi_get_sta_connect_state();
    bool connected = false;

    switch (connect_state) {
    case WIFI_STA_CONNECT_SUCC:
    case WIFI_STA_NETWORK_STACK_DHCP_SUCC:
    case WIFI_STA_IP_GOT_IPV6_SUCC:
        connected = true;
        break;
    default:
        break;
    }

    if (!connected) {
        return false;
    }

    char ssid_buf[33] = {0};
    char pwd_buf[65] = {0};
    struct wifi_mode_info mode_info = {
        .mode = STA_MODE,
        .ssid = ssid_buf,
        .pwd = pwd_buf,
    };

    wifi_get_mode_cur_info(&mode_info);

    if (!mode_info.ssid || mode_info.ssid[0] == '\0') {
        return false;
    }

    u8 bssid[6] = {0};
    wifi_get_bssid(bssid);

    memset(out_entry, 0, sizeof(*out_entry));

    size_t ssid_len = strlen(mode_info.ssid);
    if (ssid_len >= sizeof(out_entry->ssid)) {
        ssid_len = sizeof(out_entry->ssid) - 1;
    }

    memcpy(out_entry->ssid, mode_info.ssid, ssid_len);
    out_entry->ssid[ssid_len] = '\0';
    out_entry->ssid_len = (unsigned char)ssid_len;
    memcpy(out_entry->mac_addr, bssid, sizeof(out_entry->mac_addr));
    out_entry->rssi = wifi_get_rssi();
    out_entry->channel_number = (char)wifi_get_channel();
    out_entry->auth_mode = WIFI_AUTH_MODE_OPEN;

    return true;
}

/**
 * @brief 将扫描得到的热点列表写入本地缓存。
 *
 * @param entries 扫描结果数组。
 * @param count   数组元素数量。
 */
static void wifi_camera_ws_cache_store(const struct wifi_scan_ssid_info *entries, size_t count)
{
    if (!entries || !count) {
        return;
    }

    size_t copy = count > WIFI_CAMERA_WS_LOCATION_WIFI_MAX_COUNT ? WIFI_CAMERA_WS_LOCATION_WIFI_MAX_COUNT : count;

    if (!wifi_camera_ws_lock()) {
        memcpy(s_ws_cached_scan.entries, entries, copy * sizeof(*entries));
        s_ws_cached_scan.count = copy;
        s_ws_cached_scan.valid = true;
        s_ws_cached_scan.timestamp_ms = wifi_camera_ws_monotonic_ms();
        wifi_camera_ws_unlock();
    }
}

/**
 * @brief 从本地缓存读取热点列表。
 *
 * @param out_entries     输出数组指针。
 * @param max_count       输出数组的最大容量。
 * @param out_timestamp_ms 返回缓存时间戳，可为 NULL。
 *
 * @return 成功复制的热点数量。
 */
static size_t wifi_camera_ws_cache_fetch(struct wifi_scan_ssid_info *out_entries,
                                         size_t max_count,
                                         u64 *out_timestamp_ms)
{
    if (!out_entries || !max_count) {
        return 0;
    }

    size_t copy = 0;
    if (out_timestamp_ms) {
        *out_timestamp_ms = 0;
    }
    if (!wifi_camera_ws_lock()) {
        if (s_ws_cached_scan.valid && s_ws_cached_scan.count) {
            copy = s_ws_cached_scan.count > max_count ? max_count : s_ws_cached_scan.count;
            memcpy(out_entries, s_ws_cached_scan.entries, copy * sizeof(*out_entries));
            if (out_timestamp_ms) {
                *out_timestamp_ms = s_ws_cached_scan.timestamp_ms;
            }
        }
        wifi_camera_ws_unlock();
    }
    return copy;
}

/**
 * @brief 设置异步扫描的延迟执行时间。
 *
 * @param now_ms   当前单调计时，单位毫秒。
 * @param delay_ms 延迟的时间长度，0 表示不延迟。
 */
static void wifi_camera_ws_scan_async_set_defer(u64 now_ms, u32 delay_ms)
{
    if (!delay_ms) {
        return;
    }

    u64 target = now_ms + delay_ms;

    if (!wifi_camera_ws_lock()) {
        s_ws_scan_ratelimit.deferred_async_until_ms = target;
        wifi_camera_ws_unlock();
    }
}

/**
 * @brief 判断异步扫描是否满足节流条件。
 *
 * @param force        是否强制放行。
 * @param out_wait_ms  若未放行返回剩余等待时间，单位毫秒。
 *
 * @return true 表示可立即执行，false 表示需要等待。
 */
static bool wifi_camera_ws_scan_async_acquire(bool force, u32 *out_wait_ms)
{
    bool allowed = false;
    u32 remaining = 0;
    u64 now = wifi_camera_ws_monotonic_ms();

    if (!wifi_camera_ws_lock()) {
        u64 defer_until = s_ws_scan_ratelimit.deferred_async_until_ms;

        if (!force && defer_until && defer_until > now) {
            remaining = (u32)(defer_until - now);
        } else {
            if (defer_until && defer_until <= now) {
                s_ws_scan_ratelimit.deferred_async_until_ms = 0;
            }
            if (force || !s_ws_scan_ratelimit.last_async_request_ms ||
                now - s_ws_scan_ratelimit.last_async_request_ms >= WIFI_CAMERA_WS_LOCATION_ASYNC_SCAN_MIN_INTERVAL_MS) {
                s_ws_scan_ratelimit.last_async_request_ms = now;
                allowed = true;
            } else {
                u64 next_allowed = s_ws_scan_ratelimit.last_async_request_ms + WIFI_CAMERA_WS_LOCATION_ASYNC_SCAN_MIN_INTERVAL_MS;
                if (next_allowed > now) {
                    remaining = (u32)(next_allowed - now);
                }
            }
        }
        wifi_camera_ws_unlock();
    }

    if (out_wait_ms) {
        *out_wait_ms = allowed ? 0 : remaining;
    }
    return allowed;
}

/**
 * @brief 判断同步扫描是否满足节流条件。
 *
 * @param force        是否强制放行。
 * @param out_wait_ms  若未放行返回剩余等待时间，单位毫秒。
 *
 * @return true 表示可立即执行，false 表示需要等待。
 */
static bool wifi_camera_ws_scan_sync_acquire(bool force, u32 *out_wait_ms)
{
    bool allowed = false;
    u32 remaining = 0;
    u64 now = wifi_camera_ws_monotonic_ms();

    if (!wifi_camera_ws_lock()) {
        u64 last = s_ws_scan_ratelimit.last_sync_request_ms;
        if (force || !last || now - last >= WIFI_CAMERA_WS_LOCATION_SYNC_SCAN_MIN_INTERVAL_MS) {
            s_ws_scan_ratelimit.last_sync_request_ms = now;
            allowed = true;
        } else {
            u64 next_allowed = last + WIFI_CAMERA_WS_LOCATION_SYNC_SCAN_MIN_INTERVAL_MS;
            if (next_allowed > now) {
                remaining = (u32)(next_allowed - now);
            }
        }
        wifi_camera_ws_unlock();
    }

    if (out_wait_ms) {
        *out_wait_ms = allowed ? 0 : remaining;
    }
    return allowed;
}

/**
 * @brief 将热点扫描结果追加到 JSON 数组中。
 *
 * @param wifi_array    JSON 数组对象指针。
 * @param entries       扫描结果数组。
 * @param count         数组元素数量。
 * @param out_appended  返回实际追加的热点数量，可为 NULL。
 *
 * @return 成功返回 0，失败返回负值错误码。
 */
static int wifi_camera_ws_append_wifi_entries(cJSON *wifi_array,
                                              const struct wifi_scan_ssid_info *entries,
                                              size_t count,
                                              size_t *out_appended)
{
    if (!wifi_array || !entries || !count) {
        if (out_appended) {
            *out_appended = 0;
        }
        return -EINVAL;
    }

    size_t appended = 0;
    for (size_t i = 0; i < count && appended < WIFI_CAMERA_WS_LOCATION_WIFI_MAX_COUNT; ++i) {
        const struct wifi_scan_ssid_info *info = &entries[i];
        char mac_buf[18];

        snprintf(mac_buf,
                 sizeof(mac_buf),
                 "%02x:%02x:%02x:%02x:%02x:%02x",
                 info->mac_addr[0],
                 info->mac_addr[1],
                 info->mac_addr[2],
                 info->mac_addr[3],
                 info->mac_addr[4],
                 info->mac_addr[5]);

        const char *ssid = (info->ssid_len > 0 && info->ssid[0] != '\0') ? info->ssid : "(hidden)";

        cJSON *entry = cJSON_CreateObject();
        if (!entry) {
            if (out_appended) {
                *out_appended = appended;
            }
            return -ENOMEM;
        }

        if (!cJSON_AddStringToObject(entry, "ssid", ssid) ||
            !cJSON_AddNumberToObject(entry, "signal", (double)info->rssi) ||
            !cJSON_AddStringToObject(entry, "mac", mac_buf)) {
            cJSON_Delete(entry);
            if (out_appended) {
                *out_appended = appended;
            }
            return -ENOMEM;
        }

        cJSON_AddItemToArray(wifi_array, entry);
        appended++;
    }

    if (out_appended) {
        *out_appended = appended;
    }
    return appended ? 0 : -ENODATA;
}

static int wifi_camera_ws_send_login_message(void);
static int wifi_camera_ws_build_login_json(char *buf, size_t len, size_t *out_len);
static int wifi_camera_ws_send_heartbeat_message(void);
static int wifi_camera_ws_build_heartbeat_json(char *buf, size_t len, size_t *out_len);
static void wifi_camera_ws_heartbeat_thread(void *priv);
static int wifi_camera_ws_start_heartbeat_thread(void);
static void wifi_camera_ws_stop_heartbeat_thread(void);
static u64 wifi_camera_ws_monotonic_ms(void);
static u64 wifi_camera_ws_current_timestamp_ms(void);
static int wifi_camera_ws_build_request_envelope(const char *type,
                                                 const char *ref,
                                                 u32 ident,
                                                 u64 timestamp,
                                                 cJSON *data,
                                                 cJSON **out_root);
static u32 wifi_camera_ws_generate_login_ident(void);
static u32 wifi_camera_ws_get_heartbeat_interval_ms(void);
static void wifi_camera_ws_sleep_ms_interruptible(u32 ms);
static u32 wifi_camera_ws_get_reconnect_delay_ms(void);
static void wifi_camera_ws_reconnect_thread(void *priv);
static void wifi_camera_ws_stop_reconnect_thread(void);
static int wifi_camera_ws_schedule_reconnect(int reason);
static int wifi_camera_ws_build_location_json(enum wifi_camera_ws_location_trigger trigger,
                                              u32 request_ident,
                                              char *buf,
                                              size_t len,
                                              size_t *out_len);
static int wifi_camera_ws_build_make_friend_json(char *buf,
                                                 size_t len,
                                                 size_t *out_len);
static int wifi_camera_ws_collect_wifi_scan(cJSON *wifi_array, size_t *out_count);
static int wifi_camera_ws_scan_result_compare(const void *lhs, const void *rhs);
static int wifi_camera_ws_build_downchatvoice_ack_json(u32 request_ident,
                                                       u64 request_timestamp_ms,
                                                       char *buf,
                                                       size_t len,
                                                       size_t *out_len);
static int wifi_camera_ws_build_poweroff_ack_json(u32 request_ident,
                                                  u64 request_timestamp_ms,
                                                  char *buf,
                                                  size_t len,
                                                  size_t *out_len);
static int wifi_camera_ws_build_shutdown_json(char *buf,
                                              size_t len,
                                              size_t *out_len);

/**
 * @brief 生成登录/心跳请求的 ident 字段。
 *
 * @details ident 是服务器用于区分请求的流水号。这里利用 `rand32()` 与毫秒级
 *          系统时基做异或，既保证足够的随机性，又能降低多设备同时上线时的碰撞概率。
 *          最终结果限定为 6 位十进制整数（100000-999999）。
 *
 * @return u32 介于 100000~999999 的随机 ident 值。
 */
static u32 wifi_camera_ws_generate_login_ident(void)
{
    u32 random_val = rand32();

    /* 混入系统时基，增加并发登录时的离散性 */
    random_val ^= sys_timer_get_ms();

    random_val %= 900000U;

    return random_val + 100000U;
}

/**
 * @brief 获取当前时间的毫秒级 Unix 时间戳。
 *
 * @details 优先从 `gettimeofday()` 读取当前 UTC 时间，保证与服务器对时后的绝对
 *          时间一致；若该接口暂不可用，则尝试退化为 `time(NULL)` 的秒级时间，
 *          再不行时最后回退到单调递增的系统毫秒计数，并打印一次告警，避免重复刷屏。
 *
 * @return u64 自 1970-01-01 00:00:00 UTC 起的毫秒数；在所有时间源都不可用时返回
 *              单调计时值，可用于调试但不保证符合协议要求。
 */
static u64 wifi_camera_ws_current_timestamp_ms(void)
{
    u64 monotonic_now = wifi_camera_ws_monotonic_ms();

    if (s_ws_time_offset_valid) {
        s64 adjusted = (s64)monotonic_now + s_ws_time_offset_ms;
        if (adjusted > 0) {
            return (u64)adjusted;
        }
    }

    struct timeval tv;
    if (gettimeofday(&tv, NULL) == 0) {
        u64 epoch_ms = ((u64)tv.tv_sec * 1000ULL) + ((u64)tv.tv_usec / 1000ULL);
        if (epoch_ms >= 946684800000ULL) {
            s_ws_time_offset_ms = (s64)epoch_ms - (s64)monotonic_now;
            s_ws_time_offset_valid = true;
            s_ws_time_fallback_logged = false;
            return epoch_ms;
        }
    }

    time_t seconds = time(NULL);
    if (seconds > 0) {
        u64 epoch_ms = (u64)seconds * 1000ULL;
        if (epoch_ms >= 946684800000ULL) {
            s_ws_time_offset_ms = (s64)epoch_ms - (s64)monotonic_now;
            s_ws_time_offset_valid = true;
            s_ws_time_fallback_logged = false;
            return epoch_ms;
        }
    }

    if (!s_ws_time_fallback_logged) {
        printf("[WS][TIME] realtime source unavailable, using monotonic counter\n");
        s_ws_time_fallback_logged = true;
    }

    return monotonic_now;
}

/**
 * @brief 根据服务端时间修正本地时间偏移。
 *
 * @param server_timestamp_ms 服务端返回的毫秒级时间戳。
 */
void wifi_camera_ws_update_remote_timestamp(u64 server_timestamp_ms)
{
    if (server_timestamp_ms < 946684800000ULL) {
        return;
    }

    u64 monotonic_now = wifi_camera_ws_monotonic_ms();
    s_ws_time_offset_ms = (s64)server_timestamp_ms - (s64)monotonic_now;
    s_ws_time_offset_valid = true;
    s_ws_time_fallback_logged = false;

    printf("[WS][TIME] synced offset=%lld ms (server=%" PRIu64 ")\n",
           (long long)s_ws_time_offset_ms,
           server_timestamp_ms);
}

/**
 * @brief 按统一格式构建 WebSocket 请求 envelope。
 *
 * @param type      顶层消息类型（如 "login"、"heartbeat"）。
 * @param ref       服务器路由引用字符串，可为空。
 * @param ident     6 位请求序列号，需保证非 0。
 * @param timestamp 毫秒级时间戳，同一请求的 data 与 envelope 需保持一致。
 * @param data      已填充好的数据对象，函数成功时会转移其所有权。
 * @param out_root  输出参数，返回构建完成的 cJSON 根节点。
 *
 * @return 成功返回 0；参数非法或内存不足时返回负值错误码。
 */
static int wifi_camera_ws_build_request_envelope(const char *type,
                                                 const char *ref,
                                                 u32 ident,
                                                 u64 timestamp,
                                                 cJSON *data,
                                                 cJSON **out_root)
{
    if (!type || !data || !out_root || ident == 0 || timestamp == 0) {
        if (data) {
            cJSON_Delete(data);
        }
        return -EINVAL;
    }

    int ret = -ENOMEM;
    cJSON *root = cJSON_CreateObject();
    bool data_attached = false;

    if (!root) {
        cJSON_Delete(data);
        return -ENOMEM;
    }

    if (!cJSON_AddStringToObject(root, "type", type)) {
        goto fail;
    }
    if (!cJSON_AddNumberToObject(root, "ident", (double)ident)) {
        goto fail;
    }
    if (ref && !cJSON_AddStringToObject(root, "ref", ref)) {
        goto fail;
    }
    if (!cJSON_AddStringToObject(root, "imei", WIFI_CAMERA_WS_LOGIN_IMEI)) {
        goto fail;
    }

    const char *extend_token = WIFI_CAMERA_WS_LOGIN_EXTEND_TOKEN;
    if (extend_token) {
        if (strcmp(extend_token, "null") == 0) {
            if (!cJSON_AddNullToObject(root, "extend")) {
                goto fail;
            }
        } else {
            cJSON *extend_obj = cJSON_Parse(extend_token);
            if (extend_obj) {
                cJSON_AddItemToObject(root, "extend", extend_obj);
            } else if (!cJSON_AddStringToObject(root, "extend", extend_token)) {
                goto fail;
            }
        }
    }

    if (!cJSON_AddNumberToObject(root, "timestamp", (double)timestamp)) {
        goto fail;
    }
    if (!cJSON_AddStringToObject(root, "deviceModel", WIFI_CAMERA_WS_DEVICE_MODEL)) {
        goto fail;
    }

    cJSON_AddItemToObject(root, "data", data);
    data_attached = true;

    *out_root = root;
    return 0;

fail:
    if (!data_attached) {
        cJSON_Delete(data);
    }
    cJSON_Delete(root);
    return ret;
}

/**
 * @brief 构建查找设备回复报文的 JSON。
 *
 * @param request_ident        请求方提供的 ident，0 时自动生成。
 * @param request_timestamp_ms 请求方携带的时间戳，0 时使用当前时间。
 * @param buf                  预分配的输出缓冲区。
 * @param len                  缓冲区长度。
 * @param out_len              返回实际填充的长度。
 *
 * @return 0 表示成功，负值表示失败原因。
 */
static int wifi_camera_ws_build_find_ack_json(u32 request_ident,
                                              u64 request_timestamp_ms,
                                              char *buf,
                                              size_t len,
                                              size_t *out_len)
{
    if (!buf || !out_len) {
        return -EINVAL;
    }

    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    u64 timestamp = request_timestamp_ms ? request_timestamp_ms : wifi_camera_ws_current_timestamp_ms();

    if (!cJSON_AddStringToObject(data, "type", "find") ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_FIND_ACK_IMEI) ||
        !cJSON_AddNumberToObject(data, "timestamp", (double)timestamp)) {
        cJSON_Delete(data);
        return -ENOMEM;
    }

    u32 ident = request_ident ? request_ident : wifi_camera_ws_generate_login_ident();
    int ret = wifi_camera_ws_build_request_envelope("find",
                                                    "w:reply",
                                                    ident,
                                                    timestamp,
                                                    data,
                                                    &root);
    if (ret) {
        return ret;
    }
    data = NULL;

    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            cJSON_Delete(root);
            return -EIO;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            cJSON_Delete(root);
            return -EOVERFLOW;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    cJSON_Delete(root);
    return 0;
}

/*
 * 动态创建互斥量并上锁，确保多线程安全：
 * - 首次调用自动创建 mutex
 * - 返回 UCOS 错误码，0 代表成功
 */
static int wifi_camera_ws_lock(void)
{
    if (!s_ws_ctx.lock_ready) {
        if (os_mutex_create(&s_ws_ctx.lock)) {
            return -ENOMEM;
        }
        s_ws_ctx.lock_ready = 1;
    }
    return os_mutex_pend(&s_ws_ctx.lock, 0);
}

/**
 * @brief 释放全局互斥量，允许其他线程访问上下文。
 */
static void wifi_camera_ws_unlock(void)
{
    if (s_ws_ctx.lock_ready) {
        os_mutex_post(&s_ws_ctx.lock);
    }
}

/*
 * websocket 库收到完整帧后会回调 `_recv_cb`，在此桥接到用户注册的 on_message。
 * 若用户未注册，则简单打印帧类型与长度，方便调试。
 */
static void wifi_camera_ws_recv_adapter(u8 *buf, u32 len, u8 type)
{
    const struct wifi_camera_ws_handlers *ops = &s_ws_ctx.handlers;
    if (ops->on_message) {
        ops->on_message(buf, len, type, ops->priv);
    } else {
        printf("[WS] recv type=0x%x len=%u\n", type, len);
    }
}

/* 默认事件处理：仅打印日志，避免用户未注册回调时完全静默。 */
static void wifi_camera_ws_default_event(enum wifi_camera_ws_event event, int value, void *priv)
{
    printf("[WS] event=%d value=%d\n", event, value);
}

/*
 * 安全分发事件：
 * - 用户注册则调用用户回调
 * - 未注册时除心跳超时外，统一走默认日志，避免刷屏
 */
static void wifi_camera_ws_dispatch_event(enum wifi_camera_ws_event event, int value)
{
    if (s_ws_ctx.handlers.on_event) {
        s_ws_ctx.handlers.on_event(event, value, s_ws_ctx.handlers.priv);
    } else if (event != WIFI_CAMERA_WS_EVENT_PING_TIMEOUT) {
        wifi_camera_ws_default_event(event, value, NULL);
    }

    if (event == WIFI_CAMERA_WS_EVENT_DISCONNECTED) {
        bool should_reconnect = false;
        if (!wifi_camera_ws_lock()) {
            should_reconnect = s_ws_ctx.auto_reconnect_enabled && !s_ws_ctx.manual_close;
            wifi_camera_ws_unlock();
        }
        if (should_reconnect) {
            wifi_camera_ws_schedule_reconnect(value);
        }
    }
}

/* 枚举值到底层协议栈宏的映射。 */
/**
 * @brief 将自定义模式枚举映射为底层协议栈识别的模式值。
 *
 * @param mode 上层配置的运行模式（明文 / TLS）。
 *
 * @return char 协议栈所需的宏值。
 */
static char wifi_camera_ws_mode_to_stack(enum wifi_camera_ws_mode mode)
{
    return (mode == WIFI_CAMERA_WS_MODE_TLS) ? WEBSOCKETS_MODE : WEBSOCKET_MODE;
}



/**
 * @brief 原子化更新全局 running 标志位。
 *
 * @details 通过互斥量保护状态，只有状态发生变化时才返回 true，便于上层
 *          决定是否触发连接事件。
 *
 * @param running 目标状态。
 *
 * @return bool 若状态变化则返回 true。
 */
static bool wifi_camera_ws_set_running_flag(bool running)
{
    bool changed = false;
    if (!wifi_camera_ws_lock()) {
        if (s_ws_ctx.running != running) {
            s_ws_ctx.running = running;
            changed = true;
        }
        wifi_camera_ws_unlock();
    }
    return changed;
}

/**
 * @brief 通知上层连接已断开，并根据需要触发事件分发。
 *
 * @param reason 断开原因。
 */
static void wifi_camera_ws_notify_disconnected(int reason)
{
    if (wifi_camera_ws_set_running_flag(false)) {
        wifi_camera_ws_dispatch_event(WIFI_CAMERA_WS_EVENT_DISCONNECTED, reason);
    }
}

/*
 * 将第三方 websocket 库的钩子函数注册到 `ws` 结构中，同时设置底层运行模式。
 */
static void wifi_camera_ws_register_stack(struct websocket_struct *ws, enum wifi_camera_ws_mode mode)
{
    printf("[WS] register stack, mode=%s\n", (mode == WIFI_CAMERA_WS_MODE_TLS) ? "wss" : "ws");
    memset(ws, 0, sizeof(*ws));
    ws->_init         = websockets_client_socket_init;
    ws->_exit         = websockets_client_socket_exit;
    ws->_handshack    = webcockets_client_socket_handshack;
    ws->_send         = websockets_client_socket_send;
    ws->_recv_thread  = websockets_client_socket_recv_thread;
    ws->_heart_thread = websockets_client_socket_heart_thread;
    ws->_recv_cb      = wifi_camera_ws_recv_adapter;
    ws->_recv         = NULL;
    ws->websocket_mode = wifi_camera_ws_mode_to_stack(mode);
}

/**
 * @brief 根据调用方提供的配置或已注册的默认回调刷新处理函数。
 *
 * @param config 当前初始化使用的配置指针，可为 NULL。
 */
static void wifi_camera_ws_apply_handlers(const struct wifi_camera_ws_config *config)
{
    if (config && config->handlers) {
        s_ws_ctx.handlers = *config->handlers;
    } else if (s_registered_handlers_valid) {
        s_ws_ctx.handlers = s_registered_handlers;
    } else {
        memset(&s_ws_ctx.handlers, 0, sizeof(s_ws_ctx.handlers));
    }
}

/**
 * @brief 启动业务心跳线程，按设定间隔发送心跳。
 *
 * @return 0 表示成功，否则返回错误码。
 */
static int wifi_camera_ws_start_heartbeat_thread(void)
{
    int ret = wifi_camera_ws_lock();
    if (ret) {
        return ret;
    }
    if (s_ws_ctx.heartbeat_thread_pid) {
        wifi_camera_ws_unlock();
        return 0;
    }
    wifi_camera_ws_unlock();

    ret = thread_fork("ws_cli_hb",
                      WIFI_CAMERA_WS_HEARTBEAT_TASK_PRIO,
                      WIFI_CAMERA_WS_HEARTBEAT_TASK_STACK,
                      0,
                      &s_ws_ctx.heartbeat_thread_pid,
                      wifi_camera_ws_heartbeat_thread,
                      NULL);
    if (ret) {
        printf("[WS][HB] thread start failed:%d\n", ret);
        s_ws_ctx.heartbeat_thread_pid = 0;
        return ret;
    }
    printf("[WS][HB] thread started pid=%d\n", s_ws_ctx.heartbeat_thread_pid);
    return 0;
}

/**
 * @brief 停止心跳线程，确保资源释放。
 */
static void wifi_camera_ws_stop_heartbeat_thread(void)
{
    if (!s_ws_ctx.heartbeat_thread_pid) {
        return;
    }
    thread_kill(&s_ws_ctx.heartbeat_thread_pid, KILL_REQ);
    thread_kill(&s_ws_ctx.heartbeat_thread_pid, KILL_WAIT);
    s_ws_ctx.heartbeat_thread_pid = 0;
    printf("[WS][HB] thread stopped\n");
}

/**
 * @brief 判断服务器 URL 是否包含 ws:// 或 wss:// 前缀。
 *
 * @param url 待检测的 URL 字符串。
 *
 * @return bool true 表示已带协议头。
 */
static bool wifi_camera_ws_has_scheme(const char *url)
{
    if (!url) {
        return false;
    }
    return (strncmp(url, "ws://", 5) == 0) || (strncmp(url, "wss://", 6) == 0);
}

/*
 * 将调用者传入的配置落地到全局上下文：
 * - 无配置时使用默认 URL/Origin/超时
 * - 模式/回调在此统一更新
 */
static void wifi_camera_ws_apply_config(const struct wifi_camera_ws_config *config)
{
    const char *raw_url = (config && config->url) ? config->url : WIFI_CAMERA_WS_DEFAULT_URL;
    const char *origin = (config && config->origin) ? config->origin : WIFI_CAMERA_WS_DEFAULT_ORIGIN;
    s_ws_ctx.mode = config ? config->mode : WIFI_CAMERA_WS_MODE_PLAIN;

    if (wifi_camera_ws_has_scheme(raw_url)) {
        strncpy(s_ws_ctx.url, raw_url, sizeof(s_ws_ctx.url) - 1);
        s_ws_ctx.url[sizeof(s_ws_ctx.url) - 1] = '\0';
    } else {
        const char *prefix = (s_ws_ctx.mode == WIFI_CAMERA_WS_MODE_TLS) ? "wss://" : "ws://";
        snprintf(s_ws_ctx.url, sizeof(s_ws_ctx.url), "%s%s", prefix, raw_url);
    }

    strncpy(s_ws_ctx.origin, origin, sizeof(s_ws_ctx.origin) - 1);
    s_ws_ctx.origin[sizeof(s_ws_ctx.origin) - 1] = '\0';
    s_ws_ctx.recv_timeout_ms = (config && config->recv_timeout_ms) ? config->recv_timeout_ms : WIFI_CAMERA_WS_DEFAULT_TIMEOUT;
    s_ws_ctx.heartbeat_interval_ms = WIFI_CAMERA_WS_HEARTBEAT_INTERVAL_MS;
    s_ws_ctx.reconnect_delay_ms = WIFI_CAMERA_WS_RECONNECT_DELAY_MS;
    s_ws_ctx.auto_reconnect_enabled = (WIFI_CAMERA_WS_RECONNECT_ENABLE != 0);
    s_ws_ctx.manual_close = false;
    wifi_camera_ws_apply_handlers(config);
}

/**
 * @brief 注册或更新 WebSocket 客户端的回调处理器。
 *
 * @param handlers 新的回调集合，传入 NULL 表示清除并禁用回调。
 *
 * @return 0 表示成功，负值表示互斥量获取失败。
 */
int wifi_camera_ws_client_register_handlers(const struct wifi_camera_ws_handlers *handlers)
{
    int ret = wifi_camera_ws_lock();
    if (ret) {
        return ret;
    }

    if (handlers) {
        s_registered_handlers = *handlers;
        s_registered_handlers_valid = true;
    } else {
        memset(&s_registered_handlers, 0, sizeof(s_registered_handlers));
        s_registered_handlers_valid = false;
    }

    wifi_camera_ws_unlock();
    return 0;
}

/*
 * 启动心跳与收包线程：任一线程创建失败都需要清理现场。
 * 注意：心跳线程优先级低于收包线程，确保收包更及时。
 */
static int wifi_camera_ws_start_threads(struct websocket_struct *ws)
{
    int err = thread_fork("ws_cli_heart", WIFI_CAMERA_WS_HEART_TASK_PRIO, WIFI_CAMERA_WS_HEART_TASK_STACK, 0,
                          &ws->ping_thread_id, ws->_heart_thread, ws);
    if (err) {
        printf("[WS] heart thread start failed:%d\n", err);
        ws->ping_thread_id = 0;
        return -ECHILD;
    }

    err = thread_fork("ws_cli_recv", WIFI_CAMERA_WS_RECV_TASK_PRIO, WIFI_CAMERA_WS_RECV_TASK_STACK, 0,
                      &ws->recv_thread_id, ws->_recv_thread, ws);
    if (err) {
        printf("[WS] recv thread start failed:%d\n", err);
        thread_kill(&ws->ping_thread_id, KILL_REQ);
        thread_kill(&ws->ping_thread_id, KILL_WAIT);
        ws->recv_thread_id = 0;
        ws->ping_thread_id = 0;
        return -ECHILD;
    }
    printf("[WS] heart thread=%d recv thread=%d started\n", ws->ping_thread_id, ws->recv_thread_id);
    return 0;
}

/* 停止线程：依次发送 KILL_REQ，并等待退出，保证栈资源释放。 */
static void wifi_camera_ws_stop_threads(struct websocket_struct *ws)
{
    if (ws->ping_thread_id) {
        thread_kill(&ws->ping_thread_id, KILL_REQ);
        thread_kill(&ws->ping_thread_id, KILL_WAIT);
        ws->ping_thread_id = 0;
    }
    if (ws->recv_thread_id) {
        thread_kill(&ws->recv_thread_id, KILL_REQ);
        thread_kill(&ws->recv_thread_id, KILL_WAIT);
        ws->recv_thread_id = 0;
    }
}

/* 统一清理入口：退出线程 + 调用底层 `_exit`，用于错误回滚或主动断开。 */
static void wifi_camera_ws_client_cleanup(void)
{
    printf("[WS] cleanup connection\n");
    wifi_camera_ws_stop_heartbeat_thread();
    wifi_camera_ws_stop_threads(&s_ws_ctx.ws);
    if (s_ws_ctx.ws._exit) {
        s_ws_ctx.ws._exit(&s_ws_ctx.ws);
    }
    wifi_camera_ws_set_running_flag(false);

    bool should_schedule = false;
    if (!wifi_camera_ws_lock()) {
        should_schedule = s_ws_ctx.auto_reconnect_enabled && !s_ws_ctx.manual_close;
        wifi_camera_ws_unlock();
    }
    if (should_schedule) {
        wifi_camera_ws_schedule_reconnect(0);
    }
}

/*
 * 等待 STA 获得 IP：
 * - 轮询 wifi_get_sta_connect_state，最长等待 `timeout_ms`
 * - 失败返回 -ETIMEDOUT，用于提醒上层先连接热点
 */
static int wifi_camera_ws_wait_network(u32 timeout_ms)
{
#if defined(CONFIG_WIFI_ENABLE)
    u32 elapsed = 0;
    const u32 step = 100;
    printf("[WS] wait network (timeout=%u ms)\n", timeout_ms);
    while (1) {
        if (wifi_get_sta_connect_state() == WIFI_STA_NETWORK_STACK_DHCP_SUCC) {
            printf("[WS] network ready after %u ms\n", elapsed);
            return 0;
        }
        if (timeout_ms && elapsed >= timeout_ms) {
            printf("[WS] wait network timeout after %u ms\n", elapsed);
            return -ETIMEDOUT;
        }
        os_time_dly(10);
        elapsed += step;
    }
#else
    (void)timeout_ms;
    return 0;
#endif
}

/*
 * 对外初始化：
 * 1. 保护配置并避免重复初始化
 * 2. 落地配置、注册钩子
 * 3. 校验结构体版本、等待联网、握手
 * 4. 启动心跳/收包线程并触发“已连接”事件
 */
/**
 * @brief 在禁用 WebSocket 功能时的占位初始化函数。
 */
int wifi_camera_ws_client_init(const struct wifi_camera_ws_config *config)
{
    printf("[WS] client init requested\n");
    int ret = wifi_camera_ws_lock();
    if (ret) {
        printf("[WS] lock failed:%d\n", ret);
        return ret;
    }
    if (s_ws_ctx.running) {
        printf("[WS] already running, skip init\n");
        wifi_camera_ws_unlock();
        return 0;
    }
    wifi_camera_ws_apply_config(config);
    wifi_camera_ws_register_stack(&s_ws_ctx.ws, s_ws_ctx.mode);
    wifi_camera_ws_unlock();

    printf("[WS] config: url=%s origin=%s timeout=%u mode=%s\n",
           s_ws_ctx.url,
           s_ws_ctx.origin,
           s_ws_ctx.recv_timeout_ms ? s_ws_ctx.recv_timeout_ms : WIFI_CAMERA_WS_DEFAULT_TIMEOUT,
           (s_ws_ctx.mode == WIFI_CAMERA_WS_MODE_TLS) ? "wss" : "ws");

    if (websockets_struct_check(sizeof(struct websocket_struct)) == FALSE) {
        wifi_camera_ws_dispatch_event(WIFI_CAMERA_WS_EVENT_ERROR, -EFAULT);
        printf("[WS] struct check failed\n");
        return -EFAULT;
    }

    s_ws_ctx.ws.ip_or_url = (u8 *)s_ws_ctx.url;
    s_ws_ctx.ws.origin_str = s_ws_ctx.origin;
    s_ws_ctx.ws.recv_time_out = s_ws_ctx.recv_timeout_ms ? s_ws_ctx.recv_timeout_ms : WIFI_CAMERA_WS_DEFAULT_TIMEOUT;

    ret = wifi_camera_ws_wait_network(WIFI_CAMERA_WS_NET_WAIT_MS);
    if (ret) {
        wifi_camera_ws_dispatch_event(WIFI_CAMERA_WS_EVENT_ERROR, ret);
        printf("[WS] wait network failed:%d\n", ret);
        return ret;
    }

    if (s_ws_ctx.ws._init(&s_ws_ctx.ws) == FALSE) {
        wifi_camera_ws_dispatch_event(WIFI_CAMERA_WS_EVENT_ERROR, -EIO);
        printf("[WS] ws _init failed\n");
        return -EIO;
    }

    if (s_ws_ctx.ws._handshack(&s_ws_ctx.ws) == FALSE) {
        wifi_camera_ws_client_cleanup();
        wifi_camera_ws_dispatch_event(WIFI_CAMERA_WS_EVENT_ERROR, -ECONNREFUSED);
        printf("[WS] handshake rejected\n");
        return -ECONNREFUSED;
    }

    ret = wifi_camera_ws_start_threads(&s_ws_ctx.ws);
    if (ret) {
        wifi_camera_ws_client_cleanup();
        wifi_camera_ws_dispatch_event(WIFI_CAMERA_WS_EVENT_ERROR, ret);
        printf("[WS] start threads failed:%d\n", ret);
        return ret;
    }

    wifi_camera_ws_set_running_flag(true);
    wifi_camera_ws_stop_reconnect_thread();
    if (!wifi_camera_ws_lock()) {
        s_ws_ctx.manual_close = false;
        if (WIFI_CAMERA_WS_RECONNECT_ENABLE) {
            s_ws_ctx.auto_reconnect_enabled = true;
        }
        wifi_camera_ws_unlock();
    }

    int login_err = wifi_camera_ws_send_login_message();
    if (login_err) {
        printf("[WS] login payload send failed:%d\n", login_err);
    }

    int hb_err = wifi_camera_ws_start_heartbeat_thread();
    if (hb_err) {
        printf("[WS] heartbeat thread start failed:%d\n", hb_err);
    }

    printf("[WS] client init success\n");
    wifi_camera_ws_dispatch_event(WIFI_CAMERA_WS_EVENT_CONNECTED, 0);
    return 0;
}

/* 查询当前会话是否已经建立，常用于发送前的快速判定。 */
/**
 * @brief WebSocket 功能禁用时始终返回未运行。
 */
bool wifi_camera_ws_client_is_running(void)
{
    bool running = false;
    if (!wifi_camera_ws_lock()) {
        running = s_ws_ctx.running;
        wifi_camera_ws_unlock();
    }
    return running;
}

/*
 * 发送公共流程：
 * - 校验参数与运行状态
 * - 传递 opcode（文本/二进制/ping 等）给底层库
 */
static int wifi_camera_ws_send_common(const void *buf, size_t len, char type)
{
    if (!buf || !len) {
        return -EINVAL;
    }
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }
    int err = s_ws_ctx.ws._send(&s_ws_ctx.ws, (u8 *)buf, (int)len, type);
    if (err == FALSE) {
        wifi_camera_ws_notify_disconnected(-EIO);
        return -EIO;
    }
    return 0;
}

/**
 * @brief 获取单调递增的毫秒数，用于内部定时逻辑。
 *
 * @return u64 单调递增的毫秒计时。
 */
static u64 wifi_camera_ws_monotonic_ms(void)
{
    return (u64)sys_timer_get_ms();
}

/**
 * @brief 获取当前心跳间隔配置。
 *
 * @details 若外部未显式配置，则回退到默认宏 `WIFI_CAMERA_WS_HEARTBEAT_INTERVAL_MS`。
 *
 * @return u32 心跳间隔（毫秒）。
 */
static u32 wifi_camera_ws_get_heartbeat_interval_ms(void)
{
    u32 interval = WIFI_CAMERA_WS_HEARTBEAT_INTERVAL_MS;
    if (!wifi_camera_ws_lock()) {
        if (s_ws_ctx.heartbeat_interval_ms) {
            interval = s_ws_ctx.heartbeat_interval_ms;
        }
        wifi_camera_ws_unlock();
    }
    if (interval == 0) {
        interval = WIFI_CAMERA_WS_HEARTBEAT_INTERVAL_MS;
    }
    return interval;
}

/**
 * @brief 可被线程退出打断的休眠实现。
 *
 * @details 将长休眠拆分为小片段，以便在收到 `thread_kill_req()` 时快速响应。
 *
 * @param ms 目标休眠时长（毫秒）。
 */
static void wifi_camera_ws_sleep_ms_interruptible(u32 ms)
{
    if (ms == 0) {
        os_time_dly(1);
        return;
    }

    u32 elapsed = 0;
    while (elapsed < ms && !thread_kill_req()) {
        u32 slice = ms - elapsed;
        if (slice > WIFI_CAMERA_WS_HEARTBEAT_SLEEP_SLICE_MS) {
            slice = WIFI_CAMERA_WS_HEARTBEAT_SLEEP_SLICE_MS;
        }
        msleep(slice);
        elapsed += slice;
    }
}

/**
 * @brief 获取重连延时配置。
 *
 * @return u32 重连前的等待时间（毫秒）。
 */
static u32 wifi_camera_ws_get_reconnect_delay_ms(void)
{
    u32 delay = WIFI_CAMERA_WS_RECONNECT_DELAY_MS;
    if (!wifi_camera_ws_lock()) {
        if (s_ws_ctx.reconnect_delay_ms) {
            delay = s_ws_ctx.reconnect_delay_ms;
        }
        wifi_camera_ws_unlock();
    }
    if (delay == 0) {
        delay = WIFI_CAMERA_WS_RECONNECT_DELAY_MS;
    }
    return delay;
}

/**
 * @brief 停止重连线程，确保不会重复调度。
 */
static void wifi_camera_ws_stop_reconnect_thread(void)
{
    if (s_ws_ctx.reconnect_thread_pid) {
        thread_kill(&s_ws_ctx.reconnect_thread_pid, KILL_REQ);
        thread_kill(&s_ws_ctx.reconnect_thread_pid, KILL_WAIT);
        s_ws_ctx.reconnect_thread_pid = 0;
        printf("[WS][RC] thread stopped\n");
    }
}

/**
 * @brief 重连线程入口：等待指定延时后尝试重新发起连接。
 *
 * @param priv 断开原因，通过指针传入的整数。
 */
static void wifi_camera_ws_reconnect_thread(void *priv)
{
    int reason = (int)(intptr_t)priv;
    u32 delay_ms = wifi_camera_ws_get_reconnect_delay_ms();
    printf("[WS][RC] worker enter (reason=%d delay=%u ms)\n", reason, delay_ms);

    wifi_camera_ws_sleep_ms_interruptible(delay_ms);
    if (!thread_kill_req()) {
        bool should_reconnect = false;
        if (!wifi_camera_ws_lock()) {
            should_reconnect = s_ws_ctx.auto_reconnect_enabled && !s_ws_ctx.manual_close;
            wifi_camera_ws_unlock();
        }
        if (should_reconnect && !wifi_camera_ws_client_is_running()) {
            int err = wifi_camera_ws_client_start_default_async();
            if (err) {
                printf("[WS][RC] start default async failed:%d\n", err);
            } else {
                printf("[WS][RC] start default async triggered\n");
            }
        }
    }

    wifi_camera_ws_lock();
    s_ws_ctx.reconnect_thread_pid = 0;
    wifi_camera_ws_unlock();
    printf("[WS][RC] worker exit\n");
}

/**
 * @brief 调度重连线程，避免重复创建。
 *
 * @param reason 断开原因代码。
 *
 * @return 0 表示成功调度或无需调度，负值表示错误。
 */
static int wifi_camera_ws_schedule_reconnect(int reason)
{
    if (!WIFI_CAMERA_WS_RECONNECT_ENABLE) {
        return 0;
    }

    int ret = wifi_camera_ws_lock();
    if (ret) {
        return ret;
    }
    if (!s_ws_ctx.auto_reconnect_enabled || s_ws_ctx.manual_close) {
        wifi_camera_ws_unlock();
        return 0;
    }
    if (s_ws_ctx.reconnect_thread_pid) {
        wifi_camera_ws_unlock();
        return 0;
    }
    wifi_camera_ws_unlock();

    ret = thread_fork("ws_cli_reconn",
                      WIFI_CAMERA_WS_RECONNECT_TASK_PRIO,
                      WIFI_CAMERA_WS_RECONNECT_TASK_STACK,
                      0,
                      &s_ws_ctx.reconnect_thread_pid,
                      wifi_camera_ws_reconnect_thread,
                      (void *)(intptr_t)reason);
    if (ret) {
        printf("[WS][RC] thread start failed:%d\n", ret);
        wifi_camera_ws_lock();
        s_ws_ctx.reconnect_thread_pid = 0;
        wifi_camera_ws_unlock();
        return ret;
    }
    printf("[WS][RC] thread started pid=%d\n", s_ws_ctx.reconnect_thread_pid);
    return 0;
}

/**
 * @brief 比较两个 Wi-Fi 扫描结果的信号强度。
 *
 * @param lhs 排序回调收到的第一个元素。
 * @param rhs 排序回调收到的第二个元素。
 *
 * @return 正值表示 lhs 信号弱于 rhs，负值相反，0 表示相等。
 */
static int wifi_camera_ws_scan_result_compare(const void *lhs, const void *rhs)
{
    const struct wifi_scan_ssid_info *a = lhs;
    const struct wifi_scan_ssid_info *b = rhs;
    return (int)b->rssi - (int)a->rssi;
}

/**
 * @brief 构建语音下行确认报文的 JSON。
 *
 * @param request_ident        请求 ident，0 时自动生成。
 * @param request_timestamp_ms 请求时间戳，0 时使用当前时间。
 * @param buf                  输出缓冲区。
 * @param len                  缓冲区长度。
 * @param out_len              返回实际写入的长度。
 *
 * @return 0 表示成功，否则返回负值错误码。
 */
static int wifi_camera_ws_build_downchatvoice_ack_json(u32 request_ident,
                                                       u64 request_timestamp_ms,
                                                       char *buf,
                                                       size_t len,
                                                       size_t *out_len)
{
    if (!buf || !out_len) {
        return -EINVAL;
    }

    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    u64 timestamp = request_timestamp_ms ? request_timestamp_ms : wifi_camera_ws_current_timestamp_ms();

    if (!cJSON_AddStringToObject(data, "type", "downChatVoice") ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI) ||
        !cJSON_AddNumberToObject(data, "timestamp", (double)timestamp)) {
        cJSON_Delete(data);
        return -ENOMEM;
    }

    u32 ident = request_ident ? request_ident : wifi_camera_ws_generate_login_ident();
    int ret = wifi_camera_ws_build_request_envelope("downChatVoice",
                                                    "w:reply",
                                                    ident,
                                                    timestamp,
                                                    data,
                                                    &root);
    if (ret) {
        return ret;
    }
    data = NULL;

    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            cJSON_Delete(root);
            return -EIO;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            cJSON_Delete(root);
            return -EOVERFLOW;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    cJSON_Delete(root);
    return 0;
}

/**
 * @brief 构建重启指令的确认报文 JSON。
 *
 * @param request_ident        请求 ident，0 时自动生成。
 * @param request_timestamp_ms 请求时间戳，0 时使用当前时间。
 * @param buf                  输出缓冲区。
 * @param len                  缓冲区长度。
 * @param out_len              返回实际写入的长度。
 *
 * @return 0 表示成功，否则返回负值错误码。
 */
static int wifi_camera_ws_build_restart_ack_json(u32 request_ident,
                                                 u64 request_timestamp_ms,
                                                 char *buf,
                                                 size_t len,
                                                 size_t *out_len)
{
    if (!buf || !out_len) {
        return -EINVAL;
    }

    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    u64 timestamp = request_timestamp_ms ? request_timestamp_ms : wifi_camera_ws_current_timestamp_ms();

    if (!cJSON_AddStringToObject(data, "type", "restart") ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI) ||
        !cJSON_AddNumberToObject(data, "timestamp", (double)timestamp)) {
        cJSON_Delete(data);
        return -ENOMEM;
    }

    u32 ident = request_ident ? request_ident : wifi_camera_ws_generate_login_ident();
    int ret = wifi_camera_ws_build_request_envelope("restart",
                                                    "w:reply",
                                                    ident,
                                                    timestamp,
                                                    data,
                                                    &root);
    if (ret) {
        return ret;
    }
    data = NULL;

    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            cJSON_Delete(root);
            return -EIO;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            cJSON_Delete(root);
            return -EOVERFLOW;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    cJSON_Delete(root);
    return 0;
}

/**
 * @brief 构建关机指令的确认报文 JSON。
 *
 * @param request_ident        请求 ident，0 时自动生成。
 * @param request_timestamp_ms 请求时间戳，0 时使用当前时间。
 * @param buf                  输出缓冲区。
 * @param len                  缓冲区长度。
 * @param out_len              返回实际写入的长度。
 *
 * @return 0 表示成功，否则返回负值错误码。
 */
static int wifi_camera_ws_build_poweroff_ack_json(u32 request_ident,
                                                  u64 request_timestamp_ms,
                                                  char *buf,
                                                  size_t len,
                                                  size_t *out_len)
{
    if (!buf || !out_len) {
        return -EINVAL;
    }

    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    u64 timestamp = request_timestamp_ms ? request_timestamp_ms : wifi_camera_ws_current_timestamp_ms();

    if (!cJSON_AddStringToObject(data, "type", "powerOff") ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI) ||
        !cJSON_AddNumberToObject(data, "timestamp", (double)timestamp)) {
        cJSON_Delete(data);
        return -ENOMEM;
    }

    u32 ident = request_ident ? request_ident : wifi_camera_ws_generate_login_ident();
    int ret = wifi_camera_ws_build_request_envelope("powerOff",
                                                    "w:reply",
                                                    ident,
                                                    timestamp,
                                                    data,
                                                    &root);
    if (ret) {
        return ret;
    }
    data = NULL;

    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            cJSON_Delete(root);
            return -EIO;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            cJSON_Delete(root);
            return -EOVERFLOW;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    cJSON_Delete(root);
    return 0;
}

/**
 * @brief 向服务器请求最新的联系人列表。
 *
 * @return 0 表示发送成功；若连接未建立或构建失败则返回负值错误码。
 */
int wifi_camera_ws_send_get_chat_user_list(void)
{
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    int err = 0;
    char payload[WIFI_CAMERA_WS_GET_CHAT_USER_LIST_PAYLOAD_MAX_LEN];
    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    u64 timestamp_ms = wifi_camera_ws_current_timestamp_ms();
    u32 ident = wifi_camera_ws_generate_login_ident();

    if (!cJSON_AddStringToObject(data, "type", "upGetChatUserList") ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI) ||
        !cJSON_AddNumberToObject(data, "timestamp", (double)timestamp_ms)) {
        cJSON_Delete(data);
        return -ENOMEM;
    }

    err = wifi_camera_ws_build_request_envelope("upGetChatUserList",
                                                WIFI_CAMERA_WS_REQUEST_REF,
                                                ident,
                                                timestamp_ms,
                                                data,
                                                &root);
    if (err) {
        return err;
    }
    data = NULL;

    memset(payload, 0, sizeof(payload));
    if (!cJSON_PrintPreallocated(root, payload, sizeof(payload), 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            err = -EIO;
            goto cleanup;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= sizeof(payload)) {
            cJSON_free(dynamic_buf);
            err = -EOVERFLOW;
            goto cleanup;
        }
        memcpy(payload, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    size_t payload_len = strlen(payload);
    printf("[WS][CHAT] get chat user list json: %s\n", payload);
    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][CHAT] send get chat user list failed:%d\n", err);
    }

cleanup:
    if (root) {
        cJSON_Delete(root);
    }
    if (data) {
        cJSON_Delete(data);
    }
    return err;
}

/**
 * @brief 触发好友同步流程，请求服务器下发最新好友数据。
 *
 * @return 0 表示发送成功；若连接未建立或构建失败则返回负值。
 */
int wifi_camera_ws_send_sync_friend_request(void)
{
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    int err = 0;
    char payload[WIFI_CAMERA_WS_SYNC_FRIEND_PAYLOAD_MAX_LEN];
    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    u64 timestamp_ms = wifi_camera_ws_current_timestamp_ms();
    u32 ident = wifi_camera_ws_generate_login_ident();

    if (!cJSON_AddStringToObject(data, "type", "upSyncFriend") ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI) ||
        !cJSON_AddNumberToObject(data, "timestamp", (double)timestamp_ms)) {
        cJSON_Delete(data);
        return -ENOMEM;
    }

    err = wifi_camera_ws_build_request_envelope("upSyncFriend",
                                                WIFI_CAMERA_WS_REQUEST_REF,
                                                ident,
                                                timestamp_ms,
                                                data,
                                                &root);
    if (err) {
        return err;
    }
    data = NULL;

    memset(payload, 0, sizeof(payload));
    if (!cJSON_PrintPreallocated(root, payload, sizeof(payload), 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            err = -EIO;
            goto cleanup;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= sizeof(payload)) {
            cJSON_free(dynamic_buf);
            err = -EOVERFLOW;
            goto cleanup;
        }
        memcpy(payload, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    size_t payload_len = strlen(payload);
    printf("[WS][CHAT] sync friend json: %s\n", payload);
    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][CHAT] send sync friend failed:%d\n", err);
    }

cleanup:
    if (root) {
        cJSON_Delete(root);
    }
    if (data) {
        cJSON_Delete(data);
    }
    return err;
}

/**
 * @brief 构建电池状态上报的 JSON 报文。
 *
 * @param battery_type 电池类型枚举，范围 0~3。
 * @param buf          输出缓冲区。
 * @param len          缓冲区长度。
 * @param out_len      返回实际写入的字节数。
 *
 * @return 0 表示成功，负值表示失败原因。
 */
static int wifi_camera_ws_build_battery_json(int battery_type,
                                             char *buf,
                                             size_t len,
                                             size_t *out_len)
{
    if (!buf || !out_len) {
        return -EINVAL;
    }

    int ret = -ENOMEM;
    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    int level = adc_get_battery_level_percent();
    if (level < 0) {
        level = 0;
    } else if (level > 100) {
        level = 100;
    }

    int state = adc_get_charging_state() ? 1 : 0;

    if (battery_type < 0) {
        battery_type = 0;
    } else if (battery_type > 3) {
        battery_type = 3;
    }

    u64 timestamp = wifi_camera_ws_current_timestamp_ms();
    u32 ident = wifi_camera_ws_generate_login_ident();

    if (!cJSON_AddStringToObject(data, "type", "upBattery") ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI) ||
        !cJSON_AddStringToObject(data, "deviceModel", WIFI_CAMERA_WS_DEVICE_MODEL) ||
        !cJSON_AddNumberToObject(data, "batteryLevel", (double)level) ||
        !cJSON_AddNumberToObject(data, "batteryState", (double)state) ||
        !cJSON_AddNumberToObject(data, "batteryType", (double)battery_type) ||
        !cJSON_AddNumberToObject(data, "timestamp", (double)timestamp)) {
        goto cleanup;
    }

    ret = wifi_camera_ws_build_request_envelope("upBattery",
                                                WIFI_CAMERA_WS_REQUEST_REF,
                                                ident,
                                                timestamp,
                                                data,
                                                &root);
    if (ret) {
        goto cleanup;
    }
    data = NULL;

    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            ret = -EIO;
            goto cleanup;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            ret = -EOVERFLOW;
            goto cleanup;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    ret = 0;

cleanup:
    if (data) {
        cJSON_Delete(data);
    }
    if (root) {
        cJSON_Delete(root);
    }
    return ret;
}

/**
 * @brief 构建设备关机上报的 JSON 报文。
 *
 * @param buf     输出缓冲区。
 * @param len     缓冲区长度。
 * @param out_len 返回实际写入的字节数。
 *
 * @return 0 表示成功，负值表示失败原因。
 */
static int wifi_camera_ws_build_shutdown_json(char *buf,
                                              size_t len,
                                              size_t *out_len)
{
    if (!buf || !out_len) {
        return -EINVAL;
    }

    int ret = -ENOMEM;
    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    u64 timestamp = wifi_camera_ws_current_timestamp_ms();
    u32 ident = wifi_camera_ws_generate_login_ident();

    if (!cJSON_AddStringToObject(data, "type", "upShutdown") ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI) ||
        !cJSON_AddStringToObject(data, "deviceModel", WIFI_CAMERA_WS_DEVICE_MODEL) ||
        !cJSON_AddNumberToObject(data, "timestamp", (double)timestamp)) {
        goto cleanup;
    }

    ret = wifi_camera_ws_build_request_envelope("upShutdown",
                                                WIFI_CAMERA_WS_REQUEST_REF,
                                                ident,
                                                timestamp,
                                                data,
                                                &root);
    if (ret) {
        goto cleanup;
    }
    data = NULL;

    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            ret = -EIO;
            goto cleanup;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            ret = -EOVERFLOW;
            goto cleanup;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    ret = 0;

cleanup:
    if (root) {
        cJSON_Delete(root);
    } else if (data) {
        cJSON_Delete(data);
    }
    return ret;
}

/**
 * @brief 收集 Wi-Fi 扫描结果并写入 JSON 数组。
 *
 * @param wifi_array JSON 数组指针，用于承载热点信息。
 * @param out_count  返回追加的热点数量，可为 NULL。
 *
 * @return 0 表示成功；若无可用数据或发生错误返回负值。
 */
static int wifi_camera_ws_collect_wifi_scan(cJSON *wifi_array, size_t *out_count)
{
    if (!wifi_array) {
        return -EINVAL;
    }

    struct wifi_scan_ssid_info *scan_results = NULL;
    u32 ssid_count = 0;
    struct wifi_scan_ssid_info fresh_entries[WIFI_CAMERA_WS_LOCATION_WIFI_MAX_COUNT];
    struct wifi_scan_ssid_info cached_entries[WIFI_CAMERA_WS_LOCATION_WIFI_MAX_COUNT];
    size_t fresh_count = 0;
    size_t appended = 0;
    int ret = -ENODATA;
    bool need_async_refresh = false;
    bool used_connected_ap_fallback = false;
    bool used_cached_entries = false;
    bool cache_stale = false;
    bool tried_sync_scan = false;

    scan_results = wifi_get_scan_result(&ssid_count);

    enum wifi_sta_connect_state connect_state = wifi_get_sta_connect_state();
    bool sta_connected = false;
    switch (connect_state) {
    case WIFI_STA_CONNECT_SUCC:
    case WIFI_STA_NETWORK_STACK_DHCP_SUCC:
    case WIFI_STA_IP_GOT_IPV6_SUCC:
        sta_connected = true;
        break;
    default:
        break;
    }

    if (!scan_results || ssid_count < WIFI_CAMERA_WS_LOCATION_WIFI_MIN_COUNT) {
        bool force_sync = (!scan_results || ssid_count == 0);
        u32 wait_ms = 0;

        if (!sta_connected) {
            if (wifi_camera_ws_scan_sync_acquire(force_sync, &wait_ms)) {
                int scan_ret = wifi_scan_req();
                if (scan_ret) {
                    if (scan_ret != -EINPROGRESS) {
                        printf("[WS][LOC] wifi_scan_req failed:%d\n", scan_ret);
                    }
                }
                tried_sync_scan = true;
                for (int attempt = 0; attempt < WIFI_CAMERA_WS_LOCATION_SCAN_MAX_ATTEMPTS; ++attempt) {
                    os_time_dly(WIFI_CAMERA_WS_LOCATION_SCAN_WAIT_TICKS);
                    struct wifi_scan_ssid_info *tmp_results = wifi_get_scan_result(&ssid_count);
                    if (!tmp_results) {
                        continue;
                    }
                    if (scan_results) {
                        wifi_clear_scan_result();
                        free(scan_results);
                    }
                    scan_results = tmp_results;
                    if (ssid_count >= WIFI_CAMERA_WS_LOCATION_WIFI_MIN_COUNT) {
                        break;
                    }
                }
            } else {
                if (wait_ms > 0) {
                    printf("[WS][LOC] skip sync wifi_scan_req, cooldown %u ms\n", wait_ms);
                }
            }
        } else {
            need_async_refresh = true;
        }
    }

    if (scan_results && ssid_count > 0) {
        if (ssid_count > 1) {
            qsort(scan_results, ssid_count, sizeof(*scan_results), wifi_camera_ws_scan_result_compare);
        }
        fresh_count = ssid_count > WIFI_CAMERA_WS_LOCATION_WIFI_MAX_COUNT ? WIFI_CAMERA_WS_LOCATION_WIFI_MAX_COUNT : ssid_count;
        memcpy(fresh_entries, scan_results, fresh_count * sizeof(*fresh_entries));
    }

    const struct wifi_scan_ssid_info *selected_entries = NULL;
    size_t selected_count = 0;
    u64 cache_timestamp_ms = 0;
    u32 cache_age_ms = 0;

    if (fresh_count >= WIFI_CAMERA_WS_LOCATION_WIFI_MIN_COUNT) {
        selected_entries = fresh_entries;
        selected_count = fresh_count;
        wifi_camera_ws_cache_store(fresh_entries, fresh_count);
        ret = 0;
    } else {
        size_t cached_count = wifi_camera_ws_cache_fetch(cached_entries,
                                                        WIFI_CAMERA_WS_LOCATION_WIFI_MAX_COUNT,
                                                        &cache_timestamp_ms);
        if (cached_count > 0) {
            selected_entries = cached_entries;
            selected_count = cached_count;
            used_cached_entries = true;
            ret = 0;
            if (cache_timestamp_ms) {
                u64 now = wifi_camera_ws_monotonic_ms();
                if (now >= cache_timestamp_ms) {
                    u64 age = now - cache_timestamp_ms;
                    cache_age_ms = (age > UINT32_MAX) ? UINT32_MAX : (u32)age;
                    if (age >= WIFI_CAMERA_WS_LOCATION_CACHE_MAX_AGE_MS) {
                        cache_stale = true;
                    }
                } else {
                    cache_stale = true;
                }
            } else {
                cache_stale = true;
            }
            if (cache_stale) {
                printf("[WS][LOC] using cached WiFi list:%u (stale %u ms)\n",
                       (unsigned)cached_count,
                       (unsigned)cache_age_ms);
            } else {
                printf("[WS][LOC] using cached WiFi list:%u\n", (unsigned)cached_count);
            }
            ret = 0;
        }

        if (!selected_entries && fresh_count > 0) {
            selected_entries = fresh_entries;
            selected_count = fresh_count;
            wifi_camera_ws_cache_store(fresh_entries, fresh_count);
            need_async_refresh = true;
            printf("[WS][LOC] wifi scan partial result:%u\n", (unsigned)fresh_count);
            ret = 0;
        }

        if (!selected_entries) {
            if (wifi_camera_ws_fill_connected_ap_entry(&fresh_entries[0])) {
                fresh_count = 1;
                selected_entries = fresh_entries;
                selected_count = fresh_count;
                wifi_camera_ws_cache_store(fresh_entries, fresh_count);
                need_async_refresh = true;
                used_connected_ap_fallback = true;
                printf("[WS][LOC] using connected AP fallback\n");
                ret = 0;
            }
        }

        if (!selected_entries) {
            need_async_refresh = true;
            printf("[WS][LOC] no WiFi scan result available\n");
        }
    }

    if (!ret && selected_entries && selected_count) {
        ret = wifi_camera_ws_append_wifi_entries(wifi_array, selected_entries, selected_count, &appended);
    }

    if (!ret) {
        if (appended < WIFI_CAMERA_WS_LOCATION_WIFI_MIN_COUNT) {
            need_async_refresh = true;
        }
        if (used_cached_entries && cache_stale) {
            need_async_refresh = true;
        }
    }

    if (need_async_refresh) {
        bool force_async = (appended == 0);
        u32 wait_ms = 0;
        u64 now_ms = wifi_camera_ws_monotonic_ms();

        if (used_connected_ap_fallback) {
            wifi_camera_ws_scan_async_set_defer(now_ms, WIFI_CAMERA_WS_LOCATION_ASYNC_DEFER_AFTER_FALLBACK_MS);
        } else if (used_cached_entries && cache_stale) {
            wifi_camera_ws_scan_async_set_defer(now_ms, WIFI_CAMERA_WS_LOCATION_ASYNC_DEFER_AFTER_STALE_MS);
        }

        if (wifi_camera_ws_scan_async_acquire(force_async, &wait_ms)) {
            int async_ret = wifi_scan_req();
            if (async_ret && async_ret != -EINPROGRESS) {
                printf("[WS][LOC] async wifi_scan_req failed:%d\n", async_ret);
            } else {
                if (!wifi_camera_ws_lock()) {
                    s_ws_scan_ratelimit.deferred_async_until_ms = 0;
                    wifi_camera_ws_unlock();
                }
            }
        } else if (!force_async) {
            if (wait_ms > 0) {
                printf("[WS][LOC] skip async wifi_scan_req, cooldown %u ms\n", wait_ms);
            }
        }
    }

    if (scan_results) {
        wifi_clear_scan_result();
        free(scan_results);
    }

    if (out_count) {
        *out_count = appended;
    }
    return ret;
}

/**
 * @brief 构建定位数据报文，支持命令触发与设备主动上报。
 *
 * @param trigger        定位触发来源。
 * @param request_ident  命令触发时沿用的请求 ident。
 * @param buf            输出缓冲区。
 * @param len            缓冲区长度。
 * @param out_len        返回实际写入的字节数。
 *
 * @return 0 表示构建成功，否则返回负值错误码。
 */
static int wifi_camera_ws_build_location_json(enum wifi_camera_ws_location_trigger trigger,
                                              u32 request_ident,
                                              char *buf,
                                              size_t len,
                                              size_t *out_len)
{
    if (!buf || !out_len) {
        return -EINVAL;
    }

    bool command_trigger = (trigger == WIFI_CAMERA_WS_LOCATION_TRIGGER_COMMAND);
    const char *message_type = command_trigger ? "dnLocation" : "upLocation";
    const char *ref = command_trigger ? "w:reply" : WIFI_CAMERA_WS_REQUEST_REF;
    const char *position_type = command_trigger ? "1" : "0";
    u32 ident = (command_trigger && request_ident) ? request_ident : wifi_camera_ws_generate_login_ident();
    u64 timestamp = wifi_camera_ws_current_timestamp_ms();
    if (command_trigger) {
        timestamp += (u64)WIFI_CAMERA_WS_COMMAND_REPLY_TIMESTAMP_OFFSET_MS;
    }

    int ret = -ENOMEM;
    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    cJSON *wifi_array = NULL;
    //cJSON *base_station_array = NULL;
    //cJSON *gps_obj = NULL;

    if (!cJSON_AddStringToObject(data, "type", message_type) ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI) ||
        !cJSON_AddStringToObject(data, "deviceModel", WIFI_CAMERA_WS_DEVICE_MODEL) ||
        !cJSON_AddNumberToObject(data, "baseStationType", 0) ||
        !cJSON_AddStringToObject(data, "positionDataType", position_type)) {
        goto cleanup;
    }

    wifi_array = cJSON_CreateArray();
    if (!wifi_array) {
        goto cleanup;
    }
    cJSON_AddItemToObject(data, "wifi", wifi_array);

    size_t wifi_count = 0;
    ret = wifi_camera_ws_collect_wifi_scan(wifi_array, &wifi_count);
    if (ret) {
        goto cleanup;
    }

    // base_station_array = cJSON_CreateArray();
    // if (!base_station_array) {
    //     goto cleanup;
    // }
    // cJSON_AddItemToObject(data, "baseStation", base_station_array);

    // gps_obj = cJSON_CreateObject();
    // if (!gps_obj) {
    //     goto cleanup;
    // }
    // cJSON_AddItemToObject(data, "gps", gps_obj);

    if (!cJSON_AddNumberToObject(data, "timestamp", (double)timestamp)) {
        goto cleanup;
    }

    ret = wifi_camera_ws_build_request_envelope(message_type,
                                                ref,
                                                ident,
                                                timestamp,
                                                data,
                                                &root);
    if (ret) {
        goto cleanup;
    }
    data = NULL;

    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            ret = -EIO;
            goto cleanup;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            ret = -EOVERFLOW;
            goto cleanup;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    ret = 0;

cleanup:
    if (data) {
        cJSON_Delete(data);
    }
    if (root) {
        cJSON_Delete(root);
    }
    return ret;
}

/**
 * @brief 构建“加好友”上报报文。
 *
 * @param buf     输出缓冲区。
 * @param len     缓冲区长度。
 * @param out_len 返回实际写入的字节数。
 *
 * @return 0 表示成功，否则返回负值错误码。
 */
static int wifi_camera_ws_build_make_friend_json(char *buf,
                                                 size_t len,
                                                 size_t *out_len)
{
    if (!buf || !out_len) {
        return -EINVAL;
    }

    int ret = -ENOMEM;
    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    if (!cJSON_AddStringToObject(data, "type", "upMakeFriend") ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI) ||
        !cJSON_AddStringToObject(data, "deviceModel", WIFI_CAMERA_WS_DEVICE_MODEL) ||
        !cJSON_AddNumberToObject(data, "baseStationType", 0)) {
        goto cleanup;
    }

    cJSON *wifi_array = cJSON_CreateArray();
    if (!wifi_array) {
        goto cleanup;
    }
    cJSON_AddItemToObject(data, "wifi", wifi_array);

    size_t wifi_count = 0;
    ret = wifi_camera_ws_collect_wifi_scan(wifi_array, &wifi_count);
    if (ret) {
        goto cleanup;
    }
    if (wifi_count < WIFI_CAMERA_WS_LOCATION_WIFI_MIN_COUNT) {
        printf("[WS][MKF] wifi list less than minimum:%u\n", (unsigned)wifi_count);
    }

    u64 timestamp = wifi_camera_ws_current_timestamp_ms();
    if (!cJSON_AddNumberToObject(data, "timestamp", (double)timestamp)) {
        goto cleanup;
    }

    u32 ident = wifi_camera_ws_generate_login_ident();
    ret = wifi_camera_ws_build_request_envelope("upMakeFriend",
                                                WIFI_CAMERA_WS_REQUEST_REF,
                                                ident,
                                                timestamp,
                                                data,
                                                &root);
    if (ret) {
        goto cleanup;
    }
    data = NULL;

    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            ret = -EIO;
            goto cleanup;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            ret = -EOVERFLOW;
            goto cleanup;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    ret = 0;

cleanup:
    if (data) {
        cJSON_Delete(data);
    }
    if (root) {
        cJSON_Delete(root);
    }
    return ret;
}

/**
 * @brief 构建视频呼叫请求 JSON。
 *
 * @param call_device 目标呼叫设备标识。
 * @param buf         输出缓冲区。
 * @param len         缓冲区长度。
 * @param out_len     返回实际写入的字节数。
 *
 * @return 0 表示成功，否则返回负值错误码。
 */
static int wifi_camera_ws_build_video_call_json(const char *call_device,
                                                char *buf,
                                                size_t len,
                                                size_t *out_len)
{
    if (!buf || !out_len || !call_device || !call_device[0]) {
        return -EINVAL;
    }

    int ret = -ENOMEM;
    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    if (!cJSON_AddStringToObject(data, "type", "upVideoCallWithAPP") ||
        !cJSON_AddStringToObject(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI) ||
        !cJSON_AddStringToObject(data, "call_device", call_device) ||
        !cJSON_AddNumberToObject(data, "call_type", 1)) {
        goto cleanup;
    }

    u64 timestamp = wifi_camera_ws_current_timestamp_ms();
    if (!timestamp) {
        timestamp = wifi_camera_ws_monotonic_ms();
    }

    if (!cJSON_AddNumberToObject(data, "timestamp", (double)timestamp)) {
        goto cleanup;
    }

    u32 ident = wifi_camera_ws_generate_login_ident();
    ret = wifi_camera_ws_build_request_envelope("upVideoCallWithAPP",
                                                WIFI_CAMERA_WS_REQUEST_REF,
                                                ident,
                                                timestamp,
                                                data,
                                                &root);
    if (ret) {
        goto cleanup;
    }
    data = NULL;

    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            ret = -EIO;
            goto cleanup;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            ret = -EOVERFLOW;
            goto cleanup;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    ret = 0;

cleanup:
    if (data) {
        cJSON_Delete(data);
    }
    if (root) {
        cJSON_Delete(root);
    }
    return ret;
}

/*
 * 构建 WebSocket 登录 JSON 报文：
 * - 入参 `buf/len` 为目标缓存与长度，`out_len` 返回实际写入字节数
 * - 根据头文件中的宏默认值拼装完整结构，同时兼容 `extend`、`config` 可配置为 null / JSON 片段
 * - 统一通过 cJSON 创建树形结构，确保字段顺序和数据类型符合服务端协议约定
 */
static int wifi_camera_ws_build_login_json(char *buf, size_t len, size_t *out_len)
{
    /* 基础校验：外部调用必须传入有效缓存与长度指针 */
    if (!buf || !out_len) {
        return -EINVAL;
    }

    int ret = -ENOMEM;
    cJSON *root = NULL;
    /* data 节点：承载设备详细信息 */
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

    /* chips 数组：协议允许后续扩展多个芯片，此处至少填充一个默认项 */
    cJSON *chips = cJSON_CreateArray();
    if (!chips) {
        cJSON_Delete(data);
        return -ENOMEM;
    }

    /* 单个芯片描述对象，包含 type/factory/model 三个字段 */
    cJSON *chip = cJSON_CreateObject();
    if (!chip) {
        cJSON_Delete(data);
        cJSON_Delete(chips);
        return -ENOMEM;
    }

#define WS_JSON_ADD_STRING(obj, key, value)                           \
    do {                                                              \
        if (!cJSON_AddStringToObject((obj), (key), (value))) {        \
            ret = -ENOMEM;                                            \
            goto cleanup;                                             \
        }                                                             \
    } while (0)

#define WS_JSON_ADD_NUMBER(obj, key, value)                           \
    do {                                                              \
        if (!cJSON_AddNumberToObject((obj), (key), (double)(value))) {\
            ret = -ENOMEM;                                            \
            goto cleanup;                                             \
        }                                                             \
    } while (0)

    const u32 login_ident = wifi_camera_ws_generate_login_ident();
    const u64 login_timestamp = wifi_camera_ws_current_timestamp_ms();
    int battery_level = adc_get_battery_level_percent();
    if (battery_level < 0) {
        battery_level = 0;
    } else if (battery_level > 100) {
        battery_level = 100;
    }


    WS_JSON_ADD_STRING(data, "type", "login"); /* 设备端消息类型 */
    WS_JSON_ADD_STRING(data, "imei", WIFI_CAMERA_WS_LOGIN_IMEI); /* 与顶层 IMEI 一致 */
    WS_JSON_ADD_STRING(data, "deviceModel", WIFI_CAMERA_WS_DEVICE_MODEL); /* 设备型号（协议要求短型号） */
    WS_JSON_ADD_STRING(data, "platform", WIFI_CAMERA_WS_LOGIN_DATA_PLATFORM); /* 平台信息，如 Linux/RTOS */
    WS_JSON_ADD_STRING(data, "iccId", WIFI_CAMERA_WS_LOGIN_DATA_ICCID); /* 物联网卡 ICCID，可为空字符串 */
    WS_JSON_ADD_STRING(data, "phone", WIFI_CAMERA_WS_LOGIN_DATA_PHONE); /* 客服联系电话，可选 */
    WS_JSON_ADD_NUMBER(data, "batteryLevel", battery_level); /* 电池电量百分比 */
    WS_JSON_ADD_STRING(data, "versions", WIFI_CAMERA_WS_LOGIN_DATA_VERSIONS); /* 固件包自定义版本号 */
    WS_JSON_ADD_STRING(data, "mac", WIFI_CAMERA_WS_LOGIN_DATA_MAC); /* 无线或有线 MAC */
    WS_JSON_ADD_STRING(data, "sn", WIFI_CAMERA_WS_LOGIN_DATA_SN); /* 序列号 */
    WS_JSON_ADD_STRING(data, "OS", WIFI_CAMERA_WS_LOGIN_DATA_OS); /* 操作系统描述 */
    WS_JSON_ADD_STRING(data, "firmware_v", WIFI_CAMERA_WS_LOGIN_DATA_FIRMWARE_V); /* 固件版本 */
    WS_JSON_ADD_STRING(data, "software_v", WIFI_CAMERA_WS_LOGIN_DATA_SOFTWARE_V); /* 软件版本 */
    WS_JSON_ADD_STRING(data, "dateProduction", WIFI_CAMERA_WS_LOGIN_DATA_DATE_PRODUCTION); /* 出厂日期 */

    WS_JSON_ADD_STRING(chip, "type", WIFI_CAMERA_WS_LOGIN_DATA_CHIP_TYPE);
    WS_JSON_ADD_STRING(chip, "factory", WIFI_CAMERA_WS_LOGIN_DATA_CHIP_FACTORY);
    WS_JSON_ADD_STRING(chip, "model", WIFI_CAMERA_WS_LOGIN_DATA_CHIP_MODEL);
    cJSON_AddItemToArray(chips, chip);
    chip = NULL;
    cJSON_AddItemToObject(data, "chips", chips);
    chips = NULL;

    WS_JSON_ADD_STRING(data, "cpuModel", WIFI_CAMERA_WS_LOGIN_DATA_CPU_MODEL); /* CPU 型号 */
    WS_JSON_ADD_STRING(data, "romStorageSize", WIFI_CAMERA_WS_LOGIN_DATA_ROM_SIZE); /* ROM 容量 */
    WS_JSON_ADD_STRING(data, "ramStorageSize", WIFI_CAMERA_WS_LOGIN_DATA_RAM_SIZE); /* RAM 容量 */
    WS_JSON_ADD_STRING(data, "networkType", WIFI_CAMERA_WS_LOGIN_DATA_NETWORK_TYPE); /* 网络类型：WiFi/4G 等 */
    WS_JSON_ADD_STRING(data, "deviceVendor", WIFI_CAMERA_WS_LOGIN_DATA_VENDOR); /* 设备厂商 */
    WS_JSON_ADD_STRING(data, "deviceBrand", WIFI_CAMERA_WS_LOGIN_DATA_BRAND); /* 品牌 */
    WS_JSON_ADD_STRING(data, "deviceModel", WIFI_CAMERA_WS_DEVICE_MODEL); /* 完整机型标识 */
    WS_JSON_ADD_STRING(data, "deviceIP", WIFI_CAMERA_WS_LOGIN_DATA_DEVICE_IP); /* 当前局域网 IP */
    WS_JSON_ADD_STRING(data, "powerSupplyMode", WIFI_CAMERA_WS_LOGIN_DATA_POWER_SUPPLY); /* 供电方式 */
    WS_JSON_ADD_STRING(data, "key", WIFI_CAMERA_WS_LOGIN_DATA_KEY); /* 鉴权 key，服务端用于验签 */
    WS_JSON_ADD_NUMBER(data, "timestamp", (double)login_timestamp); /* data 节点独立时间戳 */

    /* config 允许自定义 JSON 文本，默认 {} */
    cJSON *config_obj = NULL;
    if (strcmp(WIFI_CAMERA_WS_LOGIN_DATA_CONFIG_TOKEN, "{}") == 0) {
        config_obj = cJSON_CreateObject();
    } else {
        config_obj = cJSON_Parse(WIFI_CAMERA_WS_LOGIN_DATA_CONFIG_TOKEN);
        if (!config_obj) {
            printf("[WS] login config parse failed\n");
            ret = -EINVAL;
            goto cleanup;
        }
    }
    cJSON_AddItemToObject(data, "config", config_obj);

    ret = wifi_camera_ws_build_request_envelope("login",
                                                WIFI_CAMERA_WS_REQUEST_REF,
                                                login_ident,
                                                login_timestamp,
                                                data,
                                                &root);
    if (ret) {
        goto cleanup;
    }
    data = NULL;

    /* 优先尝试在调用者提供的缓冲区内直接打印 JSON，失败时回退到动态缓冲 */
    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            ret = -EIO;
            goto cleanup;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            ret = -EOVERFLOW;
            goto cleanup;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    ret = 0;

#undef WS_JSON_ADD_STRING
#undef WS_JSON_ADD_NUMBER

cleanup:
    if (chips) {
        cJSON_Delete(chips);
    }
    if (chip) {
        cJSON_Delete(chip);
    }
    if (data) {
        cJSON_Delete(data);
    }
    if (root) {
        cJSON_Delete(root);
    }

    return ret;
}

/**
 * @brief 构建并发送登录请求。
 *
 * @details 调用 `wifi_camera_ws_build_login_json` 生成报文，先打印 JSON 便于排查，
 *          再通过文本帧发送给服务器。
 *
 * @return 0 成功，或返回构建/发送过程中的错误码。
 */
static int wifi_camera_ws_send_login_message(void)
{
    char payload[WIFI_CAMERA_WS_LOGIN_PAYLOAD_MAX_LEN];
    size_t payload_len = 0;

    int err = wifi_camera_ws_build_login_json(payload, sizeof(payload), &payload_len);
    if (err) {
        printf("[WS] build login json failed:%d\n", err);
        return err;
    }

    printf("[WS] login json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS] send login message failed:%d\n", err);
        return err;
    }

    printf("[WS] login payload sent (%u bytes)\n", (unsigned int)payload_len);
    return 0;
}

/**
 * @brief 构建心跳 JSON 报文。
 *
 * @param buf     调用方提供的缓存指针。
 * @param len     缓存长度，需大于生成的 JSON。
 * @param out_len 输出参数，返回最终 JSON 字节数。
 *
 * @return 0 表示成功，负值为构建失败或缓冲区不足。
 */
static int wifi_camera_ws_build_heartbeat_json(char *buf, size_t len, size_t *out_len)
{
    if (!buf || !out_len) {
        return -EINVAL;
    }

    int ret = -ENOMEM;
    cJSON *root = NULL;
    cJSON *data = cJSON_CreateObject();
    if (!data) {
        return -ENOMEM;
    }

#define WS_HB_JSON_ADD_STRING(obj, key, value)                         \
    do {                                                               \
        if (!cJSON_AddStringToObject((obj), (key), (value))) {         \
            ret = -ENOMEM;                                             \
            goto hb_cleanup;                                           \
        }                                                              \
    } while (0)

#define WS_HB_JSON_ADD_NUMBER(obj, key, value)                         \
    do {                                                               \
        if (!cJSON_AddNumberToObject((obj), (key), (double)(value))) { \
            ret = -ENOMEM;                                             \
            goto hb_cleanup;                                           \
        }                                                              \
    } while (0)

    const u32 heartbeat_ident = wifi_camera_ws_generate_login_ident();
    const u64 heartbeat_timestamp = wifi_camera_ws_current_timestamp_ms();

    int hb_battery_level = adc_get_battery_level_percent();
    if (hb_battery_level < 0) {
        hb_battery_level = 0;
    } else if (hb_battery_level > 100) {
        hb_battery_level = 100;
    }
    int hb_battery_state = adc_get_charging_state() ? 1 : 0;

    WS_HB_JSON_ADD_STRING(data, "type", WIFI_CAMERA_WS_HEARTBEAT_TYPE);
    WS_HB_JSON_ADD_STRING(data, "imei", WIFI_CAMERA_WS_HEARTBEAT_IMEI);
    WS_HB_JSON_ADD_STRING(data, "deviceModel", WIFI_CAMERA_WS_DEVICE_MODEL);
    WS_HB_JSON_ADD_NUMBER(data, "batteryLevel", hb_battery_level);
    WS_HB_JSON_ADD_NUMBER(data, "batteryState", hb_battery_state);
    WS_HB_JSON_ADD_NUMBER(data, "timestamp", (double)heartbeat_timestamp);

    ret = wifi_camera_ws_build_request_envelope(WIFI_CAMERA_WS_HEARTBEAT_TYPE,
                                                WIFI_CAMERA_WS_REQUEST_REF,
                                                heartbeat_ident,
                                                heartbeat_timestamp,
                                                data,
                                                &root);
    if (ret) {
        goto hb_cleanup;
    }
    data = NULL;

    memset(buf, 0, len);
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 0)) {
        char *dynamic_buf = cJSON_PrintUnformatted(root);
        if (!dynamic_buf) {
            ret = -EIO;
            goto hb_cleanup;
        }
        size_t printed_len = strlen(dynamic_buf);
        if (printed_len >= len) {
            cJSON_free(dynamic_buf);
            ret = -EOVERFLOW;
            goto hb_cleanup;
        }
        memcpy(buf, dynamic_buf, printed_len + 1);
        cJSON_free(dynamic_buf);
    }

    *out_len = strlen(buf);
    ret = 0;

#undef WS_HB_JSON_ADD_STRING
#undef WS_HB_JSON_ADD_NUMBER

hb_cleanup:
    if (data) {
        cJSON_Delete(data);
    }
    if (root) {
        cJSON_Delete(root);
    }
    return ret;
}

/**
 * @brief 构建并发送心跳文本帧。
 *
 * @return 0 成功；若连接已断开返回 -ENOTCONN，其它错误记录日志。
 */
static int wifi_camera_ws_send_heartbeat_message(void)
{
    char payload[WIFI_CAMERA_WS_HEARTBEAT_PAYLOAD_MAX_LEN];
    size_t payload_len = 0;

    int err = wifi_camera_ws_build_heartbeat_json(payload, sizeof(payload), &payload_len);
    if (err) {
        printf("[WS][HB] build heartbeat json failed:%d\n", err);
        return err;
    }

    printf("[WS][HB] heartbeat json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err && err != -ENOTCONN) {
        printf("[WS][HB] send heartbeat message failed:%d\n", err);
    }
    return err;
}

/**
 * @brief 发送语音消息下行的确认报文。
 *
 * @param request_ident        原始请求序列号。
 * @param request_timestamp_ms 原始请求时间戳。
 *
 * @return 0 表示发送成功，负值为失败原因。
 */
int wifi_camera_ws_send_downchatvoice_ack(u32 request_ident, u64 request_timestamp_ms)
{
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    char payload[WIFI_CAMERA_WS_DOWNCHATVOICE_ACK_PAYLOAD_MAX_LEN];
    size_t payload_len = 0;

    int err = wifi_camera_ws_build_downchatvoice_ack_json(request_ident,
                                                          request_timestamp_ms,
                                                          payload,
                                                          sizeof(payload),
                                                          &payload_len);
    if (err) {
        printf("[WS][VOICE] build downChatVoice ack failed:%d\n", err);
        return err;
    }

    printf("[WS][VOICE] downChatVoice ack json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][VOICE] downChatVoice ack send failed:%d\n", err);
    }
    return err;
}

/**
 * @brief 发送重启指令的确认报文。
 *
 * @param request_ident        原始请求序列号。
 * @param request_timestamp_ms 原始请求时间戳。
 *
 * @return 0 表示发送成功，负值为失败原因。
 */
int wifi_camera_ws_send_restart_ack(u32 request_ident, u64 request_timestamp_ms)
{
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    char payload[WIFI_CAMERA_WS_RESTART_ACK_PAYLOAD_MAX_LEN];
    size_t payload_len = 0;

    int err = wifi_camera_ws_build_restart_ack_json(request_ident,
                                                    request_timestamp_ms,
                                                    payload,
                                                    sizeof(payload),
                                                    &payload_len);
    if (err) {
        printf("[WS][RESTART] build restart ack failed:%d\n", err);
        return err;
    }

    printf("[WS][RESTART] restart ack json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][RESTART] restart ack send failed:%d\n", err);
    }
    return err;
}

/**
 * @brief 发送关机指令的确认报文。
 *
 * @param request_ident        原始请求序列号。
 * @param request_timestamp_ms 原始请求时间戳。
 *
 * @return 0 表示发送成功，负值为失败原因。
 */
int wifi_camera_ws_send_poweroff_ack(u32 request_ident, u64 request_timestamp_ms)
{
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    char payload[WIFI_CAMERA_WS_POWEROFF_ACK_PAYLOAD_MAX_LEN];
    size_t payload_len = 0;

    int err = wifi_camera_ws_build_poweroff_ack_json(request_ident,
                                                     request_timestamp_ms,
                                                     payload,
                                                     sizeof(payload),
                                                     &payload_len);
    if (err) {
        printf("[WS][POWEROFF] build powerOff ack failed:%d\n", err);
        return err;
    }

    printf("[WS][POWEROFF] powerOff ack json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][POWEROFF] powerOff ack send failed:%d\n", err);
    }
    return err;
}

/**
 * @brief 发送查找设备指令的确认报文。
 *
 * @param request_ident        原始请求序列号。
 * @param request_timestamp_ms 原始请求时间戳。
 *
 * @return 0 表示发送成功，负值为失败原因。
 */
int wifi_camera_ws_send_find_ack(u32 request_ident, u64 request_timestamp_ms)
{
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    char payload[WIFI_CAMERA_WS_FIND_ACK_PAYLOAD_MAX_LEN];
    size_t payload_len = 0;

    int err = wifi_camera_ws_build_find_ack_json(request_ident,
                                                 request_timestamp_ms,
                                                 payload,
                                                 sizeof(payload),
                                                 &payload_len);
    if (err) {
        printf("[WS][FIND] build find ack failed:%d\n", err);
        return err;
    }

    printf("[WS][FIND] find ack json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][FIND] find ack send failed:%d\n", err);
    }
    return err;
}

/**
 * @brief 主动上报电池状态。
 *
 * @param battery_type 电池类型参数。
 *
 * @return 0 表示发送成功，负值表示失败原因。
 */
int wifi_camera_ws_send_battery_report(int battery_type)
{
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    char stack_payload[WIFI_CAMERA_WS_BATTERY_PAYLOAD_MAX_LEN];
    char *payload = stack_payload;
    char *heap_payload = NULL;
    size_t payload_capacity = sizeof(stack_payload);
    size_t payload_len = 0;
    int err = 0;

    for (unsigned int attempt = 0; attempt < 4; ++attempt) {
        err = wifi_camera_ws_build_battery_json(battery_type,
                                                payload,
                                                payload_capacity,
                                                &payload_len);
        if (err != -EOVERFLOW) {
            break;
        }

        size_t new_capacity = payload_capacity * 2U;
        if (new_capacity > 2048U) {
            break;
        }

        char *new_buf = heap_payload ? realloc(heap_payload, new_capacity) : malloc(new_capacity);
        if (!new_buf) {
            err = -ENOMEM;
            break;
        }

        heap_payload = new_buf;
        payload = heap_payload;
        payload_capacity = new_capacity;
        memset(payload, 0, payload_capacity);
    }

    if (err) {
        printf("[WS][BAT] build battery json failed:%d\n", err);
        if (heap_payload) {
            free(heap_payload);
        }
        return err;
    }

    printf("[WS][BAT] battery json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][BAT] battery send failed:%d\n", err);
    }

    if (heap_payload) {
        free(heap_payload);
    }
    return err;
}

/**
 * @brief 主动上报关机状态。
 *
 * @return 0 表示成功，负值表示失败原因。
 */
int wifi_camera_ws_send_shutdown_report(void)
{
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    char stack_payload[WIFI_CAMERA_WS_SHUTDOWN_PAYLOAD_MAX_LEN];
    char *payload = stack_payload;
    char *heap_payload = NULL;
    size_t payload_capacity = sizeof(stack_payload);
    size_t payload_len = 0;
    int err = 0;

    for (unsigned int attempt = 0; attempt < 4; ++attempt) {
    err = wifi_camera_ws_build_shutdown_json(payload,
                                                 payload_capacity,
                                                 &payload_len);
        if (err != -EOVERFLOW) {
            break;
        }

        size_t new_capacity = payload_capacity * 2U;
        if (new_capacity > 1024U) {
            break;
        }

        char *new_buf = heap_payload ? realloc(heap_payload, new_capacity) : malloc(new_capacity);
        if (!new_buf) {
            err = -ENOMEM;
            break;
        }

        heap_payload = new_buf;
        payload = heap_payload;
        payload_capacity = new_capacity;
        memset(payload, 0, payload_capacity);
    }

    if (err) {
        printf("[WS][SHUTDOWN] build shutdown json failed:%d\n", err);
        if (heap_payload) {
            free(heap_payload);
        }
        return err;
    }

    printf("[WS][SHUTDOWN] shutdown json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][SHUTDOWN] shutdown send failed:%d\n", err);
    }

    if (heap_payload) {
        free(heap_payload);
    }
    return err;
}

/**
 * @brief 发起与 APP 的视频通话请求。
 *
 * @param call_device 目标设备标识。
 *
 * @return 0 表示发送成功，负值表示失败原因。
 */
int wifi_camera_ws_send_video_call_request(const char *call_device)
{
    if (!call_device || !call_device[0]) {
        return -EINVAL;
    }
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    char payload[WIFI_CAMERA_WS_VIDEO_CALL_PAYLOAD_MAX_LEN];
    size_t payload_len = 0;

    int err = wifi_camera_ws_build_video_call_json(call_device,
                                                   payload,
                                                   sizeof(payload),
                                                   &payload_len);
    if (err) {
        printf("[WS][CALL] build call json failed:%d device=%s\n", err, call_device);
        return err;
    }

    printf("[WS][CALL] call request json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][CALL] send call request failed:%d\n", err);
    }
    return err;
}

/**
 * @brief 发起主动加好友请求。
 *
 * @return 0 表示发送成功，负值表示失败原因。
 */
int wifi_camera_ws_send_make_friend_request(void)
{
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    char payload[WIFI_CAMERA_WS_MAKE_FRIEND_PAYLOAD_MAX_LEN];
    size_t payload_len = 0;

    int err = wifi_camera_ws_build_make_friend_json(payload,
                                                    sizeof(payload),
                                                    &payload_len);
    if (err) {
        printf("[WS][MKF] build make friend json failed:%d\n", err);
        return err;
    }

    printf("[WS][MKF] make friend json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][MKF] send make friend message failed:%d\n", err);
    }
    return err;
}

/**
 * @brief 发送定位数据，可由命令或设备主动触发。
 *
 * @param trigger       定位触发来源。
 * @param request_ident 命令触发时的请求 ident。
 *
 * @return 0 表示发送成功，负值表示失败原因。
 */
int wifi_camera_ws_send_location(enum wifi_camera_ws_location_trigger trigger, u32 request_ident)
{
    if (!wifi_camera_ws_client_is_running()) {
        return -ENOTCONN;
    }

    char payload[WIFI_CAMERA_WS_LOCATION_PAYLOAD_MAX_LEN];
    size_t payload_len = 0;

    int err = wifi_camera_ws_build_location_json(trigger, request_ident, payload, sizeof(payload), &payload_len);
    if (err) {
        printf("[WS][LOC] build location json failed:%d\n", err);
        return err;
    }

    printf("[WS][LOC] location json: %s\n", payload);

    err = wifi_camera_ws_client_send_text(payload, payload_len);
    if (err) {
        printf("[WS][LOC] send location message failed:%d\n", err);
    }
    return err;
}

/**
 * @brief 心跳线程入口，周期性发送心跳并监听退出请求。
 *
 * @param priv 线程私有参数，未使用。
 */
static void wifi_camera_ws_heartbeat_thread(void *priv)
{
    (void)priv;
    printf("[WS][HB] worker enter (interval=%u ms)\n", wifi_camera_ws_get_heartbeat_interval_ms());

    while (!thread_kill_req()) {
        if (!wifi_camera_ws_client_is_running()) {
            break;
        }
        u32 interval_ms = wifi_camera_ws_get_heartbeat_interval_ms();
        wifi_camera_ws_sleep_ms_interruptible(interval_ms);
        if (thread_kill_req()) {
            break;
        }
        if (!wifi_camera_ws_client_is_running()) {
            break;
        }
        int err = wifi_camera_ws_send_heartbeat_message();
        if (err == -ENOTCONN) {
            break;
        }
        if (err) {
            printf("[WS][HB] heartbeat send error:%d\n", err);
            break;
        }
    }

    wifi_camera_ws_lock();
    s_ws_ctx.heartbeat_thread_pid = 0;
    wifi_camera_ws_unlock();
    printf("[WS][HB] worker exit\n");
}

/**
 * @brief 发送文本帧。
 *
 * @param buf JSON 或普通文本指针。
 * @param len 数据长度。
 *
 * @return 0 成功或负值错误码。
 */
/**
 * @brief WebSocket 功能禁用时发送文本帧的占位实现。
 */
int wifi_camera_ws_client_send_text(const void *buf, size_t len)
{
    return wifi_camera_ws_send_common(buf, len, WCT_TXTDATA);
}

/**
 * @brief 发送二进制帧。
 */
/**
 * @brief WebSocket 功能禁用时发送二进制帧的占位实现。
 */
int wifi_camera_ws_client_send_binary(const void *buf, size_t len)
{
    return wifi_camera_ws_send_common(buf, len, WCT_BINDATA);
}

/**
 * @brief 发送 ping 帧维持底层连接。
 */
/**
 * @brief WebSocket 功能禁用时发送 ping 的占位实现。
 */
int wifi_camera_ws_client_send_ping(void)
{
    static const char ping_payload[] = "ping";
    return wifi_camera_ws_send_common(ping_payload, sizeof(ping_payload) - 1, WCT_PING);
}

/* 主动关闭连接：先停止线程，再回调“断开”事件。 */
/**
 * @brief WebSocket 功能禁用时的占位反初始化。
 */
void wifi_camera_ws_client_deinit(void)
{
    if (!wifi_camera_ws_client_is_running()) {
        return;
    }

    if (!wifi_camera_ws_lock()) {
        s_ws_ctx.manual_close = true;
        s_ws_ctx.auto_reconnect_enabled = false;
        wifi_camera_ws_unlock();
    }
    wifi_camera_ws_stop_reconnect_thread();
    wifi_camera_ws_client_cleanup();
    wifi_camera_ws_dispatch_event(WIFI_CAMERA_WS_EVENT_DISCONNECTED, 0);
}

/*
 * 自动启动线程：
 * - 使用默认配置拉起 websocket
 * - 失败仅打印日志，不影响主流程
 */
static void wifi_camera_ws_autostart_thread(void *priv)
{
    (void)priv;
    printf("[WS][AUTO] starter thread begin\n");
    const struct wifi_camera_ws_handlers *handlers = NULL;
    if (!wifi_camera_ws_lock()) {
        handlers = s_registered_handlers_valid ? &s_registered_handlers : NULL;
        wifi_camera_ws_unlock();
    }
    struct wifi_camera_ws_config cfg = {
        .url = WIFI_CAMERA_WS_DEFAULT_URL,
        .origin = WIFI_CAMERA_WS_DEFAULT_ORIGIN,
        .mode = WIFI_CAMERA_WS_MODE_PLAIN,
        .recv_timeout_ms = WIFI_CAMERA_WS_DEFAULT_TIMEOUT,
        .handlers = handlers,
    };

    int err = wifi_camera_ws_client_init(&cfg);
    if (err) {
        printf("[WS][AUTO] init failed:%d\n", err);
    } else {
        printf("[WS][AUTO] init success\n");
    }
    wifi_camera_ws_lock();
    s_ws_ctx.starter_thread_pid = 0;
    wifi_camera_ws_unlock();
    printf("[WS][AUTO] starter thread exit\n");
}

/*
 * 对外提供的自启动接口：
 * - 若已经运行或线程在创建中，直接返回
 * - 否则 fork 一个后台线程去执行默认连接
 */
/**
 * @brief WebSocket 功能禁用时的占位自启动接口。
 */
int wifi_camera_ws_client_start_default_async(void)
{
    printf("[WS][AUTO] start_default_async called\n");
    if (wifi_camera_ws_client_is_running()) {
        printf("[WS][AUTO] already running, skip\n");
        return 0;
    }

    int ret = wifi_camera_ws_lock();
    if (ret) {
        printf("[WS][AUTO] lock failed:%d\n", ret);
        return ret;
    }
    s_ws_ctx.manual_close = false;
    if (WIFI_CAMERA_WS_RECONNECT_ENABLE) {
        s_ws_ctx.auto_reconnect_enabled = true;
    }
    if (!s_ws_ctx.reconnect_delay_ms) {
        s_ws_ctx.reconnect_delay_ms = WIFI_CAMERA_WS_RECONNECT_DELAY_MS;
    }
    if (s_ws_ctx.starter_thread_pid) {
        wifi_camera_ws_unlock();
        printf("[WS][AUTO] starter thread already pending (pid=%d)\n", s_ws_ctx.starter_thread_pid);
        return 0;
    }

    ret = thread_fork("ws_auto", 22, WIFI_CAMERA_WS_AUTOSTART_STACK, 0, &s_ws_ctx.starter_thread_pid, wifi_camera_ws_autostart_thread, NULL);
    wifi_camera_ws_unlock();
    if (ret) {
        printf("[WS][AUTO] create thread failed:%d\n", ret);
    } else {
        printf("[WS][AUTO] starter thread pid=%d\n", s_ws_ctx.starter_thread_pid);
    }
    return ret;
}

#else /* CONFIG_WIFI_CAMERA_WEBSOCKET_ENABLE && CONFIG_NET_ENABLE */

#include "websocket_client.h"
#include <errno.h>

int wifi_camera_ws_client_init(const struct wifi_camera_ws_config *config)
{
    (void)config;
    return -ENOSYS;
}

bool wifi_camera_ws_client_is_running(void)
{
    return false;
}

int wifi_camera_ws_client_send_text(const void *buf, size_t len)
{
    (void)buf;
    (void)len;
    return -ENOSYS;
}

int wifi_camera_ws_client_send_binary(const void *buf, size_t len)
{
    (void)buf;
    (void)len;
    return -ENOSYS;
}

int wifi_camera_ws_client_send_ping(void)
{
    return -ENOSYS;
}

void wifi_camera_ws_client_deinit(void)
{
}

int wifi_camera_ws_client_start_default_async(void)
{
    return -ENOSYS;
}

#endif /* CONFIG_WIFI_CAMERA_WEBSOCKET_ENABLE && CONFIG_NET_ENABLE */
