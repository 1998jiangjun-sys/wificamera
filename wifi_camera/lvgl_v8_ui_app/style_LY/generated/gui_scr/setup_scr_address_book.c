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


lv_obj_t * setup_scr_address_book(lv_ui *ui)
{
	lv_ui_address_book * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_ADDRESS_BOOK);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_address_book));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_address_book));
		ui->address_book = ui_scr;
	}

	//Write codes address_book
	ui_scr->address_book = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->address_book, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book, GUI_CTRL_SCR);

	//Set style for address_book. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_grad_color(ui_scr->address_book, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->address_book, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_26
	ui_scr->address_book_img_26 = lv_img_create(ui_scr->address_book);
	lv_img_set_src(ui_scr->address_book_img_26, gui_get_res_path(GUI_RES_IMAGE_9998327_0_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_26, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_26, 0);
	lv_img_set_zoom(ui_scr->address_book_img_26, 256);
	lv_obj_set_pos(ui_scr->address_book_img_26, 0, 0);
	lv_obj_set_size(ui_scr->address_book_img_26, 480, 640);
	lv_obj_clear_flag(ui_scr->address_book_img_26, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_flag(ui_scr->address_book_img_26, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_26, GUI_CTRL_IMG);

	//Write codes address_book_view_3
	ui_scr->address_book_view_3 = lv_obj_create(ui_scr->address_book);
	lv_obj_set_pos(ui_scr->address_book_view_3, 0, 0);
	lv_obj_set_size(ui_scr->address_book_view_3, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_3, GUI_CTRL_CONT);

	//Set style for address_book_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->address_book_view_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->address_book_view_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_view_14
	ui_scr->address_book_view_14 = lv_obj_create(ui_scr->address_book_view_3);
	lv_obj_set_pos(ui_scr->address_book_view_14, 16, 1132);
	lv_obj_set_size(ui_scr->address_book_view_14, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_14, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_14, GUI_CTRL_CONT);

	//Set style for address_book_view_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_view_14, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_view_14, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_18
	ui_scr->address_book_lbl_18 = lv_label_create(ui_scr->address_book_view_14);
	lv_label_set_text(ui_scr->address_book_lbl_18, "恢复出厂设置");
	lv_label_set_long_mode(ui_scr->address_book_lbl_18, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_18, 30, 32);
	lv_obj_set_size(ui_scr->address_book_lbl_18, 292, 46);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_18, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_18, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_18. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_18, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_18, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_23
	ui_scr->address_book_img_23 = lv_img_create(ui_scr->address_book_view_14);
	lv_img_set_src(ui_scr->address_book_img_23, gui_get_res_path(GUI_RES_COMMUNICATION_EDIT_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_23, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_23, 0);
	lv_img_set_zoom(ui_scr->address_book_img_23, 256);
	lv_obj_set_pos(ui_scr->address_book_img_23, 392, 32);
	lv_obj_set_size(ui_scr->address_book_img_23, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_23, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_23, GUI_CTRL_IMG);

	//Write codes address_book_view_13
	ui_scr->address_book_view_13 = lv_obj_create(ui_scr->address_book_view_3);
	lv_obj_set_pos(ui_scr->address_book_view_13, 16, 1024);
	lv_obj_set_size(ui_scr->address_book_view_13, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_13, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_13, GUI_CTRL_CONT);

	//Set style for address_book_view_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_view_13, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_view_13, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_17
	ui_scr->address_book_lbl_17 = lv_label_create(ui_scr->address_book_view_13);
	lv_label_set_text(ui_scr->address_book_lbl_17, "软件版本");
	lv_label_set_long_mode(ui_scr->address_book_lbl_17, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_17, 30, 32);
	lv_obj_set_size(ui_scr->address_book_lbl_17, 288, 46);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_17, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_17, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_17, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_17, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_21
	ui_scr->address_book_img_21 = lv_img_create(ui_scr->address_book_view_13);
	lv_img_set_src(ui_scr->address_book_img_21, gui_get_res_path(GUI_RES_COMMUNICATION_EDIT_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_21, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_21, 0);
	lv_img_set_zoom(ui_scr->address_book_img_21, 256);
	lv_obj_set_pos(ui_scr->address_book_img_21, 392, 32);
	lv_obj_set_size(ui_scr->address_book_img_21, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_21, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_21, GUI_CTRL_IMG);

	//Write codes address_book_view_12
	ui_scr->address_book_view_12 = lv_obj_create(ui_scr->address_book_view_3);
	lv_obj_set_pos(ui_scr->address_book_view_12, 16, 924);
	lv_obj_set_size(ui_scr->address_book_view_12, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_12, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_12, GUI_CTRL_CONT);

	//Set style for address_book_view_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_view_12, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_view_12, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_16
	ui_scr->address_book_lbl_16 = lv_label_create(ui_scr->address_book_view_12);
	lv_label_set_text(ui_scr->address_book_lbl_16, "设备绑定码");
	lv_label_set_long_mode(ui_scr->address_book_lbl_16, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_16, 30, 32);
	lv_obj_set_size(ui_scr->address_book_lbl_16, 289, 46);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_16, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_16, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_16, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_16, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_19
	ui_scr->address_book_img_19 = lv_img_create(ui_scr->address_book_view_12);
	lv_img_set_src(ui_scr->address_book_img_19, gui_get_res_path(GUI_RES_COMMUNICATION_EDIT_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_19, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_19, 0);
	lv_img_set_zoom(ui_scr->address_book_img_19, 256);
	lv_obj_set_pos(ui_scr->address_book_img_19, 392, 32);
	lv_obj_set_size(ui_scr->address_book_img_19, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_19, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_19, GUI_CTRL_IMG);

	//Write codes address_book_view_11
	ui_scr->address_book_view_11 = lv_obj_create(ui_scr->address_book_view_3);
	lv_obj_set_pos(ui_scr->address_book_view_11, 16, 820);
	lv_obj_set_size(ui_scr->address_book_view_11, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_11, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_11, GUI_CTRL_CONT);

	//Set style for address_book_view_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_view_11, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_view_11, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_14
	ui_scr->address_book_lbl_14 = lv_label_create(ui_scr->address_book_view_11);
	lv_label_set_text(ui_scr->address_book_lbl_14, "图片分辨率");
	lv_label_set_long_mode(ui_scr->address_book_lbl_14, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_14, 30, 32);
	lv_obj_set_size(ui_scr->address_book_lbl_14, 303, 46);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_14, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_14, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_14, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_14, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_17
	ui_scr->address_book_img_17 = lv_img_create(ui_scr->address_book_view_11);
	lv_img_set_src(ui_scr->address_book_img_17, gui_get_res_path(GUI_RES_COMMUNICATION_EDIT_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_17, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_17, 0);
	lv_img_set_zoom(ui_scr->address_book_img_17, 256);
	lv_obj_set_pos(ui_scr->address_book_img_17, 392, 32);
	lv_obj_set_size(ui_scr->address_book_img_17, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_17, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_17, GUI_CTRL_IMG);

	//Write codes address_book_view_10
	ui_scr->address_book_view_10 = lv_obj_create(ui_scr->address_book_view_3);
	lv_obj_set_pos(ui_scr->address_book_view_10, 16, 716);
	lv_obj_set_size(ui_scr->address_book_view_10, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_10, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_10, GUI_CTRL_CONT);

	//Set style for address_book_view_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_view_10, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_view_10, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_13
	ui_scr->address_book_lbl_13 = lv_label_create(ui_scr->address_book_view_10);
	lv_label_set_text(ui_scr->address_book_lbl_13, "TF卡格式化");
	lv_label_set_long_mode(ui_scr->address_book_lbl_13, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_13, 30, 32);
	lv_obj_set_size(ui_scr->address_book_lbl_13, 295, 46);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_13, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_13, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_13, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_13, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_15
	ui_scr->address_book_img_15 = lv_img_create(ui_scr->address_book_view_10);
	lv_img_set_src(ui_scr->address_book_img_15, gui_get_res_path(GUI_RES_COMMUNICATION_EDIT_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_15, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_15, 0);
	lv_img_set_zoom(ui_scr->address_book_img_15, 256);
	lv_obj_set_pos(ui_scr->address_book_img_15, 392, 32);
	lv_obj_set_size(ui_scr->address_book_img_15, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_15, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_15, GUI_CTRL_IMG);

	//Write codes address_book_view_9
	ui_scr->address_book_view_9 = lv_obj_create(ui_scr->address_book_view_3);
	lv_obj_set_pos(ui_scr->address_book_view_9, 16, 612);
	lv_obj_set_size(ui_scr->address_book_view_9, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_9, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_9, GUI_CTRL_CONT);

	//Set style for address_book_view_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_view_9, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_view_9, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_10
	ui_scr->address_book_lbl_10 = lv_label_create(ui_scr->address_book_view_9);
	lv_label_set_text(ui_scr->address_book_lbl_10, "图片尺寸");
	lv_label_set_long_mode(ui_scr->address_book_lbl_10, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_10, 30, 32);
	lv_obj_set_size(ui_scr->address_book_lbl_10, 293, 46);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_10, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_10, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_10, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_13
	ui_scr->address_book_img_13 = lv_img_create(ui_scr->address_book_view_9);
	lv_img_set_src(ui_scr->address_book_img_13, gui_get_res_path(GUI_RES_COMMUNICATION_EDIT_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_13, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_13, 0);
	lv_img_set_zoom(ui_scr->address_book_img_13, 256);
	lv_obj_set_pos(ui_scr->address_book_img_13, 392, 32);
	lv_obj_set_size(ui_scr->address_book_img_13, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_13, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_13, GUI_CTRL_IMG);

	//Write codes address_book_view_8
	ui_scr->address_book_view_8 = lv_obj_create(ui_scr->address_book_view_3);
	lv_obj_set_pos(ui_scr->address_book_view_8, 16, 508);
	lv_obj_set_size(ui_scr->address_book_view_8, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_8, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_8, GUI_CTRL_CONT);

	//Set style for address_book_view_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_view_8, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_view_8, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_9
	ui_scr->address_book_lbl_9 = lv_label_create(ui_scr->address_book_view_8);
	lv_label_set_text(ui_scr->address_book_lbl_9, "刘浩存");
	lv_label_set_long_mode(ui_scr->address_book_lbl_9, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_9, 30, 32);
	lv_obj_set_size(ui_scr->address_book_lbl_9, 287, 46);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_9, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_9, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_9, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_9, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_11
	ui_scr->address_book_img_11 = lv_img_create(ui_scr->address_book_view_8);
	lv_img_set_src(ui_scr->address_book_img_11, gui_get_res_path(GUI_RES_COMMUNICATION_EDIT_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_11, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_11, 0);
	lv_img_set_zoom(ui_scr->address_book_img_11, 256);
	lv_obj_set_pos(ui_scr->address_book_img_11, 392, 32);
	lv_obj_set_size(ui_scr->address_book_img_11, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_11, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_11, GUI_CTRL_IMG);

	//Write codes address_book_view_7
	ui_scr->address_book_view_7 = lv_obj_create(ui_scr->address_book_view_3);
	lv_obj_set_pos(ui_scr->address_book_view_7, 16, 404);
	lv_obj_set_size(ui_scr->address_book_view_7, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_7, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_7, GUI_CTRL_CONT);

	//Set style for address_book_view_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_view_7, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_view_7, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_7
	ui_scr->address_book_lbl_7 = lv_label_create(ui_scr->address_book_view_7);
	lv_label_set_text(ui_scr->address_book_lbl_7, "迪丽热巴");
	lv_label_set_long_mode(ui_scr->address_book_lbl_7, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_7, 30, 32);
	lv_obj_set_size(ui_scr->address_book_lbl_7, 290, 46);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_7, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_7, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_7, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_9
	ui_scr->address_book_img_9 = lv_img_create(ui_scr->address_book_view_7);
	lv_img_set_src(ui_scr->address_book_img_9, gui_get_res_path(GUI_RES_COMMUNICATION_EDIT_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_9, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_9, 0);
	lv_img_set_zoom(ui_scr->address_book_img_9, 256);
	lv_obj_set_pos(ui_scr->address_book_img_9, 392, 32);
	lv_obj_set_size(ui_scr->address_book_img_9, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_9, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_9, GUI_CTRL_IMG);

	//Write codes address_book_view_6
	ui_scr->address_book_view_6 = lv_obj_create(ui_scr->address_book_view_3);
	lv_obj_set_pos(ui_scr->address_book_view_6, 16, 300);
	lv_obj_set_size(ui_scr->address_book_view_6, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_6, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_6, GUI_CTRL_CONT);

	//Set style for address_book_view_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_view_6, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_view_6, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_5
	ui_scr->address_book_lbl_5 = lv_label_create(ui_scr->address_book_view_6);
	lv_label_set_text(ui_scr->address_book_lbl_5, "古力娜扎");
	lv_label_set_long_mode(ui_scr->address_book_lbl_5, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_5, 30, 32);
	lv_obj_set_size(ui_scr->address_book_lbl_5, 296, 46);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_5, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_5, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_7
	ui_scr->address_book_img_7 = lv_img_create(ui_scr->address_book_view_6);
	lv_img_set_src(ui_scr->address_book_img_7, gui_get_res_path(GUI_RES_COMMUNICATION_EDIT_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_7, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_7, 0);
	lv_img_set_zoom(ui_scr->address_book_img_7, 256);
	lv_obj_set_pos(ui_scr->address_book_img_7, 392, 32);
	lv_obj_set_size(ui_scr->address_book_img_7, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_7, GUI_CTRL_IMG);

	//Write codes address_book_view_5
	ui_scr->address_book_view_5 = lv_obj_create(ui_scr->address_book_view_3);
	lv_obj_set_pos(ui_scr->address_book_view_5, 16, 196);
	lv_obj_set_size(ui_scr->address_book_view_5, 448, 96);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_view_5, GUI_CTRL_CONT);

	//Set style for address_book_view_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_view_5, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_view_5, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_3
	ui_scr->address_book_lbl_3 = lv_label_create(ui_scr->address_book_view_5);
	lv_label_set_text(ui_scr->address_book_lbl_3, "我的手机");
	lv_label_set_long_mode(ui_scr->address_book_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_3, 30, 32);
	lv_obj_set_size(ui_scr->address_book_lbl_3, 291, 46);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_3, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_3, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_5
	ui_scr->address_book_img_5 = lv_img_create(ui_scr->address_book_view_5);
	lv_img_set_src(ui_scr->address_book_img_5, gui_get_res_path(GUI_RES_COMMUNICATION_EDIT_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_5, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_5, 0);
	lv_img_set_zoom(ui_scr->address_book_img_5, 256);
	lv_obj_set_pos(ui_scr->address_book_img_5, 392, 32);
	lv_obj_set_size(ui_scr->address_book_img_5, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_5, GUI_CTRL_IMG);

	//Write codes address_book_view_2
	ui_scr->address_book_view_2 = lv_obj_create(ui_scr->address_book);
	lv_obj_set_pos(ui_scr->address_book_view_2, 0, 32);
	lv_obj_set_size(ui_scr->address_book_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->address_book_view_2, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->address_book_view_2, GUI_CTRL_CONT);

	//Set style for address_book_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->address_book_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->address_book_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_20
	ui_scr->address_book_lbl_20 = lv_label_create(ui_scr->address_book_view_2);
	lv_label_set_long_mode(ui_scr->address_book_lbl_20, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_20, 88, 13);
	lv_obj_set_size(ui_scr->address_book_lbl_20, 384, 40);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_20, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_20, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_20. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_align(ui_scr->address_book_lbl_20, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_27
	ui_scr->address_book_img_27 = lv_img_create(ui_scr->address_book_view_2);
	lv_img_set_src(ui_scr->address_book_img_27, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_27, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_27, 0);
	lv_img_set_zoom(ui_scr->address_book_img_27, 256);
	lv_obj_set_pos(ui_scr->address_book_img_27, 16, 8);
	lv_obj_set_size(ui_scr->address_book_img_27, 56, 56);
	lv_obj_add_flag(ui_scr->address_book_img_27, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_27, GUI_CTRL_IMG);

	//Write codes address_book_view_1
	ui_scr->address_book_view_1 = lv_obj_create(ui_scr->address_book);
	lv_obj_set_pos(ui_scr->address_book_view_1, 0, 0);
	lv_obj_set_size(ui_scr->address_book_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->address_book_view_1, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->address_book_view_1, GUI_CTRL_CONT);

	//Set style for address_book_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->address_book_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_lbl_19
	ui_scr->address_book_lbl_19 = lv_label_create(ui_scr->address_book_view_1);
	lv_label_set_text(ui_scr->address_book_lbl_19, "80%");
	lv_label_set_long_mode(ui_scr->address_book_lbl_19, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_19, 434, 6);
	lv_obj_set_size(ui_scr->address_book_lbl_19, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_19, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_19, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_19. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->address_book_lbl_19, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_img_1
	ui_scr->address_book_img_1 = lv_img_create(ui_scr->address_book_view_1);
	lv_img_set_src(ui_scr->address_book_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_1, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_1, 0);
	lv_img_set_zoom(ui_scr->address_book_img_1, 256);
	lv_obj_set_pos(ui_scr->address_book_img_1, 367, 0);
	lv_obj_set_size(ui_scr->address_book_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_1, GUI_CTRL_IMG);

	//Write codes address_book_img_2
	ui_scr->address_book_img_2 = lv_img_create(ui_scr->address_book_view_1);
	lv_img_set_src(ui_scr->address_book_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_2, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_2, 0);
	lv_img_set_zoom(ui_scr->address_book_img_2, 256);
	lv_obj_set_pos(ui_scr->address_book_img_2, 403, 0);
	lv_obj_set_size(ui_scr->address_book_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_2, GUI_CTRL_IMG);

	//Write codes address_book_img_25
	ui_scr->address_book_img_25 = lv_img_create(ui_scr->address_book_view_1);
	lv_img_set_src(ui_scr->address_book_img_25, gui_get_res_path(GUI_RES_COMMUNICATION_PNG));
	lv_img_set_pivot(ui_scr->address_book_img_25, 0, 0);
	lv_img_set_angle(ui_scr->address_book_img_25, 0);
	lv_img_set_zoom(ui_scr->address_book_img_25, 256);
	lv_obj_set_pos(ui_scr->address_book_img_25, 8, 0);
	lv_obj_set_size(ui_scr->address_book_img_25, 32, 32);
	lv_obj_add_flag(ui_scr->address_book_img_25, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->address_book_img_25, GUI_CTRL_IMG);

	//Write codes address_book_view_4
	ui_scr->address_book_view_4 = lv_obj_create(ui_scr->address_book);
	lv_obj_set_pos(ui_scr->address_book_view_4, 0, 104);
	lv_obj_set_size(ui_scr->address_book_view_4, 480, 92);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_view_4, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->address_book_view_4, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->address_book_view_4, GUI_CTRL_CONT);

	//Set style for address_book_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->address_book_view_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->address_book_view_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes address_book_btn_1
	ui_scr->address_book_btn_1 = lv_btn_create(ui_scr->address_book_view_4);
	lv_obj_set_pos(ui_scr->address_book_btn_1, 16, 16);
	lv_obj_set_size(ui_scr->address_book_btn_1, 448, 60);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_btn_1, LV_SCROLLBAR_MODE_OFF);
	lv_group_remove_obj(ui_scr->address_book_btn_1);
	ui_style_set(ui_scr->address_book_btn_1, GUI_CTRL_BUTTON);

	//Set style for address_book_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->address_book_btn_1, lv_color_make(0xE3, 0xED, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->address_book_btn_1, lv_color_make(0x3B, 0x7D, 0xEE), LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->address_book_btn_1_label = lv_label_create(ui_scr->address_book_btn_1);
	lv_obj_set_style_pad_all(ui_scr->address_book_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->address_book_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes address_book_lbl_1
	ui_scr->address_book_lbl_1 = lv_label_create(ui_scr->address_book);
	lv_label_set_long_mode(ui_scr->address_book_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->address_book_lbl_1, 125, 530);
	lv_obj_set_size(ui_scr->address_book_lbl_1, 230, 85);
	lv_obj_set_scrollbar_mode(ui_scr->address_book_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->address_book_lbl_1, GUI_CTRL_LABEL);

	//Set style for address_book_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->address_book_lbl_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->address_book_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->address_book_lbl_1, 179, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->address_book_lbl_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->address_book_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_scr->address_book_lbl_1, 24, LV_PART_MAIN|LV_STATE_DEFAULT);

	lv_obj_update_layout(ui_scr->address_book);
	ui_scr->address_book_del = false;
	i18n_refresh_texts(GUI_SCREEN_ADDRESS_BOOK);

	//Init events for screen
	events_init_address_book(ui);
	return ui_scr->address_book;
}
void unload_scr_address_book(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_ADDRESS_BOOK);
}

#endif
