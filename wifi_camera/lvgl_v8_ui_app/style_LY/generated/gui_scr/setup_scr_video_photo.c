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


lv_obj_t * setup_scr_video_photo(lv_ui *ui)
{
	lv_ui_video_photo * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_video_photo));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_video_photo));
		ui->video_photo = ui_scr;
	}

	//Write codes video_photo
	ui_scr->video_photo = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->video_photo, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->video_photo, GUI_CTRL_SCR);

	//Set style for video_photo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_photo, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo, 5, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_view_2
	ui_scr->video_photo_view_2 = lv_obj_create(ui_scr->video_photo);
	lv_obj_set_pos(ui_scr->video_photo_view_2, 0, 0);
	lv_obj_set_size(ui_scr->video_photo_view_2, 480, 640);
	lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->video_photo_view_2, LV_OBJ_FLAG_SCROLLABLE);

	//Hidden for widget video_photo_view_2
	lv_obj_add_flag(ui_scr->video_photo_view_2, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->video_photo_view_2, GUI_CTRL_CONT);

	//Set style for video_photo_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_photo_view_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo_view_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_img_3
	ui_scr->video_photo_img_3 = lv_img_create(ui_scr->video_photo_view_2);
	lv_img_set_src(ui_scr->video_photo_img_3, gui_get_res_path(GUI_RES_PHOTOGRAPH_CLOSE_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_3, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_3, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_3, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_3, 112, 600);
	lv_obj_set_size(ui_scr->video_photo_img_3, 32, 32);
	lv_obj_add_flag(ui_scr->video_photo_img_3, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_3, GUI_CTRL_IMG);

	//Write codes video_photo_img_1
	ui_scr->video_photo_img_1 = lv_img_create(ui_scr->video_photo_view_2);
	lv_img_set_src(ui_scr->video_photo_img_1, gui_get_res_path(GUI_RES_PHOTOGRAPH_LEFT_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_1, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_1, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_1, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_1, 208, 8);
	lv_obj_set_size(ui_scr->video_photo_img_1, 64, 64);
	lv_obj_add_flag(ui_scr->video_photo_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_1, GUI_CTRL_IMG);

	//Write codes video_photo_img_2
	ui_scr->video_photo_img_2 = lv_img_create(ui_scr->video_photo_view_2);
	lv_img_set_src(ui_scr->video_photo_img_2, gui_get_res_path(GUI_RES_PHOTOGRAPH_NEXT_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_2, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_2, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_2, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_2, 208, 569);
	lv_obj_set_size(ui_scr->video_photo_img_2, 64, 64);
	lv_obj_add_flag(ui_scr->video_photo_img_2, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_2, GUI_CTRL_IMG);

	//Write codes video_photo_view_3
	ui_scr->video_photo_view_3 = lv_obj_create(ui_scr->video_photo_view_2);
	lv_obj_set_pos(ui_scr->video_photo_view_3, 0, 0);
	lv_obj_set_size(ui_scr->video_photo_view_3, 104, 640);
	lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_3, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->video_photo_view_3, GUI_CTRL_CONT);

	//Set style for video_photo_view_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->video_photo_view_3, 64, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_img_6
	ui_scr->video_photo_img_6 = lv_img_create(ui_scr->video_photo_view_3);
	lv_img_set_src(ui_scr->video_photo_img_6, gui_get_res_path(GUI_RES_STICKER_3_72_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_6, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_6, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_6, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_6, 16, 192);
	lv_obj_set_size(ui_scr->video_photo_img_6, 72, 72);
	lv_obj_add_flag(ui_scr->video_photo_img_6, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_6, GUI_CTRL_IMG);

	//Set style for video_photo_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_photo_img_6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo_img_6, 64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->video_photo_img_6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->video_photo_img_6, 64, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_img_5
	ui_scr->video_photo_img_5 = lv_img_create(ui_scr->video_photo_view_3);
	lv_img_set_src(ui_scr->video_photo_img_5, gui_get_res_path(GUI_RES_STICKER_2_72_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_5, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_5, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_5, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_5, 16, 104);
	lv_obj_set_size(ui_scr->video_photo_img_5, 72, 72);
	lv_obj_add_flag(ui_scr->video_photo_img_5, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_5, GUI_CTRL_IMG);

	//Set style for video_photo_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_photo_img_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo_img_5, 64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->video_photo_img_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->video_photo_img_5, 64, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_img_4
	ui_scr->video_photo_img_4 = lv_img_create(ui_scr->video_photo_view_3);
	lv_img_set_src(ui_scr->video_photo_img_4, gui_get_res_path(GUI_RES_STICKER_1_72_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_4, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_4, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_4, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_4, 16, 16);
	lv_obj_set_size(ui_scr->video_photo_img_4, 72, 72);
	lv_obj_add_flag(ui_scr->video_photo_img_4, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_4, GUI_CTRL_IMG);

	//Set style for video_photo_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_photo_img_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo_img_4, 64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->video_photo_img_4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui_scr->video_photo_img_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->video_photo_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_img_7
	ui_scr->video_photo_img_7 = lv_img_create(ui_scr->video_photo_view_3);
	lv_img_set_src(ui_scr->video_photo_img_7, gui_get_res_path(GUI_RES_STICKER_4_72_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_7, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_7, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_7, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_7, 16, 280);
	lv_obj_set_size(ui_scr->video_photo_img_7, 72, 72);
	lv_obj_add_flag(ui_scr->video_photo_img_7, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_7, GUI_CTRL_IMG);

	//Set style for video_photo_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_photo_img_7, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo_img_7, 64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->video_photo_img_7, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->video_photo_img_7, 64, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_img_8
	ui_scr->video_photo_img_8 = lv_img_create(ui_scr->video_photo_view_3);
	lv_img_set_src(ui_scr->video_photo_img_8, gui_get_res_path(GUI_RES_STICKER_5_72_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_8, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_8, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_8, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_8, 16, 368);
	lv_obj_set_size(ui_scr->video_photo_img_8, 72, 72);
	lv_obj_add_flag(ui_scr->video_photo_img_8, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_8, GUI_CTRL_IMG);

	//Set style for video_photo_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_photo_img_8, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo_img_8, 64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->video_photo_img_8, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->video_photo_img_8, 64, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_img_9
	ui_scr->video_photo_img_9 = lv_img_create(ui_scr->video_photo_view_3);
	lv_img_set_src(ui_scr->video_photo_img_9, gui_get_res_path(GUI_RES_STICKER_6_72_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_9, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_9, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_9, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_9, 16, 456);
	lv_obj_set_size(ui_scr->video_photo_img_9, 72, 72);
	lv_obj_add_flag(ui_scr->video_photo_img_9, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_9, GUI_CTRL_IMG);

	//Set style for video_photo_img_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_photo_img_9, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo_img_9, 64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->video_photo_img_9, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->video_photo_img_9, 64, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_img_10
	ui_scr->video_photo_img_10 = lv_img_create(ui_scr->video_photo_view_3);
	lv_img_set_src(ui_scr->video_photo_img_10, gui_get_res_path(GUI_RES_STICKER_8_72_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_10, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_10, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_10, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_10, 16, 544);
	lv_obj_set_size(ui_scr->video_photo_img_10, 72, 72);
	lv_obj_add_flag(ui_scr->video_photo_img_10, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_10, GUI_CTRL_IMG);

	//Set style for video_photo_img_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_photo_img_10, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo_img_10, 64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->video_photo_img_10, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->video_photo_img_10, 64, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_img_11
	ui_scr->video_photo_img_11 = lv_img_create(ui_scr->video_photo_view_3);
	lv_img_set_src(ui_scr->video_photo_img_11, gui_get_res_path(GUI_RES_STICKER_7_72_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_11, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_11, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_11, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_11, 16, 632);
	lv_obj_set_size(ui_scr->video_photo_img_11, 72, 72);
	lv_obj_add_flag(ui_scr->video_photo_img_11, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_11, GUI_CTRL_IMG);

	//Set style for video_photo_img_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->video_photo_img_11, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo_img_11, 64, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_scr->video_photo_img_11, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->video_photo_img_11, 64, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_view_1
	ui_scr->video_photo_view_1 = lv_obj_create(ui_scr->video_photo);
	lv_obj_set_pos(ui_scr->video_photo_view_1, 448, 0);
	lv_obj_set_size(ui_scr->video_photo_view_1, 32, 640);
	lv_obj_set_scrollbar_mode(ui_scr->video_photo_view_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_clear_flag(ui_scr->video_photo_view_1, LV_OBJ_FLAG_SCROLLABLE);
	ui_style_set(ui_scr->video_photo_view_1, GUI_CTRL_CONT);

	//Set style for video_photo_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->video_photo_view_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_img_24
	ui_scr->video_photo_img_24 = lv_img_create(ui_scr->video_photo_view_1);
	lv_img_set_src(ui_scr->video_photo_img_24, gui_get_res_path(GUI_RES_PHOTOGRAPH_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_24, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_24, 900);
	lv_img_set_zoom(ui_scr->video_photo_img_24, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_24, 32, 8);
	lv_obj_set_size(ui_scr->video_photo_img_24, 32, 32);
	lv_obj_add_flag(ui_scr->video_photo_img_24, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_24, GUI_CTRL_IMG);

	//Write codes video_photo_img_13
	ui_scr->video_photo_img_13 = lv_img_create(ui_scr->video_photo);
	lv_img_set_src(ui_scr->video_photo_img_13, gui_get_res_path(GUI_RES_BACK_1_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_13, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_13, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_13, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_13, 376, 9);
	lv_obj_set_size(ui_scr->video_photo_img_13, 56, 56);
	lv_obj_add_flag(ui_scr->video_photo_img_13, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_13, GUI_CTRL_IMG);

	//Set style for video_photo_img_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_outline_color(ui_scr->video_photo_img_13, lv_color_make(0xE9, 0x1E, 0x63), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui_scr->video_photo_img_13, 10, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes video_photo_btn_1
	ui_scr->video_photo_btn_1 = lv_btn_create(ui_scr->video_photo);
	lv_obj_set_pos(ui_scr->video_photo_btn_1, 374, 427);
	lv_obj_set_size(ui_scr->video_photo_btn_1, 1, 1);
	lv_obj_set_scrollbar_mode(ui_scr->video_photo_btn_1, LV_SCROLLBAR_MODE_OFF);
	lv_group_remove_obj(ui_scr->video_photo_btn_1);
	ui_style_set(ui_scr->video_photo_btn_1, GUI_CTRL_BUTTON);

	//Set style for video_photo_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui_scr->video_photo_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_scr->video_photo_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_scr->video_photo_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui_scr->video_photo_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_scr->video_photo_btn_1, &lv_font_simsun_32, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui_scr->video_photo_btn_1_label = lv_label_create(ui_scr->video_photo_btn_1);
	lv_label_set_text(ui_scr->video_photo_btn_1_label, "");
	lv_obj_set_style_pad_all(ui_scr->video_photo_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_align(ui_scr->video_photo_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes video_photo_img_26
	ui_scr->video_photo_img_26 = lv_img_create(ui_scr->video_photo);
	lv_img_set_src(ui_scr->video_photo_img_26, gui_get_res_path(GUI_RES_PHOTOGRAPH_NARROW_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_26, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_26, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_26, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_26, 384, 576);
	lv_obj_set_size(ui_scr->video_photo_img_26, 32, 32);
	lv_obj_add_flag(ui_scr->video_photo_img_26, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget video_photo_img_26
	lv_obj_add_flag(ui_scr->video_photo_img_26, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->video_photo_img_26, GUI_CTRL_IMG);

	//Write codes video_photo_img_25
	ui_scr->video_photo_img_25 = lv_img_create(ui_scr->video_photo);
	lv_img_set_src(ui_scr->video_photo_img_25, gui_get_res_path(GUI_RES_PHOTOGRAPH_ENLARGE_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_25, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_25, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_25, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_25, 384, 532);
	lv_obj_set_size(ui_scr->video_photo_img_25, 32, 32);
	lv_obj_add_flag(ui_scr->video_photo_img_25, LV_OBJ_FLAG_CLICKABLE);

	//Hidden for widget video_photo_img_25
	lv_obj_add_flag(ui_scr->video_photo_img_25, LV_OBJ_FLAG_HIDDEN);
	ui_style_set(ui_scr->video_photo_img_25, GUI_CTRL_IMG);

	//Write codes video_photo_img_12
	ui_scr->video_photo_img_12 = lv_img_create(ui_scr->video_photo);
	lv_obj_set_pos(ui_scr->video_photo_img_12, 240, 253);
	lv_obj_set_size(ui_scr->video_photo_img_12, 120, 120);
	ui_style_set(ui_scr->video_photo_img_12, GUI_CTRL_IMG);

	//Write codes video_photo_img_27
	ui_scr->video_photo_img_27 = lv_img_create(ui_scr->video_photo);
	lv_img_set_src(ui_scr->video_photo_img_27, gui_get_res_path(GUI_RES_HOME_STICK_PNG));
	lv_img_set_pivot(ui_scr->video_photo_img_27, 0, 0);
	lv_img_set_angle(ui_scr->video_photo_img_27, 0);
	lv_img_set_zoom(ui_scr->video_photo_img_27, 256);
	lv_obj_set_pos(ui_scr->video_photo_img_27, 16, 504);
	lv_obj_set_size(ui_scr->video_photo_img_27, 120, 120);
	lv_obj_add_flag(ui_scr->video_photo_img_27, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->video_photo_img_27, GUI_CTRL_IMG);

	lv_obj_update_layout(ui_scr->video_photo);
	ui_scr->video_photo_del = false;
	i18n_refresh_texts(GUI_SCREEN_VIDEO_PHOTO);

	//Init events for screen
	events_init_video_photo(ui);
	return ui_scr->video_photo;
}
void unload_scr_video_photo(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_VIDEO_PHOTO);
}

#endif
