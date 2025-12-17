#include "system/includes.h"
#include "app_msg.h"
#include "app_tone.h"
#include "tone_player.h"
#include "action.h"
#include "app_config.h"
#include "storage_device.h"
#include "generic/log.h"
#include "os/os_api.h"
#include "event/key_event.h"
#include "event/bt_event.h"
#include "event/device_event.h"
#include "event/net_event.h"
#include "wifi/wifi_connect.h"
#include "asm/gpio.h"
#include "asm/clock.h"
#include "asm/cpu.h"
#include "ctp_server.h"
#include "websocket_client.h"
#include "wifi_camera_http.h"
#include "chat_manager.h"
#include "app_power_manage.h"
#include "audio_config.h"
#include "mic_effect.h"
#include "fs/fs.h"
#include "vir_dev_player.h"
#include "audio/find_audio_data.h"
#include "../../rtc/include/jrtc0.h"
#include "../../rtc/include/jrtc.h"
#if TCFG_LOCAL_TWS_ENABLE
#include "local_tws.h"
#endif
#if TCFG_LE_AUDIO_STREAM_ENABLE
#include "wireless_trans.h"
#endif
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
#include "multi_box_adv/multi_box_adv.h"
#endif


#include "device/vm.h"
#if TCFG_USB_SLAVE_ENABLE || TCFG_USB_HOST_ENABLE
#include "usb_stack.h"
#endif

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cJSON.h"
#include <inttypes.h>
#include <errno.h>

#if defined(CONFIG_UI_STYLE_LY_ENABLE)
#include "lvgl.h"
#include "lvgl_v8_ui_app/style_LY/generated/gui_guider.h"
extern lv_ui guider_ui;

/*这个函数用于在 联系人列表更新 时通知 LVGL UI 进行刷新。

相当于 “通知 UI 刷新联系人界面”。*/
static void address_book_post_refresh(void *unused, ...)
{
    (void)unused;
    if (!guider_ui.address_book) {
        return;
    }
    lv_ui_address_book *ui_scr = guider_ui.address_book;
    if (!ui_scr || !ui_scr->address_book || !lv_obj_is_valid(ui_scr->address_book)) {
        return;
    }
    lv_event_send(ui_scr->address_book, LV_EVENT_VALUE_CHANGED, NULL);
}
#endif

extern int virtual_test(const char *path);
extern int adc_get_battery_level_percent(void);
extern u32 timer_get_ms(void);

//配置音视频通信 SDK（Justalk RTC），用于实时语音/视频会话（如远程监控或对讲）。
/* --------------------------------------------------------------------------
 * JRTC 配置占位符
 * --------------------------------------------------------------------------
 * 需替换为后台颁发的真实凭据；字符串长度需满足协议要求：
 * - appKey: 24 字节
 * - uid   : <=64 字节
 * - aesKey: 16 字节
 * - token : <=128 字节
 */
#ifndef CONFIG_JRTC_APP_KEY
#define CONFIG_JRTC_APP_KEY           "0f2bbba07542b80511334097"
#endif

#ifndef CONFIG_JRTC_UID
//#define CONFIG_JRTC_UID               "imei-105477028731763955427"
#define CONFIG_JRTC_UID          "imei-105477128731763955427"
#endif

#ifndef CONFIG_JRTC_AES_KEY
#define CONFIG_JRTC_AES_KEY           "7f5139746s5IR99W"
#endif

#ifndef CONFIG_JRTC_TOKEN
#define CONFIG_JRTC_TOKEN             ""
#endif

#ifndef CONFIG_JRTC_SERVER_URL
#define CONFIG_JRTC_SERVER_URL        "cn.iot.justalkcloud.com:2198"
#endif

#ifndef CONFIG_JRTC_PEER_UID
//#define CONFIG_JRTC_PEER_UID          "imei-105477128731763955427"
#define CONFIG_JRTC_PEER_UID               "imei-105477028731763955427"
#endif

#ifndef CONFIG_JRTC_SESSION_TICKET
#define CONFIG_JRTC_SESSION_TICKET    "318877374"
#endif


static const char g_jrtc_app_key[] = CONFIG_JRTC_APP_KEY;
static const char g_jrtc_uid[] = CONFIG_JRTC_UID;
static const char g_jrtc_aes_key[] = CONFIG_JRTC_AES_KEY;
static const char g_jrtc_token[] = CONFIG_JRTC_TOKEN;
static const char *g_jrtc_server_url =
#if defined(CONFIG_JRTC_SERVER_URL)
    CONFIG_JRTC_SERVER_URL;
#else
    NULL;
#endif
static const char g_jrtc_peer_uid[] = CONFIG_JRTC_PEER_UID;
static const char g_jrtc_session_ticket[] = CONFIG_JRTC_SESSION_TICKET;

#define JRTC_DEFAULT_WIDTH      640
#define JRTC_DEFAULT_HEIGHT     480
#define JRTC_DEFAULT_FPS        15
#define JRTC_DEFAULT_KBPS       256
#define JRTC_BUFFER_SIZE(width, height) (((width) * (height) * 3) / 2)

static u8 g_jrtc_video_buffer[JRTC_BUFFER_SIZE(JRTC_DEFAULT_WIDTH, JRTC_DEFAULT_HEIGHT)];
static u8 g_jrtc_camera_buffer[JRTC_BUFFER_SIZE(JRTC_DEFAULT_WIDTH, JRTC_DEFAULT_HEIGHT)];

static u8 g_ws_restart_pending = 0;
static u8 g_ws_poweroff_pending = 0;

static bool wifi_camera_find_tone_is_active(void);
static int wifi_camera_find_tone_start(void);
static void wifi_camera_find_tone_stop(void);
static int wifi_camera_find_tone_cb(void *priv, enum stream_event event);

#define WIFI_CAMERA_WS_BATTERY_CHECK_INTERVAL_MS        (60 * 1000U)
#define WIFI_CAMERA_WS_BATTERY_REPORT_INTERVAL_MS       (60 * 60 * 1000U)
#define WIFI_CAMERA_WS_LOW_BATTERY_THRESHOLD_PERCENT    10
#define WIFI_CAMERA_WS_LOW_BATTERY_RESET_PERCENT        15

static u16 g_ws_battery_timer_id = 0;
static u32 g_ws_battery_elapsed_ms = 0;
static u8 g_ws_low_battery_reported = 0;

static void wifi_camera_ws_battery_timer_cb(void *priv);
static void wifi_camera_ws_start_battery_monitor(void);
static void wifi_camera_ws_check_and_report_low_battery(void);
static int wifi_camera_ws_read_battery_percent(void);

#if defined(CONFIG_NET_ENABLE) && defined(CONFIG_WIFI_CAMERA_WEBSOCKET_ENABLE)
static void wifi_camera_ws_report_shutdown(const char *tag)
{
    int err = wifi_camera_ws_send_shutdown_report();
    if (err) {
        printf("%s shutdown report failed:%d\n", tag, err);
    } else {
        printf("%s shutdown report sent\n", tag);
    }
}
#else
static void wifi_camera_ws_report_shutdown(const char *tag)
{
    (void)tag;
}
#endif

static void wifi_camera_ws_restart_timer_cb(void *priv)
{
    (void)priv;

    g_ws_restart_pending = 0;

    wifi_camera_ws_report_shutdown("[WS][RESTART]");
    printf("[WS][RESTART] performing system soft reset\n");
    system_soft_reset();
}

static void wifi_camera_ws_poweroff_timer_cb(void *priv)
{
    (void)priv;

    g_ws_poweroff_pending = 0;

    printf("[WS][POWEROFF] performing system power off\n");
    sys_power_poweroff();
}

static int wifi_camera_ws_read_battery_percent(void)
{
    int percent = adc_get_battery_level_percent();
    if (percent < 0) {
        percent = 0;
    } else if (percent > 100) {
        percent = 100;
    }
    return percent;
}

static void wifi_camera_ws_check_and_report_low_battery(void)
{
    int percent = wifi_camera_ws_read_battery_percent();

    if (percent < WIFI_CAMERA_WS_LOW_BATTERY_THRESHOLD_PERCENT) {
        if (!g_ws_low_battery_reported) {
            int err = wifi_camera_ws_send_battery_report(3);
            if (!err) {
                g_ws_low_battery_reported = 1;
                printf("[WS][BAT] low battery report sent (percent=%d)\n", percent);
            } else {
                printf("[WS][BAT] low battery report failed:%d (percent=%d)\n", err, percent);
            }
        }
    } else if (percent >= WIFI_CAMERA_WS_LOW_BATTERY_RESET_PERCENT) {
        if (g_ws_low_battery_reported) {
            printf("[WS][BAT] low battery cleared (percent=%d)\n", percent);
        }
        g_ws_low_battery_reported = 0;
    }
}

static void wifi_camera_ws_battery_timer_cb(void *priv)
{
    (void)priv;

    if (WIFI_CAMERA_WS_BATTERY_CHECK_INTERVAL_MS >= UINT32_MAX - g_ws_battery_elapsed_ms) {
        g_ws_battery_elapsed_ms = WIFI_CAMERA_WS_BATTERY_REPORT_INTERVAL_MS;
    } else {
        g_ws_battery_elapsed_ms += WIFI_CAMERA_WS_BATTERY_CHECK_INTERVAL_MS;
    }

    if (g_ws_battery_elapsed_ms >= WIFI_CAMERA_WS_BATTERY_REPORT_INTERVAL_MS) {
        int err = wifi_camera_ws_send_battery_report(2);
        if (!err) {
            printf("[WS][BAT] hourly battery report sent\n");
            g_ws_battery_elapsed_ms = 0;
        } else {
            printf("[WS][BAT] hourly battery report failed:%d\n", err);
            if (err == -ENOTCONN) {
                g_ws_battery_elapsed_ms = WIFI_CAMERA_WS_BATTERY_REPORT_INTERVAL_MS;
            } else {
                g_ws_battery_elapsed_ms = 0;
            }
        }
    }

    wifi_camera_ws_check_and_report_low_battery();
}

static void wifi_camera_ws_start_battery_monitor(void)
{
    if (g_ws_battery_timer_id) {
        return;
    }

    g_ws_battery_elapsed_ms = 0;

    g_ws_battery_timer_id = sys_timer_add(NULL, wifi_camera_ws_battery_timer_cb, WIFI_CAMERA_WS_BATTERY_CHECK_INTERVAL_MS);
    if (!g_ws_battery_timer_id) {
        printf("[WS][BAT] battery monitor timer start failed\n");
    } else {
        printf("[WS][BAT] battery monitor timer started (%u ms)\n", WIFI_CAMERA_WS_BATTERY_CHECK_INTERVAL_MS);
    }
}

