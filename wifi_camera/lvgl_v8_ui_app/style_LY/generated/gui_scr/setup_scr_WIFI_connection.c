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


lv_obj_t * setup_scr_WIFI_connection(lv_ui *ui)
{
	lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_WIFI_connection));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_WIFI_connection));
		ui->WIFI_connection = ui_scr;
	}

	//Write codes WIFI_connection
	ui_scr->WIFI_connection = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_connection, GUI_CTRL_SCR);

	//Set style for WIFI_connection. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_grad_color(ui_scr->WIFI_connection, lv_color_make(0x33, 0x5D, 0xD3), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui_scr->WIFI_connection, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_connection_view_2
	ui_scr->WIFI_connection_view_2 = lv_obj_create(ui_scr->WIFI_connection);
	lv_obj_set_pos(ui_scr->WIFI_connection_view_2, 0, 32);
	lv_obj_set_size(ui_scr->WIFI_connection_view_2, 480, 72);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_view_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->WIFI_connection_view_2, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_ONE | LV_OBJ_FLAG_SCROLL_CHAIN_HOR | LV_OBJ_FLAG_SCROLL_CHAIN_VER | LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_SCROLL_ON_FOCUS | LV_OBJ_FLAG_SCROLL_WITH_ARROW);
	ui_style_set(ui_scr->WIFI_connection_view_2, GUI_CTRL_CONT);

	//Set style for WIFI_connection_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->WIFI_connection_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->WIFI_connection_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_connection_lbl_2
	ui_scr->WIFI_connection_lbl_2 = lv_label_create(ui_scr->WIFI_connection_view_2);
	lv_label_set_text(ui_scr->WIFI_connection_lbl_2, "ChinaNet_145nt");
	lv_label_set_long_mode(ui_scr->WIFI_connection_lbl_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->WIFI_connection_lbl_2, 89, 16);
	lv_obj_set_size(ui_scr->WIFI_connection_lbl_2, 513, 40);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_lbl_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_connection_lbl_2, GUI_CTRL_LABEL);

	//Set style for WIFI_connection_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->WIFI_connection_lbl_2, &lv_font_simsun_36, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_scr->WIFI_connection_lbl_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_connection_img_3
	ui_scr->WIFI_connection_img_3 = lv_img_create(ui_scr->WIFI_connection_view_2);
	lv_img_set_src(ui_scr->WIFI_connection_img_3, gui_get_res_path(GUI_RES_BACK_2_PNG));
	lv_img_set_pivot(ui_scr->WIFI_connection_img_3, 0, 0);
	lv_img_set_angle(ui_scr->WIFI_connection_img_3, 0);
	lv_img_set_zoom(ui_scr->WIFI_connection_img_3, 256);
	lv_obj_set_pos(ui_scr->WIFI_connection_img_3, 16, 8);
	lv_obj_set_size(ui_scr->WIFI_connection_img_3, 56, 56);
	lv_obj_add_flag(ui_scr->WIFI_connection_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->WIFI_connection_img_3, GUI_CTRL_IMG);

	//Write codes WIFI_connection_btnm_1
	ui_scr->WIFI_connection_btnm_1 = lv_btnmatrix_create(ui_scr->WIFI_connection);
	static const char *WIFI_connection_btnm_1_text_map[] = {
	"0","1","2","3",
	"4","5","\n","6",
	"7","8","9","!",
	"“","\n","#","$",
	"%","&","`","(",
	"\n",")","*",",",
	"-",",","/","\n",
	":","  ;","<","=",
	">","?","\n","@",
	"[","·","]","^",
	"_","\n",".","{",
	"|","}","~","",
	};
	lv_btnmatrix_set_map(ui_scr->WIFI_connection_btnm_1, WIFI_connection_btnm_1_text_map);
	lv_obj_set_pos(ui_scr->WIFI_connection_btnm_1, 16, 308);
	lv_obj_set_size(ui_scr->WIFI_connection_btnm_1, 448, 448);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_btnm_1, LV_SCROLLBAR_MODE_ON);
	lv_obj_add_flag(ui_scr->WIFI_connection_btnm_1, LV_OBJ_FLAG_SCROLLABLE);

	//Hidden for widget WIFI_connection_btnm_1
	lv_obj_add_flag(ui_scr->WIFI_connection_btnm_1, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->WIFI_connection_btnm_1, GUI_CTRL_BTNMATRIX);

	//Write codes WIFI_connection_edit_2
	ui_scr->WIFI_connection_edit_2 = lv_textarea_create(ui_scr->WIFI_connection);
	lv_obj_set_pos(ui_scr->WIFI_connection_edit_2, 16, 120);
	lv_obj_set_size(ui_scr->WIFI_connection_edit_2, 300, 100);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_edit_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->WIFI_connection_edit_2, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->WIFI_connection_edit_2, GUI_CTRL_TEXTAREA);

	//Write codes WIFI_connection_btnm_2
	ui_scr->WIFI_connection_btnm_2 = lv_btnmatrix_create(ui_scr->WIFI_connection);
	static const char *WIFI_connection_btnm_2_text_map[] = {
	"abc","?12","",};
	lv_btnmatrix_set_map(ui_scr->WIFI_connection_btnm_2, WIFI_connection_btnm_2_text_map);
	lv_obj_set_pos(ui_scr->WIFI_connection_btnm_2, 16, 228);
	lv_obj_set_size(ui_scr->WIFI_connection_btnm_2, 222, 72);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_btnm_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->WIFI_connection_btnm_2, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->WIFI_connection_btnm_2, GUI_CTRL_BTNMATRIX);

	//Set style for WIFI_connection_btnm_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->WIFI_connection_btnm_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->WIFI_connection_btnm_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui_scr->WIFI_connection_btnm_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_recolor(ui_scr->WIFI_connection_btnm_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for WIFI_connection_btnm_2. Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->WIFI_connection_btnm_2, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui_scr->WIFI_connection_btnm_2, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->WIFI_connection_btnm_2, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->WIFI_connection_btnm_2, lv_color_make(0x97, 0xEB, 0x3C), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->WIFI_connection_btnm_2, &lv_font_fangsong_32, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes WIFI_connection_btn_1
	ui_scr->WIFI_connection_btn_1 = lv_btn_create(ui_scr->WIFI_connection);
	lv_obj_set_pos(ui_scr->WIFI_connection_btn_1, 324, 120);
	lv_obj_set_size(ui_scr->WIFI_connection_btn_1, 140, 100);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_btn_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->WIFI_connection_btn_1, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->WIFI_connection_btn_1, GUI_CTRL_BUTTON);

	//Set style for WIFI_connection_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->WIFI_connection_btn_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->WIFI_connection_btn_1, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->WIFI_connection_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->WIFI_connection_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->WIFI_connection_btn_1, -1, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->WIFI_connection_btn_1_label = lv_label_create(ui_scr->WIFI_connection_btn_1);
	lv_obj_set_style_pad_all(ui_scr->WIFI_connection_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->WIFI_connection_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes WIFI_connection_btnm_3
	ui_scr->WIFI_connection_btnm_3 = lv_btnmatrix_create(ui_scr->WIFI_connection);
	static const char *WIFI_connection_btnm_3_text_map[] = {
	"︼","",};
	lv_btnmatrix_set_map(ui_scr->WIFI_connection_btnm_3, WIFI_connection_btnm_3_text_map);
	lv_obj_set_pos(ui_scr->WIFI_connection_btnm_3, 242, 228);
	lv_obj_set_size(ui_scr->WIFI_connection_btnm_3, 109, 72);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_btnm_3, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->WIFI_connection_btnm_3, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->WIFI_connection_btnm_3, GUI_CTRL_BTNMATRIX);

	//Set style for WIFI_connection_btnm_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->WIFI_connection_btnm_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->WIFI_connection_btnm_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui_scr->WIFI_connection_btnm_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui_scr->WIFI_connection_btnm_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_recolor(ui_scr->WIFI_connection_btnm_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for WIFI_connection_btnm_3. Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->WIFI_connection_btnm_3, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui_scr->WIFI_connection_btnm_3, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->WIFI_connection_btnm_3, &lv_font_fangsong_32, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes WIFI_connection_btn_2
	ui_scr->WIFI_connection_btn_2 = lv_btn_create(ui_scr->WIFI_connection);
	lv_obj_set_pos(ui_scr->WIFI_connection_btn_2, 355, 228);
	lv_obj_set_size(ui_scr->WIFI_connection_btn_2, 109, 72);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_btn_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->WIFI_connection_btn_2, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->WIFI_connection_btn_2, GUI_CTRL_BUTTON);

	//Set style for WIFI_connection_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->WIFI_connection_btn_2, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->WIFI_connection_btn_2, lv_color_make(0x5F, 0x93, 0xE8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->WIFI_connection_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->WIFI_connection_btn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->WIFI_connection_btn_2_label = lv_label_create(ui_scr->WIFI_connection_btn_2);
	lv_obj_set_style_pad_all(ui_scr->WIFI_connection_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->WIFI_connection_btn_2_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes WIFI_connection_btnm_4
	ui_scr->WIFI_connection_btnm_4 = lv_btnmatrix_create(ui_scr->WIFI_connection);
	static const char *WIFI_connection_btnm_4_text_map[] = {
	"a","b","c","d",
	"e","f","\n","g",
	"h","i","j","k",
	"l","\n","m","n",
	"o","p","q","r",
	"\n","s","t","u",
	"v","w","x","\n",
	"y","z","",};
	lv_btnmatrix_set_map(ui_scr->WIFI_connection_btnm_4, WIFI_connection_btnm_4_text_map);
	lv_obj_set_pos(ui_scr->WIFI_connection_btnm_4, 16, 308);
	lv_obj_set_size(ui_scr->WIFI_connection_btnm_4, 448, 296);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_btnm_4, LV_SCROLLBAR_MODE_ON);

	//Hidden for widget WIFI_connection_btnm_4
	lv_obj_add_flag(ui_scr->WIFI_connection_btnm_4, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->WIFI_connection_btnm_4, GUI_CTRL_BTNMATRIX);

	//Write codes WIFI_connection_btnm_5
	ui_scr->WIFI_connection_btnm_5 = lv_btnmatrix_create(ui_scr->WIFI_connection);
	static const char *WIFI_connection_btnm_5_text_map[] = {
	"A","B","C","D",
	"E","F","\n","G",
	"H","I","J","K",
	"L","\n","M","N",
	"O","P","Q","R",
	"\n","S","T","U",
	"V","W","X","\n",
	"Y","Z","",};
	lv_btnmatrix_set_map(ui_scr->WIFI_connection_btnm_5, WIFI_connection_btnm_5_text_map);
	lv_obj_set_pos(ui_scr->WIFI_connection_btnm_5, 16, 308);
	lv_obj_set_size(ui_scr->WIFI_connection_btnm_5, 448, 296);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_btnm_5, LV_SCROLLBAR_MODE_ON);
	ui_style_set(ui_scr->WIFI_connection_btnm_5, GUI_CTRL_BTNMATRIX);

	//Write codes WIFI_connection_view_1
	ui_scr->WIFI_connection_view_1 = lv_obj_create(ui_scr->WIFI_connection);
	lv_obj_set_pos(ui_scr->WIFI_connection_view_1, 0, 0);
	lv_obj_set_size(ui_scr->WIFI_connection_view_1, 480, 32);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_connection_view_1, GUI_CTRL_CONT);

	//Set style for WIFI_connection_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->WIFI_connection_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_connection_lbl_1
	ui_scr->WIFI_connection_lbl_1 = lv_label_create(ui_scr->WIFI_connection_view_1);
	lv_label_set_text(ui_scr->WIFI_connection_lbl_1, "80%");
	lv_label_set_long_mode(ui_scr->WIFI_connection_lbl_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->WIFI_connection_lbl_1, 435, 6);
	lv_obj_set_size(ui_scr->WIFI_connection_lbl_1, 41, 23);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_lbl_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->WIFI_connection_lbl_1, GUI_CTRL_LABEL);

	//Set style for WIFI_connection_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_text_font(ui_scr->WIFI_connection_lbl_1, &lv_font_simsun_20, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes WIFI_connection_img_1
	ui_scr->WIFI_connection_img_1 = lv_img_create(ui_scr->WIFI_connection_view_1);
	lv_img_set_src(ui_scr->WIFI_connection_img_1, gui_get_res_path(GUI_RES_WIFI_4_PNG));
	lv_img_set_pivot(ui_scr->WIFI_connection_img_1, 0, 0);
	lv_img_set_angle(ui_scr->WIFI_connection_img_1, 0);
	lv_img_set_zoom(ui_scr->WIFI_connection_img_1, 256);
	lv_obj_set_pos(ui_scr->WIFI_connection_img_1, 367, 0);
	lv_obj_set_size(ui_scr->WIFI_connection_img_1, 32, 32);
	lv_obj_add_flag(ui_scr->WIFI_connection_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->WIFI_connection_img_1, GUI_CTRL_IMG);

	//Write codes WIFI_connection_img_2
	ui_scr->WIFI_connection_img_2 = lv_img_create(ui_scr->WIFI_connection_view_1);
	lv_img_set_src(ui_scr->WIFI_connection_img_2, gui_get_res_path(GUI_RES_3_PNG));
	lv_img_set_pivot(ui_scr->WIFI_connection_img_2, 0, 0);
	lv_img_set_angle(ui_scr->WIFI_connection_img_2, 0);
	lv_img_set_zoom(ui_scr->WIFI_connection_img_2, 256);
	lv_obj_set_pos(ui_scr->WIFI_connection_img_2, 402, 0);
	lv_obj_set_size(ui_scr->WIFI_connection_img_2, 32, 32);
	lv_obj_add_flag(ui_scr->WIFI_connection_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->WIFI_connection_img_2, GUI_CTRL_IMG);

	//Write codes WIFI_connection_lbl_3
	ui_scr->WIFI_connection_lbl_3 = lv_label_create(ui_scr->WIFI_connection);
	lv_label_set_long_mode(ui_scr->WIFI_connection_lbl_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui_scr->WIFI_connection_lbl_3, 125, 530);
	lv_obj_set_size(ui_scr->WIFI_connection_lbl_3, 230, 85);
	lv_obj_set_scrollbar_mode(ui_scr->WIFI_connection_lbl_3, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget WIFI_connection_lbl_3
	lv_obj_add_flag(ui_scr->WIFI_connection_lbl_3, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->WIFI_connection_lbl_3, GUI_CTRL_LABEL);

	//Set style for WIFI_connection_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->WIFI_connection_lbl_3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->WIFI_connection_lbl_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->WIFI_connection_lbl_3, 179, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->WIFI_connection_lbl_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_scr->WIFI_connection_lbl_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_scr->WIFI_connection_lbl_3, 24, LV_PART_MAIN|LV_STATE_DEFAULT);

	lv_obj_update_layout(ui_scr->WIFI_connection);
	ui_scr->WIFI_connection_del = false;
	i18n_refresh_texts(GUI_SCREEN_WIFI_CONNECTION);

	//Init events for screen
	events_init_WIFI_connection(ui);
	return ui_scr->WIFI_connection;
}
void unload_scr_WIFI_connection(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_WIFI_CONNECTION);
}

#endif
