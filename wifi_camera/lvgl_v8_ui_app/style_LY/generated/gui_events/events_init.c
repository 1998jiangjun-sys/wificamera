#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "./events_init.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "lvgl.h"
#include "./callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../gui_group/gui_group.h"

#include "wifi/wifi_connect.h"  // 添加WiFi连接相关的头文件


typedef enum {
	WIFI_SEARCH_ENTRY_UNKNOWN = 0,
	WIFI_SEARCH_ENTRY_FROM_HOME_PAGE,
	WIFI_SEARCH_ENTRY_FROM_SETTING
} wifi_search_entry_t;

static wifi_search_entry_t s_wifi_search_entry_source = WIFI_SEARCH_ENTRY_UNKNOWN;

#ifdef CONFIG_NET_ENABLE
static int home_page_has_saved_sta_credentials(void)
{
	struct wifi_mode_info stored_info = {0};
	char ssid_buf[33] = {0};
	char pwd_buf[65] = {0};
	stored_info.ssid = ssid_buf;
	stored_info.pwd = pwd_buf;

	stored_info.mode = STA_MODE;

	if (wifi_get_mode_stored_info(&stored_info) != 0) {
		printf("[Home Page] 未找到已保存的WiFi信息\n");
		return 0;
	}

	if (stored_info.mode != STA_MODE) {
		printf("[Home Page] 保存的WiFi模式为 %d ，非STA模式，忽略\n", stored_info.mode);
		return 0;
	}

	if (!stored_info.ssid || strlen(stored_info.ssid) == 0) {
		printf("[Home Page] 保存的SSID为空\n");
		return 0;
	}

	if (!stored_info.pwd || strlen(stored_info.pwd) == 0) {
		printf("[Home Page] 保存的密码为空\n");
		return 0;
	}

	printf("[Home Page] 检测到已保存的WiFi: %s\n", stored_info.ssid);
	return 1;
}
#else
static int home_page_has_saved_sta_credentials(void)
{
	return 0;
}
#endif

static void home_page_update_wifi_prompt_visibility(lv_ui *ui)
{
	if (!ui) {
		return;
	}

	lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);

	if (!ui_scr || !ui_scr->home_page_view_2) {
		return;
	}

#ifdef CONFIG_NET_ENABLE
	if (home_page_has_saved_sta_credentials()) {
		lv_obj_add_flag(ui_scr->home_page_view_2, LV_OBJ_FLAG_HIDDEN);
		printf("[Home Page] 已隐藏home_page_view_2，直接使用已保存的WiFi\n");
		return;
	}
#endif

	lv_obj_clear_flag(ui_scr->home_page_view_2, LV_OBJ_FLAG_HIDDEN);
	printf("[Home Page] 未检测到有效的WiFi凭据，展示home_page_view_2\n");
}



extern void wifi_camera_find_tone_cancel_from_ui(const char *source);



#include "../../custom/custom.h"
#include "../gui_res/res_common.h"
static uint8_t s_rec_btn_recording = 0;

static lv_timer_t *s_video_rec_timer = NULL;
static uint32_t s_video_rec_elapsed_sec = 0;

static const int s_video_rec_digit_res_ids[10] = {
	GUI_RES_IMG_0_PNG,
	RES_IMG_1,
	RES_IMG_2,
	RES_IMG_3,
	RES_IMG_4,
	RES_IMG_5,
	RES_IMG_6,
	RES_IMG_7,
	RES_IMG_8,
	RES_IMG_9,
};

static const void *video_rec_get_digit_src(uint8_t digit)
{
	if (digit >= (sizeof(s_video_rec_digit_res_ids) / sizeof(s_video_rec_digit_res_ids[0]))) {
		digit = 0;
	}
	int res_id = s_video_rec_digit_res_ids[digit];
	return gui_get_res_path(res_id);
}

static void video_rec_set_digit(lv_obj_t *img, uint8_t digit)
{
	if (!img || !lv_obj_is_valid(img)) {
		return;
	}
	const void *src = video_rec_get_digit_src(digit);
	if (!src) {
		return;
	}
	lv_img_set_src(img, src);
	lv_obj_invalidate(img);
}

static void video_rec_update_time_display(lv_ui_video_rec *ui_scr, uint32_t elapsed_seconds)
{
	if (!ui_scr) {
		return;
	}

	uint32_t seconds = elapsed_seconds % 60U;
	uint32_t minutes = (elapsed_seconds / 60U) % 60U;
	uint32_t hours = elapsed_seconds / 3600U;
	if (hours > 99U) {
		hours = 99U;
	}

	video_rec_set_digit(ui_scr->video_rec_img_3, (uint8_t)(hours / 10U));
	video_rec_set_digit(ui_scr->video_rec_img_4, (uint8_t)(hours % 10U));
	video_rec_set_digit(ui_scr->video_rec_img_6, (uint8_t)(minutes / 10U));
	video_rec_set_digit(ui_scr->video_rec_img_7, (uint8_t)(minutes % 10U));
	video_rec_set_digit(ui_scr->video_rec_img_9, (uint8_t)(seconds / 10U));
	video_rec_set_digit(ui_scr->video_rec_img_10, (uint8_t)(seconds % 10U));
}

static void video_rec_stop_timer(void)
{
	if (s_video_rec_timer) {
		lv_timer_t *timer = s_video_rec_timer;
		s_video_rec_timer = NULL;
		lv_timer_del(timer);
	}
	s_video_rec_elapsed_sec = 0;
}

static void video_rec_reset_time_display(lv_ui *ui)
{
	if (!ui) {
		return;
	}
	lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
	if (!ui_scr) {
		return;
	}
	video_rec_update_time_display(ui_scr, 0);
}

static void video_rec_timer_cb(lv_timer_t *timer)
{
	if (!timer) {
		return;
	}
	lv_ui *ui = (lv_ui *)timer->user_data;
	if (!s_rec_btn_recording || !ui) {
		video_rec_stop_timer();
		return;
	}

	lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
	if (!ui_scr || !ui_scr->video_rec_view_1 || !lv_obj_is_valid(ui_scr->video_rec_view_1)) {
		video_rec_stop_timer();
		return;
	}

	s_video_rec_elapsed_sec++;
	video_rec_update_time_display(ui_scr, s_video_rec_elapsed_sec);
}

static void video_rec_start_timer(lv_ui *ui)
{
	if (!ui) {
		return;
	}

	video_rec_stop_timer();
	lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
	if (!ui_scr) {
		return;
	}

	video_rec_update_time_display(ui_scr, 0);

	s_video_rec_timer = lv_timer_create(video_rec_timer_cb, 1000, ui);
	if (!s_video_rec_timer) {
		printf("[Video Rec] failed to create timer\n");
	}
}


void video_rec_toggle_recording(lv_ui *ui, bool update_label)
{
	if (!ui) {
		return;
	}

	rec_control_ontouch();
	s_rec_btn_recording = !s_rec_btn_recording;
	if (s_rec_btn_recording) {
		video_rec_start_timer(ui);
	} else {
		video_rec_stop_timer();
		video_rec_reset_time_display(ui);
	}

	lv_ui_video_rec *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
	if (!ui_scr) {
		return;
	}

	if (update_label && ui_scr->video_rec_btn_1_label && lv_obj_is_valid(ui_scr->video_rec_btn_1_label)) {
		lv_label_set_text(ui_scr->video_rec_btn_1_label, s_rec_btn_recording ? "结束" : "录像");
	}

	if (ui_scr->video_rec_view_1 && lv_obj_is_valid(ui_scr->video_rec_view_1)) {
		if (s_rec_btn_recording) {
			lv_obj_clear_flag(ui_scr->video_rec_view_1, LV_OBJ_FLAG_HIDDEN);
		} else {
			lv_obj_add_flag(ui_scr->video_rec_view_1, LV_OBJ_FLAG_HIDDEN);
		}
	}

	if (ui_scr->video_rec_img_2 && lv_obj_is_valid(ui_scr->video_rec_img_2)) {
		if (s_rec_btn_recording) {
			lv_obj_clear_flag(ui_scr->video_rec_img_2, LV_OBJ_FLAG_HIDDEN);
		} else {
			lv_obj_add_flag(ui_scr->video_rec_img_2, LV_OBJ_FLAG_HIDDEN);
		}
	}
}

#define VIDEO_PHOTO_STICKER_MAX 8
#define VIDEO_PHOTO_STICKER_INDEX_NONE   (-1)
extern void video_photo_ui_set_sticker_index(int index);
static uint8_t s_video_photo_selected_sticker = 0;

typedef struct {
	uint16_t c_res_id;
	uint32_t png_res_id;
} video_photo_preview_resource_t;

static const video_photo_preview_resource_t s_video_photo_preview_map[VIDEO_PHOTO_STICKER_MAX] = {
	{RES_C_STICKER_1_120, 0},
	{RES_C_STICKER_2_120, 0},
	{RES_C_STICKER_3_120, 0},
	{RES_C_STICKER_4_120, 0},
	{RES_C_STICKER_5_120, 0},
	{RES_C_STICKER_6_120, 0},
	{RES_C_STICKER_8_120, 0},
	{RES_C_STICKER_7_120, 0},
};

static const void *video_photo_resolve_preview_src(size_t index)
{
	size_t count = sizeof(s_video_photo_preview_map) / sizeof(s_video_photo_preview_map[0]);
	if (count == 0) {
		return NULL;
	}
	if (index >= count) {
		index = 0;
	}
	const video_photo_preview_resource_t *entry = &s_video_photo_preview_map[index];
	if (entry->c_res_id != 0) {
		const lv_img_dsc_t *img = GUI_GET_C_IMAGE(entry->c_res_id);
		if (img) {
			return img;
		}
	}
	if (entry->png_res_id != 0) {
		const char *path = gui_get_res_path(entry->png_res_id);
		if (path) {
			return path;
		}
	}
	return GUI_GET_C_IMAGE(RES_C_STICKER_1_120);
}

static void video_photo_update_preview_image(lv_ui_video_photo *ui_scr, size_t index)
{
	if (!ui_scr) {
		return;
	}

	lv_obj_t *preview = ui_scr->video_photo_img_12;
	if (!preview || !lv_obj_is_valid(preview)) {
		return;
	}

	const void *src = video_photo_resolve_preview_src(index);
	if (!src) {
		return;
	}

	lv_img_set_src(preview, src);
	lv_obj_invalidate(preview);
	video_photo_ui_set_sticker_index((int)index);
}

static size_t video_photo_collect_stickers(lv_ui_video_photo *ui_scr, lv_obj_t **buffer, size_t capacity)
{
	if (!ui_scr || !buffer || capacity == 0) {
		return 0;
	}

	lv_obj_t *all[] = {
		ui_scr->video_photo_img_4,
		ui_scr->video_photo_img_5,
		ui_scr->video_photo_img_6,
		ui_scr->video_photo_img_7,
		ui_scr->video_photo_img_8,
		ui_scr->video_photo_img_9,
		ui_scr->video_photo_img_10,
		ui_scr->video_photo_img_11,
	};
	size_t total = sizeof(all) / sizeof(all[0]);
	if (total > capacity) {
		total = capacity;
	}
	for (size_t i = 0; i < total; ++i) {
		buffer[i] = all[i];
	}
	return total;
}

