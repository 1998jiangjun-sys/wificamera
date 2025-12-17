#ifndef WIFI_CAMERA_WEBSOCKET_CLIENT_H
#define WIFI_CAMERA_WEBSOCKET_CLIENT_H

#include <stdbool.h>
#include <stddef.h>
#include "typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WIFI_CAMERA_WS_DEFAULT_URL       "htcpovs.kidxin.com:16604"
#define WIFI_CAMERA_WS_DEFAULT_ORIGIN    "http://htcpovs.kidxin.com"
#define WIFI_CAMERA_WS_DEFAULT_TIMEOUT   1000U

/* 默认登录 JSON 字段，可根据实际设备信息覆写。 */
#ifndef WIFI_CAMERA_WS_LOGIN_IMEI
#define WIFI_CAMERA_WS_LOGIN_IMEI                "865028000000307" /* 顶层字段 imei：设备 IMEI 号， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_EXTEND_TOKEN
#define WIFI_CAMERA_WS_LOGIN_EXTEND_TOKEN        "null"         /* 顶层字段 extend：扩展 JSON， */
#endif

#ifndef WIFI_CAMERA_WS_DEVICE_MODEL
#define WIFI_CAMERA_WS_DEVICE_MODEL   "YYZ-device-3"   /* data.deviceModel：设备型号展示名称， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_PLATFORM
#define WIFI_CAMERA_WS_LOGIN_DATA_PLATFORM       "RTOS"           /* data.platform：设备运行平台， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_ICCID
#define WIFI_CAMERA_WS_LOGIN_DATA_ICCID          "" /* data.iccId：SIM 卡 ICCID， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_PHONE
#define WIFI_CAMERA_WS_LOGIN_DATA_PHONE          ""   /* data.phone：SIM 卡号码， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_VERSIONS
#define WIFI_CAMERA_WS_LOGIN_DATA_VERSIONS       "1.2.42"        /* data.versions：固件版本， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_MAC
#define WIFI_CAMERA_WS_LOGIN_DATA_MAC            "8c:14:b4:42:44:01" /* data.mac：设备真实 MAC 地址， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_SN
#define WIFI_CAMERA_WS_LOGIN_DATA_SN             "S1234567"       /* data.sn：设备序列号， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_OS
#define WIFI_CAMERA_WS_LOGIN_DATA_OS             "ThreadX"       /* data.OS：操作系统及版本号， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_FIRMWARE_V
#define WIFI_CAMERA_WS_LOGIN_DATA_FIRMWARE_V     "22.2.6202"     /* data.firmware_v：固件编号， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_SOFTWARE_V
#define WIFI_CAMERA_WS_LOGIN_DATA_SOFTWARE_V     "V1.0.0;V2.0.0" /* data.software_v：软件版本列表， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_DATE_PRODUCTION
#define WIFI_CAMERA_WS_LOGIN_DATA_DATE_PRODUCTION "2022-12-22"   /* data.dateProduction：设备生产日期， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_CHIP_TYPE
#define WIFI_CAMERA_WS_LOGIN_DATA_CHIP_TYPE      "LTE_CAT1"      /* data.chips[].type：芯片类型， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_CHIP_FACTORY
#define WIFI_CAMERA_WS_LOGIN_DATA_CHIP_FACTORY   "ASR"           /* data.chips[].factory：芯片厂商， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_CHIP_MODEL
#define WIFI_CAMERA_WS_LOGIN_DATA_CHIP_MODEL     "3603"          /* data.chips[].model：芯片型号， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_CPU_MODEL
#define WIFI_CAMERA_WS_LOGIN_DATA_CPU_MODEL      "ASR-CPU-3603"  /* data.cpuModel：应用处理器(AP) 型号， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_ROM_SIZE
#define WIFI_CAMERA_WS_LOGIN_DATA_ROM_SIZE       "16MB"         /* data.romStorageSize：ROM 总容量， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_RAM_SIZE
#define WIFI_CAMERA_WS_LOGIN_DATA_RAM_SIZE       "16MB"          /* data.ramStorageSize：RAM 总容量， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_NETWORK_TYPE
#define WIFI_CAMERA_WS_LOGIN_DATA_NETWORK_TYPE   "wifi"            /* data.networkType：当前网络类型， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_VENDOR
#define WIFI_CAMERA_WS_LOGIN_DATA_VENDOR         "YYZ Tech"      /* data.deviceVendor：设备制造商， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_BRAND
#define WIFI_CAMERA_WS_LOGIN_DATA_BRAND          "YYZ"           /* data.deviceBrand：设备品牌， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_DEVICE_IP
#define WIFI_CAMERA_WS_LOGIN_DATA_DEVICE_IP      "192.168.1.101" /* data.deviceIP：设备当前 IP， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_POWER_SUPPLY
#define WIFI_CAMERA_WS_LOGIN_DATA_POWER_SUPPLY   "battery"       /* data.powerSupplyMode：供电方式， */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_CONFIG_TOKEN
#define WIFI_CAMERA_WS_LOGIN_DATA_CONFIG_TOKEN   "{}"           /* data.config：设备功能配置 JSON，默认为空对象 */
#endif
#ifndef WIFI_CAMERA_WS_LOGIN_DATA_KEY
#define WIFI_CAMERA_WS_LOGIN_DATA_KEY            "DeviceKey123457" /* data.key：设备密钥， */
#endif

