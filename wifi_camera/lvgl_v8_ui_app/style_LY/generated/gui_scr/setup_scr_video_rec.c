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


lv_obj_t * setup_scr_video_rec(lv_ui *ui)
{
	lv_ui_video_rec * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_video_rec));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_video_rec));
		ui->video_rec = ui_scr;
	}

	//Write codes video_rec
	ui_scr->video_rec = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->video_rec, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->video_rec, GUI_CTRL_SCR);

	//Set style for video_rec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_rec, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_rec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->video_rec, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_rec_img_1
	ui_scr->video_rec_img_1 = lv_img_create(ui_scr->video_rec);
	lv_img_set_src(ui_scr->video_rec_img_1, gui_get_res_path(GUI_RES_BACK_PNG));
	lv_img_set_pivot(ui_scr->video_rec_img_1, 0, 0);
	lv_img_set_angle(ui_scr->video_rec_img_1, 0);
	lv_img_set_zoom(ui_scr->video_rec_img_1, 256);
	lv_obj_set_pos(ui_scr->video_rec_img_1, 376, 9);
	lv_obj_set_size(ui_scr->video_rec_img_1, 56, 56);
	lv_obj_add_flag(ui_scr->video_rec_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_rec_img_1, GUI_CTRL_IMG);

	//Set style for video_rec_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_outline_color(ui_scr->video_rec_img_1, lv_color_make(0xE9, 0x1E, 0x63), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui_scr->video_rec_img_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_rec_btn_1
	ui_scr->video_rec_btn_1 = lv_btn_create(ui_scr->video_rec);
	lv_obj_set_pos(ui_scr->video_rec_btn_1, 396, 553);
	lv_obj_set_size(ui_scr->video_rec_btn_1, 1, 1);
	lv_obj_set_scrollbar_mode(ui_scr->video_rec_btn_1, LV_SCROLLBAR_MODE_OFF);
	lv_group_remove_obj(ui_scr->video_rec_btn_1);

	//Hidden for widget video_rec_btn_1
	lv_obj_add_flag(ui_scr->video_rec_btn_1, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->video_rec_btn_1, GUI_CTRL_BUTTON);

	//Set style for video_rec_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->video_rec_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->video_rec_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_rec_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->video_rec_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->video_rec_btn_1, &lv_font_simsun_32, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->video_rec_btn_1_label = lv_label_create(ui_scr->video_rec_btn_1);
	lv_label_set_text(ui_scr->video_rec_btn_1_label, "录像");
	lv_obj_set_style_pad_all(ui_scr->video_rec_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->video_rec_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes video_rec_img_2
	ui_scr->video_rec_img_2 = lv_img_create(ui_scr->video_rec);
	lv_img_set_src(ui_scr->video_rec_img_2, gui_get_res_path(GUI_RES_VIDEO_REC_PNG));
	lv_img_set_pivot(ui_scr->video_rec_img_2, 0, 0);
	lv_img_set_angle(ui_scr->video_rec_img_2, 0);
	lv_img_set_zoom(ui_scr->video_rec_img_2, 256);
	lv_obj_set_pos(ui_scr->video_rec_img_2, 457, 8);
	lv_obj_set_size(ui_scr->video_rec_img_2, 15, 58);
	lv_obj_add_flag(ui_scr->video_rec_img_2, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget video_rec_img_2
	lv_obj_add_flag(ui_scr->video_rec_img_2, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->video_rec_img_2, GUI_CTRL_IMG);

	//Write codes video_rec_view_1
	ui_scr->video_rec_view_1 = lv_obj_create(ui_scr->video_rec);
	lv_obj_set_pos(ui_scr->video_rec_view_1, 457, 82);
	lv_obj_set_size(ui_scr->video_rec_view_1, 16, 96);
	lv_obj_set_scrollbar_mode(ui_scr->video_rec_view_1, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget video_rec_view_1
	lv_obj_add_flag(ui_scr->video_rec_view_1, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->video_rec_view_1, GUI_CTRL_CONT);

	//Set style for video_rec_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_rec_view_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_rec_view_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_rec_img_9
	ui_scr->video_rec_img_9 = lv_img_create(ui_scr->video_rec_view_1);
	lv_img_set_src(ui_scr->video_rec_img_9, gui_get_res_path(GUI_RES_IMG_0_PNG));
	lv_img_set_pivot(ui_scr->video_rec_img_9, 0, 0);
	lv_img_set_angle(ui_scr->video_rec_img_9, 0);
	lv_img_set_zoom(ui_scr->video_rec_img_9, 256);
	lv_obj_set_pos(ui_scr->video_rec_img_9, 0, 72);
	lv_obj_set_size(ui_scr->video_rec_img_9, 16, 12);
	lv_obj_add_flag(ui_scr->video_rec_img_9, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_rec_img_9, GUI_CTRL_IMG);

	//Write codes video_rec_img_4
	ui_scr->video_rec_img_4 = lv_img_create(ui_scr->video_rec_view_1);
	lv_img_set_src(ui_scr->video_rec_img_4, gui_get_res_path(GUI_RES_IMG_0_PNG));
	lv_img_set_pivot(ui_scr->video_rec_img_4, 0, 0);
	lv_img_set_angle(ui_scr->video_rec_img_4, 0);
	lv_img_set_zoom(ui_scr->video_rec_img_4, 256);
	lv_obj_set_pos(ui_scr->video_rec_img_4, 0, 12);
	lv_obj_set_size(ui_scr->video_rec_img_4, 16, 12);
	lv_obj_add_flag(ui_scr->video_rec_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_rec_img_4, GUI_CTRL_IMG);

	//Write codes video_rec_img_3
	ui_scr->video_rec_img_3 = lv_img_create(ui_scr->video_rec_view_1);
	lv_img_set_src(ui_scr->video_rec_img_3, gui_get_res_path(GUI_RES_IMG_0_PNG));
	lv_img_set_pivot(ui_scr->video_rec_img_3, 0, 0);
	lv_img_set_angle(ui_scr->video_rec_img_3, 0);
	lv_img_set_zoom(ui_scr->video_rec_img_3, 256);
	lv_obj_set_pos(ui_scr->video_rec_img_3, 0, 0);
	lv_obj_set_size(ui_scr->video_rec_img_3, 16, 12);
	lv_obj_add_flag(ui_scr->video_rec_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_rec_img_3, GUI_CTRL_IMG);

	//Write codes video_rec_img_5
	ui_scr->video_rec_img_5 = lv_img_create(ui_scr->video_rec_view_1);
	lv_img_set_src(ui_scr->video_rec_img_5, gui_get_res_path(GUI_RES_IMAGE_2154541_0_PNG));
	lv_img_set_pivot(ui_scr->video_rec_img_5, 0, 0);
	lv_img_set_angle(ui_scr->video_rec_img_5, 0);
	lv_img_set_zoom(ui_scr->video_rec_img_5, 256);
	lv_obj_set_pos(ui_scr->video_rec_img_5, 0, 24);
	lv_obj_set_size(ui_scr->video_rec_img_5, 16, 12);
	lv_obj_add_flag(ui_scr->video_rec_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_rec_img_5, GUI_CTRL_IMG);

	//Write codes video_rec_img_6
	ui_scr->video_rec_img_6 = lv_img_create(ui_scr->video_rec_view_1);
	lv_img_set_src(ui_scr->video_rec_img_6, gui_get_res_path(GUI_RES_IMG_0_PNG));
	lv_img_set_pivot(ui_scr->video_rec_img_6, 0, 0);
	lv_img_set_angle(ui_scr->video_rec_img_6, 0);
	lv_img_set_zoom(ui_scr->video_rec_img_6, 256);
	lv_obj_set_pos(ui_scr->video_rec_img_6, 0, 36);
	lv_obj_set_size(ui_scr->video_rec_img_6, 16, 12);
	lv_obj_add_flag(ui_scr->video_rec_img_6, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_rec_img_6, GUI_CTRL_IMG);

	//Write codes video_rec_img_7
	ui_scr->video_rec_img_7 = lv_img_create(ui_scr->video_rec_view_1);
	lv_img_set_src(ui_scr->video_rec_img_7, gui_get_res_path(GUI_RES_IMG_0_PNG));
	lv_img_set_pivot(ui_scr->video_rec_img_7, 0, 0);
	lv_img_set_angle(ui_scr->video_rec_img_7, 0);
	lv_img_set_zoom(ui_scr->video_rec_img_7, 256);
	lv_obj_set_pos(ui_scr->video_rec_img_7, 0, 48);
	lv_obj_set_size(ui_scr->video_rec_img_7, 16, 12);
	lv_obj_add_flag(ui_scr->video_rec_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_rec_img_7, GUI_CTRL_IMG);

	//Write codes video_rec_img_8
	ui_scr->video_rec_img_8 = lv_img_create(ui_scr->video_rec_view_1);
	lv_img_set_src(ui_scr->video_rec_img_8, gui_get_res_path(GUI_RES_IMAGE_2154541_0_PNG));
	lv_img_set_pivot(ui_scr->video_rec_img_8, 0, 0);
	lv_img_set_angle(ui_scr->video_rec_img_8, 0);
	lv_img_set_zoom(ui_scr->video_rec_img_8, 256);
	lv_obj_set_pos(ui_scr->video_rec_img_8, 0, 60);
	lv_obj_set_size(ui_scr->video_rec_img_8, 16, 12);
	lv_obj_add_flag(ui_scr->video_rec_img_8, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_rec_img_8, GUI_CTRL_IMG);

	//Write codes video_rec_img_10
	ui_scr->video_rec_img_10 = lv_img_create(ui_scr->video_rec_view_1);
	lv_img_set_src(ui_scr->video_rec_img_10, gui_get_res_path(GUI_RES_IMG_0_PNG));
	lv_img_set_pivot(ui_scr->video_rec_img_10, 0, 0);
	lv_img_set_angle(ui_scr->video_rec_img_10, 0);
	lv_img_set_zoom(ui_scr->video_rec_img_10, 256);
	lv_obj_set_pos(ui_scr->video_rec_img_10, 0, 84);
	lv_obj_set_size(ui_scr->video_rec_img_10, 16, 12);
	lv_obj_add_flag(ui_scr->video_rec_img_10, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_rec_img_10, GUI_CTRL_IMG);

	lv_obj_update_layout(ui_scr->video_rec);
	ui_scr->video_rec_del = false;
	i18n_refresh_texts(GUI_SCREEN_VIDEO_REC);

	//Init events for screen
	events_init_video_rec(ui);
	return ui_scr->video_rec;
}
void unload_scr_video_rec(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_REC);
}

#endif
