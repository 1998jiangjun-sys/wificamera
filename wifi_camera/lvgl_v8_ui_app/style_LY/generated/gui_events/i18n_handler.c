#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "./i18n_handler.h"

void i18n_refresh_texts(int32_t scr_id)
{

	if (scr_id == GUI_SCREEN_HOME_PAGE && guider_ui.home_page) {
		lv_ui_home_page * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_HOME_PAGE);
		if (ui_scr->home_page_lbl_1 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_1)) {
			lv_label_set_text(ui_scr->home_page_lbl_1, _("sunny"));
			const lv_font_t * font = _font("sunny");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->home_page_lbl_2 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_2)) {
			lv_label_set_text(ui_scr->home_page_lbl_2, _("Sun"));
			const lv_font_t * font = _font("Sun");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->home_page_lbl_9 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_9)) {
			lv_label_set_text(ui_scr->home_page_lbl_9, _("AIQA"));
			const lv_font_t * font = _font("AIQA");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_9, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->home_page_lbl_10 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_10)) {
			lv_label_set_text(ui_scr->home_page_lbl_10, _("Settings"));
			const lv_font_t * font = _font("Settings");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_10, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->home_page_lbl_7 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_7)) {
			lv_label_set_text(ui_scr->home_page_lbl_7, _("Album"));
			const lv_font_t * font = _font("Album");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_7, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->home_page_lbl_8 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_8)) {
			lv_label_set_text(ui_scr->home_page_lbl_8, _("Contacts"));
			const lv_font_t * font = _font("Contacts");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_8, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->home_page_lbl_5 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_5)) {
			lv_label_set_text(ui_scr->home_page_lbl_5, _("Takeaphoto"));
			const lv_font_t * font = _font("Takeaphoto");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_5, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->home_page_lbl_6 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_6)) {
			lv_label_set_text(ui_scr->home_page_lbl_6, _("Recordavideo"));
			const lv_font_t * font = _font("Recordavideo");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_6, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->home_page_lbl_4 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_4)) {
			lv_label_set_text(ui_scr->home_page_lbl_4, _("SmartKidsCamera"));
			const lv_font_t * font = _font("SmartKidsCamera");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_4, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->home_page_btn_3_label != NULL && lv_obj_is_valid(ui_scr->home_page_btn_3_label)) {
			lv_label_set_text(ui_scr->home_page_btn_3_label, _("Confirm"));
			const lv_font_t * font = _font("Confirm");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_btn_3_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->home_page_lbl_13 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_13)) {
			lv_label_set_text(ui_scr->home_page_lbl_13, _("Turnoffsoundreminder"));
			const lv_font_t * font = _font("Turnoffsoundreminder");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_13, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->home_page_btn_2_label != NULL && lv_obj_is_valid(ui_scr->home_page_btn_2_label)) {
			lv_label_set_text(ui_scr->home_page_btn_2_label, _("Confirm"));
			const lv_font_t * font = _font("Confirm");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_btn_2_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->home_page_lbl_11 != NULL && lv_obj_is_valid(ui_scr->home_page_lbl_11)) {
			lv_label_set_text(ui_scr->home_page_lbl_11, _("PleaseconnecttoWiFifirst"));
			const lv_font_t * font = _font("PleaseconnecttoWiFifirst");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->home_page_lbl_11, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_SYS_POPWIN && guider_ui.sys_popwin) {
		lv_ui_sys_popwin * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_POPWIN);
		if (ui_scr->sys_popwin_lbl_1 != NULL && lv_obj_is_valid(ui_scr->sys_popwin_lbl_1)) {
			lv_label_set_text(ui_scr->sys_popwin_lbl_1, _("del_file"));
			const lv_font_t * font = _font("del_file");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->sys_popwin_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->sys_popwin_btn_1_label != NULL && lv_obj_is_valid(ui_scr->sys_popwin_btn_1_label)) {
			lv_label_set_text(ui_scr->sys_popwin_btn_1_label, _("cancel"));
			const lv_font_t * font = _font("cancel");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->sys_popwin_btn_1_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
				lv_obj_set_style_text_font(ui_scr->sys_popwin_btn_1_label, font, LV_PART_MAIN|LV_STATE_FOCUSED);
			}
		}
		if (ui_scr->sys_popwin_btn_2_label != NULL && lv_obj_is_valid(ui_scr->sys_popwin_btn_2_label)) {
			lv_label_set_text(ui_scr->sys_popwin_btn_2_label, _("ensure"));
			const lv_font_t * font = _font("ensure");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->sys_popwin_btn_2_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
				lv_obj_set_style_text_font(ui_scr->sys_popwin_btn_2_label, font, LV_PART_MAIN|LV_STATE_FOCUSED);
			}
		}
	}

	if (scr_id == GUI_SCREEN_LANGUAGE_SELECTION && guider_ui.Language_Selection) {
		lv_ui_Language_Selection * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_LANGUAGE_SELECTION);
		if (ui_scr->Language_Selection_btn_1_label != NULL && lv_obj_is_valid(ui_scr->Language_Selection_btn_1_label)) {
			lv_label_set_text(ui_scr->Language_Selection_btn_1_label, _("Confirm"));
			const lv_font_t * font = _font("Confirm");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Language_Selection_btn_1_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->Language_Selection_lbl_1 != NULL && lv_obj_is_valid(ui_scr->Language_Selection_lbl_1)) {
			lv_label_set_text(ui_scr->Language_Selection_lbl_1, _("Please_select_your_system_language"));
			const lv_font_t * font = _font("Please_select_your_system_language");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Language_Selection_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_WIFI_SEARCH && guider_ui.WIFI_search) {
		lv_ui_WIFI_search * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_WIFI_SEARCH);
		if (ui_scr->WIFI_search_lbl_1 != NULL && lv_obj_is_valid(ui_scr->WIFI_search_lbl_1)) {
			lv_label_set_text(ui_scr->WIFI_search_lbl_1, _("WiFiConnection1"));
			const lv_font_t * font = _font("WiFiConnection1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->WIFI_search_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->WIFI_search_lbl_4 != NULL && lv_obj_is_valid(ui_scr->WIFI_search_lbl_4)) {
			lv_label_set_text(ui_scr->WIFI_search_lbl_4, _("Searchingfornearbyavailablenetworks"));
			const lv_font_t * font = _font("Searchingfornearbyavailablenetworks");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->WIFI_search_lbl_4, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->WIFI_search_lbl_5 != NULL && lv_obj_is_valid(ui_scr->WIFI_search_lbl_5)) {
			lv_label_set_text(ui_scr->WIFI_search_lbl_5, _("SelectanearbyWiFinetwork"));
			const lv_font_t * font = _font("SelectanearbyWiFinetwork");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->WIFI_search_lbl_5, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_WIFI_CONNECTION && guider_ui.WIFI_connection) {
		lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_WIFI_CONNECTION);
		if (ui_scr->WIFI_connection_edit_2 != NULL && lv_obj_is_valid(ui_scr->WIFI_connection_edit_2)) {
			lv_textarea_set_text(ui_scr->WIFI_connection_edit_2, _("Pleaseenterpassword"));
			const lv_font_t * font = _font("Pleaseenterpassword");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->WIFI_connection_edit_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->WIFI_connection_btn_1_label != NULL && lv_obj_is_valid(ui_scr->WIFI_connection_btn_1_label)) {
			lv_label_set_text(ui_scr->WIFI_connection_btn_1_label, _("Done"));
			const lv_font_t * font = _font("Done");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->WIFI_connection_btn_1_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->WIFI_connection_btn_2_label != NULL && lv_obj_is_valid(ui_scr->WIFI_connection_btn_2_label)) {
			lv_label_set_text(ui_scr->WIFI_connection_btn_2_label, _("delete"));
			const lv_font_t * font = _font("delete");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->WIFI_connection_btn_2_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->WIFI_connection_lbl_3 != NULL && lv_obj_is_valid(ui_scr->WIFI_connection_lbl_3)) {
			lv_label_set_text(ui_scr->WIFI_connection_lbl_3, _("Passwordmustbeatleast8characterslong"));
			const lv_font_t * font = _font("Passwordmustbeatleast8characterslong");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->WIFI_connection_lbl_3, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_SETING && guider_ui.seting) {
		lv_ui_seting * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SETING);
		if (ui_scr->seting_lbl_21 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_21)) {
			lv_label_set_text(ui_scr->seting_lbl_21, _("Videoresolution"));
			const lv_font_t * font = _font("Videoresolution");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_21, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_18 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_18)) {
			lv_label_set_text(ui_scr->seting_lbl_18, _("Restoretofactorysettings"));
			const lv_font_t * font = _font("Restoretofactorysettings");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_18, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_17 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_17)) {
			lv_label_set_text(ui_scr->seting_lbl_17, _("Softwareversion"));
			const lv_font_t * font = _font("Softwareversion");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_17, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_16 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_16)) {
			lv_label_set_text(ui_scr->seting_lbl_16, _("Devicebindingcode"));
			const lv_font_t * font = _font("Devicebindingcode");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_16, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_14 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_14)) {
			lv_label_set_text(ui_scr->seting_lbl_14, _("Photoresolution"));
			const lv_font_t * font = _font("Photoresolution");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_14, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_13 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_13)) {
			lv_label_set_text(ui_scr->seting_lbl_13, _("FormatTFCard"));
			const lv_font_t * font = _font("FormatTFCard");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_13, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_10 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_10)) {
			lv_label_set_text(ui_scr->seting_lbl_10, _("Imagequality"));
			const lv_font_t * font = _font("Imagequality");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_10, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_9 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_9)) {
			lv_label_set_text(ui_scr->seting_lbl_9, _("Autoscreenoff"));
			const lv_font_t * font = _font("Autoscreenoff");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_9, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_7 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_7)) {
			lv_label_set_text(ui_scr->seting_lbl_7, _("WiFiConnection"));
			const lv_font_t * font = _font("WiFiConnection");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_7, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_23 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_23)) {
			lv_label_set_text(ui_scr->seting_lbl_23, _("Language"));
			const lv_font_t * font = _font("Language");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_23, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_3 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_3)) {
			lv_label_set_text(ui_scr->seting_lbl_3, _("Volume"));
			const lv_font_t * font = _font("Volume");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_3, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_1 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_1)) {
			lv_label_set_text(ui_scr->seting_lbl_1, _("Brightness"));
			const lv_font_t * font = _font("Brightness");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_24 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_24)) {
			lv_label_set_text(ui_scr->seting_lbl_24, _("PremiumMember"));
			const lv_font_t * font = _font("PremiumMember");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_24, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->seting_lbl_20 != NULL && lv_obj_is_valid(ui_scr->seting_lbl_20)) {
			lv_label_set_text(ui_scr->seting_lbl_20, _("Settings1"));
			const lv_font_t * font = _font("Settings1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->seting_lbl_20, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_BRIGHTNESS && guider_ui.brightness) {
		lv_ui_brightness * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_BRIGHTNESS);
		if (ui_scr->brightness_lbl_2 != NULL && lv_obj_is_valid(ui_scr->brightness_lbl_2)) {
			lv_label_set_text(ui_scr->brightness_lbl_2, _("Brightness1"));
			const lv_font_t * font = _font("Brightness1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->brightness_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_VOLUME && guider_ui.volume) {
		lv_ui_volume * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VOLUME);
		if (ui_scr->volume_lbl_1 != NULL && lv_obj_is_valid(ui_scr->volume_lbl_1)) {
			lv_label_set_text(ui_scr->volume_lbl_1, _("Volume1"));
			const lv_font_t * font = _font("Volume1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->volume_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->volume_lbl_4 != NULL && lv_obj_is_valid(ui_scr->volume_lbl_4)) {
			lv_label_set_text(ui_scr->volume_lbl_4, _("SilentMode"));
			const lv_font_t * font = _font("SilentMode");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->volume_lbl_4, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_DORMANCY && guider_ui.dormancy) {
		lv_ui_dormancy * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_DORMANCY);
		if (ui_scr->dormancy_lbl_1 != NULL && lv_obj_is_valid(ui_scr->dormancy_lbl_1)) {
			lv_label_set_text(ui_scr->dormancy_lbl_1, _("Autoscreenoff1"));
			const lv_font_t * font = _font("Autoscreenoff1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->dormancy_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->dormancy_lbl_4 != NULL && lv_obj_is_valid(ui_scr->dormancy_lbl_4)) {
			lv_label_set_text(ui_scr->dormancy_lbl_4, _("Stillon"));
			const lv_font_t * font = _font("Stillon");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->dormancy_lbl_4, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->dormancy_lbl_3 != NULL && lv_obj_is_valid(ui_scr->dormancy_lbl_3)) {
			lv_label_set_text(ui_scr->dormancy_lbl_3, _("3minutes"));
			const lv_font_t * font = _font("3minutes");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->dormancy_lbl_3, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->dormancy_lbl_2 != NULL && lv_obj_is_valid(ui_scr->dormancy_lbl_2)) {
			lv_label_set_text(ui_scr->dormancy_lbl_2, _("1minute"));
			const lv_font_t * font = _font("1minute");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->dormancy_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_IMAGE_SIZE && guider_ui.image_size) {
		lv_ui_image_size * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_IMAGE_SIZE);
		if (ui_scr->image_size_lbl_1 != NULL && lv_obj_is_valid(ui_scr->image_size_lbl_1)) {
			lv_label_set_text(ui_scr->image_size_lbl_1, _("Imagequality1"));
			const lv_font_t * font = _font("Imagequality1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->image_size_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->image_size_lbl_2 != NULL && lv_obj_is_valid(ui_scr->image_size_lbl_2)) {
			lv_label_set_text(ui_scr->image_size_lbl_2, _("High"));
			const lv_font_t * font = _font("High");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->image_size_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->image_size_lbl_3 != NULL && lv_obj_is_valid(ui_scr->image_size_lbl_3)) {
			lv_label_set_text(ui_scr->image_size_lbl_3, _("Medium"));
			const lv_font_t * font = _font("Medium");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->image_size_lbl_3, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->image_size_lbl_4 != NULL && lv_obj_is_valid(ui_scr->image_size_lbl_4)) {
			lv_label_set_text(ui_scr->image_size_lbl_4, _("Low"));
			const lv_font_t * font = _font("Low");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->image_size_lbl_4, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_TF_FORMATTING && guider_ui.TF_formatting) {
		lv_ui_TF_formatting * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_TF_FORMATTING);
		if (ui_scr->TF_formatting_lbl_3 != NULL && lv_obj_is_valid(ui_scr->TF_formatting_lbl_3)) {
			lv_label_set_text(ui_scr->TF_formatting_lbl_3, _("FormattingwilldeletealldataContinue"));
			const lv_font_t * font = _font("FormattingwilldeletealldataContinue");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_lbl_3, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->TF_formatting_btn_1_label != NULL && lv_obj_is_valid(ui_scr->TF_formatting_btn_1_label)) {
			lv_label_set_text(ui_scr->TF_formatting_btn_1_label, _("Format"));
			const lv_font_t * font = _font("Format");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_btn_1_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->TF_formatting_lbl_5 != NULL && lv_obj_is_valid(ui_scr->TF_formatting_lbl_5)) {
			lv_label_set_text(ui_scr->TF_formatting_lbl_5, _("ThisoperationisirreversiblePleaseproceedwithcaution"));
			const lv_font_t * font = _font("ThisoperationisirreversiblePleaseproceedwithcaution");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_lbl_5, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->TF_formatting_lbl_4 != NULL && lv_obj_is_valid(ui_scr->TF_formatting_lbl_4)) {
			lv_label_set_text(ui_scr->TF_formatting_lbl_4, _("AreyousureyouwanttoformattheTFcard"));
			const lv_font_t * font = _font("AreyousureyouwanttoformattheTFcard");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_lbl_4, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->TF_formatting_btn_2_label != NULL && lv_obj_is_valid(ui_scr->TF_formatting_btn_2_label)) {
			lv_label_set_text(ui_scr->TF_formatting_btn_2_label, _("Cancel"));
			const lv_font_t * font = _font("Cancel");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_btn_2_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->TF_formatting_btn_3_label != NULL && lv_obj_is_valid(ui_scr->TF_formatting_btn_3_label)) {
			lv_label_set_text(ui_scr->TF_formatting_btn_3_label, _("Confirm"));
			const lv_font_t * font = _font("Confirm");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_btn_3_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->TF_formatting_lbl_6 != NULL && lv_obj_is_valid(ui_scr->TF_formatting_lbl_6)) {
			lv_label_set_text(ui_scr->TF_formatting_lbl_6, _("NoSDcard"));
			const lv_font_t * font = _font("NoSDcard");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_lbl_6, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->TF_formatting_lbl_1 != NULL && lv_obj_is_valid(ui_scr->TF_formatting_lbl_1)) {
			lv_label_set_text(ui_scr->TF_formatting_lbl_1, _("FormatTFCard1"));
			const lv_font_t * font = _font("FormatTFCard1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_TF_FORMATTING_2 && guider_ui.TF_formatting_2) {
		lv_ui_TF_formatting_2 * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_TF_FORMATTING_2);
		if (ui_scr->TF_formatting_2_lbl_2 != NULL && lv_obj_is_valid(ui_scr->TF_formatting_2_lbl_2)) {
			lv_label_set_text(ui_scr->TF_formatting_2_lbl_2, _("FormatTFCard1"));
			const lv_font_t * font = _font("FormatTFCard1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_2_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->TF_formatting_2_lbl_3 != NULL && lv_obj_is_valid(ui_scr->TF_formatting_2_lbl_3)) {
			lv_label_set_text(ui_scr->TF_formatting_2_lbl_3, _("Pleasewait"));
			const lv_font_t * font = _font("Pleasewait");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_2_lbl_3, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->TF_formatting_2_lbl_4 != NULL && lv_obj_is_valid(ui_scr->TF_formatting_2_lbl_4)) {
			lv_label_set_text(ui_scr->TF_formatting_2_lbl_4, _("Formatcompleted"));
			const lv_font_t * font = _font("Formatcompleted");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->TF_formatting_2_lbl_4, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_IMAGE_RESOLUTION && guider_ui.image_resolution) {
		lv_ui_image_resolution * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_IMAGE_RESOLUTION);
		if (ui_scr->image_resolution_lbl_1 != NULL && lv_obj_is_valid(ui_scr->image_resolution_lbl_1)) {
			lv_label_set_text(ui_scr->image_resolution_lbl_1, _("Photoresolution1"));
			const lv_font_t * font = _font("Photoresolution1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->image_resolution_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_BINDING_DEVICE_CODE && guider_ui.Binding_device_code) {
		lv_ui_Binding_device_code * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_BINDING_DEVICE_CODE);
		if (ui_scr->Binding_device_code_lbl_1 != NULL && lv_obj_is_valid(ui_scr->Binding_device_code_lbl_1)) {
			lv_label_set_text(ui_scr->Binding_device_code_lbl_1, _("Devicebindingcode1"));
			const lv_font_t * font = _font("Devicebindingcode1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Binding_device_code_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_SOFTWARE_VERSION && guider_ui.software_version) {
		lv_ui_software_version * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SOFTWARE_VERSION);
		if (ui_scr->software_version_lbl_1 != NULL && lv_obj_is_valid(ui_scr->software_version_lbl_1)) {
			lv_label_set_text(ui_scr->software_version_lbl_1, _("Softwareversion1"));
			const lv_font_t * font = _font("Softwareversion1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->software_version_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->software_version_btn_1_label != NULL && lv_obj_is_valid(ui_scr->software_version_btn_1_label)) {
			lv_label_set_text(ui_scr->software_version_btn_1_label, _("Checkforupdates"));
			const lv_font_t * font = _font("Checkforupdates");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->software_version_btn_1_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->software_version_lbl_2 != NULL && lv_obj_is_valid(ui_scr->software_version_lbl_2)) {
			lv_label_set_text(ui_scr->software_version_lbl_2, _("Currentversion"));
			const lv_font_t * font = _font("Currentversion");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->software_version_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->software_version_lbl_4 != NULL && lv_obj_is_valid(ui_scr->software_version_lbl_4)) {
			lv_label_set_text(ui_scr->software_version_lbl_4, _("Youarecurrentlyusingthelatestversion"));
			const lv_font_t * font = _font("Youarecurrentlyusingthelatestversion");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->software_version_lbl_4, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->software_version_lbl_3 != NULL && lv_obj_is_valid(ui_scr->software_version_lbl_3)) {
			lv_label_set_text(ui_scr->software_version_lbl_3, _("Latestversion"));
			const lv_font_t * font = _font("Latestversion");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->software_version_lbl_3, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_RESTORE_FACTORY && guider_ui.Restore_factory) {
		lv_ui_Restore_factory * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_RESTORE_FACTORY);
		if (ui_scr->Restore_factory_lbl_3 != NULL && lv_obj_is_valid(ui_scr->Restore_factory_lbl_3)) {
			lv_label_set_text(ui_scr->Restore_factory_lbl_3, _("WarningThisoperationwilldeletealldataandcannotberecoveredPleasemakesureyouhavebackedupimportantinformation"));
			const lv_font_t * font = _font("WarningThisoperationwilldeletealldataandcannotberecoveredPleasemakesureyouhavebackedupimportantinformation");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Restore_factory_lbl_3, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->Restore_factory_btn_1_label != NULL && lv_obj_is_valid(ui_scr->Restore_factory_btn_1_label)) {
			lv_label_set_text(ui_scr->Restore_factory_btn_1_label, _("Restore"));
			const lv_font_t * font = _font("Restore");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Restore_factory_btn_1_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->Restore_factory_lbl_5 != NULL && lv_obj_is_valid(ui_scr->Restore_factory_lbl_5)) {
			lv_label_set_text(ui_scr->Restore_factory_lbl_5, _("Thisoperationisirreversiblesoproceedwithcaution"));
			const lv_font_t * font = _font("Thisoperationisirreversiblesoproceedwithcaution");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Restore_factory_lbl_5, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->Restore_factory_lbl_4 != NULL && lv_obj_is_valid(ui_scr->Restore_factory_lbl_4)) {
			lv_label_set_text(ui_scr->Restore_factory_lbl_4, _("Areyousureyouwanttorestoretofactorysettings"));
			const lv_font_t * font = _font("Areyousureyouwanttorestoretofactorysettings");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Restore_factory_lbl_4, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->Restore_factory_btn_2_label != NULL && lv_obj_is_valid(ui_scr->Restore_factory_btn_2_label)) {
			lv_label_set_text(ui_scr->Restore_factory_btn_2_label, _("Cancel"));
			const lv_font_t * font = _font("Cancel");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Restore_factory_btn_2_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->Restore_factory_btn_3_label != NULL && lv_obj_is_valid(ui_scr->Restore_factory_btn_3_label)) {
			lv_label_set_text(ui_scr->Restore_factory_btn_3_label, _("Confirm"));
			const lv_font_t * font = _font("Confirm");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Restore_factory_btn_3_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->Restore_factory_lbl_1 != NULL && lv_obj_is_valid(ui_scr->Restore_factory_lbl_1)) {
			lv_label_set_text(ui_scr->Restore_factory_lbl_1, _("Restoretofactorysettings1"));
			const lv_font_t * font = _font("Restoretofactorysettings1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Restore_factory_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_RESTORE_FACTORY_2 && guider_ui.Restore_factory_2) {
		lv_ui_Restore_factory_2 * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_RESTORE_FACTORY_2);
		if (ui_scr->Restore_factory_2_lbl_2 != NULL && lv_obj_is_valid(ui_scr->Restore_factory_2_lbl_2)) {
			lv_label_set_text(ui_scr->Restore_factory_2_lbl_2, _("Restoringfactorysettings"));
			const lv_font_t * font = _font("Restoringfactorysettings");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Restore_factory_2_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->Restore_factory_2_lbl_3 != NULL && lv_obj_is_valid(ui_scr->Restore_factory_2_lbl_3)) {
			lv_label_set_text(ui_scr->Restore_factory_2_lbl_3, _("Pleasewait"));
			const lv_font_t * font = _font("Pleasewait");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Restore_factory_2_lbl_3, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->Restore_factory_2_lbl_4 != NULL && lv_obj_is_valid(ui_scr->Restore_factory_2_lbl_4)) {
			lv_label_set_text(ui_scr->Restore_factory_2_lbl_4, _("FactoryresetcompleteDevicewillrebootshortly"));
			const lv_font_t * font = _font("FactoryresetcompleteDevicewillrebootshortly");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Restore_factory_2_lbl_4, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_ADDRESS_BOOK && guider_ui.address_book) {
		lv_ui_address_book * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_ADDRESS_BOOK);
		if (ui_scr->address_book_lbl_20 != NULL && lv_obj_is_valid(ui_scr->address_book_lbl_20)) {
			lv_label_set_text(ui_scr->address_book_lbl_20, _("Contacts"));
			const lv_font_t * font = _font("Contacts");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->address_book_lbl_20, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->address_book_btn_1_label != NULL && lv_obj_is_valid(ui_scr->address_book_btn_1_label)) {
			lv_label_set_text(ui_scr->address_book_btn_1_label, _("Addfriend"));
			const lv_font_t * font = _font("Addfriend");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->address_book_btn_1_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->address_book_lbl_1 != NULL && lv_obj_is_valid(ui_scr->address_book_lbl_1)) {
			lv_label_set_text(ui_scr->address_book_lbl_1, _(""));
			const lv_font_t * font = _font("");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->address_book_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_VIDEO_RESOLUTION && guider_ui.video_resolution) {
		lv_ui_video_resolution * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_RESOLUTION);
		if (ui_scr->video_resolution_lbl_1 != NULL && lv_obj_is_valid(ui_scr->video_resolution_lbl_1)) {
			lv_label_set_text(ui_scr->video_resolution_lbl_1, _("Videoresolution1"));
			const lv_font_t * font = _font("Videoresolution1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->video_resolution_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_AI_Q_A && guider_ui.AI_Q_A) {
		lv_ui_AI_Q_A * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_AI_Q_A);
		if (ui_scr->AI_Q_A_lbl_1 != NULL && lv_obj_is_valid(ui_scr->AI_Q_A_lbl_1)) {
			lv_label_set_text(ui_scr->AI_Q_A_lbl_1, _("AIQA1"));
			const lv_font_t * font = _font("AIQA1");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->AI_Q_A_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->AI_Q_A_btn_1_label != NULL && lv_obj_is_valid(ui_scr->AI_Q_A_btn_1_label)) {
			lv_label_set_text(ui_scr->AI_Q_A_btn_1_label, _("Pressandholdtospeak"));
			const lv_font_t * font = _font("Pressandholdtospeak");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->AI_Q_A_btn_1_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->AI_Q_A_lbl_2 != NULL && lv_obj_is_valid(ui_scr->AI_Q_A_lbl_2)) {
			lv_label_set_text(ui_scr->AI_Q_A_lbl_2, _("NetworktimeoutPleasetryagain"));
			const lv_font_t * font = _font("NetworktimeoutPleasetryagain");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->AI_Q_A_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->AI_Q_A_btn_3_label != NULL && lv_obj_is_valid(ui_scr->AI_Q_A_btn_3_label)) {
			lv_label_set_text(ui_scr->AI_Q_A_btn_3_label, _("Confirm"));
			const lv_font_t * font = _font("Confirm");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->AI_Q_A_btn_3_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
	}

	if (scr_id == GUI_SCREEN_SHUT_DOWN && guider_ui.Shut_down) {
		lv_ui_Shut_down * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SHUT_DOWN);
		if (ui_scr->Shut_down_lbl_1 != NULL && lv_obj_is_valid(ui_scr->Shut_down_lbl_1)) {
			lv_label_set_text(ui_scr->Shut_down_lbl_1, _("Poweroff"));
			const lv_font_t * font = _font("Poweroff");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Shut_down_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_AI_PAYMENT_CODE && guider_ui.AI_payment_code) {
		lv_ui_AI_payment_code * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_AI_PAYMENT_CODE);
		if (ui_scr->AI_payment_code_lbl_1 != NULL && lv_obj_is_valid(ui_scr->AI_payment_code_lbl_1)) {
			lv_label_set_text(ui_scr->AI_payment_code_lbl_1, _("Buypremiummembership"));
			const lv_font_t * font = _font("Buypremiummembership");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->AI_payment_code_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_AI_IMG_REC && guider_ui.AI_Img_Rec) {
		lv_ui_AI_Img_Rec * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_AI_IMG_REC);
		if (ui_scr->AI_Img_Rec_btn_1_label != NULL && lv_obj_is_valid(ui_scr->AI_Img_Rec_btn_1_label)) {
			lv_label_set_text(ui_scr->AI_Img_Rec_btn_1_label, _("Takeanotherphoto"));
			const lv_font_t * font = _font("Takeanotherphoto");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->AI_Img_Rec_btn_1_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->AI_Img_Rec_lbl_1 != NULL && lv_obj_is_valid(ui_scr->AI_Img_Rec_lbl_1)) {
			lv_label_set_text(ui_scr->AI_Img_Rec_lbl_1, _("Imagerecognition"));
			const lv_font_t * font = _font("Imagerecognition");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->AI_Img_Rec_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->AI_Img_Rec_lbl_2 != NULL && lv_obj_is_valid(ui_scr->AI_Img_Rec_lbl_2)) {
			lv_label_set_text(ui_scr->AI_Img_Rec_lbl_2, _("NetworktimeoutPleasetryagain"));
			const lv_font_t * font = _font("NetworktimeoutPleasetryagain");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->AI_Img_Rec_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->AI_Img_Rec_btn_3_label != NULL && lv_obj_is_valid(ui_scr->AI_Img_Rec_btn_3_label)) {
			lv_label_set_text(ui_scr->AI_Img_Rec_btn_3_label, _("Confirm"));
			const lv_font_t * font = _font("Confirm");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->AI_Img_Rec_btn_3_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
	}

	if (scr_id == GUI_SCREEN_CHAT_PAGE && guider_ui.chat_page) {
		lv_ui_chat_page * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_CHAT_PAGE);
		if (ui_scr->chat_page_lbl_1 != NULL && lv_obj_is_valid(ui_scr->chat_page_lbl_1)) {
			lv_label_set_text(ui_scr->chat_page_lbl_1, _("我的手机"));
			const lv_font_t * font = _font("我的手机");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->chat_page_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->chat_page_btn_1_label != NULL && lv_obj_is_valid(ui_scr->chat_page_btn_1_label)) {
			lv_label_set_text(ui_scr->chat_page_btn_1_label, _("Pressandholdtospeak"));
			const lv_font_t * font = _font("Pressandholdtospeak");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->chat_page_btn_1_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
		if (ui_scr->chat_page_lbl_2 != NULL && lv_obj_is_valid(ui_scr->chat_page_lbl_2)) {
			lv_label_set_text(ui_scr->chat_page_lbl_2, _("NetworktimeoutPleasetryagain"));
			const lv_font_t * font = _font("NetworktimeoutPleasetryagain");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->chat_page_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->chat_page_btn_3_label != NULL && lv_obj_is_valid(ui_scr->chat_page_btn_3_label)) {
			lv_label_set_text(ui_scr->chat_page_btn_3_label, _("Confirm"));
			const lv_font_t * font = _font("Confirm");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->chat_page_btn_3_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
	}

	if (scr_id == GUI_SCREEN_EDIT_FRIEND_INFO && guider_ui.Edit_Friend_Info) {
		lv_ui_Edit_Friend_Info * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_EDIT_FRIEND_INFO);
		if (ui_scr->Edit_Friend_Info_lbl_1 != NULL && lv_obj_is_valid(ui_scr->Edit_Friend_Info_lbl_1)) {
			lv_label_set_text(ui_scr->Edit_Friend_Info_lbl_1, _("修改好友信息"));
			const lv_font_t * font = _font("修改好友信息");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Edit_Friend_Info_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

	}

	if (scr_id == GUI_SCREEN_ADD_FRIEND && guider_ui.Add_friend) {
		lv_ui_Add_friend * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_ADD_FRIEND);
		if (ui_scr->Add_friend_lbl_1 != NULL && lv_obj_is_valid(ui_scr->Add_friend_lbl_1)) {
			lv_label_set_text(ui_scr->Add_friend_lbl_1, _("添加好友"));
			const lv_font_t * font = _font("添加好友");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Add_friend_lbl_1, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->Add_friend_lbl_2 != NULL && lv_obj_is_valid(ui_scr->Add_friend_lbl_2)) {
			lv_label_set_text(ui_scr->Add_friend_lbl_2, _("NetworktimeoutPleasetryagain"));
			const lv_font_t * font = _font("NetworktimeoutPleasetryagain");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Add_friend_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->Add_friend_btn_3_label != NULL && lv_obj_is_valid(ui_scr->Add_friend_btn_3_label)) {
			lv_label_set_text(ui_scr->Add_friend_btn_3_label, _("Confirm"));
			const lv_font_t * font = _font("Confirm");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->Add_friend_btn_3_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
	}

	if (scr_id == GUI_SCREEN_CALL && guider_ui.call) {
		lv_ui_call * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_CALL);
		if (ui_scr->call_lbl_2 != NULL && lv_obj_is_valid(ui_scr->call_lbl_2)) {
			lv_label_set_text(ui_scr->call_lbl_2, _("NetworktimeoutPleasetryagain"));
			const lv_font_t * font = _font("NetworktimeoutPleasetryagain");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->call_lbl_2, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}

		if (ui_scr->call_btn_3_label != NULL && lv_obj_is_valid(ui_scr->call_btn_3_label)) {
			lv_label_set_text(ui_scr->call_btn_3_label, _("Confirm"));
			const lv_font_t * font = _font("Confirm");
			if (font != NULL) {
				lv_obj_set_style_text_font(ui_scr->call_btn_3_label, font, LV_PART_MAIN|LV_STATE_DEFAULT);
			}
		}
	}
}

void i18n_refresh_all_texts()
{
	for (int i = 0; i < sizeof(gui_screen_ids) / sizeof(gui_screen_ids[0]); i++) {
		i18n_refresh_texts(gui_screen_ids[i]);
	}
}

#endif