/* 心跳 JSON 默认字段，可根据产品实际情况覆写。 */
#ifndef WIFI_CAMERA_WS_HEARTBEAT_TYPE
#define WIFI_CAMERA_WS_HEARTBEAT_TYPE             "heartbeat"    /* 心跳消息 type，固定值 */
#endif
#ifndef WIFI_CAMERA_WS_HEARTBEAT_IMEI
#define WIFI_CAMERA_WS_HEARTBEAT_IMEI             WIFI_CAMERA_WS_LOGIN_IMEI /* 与登录保持一致 */
#endif
#ifndef WIFI_CAMERA_WS_HEARTBEAT_INTERVAL_MS
#define WIFI_CAMERA_WS_HEARTBEAT_INTERVAL_MS      30000U         /* 心跳发送间隔，单位 ms */
#endif
#ifndef WIFI_CAMERA_WS_HEARTBEAT_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_HEARTBEAT_PAYLOAD_MAX_LEN  512            /* 心跳 JSON 最大长度，需覆盖完整 envelope */
#endif
#ifndef WIFI_CAMERA_WS_GET_CHAT_USER_LIST_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_GET_CHAT_USER_LIST_PAYLOAD_MAX_LEN  256   /* 获取好友列表 JSON 最大长度 */
#endif

#ifndef WIFI_CAMERA_WS_SYNC_FRIEND_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_SYNC_FRIEND_PAYLOAD_MAX_LEN          256   /* 同步好友 JSON 最大长度 */
#endif
#ifndef WIFI_CAMERA_WS_LOCATION_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_LOCATION_PAYLOAD_MAX_LEN   1536           /* 定位上报 JSON 最大长度 */
#endif
#ifndef WIFI_CAMERA_WS_MAKE_FRIEND_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_MAKE_FRIEND_PAYLOAD_MAX_LEN 1536           /* 添加好友请求 JSON 最大长度 */
#endif
#ifndef WIFI_CAMERA_WS_VIDEO_CALL_PAYLOAD_MAX_LEN
#define WIFI_CAMERA_WS_VIDEO_CALL_PAYLOAD_MAX_LEN 512             /* 语音/视频呼叫请求 JSON 最大长度 */
#endif
#ifndef WIFI_CAMERA_WS_COMMAND_REPLY_TIMESTAMP_OFFSET_MS
#define WIFI_CAMERA_WS_COMMAND_REPLY_TIMESTAMP_OFFSET_MS 5U       /* 指令回复时附加的时间戳偏移，避免重复 */
#endif

