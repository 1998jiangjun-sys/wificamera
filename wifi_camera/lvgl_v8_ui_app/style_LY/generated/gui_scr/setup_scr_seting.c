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


lv_obj_t * setup_scr_seting(lv_ui *ui)
{
	lv_ui_seting * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SETING);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_seting));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_seting));
		ui->seting = ui_scr;
	}

	//Write codes seting
	ui_scr->seting = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->seting, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting, GUI_CTRL_SCR);

	//Set style for seting. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_grad_color(ui_scr->seting, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->seting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_26
	ui_scr->seting_img_26 = lv_img_create(ui_scr->seting);
	lv_img_set_src(ui_scr->seting_img_26, gui_get_res_path(GUI_RES_IMAGE_9998327_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_26, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_26, 0);
	lv_img_set_zoom(ui_scr->seting_img_26, 256);
	lv_obj_set_pos(ui_scr->seting_img_26, 0, 0);
	lv_obj_set_size(ui_scr->seting_img_26, 480, 640);
	lv_obj_clear_flag(ui_scr->seting_img_26, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_flag(ui_scr->seting_img_26, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_26, GUI_CTRL_IMG);

	//Write codes seting_view_3
	ui_scr->seting_view_3 = lv_obj_create(ui_scr->seting);
	lv_obj_set_pos(ui_scr->seting_view_3, 0, 0);
	lv_obj_set_size(ui_scr->seting_view_3, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_3, GUI_CTRL_CONT);

	//Set style for seting_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->seting_view_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->seting_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_view_15
	ui_scr->seting_view_15 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_15, 16, 1118);
	lv_obj_set_size(ui_scr->seting_view_15, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_15, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_15, GUI_CTRL_CONT);

	//Set style for seting_view_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_15, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_15, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_21
	ui_scr->seting_lbl_21 = lv_label_create(ui_scr->seting_view_15);
	lv_label_set_long_mode(ui_scr->seting_lbl_21, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui_scr->seting_lbl_21, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_21, 225, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_21, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_21, GUI_CTRL_LABEL);

	//Set style for seting_lbl_21. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_21, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_21, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_28
	ui_scr->seting_img_28 = lv_img_create(ui_scr->seting_view_15);
	lv_img_set_src(ui_scr->seting_img_28, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_28, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_28, 0);
	lv_img_set_zoom(ui_scr->seting_img_28, 256);
	lv_obj_set_pos(ui_scr->seting_img_28, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_28, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_28, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_28, GUI_CTRL_IMG);

	//Write codes seting_img_29
	ui_scr->seting_img_29 = lv_img_create(ui_scr->seting_view_15);
	lv_img_set_src(ui_scr->seting_img_29, gui_get_res_path(GUI_RES_SET_VIDEO_PNG));
	lv_img_set_pivot(ui_scr->seting_img_29, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_29, 0);
	lv_img_set_zoom(ui_scr->seting_img_29, 256);
	lv_obj_set_pos(ui_scr->seting_img_29, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_29, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_29, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_29, GUI_CTRL_IMG);

	//Write codes seting_lbl_22
	ui_scr->seting_lbl_22 = lv_label_create(ui_scr->seting_view_15);
	lv_label_set_text(ui_scr->seting_lbl_22, "1080P");
	lv_label_set_long_mode(ui_scr->seting_lbl_22, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_22, 299, 32);
	lv_obj_set_size(ui_scr->seting_lbl_22, 95, 32);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_22, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_22, GUI_CTRL_LABEL);

	//Set style for seting_lbl_22. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->seting_lbl_22, &lv_font_simsun_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_22, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_22, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_view_14
	ui_scr->seting_view_14 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_14, 16, 1430);
	lv_obj_set_size(ui_scr->seting_view_14, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_14, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_14, GUI_CTRL_CONT);

	//Set style for seting_view_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_14, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_14, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_18
	ui_scr->seting_lbl_18 = lv_label_create(ui_scr->seting_view_14);
	lv_label_set_long_mode(ui_scr->seting_lbl_18, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_18, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_18, 274, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_18, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_18, GUI_CTRL_LABEL);

	//Set style for seting_lbl_18. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_18, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_18, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_23
	ui_scr->seting_img_23 = lv_img_create(ui_scr->seting_view_14);
	lv_img_set_src(ui_scr->seting_img_23, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_23, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_23, 0);
	lv_img_set_zoom(ui_scr->seting_img_23, 256);
	lv_obj_set_pos(ui_scr->seting_img_23, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_23, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_23, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_23, GUI_CTRL_IMG);

	//Write codes seting_img_24
	ui_scr->seting_img_24 = lv_img_create(ui_scr->seting_view_14);
	lv_img_set_src(ui_scr->seting_img_24, gui_get_res_path(GUI_RES_SET_RECOVER_PNG));
	lv_img_set_pivot(ui_scr->seting_img_24, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_24, 0);
	lv_img_set_zoom(ui_scr->seting_img_24, 256);
	lv_obj_set_pos(ui_scr->seting_img_24, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_24, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_24, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_24, GUI_CTRL_IMG);

	//Write codes seting_view_13
	ui_scr->seting_view_13 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_13, 16, 1326);
	lv_obj_set_size(ui_scr->seting_view_13, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_13, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_13, GUI_CTRL_CONT);

	//Set style for seting_view_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_13, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_13, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_17
	ui_scr->seting_lbl_17 = lv_label_create(ui_scr->seting_view_13);
	lv_label_set_long_mode(ui_scr->seting_lbl_17, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui_scr->seting_lbl_17, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_17, 274, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_17, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_17, GUI_CTRL_LABEL);

	//Set style for seting_lbl_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_17, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_17, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_21
	ui_scr->seting_img_21 = lv_img_create(ui_scr->seting_view_13);
	lv_img_set_src(ui_scr->seting_img_21, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_21, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_21, 0);
	lv_img_set_zoom(ui_scr->seting_img_21, 256);
	lv_obj_set_pos(ui_scr->seting_img_21, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_21, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_21, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_21, GUI_CTRL_IMG);

	//Write codes seting_img_22
	ui_scr->seting_img_22 = lv_img_create(ui_scr->seting_view_13);
	lv_img_set_src(ui_scr->seting_img_22, gui_get_res_path(GUI_RES_SET_VERSION_PNG));
	lv_img_set_pivot(ui_scr->seting_img_22, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_22, 0);
	lv_img_set_zoom(ui_scr->seting_img_22, 256);
	lv_obj_set_pos(ui_scr->seting_img_22, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_22, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_22, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_22, GUI_CTRL_IMG);

	//Write codes seting_view_12
	ui_scr->seting_view_12 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_12, 16, 1222);
	lv_obj_set_size(ui_scr->seting_view_12, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_12, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_12, GUI_CTRL_CONT);

	//Set style for seting_view_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_12, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_12, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_16
	ui_scr->seting_lbl_16 = lv_label_create(ui_scr->seting_view_12);
	lv_label_set_long_mode(ui_scr->seting_lbl_16, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui_scr->seting_lbl_16, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_16, 274, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_16, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_16, GUI_CTRL_LABEL);

	//Set style for seting_lbl_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_16, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_16, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_19
	ui_scr->seting_img_19 = lv_img_create(ui_scr->seting_view_12);
	lv_img_set_src(ui_scr->seting_img_19, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_19, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_19, 0);
	lv_img_set_zoom(ui_scr->seting_img_19, 256);
	lv_obj_set_pos(ui_scr->seting_img_19, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_19, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_19, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_19, GUI_CTRL_IMG);

	//Write codes seting_img_20
	ui_scr->seting_img_20 = lv_img_create(ui_scr->seting_view_12);
	lv_img_set_src(ui_scr->seting_img_20, gui_get_res_path(GUI_RES_SET_BINDING_PNG));
	lv_img_set_pivot(ui_scr->seting_img_20, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_20, 0);
	lv_img_set_zoom(ui_scr->seting_img_20, 256);
	lv_obj_set_pos(ui_scr->seting_img_20, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_20, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_20, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_20, GUI_CTRL_IMG);

	//Write codes seting_view_11
	ui_scr->seting_view_11 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_11, 16, 1014);
	lv_obj_set_size(ui_scr->seting_view_11, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_11, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_11, GUI_CTRL_CONT);

	//Set style for seting_view_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_11, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_11, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_14
	ui_scr->seting_lbl_14 = lv_label_create(ui_scr->seting_view_11);
	lv_label_set_long_mode(ui_scr->seting_lbl_14, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui_scr->seting_lbl_14, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_14, 201, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_14, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_14, GUI_CTRL_LABEL);

	//Set style for seting_lbl_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_14, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_14, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_17
	ui_scr->seting_img_17 = lv_img_create(ui_scr->seting_view_11);
	lv_img_set_src(ui_scr->seting_img_17, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_17, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_17, 0);
	lv_img_set_zoom(ui_scr->seting_img_17, 256);
	lv_obj_set_pos(ui_scr->seting_img_17, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_17, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_17, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_17, GUI_CTRL_IMG);

	//Write codes seting_img_18
	ui_scr->seting_img_18 = lv_img_create(ui_scr->seting_view_11);
	lv_img_set_src(ui_scr->seting_img_18, gui_get_res_path(GUI_RES_SET_PICTURE_PNG));
	lv_img_set_pivot(ui_scr->seting_img_18, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_18, 0);
	lv_img_set_zoom(ui_scr->seting_img_18, 256);
	lv_obj_set_pos(ui_scr->seting_img_18, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_18, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_18, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_18, GUI_CTRL_IMG);

	//Write codes seting_lbl_15
	ui_scr->seting_lbl_15 = lv_label_create(ui_scr->seting_view_11);
	lv_label_set_text(ui_scr->seting_lbl_15, "1080P");
	lv_label_set_long_mode(ui_scr->seting_lbl_15, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_15, 295, 32);
	lv_obj_set_size(ui_scr->seting_lbl_15, 97, 32);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_15, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_15, GUI_CTRL_LABEL);

	//Set style for seting_lbl_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->seting_lbl_15, &lv_font_simsun_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_15, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_15, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_view_10
	ui_scr->seting_view_10 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_10, 16, 910);
	lv_obj_set_size(ui_scr->seting_view_10, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_10, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_10, GUI_CTRL_CONT);

	//Set style for seting_view_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_10, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_10, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_13
	ui_scr->seting_lbl_13 = lv_label_create(ui_scr->seting_view_10);
	lv_label_set_long_mode(ui_scr->seting_lbl_13, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui_scr->seting_lbl_13, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_13, 274, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_13, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_13, GUI_CTRL_LABEL);

	//Set style for seting_lbl_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_13, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_13, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_15
	ui_scr->seting_img_15 = lv_img_create(ui_scr->seting_view_10);
	lv_img_set_src(ui_scr->seting_img_15, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_15, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_15, 0);
	lv_img_set_zoom(ui_scr->seting_img_15, 256);
	lv_obj_set_pos(ui_scr->seting_img_15, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_15, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_15, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_15, GUI_CTRL_IMG);

	//Write codes seting_img_16
	ui_scr->seting_img_16 = lv_img_create(ui_scr->seting_view_10);
	lv_img_set_src(ui_scr->seting_img_16, gui_get_res_path(GUI_RES_SET_TF_PNG));
	lv_img_set_pivot(ui_scr->seting_img_16, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_16, 0);
	lv_img_set_zoom(ui_scr->seting_img_16, 256);
	lv_obj_set_pos(ui_scr->seting_img_16, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_16, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_16, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_16, GUI_CTRL_IMG);

	//Write codes seting_view_9
	ui_scr->seting_view_9 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_9, 16, 806);
	lv_obj_set_size(ui_scr->seting_view_9, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_9, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_9, GUI_CTRL_CONT);

	//Set style for seting_view_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_9, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_9, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_10
	ui_scr->seting_lbl_10 = lv_label_create(ui_scr->seting_view_9);
	lv_label_set_long_mode(ui_scr->seting_lbl_10, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui_scr->seting_lbl_10, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_10, 252, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_10, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_10, GUI_CTRL_LABEL);

	//Set style for seting_lbl_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_10, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_13
	ui_scr->seting_img_13 = lv_img_create(ui_scr->seting_view_9);
	lv_img_set_src(ui_scr->seting_img_13, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_13, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_13, 0);
	lv_img_set_zoom(ui_scr->seting_img_13, 256);
	lv_obj_set_pos(ui_scr->seting_img_13, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_13, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_13, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_13, GUI_CTRL_IMG);

	//Write codes seting_img_14
	ui_scr->seting_img_14 = lv_img_create(ui_scr->seting_view_9);
	lv_img_set_src(ui_scr->seting_img_14, gui_get_res_path(GUI_RES_SET_SIZE_PNG));
	lv_img_set_pivot(ui_scr->seting_img_14, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_14, 0);
	lv_img_set_zoom(ui_scr->seting_img_14, 256);
	lv_obj_set_pos(ui_scr->seting_img_14, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_14, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_14, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_14, GUI_CTRL_IMG);

	//Write codes seting_lbl_12
	ui_scr->seting_lbl_12 = lv_label_create(ui_scr->seting_view_9);
	lv_label_set_text(ui_scr->seting_lbl_12, "高");
	lv_label_set_long_mode(ui_scr->seting_lbl_12, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_12, 284, 32);
	lv_obj_set_size(ui_scr->seting_lbl_12, 102, 35);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_12, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_12, GUI_CTRL_LABEL);

	//Set style for seting_lbl_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_12, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_12, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_view_8
	ui_scr->seting_view_8 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_8, 16, 702);
	lv_obj_set_size(ui_scr->seting_view_8, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_8, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_8, GUI_CTRL_CONT);

	//Set style for seting_view_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_8, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_8, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_9
	ui_scr->seting_lbl_9 = lv_label_create(ui_scr->seting_view_8);
	lv_label_set_long_mode(ui_scr->seting_lbl_9, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui_scr->seting_lbl_9, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_9, 226, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_9, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_9, GUI_CTRL_LABEL);

	//Set style for seting_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_9, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_9, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_11
	ui_scr->seting_img_11 = lv_img_create(ui_scr->seting_view_8);
	lv_img_set_src(ui_scr->seting_img_11, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_11, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_11, 0);
	lv_img_set_zoom(ui_scr->seting_img_11, 256);
	lv_obj_set_pos(ui_scr->seting_img_11, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_11, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_11, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_11, GUI_CTRL_IMG);

	//Write codes seting_img_12
	ui_scr->seting_img_12 = lv_img_create(ui_scr->seting_view_8);
	lv_img_set_src(ui_scr->seting_img_12, gui_get_res_path(GUI_RES_SET_SCREEN_OFF_PNG));
	lv_img_set_pivot(ui_scr->seting_img_12, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_12, 0);
	lv_img_set_zoom(ui_scr->seting_img_12, 256);
	lv_obj_set_pos(ui_scr->seting_img_12, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_12, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_12, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_12, GUI_CTRL_IMG);

	//Write codes seting_lbl_11
	ui_scr->seting_lbl_11 = lv_label_create(ui_scr->seting_view_8);
	lv_label_set_text(ui_scr->seting_lbl_11, "常亮");
	lv_label_set_long_mode(ui_scr->seting_lbl_11, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_11, 284, 32);
	lv_obj_set_size(ui_scr->seting_lbl_11, 102, 35);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_11, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_11, GUI_CTRL_LABEL);

	//Set style for seting_lbl_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_11, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_11, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_view_7
	ui_scr->seting_view_7 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_7, 16, 598);
	lv_obj_set_size(ui_scr->seting_view_7, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_7, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_7, GUI_CTRL_CONT);

	//Set style for seting_view_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_7, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_7, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_7
	ui_scr->seting_lbl_7 = lv_label_create(ui_scr->seting_view_7);
	lv_label_set_long_mode(ui_scr->seting_lbl_7, LV_LABEL_LONG_CLIP);
	lv_obj_set_pos(ui_scr->seting_lbl_7, 96, 30);
	lv_obj_set_size(ui_scr->seting_lbl_7, 183, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_7, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_7, GUI_CTRL_LABEL);

	//Set style for seting_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_7, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_9
	ui_scr->seting_img_9 = lv_img_create(ui_scr->seting_view_7);
	lv_img_set_src(ui_scr->seting_img_9, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_9, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_9, 0);
	lv_img_set_zoom(ui_scr->seting_img_9, 256);
	lv_obj_set_pos(ui_scr->seting_img_9, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_9, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_9, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_9, GUI_CTRL_IMG);

	//Write codes seting_img_10
	ui_scr->seting_img_10 = lv_img_create(ui_scr->seting_view_7);
	lv_img_set_src(ui_scr->seting_img_10, gui_get_res_path(GUI_RES_SET_WIFI_PNG));
	lv_img_set_pivot(ui_scr->seting_img_10, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_10, 0);
	lv_img_set_zoom(ui_scr->seting_img_10, 256);
	lv_obj_set_pos(ui_scr->seting_img_10, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_10, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_10, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_10, GUI_CTRL_IMG);

	//Write codes seting_lbl_8
	ui_scr->seting_lbl_8 = lv_label_create(ui_scr->seting_view_7);
	lv_label_set_text(ui_scr->seting_lbl_8, "未连接");
	lv_label_set_long_mode(ui_scr->seting_lbl_8, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_8, 259, 32);
	lv_obj_set_size(ui_scr->seting_lbl_8, 131, 35);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_8, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_8, GUI_CTRL_LABEL);

	//Set style for seting_lbl_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_8, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_8, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_view_6
	ui_scr->seting_view_6 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_6, 16, 494);
	lv_obj_set_size(ui_scr->seting_view_6, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_6, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_6, GUI_CTRL_CONT);

	//Set style for seting_view_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_6, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_6, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_7
	ui_scr->seting_img_7 = lv_img_create(ui_scr->seting_view_6);
	lv_img_set_src(ui_scr->seting_img_7, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_7, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_7, 0);
	lv_img_set_zoom(ui_scr->seting_img_7, 256);
	lv_obj_set_pos(ui_scr->seting_img_7, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_7, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_7, GUI_CTRL_IMG);

	//Write codes seting_img_8
	ui_scr->seting_img_8 = lv_img_create(ui_scr->seting_view_6);
	lv_img_set_src(ui_scr->seting_img_8, gui_get_res_path(GUI_RES_SET_LANGUAGE_PNG));
	lv_img_set_pivot(ui_scr->seting_img_8, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_8, 0);
	lv_img_set_zoom(ui_scr->seting_img_8, 256);
	lv_obj_set_pos(ui_scr->seting_img_8, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_8, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_8, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_8, GUI_CTRL_IMG);

	//Write codes seting_lbl_6
	ui_scr->seting_lbl_6 = lv_label_create(ui_scr->seting_view_6);
	lv_label_set_text(ui_scr->seting_lbl_6, "中文");
	lv_label_set_long_mode(ui_scr->seting_lbl_6, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_6, 285, 32);
	lv_obj_set_size(ui_scr->seting_lbl_6, 105, 35);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_6, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_6, GUI_CTRL_LABEL);

	//Set style for seting_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_6, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_6, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_23
	ui_scr->seting_lbl_23 = lv_label_create(ui_scr->seting_view_6);
	lv_label_set_long_mode(ui_scr->seting_lbl_23, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_23, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_23, 210, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_23, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_23, GUI_CTRL_LABEL);

	//Set style for seting_lbl_23. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_23, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_23, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_view_5
	ui_scr->seting_view_5 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_5, 16, 390);
	lv_obj_set_size(ui_scr->seting_view_5, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_5, GUI_CTRL_CONT);

	//Set style for seting_view_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_5, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_5, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_3
	ui_scr->seting_lbl_3 = lv_label_create(ui_scr->seting_view_5);
	lv_label_set_long_mode(ui_scr->seting_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_3, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_3, 210, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_3, GUI_CTRL_LABEL);

	//Set style for seting_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_3, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_5
	ui_scr->seting_img_5 = lv_img_create(ui_scr->seting_view_5);
	lv_img_set_src(ui_scr->seting_img_5, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_5, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_5, 0);
	lv_img_set_zoom(ui_scr->seting_img_5, 256);
	lv_obj_set_pos(ui_scr->seting_img_5, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_5, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_5, GUI_CTRL_IMG);

	//Write codes seting_img_6
	ui_scr->seting_img_6 = lv_img_create(ui_scr->seting_view_5);
	lv_img_set_src(ui_scr->seting_img_6, gui_get_res_path(GUI_RES_SET_VOLUME_PNG));
	lv_img_set_pivot(ui_scr->seting_img_6, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_6, 0);
	lv_img_set_zoom(ui_scr->seting_img_6, 256);
	lv_obj_set_pos(ui_scr->seting_img_6, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_6, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_6, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_6, GUI_CTRL_IMG);

	//Write codes seting_lbl_4
	ui_scr->seting_lbl_4 = lv_label_create(ui_scr->seting_view_5);
	lv_label_set_text(ui_scr->seting_lbl_4, "50%");
	lv_label_set_long_mode(ui_scr->seting_lbl_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_4, 304, 32);
	lv_obj_set_size(ui_scr->seting_lbl_4, 81, 33);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_4, GUI_CTRL_LABEL);

	//Set style for seting_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->seting_lbl_4, &lv_font_simsun_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_4, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_4, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_view_4
	ui_scr->seting_view_4 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_4, 16, 286);
	lv_obj_set_size(ui_scr->seting_view_4, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_4, GUI_CTRL_CONT);

	//Set style for seting_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->seting_view_4, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->seting_view_4, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_1
	ui_scr->seting_lbl_1 = lv_label_create(ui_scr->seting_view_4);
	lv_label_set_long_mode(ui_scr->seting_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_1, 96, 32);
	lv_obj_set_size(ui_scr->seting_lbl_1, 210, 46);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_1, GUI_CTRL_LABEL);

	//Set style for seting_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_1, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_4
	ui_scr->seting_img_4 = lv_img_create(ui_scr->seting_view_4);
	lv_img_set_src(ui_scr->seting_img_4, gui_get_res_path(GUI_RES_IMAGE_8787409_0_PNG));
	lv_img_set_pivot(ui_scr->seting_img_4, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_4, 0);
	lv_img_set_zoom(ui_scr->seting_img_4, 256);
	lv_obj_set_pos(ui_scr->seting_img_4, 400, 32);
	lv_obj_set_size(ui_scr->seting_img_4, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_4, GUI_CTRL_IMG);

	//Write codes seting_img_3
	ui_scr->seting_img_3 = lv_img_create(ui_scr->seting_view_4);
	lv_img_set_src(ui_scr->seting_img_3, gui_get_res_path(GUI_RES_SET_BRIGHTNESS_PNG));
	lv_img_set_pivot(ui_scr->seting_img_3, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_3, 0);
	lv_img_set_zoom(ui_scr->seting_img_3, 256);
	lv_obj_set_pos(ui_scr->seting_img_3, 16, 16);
	lv_obj_set_size(ui_scr->seting_img_3, 64, 64);
	lv_obj_add_flag(ui_scr->seting_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_3, GUI_CTRL_IMG);

	//Write codes seting_lbl_2
	ui_scr->seting_lbl_2 = lv_label_create(ui_scr->seting_view_4);
	lv_label_set_text(ui_scr->seting_lbl_2, "50%");
	lv_label_set_long_mode(ui_scr->seting_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_2, 307, 32);
	lv_obj_set_size(ui_scr->seting_lbl_2, 78, 33);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_2, GUI_CTRL_LABEL);

	//Set style for seting_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->seting_lbl_2, &lv_font_simsun_26, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_2, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_2, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_view_17
	ui_scr->seting_view_17 = lv_obj_create(ui_scr->seting_view_3);
	lv_obj_set_pos(ui_scr->seting_view_17, 16, 120);
	lv_obj_set_size(ui_scr->seting_view_17, 448, 150);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_17, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_view_17, GUI_CTRL_CONT);

	//Set style for seting_view_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->seting_view_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->seting_view_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_33
	ui_scr->seting_img_33 = lv_img_create(ui_scr->seting_view_17);
	lv_img_set_src(ui_scr->seting_img_33, gui_get_res_path(GUI_RES_BG_ADVANCED_PNG));
	lv_img_set_pivot(ui_scr->seting_img_33, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_33, 0);
	lv_img_set_zoom(ui_scr->seting_img_33, 256);
	lv_obj_set_pos(ui_scr->seting_img_33, 0, -5);
	lv_obj_set_size(ui_scr->seting_img_33, 448, 175);
	lv_obj_add_flag(ui_scr->seting_img_33, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_33, GUI_CTRL_IMG);

	//Write codes seting_lbl_24
	ui_scr->seting_lbl_24 = lv_label_create(ui_scr->seting_view_17);
	lv_label_set_long_mode(ui_scr->seting_lbl_24, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_24, 154, 84);
	lv_obj_set_size(ui_scr->seting_lbl_24, 278, 43);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_24, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_24, GUI_CTRL_LABEL);

	//Set style for seting_lbl_24. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->seting_lbl_24, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->seting_lbl_24, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_view_2
	ui_scr->seting_view_2 = lv_obj_create(ui_scr->seting);
	lv_obj_set_pos(ui_scr->seting_view_2, 0, 32);
	lv_obj_set_size(ui_scr->seting_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->seting_view_2, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->seting_view_2, GUI_CTRL_CONT);

	//Set style for seting_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->seting_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->seting_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_20
	ui_scr->seting_lbl_20 = lv_label_create(ui_scr->seting_view_2);
	lv_label_set_long_mode(ui_scr->seting_lbl_20, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_20, 88, 15);
	lv_obj_set_size(ui_scr->seting_lbl_20, 310, 49);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_20, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_20, GUI_CTRL_LABEL);

	//Set style for seting_lbl_20. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_align(ui_scr->seting_lbl_20, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_27
	ui_scr->seting_img_27 = lv_img_create(ui_scr->seting_view_2);
	lv_img_set_src(ui_scr->seting_img_27, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->seting_img_27, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_27, 0);
	lv_img_set_zoom(ui_scr->seting_img_27, 256);
	lv_obj_set_pos(ui_scr->seting_img_27, 16, 8);
	lv_obj_set_size(ui_scr->seting_img_27, 56, 56);
	lv_obj_add_flag(ui_scr->seting_img_27, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_27, GUI_CTRL_IMG);

	//Write codes seting_view_1
	ui_scr->seting_view_1 = lv_obj_create(ui_scr->seting);
	lv_obj_set_pos(ui_scr->seting_view_1, 0, 0);
	lv_obj_set_size(ui_scr->seting_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->seting_view_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->seting_view_1, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->seting_view_1, GUI_CTRL_CONT);

	//Set style for seting_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->seting_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_lbl_19
	ui_scr->seting_lbl_19 = lv_label_create(ui_scr->seting_view_1);
	lv_label_set_text(ui_scr->seting_lbl_19, "80%");
	lv_label_set_long_mode(ui_scr->seting_lbl_19, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->seting_lbl_19, 435, 6);
	lv_obj_set_size(ui_scr->seting_lbl_19, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->seting_lbl_19, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->seting_lbl_19, GUI_CTRL_LABEL);

	//Set style for seting_lbl_19. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->seting_lbl_19, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes seting_img_1
	ui_scr->seting_img_1 = lv_img_create(ui_scr->seting_view_1);
	lv_img_set_src(ui_scr->seting_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->seting_img_1, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_1, 0);
	lv_img_set_zoom(ui_scr->seting_img_1, 256);
	lv_obj_set_pos(ui_scr->seting_img_1, 367, 0);
	lv_obj_set_size(ui_scr->seting_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_1, GUI_CTRL_IMG);

	//Write codes seting_img_2
	ui_scr->seting_img_2 = lv_img_create(ui_scr->seting_view_1);
	lv_img_set_src(ui_scr->seting_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->seting_img_2, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_2, 0);
	lv_img_set_zoom(ui_scr->seting_img_2, 256);
	lv_obj_set_pos(ui_scr->seting_img_2, 403, 0);
	lv_obj_set_size(ui_scr->seting_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_2, GUI_CTRL_IMG);

	//Write codes seting_img_25
	ui_scr->seting_img_25 = lv_img_create(ui_scr->seting_view_1);
	lv_img_set_src(ui_scr->seting_img_25, gui_get_res_path(GUI_RES_SET_PNG));
	lv_img_set_pivot(ui_scr->seting_img_25, 0, 0);
	lv_img_set_angle(ui_scr->seting_img_25, 0);
	lv_img_set_zoom(ui_scr->seting_img_25, 256);
	lv_obj_set_pos(ui_scr->seting_img_25, 8, 0);
	lv_obj_set_size(ui_scr->seting_img_25, 32, 32);
	lv_obj_add_flag(ui_scr->seting_img_25, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->seting_img_25, GUI_CTRL_IMG);

	lv_obj_update_layout(ui_scr->seting);
	ui_scr->seting_del = false;
	i18n_refresh_texts(GUI_SCREEN_SETING);

	//Init events for screen
	events_init_seting(ui);
	return ui_scr->seting;
}
void unload_scr_seting(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_SETING);
}

#endif
