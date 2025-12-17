#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "lvgl.h"
#include "custom.h"

lv_timer_t *prompt_timer = 0;
static char prompt_str[64] = { 0 };
extern bool update_date;
static bool home_skip_back_once;

extern int wifi_get_connection_signal_strength_level(void);
void ui_wifi_status_push(bool force);

#define UI_BATTERY_POLL_INTERVAL_MS   1000  // 电池状态轮询间隔（毫秒，对应1秒）
#define UI_WIFI_POLL_INTERVAL_MS      3000  // WiFi状态轮询间隔（毫秒）

static char ui_battery_percentage_str[8];

#if !LV_USE_GUIBUILDER_SIMULATOR
static lv_timer_t *ui_battery_poll_timer;
static lv_timer_t *ui_wifi_poll_timer;
#endif

void ui_home_request_skip_back_once(void)
{
    home_skip_back_once = true;
}

/*
*   顶层页面显示定时器回调--倒计时隐藏系统提示界面
*
*/
static void sys_prompt_timer_cb(lv_timer_t *timer)
{
    printf("[chili]: %s %d\n", __func__, __LINE__);
    lv_ui_sys_prompt * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
    if(!ui_scr) return;
    if (ui_scr->sys_prompt_del == false && lv_obj_is_valid(ui_scr->sys_prompt)) {
        lv_obj_add_flag(ui_scr->sys_prompt, LV_OBJ_FLAG_HIDDEN);
        unload_scr_sys_prompt(&guider_ui);
        //lv_obj_del(ui_scr->sys_prompt);
    }
    if (prompt_timer) {//删除定时器
        lv_timer_del(prompt_timer);
        prompt_timer = NULL;

    }

}


/*
*
* 顶层系统警告页面显示隐藏控制---后面用bool类型的模型回调实现
*@ show_time 填0立马隐藏，提示窗提示时间，单位ms
* @tips 提示语
*/
void sys_prompt_show_ctl(int32_t show_time, void *tips)
{
    printf("[chili]: %s show_time %d\n", __func__, show_time);
    if (show_time) {
        //倒计时隐藏
        strcpy(prompt_str, tips);
        if (prompt_timer == NULL) {
            prompt_timer = lv_timer_create(sys_prompt_timer_cb, show_time, 0);
        }
        lv_ui_sys_prompt * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
        if (ui_scr && ui_scr->sys_prompt_del == false && lv_obj_is_valid(ui_scr->sys_prompt)) {
            lv_obj_clear_flag(ui_scr->sys_prompt, LV_OBJ_FLAG_HIDDEN);
        } else {
            printf("[chili]: %s %d\n", __func__, __LINE__);
            setup_scr_sys_prompt(&guider_ui);
            ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
            lv_obj_clear_flag(ui_scr->sys_prompt, LV_OBJ_FLAG_HIDDEN);
            printf("[chili]: %s %d\n", __func__, __LINE__);
            gui_model_main_msg_init_ui();
            printf("[chili]: %s %d\n", __func__, __LINE__);
            gui_model_main_msg_init_events();
        }
        lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, tips, strlen(tips), 0);
    } else {
        lv_ui_sys_prompt *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
        if (!ui_scr) {
            return;
        }
        if (ui_scr->sys_prompt_del == false && lv_obj_is_valid(ui_scr->sys_prompt)) {
            lv_obj_add_flag(ui_scr->sys_prompt, LV_OBJ_FLAG_HIDDEN);
            unload_scr_sys_prompt(&guider_ui);
            lv_obj_del(ui_scr->sys_prompt);
        }

        if (prompt_timer) {//删除定时器
            lv_timer_del(prompt_timer);
            prompt_timer = NULL;

        }

    }
}
/*
* 系统警告提示框首次GET更新提示语
*
*/
int gui_model_main_msg_sys_prompt_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_SET) {
        strcpy(prompt_str, data->value_string);
    }
    data->value_string = prompt_str;
    return 0;
}

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "ui.h"
#include "sys_time.h"
#include "system/includes.h"
#include "asm/includes.h"
#include "event/device_event.h"
#include "event/event.h"
#include "syscfg/syscfg_id.h"
#include "action.h"
#include "app_power_manage.h"
#include "../generated/gui_images/gui_images.h"

#if defined(USE_ADC_TEST_DEMO)
extern int adc_get_remaining_battery_percentage(void);
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *  STATIC FUNCTION
 **********************/
//注册页面加载卸载回调

static int get_sys_time(struct sys_time *time)
{
    void *fd = dev_open("rtc", NULL);
    if (fd) {
        dev_ioctl(fd, IOCTL_GET_SYS_TIME, (u32)time);
        if (update_date) {
            time->year = db_select("datey");
            time->month = db_select("datem");
            time->day = db_select("dated");
            time->hour = db_select("dateh");
            time->min = db_select("datemi");
            dev_ioctl(fd, IOCTL_SET_SYS_TIME, (u32)time);
            dev_close(fd);
            update_date = false;
        }
        return 0;
    }
    return -EINVAL;
}