static void wifi_camera_ws_on_message(const u8 *data, u32 len, u8 type, void *priv)
{
    (void)priv;
    printf("[WS][APP] type=0x%x len=%u payload=%.*s\n", type, (unsigned int)len, (int)len, (const char *)data);

    if (!data || !len) {
        return;
    }

    cJSON *root = cJSON_ParseWithLength((const char *)data, len);
    if (!root) {
        return;
    }

    const cJSON *data_obj = cJSON_GetObjectItemCaseSensitive(root, "data");
    const cJSON *type_item = cJSON_GetObjectItemCaseSensitive(root, "type");
    const char *type_str = NULL;
    const cJSON *ref_item = cJSON_GetObjectItemCaseSensitive(root, "ref");
    const char *ref_str = NULL;

    if (cJSON_IsString(ref_item) && ref_item->valuestring) {
        ref_str = ref_item->valuestring;
    }

    const cJSON *timestamp_item = cJSON_GetObjectItemCaseSensitive(root, "timestamp");
    u64 message_timestamp_ms = 0;
    if ((!timestamp_item || !cJSON_IsNumber(timestamp_item)) && cJSON_IsObject(data_obj)) {
        timestamp_item = cJSON_GetObjectItemCaseSensitive(data_obj, "timestamp");
    }
    if (timestamp_item && cJSON_IsNumber(timestamp_item) && timestamp_item->valuedouble > 0) {
        message_timestamp_ms = (u64)(timestamp_item->valuedouble + 0.5);
        u64 remote_ts = message_timestamp_ms;
        wifi_camera_ws_update_remote_timestamp(remote_ts);
    }

    if (cJSON_IsString(type_item) && type_item->valuestring) {
        type_str = type_item->valuestring;
    } else if (cJSON_IsObject(data_obj)) {
        const cJSON *inner_type = cJSON_GetObjectItemCaseSensitive(data_obj, "type");
        if (cJSON_IsString(inner_type) && inner_type->valuestring) {
            type_str = inner_type->valuestring;
        }
    }

    int is_reply = 0;
    if (ref_str) {
        if (strcmp(ref_str, "w:reply") == 0 || strcmp(ref_str, "s:reply") == 0) {
            is_reply = 1;
        }
    }

    if (type_str && strcmp(type_str, "login") == 0 && is_reply) {
        int err = wifi_camera_ws_send_battery_report(0);
        if (err) {
            printf("[WS][BAT] login battery report failed:%d\n", err);
        } else {
            printf("[WS][BAT] login battery report sent\n");
        }

        g_ws_battery_elapsed_ms = 0;
        g_ws_low_battery_reported = 0;

        wifi_camera_ws_start_battery_monitor();
        wifi_camera_ws_check_and_report_low_battery();

        int chat_err = chat_manager_request_group_list();
        if (chat_err) {
            printf("[WS][CHAT] request group list failed:%d\n", chat_err);
        } else {
            printf("[WS][CHAT] requested group list\n");
        }
    } else if (type_str && strcmp(type_str, "downGetChatUserList") == 0) {
        int chat_err = chat_manager_handle_group_list_json(root);
        if (chat_err) {
            if (cJSON_IsObject(data_obj)) {
                chat_err = chat_manager_handle_group_list_json(data_obj);
            }
        }
        if (chat_err) {
            printf("[WS][CHAT] handle group list failed:%d\n", chat_err);
        } else {
            printf("[WS][CHAT] group list updated\n");
#if defined(CONFIG_UI_ENABLE) && defined(CONFIG_UI_STYLE_LY_ENABLE)
            lvgl_rpc_post_func(address_book_post_refresh, 0);
#endif
        }
    } else if (type_str && strcmp(type_str, "downSyncFriend") == 0) {
        int chat_err = chat_manager_handle_sync_friend_json(root);
        if (chat_err) {
            if (cJSON_IsObject(data_obj)) {
                chat_err = chat_manager_handle_sync_friend_json(data_obj);
            }
        }
        if (chat_err) {
            printf("[WS][CHAT] handle sync friend failed:%d\n", chat_err);
        } else {
            printf("[WS][CHAT] sync friend list updated\n");
#if defined(CONFIG_UI_ENABLE) && defined(CONFIG_UI_STYLE_LY_ENABLE)
            lvgl_rpc_post_func(address_book_post_refresh, 0);
#endif
        }
    } else if (type_str && strcmp(type_str, "dnLocation") == 0) {
        unsigned int ident = 0;
        const cJSON *ident_item = cJSON_GetObjectItemCaseSensitive(root, "ident");
        if (!cJSON_IsNumber(ident_item) && cJSON_IsObject(data_obj)) {
            ident_item = cJSON_GetObjectItemCaseSensitive(data_obj, "ident");
        }
        if (cJSON_IsNumber(ident_item) && ident_item->valuedouble > 0) {
            ident = (unsigned int)ident_item->valuedouble;
        }

        int err = wifi_camera_ws_send_location(WIFI_CAMERA_WS_LOCATION_TRIGGER_COMMAND, ident);
        if (err) {
            printf("[WS][APP] dnLocation reply failed:%d (ident=%u)\n", err, ident);
        } else {
            printf("[WS][APP] dnLocation reply sent (ident=%u)\n", ident);
        }
    } else if (type_str && strcmp(type_str, "downPPmessage") == 0) {
        int chat_err = chat_manager_handle_down_pp_message(root);
        if (chat_err) {
            if (cJSON_IsObject(data_obj)) {
                chat_err = chat_manager_handle_down_pp_message(data_obj);
            }
        }
        if (chat_err) {
            printf("[WS][CHAT] handle pp message failed:%d\n", chat_err);
        } else {
            printf("[WS][CHAT] pp message processed\n");
        }
    } else if (type_str && strcmp(type_str, "downChatVoice") == 0) {
        int chat_err = chat_manager_handle_down_chat_voice(root);
        if (chat_err) {
            if (cJSON_IsObject(data_obj)) {
                chat_err = chat_manager_handle_down_chat_voice(data_obj);
            }
        }
        if (chat_err) {
            printf("[WS][CHAT] handle chat message failed:%d\n", chat_err);
        }

        unsigned int ident = 0;
        const cJSON *ident_item = cJSON_GetObjectItemCaseSensitive(root, "ident");
        if (!cJSON_IsNumber(ident_item) && cJSON_IsObject(data_obj)) {
            ident_item = cJSON_GetObjectItemCaseSensitive(data_obj, "ident");
        }
        if (cJSON_IsNumber(ident_item) && ident_item->valuedouble > 0) {
            ident = (unsigned int)(ident_item->valuedouble + 0.5);
        }

        int err = wifi_camera_ws_send_downchatvoice_ack(ident, message_timestamp_ms);
        if (err) {
            printf("[WS][APP] downChatVoice ack failed:%d (ident=%u)\n", err, ident);
        } else {
            printf("[WS][APP] downChatVoice ack sent (ident=%u, timestamp=%" PRIu64 ")\n",
                   ident,
                   message_timestamp_ms);
        }
    } else if (type_str && strcmp(type_str, "restart") == 0) {
        unsigned int ident = 0;
        const cJSON *ident_item = cJSON_GetObjectItemCaseSensitive(root, "ident");
        if (!cJSON_IsNumber(ident_item) && cJSON_IsObject(data_obj)) {
            ident_item = cJSON_GetObjectItemCaseSensitive(data_obj, "ident");
        }
        if (cJSON_IsNumber(ident_item) && ident_item->valuedouble > 0) {
            ident = (unsigned int)(ident_item->valuedouble + 0.5);
        }

        int err = wifi_camera_ws_send_restart_ack(ident, message_timestamp_ms);
        if (err) {
            printf("[WS][APP] restart ack failed:%d (ident=%u)\n", err, ident);
        } else {
            printf("[WS][APP] restart ack sent (ident=%u, timestamp=%" PRIu64 ")\n",
                   ident,
                   message_timestamp_ms);

            if (!g_ws_restart_pending) {
                u16 restart_timer_id = sys_timeout_add(NULL, wifi_camera_ws_restart_timer_cb, 500);
                if (!restart_timer_id) {
                    printf("[WS][APP] restart timer start failed, forcing reset immediately\n");
                    wifi_camera_ws_restart_timer_cb(NULL);
                } else {
                    g_ws_restart_pending = 1;
                    printf("[WS][APP] restart scheduled after 500 ms\n");
                }
            }
        }
    }
    else if (type_str && strcmp(type_str, "powerOff") == 0) {
        unsigned int ident = 0;
        const cJSON *ident_item = cJSON_GetObjectItemCaseSensitive(root, "ident");
        if (!cJSON_IsNumber(ident_item) && cJSON_IsObject(data_obj)) {
            ident_item = cJSON_GetObjectItemCaseSensitive(data_obj, "ident");
        }
        if (cJSON_IsNumber(ident_item) && ident_item->valuedouble > 0) {
            ident = (unsigned int)(ident_item->valuedouble + 0.5);
        }

        int err = wifi_camera_ws_send_poweroff_ack(ident, message_timestamp_ms);
        if (err) {
            printf("[WS][APP] powerOff ack failed:%d (ident=%u)\n", err, ident);
        } else {
            printf("[WS][APP] powerOff ack sent (ident=%u, timestamp=%" PRIu64 ")\n",
                   ident,
                   message_timestamp_ms);

            if (!g_ws_poweroff_pending) {
                u16 poweroff_timer_id = sys_timeout_add(NULL, wifi_camera_ws_poweroff_timer_cb, 500);
                if (!poweroff_timer_id) {
                    printf("[WS][APP] powerOff timer start failed, forcing shutdown immediately\n");
                    wifi_camera_ws_poweroff_timer_cb(NULL);
                } else {
                    g_ws_poweroff_pending = 1;
                    printf("[WS][APP] powerOff scheduled after 500 ms\n");
                }
            }
        }
    }
    else if (type_str && strcmp(type_str, "find") == 0) {
        unsigned int ident = 0;
        const cJSON *ident_item = cJSON_GetObjectItemCaseSensitive(root, "ident");
        if (!cJSON_IsNumber(ident_item) && cJSON_IsObject(data_obj)) {
            ident_item = cJSON_GetObjectItemCaseSensitive(data_obj, "ident");
        }
        if (cJSON_IsNumber(ident_item) && ident_item->valuedouble > 0) {
            ident = (unsigned int)(ident_item->valuedouble + 0.5);
        }

        int ack_err = wifi_camera_ws_send_find_ack(ident, message_timestamp_ms);
        if (ack_err) {
            printf("[WS][FIND] find ack failed:%d (ident=%u)\n", ack_err, ident);
        } else {
            printf("[WS][FIND] find ack sent (ident=%u, timestamp=%" PRIu64 ")\n",
                   ident,
                   message_timestamp_ms);
        }

        if (wifi_camera_find_tone_is_active()) {
            printf("[WS][FIND] ring already active, ignoring duplicate command\n");
        } else {
            int tone_err = wifi_camera_find_tone_start();
            if (tone_err) {
                printf("[WS][FIND] tone start failed:%d\n", tone_err);
            }
        }
    }

    cJSON_Delete(root);
}

