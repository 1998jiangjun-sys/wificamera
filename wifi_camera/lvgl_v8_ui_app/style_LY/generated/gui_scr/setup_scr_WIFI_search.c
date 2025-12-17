#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t * setup_scr_WIFI_search(lv_ui *ui)
{
	lv_ui_WIFI_search * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_SEARCH);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_WIFI_search));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_WIFI_search));
		ui->WIFI_search = ui_scr;
	}

	//Write codes WIFI_search
	ui_scr->WIFI_search = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_search, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_search, GUI_CTRL_SCR);

	//Set style for WIFI_search. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_grad_color(ui_scr->WIFI_search, lv_color_make(0, 0, 0), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_search_view_2
	ui_scr->WIFI_search_view_2 = lv_obj_create(ui_scr->WIFI_search);
	lv_obj_set_pos(ui_scr->WIFI_search_view_2, 0, 32);
	lv_obj_set_size(ui_scr->WIFI_search_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_search_view_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_search_view_2, GUI_CTRL_CONT);

	//Set style for WIFI_search_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->WIFI_search_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->WIFI_search_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_search_lbl_1
	ui_scr->WIFI_search_lbl_1 = lv_label_create(ui_scr->WIFI_search_view_2);
	lv_label_set_long_mode(ui_scr->WIFI_search_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->WIFI_search_lbl_1, 88, 10);
	lv_obj_set_size(ui_scr->WIFI_search_lbl_1, 386, 49);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_search_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_search_lbl_1, GUI_CTRL_LABEL);

	//Set style for WIFI_search_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_align(ui_scr->WIFI_search_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_search_img_3
	ui_scr->WIFI_search_img_3 = lv_img_create(ui_scr->WIFI_search_view_2);
	lv_img_set_src(ui_scr->WIFI_search_img_3, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->WIFI_search_img_3, 0, 0);
	lv_img_set_angle(ui_scr->WIFI_search_img_3, 0);
	lv_img_set_zoom(ui_scr->WIFI_search_img_3, 256);
	lv_obj_set_pos(ui_scr->WIFI_search_img_3, 16, 8);
	lv_obj_set_size(ui_scr->WIFI_search_img_3, 56, 56);
	lv_obj_add_flag(ui_scr->WIFI_search_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->WIFI_search_img_3, GUI_CTRL_IMG);

	//Write codes WIFI_search_view_3
	ui_scr->WIFI_search_view_3 = lv_obj_create(ui_scr->WIFI_search);
	lv_obj_set_pos(ui_scr->WIFI_search_view_3, 16, 120);
	lv_obj_set_size(ui_scr->WIFI_search_view_3, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_search_view_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_search_view_3, GUI_CTRL_CONT);

	//Set style for WIFI_search_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->WIFI_search_view_3, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->WIFI_search_view_3, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui_scr->WIFI_search_view_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->WIFI_search_view_3, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_search_imgbtn_2
	ui_scr->WIFI_search_imgbtn_2 = lv_imgbtn_create(ui_scr->WIFI_search_view_3);
	lv_obj_set_pos(ui_scr->WIFI_search_imgbtn_2, 368, 16);
	lv_obj_set_size(ui_scr->WIFI_search_imgbtn_2, 64, 64);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_search_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_search_imgbtn_2, GUI_CTRL_IMGBTN);

	//Set style for WIFI_search_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->WIFI_search_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->WIFI_search_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for WIFI_search_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
	lv_obj_set_style_shadow_opa(ui_scr->WIFI_search_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Set style for WIFI_search_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
	lv_obj_set_style_bg_opa(ui_scr->WIFI_search_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);

	//Delete extra default style for WIFI_search_imgbtn_2
	lv_obj_remove_style(ui_scr->WIFI_search_imgbtn_2, &gui_imgbtn_main_focus_key_style, LV_PART_MAIN|LV_STATE_FOCUS_KEY);
	lv_imgbtn_set_src(ui_scr->WIFI_search_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_WLAN_REFRESH_PNG), NULL);
	lv_imgbtn_set_src(ui_scr->WIFI_search_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_WLAN_REFRESH_PNG), NULL);
	lv_imgbtn_set_src(ui_scr->WIFI_search_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_WLAN_REFRESH_PNG), NULL);
	lv_imgbtn_set_src(ui_scr->WIFI_search_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_WLAN_REFRESH_PNG), NULL);
	ui_scr->WIFI_search_imgbtn_2_label = lv_label_create(ui_scr->WIFI_search_imgbtn_2);
	lv_label_set_text(ui_scr->WIFI_search_imgbtn_2_label, "");
	lv_obj_set_style_pad_all(ui_scr->WIFI_search_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->WIFI_search_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes WIFI_search_lbl_2
	ui_scr->WIFI_search_lbl_2 = lv_label_create(ui_scr->WIFI_search_view_3);
	lv_label_set_text(ui_scr->WIFI_search_lbl_2, "WIFI");
	lv_label_set_long_mode(ui_scr->WIFI_search_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->WIFI_search_lbl_2, 16, 30);
	lv_obj_set_size(ui_scr->WIFI_search_lbl_2, 70, 36);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_search_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_search_lbl_2, GUI_CTRL_LABEL);

	//Write codes WIFI_search_view_1
	ui_scr->WIFI_search_view_1 = lv_obj_create(ui_scr->WIFI_search);
	lv_obj_set_pos(ui_scr->WIFI_search_view_1, 0, 0);
	lv_obj_set_size(ui_scr->WIFI_search_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_search_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_search_view_1, GUI_CTRL_CONT);

	//Set style for WIFI_search_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->WIFI_search_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_search_lbl_3
	ui_scr->WIFI_search_lbl_3 = lv_label_create(ui_scr->WIFI_search_view_1);
	lv_label_set_text(ui_scr->WIFI_search_lbl_3, "80%");
	lv_label_set_long_mode(ui_scr->WIFI_search_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->WIFI_search_lbl_3, 435, 6);
	lv_obj_set_size(ui_scr->WIFI_search_lbl_3, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_search_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_search_lbl_3, GUI_CTRL_LABEL);

	//Set style for WIFI_search_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->WIFI_search_lbl_3, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_search_img_1
	ui_scr->WIFI_search_img_1 = lv_img_create(ui_scr->WIFI_search_view_1);
	lv_img_set_src(ui_scr->WIFI_search_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->WIFI_search_img_1, 0, 0);
	lv_img_set_angle(ui_scr->WIFI_search_img_1, 0);
	lv_img_set_zoom(ui_scr->WIFI_search_img_1, 256);
	lv_obj_set_pos(ui_scr->WIFI_search_img_1, 367, 0);
	lv_obj_set_size(ui_scr->WIFI_search_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->WIFI_search_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->WIFI_search_img_1, GUI_CTRL_IMG);

	//Write codes WIFI_search_img_2
	ui_scr->WIFI_search_img_2 = lv_img_create(ui_scr->WIFI_search_view_1);
	lv_img_set_src(ui_scr->WIFI_search_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->WIFI_search_img_2, 0, 0);
	lv_img_set_angle(ui_scr->WIFI_search_img_2, 0);
	lv_img_set_zoom(ui_scr->WIFI_search_img_2, 256);
	lv_obj_set_pos(ui_scr->WIFI_search_img_2, 403, 0);
	lv_obj_set_size(ui_scr->WIFI_search_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->WIFI_search_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->WIFI_search_img_2, GUI_CTRL_IMG);

	//Write codes WIFI_search_lbl_4
	ui_scr->WIFI_search_lbl_4 = lv_label_create(ui_scr->WIFI_search);
	lv_label_set_long_mode(ui_scr->WIFI_search_lbl_4, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui_scr->WIFI_search_lbl_4, 22, 280);
	lv_obj_set_size(ui_scr->WIFI_search_lbl_4, 436, 43);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_search_lbl_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_search_lbl_4, GUI_CTRL_LABEL);

	//Write codes WIFI_search_lbl_5
	ui_scr->WIFI_search_lbl_5 = lv_label_create(ui_scr->WIFI_search);
	lv_label_set_long_mode(ui_scr->WIFI_search_lbl_5, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->WIFI_search_lbl_5, 16, 256);
	lv_obj_set_size(ui_scr->WIFI_search_lbl_5, 445, 37);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_search_lbl_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_search_lbl_5, GUI_CTRL_LABEL);

	//Set style for WIFI_search_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->WIFI_search_lbl_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->WIFI_search_lbl_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	lv_obj_update_layout(ui_scr->WIFI_search);
	ui_scr->WIFI_search_del = false;
	i18n_refresh_texts(GUI_SCREEN_WIFI_SEARCH);

	//Init events for screen
	events_init_WIFI_search(ui);
	return ui_scr->WIFI_search;
}
void unload_scr_WIFI_search(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_WIFI_SEARCH);
}

#endif