static void video_photo_apply_sticker_highlight(lv_ui_video_photo *ui_scr)
{
	lv_obj_t *stickers[VIDEO_PHOTO_STICKER_MAX];
	size_t count = video_photo_collect_stickers(ui_scr, stickers, VIDEO_PHOTO_STICKER_MAX);
	if (count == 0) {
		return;
	}
	if (s_video_photo_selected_sticker >= count) {
		s_video_photo_selected_sticker = (uint8_t)(count - 1);
	}
	for (size_t i = 0; i < count; ++i) {
		lv_obj_t *img = stickers[i];
		if (!img || !lv_obj_is_valid(img)) {
			continue;
		}
		if (i == s_video_photo_selected_sticker) {
			lv_obj_set_style_outline_color(img, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
			lv_obj_set_style_outline_width(img, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
			lv_obj_set_style_outline_opa(img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		} else {
			lv_obj_set_style_outline_width(img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
			lv_obj_set_style_outline_opa(img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		}
	}

	video_photo_update_preview_image(ui_scr, s_video_photo_selected_sticker);
}


static void video_photo_set_sticker_selection(lv_ui_video_photo *ui_scr, size_t index)
{
	if (!ui_scr) {
		return;
	}

	lv_obj_t *stickers[VIDEO_PHOTO_STICKER_MAX];
	size_t count = video_photo_collect_stickers(ui_scr, stickers, VIDEO_PHOTO_STICKER_MAX);
	if (count == 0) {
		return;
	}

	if (index >= count) {
		index = count - 1;
	}

	if (s_video_photo_selected_sticker != index) {
		s_video_photo_selected_sticker = (uint8_t)index;
	}

	video_photo_apply_sticker_highlight(ui_scr);
}

static void video_photo_select_sticker_by_obj(lv_ui_video_photo *ui_scr, lv_obj_t *target)
{
	if (!ui_scr || !target) {
		return;
	}

	lv_obj_t *stickers[VIDEO_PHOTO_STICKER_MAX];
	size_t count = video_photo_collect_stickers(ui_scr, stickers, VIDEO_PHOTO_STICKER_MAX);
	if (count == 0) {
		return;
	}

	for (size_t i = 0; i < count; ++i) {
		if (stickers[i] == target) {
			video_photo_set_sticker_selection(ui_scr, i);
			return;
		}
	}
}

static void video_photo_shift_sticker_selection(lv_ui_video_photo *ui_scr, int delta)
{
	lv_obj_t *stickers[VIDEO_PHOTO_STICKER_MAX];
	size_t count = video_photo_collect_stickers(ui_scr, stickers, VIDEO_PHOTO_STICKER_MAX);
	if (count == 0) {
		return;
	}
	int new_index = (int)s_video_photo_selected_sticker + delta;
	if (new_index < 0) {
		new_index = 0;
	} else if (new_index >= (int)count) {
		new_index = (int)count - 1;
	}
	video_photo_set_sticker_selection(ui_scr, (size_t)new_index);
}
#include "bitstore.h"
#include "../../custom/custom.h"
// 定义静态变量用于定时器
static lv_timer_t *usb_gif_timer = NULL;

// 定时器回调函数，用于切换到主页或语言选择界面
static void usb_gif_timer_cb(lv_timer_t *timer)
{	printf("USB GIF timer expired, checking language initialization status\n");
	
	// 检查语言是否已初始化
	int lang_initialized = db_select("lang_init");
	printf("Language initialization status: %d\n", lang_initialized);
	
	gui_scr_t *screen = NULL;
	
	// 如果语言未初始化（首次开机或恢复出厂设置后），则显示语言选择界面
	// 如果已初始化，则直接进入主页
	//if (lang_initialized == 0) 
	if (0) 
	{
		printf("Language not initialized yet, showing language selection screen\n");
		screen = ui_get_scr(GUI_SCREEN_LANGUAGE_SELECTION);
		if(screen != NULL) {
			printf("Language selection screen found, loading...\n");
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
			printf("ui_load_scr_anim called for language selection\n");
		} else {
			printf("ERROR: Language selection screen is NULL, fallback to home\n");
			screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
			if(screen != NULL) {
				ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
			}
		}
	} else {
		printf("Language already initialized, switching to home page\n");
		screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
		if(screen != NULL) {
			printf("Home screen found, loading...\n");
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true, false);
			printf("ui_load_scr_anim called for home page\n");
		} else {
			printf("ERROR: Home screen is NULL\n");
		}
	}
	
	// 删除定时器
	if (usb_gif_timer) {
		lv_timer_del(usb_gif_timer);
		usb_gif_timer = NULL;
	}

	usb_mark_boot_splash_done();
}
#include "../../custom/multi_language.h"

static void language_selection_set_icon(lv_obj_t *img, bool checked)
{
	if (!img || !lv_obj_is_valid(img)) {
		return;
	}

	const char *path = gui_get_res_path(checked ? GUI_RES_SELECT_PNG : GUI_RES_SELECT_NO_PNG);
	if (!path) {
		return;
	}

	lv_img_set_src(img, path);
	lv_obj_invalidate(img);
}

static void language_selection_refresh_icons(lv_ui_Language_Selection *ui_scr, int lang_id)
{
	if (!ui_scr) {
		return;
	}

	lv_obj_t *icons[] = {
		ui_scr->Language_Selection_img_6,
		ui_scr->Language_Selection_img_5,
		ui_scr->Language_Selection_img_8,
		ui_scr->Language_Selection_img_10,
		ui_scr->Language_Selection_img_12,
		ui_scr->Language_Selection_img_14,
		ui_scr->Language_Selection_img_16,
		ui_scr->Language_Selection_img_18,
	};

	for (size_t i = 0; i < sizeof(icons) / sizeof(icons[0]); ++i) {
		language_selection_set_icon(icons[i], false);
	}

	lv_obj_t *selected_icon = NULL;
	switch (lang_id) {
	case LANG_HI:
		selected_icon = ui_scr->Language_Selection_img_6;
		break;
	case LANG_ENGLISH_1:
		selected_icon = ui_scr->Language_Selection_img_5;
		break;
	case LANG_FR:
		selected_icon = ui_scr->Language_Selection_img_8;
		break;
	case LANG_PT:
		selected_icon = ui_scr->Language_Selection_img_10;
		break;
	case LANG_ES:
		selected_icon = ui_scr->Language_Selection_img_12;
		break;
	case LANG_RU:
		selected_icon = ui_scr->Language_Selection_img_14;
		break;
	case LANG_AR:
		selected_icon = ui_scr->Language_Selection_img_16;
		break;
	case LANG_ZH_CN:
	default:
		selected_icon = ui_scr->Language_Selection_img_18;
		break;
	}

	language_selection_set_icon(selected_icon, true);
}

static void language_selection_handle_locale_click(lv_event_t *e, const char *locale)
{
	if (!locale) {
		return;
	}

	lv_ui *ui = lv_event_get_user_data(e);
	if (!ui) {
		return;
	}

	multi_language_apply_locale(locale);
	int lang_id = db_select("lag");
	lv_ui_Language_Selection *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LANGUAGE_SELECTION);
	language_selection_refresh_icons(ui_scr, lang_id);
}
#include "system/includes.h"
extern void wifi_user_scan_request_async(u32 delay_ms);
extern void wifi_user_scan_cancel_async(void);
#ifdef CONFIG_NET_ENABLE
#include "wifi/wifi_connect.h"
#endif

#include "../../custom/ui_wifi_list.h"

static volatile u8 s_user_scan_requested = 0;
static char s_selected_ssid[33];
static u8 s_selected_ssid_valid = 0;


static void wifi_search_promote_connected_network(void)
{
#ifdef CONFIG_NET_ENABLE
	if (!wifi_is_on()) {
		return;
	}

	enum wifi_sta_connect_state connect_state = wifi_get_sta_connect_state();
	bool is_connected = false;

	switch (connect_state) {
	case WIFI_STA_CONNECT_SUCC:
	case WIFI_STA_NETWORK_STACK_DHCP_SUCC:
	case WIFI_STA_IP_GOT_IPV6_SUCC:
		is_connected = true;
		break;
	default:
		break;
	}

	if (!is_connected) {
		return;
	}

	char ssid_buf[33] = {0};
	char pwd_buf[65] = {0};
	struct wifi_mode_info mode_info = {0};
	mode_info.mode = STA_MODE;
	mode_info.ssid = ssid_buf;
	mode_info.pwd = pwd_buf;
	wifi_get_mode_cur_info(&mode_info);

	if (!mode_info.ssid || mode_info.ssid[0] == '\0') {
		return;
	}

	printf("[WiFi Search] 当前已连接SSID: %s，提升至列表顶部\n", mode_info.ssid);
	wifi_list_update_connection_status(mode_info.ssid, true);
#endif
}

// WiFi项目点击回调函数
static void wifi_item_clicked_callback(const char* ssid, int rssi, int auth_mode)
{
	printf("[WiFi List] 用户选择了WiFi: %s, 信号强度: %d dBm, 认证模式: %d\n", ssid, rssi, auth_mode);

	if (ssid) {
		strncpy(s_selected_ssid, ssid, sizeof(s_selected_ssid) - 1);
		s_selected_ssid[sizeof(s_selected_ssid) - 1] = '\0';
		s_selected_ssid_valid = 1;
		printf("[WiFi List] 已缓存选中的SSID: %s\n", s_selected_ssid);
	} else {
		s_selected_ssid_valid = 0;
	}

	// 隐藏WiFi列表
	wifi_list_hide();
	  // 跳转到WiFi连接页面
	gui_scr_t* wifi_conn_scr = ui_get_scr(GUI_SCREEN_WIFI_CONNECTION);
	if (wifi_conn_scr) {
		ui_load_scr_anim(&guider_ui, wifi_conn_scr, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false, false, false);
		printf("[WiFi List] 成功跳转到WiFi连接页面\n");
	} else {
		printf("[WiFi List] 错误：无法获取WiFi连接页面\n");
	}
}

// 供外部调用的函数：显示WiFi扫描结果
void show_wifi_scan_results(struct wifi_scan_ssid_info* scan_results, uint32_t count)
{
    printf("[WiFi Search] 显示WiFi扫描结果，共 %d 个网络\n", count);
    
    // 获取当前WiFi搜索界面
    lv_ui_WIFI_search * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_WIFI_SEARCH);
    
    if (count > 0 && scan_results) {
        // 隐藏"正在搜索附近可用的网络"文字
		if (ui_scr && ui_scr->WIFI_search_lbl_4) {
			lv_obj_add_flag(ui_scr->WIFI_search_lbl_4, LV_OBJ_FLAG_HIDDEN);
        }
        
        // 显示"选取附近的WLAN"文字
		if (ui_scr && ui_scr->WIFI_search_lbl_5) {
			lv_obj_clear_flag(ui_scr->WIFI_search_lbl_5, LV_OBJ_FLAG_HIDDEN);
        }
        
        // 显示WiFi列表 (位置在搜索按钮下方)
        wifi_list_show(WIFI_LIST_POS_X, WIFI_LIST_POS_Y, WIFI_LIST_WIDTH, WIFI_LIST_HEIGHT);
        
        // 更新WiFi列表数据
        wifi_list_update_data(scan_results, count);
				wifi_search_promote_connected_network();
        
        printf("[WiFi Search] WiFi列表已显示并更新\n");
    } else {
        printf("[WiFi Search] 没有WiFi扫描结果可显示\n");
        
        // 隐藏"正在搜索附近可用的网络"文字
		if (ui_scr && ui_scr->WIFI_search_lbl_4) {
			lv_obj_add_flag(ui_scr->WIFI_search_lbl_4, LV_OBJ_FLAG_HIDDEN);
        }
        
        // 显示"选取附近的WLAN"文字
		if (ui_scr && ui_scr->WIFI_search_lbl_5) {
			lv_obj_clear_flag(ui_scr->WIFI_search_lbl_5, LV_OBJ_FLAG_HIDDEN);
        }
        
        wifi_list_hide();
    }
}

// wifi_app_task.c 会通过 extern 调用此函数判断是否需要打印扫描结果
u8 is_user_scan_requested(void)
{
    return s_user_scan_requested;
}

// wifi_app_task.c 在打印完成后调用，清除标志
void reset_user_scan_flag(void)
{
    s_user_scan_requested = 0;
}

// WiFi搜索功能实现
#include <string.h>
//静态变量来跟踪键盘状态
static int wifi_keyboard_mode = 0;  // 0: 符号键盘, 1: 字母键盘
static int wifi_letter_case = 0;    // 0: 小写, 1: 大写
#include "wifi/wifi_connect.h"  // 添加WiFi连接相关的头文件
static volatile u8 s_auto_scan_enabled = 1;
extern void wifi_sta_enable_save_after_connect(void);
static lv_timer_t *s_wifi_password_hint_timer = NULL;
static void wifi_password_hint_timer_cb(lv_timer_t *timer)
{
	if (timer == NULL) {
		return;
	}
	lv_obj_t *hint = (lv_obj_t *)timer->user_data;
	if (hint && lv_obj_is_valid(hint)) {
		lv_obj_add_flag(hint, LV_OBJ_FLAG_HIDDEN);
	}
	s_wifi_password_hint_timer = NULL;
	lv_timer_del(timer);
}
#include <stdbool.h>

static const char *photo_quality_to_text(int quality)
{
	switch (quality) {
	case PHOTO_QUA_LO:
		return "低";
	case PHOTO_QUA_MD:
		return "中";
	case PHOTO_QUA_HI:
	default:
		return "高";
	}
}
#include "bitstore.h"
#include "asm/dmm.h"
#include "syscfg/syscfg_id.h"
#define BRIGHTNESS_DB_KEY           "brt"
static u8 s_last_saved_brightness = 0xFF;

#define BRIGHTNESS_PERCENT_MIN      0
#define BRIGHTNESS_PERCENT_MAX      100
#define BRIGHTNESS_PERCENT_DEFAULT  50

static u8 brightness_clamp_percent(int32_t value)
{
	if (value < BRIGHTNESS_PERCENT_MIN) {
		return BRIGHTNESS_PERCENT_MIN;
	}
	if (value > BRIGHTNESS_PERCENT_MAX) {
		return BRIGHTNESS_PERCENT_MAX;
	}
	return (u8)value;
}

static float brightness_calc_gain(u8 percent)
{
	float gain = (float)percent / 50.0f;
	if (gain < 0.1f) {
		gain = 0.1f;
	}
	return gain;
}

static void brightness_update_label_and_hw(lv_ui_brightness * ui_scr, u8 percent)
{
	if (ui_scr == NULL) {
		return;
	}

	if (ui_scr->brightness_lbl_1) {
		lv_label_set_text_fmt(ui_scr->brightness_lbl_1, "%d%%", percent);
	}

	set_brightenss_ccmf_param(brightness_calc_gain(percent));
}

static void brightness_sync_slider_label_hw(lv_ui_brightness * ui_scr, u8 percent)
{
	if (ui_scr == NULL) {
		return;
	}

	if (ui_scr->brightness_slider_1) {
		lv_slider_set_value(ui_scr->brightness_slider_1, percent, LV_ANIM_OFF);
	}

	brightness_update_label_and_hw(ui_scr, percent);
}

static void brightness_persist_if_needed(u8 percent)
{
	u8 clamped = brightness_clamp_percent(percent);
	if (s_last_saved_brightness == clamped) {
		return;
	}

	if (db_update(BRIGHTNESS_DB_KEY, clamped) == 0) {
		s_last_saved_brightness = clamped;
		printf("[Brightness] Persisted value %d\n", clamped);
	} else {
		printf("[Brightness] Failed to persist value %d\n", clamped);
	}
}

u8 brightness_settings_get_value(void)
{
	if (s_last_saved_brightness <= BRIGHTNESS_PERCENT_MAX) {
		return s_last_saved_brightness;
	}

	int stored = (int)db_select(BRIGHTNESS_DB_KEY);
	if (stored < BRIGHTNESS_PERCENT_MIN || stored > BRIGHTNESS_PERCENT_MAX) {
		stored = BRIGHTNESS_PERCENT_DEFAULT;
		if (db_update(BRIGHTNESS_DB_KEY, stored) != 0) {
			printf("[Brightness] Failed to restore default value %d\n", stored);
		} else {
			printf("[Brightness] Restored default value %d\n", stored);
		}
	}

	s_last_saved_brightness = (u8)stored;
	return s_last_saved_brightness;
}
#include "audio_config.h"


#define VOLUME_PERCENT_MIN      0
#define VOLUME_PERCENT_MAX      100
#define VOLUME_PERCENT_DEFAULT  50

static s16 s_volume_max_steps = -1;
static u8 s_last_saved_volume_percent = 0xFF;

static u8 volume_clamp_percent(int32_t value)
{
	if (value < VOLUME_PERCENT_MIN) {
		return VOLUME_PERCENT_MIN;
	}
	if (value > VOLUME_PERCENT_MAX) {
		return VOLUME_PERCENT_MAX;
	}
	return (u8)value;
}

static s16 volume_get_max_steps(void)
{
	if (s_volume_max_steps <= 0) {
		s_volume_max_steps = app_audio_get_max_volume();
		if (s_volume_max_steps <= 0) {
			s_volume_max_steps = app_audio_volume_max_query(AppVol_BT_MUSIC);
		}
		if (s_volume_max_steps <= 0) {
			s_volume_max_steps = VOLUME_PERCENT_MAX;
		}
		app_audio_set_max_volume(APP_AUDIO_STATE_MUSIC, s_volume_max_steps);
		printf("[Volume] max steps cached: %d\n", s_volume_max_steps);
	}
	return s_volume_max_steps;
}

static s16 volume_percent_to_steps(u8 percent)
{
	s16 max_steps = volume_get_max_steps();
	if (percent >= VOLUME_PERCENT_MAX) {
		return max_steps;
	}
	if (percent <= VOLUME_PERCENT_MIN) {
		return VOLUME_PERCENT_MIN;
	}
	return (s16)((percent * max_steps + 50) / 100);
}

static u8 volume_steps_to_percent(s16 steps)
{
	s16 max_steps = volume_get_max_steps();
	if (steps <= 0) {
		return VOLUME_PERCENT_MIN;
	}
	if (steps >= max_steps) {
		return VOLUME_PERCENT_MAX;
	}
	return (u8)((steps * 100 + max_steps / 2) / max_steps);
}

static u8 volume_get_saved_percent(void)
{
	s16 stored_steps = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
	if (stored_steps < 0) {
		stored_steps = 0;
	}
	s16 max_steps = volume_get_max_steps();
	if (stored_steps > max_steps) {
		stored_steps = max_steps;
	}
	return volume_steps_to_percent(stored_steps);
}

static void volume_update_label_and_hw(lv_ui_volume * ui_scr, u8 percent)
{
	if (ui_scr == NULL) {
		return;
	}

	if (ui_scr->volume_lbl_2) {
		lv_label_set_text_fmt(ui_scr->volume_lbl_2, "%d%%", percent);
	}

	u8 clamped = volume_clamp_percent(percent);
	if (s_last_saved_volume_percent == clamped) {
		return;
	}

	s16 max_steps = volume_get_max_steps();
	s16 target_steps = volume_percent_to_steps(clamped);
	app_audio_set_max_volume(APP_AUDIO_STATE_MUSIC, max_steps);
	app_audio_set_volume(APP_AUDIO_STATE_MUSIC, target_steps, 1);
	printf("[Volume] Applied value %d%% (step %d / max %d)\n", clamped, target_steps, max_steps);
	s_last_saved_volume_percent = clamped;
}

static void volume_sync_slider_label_hw(lv_ui_volume * ui_scr, u8 percent)
{
	if (ui_scr == NULL) {
		return;
	}

	if (ui_scr->volume_slider_1) {
		lv_slider_set_value(ui_scr->volume_slider_1, percent, LV_ANIM_OFF);
	}

	volume_update_label_and_hw(ui_scr, percent);
}

static lv_timer_t *s_volume_mute_hint_timer = NULL;

static void volume_mute_hint_timer_cb(lv_timer_t *timer)
{
	if (timer == NULL) {
		return;
	}
	lv_obj_t *volume_view = (lv_obj_t *)timer->user_data;
	if (volume_view && lv_obj_is_valid(volume_view)) {
		lv_obj_add_flag(volume_view, LV_OBJ_FLAG_HIDDEN);
	}
	s_volume_mute_hint_timer = NULL;
	lv_timer_del(timer);
}
#include "../gui_res/res_common.h"

static u32 dormancy_normalize_seconds(u32 seconds)
{
	if (seconds == 0) {
		return 0;
	}
	if (seconds <= 60) {
		return 60;
	}
	if (seconds <= 180) {
		return 180;
	}
	return 0;
}


static void dormancy_set_icon(lv_obj_t *img, bool checked)
{
	if (img == NULL) {
		return;
	}

	const char *path = gui_get_res_path(checked ? GUI_RES_SELECT_PNG : GUI_RES_SELECT_NO_PNG);
	if (path == NULL) {
		return;
	}

	lv_img_set_src(img, path);
	lv_obj_invalidate(img);
}

static void dormancy_refresh_ui(lv_ui_dormancy *ui_scr, u32 seconds)
{
	if (ui_scr == NULL) {
		return;
	}

	u32 normalized = dormancy_normalize_seconds(seconds);

	dormancy_set_icon(ui_scr->dormancy_img_4, normalized == 60);
	dormancy_set_icon(ui_scr->dormancy_img_5, normalized == 180);
	dormancy_set_icon(ui_scr->dormancy_img_7, normalized == 0);
}

static void dormancy_apply_setting(lv_ui *ui, u32 seconds)
{
	if (ui == NULL) {
		return;
	}

	db_update("pro", seconds);
	u32 stored = db_select("pro");
	ui_lcd_light_time_set(stored);

	lv_ui_dormancy *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DORMANCY);
	dormancy_refresh_ui(ui_scr, stored);
}

extern int gui_set_camera_config(char *label, uint32_t value);

static void image_quality_set_icon(lv_obj_t *img, bool checked)
{
	if (!img || !lv_obj_is_valid(img)) {
		return;
	}

	const char *path = gui_get_res_path(checked ? GUI_RES_SELECT_PNG : GUI_RES_SELECT_NO_PNG);
	if (!path) {
		return;
	}

	lv_img_set_src(img, path);
	lv_obj_invalidate(img);
}

static void image_quality_refresh_ui(lv_ui_image_size *ui_scr, uint8_t quality)
{
	if (!ui_scr) {
		return;
	}

	uint8_t normalized = quality;
	if (normalized > PHOTO_QUA_HI) {
		normalized = PHOTO_QUA_HI;
	}

	image_quality_set_icon(ui_scr->image_size_img_3, normalized == PHOTO_QUA_HI);
	image_quality_set_icon(ui_scr->image_size_img_5, normalized == PHOTO_QUA_MD);
	image_quality_set_icon(ui_scr->image_size_img_7, normalized == PHOTO_QUA_LO);
}

static void image_quality_apply(lv_ui *ui, uint8_t quality)
{
	if (!ui) {
		return;
	}

	db_update("qua", quality);
	gui_set_camera_config("qua", quality);

	lv_ui_image_size *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_IMAGE_SIZE);
	image_quality_refresh_ui(ui_scr, quality);
	printf("[Image Size] quality set to %u\n", (unsigned)quality);
}
#include "storage_device.h"
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "os/os_api.h"
#endif
#include "../gui_images/gui_images.h"
static void tf_formatting_force_refresh(void)
{
	lv_disp_t *disp = lv_disp_get_default();
	if (disp) {
		lv_refr_now(disp);
	}
}

static void tf_formatting_update_progress(lv_ui_TF_formatting_2 *ui_scr, uint8_t value)
{
	if (!ui_scr) {
		return;
	}

	if (ui_scr->TF_formatting_2_bar_1 && lv_obj_is_valid(ui_scr->TF_formatting_2_bar_1)) {
		lv_bar_set_value(ui_scr->TF_formatting_2_bar_1, value, LV_ANIM_OFF);
	}
	if (ui_scr->TF_formatting_2_lbl_1 && lv_obj_is_valid(ui_scr->TF_formatting_2_lbl_1)) {
		lv_label_set_text_fmt(ui_scr->TF_formatting_2_lbl_1, "%d%%", value);
	}

	tf_formatting_force_refresh();
}

typedef struct {
	lv_ui_TF_formatting_2 *ui_scr;
	lv_timer_t *timer;
	volatile uint8_t finished;
	volatile uint8_t canceled;
	volatile int err;
	uint8_t progress;
} tf_formatting_task_ctx_t;

static tf_formatting_task_ctx_t g_tf_formatting_ctx = {0};

static void tf_formatting_finalize(tf_formatting_task_ctx_t *ctx);
static void tf_formatting_progress_timer_cb(lv_timer_t *timer);
static void tf_formatting_worker(void *priv);


static void tf_formatting_finalize(tf_formatting_task_ctx_t *ctx)
{
	if (!ctx || ctx->canceled) {
		return;
	}

	lv_ui_TF_formatting_2 *ui_scr = ctx->ui_scr;
	if (!ui_scr) {
		return;
	}

	tf_formatting_update_progress(ui_scr, 100);

	if (ui_scr->TF_formatting_2_view_3 && lv_obj_is_valid(ui_scr->TF_formatting_2_view_3)) {
		lv_obj_add_flag(ui_scr->TF_formatting_2_view_3, LV_OBJ_FLAG_HIDDEN);
	}
	if (ui_scr->TF_formatting_2_view_4 && lv_obj_is_valid(ui_scr->TF_formatting_2_view_4)) {
		lv_obj_clear_flag(ui_scr->TF_formatting_2_view_4, LV_OBJ_FLAG_HIDDEN);
	}
	if (ui_scr->TF_formatting_2_img_5 && lv_obj_is_valid(ui_scr->TF_formatting_2_img_5)) {
		lv_obj_clear_state(ui_scr->TF_formatting_2_img_5, LV_STATE_DISABLED);
	}

	const bool is_success = (ctx->err == 0);
	if (ui_scr->TF_formatting_2_lbl_4 && lv_obj_is_valid(ui_scr->TF_formatting_2_lbl_4)) {
		lv_label_set_text(ui_scr->TF_formatting_2_lbl_4, is_success ? "格式化完成" : "格式化失败");
	}
	if (ui_scr->TF_formatting_2_img_4 && lv_obj_is_valid(ui_scr->TF_formatting_2_img_4)) {
		if (is_success) {
			lv_img_set_src(ui_scr->TF_formatting_2_img_4, gui_get_res_path(GUI_RES_SET_OK_PNG));
		} else {
			lv_img_set_src(ui_scr->TF_formatting_2_img_4, GUI_GET_C_IMAGE(RES_C_SET_FAIL));
		}
		lv_obj_invalidate(ui_scr->TF_formatting_2_img_4);
	}

	if (is_success) {
		printf("[TF Formatting] Format completed successfully.\n");
	} else {
		printf("[TF Formatting] Format failed with error code: %d\n", ctx->err);
	}

	ctx->ui_scr = NULL;
	ctx->finished = 0;
	ctx->progress = 100;
}

static void tf_formatting_progress_timer_cb(lv_timer_t *timer)
{
	tf_formatting_task_ctx_t *ctx = (tf_formatting_task_ctx_t *)timer->user_data;
	if (!ctx) {
		lv_timer_del(timer);
		return;
	}

	if (ctx->canceled || !ctx->ui_scr) {
		lv_timer_del(timer);
		ctx->timer = NULL;
		return;
	}

	lv_ui_TF_formatting_2 *ui_scr = ctx->ui_scr;
	if (!(ui_scr->TF_formatting_2_bar_1 && lv_obj_is_valid(ui_scr->TF_formatting_2_bar_1))) {
		lv_timer_del(timer);
		ctx->timer = NULL;
		return;
	}

	if (!ctx->finished) {
		if (ctx->progress < 90) {
			ctx->progress = (ctx->progress < 80) ? (ctx->progress + 10) : 90;
		}
		tf_formatting_update_progress(ui_scr, ctx->progress);
		return;
	}

	if (ctx->progress < 100) {
		ctx->progress = (ctx->progress >= 95) ? 100 : (ctx->progress + 5);
		tf_formatting_update_progress(ui_scr, ctx->progress);
		return;
	}

	lv_timer_del(timer);
	ctx->timer = NULL;
	tf_formatting_finalize(ctx);
}

static void tf_formatting_worker(void *priv)
{
	tf_formatting_task_ctx_t *ctx = (tf_formatting_task_ctx_t *)priv;
	if (!ctx) {
		return;
	}

	ctx->err = sdcard_storage_device_format(SDX_DEV);
	ctx->finished = 1;
}

static const char *photo_resolution_to_text(int res)
{
	switch (res) {
	case PHOTO_RES_VGA:
		return "480P";
	case PHOTO_RES_1M:
		return "720P";
	case PHOTO_RES_2M:
		return "1080P";
	default:
		return "1080P";
	}
}

static const char *video_resolution_to_text(int res)
{
	switch (res) {
	case VIDEO_RES_VGA:
		return "480P";
	case VIDEO_RES_720P:
		return "720P";
	case VIDEO_RES_1080P:
		return "1080P";
	default:
		return "720P";
	}
}
extern int rec_set_config(char *label, uint32_t value);


static uint8_t photo_resolution_normalize(int value)
{
	switch (value) {
	case PHOTO_RES_VGA:
	case PHOTO_RES_1M:
	case PHOTO_RES_2M:
		return (uint8_t)value;
	default:
		return PHOTO_RES_2M;
	}
}

static void photo_resolution_refresh_ui(lv_ui_image_resolution *ui_scr, uint8_t res)
{
	if (!ui_scr) {
		return;
	}

	image_quality_set_icon(ui_scr->image_resolution_img_3, res == PHOTO_RES_2M);
	image_quality_set_icon(ui_scr->image_resolution_img_5, res == PHOTO_RES_1M);
	image_quality_set_icon(ui_scr->image_resolution_img_7, res == PHOTO_RES_VGA);
}

static void photo_resolution_apply(lv_ui *ui, uint8_t res)
{
	if (!ui) {
		return;
	}

	db_update("pres", res);
	gui_set_camera_config("pres", res);

	lv_ui_image_resolution *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_IMAGE_RESOLUTION);
	photo_resolution_refresh_ui(ui_scr, res);

	lv_ui_seting *setting_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SETING);
	if (setting_scr && setting_scr->seting_lbl_15 && lv_obj_is_valid(setting_scr->seting_lbl_15)) {
		lv_label_set_text(setting_scr->seting_lbl_15, photo_resolution_to_text(res));
	}
	video_photo_icon_reshow(SUBPAGE_RESOLUTION);
	printf("[Image Resolution] photo resolution set to %s (%u)\n", photo_resolution_to_text(res), (unsigned)res);
}

static uint8_t video_resolution_normalize(int value)
{
	switch (value) {
	case VIDEO_RES_VGA:
	case VIDEO_RES_720P:
		return (uint8_t)value;
	case VIDEO_RES_1080P:
	default:
		return VIDEO_RES_720P;
	}
}

static void video_resolution_refresh_ui(lv_ui_video_resolution *ui_scr, uint8_t res)
{
	if (!ui_scr) {
		return;
	}

	image_quality_set_icon(ui_scr->video_resolution_img_4, res == VIDEO_RES_720P);
	image_quality_set_icon(ui_scr->video_resolution_img_5, res == VIDEO_RES_VGA);
}

static void video_resolution_apply(lv_ui *ui, uint8_t res)
{
	if (!ui) {
		return;
	}

	db_update("res", res);
	rec_set_config("res", res);

	lv_ui_video_resolution *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_RESOLUTION);
	video_resolution_refresh_ui(ui_scr, res);

	lv_ui_seting *setting_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SETING);
	if (setting_scr && setting_scr->seting_lbl_22 && lv_obj_is_valid(setting_scr->seting_lbl_22)) {
		lv_label_set_text(setting_scr->seting_lbl_22, video_resolution_to_text(res));
	}
	video_rec_icon_reshow(SUBPAGE_RESOLUTION);
	printf("[Video Resolution] video resolution set to %s (%u)\n", video_resolution_to_text(res), (unsigned)res);
}

typedef struct {
	lv_ui_Restore_factory_2 *ui_scr;
	lv_timer_t *timer;
	lv_timer_t *reboot_timer;
	uint8_t finished;
	uint8_t canceled;
	uint8_t progress;
} factory_reset_task_ctx_t;

static factory_reset_task_ctx_t g_factory_reset_ctx = {0};

static void factory_reset_update_progress(lv_ui_Restore_factory_2 *ui_scr, uint8_t value)
{
	if (!ui_scr) {
		return;
	}

	if (ui_scr->Restore_factory_2_bar_1 && lv_obj_is_valid(ui_scr->Restore_factory_2_bar_1)) {
		lv_bar_set_value(ui_scr->Restore_factory_2_bar_1, value, LV_ANIM_OFF);
	}
	if (ui_scr->Restore_factory_2_lbl_1 && lv_obj_is_valid(ui_scr->Restore_factory_2_lbl_1)) {
		lv_label_set_text_fmt(ui_scr->Restore_factory_2_lbl_1, "%d%%", value);
	}

	tf_formatting_force_refresh();
}

static void factory_reset_reboot_timer_cb(lv_timer_t *timer)
{
	lv_timer_del(timer);
	cpu_reset();
}

static void factory_reset_finalize(factory_reset_task_ctx_t *ctx)
{
	if (!ctx || ctx->canceled) {
		return;
	}

	lv_ui_Restore_factory_2 *ui_scr = ctx->ui_scr;
	if (!ui_scr) {
		return;
	}

	factory_reset_update_progress(ui_scr, 100);

	if (ui_scr->Restore_factory_2_view_3 && lv_obj_is_valid(ui_scr->Restore_factory_2_view_3)) {
		lv_obj_add_flag(ui_scr->Restore_factory_2_view_3, LV_OBJ_FLAG_HIDDEN);
	}
	if (ui_scr->Restore_factory_2_view_4 && lv_obj_is_valid(ui_scr->Restore_factory_2_view_4)) {
		lv_obj_clear_flag(ui_scr->Restore_factory_2_view_4, LV_OBJ_FLAG_HIDDEN);
	}

	
	if (ctx->reboot_timer) {
		lv_timer_del(ctx->reboot_timer);
	}
	ctx->reboot_timer = lv_timer_create(factory_reset_reboot_timer_cb, 2000, NULL);

	ctx->ui_scr = NULL;
	ctx->finished = 0;
	ctx->progress = 100;
}

