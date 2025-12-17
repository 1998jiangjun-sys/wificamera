#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_guider.h"
#include "./gui_timelines/gui_timelines.h"
#include "./gui_group/gui_group.h"
#include "./gui_events/events_init.h"

void scr_push_stack_loaded_handler(lv_event_t *e)
{
	int32_t scr_id = (int32_t)lv_event_get_user_data(e);
	lv_obj_t * src = lv_event_get_target(e);
	gui_scr_t * scr = ui_get_scr(scr_id);
	if (scr != NULL) {
		gui_scr_stack_push(scr);
	}
}
void ui_load_scr_anim(lv_ui *ui, gui_scr_t *screen, lv_scr_load_anim_t anim_type,	uint32_t time,
											uint32_t delay, bool is_clean, bool auto_del, bool is_push_satck)
{
	if (screen == NULL) return;

	gui_scr_t * act_screen = gui_scr_get_act();
	if (act_screen == screen) return;

	gui_timelines_delete();
	gui_scr_set_act_anim(screen, ui, anim_type, time, delay, is_clean, auto_del);

	if (is_push_satck) {
		lv_obj_remove_event_cb(screen->scr, scr_push_stack_loaded_handler);
		if (screen == gui_scr_get_act()) {
			gui_scr_stack_push(act_screen);
		} else {
			lv_obj_add_event_cb(screen->scr, scr_push_stack_loaded_handler, LV_EVENT_SCREEN_LOADED, (void *)act_screen->id);
		}
	}
}

void ui_scr_stack_pop_anim(lv_ui *ui, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay,
														bool is_clean, bool auto_del, bool is_push_satck)
{
	gui_scr_t * screen = gui_scr_stack_pop();
	if (screen == NULL) return;

	ui_load_scr_anim(ui, screen, anim_type, time, delay, is_clean, auto_del, is_push_satck);
}

