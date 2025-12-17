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


lv_obj_t * setup_scr_chat_page(lv_ui *ui)
{
	lv_ui_chat_page * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_CHAT_PAGE);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_chat_page));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_chat_page));
		ui->chat_page = ui_scr;
	}

	//Write codes chat_page
	ui_scr->chat_page = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->chat_page, GUI_CTRL_SCR);

	//Write codes chat_page_view_5
	ui_scr->chat_page_view_5 = lv_obj_create(ui_scr->chat_page);
	lv_obj_set_pos(ui_scr->chat_page_view_5, 0, 0);
	lv_obj_set_size(ui_scr->chat_page_view_5, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_view_5, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->chat_page_view_5, GUI_CTRL_CONT);

	//Set style for chat_page_view_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->chat_page_view_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->chat_page_view_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes chat_page_view_4
	ui_scr->chat_page_view_4 = lv_obj_create(ui_scr->chat_page);
	lv_obj_set_pos(ui_scr->chat_page_view_4, 0, 536);
	lv_obj_set_size(ui_scr->chat_page_view_4, 480, 104);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_view_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->chat_page_view_4, GUI_CTRL_CONT);

	//Set style for chat_page_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->chat_page_view_4, lv_color_make(0x08, 0x2B, 0x8E), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes chat_page_view_2
	ui_scr->chat_page_view_2 = lv_obj_create(ui_scr->chat_page);
	lv_obj_set_pos(ui_scr->chat_page_view_2, 0, 32);
	lv_obj_set_size(ui_scr->chat_page_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_view_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->chat_page_view_2, GUI_CTRL_CONT);

	//Set style for chat_page_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->chat_page_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->chat_page_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes chat_page_lbl_1
	ui_scr->chat_page_lbl_1 = lv_label_create(ui_scr->chat_page_view_2);
	lv_label_set_long_mode(ui_scr->chat_page_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->chat_page_lbl_1, 88, 15);
	lv_obj_set_size(ui_scr->chat_page_lbl_1, 342, 49);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->chat_page_lbl_1, GUI_CTRL_LABEL);

	//Set style for chat_page_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_opa(ui_scr->chat_page_lbl_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->chat_page_lbl_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->chat_page_lbl_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes chat_page_img_6
	ui_scr->chat_page_img_6 = lv_img_create(ui_scr->chat_page_view_2);
	lv_img_set_src(ui_scr->chat_page_img_6, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->chat_page_img_6, 0, 0);
	lv_img_set_angle(ui_scr->chat_page_img_6, 0);
	lv_img_set_zoom(ui_scr->chat_page_img_6, 256);
	lv_obj_set_pos(ui_scr->chat_page_img_6, 16, 8);
	lv_obj_set_size(ui_scr->chat_page_img_6, 56, 56);
	lv_obj_add_flag(ui_scr->chat_page_img_6, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->chat_page_img_6, GUI_CTRL_IMG);

	//Write codes chat_page_img_8
	ui_scr->chat_page_img_8 = lv_img_create(ui_scr->chat_page_view_2);
	lv_img_set_src(ui_scr->chat_page_img_8, gui_get_res_path(GUI_RES_CALL_PNG));
	lv_img_set_pivot(ui_scr->chat_page_img_8, 0, 0);
	lv_img_set_angle(ui_scr->chat_page_img_8, 0);
	lv_img_set_zoom(ui_scr->chat_page_img_8, 256);
	lv_obj_set_pos(ui_scr->chat_page_img_8, 408, 8);
	lv_obj_set_size(ui_scr->chat_page_img_8, 56, 56);
	lv_obj_add_flag(ui_scr->chat_page_img_8, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->chat_page_img_8, GUI_CTRL_IMG);

	//Write codes chat_page_view_1
	ui_scr->chat_page_view_1 = lv_obj_create(ui_scr->chat_page);
	lv_obj_set_pos(ui_scr->chat_page_view_1, 0, 0);
	lv_obj_set_size(ui_scr->chat_page_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->chat_page_view_1, GUI_CTRL_CONT);

	//Set style for chat_page_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->chat_page_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes chat_page_lbl_3
	ui_scr->chat_page_lbl_3 = lv_label_create(ui_scr->chat_page_view_1);
	lv_label_set_text(ui_scr->chat_page_lbl_3, "80%");
	lv_label_set_long_mode(ui_scr->chat_page_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->chat_page_lbl_3, 435, 6);
	lv_obj_set_size(ui_scr->chat_page_lbl_3, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_lbl_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->chat_page_lbl_3, GUI_CTRL_LABEL);

	//Set style for chat_page_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->chat_page_lbl_3, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes chat_page_img_1
	ui_scr->chat_page_img_1 = lv_img_create(ui_scr->chat_page_view_1);
	lv_img_set_src(ui_scr->chat_page_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->chat_page_img_1, 0, 0);
	lv_img_set_angle(ui_scr->chat_page_img_1, 0);
	lv_img_set_zoom(ui_scr->chat_page_img_1, 256);
	lv_obj_set_pos(ui_scr->chat_page_img_1, 367, 0);
	lv_obj_set_size(ui_scr->chat_page_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->chat_page_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->chat_page_img_1, GUI_CTRL_IMG);

	//Write codes chat_page_img_2
	ui_scr->chat_page_img_2 = lv_img_create(ui_scr->chat_page_view_1);
	lv_img_set_src(ui_scr->chat_page_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->chat_page_img_2, 0, 0);
	lv_img_set_angle(ui_scr->chat_page_img_2, 0);
	lv_img_set_zoom(ui_scr->chat_page_img_2, 256);
	lv_obj_set_pos(ui_scr->chat_page_img_2, 403, 0);
	lv_obj_set_size(ui_scr->chat_page_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->chat_page_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->chat_page_img_2, GUI_CTRL_IMG);

	//Write codes chat_page_img_5
	ui_scr->chat_page_img_5 = lv_img_create(ui_scr->chat_page_view_1);
	lv_img_set_src(ui_scr->chat_page_img_5, gui_get_res_path(GUI_RES_COMMUNICATION_PNG));
	lv_img_set_pivot(ui_scr->chat_page_img_5, 0, 0);
	lv_img_set_angle(ui_scr->chat_page_img_5, 0);
	lv_img_set_zoom(ui_scr->chat_page_img_5, 256);
	lv_obj_set_pos(ui_scr->chat_page_img_5, 8, 0);
	lv_obj_set_size(ui_scr->chat_page_img_5, 32, 32);
	lv_obj_add_flag(ui_scr->chat_page_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->chat_page_img_5, GUI_CTRL_IMG);

	//Write codes chat_page_btn_1
	ui_scr->chat_page_btn_1 = lv_btn_create(ui_scr->chat_page);
	lv_obj_set_pos(ui_scr->chat_page_btn_1, 24, 552);
	lv_obj_set_size(ui_scr->chat_page_btn_1, 432, 72);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_btn_1, LV_SCROLLBAR_MODE_OFF);
	lv_group_remove_obj(ui_scr->chat_page_btn_1);
	ui_style_set(ui_scr->chat_page_btn_1, GUI_CTRL_BUTTON);
	ui_scr->chat_page_btn_1_label = lv_label_create(ui_scr->chat_page_btn_1);
	lv_obj_set_style_pad_all(ui_scr->chat_page_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->chat_page_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes chat_page_view_3
	ui_scr->chat_page_view_3 = lv_obj_create(ui_scr->chat_page);
	lv_obj_set_pos(ui_scr->chat_page_view_3, 17, 517);
	lv_obj_set_size(ui_scr->chat_page_view_3, 446, 107);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_view_3, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget chat_page_view_3
	lv_obj_add_flag(ui_scr->chat_page_view_3, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->chat_page_view_3, GUI_CTRL_CONT);

	//Set style for chat_page_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->chat_page_view_3, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->chat_page_view_3, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes chat_page_gif_1
	ui_scr->chat_page_gif_1 = lv_gif_create(ui_scr->chat_page_view_3);
	lv_obj_set_pos(ui_scr->chat_page_gif_1, 23, 0);
	lv_obj_set_size(ui_scr->chat_page_gif_1, 400, 107);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_gif_1, LV_SCROLLBAR_MODE_OFF);
	lv_gif_set_src(ui_scr->chat_page_gif_1, gui_get_res_path(GUI_RES_EZGIF_3F026D4EC0A484F1_GIF));

	//Write codes chat_page_view_6
	ui_scr->chat_page_view_6 = lv_obj_create(ui_scr->chat_page);
	lv_obj_set_pos(ui_scr->chat_page_view_6, 0, 0);
	lv_obj_set_size(ui_scr->chat_page_view_6, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_view_6, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget chat_page_view_6
	lv_obj_add_flag(ui_scr->chat_page_view_6, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->chat_page_view_6, GUI_CTRL_CONT);

	//Set style for chat_page_view_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->chat_page_view_6, 179, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes chat_page_img_3
	ui_scr->chat_page_img_3 = lv_img_create(ui_scr->chat_page_view_6);
	lv_img_set_src(ui_scr->chat_page_img_3, gui_get_res_path(GUI_RES_BG_POP_PNG));
	lv_img_set_pivot(ui_scr->chat_page_img_3, 0, 0);
	lv_img_set_angle(ui_scr->chat_page_img_3, 0);
	lv_img_set_zoom(ui_scr->chat_page_img_3, 256);
	lv_obj_set_pos(ui_scr->chat_page_img_3, 18, 190);
	lv_obj_set_size(ui_scr->chat_page_img_3, 445, 320);
	lv_obj_add_flag(ui_scr->chat_page_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->chat_page_img_3, GUI_CTRL_IMG);

	//Write codes chat_page_lbl_2
	ui_scr->chat_page_lbl_2 = lv_label_create(ui_scr->chat_page_view_6);
	lv_label_set_long_mode(ui_scr->chat_page_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->chat_page_lbl_2, 56, 313);
	lv_obj_set_size(ui_scr->chat_page_lbl_2, 370, 52);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->chat_page_lbl_2, GUI_CTRL_LABEL);

	//Set style for chat_page_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_color(ui_scr->chat_page_lbl_2, lv_color_make(0x82, 0x4A, 0x1B), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes chat_page_img_4
	ui_scr->chat_page_img_4 = lv_img_create(ui_scr->chat_page_view_6);
	lv_img_set_src(ui_scr->chat_page_img_4, gui_get_res_path(GUI_RES_HOME_ERROR_PNG));
	lv_img_set_pivot(ui_scr->chat_page_img_4, 0, 0);
	lv_img_set_angle(ui_scr->chat_page_img_4, 0);
	lv_img_set_zoom(ui_scr->chat_page_img_4, 256);
	lv_obj_set_pos(ui_scr->chat_page_img_4, 165, 128);
	lv_obj_set_size(ui_scr->chat_page_img_4, 150, 150);
	lv_obj_add_flag(ui_scr->chat_page_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->chat_page_img_4, GUI_CTRL_IMG);

	//Write codes chat_page_btn_3
	ui_scr->chat_page_btn_3 = lv_btn_create(ui_scr->chat_page_view_6);
	lv_obj_set_pos(ui_scr->chat_page_btn_3, 56, 408);
	lv_obj_set_size(ui_scr->chat_page_btn_3, 368, 62);
	lv_obj_set_scrollbar_mode(ui_scr->chat_page_btn_3, LV_SCROLLBAR_MODE_OFF);
	lv_group_remove_obj(ui_scr->chat_page_btn_3);
	ui_style_set(ui_scr->chat_page_btn_3, GUI_CTRL_BUTTON);

	//Set style for chat_page_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_shadow_width(ui_scr->chat_page_btn_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui_scr->chat_page_btn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->chat_page_btn_3, 64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui_scr->chat_page_btn_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->chat_page_btn_3_label = lv_label_create(ui_scr->chat_page_btn_3);
	lv_obj_set_style_pad_all(ui_scr->chat_page_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->chat_page_btn_3_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes chat_page_img_7
	ui_scr->chat_page_img_7 = lv_img_create(ui_scr->chat_page_view_6);
	lv_img_set_src(ui_scr->chat_page_img_7, gui_get_res_path(GUI_RES_IMAGE_7991533_0_PNG));
	lv_img_set_pivot(ui_scr->chat_page_img_7, 0, 0);
	lv_img_set_angle(ui_scr->chat_page_img_7, 0);
	lv_img_set_zoom(ui_scr->chat_page_img_7, 256);
	lv_obj_set_pos(ui_scr->chat_page_img_7, 418, 181);
	lv_obj_set_size(ui_scr->chat_page_img_7, 48, 48);
	lv_obj_add_flag(ui_scr->chat_page_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->chat_page_img_7, GUI_CTRL_IMG);

	lv_obj_update_layout(ui_scr->chat_page);
	ui_scr->chat_page_del = false;
	i18n_refresh_texts(GUI_SCREEN_CHAT_PAGE);

	//Init events for screen
	events_init_chat_page(ui);
	return ui_scr->chat_page;
}
void unload_scr_chat_page(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_CHAT_PAGE);
}

#endif
