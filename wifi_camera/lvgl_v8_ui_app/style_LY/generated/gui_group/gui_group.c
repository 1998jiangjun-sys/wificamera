#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "./gui_group.h"

void add_children_to_group(lv_obj_t *obj, lv_group_t *group);
void set_default_group_cb();

void gui_group_init()
{
	if (guider_ui.default_group == NULL) {
		guider_ui.default_group = lv_group_get_default();
	}
}

void gui_group_set_default(lv_group_t *group)
{
	if (group == NULL) return;

	if (guider_ui.default_group == group) return set_default_group_cb();
}

void gui_group_add_obj(lv_group_t *group, lv_obj_t *obj, bool is_add)
{
	if (group == NULL || obj == NULL) return;

	bool is_group_def = lv_obj_is_group_def(obj);
	if (is_group_def && is_add) lv_group_add_obj(group, obj);

	if (
#if LV_USE_LIST
		lv_obj_check_type(obj, &lv_list_class) ||
#endif
#if LV_USE_CALENDAR
		lv_obj_check_type(obj, &lv_calendar_class) ||
#endif
#if LV_USE_MSGBOX
		lv_obj_check_type(obj, &lv_msgbox_class) ||
#endif
#if LV_USE_TABVIEW
		lv_obj_check_type(obj, &lv_tabview_class) ||
#endif
#if LV_USE_CALENDAR_HEADER_ARROW
		lv_obj_check_type(obj, &lv_calendar_header_arrow_class) ||
#endif
#if LV_USE_CALENDAR_HEADER_DROPDOWN
		lv_obj_check_type(obj, &lv_calendar_header_dropdown_class) ||
#endif
		0) {
		add_children_to_group(obj, group);
#if LV_USE_WIN
	} else if (lv_obj_check_type(obj, &lv_win_class)) {
		lv_obj_t *header = lv_win_get_header(obj);
		add_children_to_group(header, group);
#endif
	}

	if (!is_group_def && is_add) lv_group_add_obj(group, obj);
}

void add_children_to_group(lv_obj_t *obj, lv_group_t *group)
{
	if (obj == NULL || group == NULL) return;

	int childCnt = lv_obj_get_child_cnt(obj);
	for (int i = 0; i < childCnt; i++) {
		lv_obj_t *child = lv_obj_get_child(obj, i);
		if (lv_obj_is_group_def(child)) {
			lv_group_add_obj(group, child);
		}
	}
}

void set_default_group_cb()
{
	if (guider_ui.default_group == NULL) return;

	lv_group_remove_all_objs(guider_ui.default_group);
	int32_t act_scr_id = gui_scr_get_id(gui_scr_get_act());

	if (act_scr_id == GUI_SCREEN_HOME_PAGE) {
		lv_ui_home_page * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_HOME_PAGE);
		gui_group_add_obj(guider_ui.default_group, ui_scr->home_page_btn_3, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->home_page_btn_2, true);
	} else if (act_scr_id == GUI_SCREEN_VIDEO_PLAY) {
		lv_ui_video_play * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_PLAY);
		gui_group_add_obj(guider_ui.default_group, ui_scr->video_play_imgbtn_pause, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->video_play_img_prev_file, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->video_play_img_next_file, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->video_play_imgbtn_loud, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->video_play_ddlist_multi_spped, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->video_play_imgbtn_1, true);
	} else if (act_scr_id == GUI_SCREEN_SYS_POPWIN) {
		lv_ui_sys_popwin * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_POPWIN);
		gui_group_add_obj(guider_ui.default_group, ui_scr->sys_popwin_btn_1, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->sys_popwin_btn_2, true);
	} else if (act_scr_id == GUI_SCREEN_WIFI_CONNECTION) {
		lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_WIFI_CONNECTION);
		gui_group_add_obj(guider_ui.default_group, ui_scr->WIFI_connection_btnm_1, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->WIFI_connection_edit_2, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->WIFI_connection_btnm_2, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->WIFI_connection_btn_1, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->WIFI_connection_btnm_3, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->WIFI_connection_btn_2, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->WIFI_connection_btnm_4, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->WIFI_connection_btnm_5, true);
	} else if (act_scr_id == GUI_SCREEN_BRIGHTNESS) {
		lv_ui_brightness * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_BRIGHTNESS);
		gui_group_add_obj(guider_ui.default_group, ui_scr->brightness_slider_1, true);
	} else if (act_scr_id == GUI_SCREEN_VOLUME) {
		lv_ui_volume * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VOLUME);
		gui_group_add_obj(guider_ui.default_group, ui_scr->volume_slider_1, true);
	} else if (act_scr_id == GUI_SCREEN_TEXT) {
		lv_ui_text * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_TEXT);
		gui_group_add_obj(guider_ui.default_group, ui_scr->text_btn_1, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->text_btn_2, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->text_btn_3, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->text_btn_4, true);
	} else if (act_scr_id == GUI_SCREEN_EDIT_FRIEND_INFO) {
		lv_ui_Edit_Friend_Info * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_EDIT_FRIEND_INFO);
		gui_group_add_obj(guider_ui.default_group, ui_scr->Edit_Friend_Info_btn_2, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->Edit_Friend_Info_btn_1, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->Edit_Friend_Info_edit_1, true);
		gui_group_add_obj(guider_ui.default_group, ui_scr->Edit_Friend_Info_ddlist_1, true);
	} else if (act_scr_id == GUI_SCREEN_ZYF_AI_PAGE) {
		lv_ui_zyf_ai_page * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_ZYF_AI_PAGE);
		gui_group_add_obj(guider_ui.default_group, ui_scr->zyf_ai_page_btn_1, true);
	}
	lv_group_set_default(guider_ui.default_group);

	lv_indev_t *indev = NULL;
	while ((indev = lv_indev_get_next(indev)) != NULL) {
		lv_indev_set_group(indev, guider_ui.default_group);
	}
}

#endif