gui_scr_t * ui_get_scr(int32_t scr_id)
{
	gui_scr_t * screen = gui_scr_get(scr_id);
	if (screen != NULL) return screen;

	if (scr_id == GUI_SCREEN_HOME_PAGE) return gui_scr_create(GUI_SCREEN_HOME_PAGE, "home_page", NULL, (gui_scr_setup_cb_t)setup_scr_home_page, (gui_scr_unload_cb_t)unload_scr_home_page);
	if (scr_id == GUI_SCREEN_VIDEO_REC) return gui_scr_create(GUI_SCREEN_VIDEO_REC, "video_rec", NULL, (gui_scr_setup_cb_t)setup_scr_video_rec, (gui_scr_unload_cb_t)unload_scr_video_rec);
	if (scr_id == GUI_SCREEN_SYS_PROMPT) return gui_scr_create(GUI_SCREEN_SYS_PROMPT, "sys_prompt", NULL, (gui_scr_setup_cb_t)setup_scr_sys_prompt, (gui_scr_unload_cb_t)unload_scr_sys_prompt);
	if (scr_id == GUI_SCREEN_VIDEO_PHOTO) return gui_scr_create(GUI_SCREEN_VIDEO_PHOTO, "video_photo", NULL, (gui_scr_setup_cb_t)setup_scr_video_photo, (gui_scr_unload_cb_t)unload_scr_video_photo);
	if (scr_id == GUI_SCREEN_VIDEO_PLAY) return gui_scr_create(GUI_SCREEN_VIDEO_PLAY, "video_play", NULL, (gui_scr_setup_cb_t)setup_scr_video_play, (gui_scr_unload_cb_t)unload_scr_video_play);
	if (scr_id == GUI_SCREEN_SYS_POPWIN) return gui_scr_create(GUI_SCREEN_SYS_POPWIN, "sys_popwin", NULL, (gui_scr_setup_cb_t)setup_scr_sys_popwin, (gui_scr_unload_cb_t)unload_scr_sys_popwin);
	if (scr_id == GUI_SCREEN_USB_SLAVE) return gui_scr_create(GUI_SCREEN_USB_SLAVE, "usb_slave", NULL, (gui_scr_setup_cb_t)setup_scr_usb_slave, (gui_scr_unload_cb_t)unload_scr_usb_slave);
	if (scr_id == GUI_SCREEN_LANGUAGE_SELECTION) return gui_scr_create(GUI_SCREEN_LANGUAGE_SELECTION, "Language_Selection", NULL, (gui_scr_setup_cb_t)setup_scr_Language_Selection, (gui_scr_unload_cb_t)unload_scr_Language_Selection);
	if (scr_id == GUI_SCREEN_WIFI_SEARCH) return gui_scr_create(GUI_SCREEN_WIFI_SEARCH, "WIFI_search", NULL, (gui_scr_setup_cb_t)setup_scr_WIFI_search, (gui_scr_unload_cb_t)unload_scr_WIFI_search);
	if (scr_id == GUI_SCREEN_WIFI_CONNECTION) return gui_scr_create(GUI_SCREEN_WIFI_CONNECTION, "WIFI_connection", NULL, (gui_scr_setup_cb_t)setup_scr_WIFI_connection, (gui_scr_unload_cb_t)unload_scr_WIFI_connection);
	if (scr_id == GUI_SCREEN_SETING) return gui_scr_create(GUI_SCREEN_SETING, "seting", NULL, (gui_scr_setup_cb_t)setup_scr_seting, (gui_scr_unload_cb_t)unload_scr_seting);
	if (scr_id == GUI_SCREEN_BRIGHTNESS) return gui_scr_create(GUI_SCREEN_BRIGHTNESS, "brightness", NULL, (gui_scr_setup_cb_t)setup_scr_brightness, (gui_scr_unload_cb_t)unload_scr_brightness);
	if (scr_id == GUI_SCREEN_VOLUME) return gui_scr_create(GUI_SCREEN_VOLUME, "volume", NULL, (gui_scr_setup_cb_t)setup_scr_volume, (gui_scr_unload_cb_t)unload_scr_volume);
	if (scr_id == GUI_SCREEN_DORMANCY) return gui_scr_create(GUI_SCREEN_DORMANCY, "dormancy", NULL, (gui_scr_setup_cb_t)setup_scr_dormancy, (gui_scr_unload_cb_t)unload_scr_dormancy);
	if (scr_id == GUI_SCREEN_IMAGE_SIZE) return gui_scr_create(GUI_SCREEN_IMAGE_SIZE, "image_size", NULL, (gui_scr_setup_cb_t)setup_scr_image_size, (gui_scr_unload_cb_t)unload_scr_image_size);
	if (scr_id == GUI_SCREEN_TF_FORMATTING) return gui_scr_create(GUI_SCREEN_TF_FORMATTING, "TF_formatting", NULL, (gui_scr_setup_cb_t)setup_scr_TF_formatting, (gui_scr_unload_cb_t)unload_scr_TF_formatting);
	if (scr_id == GUI_SCREEN_TF_FORMATTING_2) return gui_scr_create(GUI_SCREEN_TF_FORMATTING_2, "TF_formatting_2", NULL, (gui_scr_setup_cb_t)setup_scr_TF_formatting_2, (gui_scr_unload_cb_t)unload_scr_TF_formatting_2);
	if (scr_id == GUI_SCREEN_IMAGE_RESOLUTION) return gui_scr_create(GUI_SCREEN_IMAGE_RESOLUTION, "image_resolution", NULL, (gui_scr_setup_cb_t)setup_scr_image_resolution, (gui_scr_unload_cb_t)unload_scr_image_resolution);
	if (scr_id == GUI_SCREEN_BINDING_DEVICE_CODE) return gui_scr_create(GUI_SCREEN_BINDING_DEVICE_CODE, "Binding_device_code", NULL, (gui_scr_setup_cb_t)setup_scr_Binding_device_code, (gui_scr_unload_cb_t)unload_scr_Binding_device_code);
	if (scr_id == GUI_SCREEN_SOFTWARE_VERSION) return gui_scr_create(GUI_SCREEN_SOFTWARE_VERSION, "software_version", NULL, (gui_scr_setup_cb_t)setup_scr_software_version, (gui_scr_unload_cb_t)unload_scr_software_version);
	if (scr_id == GUI_SCREEN_RESTORE_FACTORY) return gui_scr_create(GUI_SCREEN_RESTORE_FACTORY, "Restore_factory", NULL, (gui_scr_setup_cb_t)setup_scr_Restore_factory, (gui_scr_unload_cb_t)unload_scr_Restore_factory);
	if (scr_id == GUI_SCREEN_RESTORE_FACTORY_2) return gui_scr_create(GUI_SCREEN_RESTORE_FACTORY_2, "Restore_factory_2", NULL, (gui_scr_setup_cb_t)setup_scr_Restore_factory_2, (gui_scr_unload_cb_t)unload_scr_Restore_factory_2);
	if (scr_id == GUI_SCREEN_ADDRESS_BOOK) return gui_scr_create(GUI_SCREEN_ADDRESS_BOOK, "address_book", NULL, (gui_scr_setup_cb_t)setup_scr_address_book, (gui_scr_unload_cb_t)unload_scr_address_book);
	if (scr_id == GUI_SCREEN_VIDEO_RESOLUTION) return gui_scr_create(GUI_SCREEN_VIDEO_RESOLUTION, "video_resolution", NULL, (gui_scr_setup_cb_t)setup_scr_video_resolution, (gui_scr_unload_cb_t)unload_scr_video_resolution);
	if (scr_id == GUI_SCREEN_AI_Q_A) return gui_scr_create(GUI_SCREEN_AI_Q_A, "AI_Q_A", NULL, (gui_scr_setup_cb_t)setup_scr_AI_Q_A, (gui_scr_unload_cb_t)unload_scr_AI_Q_A);
	if (scr_id == GUI_SCREEN_SHUT_DOWN) return gui_scr_create(GUI_SCREEN_SHUT_DOWN, "Shut_down", NULL, (gui_scr_setup_cb_t)setup_scr_Shut_down, (gui_scr_unload_cb_t)unload_scr_Shut_down);
	if (scr_id == GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE) return gui_scr_create(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE, "video_dir_landscape_mode", NULL, (gui_scr_setup_cb_t)setup_scr_video_dir_landscape_mode, (gui_scr_unload_cb_t)unload_scr_video_dir_landscape_mode);
	if (scr_id == GUI_SCREEN_AI_PAYMENT_CODE) return gui_scr_create(GUI_SCREEN_AI_PAYMENT_CODE, "AI_payment_code", NULL, (gui_scr_setup_cb_t)setup_scr_AI_payment_code, (gui_scr_unload_cb_t)unload_scr_AI_payment_code);
	if (scr_id == GUI_SCREEN_AI_IMG_REC) return gui_scr_create(GUI_SCREEN_AI_IMG_REC, "AI_Img_Rec", NULL, (gui_scr_setup_cb_t)setup_scr_AI_Img_Rec, (gui_scr_unload_cb_t)unload_scr_AI_Img_Rec);
	if (scr_id == GUI_SCREEN_TEXT) return gui_scr_create(GUI_SCREEN_TEXT, "text", NULL, (gui_scr_setup_cb_t)setup_scr_text, (gui_scr_unload_cb_t)unload_scr_text);
	if (scr_id == GUI_SCREEN_CHAT_PAGE) return gui_scr_create(GUI_SCREEN_CHAT_PAGE, "chat_page", NULL, (gui_scr_setup_cb_t)setup_scr_chat_page, (gui_scr_unload_cb_t)unload_scr_chat_page);
	if (scr_id == GUI_SCREEN_EDIT_FRIEND_INFO) return gui_scr_create(GUI_SCREEN_EDIT_FRIEND_INFO, "Edit_Friend_Info", NULL, (gui_scr_setup_cb_t)setup_scr_Edit_Friend_Info, (gui_scr_unload_cb_t)unload_scr_Edit_Friend_Info);
	if (scr_id == GUI_SCREEN_ADD_FRIEND) return gui_scr_create(GUI_SCREEN_ADD_FRIEND, "Add_friend", NULL, (gui_scr_setup_cb_t)setup_scr_Add_friend, (gui_scr_unload_cb_t)unload_scr_Add_friend);
	if (scr_id == GUI_SCREEN_CALL) return gui_scr_create(GUI_SCREEN_CALL, "call", NULL, (gui_scr_setup_cb_t)setup_scr_call, (gui_scr_unload_cb_t)unload_scr_call);
	if (scr_id == GUI_SCREEN_ZYF_AI_PAGE) return gui_scr_create(GUI_SCREEN_ZYF_AI_PAGE, "zyf_ai_page", NULL, (gui_scr_setup_cb_t)setup_scr_zyf_ai_page, (gui_scr_unload_cb_t)unload_scr_zyf_ai_page);
	return NULL;
}