static void factory_reset_progress_timer_cb(lv_timer_t *timer)
{
	factory_reset_task_ctx_t *ctx = (factory_reset_task_ctx_t *)timer->user_data;
	if (!ctx) {
		lv_timer_del(timer);
		return;
	}

	if (ctx->canceled || !ctx->ui_scr) {
		lv_timer_del(timer);
		ctx->timer = NULL;
		return;
	}

	if (!ctx->finished) {
		if (ctx->progress < 90) {
			ctx->progress = (ctx->progress < 80) ? (ctx->progress + 10) : 90;
		}
		factory_reset_update_progress(ctx->ui_scr, ctx->progress);
		return;
	}

	if (ctx->progress < 100) {
		ctx->progress = (ctx->progress >= 95) ? 100 : (ctx->progress + 5);
		factory_reset_update_progress(ctx->ui_scr, ctx->progress);
		if (ctx->progress < 100) {
			return;
		}
	}

	lv_timer_del(timer);
	ctx->timer = NULL;
	factory_reset_finalize(ctx);
}

static void factory_reset_execute(factory_reset_task_ctx_t *ctx)
{
	if (!ctx || ctx->canceled) {
		return;
	}

	setting_reset();
	ctx->finished = 1;
}

static void factory_reset_async_cb(void *user_data)
{
	factory_reset_task_ctx_t *ctx = (factory_reset_task_ctx_t *)user_data;
	factory_reset_execute(ctx);
}
#include "chat_manager.h"
#include "wifi_camera_http.h"
static bool chat_active_friend_set_by_index(size_t index);

struct chat_active_friend_context {
	bool valid;
	size_t index;
	char group_id[CHAT_MANAGER_MAX_GROUP_ID_LEN];
	int group_type;
	char display_name[CHAT_MANAGER_MAX_NAME_LEN];
};

static struct chat_active_friend_context s_chat_active_friend = {0};
static void chat_voice_capture_finalize(unsigned int total_len);
static bool s_chat_recording_active = false;

typedef enum {
	VOICE_CAPTURE_TARGET_NONE = 0,
	VOICE_CAPTURE_TARGET_AI_QA,
	VOICE_CAPTURE_TARGET_CHAT,
} voice_capture_target_t;

static voice_capture_target_t s_voice_capture_target = VOICE_CAPTURE_TARGET_NONE;

static uint32_t s_voice_capture_started_ms = 0;
static uint32_t s_voice_capture_stopped_ms = 0;
static bool s_voice_capture_has_duration = false;

static void voice_capture_timing_reset(void)
{
	s_voice_capture_started_ms = 0;
	s_voice_capture_stopped_ms = 0;
	s_voice_capture_has_duration = false;
}

static uint32_t voice_capture_get_duration_ms(void)
{
	if (!s_voice_capture_has_duration) {
		return 0;
	}
	return (uint32_t)(s_voice_capture_stopped_ms - s_voice_capture_started_ms);
}

static void address_book_refresh_friend_list(lv_ui *ui)
{
if (!ui) {
		return;
	}

	lv_ui_address_book *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_ADDRESS_BOOK);
	if (!ui_scr) {
		return;
	}

	lv_obj_t *containers[] = {
		ui_scr->address_book_view_5,
		ui_scr->address_book_view_6,
		ui_scr->address_book_view_7,
		ui_scr->address_book_view_8,
		ui_scr->address_book_view_9,
		ui_scr->address_book_view_10,
		ui_scr->address_book_view_11,
		ui_scr->address_book_view_12,
		ui_scr->address_book_view_13,
		ui_scr->address_book_view_14,
	};

	lv_obj_t *labels[] = {
		ui_scr->address_book_lbl_3,
		ui_scr->address_book_lbl_5,
		ui_scr->address_book_lbl_7,
		ui_scr->address_book_lbl_9,
		ui_scr->address_book_lbl_10,
		ui_scr->address_book_lbl_13,
		ui_scr->address_book_lbl_14,
		ui_scr->address_book_lbl_16,
		ui_scr->address_book_lbl_17,
		ui_scr->address_book_lbl_18,
	};

	lv_obj_t *avatars[] = {
		// ui_scr->address_book_img_6,
		// ui_scr->address_book_img_8,
		// ui_scr->address_book_img_10,
		// ui_scr->address_book_img_12,
		// ui_scr->address_book_img_14,
		// ui_scr->address_book_img_16,
		// ui_scr->address_book_img_18,
		// ui_scr->address_book_img_20,
		// ui_scr->address_book_img_22,
		// ui_scr->address_book_img_24,
	};

	const int avatar_fallback_res_ids[] = {
		// GUI_RES_AVATAR_9_64PX_PNG,
		// GUI_RES_AVATAR_1_64PX_PNG,
		// GUI_RES_AVATAR_2_64PX_PNG,
		// GUI_RES_AVATAR_3_64PX_PNG,
		// GUI_RES_SET_SIZE_PNG,
		// GUI_RES_SET_TF_PNG,
		// GUI_RES_SET_PICTURE_PNG,
		// GUI_RES_SET_BINDING_PNG,
		// GUI_RES_SET_VERSION_PNG,
		// GUI_RES_SET_RECOVER_PNG,
	};

	const size_t slot_total = sizeof(containers) / sizeof(containers[0]);
	const size_t max_friends = slot_total;
	size_t friend_count = chat_manager_get_friend_count();
	if (friend_count > max_friends) {
		friend_count = max_friends;
	}

	for (size_t i = 0; i < slot_total; ++i) {
		lv_obj_t *container = containers[i];
		lv_obj_t *label = labels[i];
		//lv_obj_t *avatar = avatars[i];
		lv_obj_t *avatar = NULL;
		if (i < friend_count) {
			const struct chat_friend_entry *entry = chat_manager_get_friend(i);
			const char *name = "";
			if (entry) {
				if (entry->group_name[0] != '\0') {
					name = entry->group_name;
				} else if (entry->group_id[0] != '\0') {
					name = entry->group_id;
				}
			}
			if (container && lv_obj_is_valid(container)) {
				lv_obj_clear_flag(container, LV_OBJ_FLAG_HIDDEN);
			}
			if (label && lv_obj_is_valid(label)) {
				lv_label_set_text(label, name);
			}
			if (avatar && lv_obj_is_valid(avatar) &&
			    i < (sizeof(avatar_fallback_res_ids) / sizeof(avatar_fallback_res_ids[0])) &&
			    avatar_fallback_res_ids[i] != 0) {
				lv_img_set_src(avatar, gui_get_res_path(avatar_fallback_res_ids[i]));
			}
		} else {
			if (container && lv_obj_is_valid(container)) {
				lv_obj_add_flag(container, LV_OBJ_FLAG_HIDDEN);
			}
			if (label && lv_obj_is_valid(label)) {
				lv_label_set_text(label, "");
			}
			if (avatar && lv_obj_is_valid(avatar) &&
			    i < (sizeof(avatar_fallback_res_ids) / sizeof(avatar_fallback_res_ids[0])) &&
			    avatar_fallback_res_ids[i] != 0) {
				lv_img_set_src(avatar, gui_get_res_path(avatar_fallback_res_ids[i]));
			}
		}
	}

	if (!s_chat_active_friend.valid && friend_count > 0) {
		chat_active_friend_set_by_index(0);
	}
}

static void chat_active_friend_clear(void)
{
	memset(&s_chat_active_friend, 0, sizeof(s_chat_active_friend));
	s_chat_active_friend.valid = false;
	chat_friend_history_set_active_group(NULL);
}

static int chat_friend_resolve_group_type(const struct chat_friend_entry *entry)
{
	if (!entry) {
		return 1;
	}

	if (entry->source_mask & CHAT_MANAGER_FRIEND_SOURCE_SYNC_FRIEND) {
		return 2;
	}

	if (entry->source_mask & CHAT_MANAGER_FRIEND_SOURCE_GROUP_LIST) {
		return (entry->group_type > 0) ? entry->group_type : 1;
	}

	if (entry->group_type > 0) {
		return entry->group_type;
	}

	return 1;
}

static bool chat_active_friend_set_from_entry(const struct chat_friend_entry *entry, size_t index)
{
	if (!entry || !entry->in_use || !entry->group_id[0]) {
		chat_active_friend_clear();
		return false;
	}

	s_chat_active_friend.valid = true;
	s_chat_active_friend.index = index;
	s_chat_active_friend.group_type = chat_friend_resolve_group_type(entry);
	snprintf(s_chat_active_friend.group_id,
		 sizeof(s_chat_active_friend.group_id),
		 "%s",
		 entry->group_id);
	s_chat_active_friend.group_id[sizeof(s_chat_active_friend.group_id) - 1] = '\0';

	const char *name = entry->group_name[0] ? entry->group_name : entry->group_id;
	snprintf(s_chat_active_friend.display_name,
		 sizeof(s_chat_active_friend.display_name),
		 "%s",
		 name ? name : "");
	s_chat_active_friend.display_name[sizeof(s_chat_active_friend.display_name) - 1] = '\0';
	chat_friend_history_set_active_group(s_chat_active_friend.group_id);
	return true;
}

static bool chat_active_friend_set_by_index(size_t index)
{
	const struct chat_friend_entry *entry = chat_manager_get_friend(index);
	return chat_active_friend_set_from_entry(entry, index);
}

static const struct chat_friend_entry *chat_active_friend_get(void)
{
	if (!s_chat_active_friend.valid) {
		return NULL;
	}
	return chat_manager_get_friend(s_chat_active_friend.index);
}
#include "os/os_api.h"
#include <stdio.h>
#include "watchai_api_platform.h"

extern int watchai_aud_file_play_stop(void);
extern void virtual_dev_player_stop_all(void);
static bool ai_voice_recorder_is_running(void);
static int ai_voice_upload_thread_pid = 0;
static void *g_ai_voice_recorder_handle = NULL;
static bool s_ai_q_a_recording_active = false;

struct audio_buffer_writer {
	unsigned int total_len;
	int write_failed;
};
static struct audio_buffer_writer g_audio_buffer_writer = {0};

static void audio_buffer_writer_reset(void)
{
	watchai_media_voice_buffer_reset();
	g_audio_buffer_writer.total_len = 0;
	g_audio_buffer_writer.write_failed = 0;
	voice_capture_timing_reset();
}

static void ai_voice_upload_cancel(void)
{
	if (ai_voice_upload_thread_pid) {
		thread_kill(&ai_voice_upload_thread_pid, KILL_WAIT);
		ai_voice_upload_thread_pid = 0;
		printf("[ai_voice] upload worker canceled\n");
	}
}

static void ai_voice_recorder_cancel(const char *tag, bool reset_buffer)
{
	const char *log_tag = tag ? tag : "ai_voice";

	if (ai_voice_recorder_is_running()) {
		ai_voice_recorder_close(g_ai_voice_recorder_handle);
		g_ai_voice_recorder_handle = NULL;
		printf("[%s] recording cancel\n", log_tag);
	}

	if (reset_buffer) {
		audio_buffer_writer_reset();
	} else {
		voice_capture_timing_reset();
	}

	s_ai_q_a_recording_active = false;
	s_chat_recording_active = false;
}

static void ai_q_a_stop_audio_playback(void)
{
	virtual_dev_player_stop_all();
	watchai_aud_file_play_stop();
}

static void ai_q_a_stop_all_ai_processes(const char *tag)
{
	ai_q_a_stop_audio_playback();
	ai_voice_upload_cancel();
	ai_voice_recorder_cancel(tag, true);
}
#include <stdbool.h>
#include "media/audio_def.h"

/*
 * 通过配置 CONFIG_HOME_PAGE_AI_VOICE_CODEC 在 OPUS 与 AMR 编码之间切换。
 * 默认使用 OPUS，若需 AMR，请在项目配置中将其重定义为 AUDIO_CODING_AMR。
 */
#ifndef CONFIG_HOME_PAGE_AI_VOICE_CODEC
#define CONFIG_HOME_PAGE_AI_VOICE_CODEC AUDIO_CODING_AMR
#endif


#if (CONFIG_HOME_PAGE_AI_VOICE_CODEC == AUDIO_CODING_AMR)
#define HOME_AI_VOICE_FILE_EXT        "amr"
#define HOME_AI_VOICE_SAMPLE_RATE     8000
#define HOME_AI_VOICE_FRAME_MS        20
#define HOME_AI_VOICE_FORMAT_MODE     0
#define HOME_AI_VOICE_COMPLEXITY      0
#define HOME_AI_VOICE_QUALITY         7
#elif (CONFIG_HOME_PAGE_AI_VOICE_CODEC == AUDIO_CODING_OPUS)
#define HOME_AI_VOICE_FILE_EXT        "opu"
#define HOME_AI_VOICE_SAMPLE_RATE     16000
#define HOME_AI_VOICE_FRAME_MS        80
#define HOME_AI_VOICE_FORMAT_MODE     2
#define HOME_AI_VOICE_COMPLEXITY      0
#define HOME_AI_VOICE_QUALITY         0
#else
#error "Unsupported CONFIG_HOME_PAGE_AI_VOICE_CODEC value"
#endif



#include "server/ai_server.h"
#include <stdio.h>
#include <string.h>
#include "system/includes.h"

extern int storage_device_ready(void);
extern u32 timer_get_ms(void);
extern void *ai_voice_recorder_open(struct ai_voice_param *param);
extern int ai_voice_recorder_close(void *priv);
extern void watchai_homepage_scr_process(void);


#if 0
struct audio_sd_writer {
	FILE *fp;
	char path[64];
};

static struct audio_sd_writer g_audio_writer;
static u32 g_audio_writer_seq = 1;

static void audio_writer_close(void)
{
	if (g_audio_writer.fp) {
		fclose(g_audio_writer.fp);
		g_audio_writer.fp = NULL;
	}
	g_audio_writer.path[0] = '\0';
}

static FILE *audio_writer_prepare_file(void)
{
	if (!storage_device_ready()) {
		return NULL;
	}

	if (!g_audio_writer.fp) {
		if (g_audio_writer.path[0] == '\0') {
			snprintf(g_audio_writer.path, sizeof(g_audio_writer.path),
				"storage/sd0/C/rec_%05u.%s", g_audio_writer_seq, HOME_AI_VOICE_FILE_EXT);
		}

		g_audio_writer.fp = fopen(g_audio_writer.path, "wb");
		if (!g_audio_writer.fp) {
			printf("[audio_writer] open %s failed\n", g_audio_writer.path);
			g_audio_writer.path[0] = '\0';
			return NULL;
		}
		printf("[audio_writer] open %s success\n", g_audio_writer.path);
		g_audio_writer_seq++;

	}

	return g_audio_writer.fp;
}

static int fs_write_data(void *file, void *voice_buf, unsigned int voice_len)
{
	if (!voice_buf || voice_len == 0) {
		return 0;
	}

	FILE *fp = audio_writer_prepare_file();
	if (!fp) {
		return 0;
	}

	size_t written = fwrite(voice_buf, 1, voice_len, fp);
	if (written != voice_len) {
		printf("[audio_writer] write failed, req=%u, actual=%u\n", voice_len, (unsigned int)written);
	}

	if (written > 0) {
		printf("[audio_writer] +%u bytes\n", (unsigned int)written);
	}

	return (int)written;
}
#else

static void audio_buffer_writer_abort(void)
{
	watchai_media_voice_buffer_reset();
	g_audio_buffer_writer.total_len = 0;
	g_audio_buffer_writer.write_failed = 1;
	s_voice_capture_target = VOICE_CAPTURE_TARGET_NONE;
	voice_capture_timing_reset();
}

static int audio_buffer_writer_append(const void *data, unsigned int len)
{
	if (!data || len == 0 || g_audio_buffer_writer.write_failed) {
		return 0;
	}

	int ret = watchai_media_voice_buffer_append((const unsigned char *)data, len);
	if (ret < 0) {
		g_audio_buffer_writer.write_failed = 1;
		printf("[audio_buffer] append failed len=%u\n", len);
		return 0;
	}

	g_audio_buffer_writer.total_len += (unsigned int)ret;
	return ret;
}

static unsigned int audio_buffer_writer_length(void)
{
	return g_audio_buffer_writer.total_len;
}

static void audio_buffer_writer_on_stop(void)
{
	if (g_audio_buffer_writer.write_failed) {
		printf("[audio_buffer] recording aborted due to previous write error\n");
		watchai_media_voice_buffer_reset();
		s_voice_capture_target = VOICE_CAPTURE_TARGET_NONE;
		return;
	}

	unsigned int total = audio_buffer_writer_length();
	if (total == 0) {
		printf("[audio_buffer] no audio captured, skip upload\n");
		watchai_media_voice_buffer_reset();
		s_voice_capture_target = VOICE_CAPTURE_TARGET_NONE;
		return;
	}

	switch (s_voice_capture_target) {
	case VOICE_CAPTURE_TARGET_CHAT:
		chat_voice_capture_finalize(total);
		break;
	case VOICE_CAPTURE_TARGET_AI_QA:
		watchai_homepage_scr_process();
		break;
	case VOICE_CAPTURE_TARGET_NONE:
	default:
		watchai_homepage_scr_process();
		break;
	}

	s_voice_capture_target = VOICE_CAPTURE_TARGET_NONE;
}

static void chat_voice_capture_finalize(unsigned int total_len)
{
	printf("[chat_voice] finalize len=%u\n", total_len);

	if (total_len == 0) {
		printf("[chat_voice] skip upload: empty buffer\n");
		watchai_media_voice_buffer_reset();
		voice_capture_timing_reset();
		return;
	}

	if (!s_chat_active_friend.valid || !s_chat_active_friend.group_id[0]) {
		printf("[chat_voice] skip upload: no active friend\n");
		watchai_media_voice_buffer_reset();
		voice_capture_timing_reset();
		return;
	}

	const unsigned char *buffer = watchai_media_voice_buffer_data();
	if (!buffer) {
		printf("[chat_voice] skip upload: buffer null\n");
		watchai_media_voice_buffer_reset();
		voice_capture_timing_reset();
		return;
	}

	uint32_t duration_ms = voice_capture_get_duration_ms();
	if (duration_ms == 0) {
		duration_ms = HOME_AI_VOICE_FRAME_MS;
	}
	if (duration_ms < HOME_AI_VOICE_FRAME_MS) {
		duration_ms = HOME_AI_VOICE_FRAME_MS;
	}

#if defined(CONFIG_NET_ENABLE)
	char remote_url[256] = {0};

	const struct chat_friend_entry *entry = chat_active_friend_get();
	int group_type = chat_friend_resolve_group_type(entry);
	if (group_type <= 0) {
		group_type = (s_chat_active_friend.group_type > 0) ? s_chat_active_friend.group_type : 1;
	}

	struct wifi_camera_chat_message_params params = {0};
	params.group_id = s_chat_active_friend.group_id;
	params.group_type = group_type;
	params.content_type = WIFI_CAMERA_CHAT_CONTENT_VOICE;
	params.buffer = buffer;
	params.buffer_size = total_len;
	params.audio_duration_ms = duration_ms;
	params.audio_type = HOME_AI_VOICE_FILE_EXT;
	params.display_name = s_chat_active_friend.display_name[0] ? s_chat_active_friend.display_name : "我";
	params.request_return_url = true;
	params.out_remote_url = remote_url;
	params.out_remote_url_len = sizeof(remote_url);

	int ret = wifi_camera_http_send_group_message(&params);
	if (ret) {
		printf("[chat_voice] upload failed err=%d\n", ret);
	} else {
		printf("[chat_voice] upload success url=%s\n", remote_url);
	}
#else
	printf("[chat_voice] network disabled, skip upload\n");
#endif

	watchai_media_voice_buffer_reset();
	voice_capture_timing_reset();
	s_chat_recording_active = false;
}

static int fs_write_data(void *file, void *voice_buf, unsigned int voice_len)
{
	return audio_buffer_writer_append(voice_buf, voice_len);
}
#endif



static void ai_voice_upload_worker(void *priv)
{
	const char *tag = priv ? (const char *)priv : "ai_voice";
	printf("[%s] upload worker start\n", tag);
	audio_buffer_writer_on_stop();
	printf("[%s] upload worker finish\n", tag);
	ai_voice_upload_thread_pid = 0;
}

static void ai_voice_recorder_schedule_upload(const char *tag)
{
	const char *log_tag = tag ? tag : "ai_voice";
	if (ai_voice_upload_thread_pid) {
		printf("[%s] upload worker already running (pid=%d)\n", log_tag, ai_voice_upload_thread_pid);
		return;
	}

	int ret = thread_fork("ai_voice_up", 11, 2048, 0, &ai_voice_upload_thread_pid, ai_voice_upload_worker, (void *)log_tag);
	if (ret != 0) {
		printf("[%s] upload worker fork failed (%d), fallback inline\n", log_tag, ret);
		ai_voice_upload_thread_pid = 0;
		audio_buffer_writer_on_stop();
	}
}

static bool ai_voice_recorder_is_running(void)
{
	return g_ai_voice_recorder_handle != NULL;
}

static bool ai_voice_recorder_start(const char *tag)
{
	const char *log_tag = tag ? tag : "ai_voice";

	if (ai_voice_recorder_is_running()) {
		printf("[%s] recorder already running\n", log_tag);
		return true;
	}

	if (ai_voice_upload_thread_pid) {
		printf("[%s] previous upload still running (pid=%d)\n", log_tag, ai_voice_upload_thread_pid);
		return false;
	}

#if 0
	audio_writer_close();
	g_audio_writer.path[0] = '\0';
#else
	audio_buffer_writer_reset();
#endif

	struct ai_voice_param param = {0};
	param.code_type = CONFIG_HOME_PAGE_AI_VOICE_CODEC;
	param.frame_ms = HOME_AI_VOICE_FRAME_MS;
	param.output = fs_write_data;
	param.sample_rate = HOME_AI_VOICE_SAMPLE_RATE;
	param.format_mode = HOME_AI_VOICE_FORMAT_MODE;
	param.complexity = HOME_AI_VOICE_COMPLEXITY;
	param.quality = HOME_AI_VOICE_QUALITY;

	g_ai_voice_recorder_handle = ai_voice_recorder_open(&param);
	if (!g_ai_voice_recorder_handle) {
		printf("[%s] start recorder failed\n", log_tag);
#if 0
		return false;
#else
		audio_buffer_writer_abort();
		return false;
#endif
	}

	u32 now = timer_get_ms();
	s_voice_capture_started_ms = now;
	s_voice_capture_stopped_ms = now;
	s_voice_capture_has_duration = false;

	printf("[%s] recording start\n", log_tag);
	return true;
}