static struct wifi_camera_ws_handlers g_ws_handlers = {
    .on_message = wifi_camera_ws_on_message,
};

#define WIFI_CAMERA_WS_LOCATION_INTERVAL_MS   (5 * 60 * 1000U)

static u16 g_ws_location_timer_id = 0;

static void wifi_camera_ws_location_timer_cb(void *priv)
{
    (void)priv;

    if (!wifi_camera_ws_client_is_running()) {
        return;
    }

    int err = wifi_camera_ws_send_location(WIFI_CAMERA_WS_LOCATION_TRIGGER_INTERVAL, 0);
    if (err) {
        printf("[WS][LOC] interval send failed:%d\n", err);
    }
}

static void wifi_camera_ws_start_location_timer(void)
{
    if (g_ws_location_timer_id) {
        return;
    }

    g_ws_location_timer_id = sys_timer_add(NULL, wifi_camera_ws_location_timer_cb, WIFI_CAMERA_WS_LOCATION_INTERVAL_MS);
    if (!g_ws_location_timer_id) {
        printf("[WS][LOC] interval timer start failed\n");
    } else {
        printf("[WS][LOC] interval timer started (%u ms)\n", WIFI_CAMERA_WS_LOCATION_INTERVAL_MS);
    }
}

#define WIFI_CAMERA_FIND_RING_DURATION_MS   (30U * 1000U)
#define WIFI_CAMERA_FIND_RESTART_INTERVAL_MS 2600U

static u8 g_find_tone_active = 0;
static u32 g_find_tone_deadline_ms = 0;
static u32 g_find_tone_last_start_ms = 0;
static u16 g_find_tone_stop_timer_id = 0;
static u16 g_find_tone_monitor_timer_id = 0;
static u16 g_find_tone_restart_count = 0;
static const char *wifi_camera_find_stream_event_name(enum stream_event event);

#if defined(CONFIG_UI_STYLE_LY_ENABLE)
struct wifi_camera_find_overlay_async_ctx {
    u8 show;
};

static u8 g_find_tone_overlay_visible = 0;

static void wifi_camera_find_ui_apply_visibility(u8 show)
{
    lv_ui_home_page *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_HOME_PAGE);
    if (!ui_scr || !ui_scr->home_page_view_11 ||
        !lv_obj_is_valid(ui_scr->home_page_view_11)) {
        printf("[WS][FIND][UI] overlay target invalid (show=%u)\n", show);
        g_find_tone_overlay_visible = show;
        return;
    }

    if (show) {
        lv_obj_clear_flag(ui_scr->home_page_view_11, LV_OBJ_FLAG_HIDDEN);
        lv_obj_move_foreground(ui_scr->home_page_view_11);
    } else {
        lv_obj_add_flag(ui_scr->home_page_view_11, LV_OBJ_FLAG_HIDDEN);
    }

    g_find_tone_overlay_visible = show;
}

static void wifi_camera_find_ui_async_cb(void *param)
{
    struct wifi_camera_find_overlay_async_ctx *ctx = param;
    if (!ctx) {
        return;
    }
    u8 show = ctx->show;
    free(ctx);
    wifi_camera_find_ui_apply_visibility(show);
}

static void wifi_camera_find_ui_schedule_visibility(bool show, const char *reason)
{
    printf("[WS][FIND][UI] request overlay %s (%s)\n",
           show ? "show" : "hide",
           reason ? reason : "-");

    if (g_find_tone_overlay_visible == (show ? 1 : 0)) {
        printf("[WS][FIND][UI] overlay already %s, scheduling refresh\n",
               show ? "visible" : "hidden");
    }

    struct wifi_camera_find_overlay_async_ctx *ctx = malloc(sizeof(*ctx));
    if (!ctx) {
        printf("[WS][FIND][UI] malloc failed, apply visibility immediately\n");
        wifi_camera_find_ui_apply_visibility(show ? 1 : 0);
        return;
    }

    ctx->show = show ? 1 : 0;
    lv_res_t res = lv_async_call(wifi_camera_find_ui_async_cb, ctx);
    if (res != LV_RES_OK) {
        printf("[WS][FIND][UI] lv_async_call failed (%d), fallback immediate\n", res);
        free(ctx);
        wifi_camera_find_ui_apply_visibility(show ? 1 : 0);
    }
}
#else
static inline void wifi_camera_find_ui_schedule_visibility(bool show, const char *reason)
{
    (void)show;
    (void)reason;
}
#endif

static bool wifi_camera_find_tone_is_active(void)
{
    if (!g_find_tone_active) {
        return false;
    }

    u32 now = timer_get_ms();
    if ((s32)(g_find_tone_deadline_ms - now) > 0) {
        return true;
    }

    printf("[WS][FIND] tone expired (now=%u deadline=%u)\n",
           (unsigned int)now,
           (unsigned int)g_find_tone_deadline_ms);
    wifi_camera_find_tone_stop();
    return false;
}

static void wifi_camera_find_tone_stop_timer_cb(void *priv)
{
    (void)priv;
    printf("[WS][FIND] ring duration elapsed, stopping tone\n");
    wifi_camera_find_tone_stop();
}

static const char *wifi_camera_find_stream_event_name(enum stream_event event)
{
    switch (event) {
    case STREAM_EVENT_NONE: return "NONE";
    case STREAM_EVENT_INIT: return "INIT";
    case STREAM_EVENT_LOAD_DECODER: return "LOAD_DEC";
    case STREAM_EVENT_LOAD_ENCODER: return "LOAD_ENC";
    case STREAM_EVENT_UNLOAD_DECODER: return "UNLOAD_DEC";
    case STREAM_EVENT_UNLOAD_ENCODER: return "UNLOAD_ENC";
    case STREAM_EVENT_SUSPEND: return "SUSPEND";
    case STREAM_EVENT_READY: return "READY";
    case STREAM_EVENT_START: return "START";
    case STREAM_EVENT_PAUSE: return "PAUSE";
    case STREAM_EVENT_STOP: return "STOP";
    case STREAM_EVENT_END: return "END";
    case STREAM_EVENT_CLOSE_PLAYER: return "CLOSE_PLAYER";
    case STREAM_EVENT_CLOSE_RECORDER: return "CLOSE_REC";
    case STREAM_EVENT_PREEMPTED: return "PREEMPT";
    case STREAM_EVENT_NEGOTIATE_FAILD: return "NEG_FAIL";
    case STREAM_EVENT_GET_PIPELINE_UUID: return "GET_UUID";
    case STREAM_EVENT_GET_COEXIST_POLICY: return "GET_COEX";
    case STREAM_EVENT_INC_SYS_CLOCK: return "INC_CLOCK";
    case STREAM_EVENT_GET_NODE_PARM: return "GET_NODE";
    case STREAM_EVENT_GET_EFF_ONLINE_PARM: return "GET_EFF";
    case STREAM_EVENT_A2DP_ENERGY: return "A2DP_ENERGY";
    case STREAM_EVENT_GET_SWITCH_CALLBACK: return "GET_SWITCH";
    case STREAM_EVENT_GET_MERGER_CALLBACK: return "GET_MERGER";
    case STREAM_EVENT_GET_SPATIAL_ADV_CALLBACK: return "GET_SPATIAL";
    case STREAM_EVENT_GET_FILE_BUF_SIZE: return "GET_FILEBUF";
    case STREAM_EVENT_GET_NOISEGATE_CALLBACK: return "GET_NOISEG";
    case STREAM_EVENT_GET_OUTPUT_NODE_DELAY: return "GET_OUT_DELAY";
    case STREAM_EVENT_GLOBAL_PAUSE: return "GLOBAL_PAUSE";
    case STREAM_EVENT_CHECK_DECODER_CONTINUE: return "CHK_CONT";
    default: return "UNKNOWN";
    }
}

static void wifi_camera_find_tone_monitor_timer_cb(void *priv)
{
    (void)priv;

    if (!wifi_camera_find_tone_is_active()) {
        printf("[WS][FIND] monitor: inactive, cancel\n");
        return;
    }

    u32 now = timer_get_ms();
    s32 remain_ms = (s32)(g_find_tone_deadline_ms - now);
    u32 elapsed_ms = now - g_find_tone_last_start_ms;
    int running = tone_player_runing();

    // printf("[WS][FIND] monitor tick now=%u remain=%d elapsed=%u active=%u running=%d restart_count=%u monitor_id=%u\n",
    //        (unsigned int)now,
    //        remain_ms,
    //        (unsigned int)elapsed_ms,
    //        g_find_tone_active,
    //        running,
    //        g_find_tone_restart_count,
    //        g_find_tone_monitor_timer_id);

    if (remain_ms <= 0) {
        wifi_camera_find_tone_stop();
        return;
    }

    if (elapsed_ms < WIFI_CAMERA_FIND_RESTART_INTERVAL_MS) {
        // printf("[WS][FIND] monitor: waiting interval (elapsed=%u < %u)\n",
        //        (unsigned int)elapsed_ms,
        //        WIFI_CAMERA_FIND_RESTART_INTERVAL_MS);
        return;
    }

    printf("[WS][FIND] tone restart triggered (elapsed=%u running=%d)\n",
           (unsigned int)elapsed_ms,
           running);

    tone_player_stop();

    int err = play_tone_file_callback(get_tone_files()->Find_dev, NULL, wifi_camera_find_tone_cb);
    if (err) {
        printf("[WS][FIND] tone restart failed:%d\n", err);
        wifi_camera_find_tone_stop();
    } else {
        g_find_tone_last_start_ms = timer_get_ms();
        g_find_tone_restart_count++;
        printf("[WS][FIND] tone restart succeeded count=%u (new_last=%u)\n",
               g_find_tone_restart_count,
               (unsigned int)g_find_tone_last_start_ms);
    }
}