/**********************
 *  PUBILC FUNCTION
 **********************/
extern u8 lvgl_ui_is_suspended(void);
u8 lvgl_is_prepare(void)
{
    if (!lvgl_ui_is_suspended()) {
        return 1;
    }
    return 0;
}

static int ui_battery_percent_to_res(int percent, bool charging)
{
    if (charging) {
        return RES_CHARGING;
    }

    if (percent <= 10) {
        return RES_0;
    }
    if (percent <= 30) {
        return RES_1;
    }
    if (percent <= 50) {
        return RES_2;
    }
    if (percent <= 80) {
        return RES_3;
    }
    return RES_FULL;
}

static int ui_battery_get_percent_from_source(void)
{
#if defined(USE_ADC_TEST_DEMO)
    return adc_get_remaining_battery_percentage();
#else
    return sys_power_get_battery_persent();
#endif
}

static void ui_battery_push_internal(bool force, int percent_hint, bool hint_valid)
{
    if (!lvgl_is_prepare()) {
        return;
    }

    int percent = hint_valid ? percent_hint : ui_battery_get_percent_from_source();

    if (percent < 0) {
        percent = 0;
    } else if (percent > 100) {
        percent = 100;
    }

    bool charging = sys_power_is_charging() ? true : false;
    int res_id = ui_battery_percent_to_res(percent, charging);
    static int last_res_id = -1;
    static int last_percent_value = -1;

    if (force || res_id != last_res_id) {
        lvgl_module_msg_send_value(GUI_MODEL_MAIN_MSG_ID_BATTERY, res_id, 0);
        last_res_id = res_id;
    }

    if (force || percent != last_percent_value) {
        int written = snprintf(ui_battery_percentage_str, sizeof(ui_battery_percentage_str), "%d%%", percent);
        size_t payload_len = 0;
        if (written < 0) {
            ui_battery_percentage_str[0] = '\0';
        } else if ((size_t)written >= sizeof(ui_battery_percentage_str)) {
            payload_len = sizeof(ui_battery_percentage_str) - 1;
        } else {
            payload_len = (size_t)written;
        }
        lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, ui_battery_percentage_str, payload_len + 1, 0);
        last_percent_value = percent;
    }
}

static int ui_wifi_signal_level_to_res(int level)
{
    switch (level) {
    case 4:
        return RES_WIFI_4;
    case 3:
        return RES_WIFI_3;
    case 2:
        return RES_WIFI_2;
    case 1:
        return RES_WIFI_1;
    default:
        return RES_WIFI_NO;
    }
}

void ui_wifi_status_push(bool force)
{
    if (!lvgl_is_prepare()) {
        return;
    }

    static int last_res_id = -1;

#ifdef CONFIG_NET_ENABLE
    int signal_level = wifi_get_connection_signal_strength_level();
#else
    int signal_level = 0;
#endif

    int res_id = ui_wifi_signal_level_to_res(signal_level);

    if (force || res_id != last_res_id) {
        lvgl_module_msg_send_value(GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, res_id, 0);
        last_res_id = res_id;
    }
}

static void ui_wifi_poll_timer_cb(lv_timer_t *timer)
{
    (void)timer;
    ui_wifi_status_push(false);
}

void ui_wifi_start_polling(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    if (ui_wifi_poll_timer == NULL) {
        ui_wifi_poll_timer = lv_timer_create(ui_wifi_poll_timer_cb, UI_WIFI_POLL_INTERVAL_MS, NULL);
    }
#else
    (void)ui_wifi_poll_timer_cb;
#endif
}

void ui_wifi_stop_polling(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    if (ui_wifi_poll_timer != NULL) {
        lv_timer_del(ui_wifi_poll_timer);
        ui_wifi_poll_timer = NULL;
    }
#endif
}

#if !LV_USE_GUIBUILDER_SIMULATOR
static int gui_src_action_home_page(int action)
{
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        if (home_skip_back_once) {
            home_skip_back_once = false;
        }
        ui_battery_force_push();
        ui_wifi_status_push(true);
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
    default:
        break;
    }

    return 0;
}

REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_HOME_PAGE)
.onchange = gui_src_action_home_page,
};
#endif

void ui_battery_apply_percent(int percent_hint, int hint_valid)
{
    ui_battery_push_internal(true, percent_hint, hint_valid != 0);
}

void ui_battery_force_push(void)
{
    ui_battery_push_internal(true, -1, false);
}

static void ui_battery_poll_timer_cb(lv_timer_t *timer)
{
    (void)timer;
    ui_battery_push_internal(false, -1, false);
}

