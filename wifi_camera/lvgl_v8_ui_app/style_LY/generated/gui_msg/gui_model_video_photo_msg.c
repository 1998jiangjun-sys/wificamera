#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_video_photo_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;

#if LV_USE_GUIBUILDER_SIMULATOR
_gui_msg_entry_t gui_model_video_photo_msg_entry_table[] = {
	{ GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON, gui_model_video_photo_msg_resolution_icon_cb, VALUE_STRING },
	{ GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE, gui_model_video_photo_msg_show_handshake_cb, VALUE_INT },
	{ GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE, gui_model_video_photo_msg_hide_handshake_cb, VALUE_INT },
	{ GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS, gui_model_video_photo_msg_show_shots_cb, VALUE_INT },
	{ GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS, gui_model_video_photo_msg_hide_shots_cb, VALUE_INT },
	{ GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE, gui_model_video_photo_msg_show_shots_mode_cb, VALUE_INT },
	{ GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE, gui_model_video_photo_msg_hide_shots_mode_cb, VALUE_INT },
	{ GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, gui_model_video_photo_msg_photo_remain_cb, VALUE_STRING },
	{ GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, gui_model_video_photo_msg_shots_icon_cb, VALUE_BOOL },
	{ GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO, gui_model_video_photo_msg_photo_reso_cb, VALUE_STRING },
	};
#endif


GUI_WEAK int gui_model_video_photo_msg_resolution_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char resolution_icon_init_var[] = "1M";
	static bool resolution_icon_is_init = false;
	static char * resolution_icon_var = NULL;
	_gui_msg_char_array_cb(&resolution_icon_var, resolution_icon_init_var, &resolution_icon_is_init, access, data);
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_show_handshake_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_handshake_var = LV_OBJ_FLAG_HIDDEN;
	_gui_msg_obj_flag_cb(&show_handshake_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_hide_handshake_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_handshake_var = LV_OBJ_FLAG_HIDDEN;
	_gui_msg_obj_flag_cb(&hide_handshake_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_show_shots_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_shots_var = LV_OBJ_FLAG_HIDDEN;
	_gui_msg_obj_flag_cb(&show_shots_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_hide_shots_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_shots_var = LV_OBJ_FLAG_HIDDEN;
	_gui_msg_obj_flag_cb(&hide_shots_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_show_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_shots_mode_var = LV_OBJ_FLAG_HIDDEN;
	_gui_msg_obj_flag_cb(&show_shots_mode_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_hide_shots_mode_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_shots_mode_var = LV_OBJ_FLAG_HIDDEN;
	_gui_msg_obj_flag_cb(&hide_shots_mode_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_photo_remain_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char photo_remain_init_var[] = "99999999";
	static bool photo_remain_is_init = false;
	static char * photo_remain_var = NULL;
	_gui_msg_char_array_cb(&photo_remain_var, photo_remain_init_var, &photo_remain_is_init, access, data);
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_shots_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool shots_icon_var = false;
	_gui_msg_bool_cb(&shots_icon_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_video_photo_msg_photo_reso_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char photo_reso_init_var[] = "VGA";
	static bool photo_reso_is_init = false;
	static char * photo_reso_var = NULL;
	_gui_msg_char_array_cb(&photo_reso_var, photo_reso_init_var, &photo_reso_is_init, access, data);
	return 0;
}

void gui_model_video_photo_msg_init(lv_ui *ui)
{
	int32_t ids[10] = {
		GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON,
		GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE,
		GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE,
		GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS,
		GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS,
		GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE,
		GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE,
		GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN,
		GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON,
		GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO,
	};
	for (int i = 0; i < 10; i++) {
		gui_msg_sub_t * sub = gui_msg_create_sub(ids[i]);
		if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	}
}

void gui_model_video_photo_msg_init_ui()
{
}

void gui_model_video_photo_msg_init_events()
{
	void * res = NULL;
	_gui_msg_status_t status[10] = {
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO, 0, 0},
	};

	for (int i = 0; i < 10; i++) {
		lv_subject_t * subject = gui_msg_get_subject(status[i].msg_id);
		if (subject == NULL) continue;
		lv_ll_t subject_ll = subject->subs_ll;
		gui_msg_sub_t * head = _lv_ll_get_head(&subject_ll);
		if (head != NULL) status[i].is_unsubscribe = 1;
	}


	for (int i = 0; i < 10; i++) {
		if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		} else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
		}
	}
}

void gui_model_video_photo_msg_unsubscribe()
{
	_gui_msg_status_t status[10] = {
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON, 0, 0},
		{GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO, 0, 0},
	};
	for (int i = 0; i < 10; i++) {
		lv_subject_t * subject = gui_msg_get_subject(status[i].msg_id);
		if (subject == NULL) continue;
		lv_ll_t subject_ll = subject->subs_ll;
		lv_observer_t * head = _lv_ll_get_head(&subject_ll);
		if (head != NULL) status[i].is_unsubscribe = 1;
		while (head != NULL) {
			lv_obj_t * obj = head->target;
			if (obj != NULL && lv_obj_is_valid(obj) == true) {
				lv_subject_remove_all_obj(subject, obj);
			}
			head = _lv_ll_get_head(&subject_ll);
		}
	}

	for (int i = 0; i < 10; i++) {
		if (status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		}
	}
}

gui_msg_status_t gui_model_video_photo_msg_send(int32_t msg_id, void * value, int32_t len)
{
	if (msg_id == GUI_MODEL_VIDEO_PHOTO_MSG_ID) {
	} else {
		gui_msg_data_type_t data_type = VALUE_INT;
		switch (msg_id) {
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_HANDSHAKE:
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_HANDSHAKE:
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS:
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS:
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOW_SHOTS_MODE:
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_HIDE_SHOTS_MODE:
				{
					data_type = VALUE_INT;
					guider_msg_data.value_array.ptr = value;
					guider_msg_data.value_array.len = len;
				}
			break;
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_SHOTS_ICON:
				{
					data_type = VALUE_BOOL;
					guider_msg_data.value_array.ptr = value;
					guider_msg_data.value_array.len = len;
				}
			break;
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_RESOLUTION_ICON:
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_REMAIN:
			case GUI_MODEL_VIDEO_PHOTO_MSG_ID_PHOTO_RESO:
				{
					data_type = VALUE_STRING;
					guider_msg_data.value_array.ptr = value;
					guider_msg_data.value_array.len = len;
				}
			break;
			default: 
				break;
		}
		gui_msg_action_change(msg_id, GUI_MSG_ACCESS_SET, &guider_msg_data, data_type);
		lv_subject_t * subject = gui_msg_get_subject(msg_id);
		if (subject == NULL) return GUI_MSG_STATUS_NO_SUBSCRIBE;
		lv_subject_set_pointer(subject, &guider_msg_data);
	}
	return GUI_MSG_STATUS_SUCCESS;
}

#endif

#endif
