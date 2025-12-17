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


lv_obj_t * setup_scr_Shut_down(lv_ui *ui)
{
	lv_ui_Shut_down * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SHUT_DOWN);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_Shut_down));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_Shut_down));
		ui->Shut_down = ui_scr;
	}

	//Write codes Shut_down
	ui_scr->Shut_down = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->Shut_down, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Shut_down, GUI_CTRL_SCR);

	//Set style for Shut_down. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->Shut_down, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->Shut_down, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Shut_down_img_1
	ui_scr->Shut_down_img_1 = lv_img_create(ui_scr->Shut_down);
	lv_img_set_src(ui_scr->Shut_down_img_1, gui_get_res_path(GUI_RES_IMAGE_4215637_0_PNG));
	lv_img_set_pivot(ui_scr->Shut_down_img_1, 0, 0);
	lv_img_set_angle(ui_scr->Shut_down_img_1, 0);
	lv_img_set_zoom(ui_scr->Shut_down_img_1, 256);
	lv_obj_set_pos(ui_scr->Shut_down_img_1, 0, 0);
	lv_obj_set_size(ui_scr->Shut_down_img_1, 480, 640);
	lv_obj_clear_flag(ui_scr->Shut_down_img_1, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_flag(ui_scr->Shut_down_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Shut_down_img_1, GUI_CTRL_IMG);

	//Set style for Shut_down_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->Shut_down_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->Shut_down_img_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Shut_down_view_1
	ui_scr->Shut_down_view_1 = lv_obj_create(ui_scr->Shut_down);
	lv_obj_set_pos(ui_scr->Shut_down_view_1, 0, 0);
	lv_obj_set_size(ui_scr->Shut_down_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->Shut_down_view_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->Shut_down_view_1, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->Shut_down_view_1, GUI_CTRL_CONT);

	//Set style for Shut_down_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->Shut_down_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Shut_down_lbl_3
	ui_scr->Shut_down_lbl_3 = lv_label_create(ui_scr->Shut_down_view_1);
	lv_label_set_text(ui_scr->Shut_down_lbl_3, "80%");
	lv_label_set_long_mode(ui_scr->Shut_down_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Shut_down_lbl_3, 434, 6);
	lv_obj_set_size(ui_scr->Shut_down_lbl_3, 41, 22);
	lv_obj_set_scrollbar_mode(ui_scr->Shut_down_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Shut_down_lbl_3, GUI_CTRL_LABEL);

	//Set style for Shut_down_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Shut_down_lbl_3, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Shut_down_img_2
	ui_scr->Shut_down_img_2 = lv_img_create(ui_scr->Shut_down_view_1);
	lv_img_set_src(ui_scr->Shut_down_img_2, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->Shut_down_img_2, 0, 0);
	lv_img_set_angle(ui_scr->Shut_down_img_2, 0);
	lv_img_set_zoom(ui_scr->Shut_down_img_2, 256);
	lv_obj_set_pos(ui_scr->Shut_down_img_2, 367, 0);
	lv_obj_set_size(ui_scr->Shut_down_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->Shut_down_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Shut_down_img_2, GUI_CTRL_IMG);

	//Write codes Shut_down_img_3
	ui_scr->Shut_down_img_3 = lv_img_create(ui_scr->Shut_down_view_1);
	lv_img_set_src(ui_scr->Shut_down_img_3, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->Shut_down_img_3, 0, 0);
	lv_img_set_angle(ui_scr->Shut_down_img_3, 0);
	lv_img_set_zoom(ui_scr->Shut_down_img_3, 256);
	lv_obj_set_pos(ui_scr->Shut_down_img_3, 403, 0);
	lv_obj_set_size(ui_scr->Shut_down_img_3, 32, 32);
	lv_obj_add_flag(ui_scr->Shut_down_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Shut_down_img_3, GUI_CTRL_IMG);

	//Write codes Shut_down_view_2
	ui_scr->Shut_down_view_2 = lv_obj_create(ui_scr->Shut_down);
	lv_obj_set_pos(ui_scr->Shut_down_view_2, 152, 252);
	lv_obj_set_size(ui_scr->Shut_down_view_2, 176, 136);
	lv_obj_set_scrollbar_mode(ui_scr->Shut_down_view_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Shut_down_view_2, GUI_CTRL_CONT);

	//Set style for Shut_down_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Shut_down_view_2, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Shut_down_view_2, lv_color_make(0x76, 0xE3, 0x44), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Shut_down_lbl_1
	ui_scr->Shut_down_lbl_1 = lv_label_create(ui_scr->Shut_down_view_2);
	lv_label_set_long_mode(ui_scr->Shut_down_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Shut_down_lbl_1, 0, 77);
	lv_obj_set_size(ui_scr->Shut_down_lbl_1, 172, 40);
	lv_obj_set_scrollbar_mode(ui_scr->Shut_down_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Shut_down_lbl_1, GUI_CTRL_LABEL);

	//Set style for Shut_down_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_outline_opa(ui_scr->Shut_down_lbl_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->Shut_down_lbl_1, lv_color_make(0x82, 0x4A, 0x1B), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->Shut_down_lbl_1, -1, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Shut_down_img_4
	ui_scr->Shut_down_img_4 = lv_img_create(ui_scr->Shut_down_view_2);
	lv_img_set_src(ui_scr->Shut_down_img_4, gui_get_res_path(GUI_RES_SHUTDOWN_PNG));
	lv_img_set_pivot(ui_scr->Shut_down_img_4, 0, 0);
	lv_img_set_angle(ui_scr->Shut_down_img_4, 0);
	lv_img_set_zoom(ui_scr->Shut_down_img_4, 256);
	lv_obj_set_pos(ui_scr->Shut_down_img_4, 68, 24);
	lv_obj_set_size(ui_scr->Shut_down_img_4, 40, 40);
	lv_obj_add_flag(ui_scr->Shut_down_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Shut_down_img_4, GUI_CTRL_IMG);

	//Write codes Shut_down_img_5
	ui_scr->Shut_down_img_5 = lv_img_create(ui_scr->Shut_down);
	lv_img_set_src(ui_scr->Shut_down_img_5, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->Shut_down_img_5, 0, 0);
	lv_img_set_angle(ui_scr->Shut_down_img_5, 0);
	lv_img_set_zoom(ui_scr->Shut_down_img_5, 256);
	lv_obj_set_pos(ui_scr->Shut_down_img_5, 11, 43);
	lv_obj_set_size(ui_scr->Shut_down_img_5, 56, 56);
	lv_obj_add_flag(ui_scr->Shut_down_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Shut_down_img_5, GUI_CTRL_IMG);

	lv_obj_update_layout(ui_scr->Shut_down);
	ui_scr->Shut_down_del = false;
	i18n_refresh_texts(GUI_SCREEN_SHUT_DOWN);

	//Init events for screen
	events_init_Shut_down(ui);
	return ui_scr->Shut_down;
}
void unload_scr_Shut_down(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_SHUT_DOWN);
}

#endif
