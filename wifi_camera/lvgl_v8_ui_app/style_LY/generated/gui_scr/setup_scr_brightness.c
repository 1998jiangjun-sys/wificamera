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


lv_obj_t * setup_scr_brightness(lv_ui *ui)
{
	lv_ui_brightness * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_BRIGHTNESS);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_brightness));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_brightness));
		ui->brightness = ui_scr;
	}

	//Write codes brightness
	ui_scr->brightness = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->brightness, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->brightness, GUI_CTRL_SCR);

	//Write codes brightness_view_2
	ui_scr->brightness_view_2 = lv_obj_create(ui_scr->brightness);
	lv_obj_set_pos(ui_scr->brightness_view_2, 0, 32);
	lv_obj_set_size(ui_scr->brightness_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->brightness_view_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->brightness_view_2, GUI_CTRL_CONT);

	//Set style for brightness_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->brightness_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->brightness_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes brightness_lbl_2
	ui_scr->brightness_lbl_2 = lv_label_create(ui_scr->brightness_view_2);
	lv_label_set_long_mode(ui_scr->brightness_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->brightness_lbl_2, 88, 10);
	lv_obj_set_size(ui_scr->brightness_lbl_2, 389, 49);
	lv_obj_set_scrollbar_mode(ui_scr->brightness_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->brightness_lbl_2, GUI_CTRL_LABEL);

	//Set style for brightness_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->brightness_lbl_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->brightness_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->brightness_lbl_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes brightness_img_6
	ui_scr->brightness_img_6 = lv_img_create(ui_scr->brightness_view_2);
	lv_img_set_src(ui_scr->brightness_img_6, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->brightness_img_6, 0, 0);
	lv_img_set_angle(ui_scr->brightness_img_6, 0);
	lv_img_set_zoom(ui_scr->brightness_img_6, 256);
	lv_obj_set_pos(ui_scr->brightness_img_6, 16, 8);
	lv_obj_set_size(ui_scr->brightness_img_6, 56, 56);
	lv_obj_add_flag(ui_scr->brightness_img_6, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->brightness_img_6, GUI_CTRL_IMG);

	//Write codes brightness_view_3
	ui_scr->brightness_view_3 = lv_obj_create(ui_scr->brightness);
	lv_obj_set_pos(ui_scr->brightness_view_3, 16, 276);
	lv_obj_set_size(ui_scr->brightness_view_3, 448, 88);
	lv_obj_set_scrollbar_mode(ui_scr->brightness_view_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->brightness_view_3, GUI_CTRL_CONT);

	//Set style for brightness_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->brightness_view_3, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->brightness_view_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes brightness_lbl_1
	ui_scr->brightness_lbl_1 = lv_label_create(ui_scr->brightness_view_3);
	lv_label_set_text(ui_scr->brightness_lbl_1, "");
	lv_label_set_long_mode(ui_scr->brightness_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->brightness_lbl_1, 8, 8);
	lv_obj_set_size(ui_scr->brightness_lbl_1, 432, 72);
	lv_obj_set_scrollbar_mode(ui_scr->brightness_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->brightness_lbl_1, GUI_CTRL_LABEL);

	//Set style for brightness_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->brightness_lbl_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->brightness_lbl_1, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->brightness_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_scr->brightness_lbl_1, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->brightness_lbl_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->brightness_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes brightness_img_3
	ui_scr->brightness_img_3 = lv_img_create(ui_scr->brightness_view_3);
	lv_img_set_src(ui_scr->brightness_img_3, gui_get_res_path(GUI_RES_SET_BRIGHTNESS_M_PNG));
	lv_img_set_pivot(ui_scr->brightness_img_3, 0, 0);
	lv_img_set_angle(ui_scr->brightness_img_3, 0);
	lv_img_set_zoom(ui_scr->brightness_img_3, 256);
	lv_obj_set_pos(ui_scr->brightness_img_3, 32, 24);
	lv_obj_set_size(ui_scr->brightness_img_3, 40, 40);
	lv_obj_add_flag(ui_scr->brightness_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->brightness_img_3, GUI_CTRL_IMG);

	//Write codes brightness_slider_1
	ui_scr->brightness_slider_1 = lv_slider_create(ui_scr->brightness_view_3);
	lv_obj_set_pos(ui_scr->brightness_slider_1, 87, 36);
	lv_obj_set_size(ui_scr->brightness_slider_1, 280, 16);
	lv_obj_set_scrollbar_mode(ui_scr->brightness_slider_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->brightness_slider_1, GUI_CTRL_SLIDER);
	lv_slider_set_range(ui_scr->brightness_slider_1, 0, 100);
	lv_slider_set_mode(ui_scr->brightness_slider_1, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui_scr->brightness_slider_1, 50, LV_ANIM_OFF);
	lv_slider_set_left_value(ui_scr->brightness_slider_1, 0, LV_ANIM_OFF);

	//Write codes brightness_img_4
	ui_scr->brightness_img_4 = lv_img_create(ui_scr->brightness_view_3);
	lv_img_set_src(ui_scr->brightness_img_4, gui_get_res_path(GUI_RES_SET_BRIGHTNESS_B_PNG));
	lv_img_set_pivot(ui_scr->brightness_img_4, 0, 0);
	lv_img_set_angle(ui_scr->brightness_img_4, 0);
	lv_img_set_zoom(ui_scr->brightness_img_4, 256);
	lv_obj_set_pos(ui_scr->brightness_img_4, 384, 24);
	lv_obj_set_size(ui_scr->brightness_img_4, 40, 40);
	lv_obj_add_flag(ui_scr->brightness_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->brightness_img_4, GUI_CTRL_IMG);

	//Write codes brightness_view_1
	ui_scr->brightness_view_1 = lv_obj_create(ui_scr->brightness);
	lv_obj_set_pos(ui_scr->brightness_view_1, 0, 0);
	lv_obj_set_size(ui_scr->brightness_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->brightness_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->brightness_view_1, GUI_CTRL_CONT);

	//Set style for brightness_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->brightness_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes brightness_lbl_3
	ui_scr->brightness_lbl_3 = lv_label_create(ui_scr->brightness_view_1);
	lv_label_set_text(ui_scr->brightness_lbl_3, "80%");
	lv_label_set_long_mode(ui_scr->brightness_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->brightness_lbl_3, 435, 6);
	lv_obj_set_size(ui_scr->brightness_lbl_3, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->brightness_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->brightness_lbl_3, GUI_CTRL_LABEL);

	//Set style for brightness_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->brightness_lbl_3, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes brightness_img_1
	ui_scr->brightness_img_1 = lv_img_create(ui_scr->brightness_view_1);
	lv_img_set_src(ui_scr->brightness_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->brightness_img_1, 0, 0);
	lv_img_set_angle(ui_scr->brightness_img_1, 0);
	lv_img_set_zoom(ui_scr->brightness_img_1, 256);
	lv_obj_set_pos(ui_scr->brightness_img_1, 367, 0);
	lv_obj_set_size(ui_scr->brightness_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->brightness_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->brightness_img_1, GUI_CTRL_IMG);

	//Write codes brightness_img_2
	ui_scr->brightness_img_2 = lv_img_create(ui_scr->brightness_view_1);
	lv_img_set_src(ui_scr->brightness_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->brightness_img_2, 0, 0);
	lv_img_set_angle(ui_scr->brightness_img_2, 0);
	lv_img_set_zoom(ui_scr->brightness_img_2, 256);
	lv_obj_set_pos(ui_scr->brightness_img_2, 403, 0);
	lv_obj_set_size(ui_scr->brightness_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->brightness_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->brightness_img_2, GUI_CTRL_IMG);

	//Write codes brightness_img_5
	ui_scr->brightness_img_5 = lv_img_create(ui_scr->brightness_view_1);
	lv_img_set_src(ui_scr->brightness_img_5, gui_get_res_path(GUI_RES_SET_PNG));
	lv_img_set_pivot(ui_scr->brightness_img_5, 0, 0);
	lv_img_set_angle(ui_scr->brightness_img_5, 0);
	lv_img_set_zoom(ui_scr->brightness_img_5, 256);
	lv_obj_set_pos(ui_scr->brightness_img_5, 8, 0);
	lv_obj_set_size(ui_scr->brightness_img_5, 32, 32);
	lv_obj_add_flag(ui_scr->brightness_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->brightness_img_5, GUI_CTRL_IMG);

	lv_obj_update_layout(ui_scr->brightness);
	ui_scr->brightness_del = false;
	i18n_refresh_texts(GUI_SCREEN_BRIGHTNESS);

	//Init events for screen
	events_init_brightness(ui);
	return ui_scr->brightness;
}
void unload_scr_brightness(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_BRIGHTNESS);
}

#endif