void ui_battery_start_polling(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    if (ui_battery_poll_timer == NULL) {
        ui_battery_poll_timer = lv_timer_create(ui_battery_poll_timer_cb, UI_BATTERY_POLL_INTERVAL_MS, NULL);
    }
#endif
}

void ui_battery_stop_polling(void)
{
#if !LV_USE_GUIBUILDER_SIMULATOR
    if (ui_battery_poll_timer != NULL) {
        lv_timer_del(ui_battery_poll_timer);
        ui_battery_poll_timer = NULL;
    }
#endif
}

static int ui_battery_power_event_handler(struct sys_event *event)
{
    if (event->from != DEVICE_EVENT_FROM_POWER) {
        return 0;
    }

    struct device_event *dev = (struct device_event *)event->payload;

    switch (dev->event) {
    case POWER_EVENT_POWER_CHANGE:
    case POWER_EVENT_POWER_WARNING:
    case POWER_EVENT_POWER_LOW:
    case POWER_EVENT_POWER_CHARGE:
        ui_battery_push_internal(true, -1, false);
        break;
    default:
        break;
    }

    return 0;
}

SYS_EVENT_STATIC_HANDLER_REGISTER(ui_battery_power_handler, 3) = {
    .event_type = SYS_DEVICE_EVENT,
    .prob_handler = ui_battery_power_event_handler,
    .post_handler = NULL,
};

void sys_update_post(void)
{
#if 0
    if (fs_update_set_file_path(CONFIG_UPGRADE_PATH) == true) {
        printf("[chili]: %s %d\n", __func__, __LINE__);
        extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
        lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 8000, (void *)_("sd_update"));
    }
#endif
}

void sys_update_cancel(void)
{
    extern void sys_prompt_show_ctl(int32_t show_time, void *tips);
    lvgl_rpc_post_func(sys_prompt_show_ctl, 2, 0, (void *)_("sd_update"));
}




#if 0
//sd卡状态图标更新
void post_msg2sd_icon(int online)
{
#ifdef USE_LVGL_V8_UI_DEMO
    if (online) {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_SD_ICON, (void *)RES_SD, sizeof(RES_SD), 0);
    } else {
        lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_SD_ICON, (void *)RES_SD_CLOSE, sizeof(RES_SD_CLOSE), 0);
    }
#endif // USE_LVGL_V8_UI_DEMO
}
#endif


#if 0
//电池电量图标更新
void post_msg2bat_icon(int vbt)
{
#ifdef USE_LVGL_V8_UI_DEMO
    //电量更新
    void *bat_icon = 0;
    //int vbt = get_vbat_level() * 10 / 42;
    //    printf("[chili] %s vbat:%d   \n",  __func__, vbt);
    if (vbt <= 15) {
        bat_icon = RES_0;
    } else if (vbt > 15 && vbt <= 25) {
        bat_icon = RES_1;
    } else if (vbt > 25 && vbt <= 50) {
        bat_icon = RES_2;
    } else if (vbt > 50 && vbt <= 75) {
        bat_icon = RES_3;
    } else if (vbt > 75 && vbt <= 100) {
        bat_icon = RES_FULL;
    } else { //(sys_power_is_charging())
        bat_icon = RES_CHARGING;
    }

    lvgl_module_msg_send_global_ptr(GUI_MODEL_MAIN_MSG_ID_BATTERY, bat_icon, sizeof(bat_icon), 0);
#endif // USE_LVGL_V8_UI_DEMO
}

//系统时间更新
int gui_model_main_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{

    static struct tm systime_var = { 0 };
    struct sys_time usr_time;
    get_sys_time(&usr_time);
    /*printf("[chili] %s  y:%d d:%d \n", __func__, usr_time.year, usr_time.day);*/
    systime_var.tm_year = usr_time.year - 1900;
    systime_var.tm_mon = usr_time.month - 1;
    systime_var.tm_mday = usr_time.day;
    systime_var.tm_hour = usr_time.hour;
    systime_var.tm_min = usr_time.min;
    systime_var.tm_sec = usr_time.sec;

    if (data == NULL) {
        data = &guider_msg_data;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        systime_var = data->value_time;
    }
    data->value_time = systime_var;
    return 0;
}
#endif



//SD卡图标
int gui_model_main_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    // static int32_t sd_icon_var = RES_SD_CLOSE;
    // if (data == NULL) {
    //     data = &guider_msg_data;
    // }
    // if (access == GUI_MSG_ACCESS_GET) {
    //     if (storage_device_available()) {
    //         sd_icon_var = RES_SD;
    //     } else {
    //         sd_icon_var = RES_SD_CLOSE;
    //     }
    // }
    // if (access == GUI_MSG_ACCESS_SET) {
    //     sd_icon_var = data->value_int;
    // }
    // data->value_int = sd_icon_var;
    // return 0;
}

#endif
#endif
