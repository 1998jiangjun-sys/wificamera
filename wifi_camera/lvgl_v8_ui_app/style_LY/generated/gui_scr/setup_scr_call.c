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


lv_obj_t * setup_scr_call(lv_ui *ui)
{
	lv_ui_call * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CALL);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_call));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_call));
		ui->call = ui_scr;
	}

	//Write codes call
	ui_scr->call = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->call, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->call, GUI_CTRL_SCR);

	//Write codes call_view_5
	ui_scr->call_view_5 = lv_obj_create(ui_scr->call);
	lv_obj_set_pos(ui_scr->call_view_5, 0, 0);
	lv_obj_set_size(ui_scr->call_view_5, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->call_view_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->call_view_5, GUI_CTRL_CONT);

	//Set style for call_view_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->call_view_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->call_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes call_lbl_4
	ui_scr->call_lbl_4 = lv_label_create(ui_scr->call_view_5);
	lv_label_set_text(ui_scr->call_lbl_4, "正在呼叫…");
	lv_label_set_long_mode(ui_scr->call_lbl_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->call_lbl_4, 0, 348);
	lv_obj_set_size(ui_scr->call_lbl_4, 480, 42);
	lv_obj_set_scrollbar_mode(ui_scr->call_lbl_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->call_lbl_4, GUI_CTRL_LABEL);

	//Set style for call_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_border_opa(ui_scr->call_lbl_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->call_lbl_4, &lv_font_simsun_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->call_lbl_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes call_view_1
	ui_scr->call_view_1 = lv_obj_create(ui_scr->call);
	lv_obj_set_pos(ui_scr->call_view_1, 0, 0);
	lv_obj_set_size(ui_scr->call_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->call_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->call_view_1, GUI_CTRL_CONT);

	//Set style for call_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->call_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes call_lbl_3
	ui_scr->call_lbl_3 = lv_label_create(ui_scr->call_view_1);
	lv_label_set_text(ui_scr->call_lbl_3, "80%");
	lv_label_set_long_mode(ui_scr->call_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->call_lbl_3, 435, 6);
	lv_obj_set_size(ui_scr->call_lbl_3, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->call_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->call_lbl_3, GUI_CTRL_LABEL);

	//Set style for call_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->call_lbl_3, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes call_img_1
	ui_scr->call_img_1 = lv_img_create(ui_scr->call_view_1);
	lv_img_set_src(ui_scr->call_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->call_img_1, 0, 0);
	lv_img_set_angle(ui_scr->call_img_1, 0);
	lv_img_set_zoom(ui_scr->call_img_1, 256);
	lv_obj_set_pos(ui_scr->call_img_1, 367, 0);
	lv_obj_set_size(ui_scr->call_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->call_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->call_img_1, GUI_CTRL_IMG);

	//Write codes call_img_2
	ui_scr->call_img_2 = lv_img_create(ui_scr->call_view_1);
	lv_img_set_src(ui_scr->call_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->call_img_2, 0, 0);
	lv_img_set_angle(ui_scr->call_img_2, 0);
	lv_img_set_zoom(ui_scr->call_img_2, 256);
	lv_obj_set_pos(ui_scr->call_img_2, 403, 0);
	lv_obj_set_size(ui_scr->call_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->call_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->call_img_2, GUI_CTRL_IMG);

	//Write codes call_img_5
	ui_scr->call_img_5 = lv_img_create(ui_scr->call_view_1);
	lv_img_set_src(ui_scr->call_img_5, gui_get_res_path(GUI_RES_COMMUNICATION_PNG));
	lv_img_set_pivot(ui_scr->call_img_5, 0, 0);
	lv_img_set_angle(ui_scr->call_img_5, 0);
	lv_img_set_zoom(ui_scr->call_img_5, 256);
	lv_obj_set_pos(ui_scr->call_img_5, 8, 0);
	lv_obj_set_size(ui_scr->call_img_5, 32, 32);
	lv_obj_add_flag(ui_scr->call_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->call_img_5, GUI_CTRL_IMG);

	//Write codes call_view_6
	ui_scr->call_view_6 = lv_obj_create(ui_scr->call);
	lv_obj_set_pos(ui_scr->call_view_6, 0, 0);
	lv_obj_set_size(ui_scr->call_view_6, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->call_view_6, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget call_view_6
	lv_obj_add_flag(ui_scr->call_view_6, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->call_view_6, GUI_CTRL_CONT);

	//Set style for call_view_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->call_view_6, 179, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes call_img_3
	ui_scr->call_img_3 = lv_img_create(ui_scr->call_view_6);
	lv_img_set_src(ui_scr->call_img_3, gui_get_res_path(GUI_RES_BG_POP_PNG));
	lv_img_set_pivot(ui_scr->call_img_3, 0, 0);
	lv_img_set_angle(ui_scr->call_img_3, 0);
	lv_img_set_zoom(ui_scr->call_img_3, 256);
	lv_obj_set_pos(ui_scr->call_img_3, 28, 190);
	lv_obj_set_size(ui_scr->call_img_3, 428, 320);
	lv_obj_add_flag(ui_scr->call_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->call_img_3, GUI_CTRL_IMG);

	//Write codes call_lbl_2
	ui_scr->call_lbl_2 = lv_label_create(ui_scr->call_view_6);
	lv_label_set_long_mode(ui_scr->call_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->call_lbl_2, 56, 313);
	lv_obj_set_size(ui_scr->call_lbl_2, 370, 52);
	lv_obj_set_scrollbar_mode(ui_scr->call_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->call_lbl_2, GUI_CTRL_LABEL);

	//Set style for call_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_color(ui_scr->call_lbl_2, lv_color_make(0x82, 0x4A, 0x1B), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes call_img_4
	ui_scr->call_img_4 = lv_img_create(ui_scr->call_view_6);
	lv_img_set_src(ui_scr->call_img_4, gui_get_res_path(GUI_RES_HOME_ERROR_PNG));
	lv_img_set_pivot(ui_scr->call_img_4, 0, 0);
	lv_img_set_angle(ui_scr->call_img_4, 0);
	lv_img_set_zoom(ui_scr->call_img_4, 256);
	lv_obj_set_pos(ui_scr->call_img_4, 165, 128);
	lv_obj_set_size(ui_scr->call_img_4, 150, 150);
	lv_obj_add_flag(ui_scr->call_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->call_img_4, GUI_CTRL_IMG);

	//Write codes call_btn_3
	ui_scr->call_btn_3 = lv_btn_create(ui_scr->call_view_6);
	lv_obj_set_pos(ui_scr->call_btn_3, 56, 408);
	lv_obj_set_size(ui_scr->call_btn_3, 368, 62);
	lv_obj_set_scrollbar_mode(ui_scr->call_btn_3, LV_SCROLLBAR_MODE_OFF);
	lv_group_remove_obj(ui_scr->call_btn_3);
	ui_style_set(ui_scr->call_btn_3, GUI_CTRL_BUTTON);

	//Set style for call_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_width(ui_scr->call_btn_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui_scr->call_btn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->call_btn_3, 64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui_scr->call_btn_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->call_btn_3_label = lv_label_create(ui_scr->call_btn_3);
	lv_obj_set_style_pad_all(ui_scr->call_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->call_btn_3_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes call_img_7
	ui_scr->call_img_7 = lv_img_create(ui_scr->call_view_6);
	lv_img_set_src(ui_scr->call_img_7, gui_get_res_path(GUI_RES_IMAGE_7991533_0_PNG));
	lv_img_set_pivot(ui_scr->call_img_7, 0, 0);
	lv_img_set_angle(ui_scr->call_img_7, 0);
	lv_img_set_zoom(ui_scr->call_img_7, 256);
	lv_obj_set_pos(ui_scr->call_img_7, 418, 181);
	lv_obj_set_size(ui_scr->call_img_7, 48, 48);
	lv_obj_add_flag(ui_scr->call_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->call_img_7, GUI_CTRL_IMG);

	//Write codes call_view_3
	ui_scr->call_view_3 = lv_obj_create(ui_scr->call);
	lv_obj_set_pos(ui_scr->call_view_3, 22, 128);
	lv_obj_set_size(ui_scr->call_view_3, 436, 410);
	lv_obj_set_scrollbar_mode(ui_scr->call_view_3, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget call_view_3
	lv_obj_add_flag(ui_scr->call_view_3, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->call_view_3, GUI_CTRL_CONT);

	//Set style for call_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->call_view_3, 24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->call_view_3, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes call_lbl_1
	ui_scr->call_lbl_1 = lv_label_create(ui_scr->call);
	lv_label_set_text(ui_scr->call_lbl_1, "可爱鸭");
	lv_label_set_long_mode(ui_scr->call_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->call_lbl_1, 0, 290);
	lv_obj_set_size(ui_scr->call_lbl_1, 480, 35);
	lv_obj_set_scrollbar_mode(ui_scr->call_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->call_lbl_1, GUI_CTRL_LABEL);

	//Set style for call_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->call_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->call_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->call_lbl_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->call_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes call_img_8
	ui_scr->call_img_8 = lv_img_create(ui_scr->call);
	lv_img_set_src(ui_scr->call_img_8, gui_get_res_path(GUI_RES_COMMUNICATION_HANG_PNG));
	lv_img_set_pivot(ui_scr->call_img_8, 0, 0);
	lv_img_set_angle(ui_scr->call_img_8, 0);
	lv_img_set_zoom(ui_scr->call_img_8, 256);
	lv_obj_set_pos(ui_scr->call_img_8, 198, 457);
	lv_obj_set_size(ui_scr->call_img_8, 80, 80);
	lv_obj_add_flag(ui_scr->call_img_8, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->call_img_8, GUI_CTRL_IMG);

	//Write codes call_img_9
	ui_scr->call_img_9 = lv_img_create(ui_scr->call);
	lv_img_set_src(ui_scr->call_img_9, gui_get_res_path(GUI_RES_COMMUNICATION_HANG_PNG));
	lv_img_set_pivot(ui_scr->call_img_9, 0, 0);
	lv_img_set_angle(ui_scr->call_img_9, 0);
	lv_img_set_zoom(ui_scr->call_img_9, 256);
	lv_obj_set_pos(ui_scr->call_img_9, 96, 457);
	lv_obj_set_size(ui_scr->call_img_9, 80, 80);
	lv_obj_add_flag(ui_scr->call_img_9, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget call_img_9
	lv_obj_add_flag(ui_scr->call_img_9, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->call_img_9, GUI_CTRL_IMG);

	//Write codes call_img_10
	ui_scr->call_img_10 = lv_img_create(ui_scr->call);
	lv_img_set_src(ui_scr->call_img_10, gui_get_res_path(GUI_RES_COMMUNICATION_ANSWER_PNG));
	lv_img_set_pivot(ui_scr->call_img_10, 0, 0);
	lv_img_set_angle(ui_scr->call_img_10, 0);
	lv_img_set_zoom(ui_scr->call_img_10, 256);
	lv_obj_set_pos(ui_scr->call_img_10, 304, 457);
	lv_obj_set_size(ui_scr->call_img_10, 80, 80);
	lv_obj_add_flag(ui_scr->call_img_10, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget call_img_10
	lv_obj_add_flag(ui_scr->call_img_10, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->call_img_10, GUI_CTRL_IMG);

	//Write codes call_img_11
	ui_scr->call_img_11 = lv_img_create(ui_scr->call);
	lv_img_set_src(ui_scr->call_img_11, gui_get_res_path(GUI_RES_COMMUNICATION_MIC_PNG));
	lv_img_set_pivot(ui_scr->call_img_11, 0, 0);
	lv_img_set_angle(ui_scr->call_img_11, 0);
	lv_img_set_zoom(ui_scr->call_img_11, 256);
	lv_obj_set_pos(ui_scr->call_img_11, 64, 468);
	lv_obj_set_size(ui_scr->call_img_11, 72, 72);
	lv_obj_add_flag(ui_scr->call_img_11, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget call_img_11
	lv_obj_add_flag(ui_scr->call_img_11, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->call_img_11, GUI_CTRL_IMG);

	//Write codes call_img_12
	ui_scr->call_img_12 = lv_img_create(ui_scr->call);
	lv_img_set_src(ui_scr->call_img_12, gui_get_res_path(GUI_RES_COMMUNICATION_HANG_PNG));
	lv_img_set_pivot(ui_scr->call_img_12, 0, 0);
	lv_img_set_angle(ui_scr->call_img_12, 0);
	lv_img_set_zoom(ui_scr->call_img_12, 256);
	lv_obj_set_pos(ui_scr->call_img_12, 204, 464);
	lv_obj_set_size(ui_scr->call_img_12, 80, 80);
	lv_obj_add_flag(ui_scr->call_img_12, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget call_img_12
	lv_obj_add_flag(ui_scr->call_img_12, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->call_img_12, GUI_CTRL_IMG);

	//Write codes call_img_13
	ui_scr->call_img_13 = lv_img_create(ui_scr->call);
	lv_img_set_src(ui_scr->call_img_13, gui_get_res_path(GUI_RES_COMMUNICATION_SPEAKER_PNG));
	lv_img_set_pivot(ui_scr->call_img_13, 0, 0);
	lv_img_set_angle(ui_scr->call_img_13, 0);
	lv_img_set_zoom(ui_scr->call_img_13, 256);
	lv_obj_set_pos(ui_scr->call_img_13, 352, 468);
	lv_obj_set_size(ui_scr->call_img_13, 72, 72);
	lv_obj_add_flag(ui_scr->call_img_13, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget call_img_13
	lv_obj_add_flag(ui_scr->call_img_13, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->call_img_13, GUI_CTRL_IMG);

	lv_obj_update_layout(ui_scr->call);
	ui_scr->call_del = false;
	i18n_refresh_texts(GUI_SCREEN_CALL);

	//Init events for screen
	events_init_call(ui);
	return ui_scr->call;
}
void unload_scr_call(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_CALL);
}

#endif