static void ai_voice_recorder_stop(const char *tag)
{
	const char *log_tag = tag ? tag : "ai_voice";

	if (!ai_voice_recorder_is_running()) {
		return;
	}

	ai_voice_recorder_close(g_ai_voice_recorder_handle);
	g_ai_voice_recorder_handle = NULL;
	s_voice_capture_stopped_ms = timer_get_ms();
	s_voice_capture_has_duration = true;

#if 0
	audio_writer_close();
#else
	ai_voice_recorder_schedule_upload(log_tag);
#endif

	printf("[%s] recording stop\n", log_tag);
}

#include "app_power_manage.h"
#if defined(CONFIG_NET_ENABLE) && defined(CONFIG_WIFI_CAMERA_WEBSOCKET_ENABLE)
#include "websocket_client.h"
#endif

#define SHUTDOWN_DELAY_MS 500
static int shutdown_delay_timer_id = 0;

static void shutdown_poweroff_cb(void *priv)
{
	shutdown_delay_timer_id = 0;
#if defined(CONFIG_NET_ENABLE) && defined(CONFIG_WIFI_CAMERA_WEBSOCKET_ENABLE)
	int err = wifi_camera_ws_send_shutdown_report();
	if (err) {
		printf("[UI][SHUTDOWN] report failed:%d\n", err);
	} else {
		printf("[UI][SHUTDOWN] report sent\n");
	}
#endif
	sys_power_shutdown();
}


static lv_timer_t *s_video_dir_lbl5_timer = NULL;

static void video_dir_lbl_5_hide_timer_cb(lv_timer_t *timer)
{
	if (!timer) {
		return;
	}
	lv_obj_t *label = (lv_obj_t *)timer->user_data;
	if (label && lv_obj_is_valid(label)) {
		lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
	}
	if (s_video_dir_lbl5_timer == timer) {
		s_video_dir_lbl5_timer = NULL;
	}
	lv_timer_del(timer);
}
extern void watchai_media_data_release(void);
static void ai_img_rec_stop_all_ai_processes(const char *tag)
{
	const char *log_tag = tag ? tag : "AI_Img_Rec";
	printf("[%s] stop ai img rec flow\n", log_tag);
	ai_q_a_stop_audio_playback();
	watchai_ident_cancel_pending();
	watchai_media_data_release();
	watchai_ident_prepare_image(NULL);
}

#define AI_IMG_REC_THUMB_DEFAULT_W   128
#define AI_IMG_REC_THUMB_DEFAULT_H    96
#define AI_IMG_REC_THUMB_DEFAULT_X   176
#define AI_IMG_REC_THUMB_DEFAULT_Y   118

static lv_coord_t s_ai_img_rec_thumb_base_w = -1;
static lv_coord_t s_ai_img_rec_thumb_base_h = -1;
static lv_coord_t s_ai_img_rec_thumb_base_x = -1;
static lv_coord_t s_ai_img_rec_thumb_base_y = -1;

#define AI_IMG_REC_PREVIEW_MAX_WIDTH   640
#define AI_IMG_REC_PREVIEW_MAX_HEIGHT  480

static lv_img_dsc_t s_ai_img_rec_rotated_preview_dsc = {0};
static uint16_t s_ai_img_rec_rotated_preview_buf[AI_IMG_REC_PREVIEW_MAX_WIDTH * AI_IMG_REC_PREVIEW_MAX_HEIGHT];
static lv_img_dsc_t s_ai_img_rec_prepared_preview_dsc = {0};
static uint16_t s_ai_img_rec_prepared_preview_buf[AI_IMG_REC_PREVIEW_MAX_WIDTH * AI_IMG_REC_PREVIEW_MAX_HEIGHT];

static void ai_img_rec_rotate_rgb565_ccw(uint16_t *dst, const uint16_t *src, lv_coord_t src_w, lv_coord_t src_h)
{
	if (!dst || !src || src_w <= 0 || src_h <= 0) {
		return;
	}

	int dst_w = src_h;
	int dst_h = src_w;

	for (int y = 0; y < src_h; ++y) {
		const uint16_t *src_row = src + y * src_w;
		for (int x = 0; x < src_w; ++x) {
			int new_x = y;
			int new_y = dst_h - 1 - x;
			dst[new_y * dst_w + new_x] = src_row[x];
		}
	}
}

static void ai_img_rec_downscale_rgb565(uint16_t *dst,
											 lv_coord_t dst_w,
											 lv_coord_t dst_h,
											 const uint16_t *src,
											 lv_coord_t src_w,
											 lv_coord_t src_h)
{
	if (!dst || !src || dst_w <= 0 || dst_h <= 0 || src_w <= 0 || src_h <= 0) {
		return;
	}

	for (lv_coord_t y = 0; y < dst_h; ++y) {
		uint32_t src_y = (uint32_t)y * (uint32_t)src_h / (uint32_t)dst_h;
		const uint16_t *src_row = src + src_y * src_w;
		uint16_t *dst_row = dst + y * dst_w;
		for (lv_coord_t x = 0; x < dst_w; ++x) {
			uint32_t src_x = (uint32_t)x * (uint32_t)src_w / (uint32_t)dst_w;
			dst_row[x] = src_row[src_x];
		}
	}
}

static const lv_img_dsc_t *ai_img_rec_prepare_preview_dsc(const lv_img_dsc_t *src,
											   lv_coord_t target_w,
											   lv_coord_t target_h)
{
	if (!src || !src->data) {
		return NULL;
	}

	if (src->header.cf != LV_IMG_CF_TRUE_COLOR) {
		return src;
	}

	lv_coord_t src_w = src->header.w;
	lv_coord_t src_h = src->header.h;
	if (src_w <= 0 || src_h <= 0) {
		return NULL;
	}

	const lv_img_dsc_t *work_dsc = src;
	const uint16_t *work_buf = (const uint16_t *)src->data;
	lv_coord_t work_w = src_w;
	lv_coord_t work_h = src_h;

	if (src_w < src_h && src_h <= AI_IMG_REC_PREVIEW_MAX_WIDTH && src_w <= AI_IMG_REC_PREVIEW_MAX_HEIGHT) {
		ai_img_rec_rotate_rgb565_ccw(s_ai_img_rec_rotated_preview_buf, (const uint16_t *)src->data, src_w, src_h);
		s_ai_img_rec_rotated_preview_dsc = *src;
		s_ai_img_rec_rotated_preview_dsc.header.w = src_h;
		s_ai_img_rec_rotated_preview_dsc.header.h = src_w;
		s_ai_img_rec_rotated_preview_dsc.data_size = (uint32_t)src_w * (uint32_t)src_h * 2u;
		s_ai_img_rec_rotated_preview_dsc.data = (const uint8_t *)s_ai_img_rec_rotated_preview_buf;
		work_dsc = &s_ai_img_rec_rotated_preview_dsc;
		work_buf = s_ai_img_rec_rotated_preview_buf;
		work_w = s_ai_img_rec_rotated_preview_dsc.header.w;
		work_h = s_ai_img_rec_rotated_preview_dsc.header.h;
	}

	if (target_w > 0 && target_h > 0 && work_w > target_w && work_h > target_h) {
		ai_img_rec_downscale_rgb565(s_ai_img_rec_prepared_preview_buf,
									 target_w,
									 target_h,
									 work_buf,
									 work_w,
									 work_h);

		s_ai_img_rec_prepared_preview_dsc = *work_dsc;
		s_ai_img_rec_prepared_preview_dsc.header.w = target_w;
		s_ai_img_rec_prepared_preview_dsc.header.h = target_h;
		s_ai_img_rec_prepared_preview_dsc.data_size = (uint32_t)target_w * (uint32_t)target_h * 2u;
		s_ai_img_rec_prepared_preview_dsc.data = (const uint8_t *)s_ai_img_rec_prepared_preview_buf;

		return &s_ai_img_rec_prepared_preview_dsc;
	}

	return work_dsc;
}

static void chat_page_update_header(lv_ui *ui)
{
	if (!ui) {
		return;
	}

	lv_ui_chat_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CHAT_PAGE);
	if (!ui_scr) {
		return;
	}

	const char *display = "未选择好友";
	if (s_chat_active_friend.valid) {
		if (s_chat_active_friend.display_name[0]) {
			display = s_chat_active_friend.display_name;
		} else if (s_chat_active_friend.group_id[0]) {
			display = s_chat_active_friend.group_id;
		}
	}

	if (ui_scr->chat_page_lbl_1 && lv_obj_is_valid(ui_scr->chat_page_lbl_1)) {
		lv_label_set_text(ui_scr->chat_page_lbl_1, display);
	}

	if (ui_scr->chat_page_btn_1_label && lv_obj_is_valid(ui_scr->chat_page_btn_1_label)) {
		lv_label_set_text(ui_scr->chat_page_btn_1_label, "按住说话");
	}
}

#include "../../../../include/websocket_client.h"
// ------------------------------ Add Friend helpers ------------------------------
#define ADD_FRIEND_COUNTDOWN_SEC_DEFAULT 30

static lv_timer_t *s_add_friend_countdown_timer = NULL;
static int s_add_friend_countdown_remaining = 0;

static bool add_friend_is_label_available(void)
{
	return guider_ui.Add_friend && guider_ui.Add_friend->Add_friend_lbl_4 &&
		lv_obj_is_valid(guider_ui.Add_friend->Add_friend_lbl_4);
}

static void add_friend_update_countdown_label(void)
{
	if (!add_friend_is_label_available()) {
		return;
	}
	int value = s_add_friend_countdown_remaining;
	if (value < 0) {
		value = 0;
	}
	lv_label_set_text_fmt(guider_ui.Add_friend->Add_friend_lbl_4, "%d", (int)value);
}

static void add_friend_stop_countdown(void)
{
	if (s_add_friend_countdown_timer) {
		lv_timer_t *timer = s_add_friend_countdown_timer;
		s_add_friend_countdown_timer = NULL;
		lv_timer_del(timer);
	}
	s_add_friend_countdown_remaining = 0;
}

static void add_friend_exit_screen(lv_ui *ui)
{
	add_friend_stop_countdown();
	gui_scr_t *screen = ui_get_scr(GUI_SCREEN_ADDRESS_BOOK);
	if (!screen) {
		return;
	}
	if (!ui) {
		ui = &guider_ui;
	}
	ui_load_scr_anim(ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
}

static void add_friend_countdown_timer_cb(lv_timer_t *timer)
{
	lv_ui *ui = timer ? (lv_ui *)timer->user_data : NULL;
	if (!add_friend_is_label_available()) {
		add_friend_stop_countdown();
		return;
	}
	if (s_add_friend_countdown_remaining <= 0) {
		add_friend_update_countdown_label();
		add_friend_exit_screen(ui);
		return;
	}
	s_add_friend_countdown_remaining--;
	add_friend_update_countdown_label();
	if (s_add_friend_countdown_remaining <= 0) {
		add_friend_exit_screen(ui);
	}
}

static void add_friend_start_countdown(lv_ui *ui)
{
	if (!ui) {
		ui = &guider_ui;
	}
	add_friend_stop_countdown();
	s_add_friend_countdown_remaining = ADD_FRIEND_COUNTDOWN_SEC_DEFAULT;
	add_friend_update_countdown_label();
	s_add_friend_countdown_timer = lv_timer_create(add_friend_countdown_timer_cb, 1000, ui);
	if (!s_add_friend_countdown_timer) {
		printf("[Add Friend] Failed to create countdown timer\n");
	}
}

void scr_loaded_handler(lv_event_t *e)
{
	lv_obj_t * src = lv_event_get_target(e);
	gui_msg_init_ui();
	gui_msg_init_events();
}

void events_init(lv_ui *ui)
{
}

static void home_page_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
				switch (code)
				{
					case LV_EVENT_SCREEN_LOAD_START:
					{
						gui_scr_action_cb(GUI_SCREEN_HOME_PAGE, GUI_SCREEN_ACTION_LOAD);
						lv_ui * ui = lv_event_get_user_data(e);
						home_page_update_wifi_prompt_visibility(ui);
						break;
					}
					case LV_EVENT_SCREEN_LOADED:
					{
						lv_ui * ui = lv_event_get_user_data(e);
						home_page_update_wifi_prompt_visibility(ui);
						break;
					}
					case LV_EVENT_SCREEN_UNLOADED:
					{
						gui_scr_action_cb(GUI_SCREEN_HOME_PAGE, GUI_SCREEN_ACTION_UNLOAD);
						break;
					}
				}
		}
	}
}

static void home_page_img_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_AI_Q_A);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void home_page_img_13_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void home_page_img_10_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void home_page_img_11_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_ADDRESS_BOOK);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void home_page_img_8_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_VIDEO_PHOTO);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void home_page_img_9_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_VIDEO_REC);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void home_page_img_18_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (ui) {
			  lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
			  if (ui_scr && ui_scr->home_page_view_11 && lv_obj_is_valid(ui_scr->home_page_view_11)) {
			    lv_obj_add_flag(ui_scr->home_page_view_11, LV_OBJ_FLAG_HIDDEN);
			  }
			}
			wifi_camera_find_tone_cancel_from_ui("home_page_img_18");
		}
	}
	break;
	default:
		break;
	}
}

static void home_page_btn_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (ui) {
			  lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
			  if (ui_scr && ui_scr->home_page_view_11 && lv_obj_is_valid(ui_scr->home_page_view_11)) {
			    lv_obj_add_flag(ui_scr->home_page_view_11, LV_OBJ_FLAG_HIDDEN);
			  }
			}
			wifi_camera_find_tone_cancel_from_ui("home_page_btn_3");
		}
	}
	break;
	default:
		break;
	}
}

static void home_page_img_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
						// 获取UI指针和屏幕UI对象
						lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
						lv_ui_home_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
						// 隐藏 home_page_view_2
						if (ui_scr && ui_scr->home_page_view_2) {
							lv_obj_add_flag(ui_scr->home_page_view_2, LV_OBJ_FLAG_HIDDEN);
						}
		}
	}
	break;
	default:
		break;
	}
}

static void home_page_btn_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_WIFI_SEARCH);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
		//custom code WIFI_search
		{
			s_wifi_search_entry_source = WIFI_SEARCH_ENTRY_FROM_HOME_PAGE;
		}
	}
	break;
	default:
		break;
	}
}

void events_init_home_page(lv_ui *ui)
{
	lv_ui_home_page * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
	lv_obj_add_event_cb(ui_scr->home_page, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->home_page, home_page_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->home_page_img_12, home_page_img_12_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->home_page_img_13, home_page_img_13_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->home_page_img_10, home_page_img_10_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->home_page_img_11, home_page_img_11_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->home_page_img_8, home_page_img_8_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->home_page_img_9, home_page_img_9_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->home_page_img_18, home_page_img_18_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->home_page_btn_3, home_page_btn_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->home_page_img_6, home_page_img_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->home_page_btn_2, home_page_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void video_rec_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOADED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_video_rec * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
			printf("[chili] %s %d   \n",  __func__, __LINE__);
			
		}
	}
	break;
	default:
		break;
	}
}

static void video_rec_img_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
		//custom code home_page
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (s_rec_btn_recording) {
			  rec_control_ontouch();
			  s_rec_btn_recording = 0;
			  video_rec_stop_timer();
			}
		}
	}
	break;
	default:
		break;
	}
}

static void video_rec_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			video_rec_toggle_recording(ui, true);
		}
	}
	break;
	default:
		break;
	}
}
static void video_rec_screen_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
		case LV_EVENT_SCREEN_LOAD_START:
		{
			gui_scr_action_cb(GUI_SCREEN_VIDEO_REC, GUI_SCREEN_ACTION_LOAD);
			break;
		}
		case LV_EVENT_SCREEN_UNLOADED:
		{
			gui_scr_action_cb(GUI_SCREEN_VIDEO_REC, GUI_SCREEN_ACTION_UNLOAD);
			break;
		}
	}
}

void events_init_video_rec(lv_ui *ui)
{
	lv_ui_video_rec * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
	lv_obj_add_event_cb(ui_scr->video_rec, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->video_rec, video_rec_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_rec_img_1, video_rec_img_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_rec_btn_1, video_rec_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_rec, video_rec_screen_event_handler, LV_EVENT_ALL, ui);
}

static void sys_prompt_img_warn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code sys_prompt
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_sys_prompt * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_PROMPT);
			lv_obj_t * dest = ui_scr->sys_prompt;
			extern lv_timer_t *prompt_timer;
			if (prompt_timer) 
			{
			  lv_timer_del(prompt_timer);     
			  prompt_timer = NULL;                                                                                                                                                                             
			}
			if (ui_scr->sys_prompt_del == false && lv_obj_is_valid(ui_scr->sys_prompt)) {
			  lv_obj_add_flag(ui_scr->sys_prompt, LV_OBJ_FLAG_HIDDEN);
			  unload_scr_sys_prompt(&guider_ui);
			}
			
		}
	}
	break;
	default:
		break;
	}
}

void events_init_sys_prompt(lv_ui *ui)
{
	lv_ui_sys_prompt * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_PROMPT);
	lv_obj_add_event_cb(ui_scr->sys_prompt, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->sys_prompt_img_warn, sys_prompt_img_warn_event_handler, LV_EVENT_ALL, ui);
}

static void video_photo_img_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			printf("[Photo] video_photo_img_3 clicked -> switch to video mode\n");
			
			if (ui_scr->video_photo_view_2 && lv_obj_is_valid(ui_scr->video_photo_view_2)) {
			  lv_obj_add_flag(ui_scr->video_photo_view_2, LV_OBJ_FLAG_HIDDEN);
			}
			
			if (ui_scr->video_photo_img_27 && lv_obj_is_valid(ui_scr->video_photo_img_27)) {
			  lv_obj_clear_flag(ui_scr->video_photo_img_27, LV_OBJ_FLAG_HIDDEN);
			}
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			video_photo_shift_sticker_selection(ui_scr, -1);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			video_photo_shift_sticker_selection(ui_scr, 1);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			lv_obj_t *target = lv_event_get_target(e);
			video_photo_select_sticker_by_obj(ui_scr, target);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			lv_obj_t *target = lv_event_get_target(e);
			video_photo_select_sticker_by_obj(ui_scr, target);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_4_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			lv_obj_t *target = lv_event_get_target(e);
			video_photo_select_sticker_by_obj(ui_scr, target);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_7_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			lv_obj_t *target = lv_event_get_target(e);
			video_photo_select_sticker_by_obj(ui_scr, target);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_8_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			lv_obj_t *target = lv_event_get_target(e);
			video_photo_select_sticker_by_obj(ui_scr, target);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_9_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			lv_obj_t *target = lv_event_get_target(e);
			video_photo_select_sticker_by_obj(ui_scr, target);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_10_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			lv_obj_t *target = lv_event_get_target(e);
			video_photo_select_sticker_by_obj(ui_scr, target);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_11_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			
			lv_obj_t *target = lv_event_get_target(e);
			video_photo_select_sticker_by_obj(ui_scr, target);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_13_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
		//custom code home_page
		{
			video_photo_ui_set_sticker_index(VIDEO_PHOTO_STICKER_INDEX_NONE);
			printf("dcq Exit the photo interface!!!");
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			printf("[Photo] video_photo_img_27 clicked -> take photo\n");
			app_send_message(APP_MSG_PHOTO_DELAY, 0);
		}
	}
	break;
	default:
		break;
	}
}

static void video_photo_img_27_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_video_photo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
			if (!ui_scr) {
			  break;
			}
			printf("[Photo] video_photo_img_27 clicked -> view photo gallery\n");
			
			if (ui_scr->video_photo_view_2 && lv_obj_is_valid(ui_scr->video_photo_view_2)) {
			  lv_obj_clear_flag(ui_scr->video_photo_view_2, LV_OBJ_FLAG_HIDDEN);
			}
			
			if (ui_scr->video_photo_img_27 && lv_obj_is_valid(ui_scr->video_photo_img_27)) {
			  lv_obj_add_flag(ui_scr->video_photo_img_27, LV_OBJ_FLAG_HIDDEN);
			}
			
			video_photo_apply_sticker_highlight(ui_scr);
		}
	}
	break;
	default:
		break;
	}
}
static void video_photo_screen_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
		case LV_EVENT_SCREEN_LOAD_START:
		{
			gui_scr_action_cb(GUI_SCREEN_VIDEO_PHOTO, GUI_SCREEN_ACTION_LOAD);
			break;
		}
		case LV_EVENT_SCREEN_UNLOADED:
		{
			gui_scr_action_cb(GUI_SCREEN_VIDEO_PHOTO, GUI_SCREEN_ACTION_UNLOAD);
			break;
		}
	}
}

void events_init_video_photo(lv_ui *ui)
{
	lv_ui_video_photo * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
	lv_obj_add_event_cb(ui_scr->video_photo, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_3, video_photo_img_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_1, video_photo_img_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_2, video_photo_img_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_6, video_photo_img_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_5, video_photo_img_5_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_4, video_photo_img_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_7, video_photo_img_7_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_8, video_photo_img_8_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_9, video_photo_img_9_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_10, video_photo_img_10_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_11, video_photo_img_11_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_13, video_photo_img_13_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_btn_1, video_photo_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo_img_27, video_photo_img_27_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_photo, video_photo_screen_event_handler, LV_EVENT_ALL, ui);
}

static void video_play_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOADED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_video_play * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
			lv_group_focus_obj(ui_scr->video_play_imgbtn_pause);
		}
	}
	break;
	default:
		break;
	}
}

static void video_play_imgbtn_pause_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code video_play_imgbtn_pause
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_video_play * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
			lv_obj_t * dest = ui_scr->video_play_imgbtn_pause;
			#if LV_USE_GUIBUILDER_SIMULATOR
			#else
			printf("------>%s()----->%d\n", __func__, __LINE__);
			cfun_dec_ok();
			#endif
		}
	}
	break;
	default:
		break;
	}
}

static void video_play_img_prev_file_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code video_play_lbl_msg
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_video_play * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
			lv_obj_t * dest = ui_scr->video_play_lbl_msg;
			#if LV_USE_GUIBUILDER_SIMULATOR
			#else
			 //static int32_t prev_file = RES_SKIP_PREVIOUS;
			 //lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_PREV_FILE, prev_file, 0); 
			 lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_FILE_NAME, NULL, 0, 0);
			 lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_TOTAL_TIME, NULL, 0, 0);
			dec_video_prev_next(3);
			#endif
			// 显示标签
			lv_obj_clear_flag(dest, LV_OBJ_FLAG_HIDDEN);
			
			uint32_t HIDE_DELAY_MS = 1500; // 例如，隐藏前延迟1.5秒
			lv_timer_t * timer = lv_timer_create(hide_label_timer_cb, HIDE_DELAY_MS, dest);
		}
	}
	break;
	default:
		break;
	}
}

