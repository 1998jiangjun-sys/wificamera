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


lv_obj_t * setup_scr_Restore_factory_2(lv_ui *ui)
{
	lv_ui_Restore_factory_2 * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_RESTORE_FACTORY_2);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_Restore_factory_2));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_Restore_factory_2));
		ui->Restore_factory_2 = ui_scr;
	}

	//Write codes Restore_factory_2
	ui_scr->Restore_factory_2 = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Restore_factory_2, GUI_CTRL_SCR);

	//Set style for Restore_factory_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_border_color(ui_scr->Restore_factory_2, lv_color_make(0x33, 0x5D, 0xD3), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Restore_factory_2_view_2
	ui_scr->Restore_factory_2_view_2 = lv_obj_create(ui_scr->Restore_factory_2);
	lv_obj_set_pos(ui_scr->Restore_factory_2_view_2, 0, 32);
	lv_obj_set_size(ui_scr->Restore_factory_2_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2_view_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Restore_factory_2_view_2, GUI_CTRL_CONT);

	//Set style for Restore_factory_2_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->Restore_factory_2_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->Restore_factory_2_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Restore_factory_2_lbl_2
	ui_scr->Restore_factory_2_lbl_2 = lv_label_create(ui_scr->Restore_factory_2_view_2);
	lv_label_set_long_mode(ui_scr->Restore_factory_2_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Restore_factory_2_lbl_2, 15, 10);
	lv_obj_set_size(ui_scr->Restore_factory_2_lbl_2, 460, 49);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Restore_factory_2_lbl_2, GUI_CTRL_LABEL);

	//Set style for Restore_factory_2_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->Restore_factory_2_lbl_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->Restore_factory_2_lbl_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->Restore_factory_2_lbl_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Restore_factory_2_view_3
	ui_scr->Restore_factory_2_view_3 = lv_obj_create(ui_scr->Restore_factory_2);
	lv_obj_set_pos(ui_scr->Restore_factory_2_view_3, 16, 120);
	lv_obj_set_size(ui_scr->Restore_factory_2_view_3, 448, 506);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2_view_3, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget Restore_factory_2_view_3
	lv_obj_add_flag(ui_scr->Restore_factory_2_view_3, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->Restore_factory_2_view_3, GUI_CTRL_CONT);

	//Set style for Restore_factory_2_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Restore_factory_2_view_3, 24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Restore_factory_2_view_3, lv_color_make(0xE3, 0xED, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Restore_factory_2_gif_1
	ui_scr->Restore_factory_2_gif_1 = lv_gif_create(ui_scr->Restore_factory_2_view_3);
	lv_obj_set_pos(ui_scr->Restore_factory_2_gif_1, 144, 140);
	lv_obj_set_size(ui_scr->Restore_factory_2_gif_1, 160, 160);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2_gif_1, LV_SCROLLBAR_MODE_OFF);
	lv_gif_set_src(ui_scr->Restore_factory_2_gif_1, gui_get_res_path(GUI_RES_EZGIF_3A421AA367158DBB_GIF));

	//Write codes Restore_factory_2_lbl_3
	ui_scr->Restore_factory_2_lbl_3 = lv_label_create(ui_scr->Restore_factory_2_view_3);
	lv_label_set_long_mode(ui_scr->Restore_factory_2_lbl_3, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui_scr->Restore_factory_2_lbl_3, 80, 299);
	lv_obj_set_size(ui_scr->Restore_factory_2_lbl_3, 286, 48);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Restore_factory_2_lbl_3, GUI_CTRL_LABEL);

	//Set style for Restore_factory_2_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_color(ui_scr->Restore_factory_2_lbl_3, lv_color_make(0x3B, 0x7D, 0xEE), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Restore_factory_2_bar_1
	ui_scr->Restore_factory_2_bar_1 = lv_bar_create(ui_scr->Restore_factory_2_view_3);
	lv_obj_set_pos(ui_scr->Restore_factory_2_bar_1, 44, 350);
	lv_obj_set_size(ui_scr->Restore_factory_2_bar_1, 360, 16);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2_bar_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Restore_factory_2_bar_1, GUI_CTRL_BAR);
	lv_obj_set_style_anim_time(ui_scr->Restore_factory_2_bar_1, 1000, 0);
	lv_bar_set_mode(ui_scr->Restore_factory_2_bar_1, LV_BAR_MODE_NORMAL);
	lv_bar_set_range(ui_scr->Restore_factory_2_bar_1, 0, 100);
	lv_bar_set_value(ui_scr->Restore_factory_2_bar_1, 10, LV_ANIM_OFF);

	//Write codes Restore_factory_2_view_1
	ui_scr->Restore_factory_2_view_1 = lv_obj_create(ui_scr->Restore_factory_2);
	lv_obj_set_pos(ui_scr->Restore_factory_2_view_1, 0, 0);
	lv_obj_set_size(ui_scr->Restore_factory_2_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Restore_factory_2_view_1, GUI_CTRL_CONT);

	//Set style for Restore_factory_2_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->Restore_factory_2_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Restore_factory_2_lbl_1
	ui_scr->Restore_factory_2_lbl_1 = lv_label_create(ui_scr->Restore_factory_2_view_1);
	lv_label_set_text(ui_scr->Restore_factory_2_lbl_1, "80%");
	lv_label_set_long_mode(ui_scr->Restore_factory_2_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Restore_factory_2_lbl_1, 435, 6);
	lv_obj_set_size(ui_scr->Restore_factory_2_lbl_1, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Restore_factory_2_lbl_1, GUI_CTRL_LABEL);

	//Set style for Restore_factory_2_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Restore_factory_2_lbl_1, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Restore_factory_2_img_1
	ui_scr->Restore_factory_2_img_1 = lv_img_create(ui_scr->Restore_factory_2_view_1);
	lv_img_set_src(ui_scr->Restore_factory_2_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->Restore_factory_2_img_1, 0, 0);
	lv_img_set_angle(ui_scr->Restore_factory_2_img_1, 0);
	lv_img_set_zoom(ui_scr->Restore_factory_2_img_1, 256);
	lv_obj_set_pos(ui_scr->Restore_factory_2_img_1, 367, 0);
	lv_obj_set_size(ui_scr->Restore_factory_2_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->Restore_factory_2_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Restore_factory_2_img_1, GUI_CTRL_IMG);

	//Write codes Restore_factory_2_img_2
	ui_scr->Restore_factory_2_img_2 = lv_img_create(ui_scr->Restore_factory_2_view_1);
	lv_img_set_src(ui_scr->Restore_factory_2_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->Restore_factory_2_img_2, 0, 0);
	lv_img_set_angle(ui_scr->Restore_factory_2_img_2, 0);
	lv_img_set_zoom(ui_scr->Restore_factory_2_img_2, 256);
	lv_obj_set_pos(ui_scr->Restore_factory_2_img_2, 403, 0);
	lv_obj_set_size(ui_scr->Restore_factory_2_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->Restore_factory_2_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Restore_factory_2_img_2, GUI_CTRL_IMG);

	//Write codes Restore_factory_2_img_3
	ui_scr->Restore_factory_2_img_3 = lv_img_create(ui_scr->Restore_factory_2_view_1);
	lv_img_set_src(ui_scr->Restore_factory_2_img_3, gui_get_res_path(GUI_RES_SET_PNG));
	lv_img_set_pivot(ui_scr->Restore_factory_2_img_3, 0, 0);
	lv_img_set_angle(ui_scr->Restore_factory_2_img_3, 0);
	lv_img_set_zoom(ui_scr->Restore_factory_2_img_3, 256);
	lv_obj_set_pos(ui_scr->Restore_factory_2_img_3, 8, 0);
	lv_obj_set_size(ui_scr->Restore_factory_2_img_3, 32, 32);
	lv_obj_add_flag(ui_scr->Restore_factory_2_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Restore_factory_2_img_3, GUI_CTRL_IMG);

	//Write codes Restore_factory_2_view_4
	ui_scr->Restore_factory_2_view_4 = lv_obj_create(ui_scr->Restore_factory_2);
	lv_obj_set_pos(ui_scr->Restore_factory_2_view_4, 16, 120);
	lv_obj_set_size(ui_scr->Restore_factory_2_view_4, 448, 506);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2_view_4, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget Restore_factory_2_view_4
	lv_obj_add_flag(ui_scr->Restore_factory_2_view_4, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->Restore_factory_2_view_4, GUI_CTRL_CONT);

	//Set style for Restore_factory_2_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Restore_factory_2_view_4, 24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Restore_factory_2_view_4, lv_color_make(0xE3, 0xED, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Restore_factory_2_img_4
	ui_scr->Restore_factory_2_img_4 = lv_img_create(ui_scr->Restore_factory_2_view_4);
	lv_img_set_src(ui_scr->Restore_factory_2_img_4, gui_get_res_path(GUI_RES_SET_OK_1_PNG));
	lv_img_set_pivot(ui_scr->Restore_factory_2_img_4, 0, 0);
	lv_img_set_angle(ui_scr->Restore_factory_2_img_4, 0);
	lv_img_set_zoom(ui_scr->Restore_factory_2_img_4, 256);
	lv_obj_set_pos(ui_scr->Restore_factory_2_img_4, 144, 154);
	lv_obj_set_size(ui_scr->Restore_factory_2_img_4, 160, 160);
	lv_obj_add_flag(ui_scr->Restore_factory_2_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Restore_factory_2_img_4, GUI_CTRL_IMG);

	//Write codes Restore_factory_2_lbl_4
	ui_scr->Restore_factory_2_lbl_4 = lv_label_create(ui_scr->Restore_factory_2_view_4);
	lv_label_set_long_mode(ui_scr->Restore_factory_2_lbl_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Restore_factory_2_lbl_4, 82, 329);
	lv_obj_set_size(ui_scr->Restore_factory_2_lbl_4, 288, 70);
	lv_obj_set_scrollbar_mode(ui_scr->Restore_factory_2_lbl_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Restore_factory_2_lbl_4, GUI_CTRL_LABEL);

	//Set style for Restore_factory_2_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_color(ui_scr->Restore_factory_2_lbl_4, lv_color_make(0x3B, 0x7D, 0xEE), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui_scr->Restore_factory_2_lbl_4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);

	lv_obj_update_layout(ui_scr->Restore_factory_2);
	ui_scr->Restore_factory_2_del = false;
	i18n_refresh_texts(GUI_SCREEN_RESTORE_FACTORY_2);

	//Init events for screen
	events_init_Restore_factory_2(ui);
	return ui_scr->Restore_factory_2;
}
void unload_scr_Restore_factory_2(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_RESTORE_FACTORY_2);
}

#endif