/* 自动重连默认设置，可根据产品策略覆写。 */
#ifndef WIFI_CAMERA_WS_RECONNECT_ENABLE
#define WIFI_CAMERA_WS_RECONNECT_ENABLE          1               /* 默认启用重连 */
#endif
#ifndef WIFI_CAMERA_WS_RECONNECT_DELAY_MS
#define WIFI_CAMERA_WS_RECONNECT_DELAY_MS        5000U           /* 触发重连前的延时，单位 ms */
#endif
#ifndef WIFI_CAMERA_WS_RECONNECT_TASK_PRIO
#define WIFI_CAMERA_WS_RECONNECT_TASK_PRIO       22              /* 重连线程优先级 */
#endif
#ifndef WIFI_CAMERA_WS_RECONNECT_TASK_STACK
#define WIFI_CAMERA_WS_RECONNECT_TASK_STACK      1024            /* 重连线程栈大小（字节） */
#endif

/**
 * @brief 传输链路模式：明文 / TLS。
 */
enum wifi_camera_ws_mode {
    WIFI_CAMERA_WS_MODE_PLAIN = 0,
    WIFI_CAMERA_WS_MODE_TLS   = 1,
};

/**
 * @brief WebSocket 客户端事件。
 */
enum wifi_camera_ws_event {
    WIFI_CAMERA_WS_EVENT_CONNECTED = 0,
    WIFI_CAMERA_WS_EVENT_DISCONNECTED,
    WIFI_CAMERA_WS_EVENT_ERROR,
    WIFI_CAMERA_WS_EVENT_PING_TIMEOUT,
};

enum wifi_camera_ws_location_trigger {
    WIFI_CAMERA_WS_LOCATION_TRIGGER_INTERVAL = 0, /**< 定时上报 */
    WIFI_CAMERA_WS_LOCATION_TRIGGER_COMMAND  = 1, /**< 指令响应 */
};

/**
 * @brief WebSocket 客户端回调集合。
 */
struct wifi_camera_ws_handlers {
    void (*on_event)(enum wifi_camera_ws_event event, int value, void *priv);
    void (*on_message)(const u8 *data, u32 len, u8 type, void *priv);
    void *priv;
};

/**
 * @brief WebSocket 客户端配置。
 */
struct wifi_camera_ws_config {
    const char *url;          /**< 形如 ws://host:port/path */
    const char *origin;       /**< HTTP Origin 头 */
    enum wifi_camera_ws_mode mode; /**< 0=ws, 1=wss */
    u32 recv_timeout_ms;      /**< 接收超时，默认 1000 ms */
    const struct wifi_camera_ws_handlers *handlers; /**< 回调集合，可为空 */
};

int  wifi_camera_ws_client_init(const struct wifi_camera_ws_config *config);
int  wifi_camera_ws_client_send_text(const void *buf, size_t len);
int  wifi_camera_ws_client_send_binary(const void *buf, size_t len);
int  wifi_camera_ws_client_send_ping(void);
void wifi_camera_ws_client_deinit(void);
bool wifi_camera_ws_client_is_running(void);
int  wifi_camera_ws_client_start_default_async(void);
int  wifi_camera_ws_send_get_chat_user_list(void);
int  wifi_camera_ws_send_sync_friend_request(void);
int  wifi_camera_ws_client_register_handlers(const struct wifi_camera_ws_handlers *handlers);
int  wifi_camera_ws_send_location(enum wifi_camera_ws_location_trigger trigger,
                                  u32 request_ident);
int  wifi_camera_ws_send_make_friend_request(void);
int  wifi_camera_ws_send_video_call_request(const char *call_device);
int  wifi_camera_ws_send_downchatvoice_ack(u32 request_ident,
                                           u64 request_timestamp_ms);
int  wifi_camera_ws_send_restart_ack(u32 request_ident,
                                     u64 request_timestamp_ms);
int  wifi_camera_ws_send_poweroff_ack(u32 request_ident,
                                      u64 request_timestamp_ms);
int  wifi_camera_ws_send_find_ack(u32 request_ident, u64 request_timestamp_ms);
int  wifi_camera_ws_send_battery_report(int battery_type);
int  wifi_camera_ws_send_shutdown_report(void);
void wifi_camera_ws_update_remote_timestamp(u64 server_timestamp_ms);

#ifdef __cplusplus
}
#endif

#endif /* WIFI_CAMERA_WEBSOCKET_CLIENT_H */
