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


lv_obj_t * setup_scr_image_resolution(lv_ui *ui)
{
	lv_ui_image_resolution * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_IMAGE_RESOLUTION);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_image_resolution));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_image_resolution));
		ui->image_resolution = ui_scr;
	}

	//Write codes image_resolution
	ui_scr->image_resolution = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution, GUI_CTRL_SCR);

	//Write codes image_resolution_view_2
	ui_scr->image_resolution_view_2 = lv_obj_create(ui_scr->image_resolution);
	lv_obj_set_pos(ui_scr->image_resolution_view_2, 0, 32);
	lv_obj_set_size(ui_scr->image_resolution_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_view_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_view_2, GUI_CTRL_CONT);

	//Set style for image_resolution_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->image_resolution_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->image_resolution_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_lbl_1
	ui_scr->image_resolution_lbl_1 = lv_label_create(ui_scr->image_resolution_view_2);
	lv_label_set_long_mode(ui_scr->image_resolution_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->image_resolution_lbl_1, 88, 10);
	lv_obj_set_size(ui_scr->image_resolution_lbl_1, 383, 49);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_lbl_1, GUI_CTRL_LABEL);

	//Set style for image_resolution_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->image_resolution_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->image_resolution_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->image_resolution_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_img_12
	ui_scr->image_resolution_img_12 = lv_img_create(ui_scr->image_resolution_view_2);
	lv_img_set_src(ui_scr->image_resolution_img_12, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->image_resolution_img_12, 0, 0);
	lv_img_set_angle(ui_scr->image_resolution_img_12, 0);
	lv_img_set_zoom(ui_scr->image_resolution_img_12, 256);
	lv_obj_set_pos(ui_scr->image_resolution_img_12, 16, 8);
	lv_obj_set_size(ui_scr->image_resolution_img_12, 56, 56);
	lv_obj_add_flag(ui_scr->image_resolution_img_12, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->image_resolution_img_12, GUI_CTRL_IMG);

	//Write codes image_resolution_view_6
	ui_scr->image_resolution_view_6 = lv_obj_create(ui_scr->image_resolution);
	lv_obj_set_pos(ui_scr->image_resolution_view_6, 16, 120);
	lv_obj_set_size(ui_scr->image_resolution_view_6, 448, 288);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_view_6, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_view_6, GUI_CTRL_CONT);

	//Set style for image_resolution_view_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->image_resolution_view_6, 24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->image_resolution_view_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_view_3
	ui_scr->image_resolution_view_3 = lv_obj_create(ui_scr->image_resolution_view_6);
	lv_obj_set_pos(ui_scr->image_resolution_view_3, 16, 192);
	lv_obj_set_size(ui_scr->image_resolution_view_3, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_view_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_view_3, GUI_CTRL_CONT);

	//Set style for image_resolution_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->image_resolution_view_3, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->image_resolution_view_3, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_img_3
	ui_scr->image_resolution_img_3 = lv_img_create(ui_scr->image_resolution_view_3);
	lv_img_set_src(ui_scr->image_resolution_img_3, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->image_resolution_img_3, 0, 0);
	lv_img_set_angle(ui_scr->image_resolution_img_3, 0);
	lv_img_set_zoom(ui_scr->image_resolution_img_3, 256);
	lv_obj_set_pos(ui_scr->image_resolution_img_3, 368, 24);
	lv_obj_set_size(ui_scr->image_resolution_img_3, 32, 32);
	lv_obj_add_flag(ui_scr->image_resolution_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->image_resolution_img_3, GUI_CTRL_IMG);

	//Write codes image_resolution_lbl_2
	ui_scr->image_resolution_lbl_2 = lv_label_create(ui_scr->image_resolution_view_3);
	lv_label_set_text(ui_scr->image_resolution_lbl_2, "1080P");
	lv_label_set_long_mode(ui_scr->image_resolution_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->image_resolution_lbl_2, 18, 23);
	lv_obj_set_size(ui_scr->image_resolution_lbl_2, 102, 32);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_lbl_2, GUI_CTRL_LABEL);

	//Set style for image_resolution_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->image_resolution_lbl_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->image_resolution_lbl_2, &lv_font_simsun_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->image_resolution_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->image_resolution_lbl_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_view_4
	ui_scr->image_resolution_view_4 = lv_obj_create(ui_scr->image_resolution_view_6);
	lv_obj_set_pos(ui_scr->image_resolution_view_4, 16, 104);
	lv_obj_set_size(ui_scr->image_resolution_view_4, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_view_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_view_4, GUI_CTRL_CONT);

	//Set style for image_resolution_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->image_resolution_view_4, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->image_resolution_view_4, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_img_5
	ui_scr->image_resolution_img_5 = lv_img_create(ui_scr->image_resolution_view_4);
	lv_img_set_src(ui_scr->image_resolution_img_5, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->image_resolution_img_5, 0, 0);
	lv_img_set_angle(ui_scr->image_resolution_img_5, 0);
	lv_img_set_zoom(ui_scr->image_resolution_img_5, 256);
	lv_obj_set_pos(ui_scr->image_resolution_img_5, 368, 24);
	lv_obj_set_size(ui_scr->image_resolution_img_5, 32, 32);
	lv_obj_add_flag(ui_scr->image_resolution_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->image_resolution_img_5, GUI_CTRL_IMG);

	//Write codes image_resolution_lbl_3
	ui_scr->image_resolution_lbl_3 = lv_label_create(ui_scr->image_resolution_view_4);
	lv_label_set_text(ui_scr->image_resolution_lbl_3, "720P");
	lv_label_set_long_mode(ui_scr->image_resolution_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->image_resolution_lbl_3, 17, 23);
	lv_obj_set_size(ui_scr->image_resolution_lbl_3, 83, 32);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_lbl_3, GUI_CTRL_LABEL);

	//Set style for image_resolution_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->image_resolution_lbl_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->image_resolution_lbl_3, &lv_font_simsun_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->image_resolution_lbl_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->image_resolution_lbl_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_view_5
	ui_scr->image_resolution_view_5 = lv_obj_create(ui_scr->image_resolution_view_6);
	lv_obj_set_pos(ui_scr->image_resolution_view_5, 16, 16);
	lv_obj_set_size(ui_scr->image_resolution_view_5, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_view_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_view_5, GUI_CTRL_CONT);

	//Set style for image_resolution_view_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->image_resolution_view_5, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->image_resolution_view_5, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_img_7
	ui_scr->image_resolution_img_7 = lv_img_create(ui_scr->image_resolution_view_5);
	lv_img_set_src(ui_scr->image_resolution_img_7, gui_get_res_path(GUI_RES_SELECT_PNG));
	lv_img_set_pivot(ui_scr->image_resolution_img_7, 0, 0);
	lv_img_set_angle(ui_scr->image_resolution_img_7, 0);
	lv_img_set_zoom(ui_scr->image_resolution_img_7, 256);
	lv_obj_set_pos(ui_scr->image_resolution_img_7, 368, 24);
	lv_obj_set_size(ui_scr->image_resolution_img_7, 32, 32);
	lv_obj_add_flag(ui_scr->image_resolution_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->image_resolution_img_7, GUI_CTRL_IMG);

	//Write codes image_resolution_lbl_4
	ui_scr->image_resolution_lbl_4 = lv_label_create(ui_scr->image_resolution_view_5);
	lv_label_set_text(ui_scr->image_resolution_lbl_4, "480P");
	lv_label_set_long_mode(ui_scr->image_resolution_lbl_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->image_resolution_lbl_4, 16, 23);
	lv_obj_set_size(ui_scr->image_resolution_lbl_4, 71, 32);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_lbl_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_lbl_4, GUI_CTRL_LABEL);

	//Set style for image_resolution_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->image_resolution_lbl_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->image_resolution_lbl_4, &lv_font_simsun_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->image_resolution_lbl_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->image_resolution_lbl_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_view_1
	ui_scr->image_resolution_view_1 = lv_obj_create(ui_scr->image_resolution);
	lv_obj_set_pos(ui_scr->image_resolution_view_1, 0, 0);
	lv_obj_set_size(ui_scr->image_resolution_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_view_1, GUI_CTRL_CONT);

	//Set style for image_resolution_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->image_resolution_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_lbl_6
	ui_scr->image_resolution_lbl_6 = lv_label_create(ui_scr->image_resolution_view_1);
	lv_label_set_text(ui_scr->image_resolution_lbl_6, "80%");
	lv_label_set_long_mode(ui_scr->image_resolution_lbl_6, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->image_resolution_lbl_6, 435, 6);
	lv_obj_set_size(ui_scr->image_resolution_lbl_6, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->image_resolution_lbl_6, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->image_resolution_lbl_6, GUI_CTRL_LABEL);

	//Set style for image_resolution_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->image_resolution_lbl_6, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes image_resolution_img_1
	ui_scr->image_resolution_img_1 = lv_img_create(ui_scr->image_resolution_view_1);
	lv_img_set_src(ui_scr->image_resolution_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->image_resolution_img_1, 0, 0);
	lv_img_set_angle(ui_scr->image_resolution_img_1, 0);
	lv_img_set_zoom(ui_scr->image_resolution_img_1, 256);
	lv_obj_set_pos(ui_scr->image_resolution_img_1, 367, 0);
	lv_obj_set_size(ui_scr->image_resolution_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->image_resolution_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->image_resolution_img_1, GUI_CTRL_IMG);

	//Write codes image_resolution_img_2
	ui_scr->image_resolution_img_2 = lv_img_create(ui_scr->image_resolution_view_1);
	lv_img_set_src(ui_scr->image_resolution_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->image_resolution_img_2, 0, 0);
	lv_img_set_angle(ui_scr->image_resolution_img_2, 0);
	lv_img_set_zoom(ui_scr->image_resolution_img_2, 256);
	lv_obj_set_pos(ui_scr->image_resolution_img_2, 403, 0);
	lv_obj_set_size(ui_scr->image_resolution_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->image_resolution_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->image_resolution_img_2, GUI_CTRL_IMG);

	//Write codes image_resolution_img_11
	ui_scr->image_resolution_img_11 = lv_img_create(ui_scr->image_resolution_view_1);
	lv_img_set_src(ui_scr->image_resolution_img_11, gui_get_res_path(GUI_RES_SET_PNG));
	lv_img_set_pivot(ui_scr->image_resolution_img_11, 0, 0);
	lv_img_set_angle(ui_scr->image_resolution_img_11, 0);
	lv_img_set_zoom(ui_scr->image_resolution_img_11, 256);
	lv_obj_set_pos(ui_scr->image_resolution_img_11, 8, 0);
	lv_obj_set_size(ui_scr->image_resolution_img_11, 32, 32);
	lv_obj_add_flag(ui_scr->image_resolution_img_11, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->image_resolution_img_11, GUI_CTRL_IMG);

	lv_obj_update_layout(ui_scr->image_resolution);
	ui_scr->image_resolution_del = false;
	i18n_refresh_texts(GUI_SCREEN_IMAGE_RESOLUTION);

	//Init events for screen
	events_init_image_resolution(ui);
	return ui_scr->image_resolution;
}
void unload_scr_image_resolution(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_IMAGE_RESOLUTION);
}

#endif
