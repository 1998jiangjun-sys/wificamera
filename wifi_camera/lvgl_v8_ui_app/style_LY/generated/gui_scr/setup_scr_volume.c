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


lv_obj_t * setup_scr_volume(lv_ui *ui)
{
	lv_ui_volume * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VOLUME);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_volume));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_volume));
		ui->volume = ui_scr;
	}

	//Write codes volume
	ui_scr->volume = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->volume, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->volume, GUI_CTRL_SCR);

	//Write codes volume_view_2
	ui_scr->volume_view_2 = lv_obj_create(ui_scr->volume);
	lv_obj_set_pos(ui_scr->volume_view_2, 0, 32);
	lv_obj_set_size(ui_scr->volume_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->volume_view_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->volume_view_2, GUI_CTRL_CONT);

	//Set style for volume_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->volume_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->volume_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes volume_lbl_1
	ui_scr->volume_lbl_1 = lv_label_create(ui_scr->volume_view_2);
	lv_label_set_long_mode(ui_scr->volume_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->volume_lbl_1, 88, 10);
	lv_obj_set_size(ui_scr->volume_lbl_1, 382, 49);
	lv_obj_set_scrollbar_mode(ui_scr->volume_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->volume_lbl_1, GUI_CTRL_LABEL);

	//Set style for volume_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->volume_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->volume_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->volume_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes volume_img_6
	ui_scr->volume_img_6 = lv_img_create(ui_scr->volume_view_2);
	lv_img_set_src(ui_scr->volume_img_6, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->volume_img_6, 0, 0);
	lv_img_set_angle(ui_scr->volume_img_6, 0);
	lv_img_set_zoom(ui_scr->volume_img_6, 256);
	lv_obj_set_pos(ui_scr->volume_img_6, 16, 8);
	lv_obj_set_size(ui_scr->volume_img_6, 56, 56);
	lv_obj_add_flag(ui_scr->volume_img_6, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->volume_img_6, GUI_CTRL_IMG);

	//Write codes volume_view_3
	ui_scr->volume_view_3 = lv_obj_create(ui_scr->volume);
	lv_obj_set_pos(ui_scr->volume_view_3, 16, 276);
	lv_obj_set_size(ui_scr->volume_view_3, 448, 88);
	lv_obj_set_scrollbar_mode(ui_scr->volume_view_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->volume_view_3, GUI_CTRL_CONT);

	//Set style for volume_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->volume_view_3, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->volume_view_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes volume_lbl_2
	ui_scr->volume_lbl_2 = lv_label_create(ui_scr->volume_view_3);
	lv_label_set_text(ui_scr->volume_lbl_2, "");
	lv_label_set_long_mode(ui_scr->volume_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->volume_lbl_2, 8, 8);
	lv_obj_set_size(ui_scr->volume_lbl_2, 432, 72);
	lv_obj_set_scrollbar_mode(ui_scr->volume_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->volume_lbl_2, GUI_CTRL_LABEL);

	//Set style for volume_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->volume_lbl_2, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->volume_lbl_2, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->volume_lbl_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_scr->volume_lbl_2, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->volume_lbl_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->volume_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes volume_img_3
	ui_scr->volume_img_3 = lv_img_create(ui_scr->volume_view_3);
	lv_img_set_src(ui_scr->volume_img_3, gui_get_res_path(GUI_RES_SET_SPEAKER_UN_1_PNG));
	lv_img_set_pivot(ui_scr->volume_img_3, 0, 0);
	lv_img_set_angle(ui_scr->volume_img_3, 0);
	lv_img_set_zoom(ui_scr->volume_img_3, 256);
	lv_obj_set_pos(ui_scr->volume_img_3, 32, 24);
	lv_obj_set_size(ui_scr->volume_img_3, 40, 40);
	lv_obj_add_flag(ui_scr->volume_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->volume_img_3, GUI_CTRL_IMG);

	//Write codes volume_slider_1
	ui_scr->volume_slider_1 = lv_slider_create(ui_scr->volume_view_3);
	lv_obj_set_pos(ui_scr->volume_slider_1, 87, 36);
	lv_obj_set_size(ui_scr->volume_slider_1, 280, 16);
	lv_obj_set_scrollbar_mode(ui_scr->volume_slider_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->volume_slider_1, GUI_CTRL_SLIDER);
	lv_slider_set_range(ui_scr->volume_slider_1, 0, 100);
	lv_slider_set_mode(ui_scr->volume_slider_1, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui_scr->volume_slider_1, 50, LV_ANIM_OFF);
	lv_slider_set_left_value(ui_scr->volume_slider_1, 0, LV_ANIM_OFF);

	//Write codes volume_img_4
	ui_scr->volume_img_4 = lv_img_create(ui_scr->volume_view_3);
	lv_img_set_src(ui_scr->volume_img_4, gui_get_res_path(GUI_RES_SET_SPEAKER_W_1_PNG));
	lv_img_set_pivot(ui_scr->volume_img_4, 0, 0);
	lv_img_set_angle(ui_scr->volume_img_4, 0);
	lv_img_set_zoom(ui_scr->volume_img_4, 256);
	lv_obj_set_pos(ui_scr->volume_img_4, 384, 24);
	lv_obj_set_size(ui_scr->volume_img_4, 40, 40);
	lv_obj_add_flag(ui_scr->volume_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->volume_img_4, GUI_CTRL_IMG);

	//Write codes volume_view_1
	ui_scr->volume_view_1 = lv_obj_create(ui_scr->volume);
	lv_obj_set_pos(ui_scr->volume_view_1, 0, 0);
	lv_obj_set_size(ui_scr->volume_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->volume_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->volume_view_1, GUI_CTRL_CONT);

	//Set style for volume_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->volume_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes volume_lbl_3
	ui_scr->volume_lbl_3 = lv_label_create(ui_scr->volume_view_1);
	lv_label_set_text(ui_scr->volume_lbl_3, "80%");
	lv_label_set_long_mode(ui_scr->volume_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->volume_lbl_3, 435, 6);
	lv_obj_set_size(ui_scr->volume_lbl_3, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->volume_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->volume_lbl_3, GUI_CTRL_LABEL);

	//Set style for volume_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->volume_lbl_3, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes volume_img_1
	ui_scr->volume_img_1 = lv_img_create(ui_scr->volume_view_1);
	lv_img_set_src(ui_scr->volume_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->volume_img_1, 0, 0);
	lv_img_set_angle(ui_scr->volume_img_1, 0);
	lv_img_set_zoom(ui_scr->volume_img_1, 256);
	lv_obj_set_pos(ui_scr->volume_img_1, 367, 0);
	lv_obj_set_size(ui_scr->volume_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->volume_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->volume_img_1, GUI_CTRL_IMG);

	//Write codes volume_img_2
	ui_scr->volume_img_2 = lv_img_create(ui_scr->volume_view_1);
	lv_img_set_src(ui_scr->volume_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->volume_img_2, 0, 0);
	lv_img_set_angle(ui_scr->volume_img_2, 0);
	lv_img_set_zoom(ui_scr->volume_img_2, 256);
	lv_obj_set_pos(ui_scr->volume_img_2, 403, 0);
	lv_obj_set_size(ui_scr->volume_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->volume_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->volume_img_2, GUI_CTRL_IMG);

	//Write codes volume_img_5
	ui_scr->volume_img_5 = lv_img_create(ui_scr->volume_view_1);
	lv_img_set_src(ui_scr->volume_img_5, gui_get_res_path(GUI_RES_SET_PNG));
	lv_img_set_pivot(ui_scr->volume_img_5, 0, 0);
	lv_img_set_angle(ui_scr->volume_img_5, 0);
	lv_img_set_zoom(ui_scr->volume_img_5, 256);
	lv_obj_set_pos(ui_scr->volume_img_5, 8, 0);
	lv_obj_set_size(ui_scr->volume_img_5, 32, 32);
	lv_obj_add_flag(ui_scr->volume_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->volume_img_5, GUI_CTRL_IMG);

	//Write codes volume_view_4
	ui_scr->volume_view_4 = lv_obj_create(ui_scr->volume);
	lv_obj_set_pos(ui_scr->volume_view_4, 167, 488);
	lv_obj_set_size(ui_scr->volume_view_4, 146, 122);
	lv_obj_set_scrollbar_mode(ui_scr->volume_view_4, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget volume_view_4
	lv_obj_add_flag(ui_scr->volume_view_4, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->volume_view_4, GUI_CTRL_CONT);

	//Set style for volume_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->volume_view_4, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->volume_view_4, 179, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes volume_lbl_4
	ui_scr->volume_lbl_4 = lv_label_create(ui_scr->volume_view_4);
	lv_label_set_long_mode(ui_scr->volume_lbl_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->volume_lbl_4, -25, 79);
	lv_obj_set_size(ui_scr->volume_lbl_4, 198, 35);
	lv_obj_set_scrollbar_mode(ui_scr->volume_lbl_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->volume_lbl_4, GUI_CTRL_LABEL);

	//Write codes volume_img_7
	ui_scr->volume_img_7 = lv_img_create(ui_scr->volume_view_4);
	lv_img_set_src(ui_scr->volume_img_7, gui_get_res_path(GUI_RES_SET_SPEAKER_UN_1_PNG));
	lv_img_set_pivot(ui_scr->volume_img_7, 0, 0);
	lv_img_set_angle(ui_scr->volume_img_7, 0);
	lv_img_set_zoom(ui_scr->volume_img_7, 256);
	lv_obj_set_pos(ui_scr->volume_img_7, 53, 24);
	lv_obj_set_size(ui_scr->volume_img_7, 40, 40);
	lv_obj_add_flag(ui_scr->volume_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->volume_img_7, GUI_CTRL_IMG);

	lv_obj_update_layout(ui_scr->volume);
	ui_scr->volume_del = false;
	i18n_refresh_texts(GUI_SCREEN_VOLUME);

	//Init events for screen
	events_init_volume(ui);
	return ui_scr->volume;
}
void unload_scr_volume(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_VOLUME);
}

#endif
