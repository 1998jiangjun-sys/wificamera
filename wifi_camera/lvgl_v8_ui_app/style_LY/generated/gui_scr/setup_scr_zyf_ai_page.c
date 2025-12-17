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


lv_obj_t * setup_scr_zyf_ai_page(lv_ui *ui)
{
	lv_ui_zyf_ai_page * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_ZYF_AI_PAGE);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_zyf_ai_page));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_zyf_ai_page));
		ui->zyf_ai_page = ui_scr;
	}

	//Write codes zyf_ai_page
	ui_scr->zyf_ai_page = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->zyf_ai_page, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->zyf_ai_page, GUI_CTRL_SCR);

	//Set style for zyf_ai_page. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->zyf_ai_page, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->zyf_ai_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes zyf_ai_page_view_1
	ui_scr->zyf_ai_page_view_1 = lv_obj_create(ui_scr->zyf_ai_page);
	lv_obj_set_pos(ui_scr->zyf_ai_page_view_1, 0, 0);
	lv_obj_set_size(ui_scr->zyf_ai_page_view_1, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->zyf_ai_page_view_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->zyf_ai_page_view_1, GUI_CTRL_CONT);

	//Set style for zyf_ai_page_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->zyf_ai_page_view_1, lv_color_make(0xDF, 0xBB, 0x20), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->zyf_ai_page_view_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_scr->zyf_ai_page_view_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->zyf_ai_page_view_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->zyf_ai_page_view_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes zyf_ai_page_img_1
	ui_scr->zyf_ai_page_img_1 = lv_img_create(ui_scr->zyf_ai_page_view_1);
	lv_img_set_src(ui_scr->zyf_ai_page_img_1, gui_get_res_path(GUI_RES_BACK_3_PNG));
	lv_img_set_pivot(ui_scr->zyf_ai_page_img_1, 0, 0);
	lv_img_set_angle(ui_scr->zyf_ai_page_img_1, 0);
	lv_img_set_zoom(ui_scr->zyf_ai_page_img_1, 256);
	lv_obj_set_pos(ui_scr->zyf_ai_page_img_1, 16, 40);
	lv_obj_set_size(ui_scr->zyf_ai_page_img_1, 56, 56);
	lv_obj_add_flag(ui_scr->zyf_ai_page_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->zyf_ai_page_img_1, GUI_CTRL_IMG);

	//Write codes zyf_ai_page_btn_1
	ui_scr->zyf_ai_page_btn_1 = lv_btn_create(ui_scr->zyf_ai_page_view_1);
	lv_obj_set_pos(ui_scr->zyf_ai_page_btn_1, 24, 552);
	lv_obj_set_size(ui_scr->zyf_ai_page_btn_1, 432, 72);
	lv_obj_set_scrollbar_mode(ui_scr->zyf_ai_page_btn_1, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->zyf_ai_page_btn_1, GUI_CTRL_BUTTON);

	//Set style for zyf_ai_page_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->zyf_ai_page_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui_scr->zyf_ai_page_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->zyf_ai_page_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->zyf_ai_page_btn_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->zyf_ai_page_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->zyf_ai_page_btn_1, &lv_font_simsun_32, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->zyf_ai_page_btn_1_label = lv_label_create(ui_scr->zyf_ai_page_btn_1);
	lv_label_set_text(ui_scr->zyf_ai_page_btn_1_label, "起飞");
	lv_obj_set_style_pad_all(ui_scr->zyf_ai_page_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->zyf_ai_page_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	lv_obj_update_layout(ui_scr->zyf_ai_page);
	ui_scr->zyf_ai_page_del = false;
	i18n_refresh_texts(GUI_SCREEN_ZYF_AI_PAGE);

	//Init events for screen
	events_init_zyf_ai_page(ui);
	return ui_scr->zyf_ai_page;
}
void unload_scr_zyf_ai_page(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_ZYF_AI_PAGE);
}

#endif
