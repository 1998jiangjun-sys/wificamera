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


lv_obj_t * setup_scr_Edit_Friend_Info(lv_ui *ui)
{
	lv_ui_Edit_Friend_Info * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_EDIT_FRIEND_INFO);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_Edit_Friend_Info));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_Edit_Friend_Info));
		ui->Edit_Friend_Info = ui_scr;
	}

	//Write codes Edit_Friend_Info
	ui_scr->Edit_Friend_Info = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info, GUI_CTRL_SCR);

	//Write codes Edit_Friend_Info_view_5
	ui_scr->Edit_Friend_Info_view_5 = lv_obj_create(ui_scr->Edit_Friend_Info);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_view_5, 0, 0);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_view_5, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info_view_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info_view_5, GUI_CTRL_CONT);

	//Set style for Edit_Friend_Info_view_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->Edit_Friend_Info_view_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->Edit_Friend_Info_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Edit_Friend_Info_view_2
	ui_scr->Edit_Friend_Info_view_2 = lv_obj_create(ui_scr->Edit_Friend_Info);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_view_2, 0, 32);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info_view_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info_view_2, GUI_CTRL_CONT);

	//Set style for Edit_Friend_Info_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->Edit_Friend_Info_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->Edit_Friend_Info_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Edit_Friend_Info_lbl_1
	ui_scr->Edit_Friend_Info_lbl_1 = lv_label_create(ui_scr->Edit_Friend_Info_view_2);
	lv_label_set_long_mode(ui_scr->Edit_Friend_Info_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_lbl_1, 88, 15);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_lbl_1, 342, 49);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info_lbl_1, GUI_CTRL_LABEL);

	//Set style for Edit_Friend_Info_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->Edit_Friend_Info_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->Edit_Friend_Info_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->Edit_Friend_Info_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Edit_Friend_Info_img_6
	ui_scr->Edit_Friend_Info_img_6 = lv_img_create(ui_scr->Edit_Friend_Info_view_2);
	lv_img_set_src(ui_scr->Edit_Friend_Info_img_6, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->Edit_Friend_Info_img_6, 0, 0);
	lv_img_set_angle(ui_scr->Edit_Friend_Info_img_6, 0);
	lv_img_set_zoom(ui_scr->Edit_Friend_Info_img_6, 256);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_img_6, 16, 8);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_img_6, 56, 56);
	lv_obj_add_flag(ui_scr->Edit_Friend_Info_img_6, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Edit_Friend_Info_img_6, GUI_CTRL_IMG);

	//Write codes Edit_Friend_Info_view_1
	ui_scr->Edit_Friend_Info_view_1 = lv_obj_create(ui_scr->Edit_Friend_Info);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_view_1, 0, 0);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info_view_1, GUI_CTRL_CONT);

	//Set style for Edit_Friend_Info_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->Edit_Friend_Info_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Edit_Friend_Info_lbl_3
	ui_scr->Edit_Friend_Info_lbl_3 = lv_label_create(ui_scr->Edit_Friend_Info_view_1);
	lv_label_set_text(ui_scr->Edit_Friend_Info_lbl_3, "80%");
	lv_label_set_long_mode(ui_scr->Edit_Friend_Info_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_lbl_3, 435, 6);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_lbl_3, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info_lbl_3, GUI_CTRL_LABEL);

	//Set style for Edit_Friend_Info_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->Edit_Friend_Info_lbl_3, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Edit_Friend_Info_img_1
	ui_scr->Edit_Friend_Info_img_1 = lv_img_create(ui_scr->Edit_Friend_Info_view_1);
	lv_img_set_src(ui_scr->Edit_Friend_Info_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->Edit_Friend_Info_img_1, 0, 0);
	lv_img_set_angle(ui_scr->Edit_Friend_Info_img_1, 0);
	lv_img_set_zoom(ui_scr->Edit_Friend_Info_img_1, 256);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_img_1, 367, 0);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->Edit_Friend_Info_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Edit_Friend_Info_img_1, GUI_CTRL_IMG);

	//Write codes Edit_Friend_Info_img_2
	ui_scr->Edit_Friend_Info_img_2 = lv_img_create(ui_scr->Edit_Friend_Info_view_1);
	lv_img_set_src(ui_scr->Edit_Friend_Info_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->Edit_Friend_Info_img_2, 0, 0);
	lv_img_set_angle(ui_scr->Edit_Friend_Info_img_2, 0);
	lv_img_set_zoom(ui_scr->Edit_Friend_Info_img_2, 256);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_img_2, 403, 0);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->Edit_Friend_Info_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Edit_Friend_Info_img_2, GUI_CTRL_IMG);

	//Write codes Edit_Friend_Info_img_5
	ui_scr->Edit_Friend_Info_img_5 = lv_img_create(ui_scr->Edit_Friend_Info_view_1);
	lv_img_set_src(ui_scr->Edit_Friend_Info_img_5, gui_get_res_path(GUI_RES_AI_PNG));
	lv_img_set_pivot(ui_scr->Edit_Friend_Info_img_5, 0, 0);
	lv_img_set_angle(ui_scr->Edit_Friend_Info_img_5, 0);
	lv_img_set_zoom(ui_scr->Edit_Friend_Info_img_5, 256);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_img_5, 8, 0);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_img_5, 32, 32);
	lv_obj_add_flag(ui_scr->Edit_Friend_Info_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Edit_Friend_Info_img_5, GUI_CTRL_IMG);

	//Write codes Edit_Friend_Info_view_7
	ui_scr->Edit_Friend_Info_view_7 = lv_obj_create(ui_scr->Edit_Friend_Info);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_view_7, 16, 164);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_view_7, 448, 416);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info_view_7, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info_view_7, GUI_CTRL_CONT);

	//Set style for Edit_Friend_Info_view_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Edit_Friend_Info_view_7, 24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Edit_Friend_Info_view_7, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_scr->Edit_Friend_Info_view_7, lv_color_make(0xE3, 0xED, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_scr->Edit_Friend_Info_view_7, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->Edit_Friend_Info_view_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Edit_Friend_Info_btn_2
	ui_scr->Edit_Friend_Info_btn_2 = lv_btn_create(ui_scr->Edit_Friend_Info_view_7);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_btn_2, 227, 272);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_btn_2, 154, 72);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info_btn_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info_btn_2, GUI_CTRL_BUTTON);

	//Set style for Edit_Friend_Info_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Edit_Friend_Info_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Edit_Friend_Info_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->Edit_Friend_Info_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->Edit_Friend_Info_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->Edit_Friend_Info_btn_2, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->Edit_Friend_Info_btn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->Edit_Friend_Info_btn_2, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->Edit_Friend_Info_btn_2_label = lv_label_create(ui_scr->Edit_Friend_Info_btn_2);
	lv_label_set_text(ui_scr->Edit_Friend_Info_btn_2_label, "button");
	lv_obj_set_style_pad_all(ui_scr->Edit_Friend_Info_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->Edit_Friend_Info_btn_2_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes Edit_Friend_Info_btn_1
	ui_scr->Edit_Friend_Info_btn_1 = lv_btn_create(ui_scr->Edit_Friend_Info_view_7);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_btn_1, 48, 290);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_btn_1, 137, 54);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info_btn_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info_btn_1, GUI_CTRL_BUTTON);

	//Set style for Edit_Friend_Info_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Edit_Friend_Info_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Edit_Friend_Info_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->Edit_Friend_Info_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->Edit_Friend_Info_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->Edit_Friend_Info_btn_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->Edit_Friend_Info_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->Edit_Friend_Info_btn_1, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->Edit_Friend_Info_btn_1_label = lv_label_create(ui_scr->Edit_Friend_Info_btn_1);
	lv_label_set_text(ui_scr->Edit_Friend_Info_btn_1_label, "button");
	lv_obj_set_style_pad_all(ui_scr->Edit_Friend_Info_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->Edit_Friend_Info_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes Edit_Friend_Info_edit_1
	ui_scr->Edit_Friend_Info_edit_1 = lv_textarea_create(ui_scr->Edit_Friend_Info_view_7);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_edit_1, 17, 112);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_edit_1, 400, 80);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info_edit_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info_edit_1, GUI_CTRL_TEXTAREA);

	//Set style for Edit_Friend_Info_edit_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_grad_color(ui_scr->Edit_Friend_Info_edit_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->Edit_Friend_Info_edit_1, &lv_font_simsun_32, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->Edit_Friend_Info_edit_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_scr->Edit_Friend_Info_edit_1, 24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_scr->Edit_Friend_Info_edit_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_scr->Edit_Friend_Info_edit_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_textarea_set_text(ui_scr->Edit_Friend_Info_edit_1,"请输入好友备注");

	//Write codes Edit_Friend_Info_img_4
	ui_scr->Edit_Friend_Info_img_4 = lv_img_create(ui_scr->Edit_Friend_Info);
	lv_img_set_src(ui_scr->Edit_Friend_Info_img_4, gui_get_res_path(GUI_RES_COMMUNICATION_DOWN_PNG));
	lv_img_set_pivot(ui_scr->Edit_Friend_Info_img_4, 0, 0);
	lv_img_set_angle(ui_scr->Edit_Friend_Info_img_4, 0);
	lv_img_set_zoom(ui_scr->Edit_Friend_Info_img_4, 256);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_img_4, 384, 384);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_img_4, 32, 32);
	lv_obj_add_flag(ui_scr->Edit_Friend_Info_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->Edit_Friend_Info_img_4, GUI_CTRL_IMG);

	//Write codes Edit_Friend_Info_ddlist_1
	ui_scr->Edit_Friend_Info_ddlist_1 = lv_dropdown_create(ui_scr->Edit_Friend_Info);
	lv_dropdown_set_options(ui_scr->Edit_Friend_Info_ddlist_1, "list1\nlist2\nlist3");
	lv_dropdown_set_dir(ui_scr->Edit_Friend_Info_ddlist_1, LV_DIR_BOTTOM);
	lv_dropdown_set_symbol(ui_scr->Edit_Friend_Info_ddlist_1, LV_SYMBOL_DOWN);
	lv_dropdown_set_selected(ui_scr->Edit_Friend_Info_ddlist_1, 0);
	lv_obj_set_pos(ui_scr->Edit_Friend_Info_ddlist_1, 40, 200);
	lv_obj_set_size(ui_scr->Edit_Friend_Info_ddlist_1, 386, 60);
	lv_obj_set_scrollbar_mode(ui_scr->Edit_Friend_Info_ddlist_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->Edit_Friend_Info_ddlist_1, GUI_CTRL_DROPDOWN);

	//Set style for Edit_Friend_Info_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->Edit_Friend_Info_ddlist_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->Edit_Friend_Info_ddlist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui_scr->Edit_Friend_Info_ddlist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->Edit_Friend_Info_ddlist_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->Edit_Friend_Info_ddlist_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->Edit_Friend_Info_ddlist_1, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->Edit_Friend_Info_ddlist_1, &lv_font_simsun_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_scr->Edit_Friend_Info_ddlist_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_CHECKED for style_edit_friend_info_ddlist_1_extra_list_selected_checked
	static lv_style_t style_edit_friend_info_ddlist_1_extra_list_selected_checked;
	ui_init_style(&style_edit_friend_info_ddlist_1_extra_list_selected_checked);
	lv_style_set_bg_color(&style_edit_friend_info_ddlist_1_extra_list_selected_checked, lv_color_make(0xB0, 0xB8, 0xB8));
	lv_style_set_bg_opa(&style_edit_friend_info_ddlist_1_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_edit_friend_info_ddlist_1_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_edit_friend_info_ddlist_1_extra_list_selected_checked, 1);
	lv_style_set_border_side(&style_edit_friend_info_ddlist_1_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_text_font(&style_edit_friend_info_ddlist_1_extra_list_selected_checked, &lv_font_simsun_12);
	lv_obj_add_style(lv_dropdown_get_list(ui_scr->Edit_Friend_Info_ddlist_1), &gui_ddlist_selected_checked_style, LV_PART_SELECTED|LV_STATE_CHECKED);
	lv_obj_add_style(lv_dropdown_get_list(ui_scr->Edit_Friend_Info_ddlist_1), &style_edit_friend_info_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_edit_friend_info_ddlist_1_extra_list_main_default
	static lv_style_t style_edit_friend_info_ddlist_1_extra_list_main_default;
	ui_init_style(&style_edit_friend_info_ddlist_1_extra_list_main_default);
	lv_style_set_bg_color(&style_edit_friend_info_ddlist_1_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_edit_friend_info_ddlist_1_extra_list_main_default, 255);
	lv_style_set_border_side(&style_edit_friend_info_ddlist_1_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_text_color(&style_edit_friend_info_ddlist_1_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_edit_friend_info_ddlist_1_extra_list_main_default, &lv_font_simsun_12);
	lv_style_set_max_height(&style_edit_friend_info_ddlist_1_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(ui_scr->Edit_Friend_Info_ddlist_1), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(lv_dropdown_get_list(ui_scr->Edit_Friend_Info_ddlist_1), &style_edit_friend_info_ddlist_1_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_edit_friend_info_ddlist_1_extra_list_scrollbar_default
	static lv_style_t style_edit_friend_info_ddlist_1_extra_list_scrollbar_default;
	ui_init_style(&style_edit_friend_info_ddlist_1_extra_list_scrollbar_default);
	lv_style_set_bg_opa(&style_edit_friend_info_ddlist_1_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui_scr->Edit_Friend_Info_ddlist_1), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_add_style(lv_dropdown_get_list(ui_scr->Edit_Friend_Info_ddlist_1), &style_edit_friend_info_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Delete extra default style for Edit_Friend_Info_ddlist_1
	lv_obj_remove_style(ui_scr->Edit_Friend_Info_ddlist_1, &gui_ddlist_selected_checked_style, LV_PART_SELECTED|LV_STATE_CHECKED);
	lv_obj_remove_style(ui_scr->Edit_Friend_Info_ddlist_1, &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_remove_style(ui_scr->Edit_Friend_Info_ddlist_1, &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_remove_style(ui_scr->Edit_Friend_Info_ddlist_1, &gui_ddlist_main_focus_key_style, LV_PART_MAIN|LV_STATE_FOCUS_KEY);

	lv_obj_update_layout(ui_scr->Edit_Friend_Info);
	ui_scr->Edit_Friend_Info_del = false;
	i18n_refresh_texts(GUI_SCREEN_EDIT_FRIEND_INFO);

	//Init events for screen
	events_init_Edit_Friend_Info(ui);
	return ui_scr->Edit_Friend_Info;
}
void unload_scr_Edit_Friend_Info(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_EDIT_FRIEND_INFO);
}

#endif
