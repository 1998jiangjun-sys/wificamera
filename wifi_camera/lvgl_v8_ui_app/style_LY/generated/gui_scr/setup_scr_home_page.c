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


lv_obj_t * setup_scr_home_page(lv_ui *ui)
{
	lv_ui_home_page * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_home_page));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_home_page));
		ui->home_page = ui_scr;
	}

	//Write codes home_page
	ui_scr->home_page = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->home_page, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page, GUI_CTRL_SCR);

	//Set style for home_page. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->home_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_1
	ui_scr->home_page_img_1 = lv_img_create(ui_scr->home_page);
	lv_img_set_src(ui_scr->home_page_img_1, gui_get_res_path(GUI_RES_IMAGE_4215637_0_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_1, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_1, 0);
	lv_img_set_zoom(ui_scr->home_page_img_1, 256);
	lv_obj_set_pos(ui_scr->home_page_img_1, 0, 0);
	lv_obj_set_size(ui_scr->home_page_img_1, 480, 640);
	lv_obj_clear_flag(ui_scr->home_page_img_1, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_flag(ui_scr->home_page_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_1, GUI_CTRL_IMG);

	//Set style for home_page_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->home_page_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->home_page_img_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_digitclock_1
	ui_scr->home_page_digitclock_1 = lv_label_create(ui_scr->home_page);
	lv_label_set_text_fmt(ui_scr->home_page_digitclock_1, "%04d-%02d-%02d %02d:%02d:%02d", 2024, 06, 13, 21 % 12, 25, 50);
	lv_obj_set_style_text_align(ui_scr->home_page_digitclock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_pos(ui_scr->home_page_digitclock_1, 96, 17);
	lv_obj_set_size(ui_scr->home_page_digitclock_1, 534, 65);

	//Hidden for widget home_page_digitclock_1
	lv_obj_add_flag(ui_scr->home_page_digitclock_1, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->home_page_digitclock_1, GUI_CTRL_DIGITALCLOCK);

	//Write codes home_page_lbl_1
	ui_scr->home_page_lbl_1 = lv_label_create(ui_scr->home_page);
	lv_label_set_long_mode(ui_scr->home_page_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_1, 587, 38);
	lv_obj_set_size(ui_scr->home_page_lbl_1, 50, 50);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_1, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget home_page_lbl_1
	lv_obj_add_flag(ui_scr->home_page_lbl_1, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->home_page_lbl_1, GUI_CTRL_LABEL);

	//Set style for home_page_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->home_page_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->home_page_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->home_page_lbl_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->home_page_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_scr->home_page_lbl_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_lbl_2
	ui_scr->home_page_lbl_2 = lv_label_create(ui_scr->home_page);
	lv_label_set_long_mode(ui_scr->home_page_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_2, 10, 15);
	lv_obj_set_size(ui_scr->home_page_lbl_2, 197, 67);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_2, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget home_page_lbl_2
	lv_obj_add_flag(ui_scr->home_page_lbl_2, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->home_page_lbl_2, GUI_CTRL_LABEL);

	//Set style for home_page_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->home_page_lbl_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->home_page_lbl_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->home_page_lbl_2, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->home_page_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_scr->home_page_lbl_2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_view_9
	ui_scr->home_page_view_9 = lv_obj_create(ui_scr->home_page);
	lv_obj_set_pos(ui_scr->home_page_view_9, 0, 0);
	lv_obj_set_size(ui_scr->home_page_view_9, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_9, LV_SCROLLBAR_MODE_ON);
	lv_obj_add_flag(ui_scr->home_page_view_9, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->home_page_view_9, GUI_CTRL_CONT);

	//Set style for home_page_view_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page_view_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_view_7
	ui_scr->home_page_view_7 = lv_obj_create(ui_scr->home_page_view_9);
	lv_obj_set_pos(ui_scr->home_page_view_7, 26, 616);
	lv_obj_set_size(ui_scr->home_page_view_7, 200, 240);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_7, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->home_page_view_7, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->home_page_view_7, GUI_CTRL_CONT);

	//Set style for home_page_view_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page_view_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_12
	ui_scr->home_page_img_12 = lv_img_create(ui_scr->home_page_view_7);
	lv_img_set_src(ui_scr->home_page_img_12, gui_get_res_path(GUI_RES_HOME_AI_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_12, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_12, 0);
	lv_img_set_zoom(ui_scr->home_page_img_12, 256);
	lv_obj_set_pos(ui_scr->home_page_img_12, 0, 0);
	lv_obj_set_size(ui_scr->home_page_img_12, 200, 200);
	lv_obj_add_flag(ui_scr->home_page_img_12, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_12, GUI_CTRL_IMG);

	//Write codes home_page_lbl_9
	ui_scr->home_page_lbl_9 = lv_label_create(ui_scr->home_page_view_7);
	lv_label_set_long_mode(ui_scr->home_page_lbl_9, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_9, 0, 204);
	lv_obj_set_size(ui_scr->home_page_lbl_9, 200, 40);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_9, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_9, GUI_CTRL_LABEL);

	//Write codes home_page_view_8
	ui_scr->home_page_view_8 = lv_obj_create(ui_scr->home_page_view_9);
	lv_obj_set_pos(ui_scr->home_page_view_8, 254, 616);
	lv_obj_set_size(ui_scr->home_page_view_8, 200, 240);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_8, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->home_page_view_8, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->home_page_view_8, GUI_CTRL_CONT);

	//Set style for home_page_view_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page_view_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_13
	ui_scr->home_page_img_13 = lv_img_create(ui_scr->home_page_view_8);
	lv_img_set_src(ui_scr->home_page_img_13, gui_get_res_path(GUI_RES_HOME_SETTING_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_13, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_13, 0);
	lv_img_set_zoom(ui_scr->home_page_img_13, 256);
	lv_obj_set_pos(ui_scr->home_page_img_13, 0, 0);
	lv_obj_set_size(ui_scr->home_page_img_13, 200, 200);
	lv_obj_add_flag(ui_scr->home_page_img_13, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_13, GUI_CTRL_IMG);

	//Write codes home_page_lbl_10
	ui_scr->home_page_lbl_10 = lv_label_create(ui_scr->home_page_view_8);
	lv_label_set_long_mode(ui_scr->home_page_lbl_10, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_10, 0, 204);
	lv_obj_set_size(ui_scr->home_page_lbl_10, 200, 40);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_10, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_10, GUI_CTRL_LABEL);

	//Write codes home_page_view_5
	ui_scr->home_page_view_5 = lv_obj_create(ui_scr->home_page_view_9);
	lv_obj_set_pos(ui_scr->home_page_view_5, 26, 364);
	lv_obj_set_size(ui_scr->home_page_view_5, 200, 240);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_5, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->home_page_view_5, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->home_page_view_5, GUI_CTRL_CONT);

	//Set style for home_page_view_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page_view_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_10
	ui_scr->home_page_img_10 = lv_img_create(ui_scr->home_page_view_5);
	lv_img_set_src(ui_scr->home_page_img_10, gui_get_res_path(GUI_RES_HOME_ALBUM_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_10, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_10, 0);
	lv_img_set_zoom(ui_scr->home_page_img_10, 256);
	lv_obj_set_pos(ui_scr->home_page_img_10, 0, 0);
	lv_obj_set_size(ui_scr->home_page_img_10, 200, 200);
	lv_obj_add_flag(ui_scr->home_page_img_10, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_10, GUI_CTRL_IMG);

	//Write codes home_page_lbl_7
	ui_scr->home_page_lbl_7 = lv_label_create(ui_scr->home_page_view_5);
	lv_label_set_long_mode(ui_scr->home_page_lbl_7, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_7, 0, 204);
	lv_obj_set_size(ui_scr->home_page_lbl_7, 200, 40);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_7, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_7, GUI_CTRL_LABEL);

	//Write codes home_page_view_6
	ui_scr->home_page_view_6 = lv_obj_create(ui_scr->home_page_view_9);
	lv_obj_set_pos(ui_scr->home_page_view_6, 254, 364);
	lv_obj_set_size(ui_scr->home_page_view_6, 200, 240);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_6, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->home_page_view_6, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->home_page_view_6, GUI_CTRL_CONT);

	//Set style for home_page_view_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page_view_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_11
	ui_scr->home_page_img_11 = lv_img_create(ui_scr->home_page_view_6);
	lv_img_set_src(ui_scr->home_page_img_11, gui_get_res_path(GUI_RES_HOME_COMMUNICATION_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_11, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_11, 0);
	lv_img_set_zoom(ui_scr->home_page_img_11, 256);
	lv_obj_set_pos(ui_scr->home_page_img_11, 0, 0);
	lv_obj_set_size(ui_scr->home_page_img_11, 200, 200);
	lv_obj_add_flag(ui_scr->home_page_img_11, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_11, GUI_CTRL_IMG);

	//Write codes home_page_lbl_8
	ui_scr->home_page_lbl_8 = lv_label_create(ui_scr->home_page_view_6);
	lv_label_set_long_mode(ui_scr->home_page_lbl_8, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_8, 0, 204);
	lv_obj_set_size(ui_scr->home_page_lbl_8, 200, 40);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_8, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_8, GUI_CTRL_LABEL);

	//Write codes home_page_view_3
	ui_scr->home_page_view_3 = lv_obj_create(ui_scr->home_page_view_9);
	lv_obj_set_pos(ui_scr->home_page_view_3, 23, 112);
	lv_obj_set_size(ui_scr->home_page_view_3, 200, 240);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->home_page_view_3, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->home_page_view_3, GUI_CTRL_CONT);

	//Set style for home_page_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page_view_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_8
	ui_scr->home_page_img_8 = lv_img_create(ui_scr->home_page_view_3);
	lv_img_set_src(ui_scr->home_page_img_8, gui_get_res_path(GUI_RES_HOME_PHOTOGRAPH_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_8, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_8, 0);
	lv_img_set_zoom(ui_scr->home_page_img_8, 256);
	lv_obj_set_pos(ui_scr->home_page_img_8, 0, 0);
	lv_obj_set_size(ui_scr->home_page_img_8, 200, 200);
	lv_obj_add_flag(ui_scr->home_page_img_8, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_8, GUI_CTRL_IMG);

	//Write codes home_page_lbl_5
	ui_scr->home_page_lbl_5 = lv_label_create(ui_scr->home_page_view_3);
	lv_label_set_long_mode(ui_scr->home_page_lbl_5, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_5, 0, 204);
	lv_obj_set_size(ui_scr->home_page_lbl_5, 200, 40);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_5, GUI_CTRL_LABEL);

	//Write codes home_page_view_4
	ui_scr->home_page_view_4 = lv_obj_create(ui_scr->home_page_view_9);
	lv_obj_set_pos(ui_scr->home_page_view_4, 255, 112);
	lv_obj_set_size(ui_scr->home_page_view_4, 200, 240);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_4, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->home_page_view_4, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->home_page_view_4, GUI_CTRL_CONT);

	//Set style for home_page_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page_view_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_9
	ui_scr->home_page_img_9 = lv_img_create(ui_scr->home_page_view_4);
	lv_img_set_src(ui_scr->home_page_img_9, gui_get_res_path(GUI_RES_HOME_RECORD_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_9, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_9, 0);
	lv_img_set_zoom(ui_scr->home_page_img_9, 256);
	lv_obj_set_pos(ui_scr->home_page_img_9, 0, 0);
	lv_obj_set_size(ui_scr->home_page_img_9, 200, 200);
	lv_obj_clear_flag(ui_scr->home_page_img_9, LV_OBJ_FLAG_SCROLL_MOMENTUM);
	lv_obj_add_flag(ui_scr->home_page_img_9, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_9, GUI_CTRL_IMG);

	//Write codes home_page_lbl_6
	ui_scr->home_page_lbl_6 = lv_label_create(ui_scr->home_page_view_4);
	lv_label_set_long_mode(ui_scr->home_page_lbl_6, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_6, -15, 204);
	lv_obj_set_size(ui_scr->home_page_lbl_6, 230, 40);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_6, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_6, GUI_CTRL_LABEL);

	//Write codes home_page_view_10
	ui_scr->home_page_view_10 = lv_obj_create(ui_scr->home_page_view_9);
	lv_obj_set_pos(ui_scr->home_page_view_10, 26, 868);
	lv_obj_set_size(ui_scr->home_page_view_10, 200, 240);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_10, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_view_10, GUI_CTRL_CONT);

	//Set style for home_page_view_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page_view_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->home_page_view_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_scr->home_page_view_10, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->home_page_view_10, 128, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_14
	ui_scr->home_page_img_14 = lv_img_create(ui_scr->home_page_view_10);
	lv_img_set_src(ui_scr->home_page_img_14, gui_get_res_path(GUI_RES_HOME_PHOTOGRAPH_1_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_14, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_14, 0);
	lv_img_set_zoom(ui_scr->home_page_img_14, 256);
	lv_obj_set_pos(ui_scr->home_page_img_14, 0, 0);
	lv_obj_set_size(ui_scr->home_page_img_14, 200, 200);
	lv_obj_add_flag(ui_scr->home_page_img_14, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_14, GUI_CTRL_IMG);

	//Write codes home_page_lbl_12
	ui_scr->home_page_lbl_12 = lv_label_create(ui_scr->home_page_view_10);
	lv_label_set_text(ui_scr->home_page_lbl_12, "机器人");
	lv_label_set_long_mode(ui_scr->home_page_lbl_12, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_12, 0, 204);
	lv_obj_set_size(ui_scr->home_page_lbl_12, 200, 40);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_12, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_12, GUI_CTRL_LABEL);

	//Set style for home_page_lbl_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_outline_opa(ui_scr->home_page_lbl_12, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->home_page_lbl_12, &lv_font_simsun_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_scr->home_page_lbl_12, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_lbl_4
	ui_scr->home_page_lbl_4 = lv_label_create(ui_scr->home_page);
	lv_label_set_long_mode(ui_scr->home_page_lbl_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_4, 80, 52);
	lv_obj_set_size(ui_scr->home_page_lbl_4, 400, 47);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_4, GUI_CTRL_LABEL);

	//Set style for home_page_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_align(ui_scr->home_page_lbl_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_7
	ui_scr->home_page_img_7 = lv_img_create(ui_scr->home_page);
	lv_img_set_src(ui_scr->home_page_img_7, gui_get_res_path(GUI_RES_HOME_IMG_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_7, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_7, 0);
	lv_img_set_zoom(ui_scr->home_page_img_7, 256);
	lv_obj_set_pos(ui_scr->home_page_img_7, 24, 48);
	lv_obj_set_size(ui_scr->home_page_img_7, 48, 48);
	lv_obj_add_flag(ui_scr->home_page_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_7, GUI_CTRL_IMG);

	//Write codes home_page_view_1
	ui_scr->home_page_view_1 = lv_obj_create(ui_scr->home_page);
	lv_obj_set_pos(ui_scr->home_page_view_1, 0, 0);
	lv_obj_set_size(ui_scr->home_page_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->home_page_view_1, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->home_page_view_1, GUI_CTRL_CONT);

	//Set style for home_page_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_lbl_3
	ui_scr->home_page_lbl_3 = lv_label_create(ui_scr->home_page_view_1);
	lv_label_set_text(ui_scr->home_page_lbl_3, "80%");
	lv_label_set_long_mode(ui_scr->home_page_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_3, 436, 6);
	lv_obj_set_size(ui_scr->home_page_lbl_3, 41, 22);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_3, GUI_CTRL_LABEL);

	//Set style for home_page_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->home_page_lbl_3, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_2
	ui_scr->home_page_img_2 = lv_img_create(ui_scr->home_page_view_1);
	lv_img_set_src(ui_scr->home_page_img_2, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_2, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_2, 0);
	lv_img_set_zoom(ui_scr->home_page_img_2, 256);
	lv_obj_set_pos(ui_scr->home_page_img_2, 367, 0);
	lv_obj_set_size(ui_scr->home_page_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->home_page_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_2, GUI_CTRL_IMG);

	//Write codes home_page_img_3
	ui_scr->home_page_img_3 = lv_img_create(ui_scr->home_page_view_1);
	lv_img_set_src(ui_scr->home_page_img_3, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_3, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_3, 0);
	lv_img_set_zoom(ui_scr->home_page_img_3, 256);
	lv_obj_set_pos(ui_scr->home_page_img_3, 403, 0);
	lv_obj_set_size(ui_scr->home_page_img_3, 32, 32);
	lv_obj_add_flag(ui_scr->home_page_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_3, GUI_CTRL_IMG);

	//Write codes home_page_view_11
	ui_scr->home_page_view_11 = lv_obj_create(ui_scr->home_page);
	lv_obj_set_pos(ui_scr->home_page_view_11, 0, 0);
	lv_obj_set_size(ui_scr->home_page_view_11, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_11, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->home_page_view_11, LV_OBJ_FLAG_SCROLLABLE);

	//Hidden for widget home_page_view_11
	lv_obj_add_flag(ui_scr->home_page_view_11, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->home_page_view_11, GUI_CTRL_CONT);

	//Set style for home_page_view_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_11, 179, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->home_page_view_11, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_17
	ui_scr->home_page_img_17 = lv_img_create(ui_scr->home_page_view_11);
	lv_img_set_src(ui_scr->home_page_img_17, gui_get_res_path(GUI_RES_BG_POP_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_17, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_17, 0);
	lv_img_set_zoom(ui_scr->home_page_img_17, 256);
	lv_obj_set_pos(ui_scr->home_page_img_17, 28, 188);
	lv_obj_set_size(ui_scr->home_page_img_17, 428, 320);
	lv_obj_add_flag(ui_scr->home_page_img_17, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_17, GUI_CTRL_IMG);

	//Write codes home_page_img_18
	ui_scr->home_page_img_18 = lv_img_create(ui_scr->home_page_view_11);
	lv_img_set_src(ui_scr->home_page_img_18, gui_get_res_path(GUI_RES_IMAGE_7991533_0_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_18, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_18, 0);
	lv_img_set_zoom(ui_scr->home_page_img_18, 256);
	lv_obj_set_pos(ui_scr->home_page_img_18, 418, 181);
	lv_obj_set_size(ui_scr->home_page_img_18, 48, 48);
	lv_obj_add_flag(ui_scr->home_page_img_18, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_18, GUI_CTRL_IMG);

	//Write codes home_page_img_19
	ui_scr->home_page_img_19 = lv_img_create(ui_scr->home_page_view_11);
	lv_img_set_src(ui_scr->home_page_img_19, gui_get_res_path(GUI_RES_HOME_REMIND_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_19, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_19, 0);
	lv_img_set_zoom(ui_scr->home_page_img_19, 256);
	lv_obj_set_pos(ui_scr->home_page_img_19, 165, 128);
	lv_obj_set_size(ui_scr->home_page_img_19, 150, 150);
	lv_obj_add_flag(ui_scr->home_page_img_19, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_19, GUI_CTRL_IMG);

	//Write codes home_page_btn_3
	ui_scr->home_page_btn_3 = lv_btn_create(ui_scr->home_page_view_11);
	lv_obj_set_pos(ui_scr->home_page_btn_3, 56, 408);
	lv_obj_set_size(ui_scr->home_page_btn_3, 368, 62);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_btn_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_btn_3, GUI_CTRL_BUTTON);

	//Set style for home_page_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page_btn_3, lv_color_make(0xB5, 0xFF, 0x66), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui_scr->home_page_btn_3, lv_color_make(0x76, 0xE3, 0x44), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->home_page_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->home_page_btn_3, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->home_page_btn_3_label = lv_label_create(ui_scr->home_page_btn_3);
	lv_obj_set_style_pad_all(ui_scr->home_page_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->home_page_btn_3_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes home_page_lbl_13
	ui_scr->home_page_lbl_13 = lv_label_create(ui_scr->home_page_view_11);
	lv_label_set_long_mode(ui_scr->home_page_lbl_13, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_13, 40, 310);
	lv_obj_set_size(ui_scr->home_page_lbl_13, 402, 51);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_13, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_13, GUI_CTRL_LABEL);

	//Set style for home_page_lbl_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_color(ui_scr->home_page_lbl_13, lv_color_make(0x82, 0x4A, 0x1B), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_view_2
	ui_scr->home_page_view_2 = lv_obj_create(ui_scr->home_page);
	lv_obj_set_pos(ui_scr->home_page_view_2, 0, 0);
	lv_obj_set_size(ui_scr->home_page_view_2, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_view_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->home_page_view_2, LV_OBJ_FLAG_SCROLLABLE);

	//Hidden for widget home_page_view_2
	lv_obj_add_flag(ui_scr->home_page_view_2, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->home_page_view_2, GUI_CTRL_CONT);

	//Set style for home_page_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->home_page_view_2, 179, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->home_page_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes home_page_img_4
	ui_scr->home_page_img_4 = lv_img_create(ui_scr->home_page_view_2);
	lv_img_set_src(ui_scr->home_page_img_4, gui_get_res_path(GUI_RES_BG_POP_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_4, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_4, 0);
	lv_img_set_zoom(ui_scr->home_page_img_4, 256);
	lv_obj_set_pos(ui_scr->home_page_img_4, 28, 188);
	lv_obj_set_size(ui_scr->home_page_img_4, 428, 320);
	lv_obj_add_flag(ui_scr->home_page_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_4, GUI_CTRL_IMG);

	//Write codes home_page_img_6
	ui_scr->home_page_img_6 = lv_img_create(ui_scr->home_page_view_2);
	lv_img_set_src(ui_scr->home_page_img_6, gui_get_res_path(GUI_RES_IMAGE_7991533_0_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_6, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_6, 0);
	lv_img_set_zoom(ui_scr->home_page_img_6, 256);
	lv_obj_set_pos(ui_scr->home_page_img_6, 418, 181);
	lv_obj_set_size(ui_scr->home_page_img_6, 48, 48);
	lv_obj_add_flag(ui_scr->home_page_img_6, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_6, GUI_CTRL_IMG);

	//Write codes home_page_img_5
	ui_scr->home_page_img_5 = lv_img_create(ui_scr->home_page_view_2);
	lv_img_set_src(ui_scr->home_page_img_5, gui_get_res_path(GUI_RES_HOME_WLAN_PNG));
	lv_img_set_pivot(ui_scr->home_page_img_5, 0, 0);
	lv_img_set_angle(ui_scr->home_page_img_5, 0);
	lv_img_set_zoom(ui_scr->home_page_img_5, 256);
	lv_obj_set_pos(ui_scr->home_page_img_5, 165, 128);
	lv_obj_set_size(ui_scr->home_page_img_5, 150, 150);
	lv_obj_add_flag(ui_scr->home_page_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->home_page_img_5, GUI_CTRL_IMG);

	//Write codes home_page_btn_2
	ui_scr->home_page_btn_2 = lv_btn_create(ui_scr->home_page_view_2);
	lv_obj_set_pos(ui_scr->home_page_btn_2, 56, 408);
	lv_obj_set_size(ui_scr->home_page_btn_2, 368, 62);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_btn_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_btn_2, GUI_CTRL_BUTTON);

	//Set style for home_page_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->home_page_btn_2, lv_color_make(0xB5, 0xFF, 0x66), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui_scr->home_page_btn_2, lv_color_make(0x76, 0xE3, 0x44), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->home_page_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->home_page_btn_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->home_page_btn_2_label = lv_label_create(ui_scr->home_page_btn_2);
	lv_obj_set_style_pad_all(ui_scr->home_page_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->home_page_btn_2_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes home_page_lbl_11
	ui_scr->home_page_lbl_11 = lv_label_create(ui_scr->home_page_view_2);
	lv_label_set_long_mode(ui_scr->home_page_lbl_11, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->home_page_lbl_11, 40, 310);
	lv_obj_set_size(ui_scr->home_page_lbl_11, 402, 51);
	lv_obj_set_scrollbar_mode(ui_scr->home_page_lbl_11, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->home_page_lbl_11, GUI_CTRL_LABEL);

	//Set style for home_page_lbl_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_color(ui_scr->home_page_lbl_11, lv_color_make(0x82, 0x4A, 0x1B), LV_PART_MAIN|LV_STATE_DEFAULT);

	lv_obj_update_layout(ui_scr->home_page);
	ui_scr->home_page_del = false;
	i18n_refresh_texts(GUI_SCREEN_HOME_PAGE);

	//Init events for screen
	events_init_home_page(ui);
	return ui_scr->home_page;
}
void unload_scr_home_page(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_HOME_PAGE);
}

#endif