gui_scr_t * ui_get_setup_scr(int32_t scr_id)
{
	gui_scr_t * screen = ui_get_scr(scr_id);
	if (screen == NULL) return NULL;

	if (screen->scr == NULL || lv_obj_is_valid(screen->scr) == false) {
		if (screen->setup_cb != NULL) {
			screen->scr = screen->setup_cb(&guider_ui);
			screen->is_del = false;
			if (screen->scr == NULL || lv_obj_is_valid(screen->scr) == false) {
				screen->is_del = true;
				return NULL;
			}
		}
	}
	return screen;
}

lv_obj_t * ui_get_setup_scr_obj(int32_t scr_id)
{
	gui_scr_t * screen = ui_get_setup_scr(scr_id);
	if (screen == NULL) return NULL;

	return screen->scr;
}


void * ui_get_scr_ptr(lv_ui *ui, int32_t scr_id)
{
	if (ui == NULL) return NULL;

	if (scr_id == GUI_SCREEN_HOME_PAGE) return ui->home_page;
	if (scr_id == GUI_SCREEN_VIDEO_REC) return ui->video_rec;
	if (scr_id == GUI_SCREEN_SYS_PROMPT) return ui->sys_prompt;
	if (scr_id == GUI_SCREEN_VIDEO_PHOTO) return ui->video_photo;
	if (scr_id == GUI_SCREEN_VIDEO_PLAY) return ui->video_play;
	if (scr_id == GUI_SCREEN_SYS_POPWIN) return ui->sys_popwin;
	if (scr_id == GUI_SCREEN_USB_SLAVE) return ui->usb_slave;
	if (scr_id == GUI_SCREEN_LANGUAGE_SELECTION) return ui->Language_Selection;
	if (scr_id == GUI_SCREEN_WIFI_SEARCH) return ui->WIFI_search;
	if (scr_id == GUI_SCREEN_WIFI_CONNECTION) return ui->WIFI_connection;
	if (scr_id == GUI_SCREEN_SETING) return ui->seting;
	if (scr_id == GUI_SCREEN_BRIGHTNESS) return ui->brightness;
	if (scr_id == GUI_SCREEN_VOLUME) return ui->volume;
	if (scr_id == GUI_SCREEN_DORMANCY) return ui->dormancy;
	if (scr_id == GUI_SCREEN_IMAGE_SIZE) return ui->image_size;
	if (scr_id == GUI_SCREEN_TF_FORMATTING) return ui->TF_formatting;
	if (scr_id == GUI_SCREEN_TF_FORMATTING_2) return ui->TF_formatting_2;
	if (scr_id == GUI_SCREEN_IMAGE_RESOLUTION) return ui->image_resolution;
	if (scr_id == GUI_SCREEN_BINDING_DEVICE_CODE) return ui->Binding_device_code;
	if (scr_id == GUI_SCREEN_SOFTWARE_VERSION) return ui->software_version;
	if (scr_id == GUI_SCREEN_RESTORE_FACTORY) return ui->Restore_factory;
	if (scr_id == GUI_SCREEN_RESTORE_FACTORY_2) return ui->Restore_factory_2;
	if (scr_id == GUI_SCREEN_ADDRESS_BOOK) return ui->address_book;
	if (scr_id == GUI_SCREEN_VIDEO_RESOLUTION) return ui->video_resolution;
	if (scr_id == GUI_SCREEN_AI_Q_A) return ui->AI_Q_A;
	if (scr_id == GUI_SCREEN_SHUT_DOWN) return ui->Shut_down;
	if (scr_id == GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE) return ui->video_dir_landscape_mode;
	if (scr_id == GUI_SCREEN_AI_PAYMENT_CODE) return ui->AI_payment_code;
	if (scr_id == GUI_SCREEN_AI_IMG_REC) return ui->AI_Img_Rec;
	if (scr_id == GUI_SCREEN_TEXT) return ui->text;
	if (scr_id == GUI_SCREEN_CHAT_PAGE) return ui->chat_page;
	if (scr_id == GUI_SCREEN_EDIT_FRIEND_INFO) return ui->Edit_Friend_Info;
	if (scr_id == GUI_SCREEN_ADD_FRIEND) return ui->Add_friend;
	if (scr_id == GUI_SCREEN_CALL) return ui->call;
	if (scr_id == GUI_SCREEN_ZYF_AI_PAGE) return ui->zyf_ai_page;
	return NULL;
}