static int wifi_camera_find_tone_cb(void *priv, enum stream_event event)
{
    (void)priv;

    printf("[WS][FIND] tone callback event=%s(%d) active=%u running=%d deadline=%u now=%u\n",
           wifi_camera_find_stream_event_name(event),
           event,
           g_find_tone_active,
           tone_player_runing(),
           (unsigned int)g_find_tone_deadline_ms,
           (unsigned int)timer_get_ms());

    return 0;
}

static int wifi_camera_find_tone_start(void)
{
    printf("[WS][FIND] tone start requested active=%u deadline=%u stop_timer=%u monitor_timer=%u\n",
           g_find_tone_active,
           (unsigned int)g_find_tone_deadline_ms,
           g_find_tone_stop_timer_id,
           g_find_tone_monitor_timer_id);
    if (wifi_camera_find_tone_is_active()) {
        printf("[WS][FIND] tone start skipped (already active)\n");
        return 0;
    }

    u32 now = timer_get_ms();

    if (g_find_tone_stop_timer_id) {
        sys_timeout_del(g_find_tone_stop_timer_id);
        g_find_tone_stop_timer_id = 0;
    }

    if (g_find_tone_monitor_timer_id) {
        sys_timer_del(g_find_tone_monitor_timer_id);
        g_find_tone_monitor_timer_id = 0;
    }

    g_find_tone_stop_timer_id = sys_timeout_add(NULL,
                                                wifi_camera_find_tone_stop_timer_cb,
                                                WIFI_CAMERA_FIND_RING_DURATION_MS);
    if (!g_find_tone_stop_timer_id) {
        printf("[WS][FIND] failed to create find stop timer\n");
    }

    tone_player_stop();

    g_find_tone_active = 1;
    g_find_tone_deadline_ms = now + WIFI_CAMERA_FIND_RING_DURATION_MS;
    g_find_tone_last_start_ms = now;
    g_find_tone_restart_count = 0;

    int err = play_tone_file_callback(get_tone_files()->Find_dev, NULL, wifi_camera_find_tone_cb);
    if (err) {
        printf("[WS][FIND] tone start failed:%d\n", err);
        wifi_camera_find_tone_stop();
    } else {
        g_find_tone_last_start_ms = timer_get_ms();
        g_find_tone_monitor_timer_id = sys_timer_add(NULL,
                                                     wifi_camera_find_tone_monitor_timer_cb,
                                                     150);
        if (!g_find_tone_monitor_timer_id) {
            printf("[WS][FIND] tone monitor timer start failed\n");
        } else {
            printf("[WS][FIND] tone monitor timer started id=%u\n",
                   g_find_tone_monitor_timer_id);
        }
        wifi_camera_find_ui_schedule_visibility(true, "tone_start");
    }

    return err;
}

static void wifi_camera_find_tone_stop(void)
{
    if (!g_find_tone_active) {
        printf("[WS][FIND] tone stop ignored (not active)\n");
        return;
    }

    printf("[WS][FIND] tone stop executing (deadline=%u last_start=%u stop_timer=%u monitor_timer=%u restart_count=%u running=%d)\n",
           (unsigned int)g_find_tone_deadline_ms,
           (unsigned int)g_find_tone_last_start_ms,
           g_find_tone_stop_timer_id,
           g_find_tone_monitor_timer_id,
           g_find_tone_restart_count,
           tone_player_runing());

    g_find_tone_active = 0;
    g_find_tone_deadline_ms = 0;
    g_find_tone_last_start_ms = 0;
    g_find_tone_restart_count = 0;

    if (g_find_tone_stop_timer_id) {
        sys_timeout_del(g_find_tone_stop_timer_id);
        g_find_tone_stop_timer_id = 0;
    }

    if (g_find_tone_monitor_timer_id) {
        sys_timer_del(g_find_tone_monitor_timer_id);
        g_find_tone_monitor_timer_id = 0;
    }

    tone_player_stop();
    wifi_camera_find_ui_schedule_visibility(false, "tone_stop");
    printf("[WS][FIND] tone stop complete\n");
}

void wifi_camera_find_tone_cancel_from_ui(const char *source)
{
    printf("[WS][FIND][UI] cancel request from %s (active=%u)\n",
           source ? source : "-",
           g_find_tone_active);
    wifi_camera_find_tone_stop();
}

static struct jrtc_image_t g_jrtc_video_image = {
    .data   = g_jrtc_video_buffer,
    .bytes  = sizeof(g_jrtc_video_buffer),
    .width  = JRTC_DEFAULT_WIDTH,
    .height = JRTC_DEFAULT_HEIGHT,
    .format = JRTC_NV12,
    .fps    = JRTC_DEFAULT_FPS,
    .kbps   = JRTC_DEFAULT_KBPS,
};

static struct jrtc_image_t g_jrtc_camera_image = {
    .data   = g_jrtc_camera_buffer,
    .bytes  = sizeof(g_jrtc_camera_buffer),
    .width  = JRTC_DEFAULT_WIDTH,
    .height = JRTC_DEFAULT_HEIGHT,
    .format = JRTC_NV12,
    .fps    = JRTC_DEFAULT_FPS,
    .kbps   = JRTC_DEFAULT_KBPS,
};

static struct jrtc_t *g_jrtc_session1 = NULL;
static struct jrtc_t *g_jrtc_session2 = NULL;

#define WEARAI_RTC_MAX_MEMBERS 8

struct wearai_rtc_member {
    char uid[64];
    unsigned role;
    unsigned status;
    int index;
};

static struct wearai_rtc_member g_wearai_rtc_members[WEARAI_RTC_MAX_MEMBERS];
static u8 g_wearai_rtc_handler_registered1 = 0;
static u8 g_wearai_rtc_handler_registered2 = 0;

/*
 * 在当前成员表中查找指定 uid 对应的槽位索引。
 * 返回值：找到则返回槽序号（0~N-1），找不到返回 -1。
 */
static int wearai_rtc_member_lookup(const char uid[64])
{
    if (!uid || !uid[0]) {
        return -1;
    }

    for (int i = 0; i < WEARAI_RTC_MAX_MEMBERS; i++) {
        if (g_wearai_rtc_members[i].index <= 0) {
            continue;
        }

        if (strncmp(g_wearai_rtc_members[i].uid, uid, sizeof(g_wearai_rtc_members[i].uid)) == 0) {
            return i;
        }
    }

    return -1;
}

/*
 * 将用户信息写入指定槽位，并生成 handler 所需的 index（slot+1）。
 * 用于首次绑定或在 claim 阶段直接占用空槽。
 */
static int wearai_rtc_member_bind_slot(int slot, const char uid[64], unsigned role, unsigned status)
{
    if (slot < 0 || slot >= WEARAI_RTC_MAX_MEMBERS) {
        return 0;
    }

    struct wearai_rtc_member *member = &g_wearai_rtc_members[slot];
    memset(member, 0, sizeof(*member));
    if (uid) {
        strncpy(member->uid, uid, sizeof(member->uid) - 1);
        member->uid[sizeof(member->uid) - 1] = '\0';
    }
    member->role = role;
    member->status = status;
    member->index = slot + 1;
    return member->index;
}

/*
 * 为新 uid 分配可用槽位：若已存在则更新角色/状态，否则寻找首个空槽绑定。
 * 返回值：成功时为绑定后的 index，失败返回 0。
 */
static int wearai_rtc_member_alloc(const char uid[64], unsigned role, unsigned status)
{
    int slot = wearai_rtc_member_lookup(uid);
    if (slot >= 0) {
        struct wearai_rtc_member *member = &g_wearai_rtc_members[slot];
        member->role = role;
        member->status = status;
        return member->index;
    }

    for (int i = 0; i < WEARAI_RTC_MAX_MEMBERS; i++) {
        if (g_wearai_rtc_members[i].index == 0) {
            return wearai_rtc_member_bind_slot(i, uid, role, status);
        }
    }

    printf("[RTC] no free slot for user %s\n", uid ? uid : "<null>");
    return 0;
}

/*
 * 处理 on_user_changed 传入的 preferred_index：优先复用原有槽位，否则降级为新分配。
 * 兼容 SDK 可能重复通知的场景，保持索引稳定。
 */
static int wearai_rtc_member_claim(const char uid[64], int preferred_index, unsigned role, unsigned status)
{
    int slot = wearai_rtc_member_lookup(uid);
    if (slot >= 0) {
        struct wearai_rtc_member *member = &g_wearai_rtc_members[slot];
        member->role = role;
        member->status = status;
        return member->index;
    }

    if (preferred_index > 0) {
        slot = preferred_index - 1;
        if (slot >= 0 && slot < WEARAI_RTC_MAX_MEMBERS) {
            struct wearai_rtc_member *member = &g_wearai_rtc_members[slot];
            if (member->index == 0) {
                return wearai_rtc_member_bind_slot(slot, uid, role, status);
            }
            if (strncmp(member->uid, uid, sizeof(member->uid)) == 0) {
                member->role = role;
                member->status = status;
                if (member->index <= 0) {
                    member->index = slot + 1;
                }
                return member->index;
            }
        }
    }

    return wearai_rtc_member_alloc(uid, role, status);
}

/*
 * 在成员离线时清空其槽位，后续可以再次复用该位置。
 */
static void wearai_rtc_member_release(const char uid[64])
{
    int slot = wearai_rtc_member_lookup(uid);
    if (slot < 0) {
        return;
    }

    memset(&g_wearai_rtc_members[slot], 0, sizeof(g_wearai_rtc_members[slot]));
}

static int wearai_rtc_on_user_joined(struct jrtc_t *jc, const char uid[64], unsigned role, unsigned status)
{
    const char *user = uid && uid[0] ? uid : "<null>";
    int index = wearai_rtc_member_alloc(uid, role, status);
    printf("[RTC] on_user_joined uid=%s role=0x%x status=0x%x -> index=%d\n", user, role, status, index);
    return index;
}

static int wearai_rtc_on_user_changed(struct jrtc_t *jc, const char uid[64], int index, unsigned role, unsigned status)
{
    const char *user = uid && uid[0] ? uid : "<null>";
    int bound_index = wearai_rtc_member_claim(uid, index, role, status);
    printf("[RTC] on_user_changed uid=%s index=%d role=0x%x status=0x%x -> bound=%d\n", user, index, role, status, bound_index);
    return bound_index;
}

