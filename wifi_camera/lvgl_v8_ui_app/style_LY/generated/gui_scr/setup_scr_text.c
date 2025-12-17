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


lv_obj_t * setup_scr_text(lv_ui *ui)
{
	lv_ui_text * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_TEXT);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_text));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_text));
		ui->text = ui_scr;
	}

	//Write codes text
	ui_scr->text = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->text, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->text, GUI_CTRL_SCR);

	//Set style for text. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->text, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes text_btn_1
	ui_scr->text_btn_1 = lv_btn_create(ui_scr->text);
	lv_obj_set_pos(ui_scr->text_btn_1, 98, 319);
	lv_obj_set_size(ui_scr->text_btn_1, 110, 59);
	lv_obj_set_scrollbar_mode(ui_scr->text_btn_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->text_btn_1, GUI_CTRL_BUTTON);

	//Set style for text_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->text_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->text_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->text_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->text_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->text_btn_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->text_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->text_btn_1, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->text_btn_1_label = lv_label_create(ui_scr->text_btn_1);
	lv_label_set_text(ui_scr->text_btn_1_label, "拨打");
	lv_obj_set_style_pad_all(ui_scr->text_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->text_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes text_btn_2
	ui_scr->text_btn_2 = lv_btn_create(ui_scr->text);
	lv_obj_set_pos(ui_scr->text_btn_2, 272, 318);
	lv_obj_set_size(ui_scr->text_btn_2, 104, 60);
	lv_obj_set_scrollbar_mode(ui_scr->text_btn_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->text_btn_2, GUI_CTRL_BUTTON);

	//Set style for text_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->text_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->text_btn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->text_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->text_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->text_btn_2, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->text_btn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->text_btn_2, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->text_btn_2_label = lv_label_create(ui_scr->text_btn_2);
	lv_label_set_text(ui_scr->text_btn_2_label, "接听");
	lv_obj_set_style_pad_all(ui_scr->text_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->text_btn_2_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes text_btn_3
	ui_scr->text_btn_3 = lv_btn_create(ui_scr->text);
	lv_obj_set_pos(ui_scr->text_btn_3, 98, 423);
	lv_obj_set_size(ui_scr->text_btn_3, 85, 65);
	lv_obj_set_scrollbar_mode(ui_scr->text_btn_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->text_btn_3, GUI_CTRL_BUTTON);

	//Set style for text_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->text_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->text_btn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->text_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->text_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->text_btn_3, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->text_btn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->text_btn_3, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->text_btn_3_label = lv_label_create(ui_scr->text_btn_3);
	lv_label_set_text(ui_scr->text_btn_3_label, "挂断");
	lv_obj_set_style_pad_all(ui_scr->text_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->text_btn_3_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes text_btn_4
	ui_scr->text_btn_4 = lv_btn_create(ui_scr->text);
	lv_obj_set_pos(ui_scr->text_btn_4, 68, 41);
	lv_obj_set_size(ui_scr->text_btn_4, 96, 61);
	lv_obj_set_scrollbar_mode(ui_scr->text_btn_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->text_btn_4, GUI_CTRL_BUTTON);

	//Set style for text_btn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->text_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->text_btn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->text_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->text_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->text_btn_4, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->text_btn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->text_btn_4, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->text_btn_4_label = lv_label_create(ui_scr->text_btn_4);
	lv_label_set_text(ui_scr->text_btn_4_label, "返回");
	lv_obj_set_style_pad_all(ui_scr->text_btn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->text_btn_4_label, LV_ALIGN_CENTER, 0, 0);

	lv_obj_update_layout(ui_scr->text);
	ui_scr->text_del = false;
	i18n_refresh_texts(GUI_SCREEN_TEXT);

	//Init events for screen
	events_init_text(ui);
	return ui_scr->text;
}
void unload_scr_text(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_TEXT);
}

#endif
