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


lv_obj_t * setup_scr_video_dir_landscape_mode(lv_ui *ui)
{
	lv_ui_video_dir_landscape_mode * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_video_dir_landscape_mode));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_video_dir_landscape_mode));
		ui->video_dir_landscape_mode = ui_scr;
	}

	//Write codes video_dir_landscape_mode
	ui_scr->video_dir_landscape_mode = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->video_dir_landscape_mode, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->video_dir_landscape_mode, GUI_CTRL_SCR);

	//Set style for video_dir_landscape_mode. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_dir_landscape_mode, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_dir_landscape_mode_img_6
	ui_scr->video_dir_landscape_mode_img_6 = lv_img_create(ui_scr->video_dir_landscape_mode);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_6, 0, 0);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_6, 480, 640);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_6, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_view_2
	ui_scr->video_dir_landscape_mode_view_2 = lv_obj_create(ui_scr->video_dir_landscape_mode);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_view_2, 408, 0);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_view_2, 72, 640);
	lv_obj_set_scrollbar_mode(ui_scr->video_dir_landscape_mode_view_2, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->video_dir_landscape_mode_view_2, GUI_CTRL_CONT);

	//Set style for video_dir_landscape_mode_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->video_dir_landscape_mode_view_2, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_scr->video_dir_landscape_mode_view_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_dir_landscape_mode_img_1
	ui_scr->video_dir_landscape_mode_img_1 = lv_img_create(ui_scr->video_dir_landscape_mode_view_2);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_1, gui_get_res_path(GUI_RES_BACK_1_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_1, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_1, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_1, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_1, 8, 16);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_1, 56, 56);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_1, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_2
	ui_scr->video_dir_landscape_mode_img_2 = lv_img_create(ui_scr->video_dir_landscape_mode_view_2);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_2, gui_get_res_path(GUI_RES_IMAGE_2242091_0_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_2, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_2, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_2, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_2, 19, 83);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_2, 34, 70);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_2, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_7
	ui_scr->video_dir_landscape_mode_img_7 = lv_img_create(ui_scr->video_dir_landscape_mode);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_7, gui_get_res_path(GUI_RES_DELETED_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_7, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_7, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_7, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_7, 124, 560);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_7, 64, 64);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_7, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_view_4
	ui_scr->video_dir_landscape_mode_view_4 = lv_obj_create(ui_scr->video_dir_landscape_mode);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_view_4, 0, 0);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_view_4, 102, 640);
	lv_obj_set_scrollbar_mode(ui_scr->video_dir_landscape_mode_view_4, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->video_dir_landscape_mode_view_4, GUI_CTRL_CONT);

	//Set style for video_dir_landscape_mode_view_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->video_dir_landscape_mode_view_4, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_scr->video_dir_landscape_mode_view_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_dir_landscape_mode_view_1
	ui_scr->video_dir_landscape_mode_view_1 = lv_obj_create(ui_scr->video_dir_landscape_mode);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_view_1, 0, 0);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_view_1, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->video_dir_landscape_mode_view_1, LV_SCROLLBAR_MODE_OFF);

	//Hidden for widget video_dir_landscape_mode_view_1
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_view_1, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->video_dir_landscape_mode_view_1, GUI_CTRL_CONT);

	//Set style for video_dir_landscape_mode_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->video_dir_landscape_mode_view_1, 179, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_dir_landscape_mode_img_8
	ui_scr->video_dir_landscape_mode_img_8 = lv_img_create(ui_scr->video_dir_landscape_mode_view_1);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_8, gui_get_res_path(GUI_RES_BG_POP_1_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_8, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_8, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_8, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_8, 60, 108);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_8, 320, 428);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_8, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_8, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_3
	ui_scr->video_dir_landscape_mode_img_3 = lv_img_create(ui_scr->video_dir_landscape_mode_view_1);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_3, gui_get_res_path(GUI_RES_SURE_BTN_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_3, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_3, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_3, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_3, 96, 136);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_3, 66, 180);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_3, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_4
	ui_scr->video_dir_landscape_mode_img_4 = lv_img_create(ui_scr->video_dir_landscape_mode_view_1);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_4, gui_get_res_path(GUI_RES_CANCEL_BTN_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_4, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_4, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_4, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_4, 96, 328);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_4, 66, 180);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_4, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_12
	ui_scr->video_dir_landscape_mode_img_12 = lv_img_create(ui_scr->video_dir_landscape_mode_view_1);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_12, gui_get_res_path(GUI_RES_TEXT_COPYWRITING_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_12, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_12, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_12, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_12, 210, 178);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_12, 26, 291);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_12, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_12, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_11
	ui_scr->video_dir_landscape_mode_img_11 = lv_img_create(ui_scr->video_dir_landscape_mode_view_1);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_11, gui_get_res_path(GUI_RES_TEXT_TITLE_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_11, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_11, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_11, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_11, 256, 250);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_11, 30, 126);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_11, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_11, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_9
	ui_scr->video_dir_landscape_mode_img_9 = lv_img_create(ui_scr->video_dir_landscape_mode_view_1);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_9, gui_get_res_path(GUI_RES_HOME_ALBUM_1_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_9, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_9, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_9, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_9, 290, 240);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_9, 150, 150);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_9, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_9, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_10
	ui_scr->video_dir_landscape_mode_img_10 = lv_img_create(ui_scr->video_dir_landscape_mode_view_1);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_10, gui_get_res_path(GUI_RES_IMAGE_7991533_0_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_10, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_10, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_10, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_10, 339, 498);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_10, 48, 48);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_10, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_10, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_13
	ui_scr->video_dir_landscape_mode_img_13 = lv_img_create(ui_scr->video_dir_landscape_mode);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_13, gui_get_res_path(GUI_RES_TEXT_DELETED_IMG_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_13, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_13, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_13, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_13, 108, 248);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_13, 129, 144);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_13, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget video_dir_landscape_mode_img_13
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_13, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_13, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_14
	ui_scr->video_dir_landscape_mode_img_14 = lv_img_create(ui_scr->video_dir_landscape_mode);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_14, gui_get_res_path(GUI_RES_TEXT_LOADING_IMG_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_14, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_14, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_14, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_14, 108, 248);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_14, 129, 144);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_14, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget video_dir_landscape_mode_img_14
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_14, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->video_dir_landscape_mode_img_14, GUI_CTRL_IMG);

	//Write codes video_dir_landscape_mode_img_15
	ui_scr->video_dir_landscape_mode_img_15 = lv_img_create(ui_scr->video_dir_landscape_mode);
	lv_img_set_src(ui_scr->video_dir_landscape_mode_img_15, gui_get_res_path(GUI_RES_IMAGE_3532909_0_PNG));
	lv_img_set_pivot(ui_scr->video_dir_landscape_mode_img_15, 0, 0);
	lv_img_set_angle(ui_scr->video_dir_landscape_mode_img_15, 0);
	lv_img_set_zoom(ui_scr->video_dir_landscape_mode_img_15, 256);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_img_15, 216, 296);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_img_15, 48, 48);
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_15, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget video_dir_landscape_mode_img_15
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_img_15, LV_OBJ_FLAG_HIDDEN);

	//Write codes video_dir_landscape_mode_btn_1
	ui_scr->video_dir_landscape_mode_btn_1 = lv_btn_create(ui_scr->video_dir_landscape_mode);
	lv_obj_set_pos(ui_scr->video_dir_landscape_mode_btn_1, 296, 18);
	lv_obj_set_size(ui_scr->video_dir_landscape_mode_btn_1, 1, 1);
	lv_obj_set_scrollbar_mode(ui_scr->video_dir_landscape_mode_btn_1, LV_SCROLLBAR_MODE_OFF);
	lv_group_remove_obj(ui_scr->video_dir_landscape_mode_btn_1);

	//Hidden for widget video_dir_landscape_mode_btn_1
	lv_obj_add_flag(ui_scr->video_dir_landscape_mode_btn_1, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->video_dir_landscape_mode_btn_1, GUI_CTRL_BUTTON);

	//Set style for video_dir_landscape_mode_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->video_dir_landscape_mode_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->video_dir_landscape_mode_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_dir_landscape_mode_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->video_dir_landscape_mode_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->video_dir_landscape_mode_btn_1, &lv_font_simsun_32, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->video_dir_landscape_mode_btn_1_label = lv_label_create(ui_scr->video_dir_landscape_mode_btn_1);
	lv_label_set_text(ui_scr->video_dir_landscape_mode_btn_1_label, "");
	lv_obj_set_style_pad_all(ui_scr->video_dir_landscape_mode_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->video_dir_landscape_mode_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	lv_obj_update_layout(ui_scr->video_dir_landscape_mode);
	ui_scr->video_dir_landscape_mode_del = false;
	i18n_refresh_texts(GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);

	//Init events for screen
	events_init_video_dir_landscape_mode(ui);
	return ui_scr->video_dir_landscape_mode;
}
void unload_scr_video_dir_landscape_mode(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_DIR_LANDSCAPE_MODE);
}

#endif