static void video_play_img_next_file_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code video_play_lbl_msg
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_video_play * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
			lv_obj_t * dest = ui_scr->video_play_lbl_msg;
			#if LV_USE_GUIBUILDER_SIMULATOR
			#else
			//static int32_t next_file = RES_SKIP_NEXT;
			//lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_NEXT_FILE, next_file , 0); 
			lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_FILE_NAME, NULL, 0, 0);
			//lvgl_module_msg_send_value(GUI_MODEL_MSG_ID_NEXT_FILE, next_file, 0);
			lvgl_module_msg_send_global_ptr(GUI_MODEL_MSG_ID_TOTAL_TIME, NULL, 0, 0);
			dec_video_prev_next(2);
			#endif
			// 显示标签
			lv_obj_clear_flag(dest, LV_OBJ_FLAG_HIDDEN);
			
			uint32_t HIDE_DELAY_MS = 1500; // 例如，隐藏前延迟1.5秒
			lv_timer_t * timer = lv_timer_create(hide_label_timer_cb, HIDE_DELAY_MS, dest);
		}
	}
	break;
	default:
		break;
	}
}

static void video_play_imgbtn_loud_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_video_play * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
			#if !LV_USE_GUIBUILDER_SIMULATOR
			gui_set_video_volume();
			#endif
		}
	}
	break;
	default:
		break;
	}
}

static void video_play_ddlist_multi_spped_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_video_play * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
			lv_group_focus_obj(ui_scr->video_play_imgbtn_pause);
		}
	}
	break;
	case LV_EVENT_VALUE_CHANGED:
	{
		//custom code video_play_ddlist_multi_spped
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_video_play * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
			lv_obj_t * dest = ui_scr->video_play_ddlist_multi_spped;
			int selected_index = lv_dropdown_get_selected(dest);
			printf("Selected (Index: %d)\n", selected_index);
			#if LV_USE_GUIBUILDER_SIMULATOR
			#else
			void speed_change(int index);
			speed_change(selected_index);
			#endif
			
			
			
		}
	}
	break;
	default:
		break;
	}
}

static void video_play_imgbtn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_video_play * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
			#if !LV_USE_GUIBUILDER_SIMULATOR
			gui_get_video_frame();
			#endif
		}
	}
	break;
	default:
		break;
	}
}

static void video_play_img_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}
static void video_play_screen_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
		case LV_EVENT_SCREEN_LOAD_START:
		{
			gui_scr_action_cb(GUI_SCREEN_VIDEO_PLAY, GUI_SCREEN_ACTION_LOAD);
			break;
		}
		case LV_EVENT_SCREEN_UNLOADED:
		{
			gui_scr_action_cb(GUI_SCREEN_VIDEO_PLAY, GUI_SCREEN_ACTION_UNLOAD);
			break;
		}
	}
}

void events_init_video_play(lv_ui *ui)
{
	lv_ui_video_play * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PLAY);
	lv_obj_add_event_cb(ui_scr->video_play, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->video_play, video_play_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_play_imgbtn_pause, video_play_imgbtn_pause_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_play_img_prev_file, video_play_img_prev_file_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_play_img_next_file, video_play_img_next_file_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_play_imgbtn_loud, video_play_imgbtn_loud_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_play_ddlist_multi_spped, video_play_ddlist_multi_spped_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_play_imgbtn_1, video_play_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_play_img_1, video_play_img_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_play, video_play_screen_event_handler, LV_EVENT_ALL, ui);
}

static void sys_popwin_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code sys_popwin
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_sys_popwin * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
			lv_obj_t * dest = ui_scr->sys_popwin;
			if (ui_scr->sys_popwin_del == false && lv_obj_is_valid(ui_scr->sys_popwin)) {
			  lv_obj_add_flag(ui_scr->sys_popwin, LV_OBJ_FLAG_HIDDEN);
			      /*unload_scr_sys_popwin(&guider_ui);*/
			      /*lv_obj_del(ui_scr->sys_popwin);*/
			      gui_msg_init_ui();
			    gui_msg_init_events();
			    delete_gui_timelines();
			} 
		}
	}
	break;
	default:
		break;
	}
}

static void sys_popwin_btn_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code sys_popwin
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_sys_popwin * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
			lv_obj_t * dest = ui_scr->sys_popwin;
			//video_dec_edit_files(del);
			if (ui_scr->sys_popwin_del == false && lv_obj_is_valid(ui_scr->sys_popwin)) {
			  lv_obj_add_flag(ui_scr->sys_popwin, LV_OBJ_FLAG_HIDDEN);
			      /*unload_scr_sys_popwin(&guider_ui);*/
			      /*lv_obj_del(ui_scr->sys_popwin);*/
			      gui_msg_init_ui();
			    gui_msg_init_events();
			    delete_gui_timelines();
			} 
		}
	}
	break;
	default:
		break;
	}
}

void events_init_sys_popwin(lv_ui *ui)
{
	lv_ui_sys_popwin * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYS_POPWIN);
	lv_obj_add_event_cb(ui_scr->sys_popwin, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->sys_popwin_btn_1, sys_popwin_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->sys_popwin_btn_2, sys_popwin_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void usb_slave_gif_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_DRAW_MAIN_BEGIN:
	{
		//custom code 
		{
			
					// 在第一次绘制开始时启动定时器（如果还没有启动）
					if (usb_gif_timer == NULL) {
						printf("Starting USB GIF timer for 3 seconds\n");
						usb_gif_timer = lv_timer_create(usb_gif_timer_cb, 3000, NULL); // 3秒后自动切换
						lv_timer_set_repeat_count(usb_gif_timer, 1); // 只执行一次
					}
			
						
				// 从数据库读取保存的语言设置并应用
				//extern int db_select(const char *table);
				extern char* refresh_all_obj_language_style();
				
				int lang_init = db_select("lang_init");
				
				// 如果已经初始化过语言设置，应用保存的语言
				if (lang_init == 1) {
					//printf("setup_ui: restoring saved language settings\n");
					refresh_all_obj_language_style();
				} else {
					//printf("setup_ui: using default language (Chinese)\n");
				}
				
		}
	}
	break;
	default:
		break;
	}
}

void events_init_usb_slave(lv_ui *ui)
{
	lv_ui_usb_slave * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
	lv_obj_add_event_cb(ui_scr->usb_slave, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->usb_slave_gif_1, usb_slave_gif_1_event_handler, LV_EVENT_ALL, ui);
}

static void Language_Selection_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_SCREEN_LOAD_START:
			{
			  lv_ui *ui = lv_event_get_user_data(e);
			  if (!ui) {
			    break;
			  }
			
			  lv_ui_Language_Selection *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LANGUAGE_SELECTION);
			  language_selection_refresh_icons(ui_scr, db_select("lag"));
			}
			break;
			case LV_EVENT_SCREEN_LOADED:
			{
			  // 确保界面完全加载后也同步一次，避免初始状态不同步
			  lv_ui *ui = lv_event_get_user_data(e);
			  if (!ui) {
			    break;
			  }
			
			  lv_ui_Language_Selection *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LANGUAGE_SELECTION);
			  language_selection_refresh_icons(ui_scr, db_select("lag"));
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void Language_Selection_view_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			language_selection_handle_locale_click(e, "hi");
			printf("印地语hi");
		}
	}
	break;
	default:
		break;
	}
}

static void Language_Selection_view_4_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			language_selection_handle_locale_click(e, "en");
		}
	}
	break;
	default:
		break;
	}
}

static void Language_Selection_view_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			language_selection_handle_locale_click(e, "fr");
			printf("法语fr");
		}
	}
	break;
	default:
		break;
	}
}

static void Language_Selection_view_7_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			language_selection_handle_locale_click(e, "pt");
			printf("葡萄牙pt");
		}
	}
	break;
	default:
		break;
	}
}

static void Language_Selection_view_8_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			language_selection_handle_locale_click(e, "es");
			printf("西班牙es");
		}
	}
	break;
	default:
		break;
	}
}

static void Language_Selection_view_9_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			language_selection_handle_locale_click(e, "ru");
			printf("俄罗斯ru");
		}
	}
	break;
	default:
		break;
	}
}

static void Language_Selection_view_10_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			language_selection_handle_locale_click(e, "ar_sa");
			printf("阿拉伯ar");
		}
	}
	break;
	default:
		break;
	}
}

static void Language_Selection_view_11_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			language_selection_handle_locale_click(e, "zh_cn");
			printf("中文zh");
		}
	}
	break;
	default:
		break;
	}
}

static void Language_Selection_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
		//custom code home_page
		{
						// 确保用户选择的语言已经保存到数据库
						// 获取当前选择的语言ID（已通过flex_cont_event_handler保存）
						int selected_lang_id = db_select("lag");
						
						// 设置语言初始化标志，表示用户已经选择过语言
						db_update("lang_init", 1);
						
						// 确保语言设置正确应用
						refresh_all_obj_language_style();
						
						printf("Language selection confirmed: lang_id=%d, lang_init=1\n", selected_lang_id);
			
					
		}
	}
	break;
	default:
		break;
	}
}

void events_init_Language_Selection(lv_ui *ui)
{
	lv_ui_Language_Selection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LANGUAGE_SELECTION);
	lv_obj_add_event_cb(ui_scr->Language_Selection, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->Language_Selection, Language_Selection_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Language_Selection_view_5, Language_Selection_view_5_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Language_Selection_view_4, Language_Selection_view_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Language_Selection_view_6, Language_Selection_view_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Language_Selection_view_7, Language_Selection_view_7_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Language_Selection_view_8, Language_Selection_view_8_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Language_Selection_view_9, Language_Selection_view_9_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Language_Selection_view_10, Language_Selection_view_10_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Language_Selection_view_11, Language_Selection_view_11_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Language_Selection_btn_1, Language_Selection_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void WIFI_search_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_SCREEN_LOADED:
			{
				//custom code 
				{		
					wifi_user_scan_cancel_async();
					printf("WiFi search screen loaded - initializing WiFi list\n");
														
					// 每次界面加载都重新初始化WiFi列表组件，避免静态变量导致的问题
					lv_ui_WIFI_search * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_WIFI_SEARCH);
					if (ui_scr && ui_scr->WIFI_search) {
						// 移除静态变量，每次都重新初始化，确保WiFi列表功能正常
						wifi_list_init(ui_scr->WIFI_search);
						
						// 设置WiFi项点击回调函数
						wifi_list_set_item_click_callback(wifi_item_clicked_callback);
						
						printf("[WiFi List] Initialized successfully\n");
						printf("WiFi list initialized and callback set successfully\n");
						
						// 检查是否应该自动搜索WiFi
						if (s_auto_scan_enabled) {
							printf("Auto scan enabled - starting new scan\n");
							
							// 1. 隐藏"选取附近的WLAN"文字
							if (ui_scr->WIFI_search_lbl_5) {
								lv_obj_add_flag(ui_scr->WIFI_search_lbl_5, LV_OBJ_FLAG_HIDDEN);
							}
							
							// 2. 显示"正在搜索附近可用的网络"文字
							if (ui_scr->WIFI_search_lbl_4) {
								lv_obj_clear_flag(ui_scr->WIFI_search_lbl_4, LV_OBJ_FLAG_HIDDEN);
							}
							
							// 3. 先隐藏WiFi列表
							wifi_list_hide();
							
							// 4. 设置用户扫描标志并自动开始搜索
							s_user_scan_requested = 1;
							printf("界面自动启动WiFi搜索\n");
							
							#if !LV_USE_GUIBUILDER_SIMULATOR
							wifi_user_scan_request_async(50);
							#else
							printf("模拟器模式：执行WiFi搜索...\n");
							#endif
						} else {
							printf("Auto scan disabled - attempting to restore persistent WiFi data\n");
							
							// 检查是否有保存的WiFi列表数据
							extern bool wifi_list_has_persistent_data(void);
							extern bool wifi_list_restore_persistent_data(void);
							
							if (wifi_list_has_persistent_data()) {
								printf("Found persistent WiFi data - restoring from connection screen return\n");
								
								// 恢复之前保存的WiFi列表
								if (wifi_list_restore_persistent_data()) {
									printf("Successfully restored persistent WiFi data\n");
									
									// 显示"选取附近的WLAN"文字
									if (ui_scr->WIFI_search_lbl_5) {
										lv_obj_clear_flag(ui_scr->WIFI_search_lbl_5, LV_OBJ_FLAG_HIDDEN);
									}
									
									// 隐藏"正在搜索附近可用的网络"文字
									if (ui_scr->WIFI_search_lbl_4) {
										lv_obj_add_flag(ui_scr->WIFI_search_lbl_4, LV_OBJ_FLAG_HIDDEN);
									}
									
									// 显示恢复的WiFi列表
									wifi_list_show(WIFI_LIST_POS_X, WIFI_LIST_POS_Y, WIFI_LIST_WIDTH, WIFI_LIST_HEIGHT);
									wifi_search_promote_connected_network();
								} else {
									printf("Failed to restore persistent WiFi data\n");
								}
							} else {
								printf("No persistent WiFi data available to restore\n");
								
								// 显示"选取附近的WLAN"文字
								if (ui_scr->WIFI_search_lbl_5) {
									lv_obj_clear_flag(ui_scr->WIFI_search_lbl_5, LV_OBJ_FLAG_HIDDEN);
								}
								
								// 隐藏"正在搜索附近可用的网络"文字
								if (ui_scr->WIFI_search_lbl_4) {
									lv_obj_add_flag(ui_scr->WIFI_search_lbl_4, LV_OBJ_FLAG_HIDDEN);
								}
							}
							
							// 重新启用自动搜索，为下次进入准备
							s_auto_scan_enabled = 1;
						}
						
					} else {
						printf("Failed to initialize WiFi list - screen not found\n");
					}
				}
			}
			break;
			case LV_EVENT_SCREEN_UNLOADED:
							wifi_user_scan_cancel_async();
							wifi_list_destroy();
			break;
			default:
			break;
			}
		}
	}
}

static void WIFI_search_img_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  //custom code seting
			  {
			    s_auto_scan_enabled = 1;
			    wifi_list_destroy();
			  }
			
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void WIFI_search_imgbtn_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_WIFI_search * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_SEARCH);
			
			s_user_scan_requested = 1;
			printf("WiFi搜索按钮被点击！\n");
			
			// 清除持久化数据，强制重新搜索
			extern void wifi_list_clear_persistent_data(void);
			wifi_list_clear_persistent_data();
			printf("[WiFi搜索] 已清除持久化数据，将进行全新搜索\n");
			
			// 1. 先隐藏WiFi列表
			printf("[Debug] 准备隐藏WiFi列表...\n");
			wifi_list_hide();
			printf("[Debug] wifi_list_hide() 调用完成\n");
			
			// 2. 隐藏"选取附近的WLAN"文字
			if (ui_scr && ui_scr->WIFI_search_lbl_5) {
				lv_obj_add_flag(ui_scr->WIFI_search_lbl_5, LV_OBJ_FLAG_HIDDEN);
				printf("[Debug] 隐藏了'选取附近的WLAN'文字\n");
			} else {
				printf("[Debug] Warning: WIFI_search_lbl_5 is NULL\n");
			}
			
			// 3. 显示"正在搜索附近可用的网络"文字
			if (ui_scr && ui_scr->WIFI_search_lbl_4) {
				lv_obj_clear_flag(ui_scr->WIFI_search_lbl_4, LV_OBJ_FLAG_HIDDEN);
				printf("[Debug] 显示了'正在搜索'文字\n");
			} else {
				printf("[Debug] Warning: WIFI_search_lbl_4 is NULL\n");
			}
			
			// 4. 调用WiFi搜索功能
			#if !LV_USE_GUIBUILDER_SIMULATOR
			wifi_user_scan_request_async(50);
			#else
			printf("模拟器模式：执行WiFi搜索...\n");
			#endif
		}
	}
	break;
	default:
		break;
	}
}

void events_init_WIFI_search(lv_ui *ui)
{
	lv_ui_WIFI_search * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_SEARCH);
	lv_obj_add_event_cb(ui_scr->WIFI_search, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_search, WIFI_search_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_search_img_3, WIFI_search_img_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_search_imgbtn_2, WIFI_search_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
}

static void WIFI_connection_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOADED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
			lv_obj_t *ssid_label = (ui_scr != NULL) ? ui_scr->WIFI_connection_lbl_2 : NULL;
			
			// 获取存储的WiFi信息并自动填充SSID显示标签
			const char *ssid_to_show = NULL;
			if (s_selected_ssid_valid && strlen(s_selected_ssid) > 0) {
				ssid_to_show = s_selected_ssid;
			} else {
				struct wifi_mode_info stored_info = {0};
				char stored_ssid_buf[33] = {0};
				char stored_pwd_buf[65] = {0};
				stored_info.mode = STA_MODE;
				stored_info.ssid = stored_ssid_buf;
				stored_info.pwd = stored_pwd_buf;
				extern int wifi_get_mode_stored_info(struct wifi_mode_info *info);
				if (wifi_get_mode_stored_info(&stored_info) == 0 && stored_info.ssid && strlen(stored_info.ssid) > 0) {
					ssid_to_show = stored_info.ssid;
				}
			}
			
			if (ssid_label) {
				if (ssid_to_show) {
					lv_label_set_text(ssid_label, ssid_to_show);
					printf("[WiFi Connection] 自动填充SSID: %s\n", ssid_to_show);
				} else {
					lv_label_set_text(ssid_label, "");
					printf("[WiFi Connection] 未找到待显示的SSID，清空显示标签\n");
				}
			} else {
				printf("[WiFi Connection] 警告：SSID显示控件无效，无法更新\n");
			}
		}
	}
	break;
	default:
		break;
	}
}

static void WIFI_connection_img_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_WIFI_SEARCH);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void WIFI_connection_btnm_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
			// 获取按下的按键索引
			uint32_t btn_id = lv_btnmatrix_get_selected_btn(lv_event_get_target(e));
			
			// 检查UI结构是否有效
			if (ui_scr && ui_scr->WIFI_connection_edit_2) {
				// 直接获取按键文本
				const char *btn_text = lv_btnmatrix_get_btn_text(lv_event_get_target(e), btn_id);
				
				// 过滤掉空字符串、换行符和空白按键，只处理有效字符
				if (btn_text && strlen(btn_text) > 0 && 
					strcmp(btn_text, "\n") != 0 && 
					strcmp(btn_text, "  ") != 0 && 
					strcmp(btn_text, "") != 0) {
					
					// 获取当前文本内容
					const char *current_text = lv_textarea_get_text(ui_scr->WIFI_connection_edit_2);
					// 如果当前文本是默认提示文字"请输入密码"，则先清空
					if (current_text && (strcmp(current_text, "请输入密码") == 0) || (strcmp(current_text, "Enter password") == 0)) {
						lv_textarea_set_text(ui_scr->WIFI_connection_edit_2, "");
					}
					// 设置字体颜色为白色
					lv_obj_set_style_text_color(ui_scr->WIFI_connection_edit_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
					
					// 添加字符到文本框
					lv_textarea_add_text(ui_scr->WIFI_connection_edit_2, btn_text);
					
					printf("按键 %d 被按下: %s\n", (int)btn_id, btn_text);
				}
			}
		}
	}
	break;
	default:
		break;
	}
}

static void WIFI_connection_btnm_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			uint32_t btn_id = lv_btnmatrix_get_selected_btn(lv_event_get_target(e));
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
			
			if (ui_scr) {
				if (btn_id == 0) {  // "abc" 按钮 - 切换显示和隐藏字母键盘大小写
					if (wifi_keyboard_mode == 1) {  // 当前是字母键盘模式
						// 切换大小写
						wifi_letter_case = !wifi_letter_case;
						
						if (wifi_letter_case) {
							// 显示大写键盘，隐藏小写键盘
							lv_obj_clear_flag(ui_scr->WIFI_connection_btnm_5, LV_OBJ_FLAG_HIDDEN);
							lv_obj_add_flag(ui_scr->WIFI_connection_btnm_4, LV_OBJ_FLAG_HIDDEN);
							printf("切换到大写字母键盘\n");
						} else {
							// 显示小写键盘，隐藏大写键盘
							lv_obj_clear_flag(ui_scr->WIFI_connection_btnm_4, LV_OBJ_FLAG_HIDDEN);
							lv_obj_add_flag(ui_scr->WIFI_connection_btnm_5, LV_OBJ_FLAG_HIDDEN);
							printf("切换到小写字母键盘\n");
						}
					} else {
						// 当前是符号键盘，切换到字母键盘并显示
						wifi_keyboard_mode = 1;
						
						// 隐藏符号键盘
						lv_obj_add_flag(ui_scr->WIFI_connection_btnm_1, LV_OBJ_FLAG_HIDDEN);
						
						// 根据当前大小写状态显示对应键盘
						if (wifi_letter_case) {
							lv_obj_clear_flag(ui_scr->WIFI_connection_btnm_5, LV_OBJ_FLAG_HIDDEN);
							lv_obj_add_flag(ui_scr->WIFI_connection_btnm_4, LV_OBJ_FLAG_HIDDEN);
							printf("显示大写字母键盘\n");
						} else {
							lv_obj_clear_flag(ui_scr->WIFI_connection_btnm_4, LV_OBJ_FLAG_HIDDEN);
							lv_obj_add_flag(ui_scr->WIFI_connection_btnm_5, LV_OBJ_FLAG_HIDDEN);
							printf("显示小写字母键盘\n");
						}
					}
				}
				else if (btn_id == 1) {  // "?12" 按钮 - 切换字符键盘
					wifi_keyboard_mode = 0;
					
					// 显示符号键盘
					lv_obj_clear_flag(ui_scr->WIFI_connection_btnm_1, LV_OBJ_FLAG_HIDDEN);
					// 隐藏所有字母键盘
					lv_obj_add_flag(ui_scr->WIFI_connection_btnm_4, LV_OBJ_FLAG_HIDDEN);
					lv_obj_add_flag(ui_scr->WIFI_connection_btnm_5, LV_OBJ_FLAG_HIDDEN);
					
					printf("切换到符号键盘\n");
				}
			}
		}
	}
	break;
	default:
		break;
	}
}