static void wearai_rtc_on_user_offline(struct jrtc_t *jc, const char uid[64], int index, enum jrtc_error reason)
{
    const char *user = uid && uid[0] ? uid : "<null>";
    printf("[RTC] on_user_offline uid=%s index=%d reason=%d\n", user, index, reason);
    wearai_rtc_member_release(uid);
}



/*中断列表 */
const struct irq_info irq_info_table[] = {
    //中断号   //优先级0-7   //注册的cpu(0或1)
    /* { IRQ_ISC_IDX,		7,	0}, */
#ifdef CONFIG_IPMASK_ENABLE
    //不可屏蔽中断方法：支持写flash，但中断函数和调用函数和const要全部放在内部ram
    { IRQ_SOFT5_IDX,      6,   0    }, //此中断强制注册到cpu0
    { IRQ_SOFT4_IDX,      6,   1    }, //此中断强制注册到cpu1
#if 0 //如下，SPI1使用不可屏蔽中断设置
    { IRQ_SPI1_IDX,      7,   1    },//中断强制注册到cpu0/1
#endif
#endif
#if CPU_CORE_NUM == 1
    { IRQ_SOFT5_IDX,      7,   0    }, //此中断强制注册到cpu0
    { IRQ_SOFT4_IDX,      7,   1    }, //此中断强制注册到cpu1
    { -2,     			-2,   -2   },//如果加入了该行, 那么只有该行之前的中断注册到对应核, 其他所有中断强制注册到CPU0
#endif

    { IRQ_BT_TIMEBASE_IDX,  5,   0 },
    { IRQ_BLE_RX_IDX,       5,   0 },
    { IRQ_BLE_EVENT_IDX,    5,   0 },
    { IRQ_BT_CLKN_IDX,      5,   0 },
    { IRQ_BREDR_IDX,        5,   0 },

    { -1,     -1,   -1    },
};


/*创建使用 os_task_create_static 或者task_create 接口的 静态任务堆栈*/
#define SYS_TIMER_STK_SIZE 512
#define SYS_TIMER_Q_SIZE 256
static u8 sys_timer_tcb_stk_q[sizeof(StaticTask_t) + SYS_TIMER_STK_SIZE * 4 + sizeof(struct task_queue) + SYS_TIMER_Q_SIZE] ALIGNE(4);

#define SYSTIMER_STK_SIZE 256
static u8 systimer_tcb_stk_q[sizeof(StaticTask_t) + SYSTIMER_STK_SIZE * 4] ALIGNE(4);

#define SYS_EVENT_STK_SIZE 512
static u8 sys_event_tcb_stk_q[sizeof(StaticTask_t) + SYS_EVENT_STK_SIZE * 4] ALIGNE(4);

#define APP_CORE_STK_SIZE 2048
#define APP_CORE_Q_SIZE 1024
static u8 app_core_tcb_stk_q[sizeof(StaticTask_t) + APP_CORE_STK_SIZE * 4 + sizeof(struct task_queue) + APP_CORE_Q_SIZE] ALIGNE(4);

/*创建使用  thread_fork 接口的 静态任务堆栈*/
#define WIFI_TASKLET_STK_SIZE 1400
static u8 wifi_tasklet_tcb_stk_q[sizeof(struct thread_parm) + WIFI_TASKLET_STK_SIZE * 4] ALIGNE(4);

#define WIFI_CMDQ_STK_SIZE 300
static u8 wifi_cmdq_tcb_stk_q[sizeof(struct thread_parm) + WIFI_CMDQ_STK_SIZE * 4] ALIGNE(4);

#define WIFI_MLME_STK_SIZE 900
static u8 wifi_mlme_tcb_stk_q[sizeof(struct thread_parm) + WIFI_MLME_STK_SIZE * 4] ALIGNE(4);

#define WIFI_RX_STK_SIZE 256
static u8 wifi_rx_tcb_stk_q[sizeof(struct thread_parm) + WIFI_RX_STK_SIZE * 4] ALIGNE(4);

/*
任务	功能	栈word / 栈KB	队列word / B	静态缓冲
thread_fork_kill	统筹 thread_fork 回收/杀任务	256 / 1.0	0 / 0	动态
app_core	应用核心调度/消息枢纽	2048 / 8.0	1024 / 4096	app_core_tcb_stk_q
sys_event	系统事件转发	512 / 2.0	0	sys_event_tcb_stk_q
systimer	软件定时器内核	256 / 1.0	0	systimer_tcb_stk_q
sys_timer	系统定时器任务	512 / 2.0	256 / 1024	sys_timer_tcb_stk_q
dlog	串口/调试日志	256 / 1.0	128 / 512	动态
uda_main	UDA（固件升级/下载代理）	7000 / 27.3	0	动态
update / dw_update	OTA/双备份升级流程	512 / 2.0	32 / 128	动态
lvgl_v8_main_task	LVGL UI 主线程	8192 / 32.0	1024 / 4096	LVGL 内部静态

任务	功能	栈word / 栈KB	队列word / B	静态缓冲
audio_server	音频服务器调度	512 / 2.0	64 / 256	动态
audio_mix	混音	512 / 2.0	0	动态
audio_encoder	通用编码器调度	384 / 1.5	64 / 256	动态
mp3_encoder / sbc_encoder / msbc_encoder / adpcm_encoder	各种编码任务	768<del>256 / 3.0</del>1.0	0	动态
vad_encoder	语音活动检测编码	768 / 3.0	0	动态
aec_encoder	回声消除编码	1024 / 4.0	0	动态
dns_encoder	动态噪声抑制	512 / 2.0	0	动态
dynamic_huffman0/1	编码辅助 (Huffman)	300 / 1.17	32 / 128	动态
echo_deal	回声路径处理	1024 / 4.0	32 / 128	动态
uac_sync / uac_play0/1 / uac_record0/1	USB Audio Class 同步/播放/录音	512 / 2.0	0 或 32 / 128	动态
mic_effect	麦克风特效链路	768 / 3.0	0	动态
audio_enc	通用编码隔离线程	768 / 3.0	128 / 512	动态
aec	宿主回声抵消	768 / 3.0	128 / 512	动态
aec_dbg	AEC 调试	512 / 2.0	128 / 512	动态
aud_capture	音频采集	512 / 2.0	256 / 1024	动态
dac	DAC 输出	256 / 1.0	128 / 512	动态
spec_adv	频谱广告/可视化	512 / 2.0	128 / 512	动态
kws	关键词唤醒	256 / 1.0	64 / 256	动态
smart_voice	智能语音	512 / 2.0	128 / 512	动态
audio_vad	语音活动检测	768 / 3.0	0	动态
key_tone	按键音	256 / 1.0	32 / 128	动态
cvp_ref / CVP_RefTask	语音参照链路	256 / 1.0	128 / 512	动态
vir_dev_task	虚拟设备桥接	256 / 1.0	0	动态

任务	功能	栈word / 栈KB	队列word / B	静态缓冲
iperf_test	Wi-Fi 吞吐测试工具	1024 / 4.0	0	动态
tcpip_thread	lwIP 主线程	800 / 3.1	0	动态
tasklet	MAC 层收发调度	1400 / 5.5	0	wifi_tasklet_tcb_stk_q
RtmpMlmeTask	连接管理(MAC MLME)	900 / 3.5	0	wifi_mlme_tcb_stk_q
RtmpCmdQTask	命令队列处理	300 / 1.17	0	wifi_cmdq_tcb_stk_q
wl_rx_irq_thread	Wi-Fi 中断下半部	256 / 1.0	0	wifi_rx_tcb_stk_q
ctp_server	CTP 远程控制协议	600 / 2.3	64 / 256	动态
net_avi0/1、net_mov0/1、mov_unpkg0	网络录制/打包	600 / 2.3	600 / 2400	动态
stream_avi0/1、stream_mov0/1	网络直播分流	320 / 1.25	600 / 2400	动态

任务	功能	栈word / 栈KB	队列word / B	静态缓冲
video_engine_server	视频引擎管理	1024 / 4.0	1024 / 4096	动态
video_engine_task	视频引擎算子	2048 / 8.0	0	动态
vpkg_server	视频封装	512 / 2.0	128 / 512	动态
avi0/1/2	本地 AVI 写入	320 / 1.25	64 / 256	动态
jpg_dec	JPEG 解码	1024 / 4.0	32 / 128	动态
video_dec_server	视频解码调度	1024 / 4.0	256 / 1024	动态
vunpkg_server	视频解包	1024 / 4.0	128 / 512	动态
wl80_test	Wi-Fi/视频测试工具	2048 / 8.0	64 / 256	动态

蓝牙 (受 CONFIG_BT_ENABLE 控制)
任务	功能	栈word / 栈KB	队列word / B	静态缓冲
btencry	蓝牙加密	512 / 2.0	128 / 512	动态
btctrler	控制器	512 / 2.0	384 / 1536	动态
btstack	Host Stack	768 / 3.0	384 / 1536	动态

任务	功能	栈word / 栈KB	队列word / B	静态缓冲	条件
usb_msd0/1	USB 大容量协议	512 / 2.0	128 / 512	动态	USB Mass Storage 设备
rcsp / dev_mg	RCSP 协议 & 设备管理	768 / 3.0；512 / 2.0	128 / 512；512 / 2048	动态	RCSP_MODE
file_bs / ftran_back	存储后台服务	768 / 3.0；512 / 2.0	0	动态	TCFG_DEV_MANAGER_ENABLE
*/
/*任务列表 */
const struct task_info task_info_table[] = {
    {"thread_fork_kill",    25,      256,   0     },
    {"app_core",            15,     APP_CORE_STK_SIZE,	  APP_CORE_Q_SIZE,		 app_core_tcb_stk_q },
    {"sys_event",           29,     SYS_EVENT_STK_SIZE,	   0, 					 sys_event_tcb_stk_q },
    {"systimer",            14,     SYSTIMER_STK_SIZE, 	   0,					 systimer_tcb_stk_q },
    {"sys_timer",            9,     SYS_TIMER_STK_SIZE,	  SYS_TIMER_Q_SIZE,		 sys_timer_tcb_stk_q },
    {"dlog",                 1,      256,   128   },
    {"audio_server",        16,      512,   64    },
    {"audio_mix",           28,      512,   0     },
    {"audio_encoder",       12,      384,   64    },
    {"mp3_encoder",         13,      768,   0     },
    {"vir_dev_task",        14,      256,   0     },
    {"vad_encoder",         14,      768,   0     },
    {"aec_encoder",         13,     1024,   0     },
    {"dns_encoder",         13,      512,   0     },
    {"msbc_encoder",        13,      256,   0     },
    {"sbc_encoder",         13,      512,   0     },
    {"adpcm_encoder",       13,      512,   0     },
    {"dynamic_huffman0",    15,		300,	32    },
    {"dynamic_huffman1",    15,		300,	32    },


    {"echo_deal",           11,     1024,   32    },
    {"uac_sync",            20,      512,   0     },
    {"uac_play0",           26,      512,   32    },
    {"uac_play1",           26,      512,   32    },
    {"uac_record0",         26,      512,   0     },
    {"uac_record1",         26,      512,   0     },
#if (RCSP_MODE)
    {"rcsp",            	4,       768,   128  },
    {"dev_mg",              3,       512,   512  },
#endif//RCSP_MODE
#if (TCFG_DEV_MANAGER_ENABLE)
    {"file_bs",              1,       768,   0  },
    {"ftran_back",           1,       512,   0  },
#endif
    {"usb_msd0",             1,      512,   128   },
    {"usb_msd1",             1,      512,   128   },
    {"uda_main",             2,     7000,   0     },

    {"update",              21,      512,   32    },
    {"dw_update",           21,      512,   32    },

#ifdef CONFIG_WIFI_ENABLE
    {"iperf_test",          15,     1024,   0     },
    {"tcpip_thread",        16,      800,   0     },
    {"tasklet",             10,     WIFI_TASKLET_STK_SIZE,   0,		 wifi_tasklet_tcb_stk_q	 },//通过调节任务优先级平衡WIFI收发占据总CPU的比重
    {"RtmpMlmeTask",        17,     WIFI_MLME_STK_SIZE,  	 0, 	 wifi_mlme_tcb_stk_q	 },
    {"RtmpCmdQTask",        17,     WIFI_CMDQ_STK_SIZE,   	 0,  	 wifi_cmdq_tcb_stk_q	 },
    {"wl_rx_irq_thread",    16,     WIFI_RX_STK_SIZE,    	 0,  	 wifi_rx_tcb_stk_q  	 },

    {"ctp_server",          28,     600,   64    },
    {"net_video_server",    16,     256,   64 	 },
    {"net_avi0",            18,     600,   600	 },
    {"net_avi1",            18,     600,   600	 },
    {"net_mov0",            18,     600,   600	 },
    {"net_mov1",            18,     600,   600	 },
    {"mov_unpkg0",          18,     600,   600	 },
    {"stream_avi0",         18,     320,   600	 },
    {"stream_avi1",         18,     320,   600	 },
    {"stream_mov0",         18,     320,   600	 },
    {"stream_mov1",         18,     320,   600	 },



#endif
#ifdef CONFIG_BT_ENABLE
    {"btencry",             14,      512,   128   },
    {"btctrler",            19,      512,   384   },
    {"btstack",             18,      768,   384   },
#endif
    {"wl80_test",            1,     2048,   64    },

    {"video_engine_server", 10,     1024,   1024  },
    {"video_engine_task",   10,     2048,   0     },

    {"vpkg_server",         16,      512,   128   },





    {"avi0",                28,      320,   64    },
    {"avi1",                28,      320,   64    },
    {"avi2",                28,      320,   64    },
    {"jpg_dec",             10,     1024,   32    },
    {"video_dec_server",    16,     1024,   256   },
    {"vunpkg_server",       16,     1024,   128   },
    {"lvgl_v8_main_task",   25,     8192,  1024   },

#ifdef CONFIG_MEDIA_ENABLE
#if TCFG_ENC_AMR_16K_ENABLE //16k amr enc
    { "jlstream_",           25,    3072,      0 },
#else
    { "jlstream_",           25,     768,      0 },
#endif
    { "jlstream",            23,     768,    128 },
    { "a2dp_dec",            24,     768,      0 },
    /* file dec任务不打断jlstream任务运行,故优先级低于jlstream */
#if TCFG_DEC_AMR_16K_ENABLE //16k amr dec
    { "file_dec",            24,    1536,      0 },
#else
    { "file_dec",            24,     768,      0 },
#endif
    { "file_cache",          26,     512,      0 },
    { "write_file",          25,     512,      0 },
    { "vir_data_tx",         25,     768,      0 },
    /* 麦克风音效任务优先级要高 */
    { "mic_effect",          26,     768,      0 },
    /* 为了防止dac buf太大，通话一开始一直解码，导致编码输入数据需要很大的缓存，这里提高编码的优先级 */
    { "audio_enc",           26,     768,    128 },
    { "aec",                 12,     768,    128 },
    { "aec_dbg",             13,     512,    128 },
    { "aud_capture",         24,     512,    256 },
    { "dac",                 22,     256,    128 },
    { "spec_adv",            23,     512,    128 },
    { "kws",                  3,     256,     64 },
    { "smart_voice",         11,     512,    128 },
    { "audio_vad",           11,     768,      0 },
    { "key_tone",            25,     256,     32 },
    { "cvp_ref",             24,     256,    128 },
    { "CVP_RefTask",         14,     256,    128 },
#endif

    {0, 0},
};

