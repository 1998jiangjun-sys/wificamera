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


lv_obj_t * setup_scr_Language_Selection(lv_ui *ui)
{
	lv_ui_Language_Selection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LANGUAGE_SELECTION);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_Language_Selection));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_Language_Selection));
		ui->Language_Selection = ui_scr;
	}

	//Write codes Language_Selection
	ui_scr->Language_Selection = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->Language_Selection, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->Language_Selection, GUI_CTRL_SCR);

	//Set style for Language_Selection. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->Language_Selection, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_1
	ui_scr->Language_Selection_img_1 = lv_img_create(ui_scr->Language_Selection);
	lv_img_set_src(ui_scr->Language_Selection_img_1, gui_get_res_path(GUI_RES_IMAGE_4215637_0_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_1, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_1, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_1, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_1, 1, 1);
	lv_obj_set_size(ui_scr->Language_Selection_img_1, 480, 640);
	lv_obj_clear_flag(ui_scr->Language_Selection_img_1, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_flag(ui_scr->Language_Selection_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_1, GUI_CTRL_IMG);

	//Set style for Language_Selection_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->Language_Selection_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->Language_Selection_img_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_view_12
	ui_scr->Language_Selection_view_12 = lv_obj_create(ui_scr->Language_Selection);
	lv_obj_set_pos(ui_scr->Language_Selection_view_12, 0, 0);
	lv_obj_set_size(ui_scr->Language_Selection_view_12, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_12, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->Language_Selection_view_12, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->Language_Selection_view_12, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_12, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->Language_Selection_view_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_scr->Language_Selection_view_12, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_view_3
	ui_scr->Language_Selection_view_3 = lv_obj_create(ui_scr->Language_Selection_view_12);
	lv_obj_set_pos(ui_scr->Language_Selection_view_3, 14, 120);
	lv_obj_set_size(ui_scr->Language_Selection_view_3, 448, 420);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui_scr->Language_Selection_view_3, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->Language_Selection_view_3, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Language_Selection_view_3, 24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_3, lv_color_make(0xE3, 0xED, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_view_5
	ui_scr->Language_Selection_view_5 = lv_obj_create(ui_scr->Language_Selection_view_3);
	lv_obj_set_pos(ui_scr->Language_Selection_view_5, 16, 104);
	lv_obj_set_size(ui_scr->Language_Selection_view_5, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_view_5, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Language_Selection_view_5, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_5, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_6
	ui_scr->Language_Selection_img_6 = lv_img_create(ui_scr->Language_Selection_view_5);
	lv_img_set_src(ui_scr->Language_Selection_img_6, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_6, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_6, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_6, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_6, 368, 24);
	lv_obj_set_size(ui_scr->Language_Selection_img_6, 32, 32);
	lv_obj_add_flag(ui_scr->Language_Selection_img_6, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_6, GUI_CTRL_IMG);

	//Write codes Language_Selection_lbl_4
	ui_scr->Language_Selection_lbl_4 = lv_label_create(ui_scr->Language_Selection_view_5);
	lv_label_set_text(ui_scr->Language_Selection_lbl_4, "हिन्दी");
	lv_label_set_long_mode(ui_scr->Language_Selection_lbl_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Language_Selection_lbl_4, 80, 22);
	lv_obj_set_size(ui_scr->Language_Selection_lbl_4, 115, 33);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_lbl_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_lbl_4, GUI_CTRL_LABEL);

	//Set style for Language_Selection_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Language_Selection_lbl_4, &lv_font_mangal_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->Language_Selection_lbl_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_7
	ui_scr->Language_Selection_img_7 = lv_img_create(ui_scr->Language_Selection_view_5);
	lv_img_set_src(ui_scr->Language_Selection_img_7, gui_get_res_path(GUI_RES_HINDI_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_7, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_7, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_7, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_7, 16, 17);
	lv_obj_set_size(ui_scr->Language_Selection_img_7, 48, 48);
	lv_obj_add_flag(ui_scr->Language_Selection_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_7, GUI_CTRL_IMG);

	//Write codes Language_Selection_view_4
	ui_scr->Language_Selection_view_4 = lv_obj_create(ui_scr->Language_Selection_view_3);
	lv_obj_set_pos(ui_scr->Language_Selection_view_4, 16, 16);
	lv_obj_set_size(ui_scr->Language_Selection_view_4, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_view_4, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Language_Selection_view_4, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_4, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_5
	ui_scr->Language_Selection_img_5 = lv_img_create(ui_scr->Language_Selection_view_4);
	lv_img_set_src(ui_scr->Language_Selection_img_5, gui_get_res_path(GUI_RES_SELECT_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_5, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_5, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_5, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_5, 368, 24);
	lv_obj_set_size(ui_scr->Language_Selection_img_5, 32, 32);
	lv_obj_add_flag(ui_scr->Language_Selection_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_5, GUI_CTRL_IMG);

	//Write codes Language_Selection_lbl_3
	ui_scr->Language_Selection_lbl_3 = lv_label_create(ui_scr->Language_Selection_view_4);
	lv_label_set_text(ui_scr->Language_Selection_lbl_3, "English");
	lv_label_set_long_mode(ui_scr->Language_Selection_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Language_Selection_lbl_3, 80, 22);
	lv_obj_set_size(ui_scr->Language_Selection_lbl_3, 115, 33);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_lbl_3, GUI_CTRL_LABEL);

	//Set style for Language_Selection_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Language_Selection_lbl_3, &lv_font_simsun_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->Language_Selection_lbl_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_4
	ui_scr->Language_Selection_img_4 = lv_img_create(ui_scr->Language_Selection_view_4);
	lv_img_set_src(ui_scr->Language_Selection_img_4, gui_get_res_path(GUI_RES_ENGLISH_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_4, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_4, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_4, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_4, 16, 17);
	lv_obj_set_size(ui_scr->Language_Selection_img_4, 48, 48);
	lv_obj_add_flag(ui_scr->Language_Selection_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_4, GUI_CTRL_IMG);

	//Write codes Language_Selection_view_6
	ui_scr->Language_Selection_view_6 = lv_obj_create(ui_scr->Language_Selection_view_3);
	lv_obj_set_pos(ui_scr->Language_Selection_view_6, 16, 192);
	lv_obj_set_size(ui_scr->Language_Selection_view_6, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_6, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_view_6, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Language_Selection_view_6, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_6, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_8
	ui_scr->Language_Selection_img_8 = lv_img_create(ui_scr->Language_Selection_view_6);
	lv_img_set_src(ui_scr->Language_Selection_img_8, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_8, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_8, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_8, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_8, 368, 24);
	lv_obj_set_size(ui_scr->Language_Selection_img_8, 32, 32);
	lv_obj_add_flag(ui_scr->Language_Selection_img_8, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_8, GUI_CTRL_IMG);

	//Write codes Language_Selection_lbl_5
	ui_scr->Language_Selection_lbl_5 = lv_label_create(ui_scr->Language_Selection_view_6);
	lv_label_set_text(ui_scr->Language_Selection_lbl_5, "français");
	lv_label_set_long_mode(ui_scr->Language_Selection_lbl_5, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Language_Selection_lbl_5, 80, 22);
	lv_obj_set_size(ui_scr->Language_Selection_lbl_5, 115, 33);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_lbl_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_lbl_5, GUI_CTRL_LABEL);

	//Set style for Language_Selection_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Language_Selection_lbl_5, &lv_font_simsun_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->Language_Selection_lbl_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_9
	ui_scr->Language_Selection_img_9 = lv_img_create(ui_scr->Language_Selection_view_6);
	lv_img_set_src(ui_scr->Language_Selection_img_9, gui_get_res_path(GUI_RES_FRENCH_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_9, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_9, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_9, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_9, 16, 17);
	lv_obj_set_size(ui_scr->Language_Selection_img_9, 48, 48);
	lv_obj_add_flag(ui_scr->Language_Selection_img_9, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_9, GUI_CTRL_IMG);

	//Write codes Language_Selection_view_7
	ui_scr->Language_Selection_view_7 = lv_obj_create(ui_scr->Language_Selection_view_3);
	lv_obj_set_pos(ui_scr->Language_Selection_view_7, 16, 280);
	lv_obj_set_size(ui_scr->Language_Selection_view_7, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_7, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_view_7, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Language_Selection_view_7, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_7, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_10
	ui_scr->Language_Selection_img_10 = lv_img_create(ui_scr->Language_Selection_view_7);
	lv_img_set_src(ui_scr->Language_Selection_img_10, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_10, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_10, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_10, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_10, 368, 24);
	lv_obj_set_size(ui_scr->Language_Selection_img_10, 32, 32);
	lv_obj_add_flag(ui_scr->Language_Selection_img_10, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_10, GUI_CTRL_IMG);

	//Write codes Language_Selection_lbl_6
	ui_scr->Language_Selection_lbl_6 = lv_label_create(ui_scr->Language_Selection_view_7);
	lv_label_set_text(ui_scr->Language_Selection_lbl_6, "português");
	lv_label_set_long_mode(ui_scr->Language_Selection_lbl_6, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Language_Selection_lbl_6, 80, 22);
	lv_obj_set_size(ui_scr->Language_Selection_lbl_6, 126, 33);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_lbl_6, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_lbl_6, GUI_CTRL_LABEL);

	//Set style for Language_Selection_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Language_Selection_lbl_6, &lv_font_simsun_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->Language_Selection_lbl_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_11
	ui_scr->Language_Selection_img_11 = lv_img_create(ui_scr->Language_Selection_view_7);
	lv_img_set_src(ui_scr->Language_Selection_img_11, gui_get_res_path(GUI_RES_PORTUGUESE_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_11, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_11, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_11, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_11, 16, 17);
	lv_obj_set_size(ui_scr->Language_Selection_img_11, 48, 48);
	lv_obj_add_flag(ui_scr->Language_Selection_img_11, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_11, GUI_CTRL_IMG);

	//Write codes Language_Selection_view_8
	ui_scr->Language_Selection_view_8 = lv_obj_create(ui_scr->Language_Selection_view_3);
	lv_obj_set_pos(ui_scr->Language_Selection_view_8, 16, 368);
	lv_obj_set_size(ui_scr->Language_Selection_view_8, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_8, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_view_8, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Language_Selection_view_8, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_8, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_12
	ui_scr->Language_Selection_img_12 = lv_img_create(ui_scr->Language_Selection_view_8);
	lv_img_set_src(ui_scr->Language_Selection_img_12, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_12, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_12, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_12, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_12, 368, 24);
	lv_obj_set_size(ui_scr->Language_Selection_img_12, 32, 32);
	lv_obj_add_flag(ui_scr->Language_Selection_img_12, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_12, GUI_CTRL_IMG);

	//Write codes Language_Selection_lbl_7
	ui_scr->Language_Selection_lbl_7 = lv_label_create(ui_scr->Language_Selection_view_8);
	lv_label_set_text(ui_scr->Language_Selection_lbl_7, "español");
	lv_label_set_long_mode(ui_scr->Language_Selection_lbl_7, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Language_Selection_lbl_7, 80, 22);
	lv_obj_set_size(ui_scr->Language_Selection_lbl_7, 115, 33);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_lbl_7, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_lbl_7, GUI_CTRL_LABEL);

	//Set style for Language_Selection_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Language_Selection_lbl_7, &lv_font_simsun_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->Language_Selection_lbl_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_13
	ui_scr->Language_Selection_img_13 = lv_img_create(ui_scr->Language_Selection_view_8);
	lv_img_set_src(ui_scr->Language_Selection_img_13, gui_get_res_path(GUI_RES_SPAIN_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_13, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_13, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_13, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_13, 16, 17);
	lv_obj_set_size(ui_scr->Language_Selection_img_13, 48, 48);
	lv_obj_add_flag(ui_scr->Language_Selection_img_13, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_13, GUI_CTRL_IMG);

	//Write codes Language_Selection_view_9
	ui_scr->Language_Selection_view_9 = lv_obj_create(ui_scr->Language_Selection_view_3);
	lv_obj_set_pos(ui_scr->Language_Selection_view_9, 16, 456);
	lv_obj_set_size(ui_scr->Language_Selection_view_9, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_9, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_view_9, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Language_Selection_view_9, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_9, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_14
	ui_scr->Language_Selection_img_14 = lv_img_create(ui_scr->Language_Selection_view_9);
	lv_img_set_src(ui_scr->Language_Selection_img_14, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_14, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_14, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_14, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_14, 368, 24);
	lv_obj_set_size(ui_scr->Language_Selection_img_14, 32, 32);
	lv_obj_add_flag(ui_scr->Language_Selection_img_14, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_14, GUI_CTRL_IMG);

	//Write codes Language_Selection_lbl_8
	ui_scr->Language_Selection_lbl_8 = lv_label_create(ui_scr->Language_Selection_view_9);
	lv_label_set_text(ui_scr->Language_Selection_lbl_8, "русский");
	lv_label_set_long_mode(ui_scr->Language_Selection_lbl_8, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Language_Selection_lbl_8, 75, 22);
	lv_obj_set_size(ui_scr->Language_Selection_lbl_8, 181, 33);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_lbl_8, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_lbl_8, GUI_CTRL_LABEL);

	//Set style for Language_Selection_lbl_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Language_Selection_lbl_8, &lv_font_simsun_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->Language_Selection_lbl_8, -13, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->Language_Selection_lbl_8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_15
	ui_scr->Language_Selection_img_15 = lv_img_create(ui_scr->Language_Selection_view_9);
	lv_img_set_src(ui_scr->Language_Selection_img_15, gui_get_res_path(GUI_RES_RUSSIA_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_15, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_15, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_15, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_15, 16, 17);
	lv_obj_set_size(ui_scr->Language_Selection_img_15, 48, 48);
	lv_obj_add_flag(ui_scr->Language_Selection_img_15, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_15, GUI_CTRL_IMG);

	//Write codes Language_Selection_view_10
	ui_scr->Language_Selection_view_10 = lv_obj_create(ui_scr->Language_Selection_view_3);
	lv_obj_set_pos(ui_scr->Language_Selection_view_10, 16, 544);
	lv_obj_set_size(ui_scr->Language_Selection_view_10, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_10, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_view_10, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Language_Selection_view_10, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_10, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_16
	ui_scr->Language_Selection_img_16 = lv_img_create(ui_scr->Language_Selection_view_10);
	lv_img_set_src(ui_scr->Language_Selection_img_16, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_16, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_16, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_16, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_16, 368, 24);
	lv_obj_set_size(ui_scr->Language_Selection_img_16, 32, 32);
	lv_obj_add_flag(ui_scr->Language_Selection_img_16, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_16, GUI_CTRL_IMG);

	//Write codes Language_Selection_lbl_9
	ui_scr->Language_Selection_lbl_9 = lv_label_create(ui_scr->Language_Selection_view_10);
	lv_label_set_text(ui_scr->Language_Selection_lbl_9, "العربية");
	lv_label_set_long_mode(ui_scr->Language_Selection_lbl_9, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Language_Selection_lbl_9, 80, 22);
	lv_obj_set_size(ui_scr->Language_Selection_lbl_9, 115, 33);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_lbl_9, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_lbl_9, GUI_CTRL_LABEL);

	//Set style for Language_Selection_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Language_Selection_lbl_9, &lv_font_simpo_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->Language_Selection_lbl_9, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_17
	ui_scr->Language_Selection_img_17 = lv_img_create(ui_scr->Language_Selection_view_10);
	lv_img_set_src(ui_scr->Language_Selection_img_17, gui_get_res_path(GUI_RES_ARABIC_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_17, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_17, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_17, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_17, 16, 17);
	lv_obj_set_size(ui_scr->Language_Selection_img_17, 48, 48);
	lv_obj_add_flag(ui_scr->Language_Selection_img_17, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_17, GUI_CTRL_IMG);

	//Write codes Language_Selection_view_11
	ui_scr->Language_Selection_view_11 = lv_obj_create(ui_scr->Language_Selection_view_3);
	lv_obj_set_pos(ui_scr->Language_Selection_view_11, 16, 632);
	lv_obj_set_size(ui_scr->Language_Selection_view_11, 416, 80);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_11, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_view_11, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Language_Selection_view_11, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_11, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_18
	ui_scr->Language_Selection_img_18 = lv_img_create(ui_scr->Language_Selection_view_11);
	lv_img_set_src(ui_scr->Language_Selection_img_18, gui_get_res_path(GUI_RES_SELECT_NO_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_18, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_18, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_18, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_18, 368, 24);
	lv_obj_set_size(ui_scr->Language_Selection_img_18, 32, 32);
	lv_obj_add_flag(ui_scr->Language_Selection_img_18, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_18, GUI_CTRL_IMG);

	//Write codes Language_Selection_lbl_10
	ui_scr->Language_Selection_lbl_10 = lv_label_create(ui_scr->Language_Selection_view_11);
	lv_label_set_text(ui_scr->Language_Selection_lbl_10, "中文");
	lv_label_set_long_mode(ui_scr->Language_Selection_lbl_10, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Language_Selection_lbl_10, 80, 22);
	lv_obj_set_size(ui_scr->Language_Selection_lbl_10, 115, 33);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_lbl_10, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_lbl_10, GUI_CTRL_LABEL);

	//Set style for Language_Selection_lbl_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Language_Selection_lbl_10, &lv_font_simsun_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->Language_Selection_lbl_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_19
	ui_scr->Language_Selection_img_19 = lv_img_create(ui_scr->Language_Selection_view_11);
	lv_img_set_src(ui_scr->Language_Selection_img_19, gui_get_res_path(GUI_RES_CHINA_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_19, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_19, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_19, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_19, 16, 17);
	lv_obj_set_size(ui_scr->Language_Selection_img_19, 48, 48);
	lv_obj_add_flag(ui_scr->Language_Selection_img_19, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_19, GUI_CTRL_IMG);

	//Write codes Language_Selection_view_1
	ui_scr->Language_Selection_view_1 = lv_obj_create(ui_scr->Language_Selection);
	lv_obj_set_pos(ui_scr->Language_Selection_view_1, 0, 536);
	lv_obj_set_size(ui_scr->Language_Selection_view_1, 480, 104);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->Language_Selection_view_1, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->Language_Selection_view_1, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_view_1, lv_color_make(0x08, 0x2B, 0x8E), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui_scr->Language_Selection_view_1, lv_color_make(0x08, 0x2B, 0x8E), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->Language_Selection_view_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_btn_1
	ui_scr->Language_Selection_btn_1 = lv_btn_create(ui_scr->Language_Selection_view_1);
	lv_obj_set_pos(ui_scr->Language_Selection_btn_1, 24, 16);
	lv_obj_set_size(ui_scr->Language_Selection_btn_1, 432, 72);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_btn_1, LV_SCROLLBAR_MODE_OFF);
	lv_group_remove_obj(ui_scr->Language_Selection_btn_1);
	ui_style_set(ui_scr->Language_Selection_btn_1, GUI_CTRL_BUTTON);

	//Set style for Language_Selection_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->Language_Selection_btn_1, lv_color_make(0xB5, 0xFF, 0x66), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui_scr->Language_Selection_btn_1, lv_color_make(0x76, 0xE3, 0x44), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_scr->Language_Selection_btn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->Language_Selection_btn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->Language_Selection_btn_1_label = lv_label_create(ui_scr->Language_Selection_btn_1);
	lv_obj_set_style_pad_all(ui_scr->Language_Selection_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->Language_Selection_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes Language_Selection_view_2
	ui_scr->Language_Selection_view_2 = lv_obj_create(ui_scr->Language_Selection);
	lv_obj_set_pos(ui_scr->Language_Selection_view_2, 0, 0);
	lv_obj_set_size(ui_scr->Language_Selection_view_2, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_view_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->Language_Selection_view_2, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->Language_Selection_view_2, GUI_CTRL_CONT);

	//Set style for Language_Selection_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->Language_Selection_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_lbl_2
	ui_scr->Language_Selection_lbl_2 = lv_label_create(ui_scr->Language_Selection_view_2);
	lv_label_set_text(ui_scr->Language_Selection_lbl_2, "80%");
	lv_label_set_long_mode(ui_scr->Language_Selection_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Language_Selection_lbl_2, 436, 6);
	lv_obj_set_size(ui_scr->Language_Selection_lbl_2, 41, 22);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Language_Selection_lbl_2, GUI_CTRL_LABEL);

	//Set style for Language_Selection_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Language_Selection_lbl_2, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Language_Selection_img_2
	ui_scr->Language_Selection_img_2 = lv_img_create(ui_scr->Language_Selection_view_2);
	lv_img_set_src(ui_scr->Language_Selection_img_2, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_2, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_2, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_2, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_2, 367, 0);
	lv_obj_set_size(ui_scr->Language_Selection_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->Language_Selection_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_2, GUI_CTRL_IMG);

	//Write codes Language_Selection_img_3
	ui_scr->Language_Selection_img_3 = lv_img_create(ui_scr->Language_Selection_view_2);
	lv_img_set_src(ui_scr->Language_Selection_img_3, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->Language_Selection_img_3, 0, 0);
	lv_img_set_angle(ui_scr->Language_Selection_img_3, 0);
	lv_img_set_zoom(ui_scr->Language_Selection_img_3, 256);
	lv_obj_set_pos(ui_scr->Language_Selection_img_3, 403, 0);
	lv_obj_set_size(ui_scr->Language_Selection_img_3, 32, 32);
	lv_obj_add_flag(ui_scr->Language_Selection_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Language_Selection_img_3, GUI_CTRL_IMG);

	//Write codes Language_Selection_lbl_1
	ui_scr->Language_Selection_lbl_1 = lv_label_create(ui_scr->Language_Selection);
	lv_label_set_long_mode(ui_scr->Language_Selection_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Language_Selection_lbl_1, 0, 55);
	lv_obj_set_size(ui_scr->Language_Selection_lbl_1, 480, 42);
	lv_obj_set_scrollbar_mode(ui_scr->Language_Selection_lbl_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->Language_Selection_lbl_1, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->Language_Selection_lbl_1, GUI_CTRL_LABEL);

	lv_obj_update_layout(ui_scr->Language_Selection);
	ui_scr->Language_Selection_del = false;
	i18n_refresh_texts(GUI_SCREEN_LANGUAGE_SELECTION);

	//Init events for screen
	events_init_Language_Selection(ui);
	return ui_scr->Language_Selection;
}
void unload_scr_Language_Selection(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_LANGUAGE_SELECTION);
}

#endif