static void WIFI_connection_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
			
			// 获取用户输入的密码
			const char *password = lv_textarea_get_text(ui_scr->WIFI_connection_edit_2);
			if (!password) {
			  printf("[WiFi连接] 错误：无法获取密码输入\n");
			  return;
			}
			
			// 跳过默认提示文字
			if ((strcmp(password, "请输入密码") == 0) || (strcmp(password, "Enter password") == 0)) {
			  password = "";  // 如果是默认提示文字，使用空密码
			}
			
			printf("[WiFi连接] 用户输入的密码: '%s'\n", password)
			
			// 检查密码长度，若不足8位则给出提示
			if (strlen(password) < 8) {
			  if (ui_scr && ui_scr->WIFI_connection_lbl_3) {
			    lv_obj_clear_flag(ui_scr->WIFI_connection_lbl_3, LV_OBJ_FLAG_HIDDEN);
			    if (s_wifi_password_hint_timer) {
			      lv_timer_del(s_wifi_password_hint_timer);
			      s_wifi_password_hint_timer = NULL;
			    }
			    s_wifi_password_hint_timer = lv_timer_create(wifi_password_hint_timer_cb, 1000, ui_scr->WIFI_connection_lbl_3);
			    if (s_wifi_password_hint_timer == NULL) {
			      printf("[WiFi连接] 创建密码提示定时器失败\n");
			    }
			  }
			  return;
			}
			
			// 确定目标SSID，可优先使用用户刚刚选择的SSID
			const char *target_ssid = NULL;
			if (s_selected_ssid_valid && strlen(s_selected_ssid) > 0) {
			  target_ssid = s_selected_ssid;
			} else {
			  struct wifi_mode_info stored_info = {0};
			  char stored_ssid_buf[33] = {0};
			  char stored_pwd_buf[65] = {0};
			  stored_info.mode = STA_MODE;
			  stored_info.ssid = stored_ssid_buf;
			  stored_info.pwd = stored_pwd_buf;
			  extern int wifi_get_mode_stored_info(struct wifi_mode_info *info);
			  if (wifi_get_mode_stored_info(&stored_info) == 0 && stored_info.ssid && strlen(stored_info.ssid) > 0) {
			    target_ssid = stored_info.ssid;
			  }
			}
			
			if (!target_ssid) {
			  printf("[WiFi连接] 错误：没有可用的SSID，请先选择WiFi网络\n");
			  return;
			}
			
			if (ui_scr && ui_scr->WIFI_connection_lbl_3) {
			  lv_obj_add_flag(ui_scr->WIFI_connection_lbl_3, LV_OBJ_FLAG_HIDDEN);
			  if (s_wifi_password_hint_timer) {
			    lv_timer_del(s_wifi_password_hint_timer);
			    s_wifi_password_hint_timer = NULL;
			  }
			}
			
			if (!wifi_list_show_connecting_status(target_ssid)) {
			  printf("[WiFi连接] WiFi列表暂未就绪，已记录待显示的'连接中'状态\n");
			}
			
			printf("[WiFi连接] 开始连接WiFi: SSID='%s', 密码='%s'\n", target_ssid, password);
			// 使用WiFi连接API连接到指定的网络（异步API）
			extern int wifi_enter_sta_mode(char *sta_ssid, char *sta_pwd);
			wifi_sta_enable_save_after_connect();
			wifi_enter_sta_mode((char*)target_ssid, (char*)password);
			
			printf("[WiFi连接] WiFi连接请求已发送，等待连接结果...\n");
			printf("[WiFi连接] 请注意查看WiFi事件回调获取连接状态\n");
			printf("[WiFi连接] 将在连接成功后再保存SSID/密码以避免错误凭据\n");
			
			// 禁用自动搜索，这样返回搜索界面时不会重新搜索
			s_auto_scan_enabled = 0;
			
			// 连接后跳转回WiFi搜索界面
			printf("[WiFi连接] 跳转回WiFi搜索界面\n");
			gui_scr_t * screen = ui_get_scr(GUI_SCREEN_WIFI_SEARCH);
			if(screen != NULL) {
			  ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
			} else {
			  printf("[WiFi连接] 错误：无法获取WiFi搜索界面\n");
			}
		}
	}
	break;
	default:
		break;
	}
}

static void WIFI_connection_btnm_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if (lv_btnmatrix_get_selected_btn(lv_event_get_target(e)) == 0)
		{
			//custom code 
			{
				lv_obj_t * src = lv_event_get_target(e);
				lv_ui * ui = lv_event_get_user_data(e);
				lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
				
				// 检查UI结构是否有效
				if (ui_scr && ui_scr->WIFI_connection_edit_2) {
					// 获取当前文本内容
					const char *current_text = lv_textarea_get_text(ui_scr->WIFI_connection_edit_2);
					
					// 如果当前文本是默认提示文字"请输入密码"，则先清空
					if (current_text && (strcmp(current_text, "请输入密码") == 0) || (strcmp(current_text, "Enter password") == 0)) {
						lv_textarea_set_text(ui_scr->WIFI_connection_edit_2, "");
					}
				
					// 设置字体颜色为白色
					lv_obj_set_style_text_color(ui_scr->WIFI_connection_edit_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
				
					// 添加空格到文本框
					lv_textarea_add_text(ui_scr->WIFI_connection_edit_2, " ");
					
					printf("添加空格到输入框\n");
				}
			}
		}
	}
	break;
	default:
		break;
	}
}

static void WIFI_connection_btn_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
			
			// 检查UI结构是否有效
			if (ui_scr && ui_scr->WIFI_connection_edit_2) {
				// 获取当前文本内容
				const char *current_text = lv_textarea_get_text(ui_scr->WIFI_connection_edit_2);
				
				// 检查文本是否为空或只有提示文字
				if (current_text && strlen(current_text) > 0 && strcmp(current_text, "请输入密码") != 0) {
					// 删除最后一个字符
					char new_text[256];
					size_t len = strlen(current_text);
					if (len > 0) {
						strncpy(new_text, current_text, len - 1);
						new_text[len - 1] = '\0';
						lv_textarea_set_text(ui_scr->WIFI_connection_edit_2, new_text);
						printf("删除最后一个字符，剩余文本: %s\n", new_text);
					}
				} else {
					printf("文本框为空或只有提示文字，无需删除\n");
				}
			}
		}
	}
	break;
	default:
		break;
	}
}

static void WIFI_connection_btnm_4_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
			
			// 获取按下的按键索引
			uint32_t btn_id = lv_btnmatrix_get_selected_btn(lv_event_get_target(e));
			
			// 检查UI结构是否有效
			if (ui_scr && ui_scr->WIFI_connection_edit_2) {
				// 直接获取按键文本
				const char *btn_text = lv_btnmatrix_get_btn_text(lv_event_get_target(e), btn_id);
				
				// 过滤掉空字符串、换行符和空白按键，只处理有效字符
				if (btn_text && strlen(btn_text) > 0 && 
					strcmp(btn_text, "\n") != 0 && 
					strcmp(btn_text, "  ") != 0 && 
					strcmp(btn_text, "") != 0) {
					
					// 获取当前文本内容
					const char *current_text = lv_textarea_get_text(ui_scr->WIFI_connection_edit_2);
					
					// 如果当前文本是默认提示文字"请输入密码"，则先清空
					if (current_text && (strcmp(current_text, "请输入密码") == 0) || (strcmp(current_text, "Enter password") == 0)) {
						lv_textarea_set_text(ui_scr->WIFI_connection_edit_2, "");
						// 设置字体颜色为白色
						lv_obj_set_style_text_color(ui_scr->WIFI_connection_edit_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
					}
					
					// 添加字符到文本框
					lv_textarea_add_text(ui_scr->WIFI_connection_edit_2, btn_text);
					
					printf("按键组4 - 按键 %d 被按下: %s\n", (int)btn_id, btn_text);
				}
			}
		}
	}
	break;
	default:
		break;
	}
}

static void WIFI_connection_btnm_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
			
			// 获取按下的按键索引
			uint32_t btn_id = lv_btnmatrix_get_selected_btn(lv_event_get_target(e));
			
			// 检查UI结构是否有效
			if (ui_scr && ui_scr->WIFI_connection_edit_2) {
				// 直接获取按键文本
				const char *btn_text = lv_btnmatrix_get_btn_text(lv_event_get_target(e), btn_id);
				
				// 过滤掉空字符串、换行符和空白按键，只处理有效字符
				if (btn_text && strlen(btn_text) > 0 && 
					strcmp(btn_text, "\n") != 0 && 
					strcmp(btn_text, "  ") != 0 && 
					strcmp(btn_text, "") != 0) {
					
					// 获取当前文本内容
					const char *current_text = lv_textarea_get_text(ui_scr->WIFI_connection_edit_2);
					
					// 如果当前文本是默认提示文字"请输入密码"，则先清空
					if (current_text && (strcmp(current_text, "请输入密码") == 0) || (strcmp(current_text, "Enter password") == 0)) {
						lv_textarea_set_text(ui_scr->WIFI_connection_edit_2, "");
						// 设置字体颜色为白色
						lv_obj_set_style_text_color(ui_scr->WIFI_connection_edit_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
					}
					
					// 添加字符到文本框
					lv_textarea_add_text(ui_scr->WIFI_connection_edit_2, btn_text);
					
					printf("按键组5 - 按键 %d 被按下: %s\n", (int)btn_id, btn_text);
				}
			}
		}
	}
	break;
	default:
		break;
	}
}

void events_init_WIFI_connection(lv_ui *ui)
{
	lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
	lv_obj_add_event_cb(ui_scr->WIFI_connection, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_connection, WIFI_connection_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_connection_img_3, WIFI_connection_img_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_connection_btnm_1, WIFI_connection_btnm_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_connection_btnm_2, WIFI_connection_btnm_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_connection_btn_1, WIFI_connection_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_connection_btnm_3, WIFI_connection_btnm_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_connection_btn_2, WIFI_connection_btn_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_connection_btnm_4, WIFI_connection_btnm_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->WIFI_connection_btnm_5, WIFI_connection_btnm_5_event_handler, LV_EVENT_ALL, ui);
}

static void seting_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOAD_START:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  break;
			}
			
			lv_ui_seting * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SETING);
			if (ui_scr == NULL) {
			  break;
			}
			
			int lang_id = db_select("lag");
			
			if (ui_scr->seting_lbl_2) {
			  u8 saved_value = brightness_settings_get_value();
			  lv_label_set_text_fmt(ui_scr->seting_lbl_2, "%d%%", saved_value);
			}
			
			if (ui_scr->seting_lbl_4) {
			  u8 saved_percent = volume_get_saved_percent();
			  lv_label_set_text_fmt(ui_scr->seting_lbl_4, "%d%%", saved_percent);
			}
			
			if (ui_scr->seting_lbl_6) {
			  const lv_font_t *language_font = multi_language_pick_font(LANG_TEXT_LANGUAGE_NAME_CURRENT, lang_id);
			  if (language_font) {
			    lv_obj_set_style_text_font(ui_scr->seting_lbl_6, language_font, LV_PART_MAIN | LV_STATE_DEFAULT);
			  }
			  lv_label_set_text(ui_scr->seting_lbl_6, multi_language_get_text(LANG_TEXT_LANGUAGE_NAME_CURRENT, lang_id));
			}
			
			if (ui_scr->seting_lbl_11) {
			  u32 dormancy_seconds = db_select("pro");
			  u32 dormancy_normalized = dormancy_normalize_seconds(dormancy_seconds);
			  multi_language_text_key_t dormancy_key = LANG_TEXT_DORMANCY_ALWAYS_ON;
			  switch (dormancy_normalized) {
			  case 60:
			    dormancy_key = LANG_TEXT_DORMANCY_1_MIN;
			    break;
			  case 180:
			    dormancy_key = LANG_TEXT_DORMANCY_3_MIN;
			    break;
			  default:
			    dormancy_key = LANG_TEXT_DORMANCY_ALWAYS_ON;
			    break;
			  }
			  const lv_font_t *dormancy_font = multi_language_pick_font(dormancy_key, lang_id);
			  if (dormancy_font) {
			    lv_obj_set_style_text_font(ui_scr->seting_lbl_11, dormancy_font, LV_PART_MAIN | LV_STATE_DEFAULT);
			  }
			  lv_label_set_text(ui_scr->seting_lbl_11, multi_language_get_text(dormancy_key, lang_id));
			}
			
			if (ui_scr->seting_lbl_12) {
			  int quality = db_select("qua");
			  multi_language_text_key_t quality_key = LANG_TEXT_PHOTO_QUALITY_HIGH;
			  switch (quality) {
			  case PHOTO_QUA_LO:
			    quality_key = LANG_TEXT_PHOTO_QUALITY_LOW;
			    break;
			  case PHOTO_QUA_MD:
			    quality_key = LANG_TEXT_PHOTO_QUALITY_MEDIUM;
			    break;
			  case PHOTO_QUA_HI:
			  default:
			    quality_key = LANG_TEXT_PHOTO_QUALITY_HIGH;
			    break;
			  }
			  const lv_font_t *quality_font = multi_language_pick_font(quality_key, lang_id);
			  if (quality_font) {
			    lv_obj_set_style_text_font(ui_scr->seting_lbl_12, quality_font, LV_PART_MAIN | LV_STATE_DEFAULT);
			  }
			  lv_label_set_text(ui_scr->seting_lbl_12, multi_language_get_text(quality_key, lang_id));
			}
			
			if (ui_scr->seting_lbl_15) {
			  int photo_resolution = db_select("pres");
			  lv_label_set_text(ui_scr->seting_lbl_15, photo_resolution_to_text(photo_resolution));
			}
			
			if (ui_scr->seting_lbl_22) {
			  int video_resolution = db_select("res");
			  lv_label_set_text(ui_scr->seting_lbl_22, video_resolution_to_text(video_resolution));
			}
			      
			multi_language_text_key_t wifi_status_key = LANG_TEXT_WIFI_DISCONNECTED;
			#ifdef CONFIG_NET_ENABLE
			if (wifi_is_on()) {
			  enum wifi_sta_connect_state connect_state = wifi_get_sta_connect_state();
			  bool wifi_connected = false;
			
			  switch (connect_state) {
			  case WIFI_STA_CONNECT_SUCC:
			  case WIFI_STA_NETWORK_STACK_DHCP_SUCC:
			  case WIFI_STA_IP_GOT_IPV6_SUCC:
			    wifi_connected = true;
			    break;
			  default:
			    break;
			  }
			
			  if (wifi_connected) {
			    struct wifi_mode_info mode_info = {0};
			    char ssid_buf[33] = {0};
			    char pwd_buf[65] = {0};
			    mode_info.mode = STA_MODE;
			    mode_info.ssid = ssid_buf;
			    mode_info.pwd = pwd_buf;
			    wifi_get_mode_cur_info(&mode_info);
			
			    if (mode_info.ssid && mode_info.ssid[0] != '\0') {
			      wifi_status_key = LANG_TEXT_WIFI_CONNECTED;
			    }
			  }
			}
			#endif
			if (ui_scr->seting_lbl_8) {
			  const lv_font_t *wifi_font = multi_language_pick_font(wifi_status_key, lang_id);
			  if (wifi_font) {
			    lv_obj_set_style_text_font(ui_scr->seting_lbl_8, wifi_font, LV_PART_MAIN | LV_STATE_DEFAULT);
			  }
			  lv_label_set_text(ui_scr->seting_lbl_8, multi_language_get_text(wifi_status_key, lang_id));
			}
			
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_15_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_VIDEO_RESOLUTION);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_14_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_RESTORE_FACTORY);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_13_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SOFTWARE_VERSION);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_BINDING_DEVICE_CODE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_11_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_IMAGE_RESOLUTION);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_10_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_TF_FORMATTING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_9_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_IMAGE_SIZE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_8_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_DORMANCY);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_7_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_WIFI_SEARCH);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
		//custom code WIFI_search
		{
			s_wifi_search_entry_source = WIFI_SEARCH_ENTRY_FROM_SETTING;
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_LANGUAGE_SELECTION);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_VOLUME);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_view_4_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_BRIGHTNESS);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_img_33_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_AI_PAYMENT_CODE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void seting_img_27_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_seting(lv_ui *ui)
{
	lv_ui_seting * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SETING);
	lv_obj_add_event_cb(ui_scr->seting, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->seting, seting_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_15, seting_view_15_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_14, seting_view_14_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_13, seting_view_13_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_12, seting_view_12_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_11, seting_view_11_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_10, seting_view_10_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_9, seting_view_9_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_8, seting_view_8_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_7, seting_view_7_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_6, seting_view_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_5, seting_view_5_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_view_4, seting_view_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_img_33, seting_img_33_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->seting_img_27, seting_img_27_event_handler, LV_EVENT_ALL, ui);
}

static void brightness_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOAD_START:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_brightness * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_BRIGHTNESS);
			if (ui_scr) {
				u8 saved_value = brightness_settings_get_value();
				printf("saved_value = %d\n", saved_value);
				brightness_sync_slider_label_hw(ui_scr, saved_value);
			}
		}
	}
	break;
	default:
		break;
	}
}

static void brightness_img_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void brightness_slider_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			lv_obj_t * slider = lv_event_get_target(e);
			if (slider == NULL) {
			  return;
			}
			
			u8 slider_percent = brightness_clamp_percent(lv_slider_get_value(slider));
			lv_ui_brightness * ui_scr = ui->brightness;
			
			switch (code)
			{
			case LV_EVENT_VALUE_CHANGED:
			{
			  brightness_update_label_and_hw(ui_scr, slider_percent);
			printf("Brightness slider value changed: %d\n", slider_percent);
			  brightness_persist_if_needed(slider_percent);
			  break;
			}
			default:
			  break;
			}
		}
	}
}

void events_init_brightness(lv_ui *ui)
{
	lv_ui_brightness * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_BRIGHTNESS);
	lv_obj_add_event_cb(ui_scr->brightness, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->brightness, brightness_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->brightness_img_6, brightness_img_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->brightness_slider_1, brightness_slider_1_event_handler, LV_EVENT_ALL, ui);
}

static void volume_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOAD_START:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  break;
			}
			s_volume_max_steps = -1;
			s_last_saved_volume_percent = 0xFF;
			lv_ui_volume * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VOLUME);
			if (ui_scr) {
			  u8 saved_percent = volume_get_saved_percent();
			  volume_sync_slider_label_hw(ui_scr, saved_percent);
			}
		}
	}
	break;
	default:
		break;
	}
}

static void volume_img_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void volume_slider_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			lv_obj_t * src = lv_event_get_target(e);
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_volume * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VOLUME);
				switch (code)
				{
				case LV_EVENT_VALUE_CHANGED:
				{
					lv_ui * ui = lv_event_get_user_data(e);
					if (ui == NULL) {
						break;
					}
					lv_obj_t * slider = lv_event_get_target(e);
					if (slider == NULL) {
						break;
					}
					u8 slider_percent = volume_clamp_percent(lv_slider_get_value(slider));
					lv_ui_volume * ui_scr = ui->volume;
					if (ui_scr == NULL) {
						ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VOLUME);
					}
					volume_update_label_and_hw(ui_scr, slider_percent);
					if (ui_scr && ui_scr->volume_view_4) {
						if (slider_percent == 0) {
							lv_obj_clear_flag(ui_scr->volume_view_4, LV_OBJ_FLAG_HIDDEN);
							if (s_volume_mute_hint_timer) {
								lv_timer_del(s_volume_mute_hint_timer);
								s_volume_mute_hint_timer = NULL;
							}
							s_volume_mute_hint_timer = lv_timer_create(volume_mute_hint_timer_cb, 1000, ui_scr->volume_view_4);
							if (s_volume_mute_hint_timer == NULL) {
								printf("[Volume] Failed to create mute hint timer\n");
							}
						} else {
							if (s_volume_mute_hint_timer) {
								lv_timer_del(s_volume_mute_hint_timer);
								s_volume_mute_hint_timer = NULL;
							}
							lv_obj_add_flag(ui_scr->volume_view_4, LV_OBJ_FLAG_HIDDEN);
						}
					}
					printf("Volume slider value changed: %d%%\n", slider_percent);
					break;
				}
				default:
					break;
				}
		}
	}
}

void events_init_volume(lv_ui *ui)
{
	lv_ui_volume * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VOLUME);
	lv_obj_add_event_cb(ui_scr->volume, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->volume, volume_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->volume_img_6, volume_img_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->volume_slider_1, volume_slider_1_event_handler, LV_EVENT_ALL, ui);
}

static void dormancy_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOAD_START:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			
			u32 stored = db_select("pro");
			lv_ui_dormancy *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DORMANCY);
			dormancy_refresh_ui(ui_scr, stored);
		}
	}
	break;
	default:
		break;
	}
}

static void dormancy_img_10_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void dormancy_view_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			dormancy_apply_setting(ui, 0);
			printf("常亮\n");
		}
	}
	break;
	default:
		break;
	}
}

static void dormancy_view_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			dormancy_apply_setting(ui, 180);
			printf("三分钟\n");
		}
	}
	break;
	default:
		break;
	}
}

static void dormancy_view_4_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			dormancy_apply_setting(ui, 60);
			printf("1分钟\n");
		}
	}
	break;
	default:
		break;
	}
}

void events_init_dormancy(lv_ui *ui)
{
	lv_ui_dormancy * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DORMANCY);
	lv_obj_add_event_cb(ui_scr->dormancy, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->dormancy, dormancy_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->dormancy_img_10, dormancy_img_10_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->dormancy_view_6, dormancy_view_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->dormancy_view_5, dormancy_view_5_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->dormancy_view_4, dormancy_view_4_event_handler, LV_EVENT_ALL, ui);
}

static void image_size_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOAD_START:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			lv_ui_image_size *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_IMAGE_SIZE);
			if (!ui_scr) {
			  break;
			}
			int quality = db_select("qua");
			if (quality < PHOTO_QUA_LO) {
			  quality = PHOTO_QUA_LO;
			} else if (quality > PHOTO_QUA_HI) {
			  quality = PHOTO_QUA_HI;
			}
			image_quality_refresh_ui(ui_scr, (uint8_t)quality);
			break;
		}
	}
	break;
	default:
		break;
	}
}

static void image_size_img_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void image_size_view_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			image_quality_apply(ui, PHOTO_QUA_HI);
			printf("图片质量：高\n");
		}
	}
	break;
	default:
		break;
	}
}

static void image_size_view_4_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			image_quality_apply(ui, PHOTO_QUA_MD);
			printf("图片质量：中\n");
		}
	}
	break;
	default:
		break;
	}
}

static void image_size_view_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			image_quality_apply(ui, PHOTO_QUA_LO);
			printf("图片质量：低\n");
		}
	}
	break;
	default:
		break;
	}
}

void events_init_image_size(lv_ui *ui)
{
	lv_ui_image_size * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_IMAGE_SIZE);
	lv_obj_add_event_cb(ui_scr->image_size, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->image_size, image_size_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->image_size_img_12, image_size_img_12_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->image_size_view_3, image_size_view_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->image_size_view_4, image_size_view_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->image_size_view_5, image_size_view_5_event_handler, LV_EVENT_ALL, ui);
}

static void TF_formatting_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOAD_START:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_TF_formatting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_TF_FORMATTING);
			if (!ui_scr) {
			  break;
			}
			
			int sd_ready = storage_device_ready();
			if (ui_scr->TF_formatting_view_4) {
			  if (sd_ready) {
			    lv_obj_clear_flag(ui_scr->TF_formatting_view_4, LV_OBJ_FLAG_HIDDEN);
			  } else {
			    lv_obj_add_flag(ui_scr->TF_formatting_view_4, LV_OBJ_FLAG_HIDDEN);
			  }
			}
			
			if (ui_scr->TF_formatting_view_5) {
			  if (sd_ready) {
			    lv_obj_add_flag(ui_scr->TF_formatting_view_5, LV_OBJ_FLAG_HIDDEN);
			  } else {
			    lv_obj_clear_flag(ui_scr->TF_formatting_view_5, LV_OBJ_FLAG_HIDDEN);
			  }
			}
			
			printf("[TF Formatting] SD card %s\n", sd_ready ? "online" : "offline");
		}
	}
	break;
	default:
		break;
	}
}