#if 0
char task_designated_cpu(const char *task_name)//返回0指定CPU0运行,返回1指定CPU1运行,返回-1 CPU01都可以运行
{
    if (!strcmp(task_name, "init")) {
        return -1;//操作系统第一个任务init任务必须安装在核0,运行完会自动删除
    }
    if (!strcmp(task_name, "thread_fork_kill")) {
        return -1;
    }

    //用户在此增加指定任务

    return -1;
}
#endif
#ifdef CONFIG_NET_ENABLE
int net_video_event_hander(void *e)
{
    struct net_event *event = (struct net_event *)e;
    /* struct net_event *net = &event->u.net; */

    switch (event->event) {
    case NET_EVENT_CMD: {
        struct ctp_arg *event_arg = (struct ctp_arg *)event->arg;
        printf("IN NET_EVENT_CMD\n");
        ctp_cmd_analysis(event_arg->topic, event_arg->content, event_arg->cli);
        if (event_arg->content) {
            free(event_arg->content);
        }
        event_arg->content = NULL;
        if (event_arg) {
            free(event_arg);
        }
        return true;
    }
    case NET_EVENT_CONNECTED:
#if CONFIG_WIFI_CAMERA_HTTP_UPLOAD_ENABLE
        http_upload_manager_set_network_online(true);
        wifi_camera_http_trigger_scan();
#endif
        break;
    case NET_EVENT_DISCONNECTED:
    case NET_CONNECT_TIMEOUT_NOT_FOUND_SSID:
    case NET_CONNECT_ASSOCIAT_FAIL:
    case NET_CONNECT_ASSOCIAT_TIMEOUT:
    case NET_EVENT_DISCONNECTED_AND_REQ_CONNECT:
    case NET_SCR_EVENT_DISCONNECTED:
#if CONFIG_WIFI_CAMERA_HTTP_UPLOAD_ENABLE
        http_upload_manager_set_network_online(false);
#endif
        break;
    case NET_EVENT_DATA:
        break;
    default:
        break;
    }
    return false;
}
#endif



/*
 * sd卡插拔事件处理
 */
static void sd_event_handler(struct device_event *event)
{
    switch (event->event) {

    case DEVICE_EVENT_IN:
#if defined CONFIG_ENABLE_VLIST
        FILE_LIST_IN_MEM(1);
#endif
        break;
    case DEVICE_EVENT_OUT:
#if defined CONFIG_ENABLE_VLIST
        FILE_LIST_EXIT();
#endif
        break;


    }
}


static void power_off_timer_cb(void *p)
{
    sys_power_poweroff();
}

static int device_event_handler(struct sys_event *e)
{
    struct device_event *event = (struct device_event *)e->payload;

    if (e->from == DEVICE_EVENT_FROM_OTG) {
    } else if (e->from == DEVICE_EVENT_FROM_SD) {
#if TCFG_SD0_ENABLE || TCFG_SD1_ENABLE
        sd_event_handler(event);
#endif
#if defined(CONFIG_NET_ENABLE) && CONFIG_WIFI_CAMERA_HTTP_UPLOAD_ENABLE
        switch (event->event) {
        case DEVICE_EVENT_IN:
        case DEVICE_EVENT_ONLINE: {
            int storage_ok = storage_device_ready();
            http_upload_manager_set_storage_ready(storage_ok != 0);
            if (storage_ok) {
                wifi_camera_http_trigger_scan();
            }
            break;
        }
        case DEVICE_EVENT_OUT:
        case DEVICE_EVENT_OFFLINE:
            http_upload_manager_set_storage_ready(false);
            break;
        default:
            break;
        }
#endif
    } else if (e->from == DEVICE_EVENT_FROM_PC) {
        switch (event->event) {
        //添加USB弹窗
        case DEVICE_EVENT_IN:
#ifdef CONFIG_UI_ENABLE
            extern void usb_page_show(int arg);
            lvgl_rpc_post_func(usb_page_show, 1, 0);
#endif
            break;
        case DEVICE_EVENT_OUT:
#ifdef CONFIG_UI_ENABLE
            extern void usb_page_hide(int arg);
            lvgl_rpc_post_func(usb_page_hide, 1, 0);
#endif
            break;
        }

    } else if (e->from == DEVICE_EVENT_FROM_POWER && POWER_EVENT_POWER_AUTOOFF == event->event) { //关机事件
        //退出当前运行模式
        struct intent it;
        struct application *app;
        init_intent(&it);
        app = get_current_app();
        if (app) {
            it.action = ACTION_BACK;
            start_app(&it);
        }
#if defined(CONFIG_NET_ENABLE) && defined(CONFIG_WIFI_CAMERA_WEBSOCKET_ENABLE)
    wifi_camera_ws_report_shutdown("[WS][POWEROFF]");
#endif
#ifdef USE_LVGL_V8_UI_DEMO
        u8 time_out = 2;
        const char *image_path = NULL;
#ifdef PRODUCT_TEST_ENABLE
        if (mount("extflash", "mnt/extflash", "jlfat", 32, NULL)) {
            printf("extflash mount succ");
            FILE *fp = fopen("mnt/extflash/C/poweroff.jpg", "r");
            if (fp) {
                fclose(fp);
                image_path = "mnt/extflash/C/poweroff.jpg";
         printf("[WS][FIND] tone start ok (deadline=%u, last_start=%u, restart_interval=%u)\n",
             (unsigned int)g_find_tone_deadline_ms,
             (unsigned int)g_find_tone_last_start_ms,
             WIFI_CAMERA_FIND_RESTART_INTERVAL_MS);
            } else {
                printf("fopen poweroff err");
                image_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweroff.jpg";
            }
        } else {
            printf("extflash mount failed!!!");
            image_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweroff.jpg";
        }
#else
        image_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweroff.jpg";
#endif
        const char *audio_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweroff.mp3";
        int ret = logo_show(image_path, audio_path, time_out, NULL);
#endif

        //倒计时软件关机
        sys_timeout_add(0, power_off_timer_cb, 3000);//3000是关机动画显示时间
#ifdef CONFIG_PARK_ENABLE
            printf("[WS][FIND] tone stop ignored (not active)\n");
    } else if (e->from == DEVICE_EVENT_FROM_VIDEO && !strncmp((const char *)event->arg, "parking", 7)) {


        printf("[WS][FIND] tone stop executing (deadline=%u last_start=%u stop_timer=%u monitor_timer=%u running=%d)\n",
               (unsigned int)g_find_tone_deadline_ms,
               (unsigned int)g_find_tone_last_start_ms,
               g_find_tone_stop_timer_id,
               g_find_tone_monitor_timer_id,
               tone_player_runing());
        struct intent it;
        struct application *app;

        switch (event->event) {
        case DEVICE_EVENT_IN:
            puts("parking on\n"); //parking on
            puts("\n =============parking on eee video rec=========\n");
            extern u8 rec_park_flag;
            rec_park_flag++;
#ifdef CONFIG_UI_ENABLE
            extern void parking_page_show(int arg);
            lvgl_rpc_post_func(parking_page_show, 1, 0);
#endif

            sys_power_auto_shutdown_pause();
        printf("[WS][FIND] tone stop complete\n");
            return true;

        }
#endif
    }

    return 0;
}


