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


lv_obj_t * setup_scr_dormancy(lv_ui *ui)
{
	lv_ui_dormancy * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DORMANCY);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_dormancy));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_dormancy));
		ui->dormancy = ui_scr;
	}

	//Write codes dormancy
	ui_scr->dormancy = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy, GUI_CTRL_SCR);

	//Write codes dormancy_view_2
	ui_scr->dormancy_view_2 = lv_obj_create(ui_scr->dormancy);
	lv_obj_set_pos(ui_scr->dormancy_view_2, 0, 32);
	lv_obj_set_size(ui_scr->dormancy_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_view_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_view_2, GUI_CTRL_CONT);

	//Set style for dormancy_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->dormancy_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->dormancy_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_lbl_1
	ui_scr->dormancy_lbl_1 = lv_label_create(ui_scr->dormancy_view_2);
	lv_label_set_long_mode(ui_scr->dormancy_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->dormancy_lbl_1, 88, 10);
	lv_obj_set_size(ui_scr->dormancy_lbl_1, 388, 49);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_lbl_1, GUI_CTRL_LABEL);

	//Set style for dormancy_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->dormancy_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->dormancy_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->dormancy_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_img_10
	ui_scr->dormancy_img_10 = lv_img_create(ui_scr->dormancy_view_2);
	lv_img_set_src(ui_scr->dormancy_img_10, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->dormancy_img_10, 0, 0);
	lv_img_set_angle(ui_scr->dormancy_img_10, 0);
	lv_img_set_zoom(ui_scr->dormancy_img_10, 256);
	lv_obj_set_pos(ui_scr->dormancy_img_10, 16, 8);
	lv_obj_set_size(ui_scr->dormancy_img_10, 56, 56);
	lv_obj_add_flag(ui_scr->dormancy_img_10, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->dormancy_img_10, GUI_CTRL_IMG);

	//Write codes dormancy_view_3
	ui_scr->dormancy_view_3 = lv_obj_create(ui_scr->dormancy);
	lv_obj_set_pos(ui_scr->dormancy_view_3, 16, 120);
	lv_obj_set_size(ui_scr->dormancy_view_3, 448, 288);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_view_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_view_3, GUI_CTRL_CONT);

	//Set style for dormancy_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->dormancy_view_3, 24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->dormancy_view_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_view_6
	ui_scr->dormancy_view_6 = lv_obj_create(ui_scr->dormancy_view_3);
	lv_obj_set_pos(ui_scr->dormancy_view_6, 16, 192);
	lv_obj_set_size(ui_scr->dormancy_view_6, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_view_6, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_view_6, GUI_CTRL_CONT);

	//Set style for dormancy_view_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->dormancy_view_6, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->dormancy_view_6, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_img_7
	ui_scr->dormancy_img_7 = lv_img_create(ui_scr->dormancy_view_6);
	lv_img_set_src(ui_scr->dormancy_img_7, gui_get_res_path(GUI_RES_SELECT_PNG));
	lv_img_set_pivot(ui_scr->dormancy_img_7, 0, 0);
	lv_img_set_angle(ui_scr->dormancy_img_7, 0);
	lv_img_set_zoom(ui_scr->dormancy_img_7, 256);
	lv_obj_set_pos(ui_scr->dormancy_img_7, 368, 24);
	lv_obj_set_size(ui_scr->dormancy_img_7, 32, 32);
	lv_obj_add_flag(ui_scr->dormancy_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->dormancy_img_7, GUI_CTRL_IMG);

	//Write codes dormancy_lbl_4
	ui_scr->dormancy_lbl_4 = lv_label_create(ui_scr->dormancy_view_6);
	lv_label_set_long_mode(ui_scr->dormancy_lbl_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->dormancy_lbl_4, 80, 23);
	lv_obj_set_size(ui_scr->dormancy_lbl_4, 280, 32);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_lbl_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_lbl_4, GUI_CTRL_LABEL);

	//Set style for dormancy_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->dormancy_lbl_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->dormancy_lbl_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->dormancy_lbl_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_img_8
	ui_scr->dormancy_img_8 = lv_img_create(ui_scr->dormancy_view_6);
	lv_img_set_src(ui_scr->dormancy_img_8, gui_get_res_path(GUI_RES_SET_SCREEN_W_PNG));
	lv_img_set_pivot(ui_scr->dormancy_img_8, 0, 0);
	lv_img_set_angle(ui_scr->dormancy_img_8, 0);
	lv_img_set_zoom(ui_scr->dormancy_img_8, 256);
	lv_obj_set_pos(ui_scr->dormancy_img_8, 16, 16);
	lv_obj_set_size(ui_scr->dormancy_img_8, 48, 48);
	lv_obj_add_flag(ui_scr->dormancy_img_8, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->dormancy_img_8, GUI_CTRL_IMG);

	//Write codes dormancy_view_5
	ui_scr->dormancy_view_5 = lv_obj_create(ui_scr->dormancy_view_3);
	lv_obj_set_pos(ui_scr->dormancy_view_5, 16, 104);
	lv_obj_set_size(ui_scr->dormancy_view_5, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_view_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_view_5, GUI_CTRL_CONT);

	//Set style for dormancy_view_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->dormancy_view_5, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->dormancy_view_5, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_img_5
	ui_scr->dormancy_img_5 = lv_img_create(ui_scr->dormancy_view_5);
	lv_img_set_src(ui_scr->dormancy_img_5, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->dormancy_img_5, 0, 0);
	lv_img_set_angle(ui_scr->dormancy_img_5, 0);
	lv_img_set_zoom(ui_scr->dormancy_img_5, 256);
	lv_obj_set_pos(ui_scr->dormancy_img_5, 368, 24);
	lv_obj_set_size(ui_scr->dormancy_img_5, 32, 32);
	lv_obj_add_flag(ui_scr->dormancy_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->dormancy_img_5, GUI_CTRL_IMG);

	//Write codes dormancy_lbl_3
	ui_scr->dormancy_lbl_3 = lv_label_create(ui_scr->dormancy_view_5);
	lv_label_set_long_mode(ui_scr->dormancy_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->dormancy_lbl_3, 80, 22);
	lv_obj_set_size(ui_scr->dormancy_lbl_3, 206, 32);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_lbl_3, GUI_CTRL_LABEL);

	//Set style for dormancy_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->dormancy_lbl_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->dormancy_lbl_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->dormancy_lbl_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_img_6
	ui_scr->dormancy_img_6 = lv_img_create(ui_scr->dormancy_view_5);
	lv_img_set_src(ui_scr->dormancy_img_6, gui_get_res_path(GUI_RES_SET_SCREEN_W_PNG));
	lv_img_set_pivot(ui_scr->dormancy_img_6, 0, 0);
	lv_img_set_angle(ui_scr->dormancy_img_6, 0);
	lv_img_set_zoom(ui_scr->dormancy_img_6, 256);
	lv_obj_set_pos(ui_scr->dormancy_img_6, 16, 16);
	lv_obj_set_size(ui_scr->dormancy_img_6, 48, 48);
	lv_obj_add_flag(ui_scr->dormancy_img_6, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->dormancy_img_6, GUI_CTRL_IMG);

	//Write codes dormancy_view_4
	ui_scr->dormancy_view_4 = lv_obj_create(ui_scr->dormancy_view_3);
	lv_obj_set_pos(ui_scr->dormancy_view_4, 16, 14);
	lv_obj_set_size(ui_scr->dormancy_view_4, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_view_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_view_4, GUI_CTRL_CONT);

	//Set style for dormancy_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->dormancy_view_4, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->dormancy_view_4, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_img_4
	ui_scr->dormancy_img_4 = lv_img_create(ui_scr->dormancy_view_4);
	lv_img_set_src(ui_scr->dormancy_img_4, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->dormancy_img_4, 0, 0);
	lv_img_set_angle(ui_scr->dormancy_img_4, 0);
	lv_img_set_zoom(ui_scr->dormancy_img_4, 256);
	lv_obj_set_pos(ui_scr->dormancy_img_4, 368, 24);
	lv_obj_set_size(ui_scr->dormancy_img_4, 32, 32);
	lv_obj_add_flag(ui_scr->dormancy_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->dormancy_img_4, GUI_CTRL_IMG);

	//Write codes dormancy_lbl_2
	ui_scr->dormancy_lbl_2 = lv_label_create(ui_scr->dormancy_view_4);
	lv_label_set_long_mode(ui_scr->dormancy_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->dormancy_lbl_2, 80, 22);
	lv_obj_set_size(ui_scr->dormancy_lbl_2, 150, 32);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_lbl_2, GUI_CTRL_LABEL);

	//Set style for dormancy_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->dormancy_lbl_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->dormancy_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->dormancy_lbl_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_img_3
	ui_scr->dormancy_img_3 = lv_img_create(ui_scr->dormancy_view_4);
	lv_img_set_src(ui_scr->dormancy_img_3, gui_get_res_path(GUI_RES_SET_SCREEN_W_PNG));
	lv_img_set_pivot(ui_scr->dormancy_img_3, 0, 0);
	lv_img_set_angle(ui_scr->dormancy_img_3, 0);
	lv_img_set_zoom(ui_scr->dormancy_img_3, 256);
	lv_obj_set_pos(ui_scr->dormancy_img_3, 16, 16);
	lv_obj_set_size(ui_scr->dormancy_img_3, 48, 48);
	lv_obj_add_flag(ui_scr->dormancy_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->dormancy_img_3, GUI_CTRL_IMG);

	//Write codes dormancy_view_1
	ui_scr->dormancy_view_1 = lv_obj_create(ui_scr->dormancy);
	lv_obj_set_pos(ui_scr->dormancy_view_1, 0, 0);
	lv_obj_set_size(ui_scr->dormancy_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_view_1, GUI_CTRL_CONT);

	//Set style for dormancy_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->dormancy_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_lbl_5
	ui_scr->dormancy_lbl_5 = lv_label_create(ui_scr->dormancy_view_1);
	lv_label_set_text(ui_scr->dormancy_lbl_5, "80%");
	lv_label_set_long_mode(ui_scr->dormancy_lbl_5, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->dormancy_lbl_5, 435, 6);
	lv_obj_set_size(ui_scr->dormancy_lbl_5, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->dormancy_lbl_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->dormancy_lbl_5, GUI_CTRL_LABEL);

	//Set style for dormancy_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->dormancy_lbl_5, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes dormancy_img_1
	ui_scr->dormancy_img_1 = lv_img_create(ui_scr->dormancy_view_1);
	lv_img_set_src(ui_scr->dormancy_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->dormancy_img_1, 0, 0);
	lv_img_set_angle(ui_scr->dormancy_img_1, 0);
	lv_img_set_zoom(ui_scr->dormancy_img_1, 256);
	lv_obj_set_pos(ui_scr->dormancy_img_1, 367, 0);
	lv_obj_set_size(ui_scr->dormancy_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->dormancy_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->dormancy_img_1, GUI_CTRL_IMG);

	//Write codes dormancy_img_2
	ui_scr->dormancy_img_2 = lv_img_create(ui_scr->dormancy_view_1);
	lv_img_set_src(ui_scr->dormancy_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->dormancy_img_2, 0, 0);
	lv_img_set_angle(ui_scr->dormancy_img_2, 0);
	lv_img_set_zoom(ui_scr->dormancy_img_2, 256);
	lv_obj_set_pos(ui_scr->dormancy_img_2, 403, 0);
	lv_obj_set_size(ui_scr->dormancy_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->dormancy_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->dormancy_img_2, GUI_CTRL_IMG);

	//Write codes dormancy_img_9
	ui_scr->dormancy_img_9 = lv_img_create(ui_scr->dormancy_view_1);
	lv_img_set_src(ui_scr->dormancy_img_9, gui_get_res_path(GUI_RES_SET_PNG));
	lv_img_set_pivot(ui_scr->dormancy_img_9, 0, 0);
	lv_img_set_angle(ui_scr->dormancy_img_9, 0);
	lv_img_set_zoom(ui_scr->dormancy_img_9, 256);
	lv_obj_set_pos(ui_scr->dormancy_img_9, 8, 0);
	lv_obj_set_size(ui_scr->dormancy_img_9, 32, 32);
	lv_obj_add_flag(ui_scr->dormancy_img_9, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->dormancy_img_9, GUI_CTRL_IMG);

	lv_obj_update_layout(ui_scr->dormancy);
	ui_scr->dormancy_del = false;
	i18n_refresh_texts(GUI_SCREEN_DORMANCY);

	//Init events for screen
	events_init_dormancy(ui);
	return ui_scr->dormancy;
}
void unload_scr_dormancy(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_DORMANCY);
}

#endif