static void TF_formatting_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_TF_formatting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_TF_FORMATTING);
			if (!ui_scr) {
			  break;
			}
			
			if (ui_scr->TF_formatting_view_3) {
			    lv_obj_clear_flag(ui_scr->TF_formatting_view_3, LV_OBJ_FLAG_HIDDEN);
			}
		}
	}
	break;
	default:
		break;
	}
}

static void TF_formatting_btn_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (ui) {
			  lv_ui_TF_formatting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_TF_FORMATTING);
			  if (ui_scr && ui_scr->TF_formatting_view_3) {
			    lv_obj_add_flag(ui_scr->TF_formatting_view_3, LV_OBJ_FLAG_HIDDEN);
			  }
			}
		}
	}
	break;
	default:
		break;
	}
}

static void TF_formatting_btn_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_TF_FORMATTING_2);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void TF_formatting_img_7_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (ui) {
			  lv_ui_TF_formatting *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_TF_FORMATTING);
			  if (ui_scr && ui_scr->TF_formatting_view_3) {
			    lv_obj_add_flag(ui_scr->TF_formatting_view_3, LV_OBJ_FLAG_HIDDEN);
			  }
			}
		}
	}
	break;
	default:
		break;
	}
}

static void TF_formatting_img_9_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_TF_formatting(lv_ui *ui)
{
	lv_ui_TF_formatting * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_TF_FORMATTING);
	lv_obj_add_event_cb(ui_scr->TF_formatting, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->TF_formatting, TF_formatting_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->TF_formatting_btn_1, TF_formatting_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->TF_formatting_btn_2, TF_formatting_btn_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->TF_formatting_btn_3, TF_formatting_btn_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->TF_formatting_img_7, TF_formatting_img_7_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->TF_formatting_img_9, TF_formatting_img_9_event_handler, LV_EVENT_ALL, ui);
}

static void TF_formatting_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			lv_event_code_t code = lv_event_get_code(e);
			switch (code)
			{
			case LV_EVENT_SCREEN_LOAD_START:
			{
			  lv_ui *ui = lv_event_get_user_data(e);
			  lv_ui_TF_formatting_2 *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_TF_FORMATTING_2);
			  if (!ui_scr) { return; }
			
			  tf_formatting_task_ctx_t *ctx = &g_tf_formatting_ctx;
			
			  ctx->canceled = 0;
			  ctx->finished = 0;
			  ctx->err = 0;
			  ctx->progress = 0;
			  ctx->ui_scr = ui_scr;
			
			  if (ctx->timer) {
			    lv_timer_del(ctx->timer);
			    ctx->timer = NULL;
			  }
			
			  if (ui_scr->TF_formatting_2_view_4 && lv_obj_is_valid(ui_scr->TF_formatting_2_view_4)) {
			    lv_obj_add_flag(ui_scr->TF_formatting_2_view_4, LV_OBJ_FLAG_HIDDEN);
			  }
			  if (ui_scr->TF_formatting_2_view_3 && lv_obj_is_valid(ui_scr->TF_formatting_2_view_3)) {
			    lv_obj_clear_flag(ui_scr->TF_formatting_2_view_3, LV_OBJ_FLAG_HIDDEN);
			  }
			  if (ui_scr->TF_formatting_2_img_5 && lv_obj_is_valid(ui_scr->TF_formatting_2_img_5)) {
			    lv_obj_add_state(ui_scr->TF_formatting_2_img_5, LV_STATE_DISABLED);
			  }
			
			  tf_formatting_update_progress(ui_scr, ctx->progress);
			  ctx->progress = 5;
			  tf_formatting_update_progress(ui_scr, ctx->progress);
			
			  ctx->timer = lv_timer_create(tf_formatting_progress_timer_cb, 120, ctx);
			  if (!ctx->timer) {
			    ctx->err = sdcard_storage_device_format(SDX_DEV);
			    ctx->finished = 1;
			    tf_formatting_finalize(ctx);
			    ctx->ui_scr = NULL;
			    break;
			  }
			
			  int ret = thread_fork("tf_fmt", 10, 1024, 0, NULL, tf_formatting_worker, ctx);
			  if (ret != 0) {
			    lv_timer_del(ctx->timer);
			    ctx->timer = NULL;
			    ctx->err = sdcard_storage_device_format(SDX_DEV);
			    ctx->finished = 1;
			    tf_formatting_finalize(ctx);
			    ctx->ui_scr = NULL;
			  }
			}
			break;
			case LV_EVENT_SCREEN_UNLOADED:
			case LV_EVENT_DELETE:
			{
			  tf_formatting_task_ctx_t *ctx = &g_tf_formatting_ctx;
			  ctx->canceled = 1;
			  if (ctx->timer) {
			    lv_timer_del(ctx->timer);
			    ctx->timer = NULL;
			  }
			  ctx->ui_scr = NULL;
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void TF_formatting_2_img_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_TF_FORMATTING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_TF_formatting_2(lv_ui *ui)
{
	lv_ui_TF_formatting_2 * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_TF_FORMATTING_2);
	lv_obj_add_event_cb(ui_scr->TF_formatting_2, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->TF_formatting_2, TF_formatting_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->TF_formatting_2_img_5, TF_formatting_2_img_5_event_handler, LV_EVENT_ALL, ui);
}

static void image_resolution_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOAD_START:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			lv_ui_image_resolution *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_IMAGE_RESOLUTION);
			if (!ui_scr) {
			  break;
			}
			uint8_t stored = photo_resolution_normalize(db_select("pres"));
			photo_resolution_refresh_ui(ui_scr, stored);
		}
	}
	break;
	default:
		break;
	}
}

static void image_resolution_img_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void image_resolution_view_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			photo_resolution_apply(ui, PHOTO_RES_2M);
		}
	}
	break;
	default:
		break;
	}
}

static void image_resolution_view_4_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			photo_resolution_apply(ui, PHOTO_RES_1M);
		}
	}
	break;
	default:
		break;
	}
}

static void image_resolution_view_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			photo_resolution_apply(ui, PHOTO_RES_VGA);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_image_resolution(lv_ui *ui)
{
	lv_ui_image_resolution * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_IMAGE_RESOLUTION);
	lv_obj_add_event_cb(ui_scr->image_resolution, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->image_resolution, image_resolution_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->image_resolution_img_12, image_resolution_img_12_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->image_resolution_view_3, image_resolution_view_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->image_resolution_view_4, image_resolution_view_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->image_resolution_view_5, image_resolution_view_5_event_handler, LV_EVENT_ALL, ui);
}

static void Binding_device_code_img_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_Binding_device_code(lv_ui *ui)
{
	lv_ui_Binding_device_code * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_BINDING_DEVICE_CODE);
	lv_obj_add_event_cb(ui_scr->Binding_device_code, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->Binding_device_code_img_12, Binding_device_code_img_12_event_handler, LV_EVENT_ALL, ui);
}

static void software_version_img_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_software_version(lv_ui *ui)
{
	lv_ui_software_version * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SOFTWARE_VERSION);
	lv_obj_add_event_cb(ui_scr->software_version, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->software_version_img_12, software_version_img_12_event_handler, LV_EVENT_ALL, ui);
}

static void Restore_factory_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			
			lv_ui_Restore_factory *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RESTORE_FACTORY);
			if (!ui_scr) {
			  break;
			}
			
			if (ui_scr->Restore_factory_view_3) {
			    lv_obj_clear_flag(ui_scr->Restore_factory_view_3, LV_OBJ_FLAG_HIDDEN);
			}
		}
	}
	break;
	default:
		break;
	}
}

static void Restore_factory_btn_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (ui) {
			  lv_ui_Restore_factory *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RESTORE_FACTORY);
			  if (ui_scr && ui_scr->Restore_factory_view_3) {
			    lv_obj_add_flag(ui_scr->Restore_factory_view_3, LV_OBJ_FLAG_HIDDEN);
			  }
			}
		}
	}
	break;
	default:
		break;
	}
}

static void Restore_factory_btn_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_RESTORE_FACTORY_2);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void Restore_factory_img_7_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (ui) {
			  lv_ui_Restore_factory *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RESTORE_FACTORY);
			  if (ui_scr && ui_scr->Restore_factory_view_3) {
			    lv_obj_add_flag(ui_scr->Restore_factory_view_3, LV_OBJ_FLAG_HIDDEN);
			  }
			}
		}
	}
	break;
	default:
		break;
	}
}

static void Restore_factory_img_9_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_Restore_factory(lv_ui *ui)
{
	lv_ui_Restore_factory * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RESTORE_FACTORY);
	lv_obj_add_event_cb(ui_scr->Restore_factory, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->Restore_factory_btn_1, Restore_factory_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Restore_factory_btn_2, Restore_factory_btn_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Restore_factory_btn_3, Restore_factory_btn_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Restore_factory_img_7, Restore_factory_img_7_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Restore_factory_img_9, Restore_factory_img_9_event_handler, LV_EVENT_ALL, ui);
}

static void Restore_factory_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			
			lv_event_code_t code = lv_event_get_code(e);
			switch (code)
			{
			case LV_EVENT_SCREEN_LOAD_START:
			{
			  lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			  if (!ui) {
			    break;
			  }
			
			  lv_ui_Restore_factory_2 *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RESTORE_FACTORY_2);
			  if (!ui_scr) {
			    break;
			  }
			
			  factory_reset_task_ctx_t *ctx = &g_factory_reset_ctx;
			  ctx->canceled = 0;
			  ctx->finished = 0;
			  ctx->progress = 0;
			  ctx->ui_scr = ui_scr;
			
			  if (ctx->timer) {
			    lv_timer_del(ctx->timer);
			    ctx->timer = NULL;
			  }
			
			  if (ui_scr->Restore_factory_2_view_4 && lv_obj_is_valid(ui_scr->Restore_factory_2_view_4)) {
			    lv_obj_add_flag(ui_scr->Restore_factory_2_view_4, LV_OBJ_FLAG_HIDDEN);
			  }
			  if (ui_scr->Restore_factory_2_view_3 && lv_obj_is_valid(ui_scr->Restore_factory_2_view_3)) {
			    lv_obj_clear_flag(ui_scr->Restore_factory_2_view_3, LV_OBJ_FLAG_HIDDEN);
			  }
			
			  /* 初始化进度条并刷新 */
			  factory_reset_update_progress(ui_scr, ctx->progress);
			  ctx->progress = 5;
			  factory_reset_update_progress(ui_scr, ctx->progress);
			
			  /* 创建定时器驱动进度动画 */
			  ctx->timer = lv_timer_create(factory_reset_progress_timer_cb, 120, ctx);
			  if (!ctx->timer) {
			    /* 创建失败则同步执行恢复流程 */
			    factory_reset_execute(ctx);
			    factory_reset_finalize(ctx);
			    break;
			  }
			
			  /* 投递异步任务执行恢复出厂操作 */
			  lv_res_t res = lv_async_call(factory_reset_async_cb, ctx);
			  if (res != LV_RES_OK) {
			    factory_reset_execute(ctx);
			  }
			}
			break;
			case LV_EVENT_SCREEN_UNLOADED:
			case LV_EVENT_DELETE:
			{
			  factory_reset_task_ctx_t *ctx = &g_factory_reset_ctx;
			  ctx->canceled = 1;
			  if (ctx->timer) {
			    lv_timer_del(ctx->timer);
			    ctx->timer = NULL;
			  }
			  ctx->ui_scr = NULL;
			}
			break;
			default:
			  break;
			}
		}
	}
}

void events_init_Restore_factory_2(lv_ui *ui)
{
	lv_ui_Restore_factory_2 * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RESTORE_FACTORY_2);
	lv_obj_add_event_cb(ui_scr->Restore_factory_2, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->Restore_factory_2, Restore_factory_2_event_handler, LV_EVENT_ALL, ui);
}

static void address_book_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			switch (code)
			{
			case LV_EVENT_SCREEN_LOAD_START:
			{
			  address_book_refresh_friend_list(ui);
			  chat_manager_request_group_list();
			  chat_manager_request_sync_friend();
			}
			break;
			case LV_EVENT_SCREEN_LOADED:
			case LV_EVENT_VALUE_CHANGED:
			case LV_EVENT_REFRESH:
			{
			  address_book_refresh_friend_list(ui);
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_view_14_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  chat_active_friend_set_by_index(9);
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_CHAT_PAGE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_view_13_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  chat_active_friend_set_by_index(8);
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_CHAT_PAGE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_view_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  chat_active_friend_set_by_index(7);
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_CHAT_PAGE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_view_11_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  chat_active_friend_set_by_index(6);
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_CHAT_PAGE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_view_10_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  chat_active_friend_set_by_index(5);
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_CHAT_PAGE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_view_9_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  chat_active_friend_set_by_index(4);
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_CHAT_PAGE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_view_8_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  chat_active_friend_set_by_index(3);
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_CHAT_PAGE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_view_7_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code chat_page
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  chat_active_friend_set_by_index(2);
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_CHAT_PAGE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_view_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code chat_page
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  chat_active_friend_set_by_index(1);
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_CHAT_PAGE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_view_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code chat_page
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  chat_active_friend_set_by_index(0);
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_CHAT_PAGE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void address_book_img_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_EDIT_FRIEND_INFO);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
		}
	}
	break;
	default:
		break;
	}
}

static void address_book_img_27_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void address_book_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_ADD_FRIEND);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_address_book(lv_ui *ui)
{
	lv_ui_address_book * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_ADDRESS_BOOK);
	lv_obj_add_event_cb(ui_scr->address_book, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->address_book, address_book_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_view_14, address_book_view_14_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_view_13, address_book_view_13_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_view_12, address_book_view_12_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_view_11, address_book_view_11_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_view_10, address_book_view_10_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_view_9, address_book_view_9_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_view_8, address_book_view_8_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_view_7, address_book_view_7_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_view_6, address_book_view_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_view_5, address_book_view_5_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_img_5, address_book_img_5_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_img_27, address_book_img_27_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->address_book_btn_1, address_book_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void video_resolution_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOAD_START:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (!ui) {
			  break;
			}
			lv_ui_video_resolution *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_RESOLUTION);
			if (!ui_scr) {
			  break;
			}
			uint8_t stored = video_resolution_normalize(db_select("res"));
			video_resolution_refresh_ui(ui_scr, stored);
		}
	}
	break;
	default:
		break;
	}
}

static void video_resolution_img_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void video_resolution_view_4_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			video_resolution_apply(ui, VIDEO_RES_720P);
		}
	}
	break;
	default:
		break;
	}
}

static void video_resolution_view_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			video_resolution_apply(ui, VIDEO_RES_VGA);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_video_resolution(lv_ui *ui)
{
	lv_ui_video_resolution * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_RESOLUTION);
	lv_obj_add_event_cb(ui_scr->video_resolution, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->video_resolution, video_resolution_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_resolution_img_12, video_resolution_img_12_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_resolution_view_4, video_resolution_view_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_resolution_view_5, video_resolution_view_5_event_handler, LV_EVENT_ALL, ui);
}

static void AI_Q_A_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_SCREEN_LOAD_START:
			{
			  //custom code 
			  {
			    lv_ui * ui = lv_event_get_user_data(e);
			    if (ui == NULL) {
			      break;
			    }
			    lv_ui_AI_Q_A * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_AI_Q_A);
			    if (ui_scr == NULL) {
			      break;
			    }
			    ai_chat_history_init(ui_scr->AI_Q_A_view_5);
			  }
			}
			break;
			case LV_EVENT_SCREEN_UNLOADED:
			{
			  ai_q_a_stop_all_ai_processes("AI_Q_A_unload");
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void AI_Q_A_img_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  ai_q_a_stop_all_ai_processes("AI_Q_A_exit");
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
			  if(screen != NULL) {
			    ai_chat_history_clear();
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void AI_Q_A_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			if (ui == NULL) {
			  return;
			}
			lv_ui_AI_Q_A * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_AI_Q_A);
			if (ui_scr == NULL) {
			  return;
			}
			lv_obj_t *btn = ui_scr->AI_Q_A_btn_1;
			lv_obj_t *view = ui_scr->AI_Q_A_view_3;
			switch (code)
			{
			case LV_EVENT_PRESSED:
			case LV_EVENT_PRESSING:
			case LV_EVENT_LONG_PRESSED:
			{
			  if (code == LV_EVENT_PRESSED) {
			    ai_q_a_stop_audio_playback();
			  if (view && lv_obj_is_valid(view)) {
			    lv_obj_clear_flag(view, LV_OBJ_FLAG_HIDDEN);
			  }
			  if (btn && lv_obj_is_valid(btn)) {
			    lv_obj_add_flag(btn, LV_OBJ_FLAG_HIDDEN);
			  }
			  }
			  if (!s_ai_q_a_recording_active) {
			  if (ai_voice_recorder_start("AI_Q_A_btn1")) {
			    s_ai_q_a_recording_active = true;
			  }
			  }
			}
			break;
			case LV_EVENT_RELEASED:
			case LV_EVENT_PRESS_LOST:
			case LV_EVENT_LEAVE:
			case LV_EVENT_CLICKED:
			{
			  if (btn && lv_obj_is_valid(btn)) {
			  lv_obj_clear_flag(btn, LV_OBJ_FLAG_HIDDEN);
			  }
			  if (view && lv_obj_is_valid(view)) {
			  lv_obj_add_flag(view, LV_OBJ_FLAG_HIDDEN);
			  }
			  if (s_ai_q_a_recording_active || ai_voice_recorder_is_running()) {
			  ai_voice_recorder_stop("AI_Q_A_btn1");
			  s_ai_q_a_recording_active = false;
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void AI_Q_A_btn_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_AI_Q_A * ui_scr = (ui != NULL) ? ui_get_scr_ptr(ui, GUI_SCREEN_AI_Q_A) : NULL;
			if (ui_scr && ui_scr->AI_Q_A_view_6 && lv_obj_is_valid(ui_scr->AI_Q_A_view_6)) {
			  lv_obj_add_flag(ui_scr->AI_Q_A_view_6, LV_OBJ_FLAG_HIDDEN);
			}
		}
	}
	break;
	default:
		break;
	}
}

static void AI_Q_A_img_7_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_AI_Q_A * ui_scr = (ui != NULL) ? ui_get_scr_ptr(ui, GUI_SCREEN_AI_Q_A) : NULL;
			if (ui_scr && ui_scr->AI_Q_A_view_6 && lv_obj_is_valid(ui_scr->AI_Q_A_view_6)) {
			  lv_obj_add_flag(ui_scr->AI_Q_A_view_6, LV_OBJ_FLAG_HIDDEN);
			}
		}
	}
	break;
	default:
		break;
	}
}

void events_init_AI_Q_A(lv_ui *ui)
{
	lv_ui_AI_Q_A * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_AI_Q_A);
	lv_obj_add_event_cb(ui_scr->AI_Q_A, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->AI_Q_A, AI_Q_A_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->AI_Q_A_img_6, AI_Q_A_img_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->AI_Q_A_btn_1, AI_Q_A_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->AI_Q_A_btn_3, AI_Q_A_btn_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->AI_Q_A_img_7, AI_Q_A_img_7_event_handler, LV_EVENT_ALL, ui);
}

static void Shut_down_view_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui * ui = lv_event_get_user_data(e);
			lv_ui_Shut_down * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SHUT_DOWN);
			if (ui_scr && lv_obj_is_valid(ui_scr->Shut_down_lbl_1)) {
			  int lang_id = db_select("lag");
			  const lv_font_t *lang_font = multi_language_pick_font(LANG_TEXT_SHUTTING_DOWN, lang_id);
			  const char *shutdown_text = multi_language_get_text(LANG_TEXT_SHUTTING_DOWN, lang_id);
			  if (lang_font) {
			    lv_obj_set_style_text_font(ui_scr->Shut_down_lbl_1, lang_font, LV_PART_MAIN | LV_STATE_DEFAULT);
			  }
			  lv_label_set_text(ui_scr->Shut_down_lbl_1, shutdown_text);
			  lv_obj_invalidate(ui_scr->Shut_down_lbl_1);
			}
			if (shutdown_delay_timer_id != 0) {
			  sys_timeout_del(shutdown_delay_timer_id);
			  shutdown_delay_timer_id = 0;
			}
			shutdown_delay_timer_id = sys_timeout_add(NULL, shutdown_poweroff_cb, SHUTDOWN_DELAY_MS);
			if (shutdown_delay_timer_id == 0) {
			  sys_power_shutdown();
			}
		}
	}
	break;
	default:
		break;
	}
}

static void Shut_down_img_5_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
		//custom code home_page
		{
			shutdown_delay_timer_id = 0;
		}
	}
	break;
	default:
		break;
	}
}

void events_init_Shut_down(lv_ui *ui)
{
	lv_ui_Shut_down * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SHUT_DOWN);
	lv_obj_add_event_cb(ui_scr->Shut_down, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->Shut_down_view_2, Shut_down_view_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Shut_down_img_5, Shut_down_img_5_event_handler, LV_EVENT_ALL, ui);
}

static void video_dir_landscape_mode_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_SCREEN_LOAD_START:
	{
		//custom code 
		{
			printf("------>%s()----->%d\n", __func__, __LINE__);
			lvgl_module_msg_send_string(GUI_MODEL_MSG_ID_FILE_PATH, CONFIG_DEC_ROOT_PATH "1/", 0);
			video_dir_landscape_show_latest_preview();
		}
	}
	break;
	default:
		break;
	}
}

static void video_dir_landscape_mode_img_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  video_dir_landscape_cleanup_on_exit();
			
			  gui_scr_t *screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
			  if (screen) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void video_dir_landscape_mode_img_7_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (ui) {
			  lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
			  if (ui_scr && ui_scr->video_dir_landscape_mode_view_1) {
			    lv_obj_clear_flag(ui_scr->video_dir_landscape_mode_view_1, LV_OBJ_FLAG_HIDDEN);
			  }
			}
		}
	}
	break;
	default:
		break;
	}
}