void app_default_volume_change_handler(int inc)
{
    if (inc) {
        app_audio_volume_up(10);
#if TCFG_LOCAL_TWS_ENABLE && TCFG_LOCAL_TWS_SYNC_VOL
        local_tws_sync_vol();
#endif
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
        multi_box_bis_change_volume_notify();
#endif
    } else {
        app_audio_volume_down(10);

        if (app_audio_get_volume(APP_AUDIO_CURRENT_STATE) == app_audio_get_max_volume()) {
            if (tone_player_runing() == 0) {
#if TCFG_MAX_VOL_PROMPT
                play_tone_file(get_tone_files()->max_vol);
#endif
            }
        }
#if TCFG_LOCAL_TWS_ENABLE || TCFG_LOCAL_TWS_SYNC_VOL
        local_tws_sync_vol();
#endif
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
        multi_box_bis_change_volume_notify();
#endif
    }
}

static void app_default_key_click(struct key_event *key)
{
    switch (key->value) {
    case KEY_OK:
        break;
    case KEY_VOLUME_DEC:
    case KEY_UP:
    case KEY_PREV:
        app_default_volume_change_handler(0);
        break;
    case KEY_VOLUME_INC:
    case KEY_DOWN:
    case KEY_NEXT:
        app_default_volume_change_handler(1);
        break;
    case KEY_MODE:
        app_mode_change_next();
        break;
    default:
        break;
    }
}

static void app_default_key_long(struct key_event *key)
{
    switch (key->value) {
    case KEY_OK:
#if TCFG_MIC_EFFECT_ENABLE
        if (mic_effect_player_runing()) {
            mic_effect_player_close();
        } else {
            mic_effect_player_open();
        }
#endif
        break;
    case KEY_DOWN:
        /* app_mode_change(APP_MODE_BT); */
        /* config_network_start(); */
        break;

    case KEY_UP:
        /* app_mode_change(APP_MODE_BT); */
        /* config_network_start(); */
        break;



    default:
        break;
    }
}

static void app_default_key_event_handler(struct key_event *key)
{
    switch (key->action) {
    case KEY_EVENT_CLICK:
        app_default_key_click(key);
        break;
    case KEY_EVENT_LONG:
        app_default_key_long(key);
        break;
    case KEY_EVENT_HOLD:
        break;
    default:
        break;
    }
}

/*
 * 默认的系统事件处理函数
 * 当所有活动的app的事件处理函数都返回false时此函数会被调用
 */
void app_default_event_handler(struct sys_event *event)
{
    const struct app_event_handler *handler;

    for_each_app_event_handler(handler) {
        if (event->type == handler->event && handler->from == event->from) {
            handler->handler(event->payload);
        }
    }

    switch (event->type) {
    case SYS_KEY_EVENT:
        app_default_key_event_handler((struct key_event *)event->payload);
        break;
    case SYS_TOUCH_EVENT:
        break;
    case SYS_DEVICE_EVENT:
        device_event_handler(event);
        break;
    case SYS_NET_EVENT:
#ifdef CONFIG_NET_ENABLE
        net_video_event_hander((void *)event->payload);
#endif
        break;
    case SYS_BT_EVENT:
        break;
    default:
        ASSERT(0, "unknow event type: %s\n", __func__);
        break;
    }
}

/*
 * 开机动画播放完毕
 */
static void logo_poweron_play_end(void)
{
    lvgl_main_task_init();

#if defined(CONFIG_NET_ENABLE) && CONFIG_WIFI_CAMERA_HTTP_UPLOAD_ENABLE
    http_upload_manager_set_ui_busy(false);
#endif

#if TCFG_USB_SLAVE_ENABLE
    //检测usb从机在线并显示usb界面
    u32 state;
    u8 usb_slave_online = 0;
    for (usb_dev usb_id = 0; usb_id < USB_MAX_HW_NUM; usb_id++) {
        state = usb_otg_online(usb_id);
        if ((state == SLAVE_MODE) || (state == SLAVE_MODE_WAIT_CONFIRMATION)) {
            usb_slave_online = 1;
            break;
        }
    }
    if (usb_slave_online) {
        while (lvgl_ui_is_suspended()) {
            os_time_dly(1);
        }
#ifdef CONFIG_UI_ENABLE
        extern void usb_page_show(int arg);
        lvgl_rpc_post_func(usb_page_show, 1, 0);
#endif
    }
#endif

    key_event_enable();
    touch_event_enable();
}

#if defined(CONFIG_NET_ENABLE) && defined(CONFIG_WIFI_ENABLE)
extern void wearai_app_enter(void);
static void rtc_client_init(void);
static int wearai_rtc_monitor_thread_pid = 0;

static void wearai_rtc_monitor_thread(void *priv)
{
    while (1) {
        if (!wifi_is_on()) {
            os_time_dly(100);
            printf("[WearAI] WiFi is off, waiting...\n");
            continue;
        }

        enum wifi_sta_connect_state connect_state = wifi_get_sta_connect_state();
        int connected = 0;

        switch (connect_state) {
        case WIFI_STA_CONNECT_SUCC:
        case WIFI_STA_NETWORK_STACK_DHCP_SUCC:
        case WIFI_STA_IP_GOT_IPV6_SUCC:
            connected = 1;
            break;
        default:
            break;
        }

        if (!connected) {
            os_time_dly(100);
            printf("[WearAI] WiFi not connected, waiting...\n");
            continue;
        }

    struct wifi_mode_info mode_info = {0};
    char ssid_buf[33] = {0};
    char pwd_buf[65] = {0};

    /*
     * wifi_get_mode_cur_info 可能根据 mode 返回相应的数据指针，
     * 因此必须先设置 mode 再调用。函数通常会返回指向内部字符串
     * 的指针或 NULL。我们先让它返回指针，然后做安全拷贝。
     */
    mode_info.mode = STA_MODE;
    wifi_get_mode_cur_info(&mode_info);

    /* Diagnostic logging: print returned pointers and lengths to see what the API returns */
    printf("[WearAI][DIAG] mode_info.ssid=%p, mode_info.pwd=%p\n", mode_info.ssid, mode_info.pwd);
    size_t ssid_len = mode_info.ssid ? strnlen(mode_info.ssid, 128) : 0;
    size_t pwd_len = mode_info.pwd ? strnlen(mode_info.pwd, 128) : 0;
    printf("[WearAI][DIAG] ssid_len=%u, pwd_len=%u\n", (unsigned)ssid_len, (unsigned)pwd_len);
    if (mode_info.ssid && ssid_len > 0) {
        printf("[WearAI][DIAG] ssid prefix: %.16s\n", mode_info.ssid);
    }
    if (mode_info.pwd && pwd_len > 0) {
        printf("[WearAI][DIAG] pwd prefix: %.16s\n", mode_info.pwd);
    }

    const char *ssid_src = mode_info.ssid ? mode_info.ssid : "";
    const char *pwd_src = mode_info.pwd ? mode_info.pwd : "";

    /* 安全拷贝，保证以 '\0' 结尾 */
    strncpy(ssid_buf, ssid_src, sizeof(ssid_buf) - 1);
    ssid_buf[sizeof(ssid_buf) - 1] = '\0';
    strncpy(pwd_buf, pwd_src, sizeof(pwd_buf) - 1);
    pwd_buf[sizeof(pwd_buf) - 1] = '\0';

    const char *ssid = ssid_buf[0] ? ssid_buf : "<unknown>";
    printf("[WearAI] WiFi connected (ssid=%s), entering WearAI (CALL SUSPENDED FOR DIAG)\n", ssid);

    /* Temporarily suspend the actual WearAI call to check if it causes the crash. */
    wearai_app_enter(); 
    //rtc_client_init();
    break;
    }

    wearai_rtc_monitor_thread_pid = 0;
}
#endif

static int volume_monitor_thread_pid = 0;

// 音量监控线程：检测系统音量达到上限时触发 virtual_test
static void volume_monitor_thread(void *priv)
{
    u8 triggered = 0; // 触发标志，避免重复调用 virtual_test

    while (1) {
        s16 volume = app_audio_get_volume(APP_AUDIO_CURRENT_STATE); // 读取当前音量

        if (volume == 100) { // 达到最大音量阈值
            if (!triggered) {
                triggered = 1;
                printf("[virtual_test] volume=100, invoke virtual_test\n");
                int play_ret = virtual_test(NULL); // 仅在首次达到阈值时调用
                if (play_ret) {
                    printf("[virtual_test] playback start failed ret=%d\n", play_ret);
                }
            }
        } else {
            triggered = 0; // 音量回落后允许再次触发
        }

        os_time_dly(10); // 延时轮询，降低系统负载
    }
}