void ui_free_scr_ptr(lv_ui *ui, int32_t scr_id)
{
	if (ui == NULL) return;

	if (scr_id == GUI_SCREEN_HOME_PAGE) {
		if (ui->home_page != NULL) lv_mem_free(ui->home_page);
		ui->home_page = NULL;
	} else if (scr_id == GUI_SCREEN_VIDEO_REC) {
		if (ui->video_rec != NULL) lv_mem_free(ui->video_rec);
		ui->video_rec = NULL;
	} else if (scr_id == GUI_SCREEN_SYS_PROMPT) {
		if (ui->sys_prompt != NULL) lv_mem_free(ui->sys_prompt);
		ui->sys_prompt = NULL;
	} else if (scr_id == GUI_SCREEN_VIDEO_PHOTO) {
		if (ui->video_photo != NULL) lv_mem_free(ui->video_photo);
		ui->video_photo = NULL;
	} else if (scr_id == GUI_SCREEN_VIDEO_PLAY) {
		if (ui->video_play != NULL) lv_mem_free(ui->video_play);
		ui->video_play = NULL;
	} else if (scr_id == GUI_SCREEN_SYS_POPWIN) {
		if (ui->sys_popwin != NULL) lv_mem_free(ui->sys_popwin);
		ui->sys_popwin = NULL;
	} else if (scr_id == GUI_SCREEN_USB_SLAVE) {
		if (ui->usb_slave != NULL) lv_mem_free(ui->usb_slave);
		ui->usb_slave = NULL;
	} else if (scr_id == GUI_SCREEN_LANGUAGE_SELECTION) {
		if (ui->Language_Selection != NULL) lv_mem_free(ui->Language_Selection);
		ui->Language_Selection = NULL;
	} else if (scr_id == GUI_SCREEN_WIFI_SEARCH) {
		if (ui->WIFI_search != NULL) lv_mem_free(ui->WIFI_search);
		ui->WIFI_search = NULL;
	} else if (scr_id == GUI_SCREEN_WIFI_CONNECTION) {
		if (ui->WIFI_connection != NULL) lv_mem_free(ui->WIFI_connection);
		ui->WIFI_connection = NULL;
	} else if (scr_id == GUI_SCREEN_SETING) {
		if (ui->seting != NULL) lv_mem_free(ui->seting);
		ui->seting = NULL;
	} else if (scr_id == GUI_SCREEN_BRIGHTNESS) {
		if (ui->brightness != NULL) lv_mem_free(ui->brightness);
		ui->brightness = NULL;
	} else if (scr_id == GUI_SCREEN_VOLUME) {
		if (ui->volume != NULL) lv_mem_free(ui->volume);
		ui->volume = NULL;
	} else if (scr_id == GUI_SCREEN_DORMANCY) {
		if (ui->dormancy != NULL) lv_mem_free(ui->dormancy);
		ui->dormancy = NULL;
	} else if (scr_id == GUI_SCREEN_IMAGE_SIZE) {
		if (ui->image_size != NULL) lv_mem_free(ui->image_size);
		ui->image_size = NULL;
	} else if (scr_id == GUI_SCREEN_TF_FORMATTING) {
		if (ui->TF_formatting != NULL) lv_mem_free(ui->TF_formatting);
		ui->TF_formatting = NULL;
	} else if (scr_id == GUI_SCREEN_TF_FORMATTING_2) {
		if (ui->TF_formatting_2 != NULL) lv_mem_free(ui->TF_formatting_2);
		ui->TF_formatting_2 = NULL;
	} else if (scr_id == GUI_SCREEN_IMAGE_RESOLUTION) {
		if (ui->image_resolution != NULL) lv_mem_free(ui->image_resolution);
		ui->image_resolution = NULL;
	} else if (scr_id == GUI_SCREEN_BINDING_DEVICE_CODE) {
		if (ui->Binding_device_code != NULL) lv_mem_free(ui->Binding_device_code);
		ui->Binding_device_code = NULL;
	} else if (scr_id == GUI_SCREEN_SOFTWARE_VERSION) {
		if (ui->software_version != NULL) lv_mem_free(ui->software_version);
		ui->software_version = NULL;
	} else if (scr_id == GUI_SCREEN_RESTORE_FACTORY) {
		if (ui->Restore_factory != NULL) lv_mem_free(ui->Restore_factory);
		ui->Restore_factory = NULL;
	} else if (scr_id == GUI_SCREEN_RESTORE_FACTORY_2) {
		if (ui->Restore_factory_2 != NULL) lv_mem_free(ui->Restore_factory_2);
		ui->Restore_factory_2 = NULL;
	} else if (scr_id == GUI_SCREEN_ADDRESS_BOOK) {
		if (ui->address_book != NULL) lv_mem_free(ui->address_book);
		ui->address_book = NULL;
	} else if (scr_id == GUI_SCREEN_VIDEO_RESOLUTION) {
		if (ui->video_resolution != NULL) lv_mem_free(ui->video_resolution);
		ui->video_resolution = NULL;
	} else if (scr_id == GUI_SCREEN_AI_Q_A) {
		if (ui->AI_Q_A != NULL) lv_mem_free(ui->AI_Q_A);
		ui->AI_Q_A = NULL;
	} else if (scr_id == GUI_SCREEN_SHUT_DOWN) {
		if (ui->Shut_down != NULL) lv_mem_free(ui->Shut_down);
		ui->Shut_down = NULL;
	} else if (scr_id == GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE) {
		if (ui->video_dir_landscape_mode != NULL) lv_mem_free(ui->video_dir_landscape_mode);
		ui->video_dir_landscape_mode = NULL;
	} else if (scr_id == GUI_SCREEN_AI_PAYMENT_CODE) {
		if (ui->AI_payment_code != NULL) lv_mem_free(ui->AI_payment_code);
		ui->AI_payment_code = NULL;
	} else if (scr_id == GUI_SCREEN_AI_IMG_REC) {
		if (ui->AI_Img_Rec != NULL) lv_mem_free(ui->AI_Img_Rec);
		ui->AI_Img_Rec = NULL;
	} else if (scr_id == GUI_SCREEN_TEXT) {
		if (ui->text != NULL) lv_mem_free(ui->text);
		ui->text = NULL;
	} else if (scr_id == GUI_SCREEN_CHAT_PAGE) {
		if (ui->chat_page != NULL) lv_mem_free(ui->chat_page);
		ui->chat_page = NULL;
	} else if (scr_id == GUI_SCREEN_EDIT_FRIEND_INFO) {
		if (ui->Edit_Friend_Info != NULL) lv_mem_free(ui->Edit_Friend_Info);
		ui->Edit_Friend_Info = NULL;
	} else if (scr_id == GUI_SCREEN_ADD_FRIEND) {
		if (ui->Add_friend != NULL) lv_mem_free(ui->Add_friend);
		ui->Add_friend = NULL;
	} else if (scr_id == GUI_SCREEN_CALL) {
		if (ui->call != NULL) lv_mem_free(ui->call);
		ui->call = NULL;
	} else if (scr_id == GUI_SCREEN_ZYF_AI_PAGE) {
		if (ui->zyf_ai_page != NULL) lv_mem_free(ui->zyf_ai_page);
		ui->zyf_ai_page = NULL;
	}
}