static void video_dir_landscape_mode_img_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (ui) {
			  lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
			  if (ui_scr) {
			    if (video_dir_landscape_delete_active_media() == 0) {
			      if (ui_scr->video_dir_landscape_mode_view_1 && lv_obj_is_valid(ui_scr->video_dir_landscape_mode_view_1)) {
			      lv_obj_add_flag(ui_scr->video_dir_landscape_mode_view_1, LV_OBJ_FLAG_HIDDEN);
			      }
			      if (ui_scr->video_dir_landscape_mode_img_13 && lv_obj_is_valid(ui_scr->video_dir_landscape_mode_img_13)) {
			      lv_obj_clear_flag(ui_scr->video_dir_landscape_mode_img_13, LV_OBJ_FLAG_HIDDEN);
			      if (s_video_dir_lbl5_timer) {
			        lv_timer_del(s_video_dir_lbl5_timer);
			        s_video_dir_lbl5_timer = NULL;
			      }
			      lv_timer_t *timer = lv_timer_create(video_dir_lbl_5_hide_timer_cb, 1500, ui_scr->video_dir_landscape_mode_img_13);
			      if (timer) {
			        s_video_dir_lbl5_timer = timer;
			      }
			      }
			    } else {
			      printf("video_dir_landscape: delete active media failed\n");
			    }
			  }
			}
		}
	}
	break;
	default:
		break;
	}
}

static void video_dir_landscape_mode_img_4_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (ui) {
			  lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
			  if (ui_scr && ui_scr->video_dir_landscape_mode_view_1) {
			    lv_obj_add_flag(ui_scr->video_dir_landscape_mode_view_1, LV_OBJ_FLAG_HIDDEN);
			  }
			}
		}
	}
	break;
	default:
		break;
	}
}

static void video_dir_landscape_mode_img_10_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			if (ui) {
			  lv_ui_video_dir_landscape_mode *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
			  if (ui_scr && ui_scr->video_dir_landscape_mode_view_1) {
			    lv_obj_add_flag(ui_scr->video_dir_landscape_mode_view_1, LV_OBJ_FLAG_HIDDEN);
			  }
			}
		}
	}
	break;
	default:
		break;
	}
}

static void video_dir_landscape_mode_img_15_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			printf("播放对应视频");
			if (video_dir_landscape_play_active_video() != 0) {
			  printf("video_dir_landscape: failed to launch playback\n");
			}
		}
	}
	break;
	default:
		break;
	}
}

static void video_dir_landscape_mode_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			const char *active_path = video_dir_landscape_get_active_path();
			if (!active_path || !video_dir_landscape_active_is_image()) {
				printf("[AI识图] 当前未选中图片，无法进入识图界面\n");
				break;
			}
			
			watchai_ident_prepare_image(active_path);
			const lv_img_dsc_t *preview = video_dir_landscape_get_active_preview_dsc();
			if (!preview) {
				preview = video_dir_landscape_get_active_thumbnail_dsc();
			}
			watchai_ident_set_preview_descriptor(preview);
			gui_scr_t * screen = ui_get_scr(GUI_SCREEN_AI_IMG_REC);
			if(screen != NULL) {
				ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
			}
		}
	}
	break;
	default:
		break;
	}
}
static void video_dir_landscape_mode_screen_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
		case LV_EVENT_SCREEN_LOAD_START:
		{
			gui_scr_action_cb(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE, GUI_SCREEN_ACTION_LOAD);
			break;
		}
	}
}

void events_init_video_dir_landscape_mode(lv_ui *ui)
{
	lv_ui_video_dir_landscape_mode * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
	lv_obj_add_event_cb(ui_scr->video_dir_landscape_mode, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->video_dir_landscape_mode, video_dir_landscape_mode_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_dir_landscape_mode_img_1, video_dir_landscape_mode_img_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_dir_landscape_mode_img_7, video_dir_landscape_mode_img_7_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_dir_landscape_mode_img_3, video_dir_landscape_mode_img_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_dir_landscape_mode_img_4, video_dir_landscape_mode_img_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_dir_landscape_mode_img_10, video_dir_landscape_mode_img_10_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_dir_landscape_mode_img_15, video_dir_landscape_mode_img_15_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_dir_landscape_mode_btn_1, video_dir_landscape_mode_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->video_dir_landscape_mode, video_dir_landscape_mode_screen_event_handler, LV_EVENT_ALL, ui);
}

static void AI_payment_code_img_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_SETING);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_AI_payment_code(lv_ui *ui)
{
	lv_ui_AI_payment_code * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_AI_PAYMENT_CODE);
	lv_obj_add_event_cb(ui_scr->AI_payment_code, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->AI_payment_code_img_12, AI_payment_code_img_12_event_handler, LV_EVENT_ALL, ui);
}

static void AI_Img_Rec_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_SCREEN_LOAD_START:
			{
			  lv_ui_AI_Img_Rec * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_AI_IMG_REC);
			  if (!ui_scr) {
			    break;
			  }
			
			  bool has_pending_image = watchai_ident_has_pending_image();
			  const lv_img_dsc_t *preview = watchai_ident_get_preview_descriptor();
			  if (ui_scr->AI_Img_Rec_img_8 && lv_obj_is_valid(ui_scr->AI_Img_Rec_img_8)) {
			    lv_obj_t *thumb = ui_scr->AI_Img_Rec_img_8;
			    if (s_ai_img_rec_thumb_base_w <= 0 || s_ai_img_rec_thumb_base_h <= 0) {
			    lv_coord_t current_w = lv_obj_get_width(thumb);
			    lv_coord_t current_h = lv_obj_get_height(thumb);
			    s_ai_img_rec_thumb_base_w = (current_w > 0) ? current_w : AI_IMG_REC_THUMB_DEFAULT_W;
			    s_ai_img_rec_thumb_base_h = (current_h > 0) ? current_h : AI_IMG_REC_THUMB_DEFAULT_H;
			    }
			    if (s_ai_img_rec_thumb_base_x < 0 || s_ai_img_rec_thumb_base_y < 0) {
			    lv_coord_t current_x = lv_obj_get_x(thumb);
			    lv_coord_t current_y = lv_obj_get_y(thumb);
			    s_ai_img_rec_thumb_base_x = (current_x >= 0) ? current_x : AI_IMG_REC_THUMB_DEFAULT_X;
			    s_ai_img_rec_thumb_base_y = (current_y >= 0) ? current_y : AI_IMG_REC_THUMB_DEFAULT_Y;
			    }
			
			          if (preview) {
			          lv_coord_t base_w = (s_ai_img_rec_thumb_base_w > 0) ? s_ai_img_rec_thumb_base_w : AI_IMG_REC_THUMB_DEFAULT_W;
			          lv_coord_t base_h = (s_ai_img_rec_thumb_base_h > 0) ? s_ai_img_rec_thumb_base_h : AI_IMG_REC_THUMB_DEFAULT_H;
			          const lv_img_dsc_t *display = ai_img_rec_prepare_preview_dsc(preview, base_w, base_h);
			          if (!display) {
			            display = preview;
			          }
			
			          lv_img_set_src(thumb, display);
			          lv_obj_clear_flag(thumb, LV_OBJ_FLAG_HIDDEN);
			          lv_img_set_angle(thumb, 0);
			          lv_img_set_pivot(thumb, 0, 0);
			
			          lv_coord_t base_x = (s_ai_img_rec_thumb_base_x >= 0) ? s_ai_img_rec_thumb_base_x : AI_IMG_REC_THUMB_DEFAULT_X;
			          lv_coord_t base_y = (s_ai_img_rec_thumb_base_y >= 0) ? s_ai_img_rec_thumb_base_y : AI_IMG_REC_THUMB_DEFAULT_Y;
			          lv_coord_t src_w = (lv_coord_t)display->header.w;
			          lv_coord_t src_h = (lv_coord_t)display->header.h;
			
			          if (src_w > 0 && src_h > 0 && base_w > 0 && base_h > 0) {
			            uint32_t scale_w = ((uint32_t)base_w * 256u + (uint32_t)src_w / 2u) / (uint32_t)src_w;
			            uint32_t scale_h = ((uint32_t)base_h * 256u + (uint32_t)src_h / 2u) / (uint32_t)src_h;
			            uint32_t zoom = (scale_w > scale_h) ? scale_w : scale_h;
			            if (zoom == 0u) {
			              zoom = 1u;
			            } else if (zoom > 0x0FFFu) {
			              zoom = 0x0FFFu;
			            }
			
			            lv_img_set_zoom(thumb, (uint16_t)zoom);
			
			            int32_t scaled_w32 = (int32_t)(((int32_t)src_w * (int32_t)zoom + 128) >> 8);
			            int32_t scaled_h32 = (int32_t)(((int32_t)src_h * (int32_t)zoom + 128) >> 8);
			            if (scaled_w32 <= 0) {
			              scaled_w32 = 1;
			            }
			            if (scaled_h32 <= 0) {
			              scaled_h32 = 1;
			            }
			
			            lv_coord_t scaled_w = (lv_coord_t)scaled_w32;
			            lv_coord_t scaled_h = (lv_coord_t)scaled_h32;
			
			            lv_coord_t pos_x = base_x + (base_w - scaled_w) / 2;
			            lv_coord_t pos_y = base_y + (base_h - scaled_h) / 2;
			
			            lv_obj_set_size(thumb, scaled_w, scaled_h);
			            lv_obj_set_pos(thumb, pos_x, pos_y);
			
			            printf("[AI识图] preview src=%d x %d target=%d x %d zoom=%u scaled=%d x %d pos=(%d,%d)\n",
			                  (int)src_w, (int)src_h, (int)base_w, (int)base_h, (unsigned)zoom,
			                  (int)scaled_w32, (int)scaled_h32, (int)pos_x, (int)pos_y);
			          } else {
			            lv_img_set_zoom(thumb, 256);
			            lv_obj_set_size(thumb, base_w, base_h);
			            lv_obj_set_pos(thumb, base_x, base_y);
			          }
			
			          lv_obj_invalidate(thumb);
			          } else {
			          lv_img_set_zoom(thumb, 256);
			          lv_img_set_angle(thumb, 0);
			          lv_img_set_src(thumb, NULL);
			          lv_img_set_pivot(thumb, 0, 0);
			          lv_obj_set_size(thumb, (s_ai_img_rec_thumb_base_w > 0) ? s_ai_img_rec_thumb_base_w : AI_IMG_REC_THUMB_DEFAULT_W,
			            (s_ai_img_rec_thumb_base_h > 0) ? s_ai_img_rec_thumb_base_h : AI_IMG_REC_THUMB_DEFAULT_H);
			          lv_obj_set_pos(thumb,
			            (s_ai_img_rec_thumb_base_x >= 0) ? s_ai_img_rec_thumb_base_x : AI_IMG_REC_THUMB_DEFAULT_X,
			            (s_ai_img_rec_thumb_base_y >= 0) ? s_ai_img_rec_thumb_base_y : AI_IMG_REC_THUMB_DEFAULT_Y);
			          lv_obj_add_flag(thumb, LV_OBJ_FLAG_HIDDEN);
			          lv_obj_invalidate(thumb);
			          }
			  }
			
			  if (ui_scr->AI_Img_Rec_lbl_1 && lv_obj_is_valid(ui_scr->AI_Img_Rec_lbl_1)) {
			    const char *question = watchai_ident_get_question();
			    //lv_label_set_text(ui_scr->AI_Img_Rec_lbl_1, question ? question : "");
			  }
			
			  if (has_pending_image) {
			    watchai_ident_update_label_text("识图请求发送中，请稍候...", "zh");
			    if (watchai_ident_start_pending_request() != 0) {
			      watchai_ident_update_label_text("识图请求发送失败，请返回重试", "zh");
			    }
			  } else {
			    watchai_ident_update_label_text("未选择图片，无法发起识图", "zh");
			  }
			}
			break;
			case LV_EVENT_SCREEN_UNLOAD_START:
			{
			  ai_img_rec_stop_all_ai_processes("AI_Img_Rec_unload");
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void AI_Img_Rec_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code video_photo
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  ai_img_rec_stop_all_ai_processes("AI_Img_Rec_btn_1_click");
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_VIDEO_PHOTO);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void AI_Img_Rec_img_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  ai_img_rec_stop_all_ai_processes("AI_Img_Rec_img_6_click");
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

void events_init_AI_Img_Rec(lv_ui *ui)
{
	lv_ui_AI_Img_Rec * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_AI_IMG_REC);
	lv_obj_add_event_cb(ui_scr->AI_Img_Rec, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->AI_Img_Rec, AI_Img_Rec_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->AI_Img_Rec_btn_1, AI_Img_Rec_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->AI_Img_Rec_img_6, AI_Img_Rec_img_6_event_handler, LV_EVENT_ALL, ui);
}

static void text_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			rtc_client_init1();
		}
	}
	break;
	default:
		break;
	}
}

static void text_btn_2_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			rtc_client_init2();
		}
	}
	break;
	default:
		break;
	}
}

static void text_btn_3_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			rtc_client_close();
		}
	}
	break;
	default:
		break;
	}
}

static void text_btn_4_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_HOME_PAGE);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_text(lv_ui *ui)
{
	lv_ui_text * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_TEXT);
	lv_obj_add_event_cb(ui_scr->text, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->text_btn_1, text_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->text_btn_2, text_btn_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->text_btn_3, text_btn_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->text_btn_4, text_btn_4_event_handler, LV_EVENT_ALL, ui);
}

static void chat_page_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_SCREEN_LOAD_START:
			case LV_EVENT_SCREEN_LOADED:
			{
			  lv_ui *ui = lv_event_get_user_data(e);
			  if (!ui) {
			    break;
			  }
			  if (code == LV_EVENT_SCREEN_LOADED) {
			    lv_ui_chat_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CHAT_PAGE);
			    if (ui_scr) {
			      lv_obj_t *parent = ui_scr->chat_page_view_5 ? ui_scr->chat_page_view_5 : ui_scr->chat_page;
			      if (parent) {
			        if (!chat_friend_history_is_ready()) {
			          chat_friend_history_init(parent);
			        }
			        if (s_chat_active_friend.valid && s_chat_active_friend.group_id[0]) {
			          chat_friend_history_set_active_group(s_chat_active_friend.group_id);
			        } else {
			          chat_friend_history_set_active_group(NULL);
			        }
			      }
			    }
			  }
			  chat_page_update_header(ui);
			}
			break;
			case LV_EVENT_SCREEN_UNLOAD_START:
			case LV_EVENT_SCREEN_UNLOADED:
			{
			  chat_friend_history_deinit();
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void chat_page_img_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_ADDRESS_BOOK);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

static void chat_page_img_8_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			lv_ui *ui = lv_event_get_user_data(e);
			if (!ui) {
			  printf("[CHAT][CALL] ui context missing\n");
			  break;
			}
			
			const struct chat_friend_entry *entry = chat_active_friend_get();
			if (!entry || !entry->group_id[0]) {
			  printf("[CHAT][CALL] no active friend selected\n");
			  break;
			}
			
			if (strcmp(entry->group_id, WIFI_CAMERA_WS_LOGIN_IMEI) == 0) {
			  printf("[CHAT][CALL] skip calling self imei=%s\n", entry->group_id);
			  break;
			}
			
			int ws_err = wifi_camera_ws_send_video_call_request(entry->group_id);
			if (ws_err) {
			  printf("[CHAT][CALL] send request failed:%d target=%s\n", ws_err, entry->group_id);
			}
			
			gui_scr_t *screen = ui_get_scr(GUI_SCREEN_CALL);
			if (screen) {
			  lv_ui_call *call_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CALL);
			  if (call_scr) {
			    const char *display_name = entry->group_name[0] ? entry->group_name : entry->group_id;
			    if (call_scr->call_lbl_1 && lv_obj_is_valid(call_scr->call_lbl_1)) {
			      lv_label_set_text(call_scr->call_lbl_1, display_name);
			    }
			    if (call_scr->call_lbl_4 && lv_obj_is_valid(call_scr->call_lbl_4)) {
			      lv_label_set_text(call_scr->call_lbl_4, "正在发起语音通话…");
			    }
			  }
			  ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
			}
		}
	}
	break;
	default:
		break;
	}
}

static void chat_page_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			lv_ui *ui = lv_event_get_user_data(e);
			if (!ui) {
			  return;
			}
			lv_ui_chat_page *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CHAT_PAGE);
			if (!ui_scr) {
			  return;
			}
			lv_obj_t *btn = ui_scr->chat_page_btn_1;
			lv_obj_t *recording_view = ui_scr->chat_page_view_3;
			switch (code)
			{
			case LV_EVENT_PRESSED:
			case LV_EVENT_PRESSING:
			case LV_EVENT_LONG_PRESSED:
			{
			  if (code == LV_EVENT_PRESSED) {
			    if (recording_view && lv_obj_is_valid(recording_view)) {
			      lv_obj_clear_flag(recording_view, LV_OBJ_FLAG_HIDDEN);
			    }
			    if (btn && lv_obj_is_valid(btn)) {
			      lv_obj_add_flag(btn, LV_OBJ_FLAG_HIDDEN);
			    }
			  }
			
			  if (!s_chat_recording_active) {
			    if (ai_voice_recorder_is_running()) {
			      printf("[chat_voice] recorder busy, ignore press\n");
			      if (recording_view && lv_obj_is_valid(recording_view)) {
			        lv_obj_add_flag(recording_view, LV_OBJ_FLAG_HIDDEN);
			      }
			      if (btn && lv_obj_is_valid(btn)) {
			        lv_obj_clear_flag(btn, LV_OBJ_FLAG_HIDDEN);
			      }
			      break;
			    }
			
			    if (!s_chat_active_friend.valid || !s_chat_active_friend.group_id[0]) {
			      printf("[chat_voice] press ignored: no active friend\n");
			      if (recording_view && lv_obj_is_valid(recording_view)) {
			        lv_obj_add_flag(recording_view, LV_OBJ_FLAG_HIDDEN);
			      }
			      if (btn && lv_obj_is_valid(btn)) {
			        lv_obj_clear_flag(btn, LV_OBJ_FLAG_HIDDEN);
			      }
			      break;
			    }
			
			    s_voice_capture_target = VOICE_CAPTURE_TARGET_CHAT;
			    if (ai_voice_recorder_start("chat_btn1")) {
			      s_chat_recording_active = true;
			    } else {
			      printf("[chat_voice] start recorder failed\n");
			      s_voice_capture_target = VOICE_CAPTURE_TARGET_NONE;
			      if (recording_view && lv_obj_is_valid(recording_view)) {
			        lv_obj_add_flag(recording_view, LV_OBJ_FLAG_HIDDEN);
			      }
			      if (btn && lv_obj_is_valid(btn)) {
			        lv_obj_clear_flag(btn, LV_OBJ_FLAG_HIDDEN);
			      }
			    }
			  }
			}
			break;
			case LV_EVENT_RELEASED:
			case LV_EVENT_PRESS_LOST:
			case LV_EVENT_LEAVE:
			case LV_EVENT_CLICKED:
			{
			  if (btn && lv_obj_is_valid(btn)) {
			    lv_obj_clear_flag(btn, LV_OBJ_FLAG_HIDDEN);
			  }
			  if (recording_view && lv_obj_is_valid(recording_view)) {
			    lv_obj_add_flag(recording_view, LV_OBJ_FLAG_HIDDEN);
			  }
			
			  if (s_chat_recording_active || ai_voice_recorder_is_running()) {
			    ai_voice_recorder_stop("chat_btn1");
			  }
			  s_chat_recording_active = false;
			}
			break;
			default:
			  break;
			}
		}
	}
}

void events_init_chat_page(lv_ui *ui)
{
	lv_ui_chat_page * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CHAT_PAGE);
	lv_obj_add_event_cb(ui_scr->chat_page, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->chat_page, chat_page_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->chat_page_img_6, chat_page_img_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->chat_page_img_8, chat_page_img_8_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->chat_page_btn_1, chat_page_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void Edit_Friend_Info_img_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		gui_scr_t * screen = ui_get_scr(GUI_SCREEN_ADDRESS_BOOK);
		if(screen != NULL) {
			ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
		}
	}
	break;
	default:
		break;
	}
}

void events_init_Edit_Friend_Info(lv_ui *ui)
{
	lv_ui_Edit_Friend_Info * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_EDIT_FRIEND_INFO);
	lv_obj_add_event_cb(ui_scr->Edit_Friend_Info, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->Edit_Friend_Info_img_6, Edit_Friend_Info_img_6_event_handler, LV_EVENT_ALL, ui);
}

static void Add_friend_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  lv_obj_clear_flag(guider_ui.Add_friend->Add_friend_view_3, LV_OBJ_FLAG_HIDDEN);
			  lv_obj_clear_flag(guider_ui.Add_friend->Add_friend_lbl_6, LV_OBJ_FLAG_HIDDEN);
			  lv_obj_add_flag(guider_ui.Add_friend->Add_friend_view_4, LV_OBJ_FLAG_HIDDEN);
			  lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
			  add_friend_start_countdown(ui);
			  int ws_err = wifi_camera_ws_send_make_friend_request();
			  if (ws_err) {
			    printf("[Add Friend] upMakeFriend send failed:%d\n", ws_err);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

static void Add_friend_img_6_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
	// LV_EVENT_ALL
	{
		//custom code 
		{
			switch (code)
			{
			case LV_EVENT_CLICKED:
			{
			  add_friend_stop_countdown();
			  gui_scr_t * screen = ui_get_scr(GUI_SCREEN_ADDRESS_BOOK);
			  if(screen != NULL) {
			    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
			  }
			}
			break;
			default:
			  break;
			}
		}
	}
}

void events_init_Add_friend(lv_ui *ui)
{
	lv_ui_Add_friend * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_ADD_FRIEND);
	lv_obj_add_event_cb(ui_scr->Add_friend, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->Add_friend_btn_1, Add_friend_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->Add_friend_img_6, Add_friend_img_6_event_handler, LV_EVENT_ALL, ui);
}

static void call_img_8_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			printf("呼叫中挂断");
		}
	}
	break;
	default:
		break;
	}
}

static void call_img_9_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			printf("被呼叫挂断");
		}
	}
	break;
	default:
		break;
	}
}

static void call_img_10_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			printf("被呼叫接听");
		}
	}
	break;
	default:
		break;
	}
}

static void call_img_11_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			printf("通话中麦克");
		}
	}
	break;
	default:
		break;
	}
}

static void call_img_12_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			printf("通话中挂断");
		}
	}
	break;
	default:
		break;
	}
}

static void call_img_13_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		//custom code 
		{
			printf("通话中喇叭");
		}
	}
	break;
	default:
		break;
	}
}

void events_init_call(lv_ui *ui)
{
	lv_ui_call * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CALL);
	lv_obj_add_event_cb(ui_scr->call, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
	lv_obj_add_event_cb(ui_scr->call_img_8, call_img_8_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->call_img_9, call_img_9_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->call_img_10, call_img_10_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->call_img_11, call_img_11_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->call_img_12, call_img_12_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui_scr->call_img_13, call_img_13_event_handler, LV_EVENT_ALL, ui);
}

void events_init_zyf_ai_page(lv_ui *ui)
{
	lv_ui_zyf_ai_page * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_ZYF_AI_PAGE);
	lv_obj_add_event_cb(ui_scr->zyf_ai_page, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
}

#endif