void rtc_client_init1(void)
{
    if (g_jrtc_session1) {
        return;
    }

    printf("[RTC] Initializing RTC client...\n");
    memset(g_wearai_rtc_members, 0, sizeof(g_wearai_rtc_members));

    if (g_jrtc_server_url && *g_jrtc_server_url) {
        jrtc_config_server(g_jrtc_server_url);
    }

    printf("[RTC] g_jrtc_app_key = %s, g_jrtc_uid =  %s , g_jrtc_aes_key = %s, g_jrtc_token= %s \n",
         g_jrtc_app_key, g_jrtc_uid, g_jrtc_aes_key, g_jrtc_token);
    jrtc1_config(g_jrtc_app_key, g_jrtc_uid, g_jrtc_aes_key, g_jrtc_token);

    if (!g_wearai_rtc_handler_registered1) {
        _jrtc_handler.on_user_joined = wearai_rtc_on_user_joined;
        _jrtc_handler.on_user_changed = wearai_rtc_on_user_changed;
        _jrtc_handler.on_user_offline = wearai_rtc_on_user_offline;
        g_wearai_rtc_handler_registered1 = 1;
    }

    g_jrtc_session1 = jrtc1_open(g_jrtc_peer_uid, g_jrtc_session_ticket,NULL, NULL);
    if (!g_jrtc_session1) {
        enum jrtc_error err = jrtc_error(NULL);
        extern char _jrtc_errstr[]; // 来自 jrtc0.h，用于调试最近错误描述
        printf("[RTC] jrtc1_open failed (err=%d)\n", err);
        if (_jrtc_errstr && _jrtc_errstr[0]) {
            printf("[RTC] detail: %s\n", _jrtc_errstr);
        }
        return;
    }

    printf("[RTC] session opened (peer=%s, ticket=%s)\n", g_jrtc_peer_uid, g_jrtc_session_ticket);
}

void rtc_client_init2(void)
{
    if (g_jrtc_session2) {
        return;
    }

    printf("[RTC] Initializing RTC client...\n");
    memset(g_wearai_rtc_members, 0, sizeof(g_wearai_rtc_members));

    if (g_jrtc_server_url && *g_jrtc_server_url) {
        jrtc_config_server(g_jrtc_server_url);
    }

    printf("[RTC] g_jrtc_app_key = %s, g_jrtc_uid =  %s , g_jrtc_aes_key = %s, g_jrtc_token= %s \n",
         g_jrtc_app_key,  g_jrtc_peer_uid, g_jrtc_aes_key, g_jrtc_token);
    jrtc1_config(g_jrtc_app_key, g_jrtc_peer_uid, g_jrtc_aes_key, g_jrtc_token);

    if (!g_wearai_rtc_handler_registered2) {
        _jrtc_handler.on_user_joined = wearai_rtc_on_user_joined;
        _jrtc_handler.on_user_changed = wearai_rtc_on_user_changed;
        _jrtc_handler.on_user_offline = wearai_rtc_on_user_offline;
        g_wearai_rtc_handler_registered2 = 1;
    }

    g_jrtc_session2 = jrtc1_open(g_jrtc_uid, g_jrtc_session_ticket,NULL, NULL);
    if (!g_jrtc_session2) {
        enum jrtc_error err = jrtc_error(NULL);
        extern char _jrtc_errstr[]; // 来自 jrtc0.h，用于调试最近错误描述
        printf("[RTC] jrtc1_open failed (err=%d)\n", err);
        if (_jrtc_errstr && _jrtc_errstr[0]) {
            printf("[RTC] detail: %s\n", _jrtc_errstr);
        }
        return;
    }

    printf("[RTC] session opened (peer=%s, ticket=%s)\n", g_jrtc_peer_uid, g_jrtc_session_ticket);
}

void rtc_client_close()
{
    if (g_jrtc_session1) {
		jrtc_leave(g_jrtc_session1, JRTC_EBYE);
		jrtc_close(g_jrtc_session1, JRTC_EBYE);
    }

    if (g_jrtc_session2) {
		jrtc_leave(g_jrtc_session2, JRTC_EBYE);
		jrtc_close(g_jrtc_session2, JRTC_EBYE);
    }
}

/*
 * 应用程序主函数
 */
void app_main()
{

    // for (u16 id = WIFI_STA_INFO_IDX_START; id < WIFI_STA_INFO_IDX_END; id++) {
    //     syscfg_write(id, NULL, 0);
    // }
    // syscfg_write(WIFI_INFO_IDX, NULL, 0);
    // syscfg_write(WIFI_SCAN_INFO, NULL, 0);
    // syscfg_write(WIFI_PMK_INFO, NULL, 0);
    // syscfg_write(WIFI_BSS_TABLE, NULL, 0);

    struct intent it;
    //开机后检测是否需要升级
    fs_update_task();

#if defined(CONFIG_NET_ENABLE) && CONFIG_WIFI_CAMERA_HTTP_UPLOAD_ENABLE
    if (wifi_camera_http_start()) {
        printf("[HTTP][APP] uploader start failed\n");
    } else {
        int storage_ok = storage_device_ready();
        http_upload_manager_set_storage_ready(storage_ok != 0);
        if (storage_ok) {
            wifi_camera_http_trigger_scan();
        }

#if defined(CONFIG_WIFI_ENABLE)
        int network_ok = 0;
        if (wifi_is_on()) {
            switch (wifi_get_sta_connect_state()) {
            case WIFI_STA_CONNECT_SUCC:
            case WIFI_STA_NETWORK_STACK_DHCP_SUCC:
            case WIFI_STA_IP_GOT_IPV6_SUCC:
                network_ok = 1;
                break;
            default:
                break;
            }
        }
        http_upload_manager_set_network_online(network_ok != 0);
        if (network_ok) {
            wifi_camera_http_trigger_scan();
        }
#endif
    }
#endif

#ifdef CONFIG_VIDEO_IQ_TOOLS_ENABLE
    u8 lcd_tools_main(void);
    lcd_tools_main();
#endif
    app_mode_change(APP_MODE_SYSTEM);

#ifdef USE_LVGL_V8_UI_DEMO
    int lvgl_main_task_init(void);
    u8 time_out = 2; //播放开机动画时间
    const char *image_path = NULL;
#ifdef PRODUCT_TEST_ENABLE
    if (mount("extflash", "mnt/extflash", "jlfat", 32, NULL)) {
        printf("extflash mount succ");
        FILE *fp = fopen("mnt/extflash/C/poweron.jpg", "r");
        if (fp) {
            printf("fopen succ\n");
            fclose(fp);
            image_path = "mnt/extflash/C/poweron.jpg";
        } else {
            printf("fopen poweron err");
            image_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweron.jpg";
        }
    } else {
        printf("extflash mount failed!!!");
        image_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweron.jpg";
    }
#else
    image_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweron.jpg";
#endif
    const char *audio_path = "mnt/sdfile/EXT_RESERVED/logopackres/logo/poweron.mp3";
    key_event_disable();
#if defined(CONFIG_NET_ENABLE) && CONFIG_WIFI_CAMERA_HTTP_UPLOAD_ENABLE
    http_upload_manager_set_ui_busy(true);
#endif
    int ret = logo_show(image_path, audio_path, time_out, (void *)logo_poweron_play_end);
    if (ret < 0) { //开机logo播放失败,则直接显示lvgl ui
        lvgl_main_task_init();
        key_event_enable();
        touch_event_enable();
#if defined(CONFIG_NET_ENABLE) && CONFIG_WIFI_CAMERA_HTTP_UPLOAD_ENABLE
        http_upload_manager_set_ui_busy(false);
#endif
    }
#else

    puts("------------- wifi_camera app main-------------\n");
    chat_manager_init();
    key_event_enable();

    app_mode_change(APP_MODE_REC);
    app_send_message(APP_MSG_REC_MAIN, 0);
    /* app_mode_change(APP_MODE_BT); */
#endif

#if CONFIG_WIFI_CAMERA_WEBSOCKET_AUTOSTART
    int ws_reg_err = wifi_camera_ws_client_register_handlers(&g_ws_handlers);
    if (ws_reg_err) {
        printf("[WS][APP] register handlers failed:%d\n", ws_reg_err);
    }
    wifi_camera_ws_client_start_default_async();
    wifi_camera_ws_start_location_timer();
#endif

#if defined CONFIG_ENABLE_VLIST
    /*生成文件列表*/
    if (dev_online(SDX_DEV)) {
        char buf[64];
        FILE_LIST_IN_MEM(1);
        strcpy(buf, "online:1");
        CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "SD_STATUS", "NOTIFY", buf);
    }
#endif

printf("[WearAI] app main over\n");
#if defined(CONFIG_NET_ENABLE) && defined(CONFIG_WIFI_ENABLE)
    printf("[WearAI] RTC monitor thread created\n");
    if (wearai_rtc_monitor_thread_pid == 0) {
        /* increase stack size to reduce risk of stack overflow from wearai library calls */
        int err = thread_fork("wearai_rtc_mon", 20, 8192, 0, &wearai_rtc_monitor_thread_pid, wearai_rtc_monitor_thread, NULL);
        if (err) {
            printf("[WearAI] create monitor thread failed: %d\n", err);
            wearai_rtc_monitor_thread_pid = 0;
        }
    }
#endif
printf("[WearAI] RTC monitor thread end \n");

    if (volume_monitor_thread_pid == 0) {
        int err = 0;
        //err = thread_fork("vol_virtual", 22, 1024, 0, &volume_monitor_thread_pid, volume_monitor_thread, NULL);
        if (err) {
            printf("[virtual_test] create volume thread failed: %d\n", err);
            volume_monitor_thread_pid = 0;
        }
    }

#if 0
void *ai_voice_recared_open(struct ai_rec_param *param);
struct ai_voice_param param = {0};
param.code_type = AUDIO_CODING_OPUS;
param.frame_ms = 80;
param.output = fs_write_date;
param.sample_rate = 16000;
param.format_mode = 3;
ai_voice_recared_open(&param);
#else


printf("-----virtual_test play start-----\n");
//int virtual_test(const char *file_path);
//virtual_test("storage/sd0/C/f160.opu");
return;

#endif
}