bool ui_is_act_scr(int32_t scr_id)
{
	return gui_scr_is_act(ui_get_scr(scr_id));
}

void ui_init_style(lv_style_t * style)
{
	if(style->prop_cnt > 1)
		lv_style_reset(style);
	else
		lv_style_init(style);
}


void setup_ui(lv_ui *ui)
{
	lv_i18n_init(lv_i18n_language_pack);
	lv_i18n_set_locale(lv_i18n_get_default_locale());
	init_gui_fonts();
	ui_style_init();
#if LV_USE_MSG
	gui_msg_init(ui);
#endif
	gui_group_init();
	ui_scr_manager_init();
	gui_scr_t *scr = ui_get_scr(GUI_SCREEN_USB_SLAVE);
	ui_load_scr_anim(ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
	events_init(ui);
	gui_timelines_init(ui);
}
void clock_count_with_year(int *year, int *month, int *day, int *hour, int *min, int *sec)
{
	int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((*year % 4 == 0 && *year % 100 != 0) || (*year % 400 == 0)) {
		days_in_month[1] = 29;
	}
	(*sec)++;
	if (*sec >= 60) {
		*sec = 0;
		(*min)++;
	}
	if (*min >= 60) {
		*min = 0;
		(*hour)++;
	}
	if (*hour >= 24) {
		*hour = 0;
		(*day)++;
	}
	if (*day > days_in_month[*month - 1]) {
		*day = 1;
		(*month)++;
		if (*month > 12) {
			*month = 1;
			(*year)++;
		}
	}
}

#endif
