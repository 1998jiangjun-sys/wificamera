#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "./gui_model_main_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;
static lv_ll_t timer_ll;

#if LV_USE_GUIBUILDER_SIMULATOR
_gui_msg_entry_t gui_model_main_msg_entry_table[] = {
	{ GUI_MODEL_MAIN_MSG_ID_SYSTIME, gui_model_main_msg_systime_cb, VALUE_TIME },
	{ GUI_MODEL_MAIN_MSG_ID_SD_ICON, gui_model_main_msg_sd_icon_cb, VALUE_INT },
	{ GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, gui_model_main_msg_sys_prompt_cb, VALUE_STRING },
	{ GUI_MODEL_MAIN_MSG_ID_HEADLAMP, gui_model_main_msg_headlamp_cb, VALUE_BOOL },
	{ GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW, gui_model_main_msg_sys_prompt_show_cb, VALUE_BOOL },
	{ GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN, gui_model_main_msg_show_del_btn_cb, VALUE_INT },
	{ GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN, gui_model_main_msg_hide_del_btn_cb, VALUE_INT },
	{ GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN, gui_model_main_msg_show_home_btn_cb, VALUE_INT },
	{ GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN, gui_model_main_msg_hide_home_btn_cb, VALUE_INT },
	{ GUI_MODEL_MAIN_MSG_ID_BATTERY, gui_model_main_msg_battery_cb, VALUE_INT },
	{ GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, gui_model_main_msg_battery_percentage_cb, VALUE_STRING },
	{ GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, gui_model_main_msg_wifi_status_cb, VALUE_INT },
	{ GUI_MODEL_MAIN_MSG_ID_FRIENDSHIP_QR_CODE, gui_model_main_msg_friendship_qr_code_cb, VALUE_STRING },
	};
#endif

typedef struct {
	lv_timer_t * timer;
} timer_dsc_t;
static void delete_all_timer()
{
	timer_dsc_t * head = _lv_ll_get_head(&timer_ll);
	while (head != NULL)
	{
		timer_dsc_t * next = _lv_ll_get_next(&timer_ll, head);
		if (head->timer != NULL) lv_timer_del(head->timer);
		_lv_ll_remove(&timer_ll, head);
		lv_mem_free(head);
		head = next;
	}
}
static timer_dsc_t * insert_timer(lv_ll_t * ll_p, lv_timer_t * timer)
{
	timer_dsc_t * tail = _lv_ll_ins_tail(ll_p);
	tail->timer = timer;
	return tail;
}
void gui_model_main_msg_systime_timer_cb(lv_timer_t * timer)
{
	gui_msg_action_change(GUI_MODEL_MAIN_MSG_ID_SYSTIME, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
	lv_subject_t * subject = gui_msg_get_subject(GUI_MODEL_MAIN_MSG_ID_SYSTIME);
	if (subject == NULL) return;
	lv_subject_set_pointer(subject, &guider_msg_data);
}

void gui_model_main_msg_home_page_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_home_page_img_3_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_language_selection_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_language_selection_img_3_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_wifi_search_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_wifi_search_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_wifi_connection_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_wifi_connection_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_seting_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_seting_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_brightness_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_brightness_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_volume_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_volume_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_dormancy_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_dormancy_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_image_size_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_image_size_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_tf_formatting_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_tf_formatting_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_tf_formatting_2_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_tf_formatting_2_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_image_resolution_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_image_resolution_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_binding_device_code_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_binding_device_code_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_software_version_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_software_version_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_restore_factory_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_restore_factory_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_restore_factory_2_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_restore_factory_2_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_address_book_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_address_book_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_video_resolution_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_video_resolution_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_ai_q_a_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_ai_q_a_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_shut_down_img_3_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_ai_payment_code_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_ai_payment_code_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_ai_img_rec_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_ai_img_rec_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_chat_page_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_chat_page_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_edit_friend_info_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_edit_friend_info_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_add_friend_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_add_friend_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_call_img_1_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_main_msg_call_img_2_set_img_path_cb(lv_observer_t * observer, lv_subject_t * subject)
{
	lv_obj_t * obj = lv_observer_get_target_obj(observer);
	if (obj == NULL || lv_obj_is_valid(obj) == false) return;

	gui_msg_data_t * data = (gui_msg_data_t *)observer->user_data;
	lv_img_set_src(obj, gui_get_res_path(data->value_int));
}

GUI_WEAK int gui_model_main_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static struct tm systime_var = {
		.tm_year = 124,
		.tm_mon = 5,
		.tm_mday = 24,
		.tm_hour = 20,
		.tm_min = 52,
		.tm_sec = 7,
	};
	_gui_msg_tm_cb(&systime_var, false, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_sd_icon_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t sd_icon_var = RES_0;
	_gui_msg_int32_cb(&sd_icon_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_sys_prompt_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char sys_prompt_init_var[] = "";
	static bool sys_prompt_is_init = false;
	static char * sys_prompt_var = NULL;
	_gui_msg_char_array_cb(&sys_prompt_var, sys_prompt_init_var, &sys_prompt_is_init, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_headlamp_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool headlamp_var = false;
	_gui_msg_bool_cb(&headlamp_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_sys_prompt_show_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static bool sys_prompt_show_var = false;
	_gui_msg_bool_cb(&sys_prompt_show_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_show_del_btn_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_del_btn_var = 0;
	_gui_msg_obj_flag_cb(&show_del_btn_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_hide_del_btn_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_del_btn_var = 0;
	_gui_msg_obj_flag_cb(&hide_del_btn_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_show_home_btn_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t show_home_btn_var = 0;
	_gui_msg_obj_flag_cb(&show_home_btn_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_hide_home_btn_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static lv_obj_flag_t hide_home_btn_var = 0;
	_gui_msg_obj_flag_cb(&hide_home_btn_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_battery_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t battery_var = RES_CHARGING;
	_gui_msg_int32_cb(&battery_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_battery_percentage_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char battery_percentage_init_var[] = "80%";
	static bool battery_percentage_is_init = false;
	static char * battery_percentage_var = NULL;
	_gui_msg_char_array_cb(&battery_percentage_var, battery_percentage_init_var, &battery_percentage_is_init, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_wifi_status_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	static int32_t wifi_status_var = RES_WIFI_NO;
	_gui_msg_int32_cb(&wifi_status_var, access, data);
	return 0;
}
GUI_WEAK int gui_model_main_msg_friendship_qr_code_cb(gui_msg_action_t access, gui_msg_data_t * data, gui_msg_data_type_t type)
{
	char friendship_qr_code_init_var[] = "865028000000306";
	static bool friendship_qr_code_is_init = false;
	static char * friendship_qr_code_var = NULL;
	_gui_msg_char_array_cb(&friendship_qr_code_var, friendship_qr_code_init_var, &friendship_qr_code_is_init, access, data);
	return 0;
}

void gui_model_main_msg_init(lv_ui *ui)
{
	int32_t ids[13] = {
		GUI_MODEL_MAIN_MSG_ID_SYSTIME,
		GUI_MODEL_MAIN_MSG_ID_SD_ICON,
		GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT,
		GUI_MODEL_MAIN_MSG_ID_HEADLAMP,
		GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW,
		GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN,
		GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN,
		GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN,
		GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN,
		GUI_MODEL_MAIN_MSG_ID_BATTERY,
		GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE,
		GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS,
		GUI_MODEL_MAIN_MSG_ID_FRIENDSHIP_QR_CODE,
	};
	for (int i = 0; i < 13; i++) {
		gui_msg_sub_t * sub = gui_msg_create_sub(ids[i]);
		if (sub != NULL) lv_subject_init_pointer(sub->subject, &guider_msg_data);
	}
	_lv_ll_init(&timer_ll, sizeof (timer_dsc_t));
}

void gui_model_main_msg_init_ui()
{
}

void gui_model_main_msg_init_events()
{
	void * res = NULL;
	_gui_msg_status_t status[13] = {
		{GUI_MODEL_MAIN_MSG_ID_SYSTIME, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_SD_ICON, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_HEADLAMP, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_BATTERY, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_FRIENDSHIP_QR_CODE, 0, 0},
	};
	lv_timer_t * timer = NULL;
	bool systime_timer_enable = false;
	delete_all_timer();

	for (int i = 0; i < 13; i++) {
		lv_subject_t * subject = gui_msg_get_subject(status[i].msg_id);
		if (subject == NULL) continue;
		lv_ll_t subject_ll = subject->subs_ll;
		gui_msg_sub_t * head = _lv_ll_get_head(&subject_ll);
		if (head != NULL) status[i].is_unsubscribe = 1;
	}

	lv_subject_t * subject_battery_percentage = gui_msg_get_subject(GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE);
	lv_subject_t * subject_wifi_status = gui_msg_get_subject(GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS);
	lv_subject_t * subject_battery = gui_msg_get_subject(GUI_MODEL_MAIN_MSG_ID_BATTERY);
	lv_subject_t * subject_sys_prompt = gui_msg_get_subject(GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT);
	lv_subject_t * subject_friendship_qr_code = gui_msg_get_subject(GUI_MODEL_MAIN_MSG_ID_FRIENDSHIP_QR_CODE);
	if (guider_ui.home_page) {
		lv_ui_home_page * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_HOME_PAGE);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->home_page_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->home_page_img_2, &guider_msg_data, gui_model_main_msg_home_page_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->home_page_img_3, &guider_msg_data, gui_model_main_msg_home_page_img_3_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.sys_prompt) {
		lv_ui_sys_prompt * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_PROMPT);
		gui_msg_setup_component(true, false, subject_sys_prompt, ui_scr->sys_prompt_lbl_warn, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.sys_popwin) {
		lv_ui_sys_popwin * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_POPWIN);
		gui_msg_setup_component(true, false, subject_sys_prompt, ui_scr->sys_popwin_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.Language_Selection) {
		lv_ui_Language_Selection * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_LANGUAGE_SELECTION);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->Language_Selection_lbl_2, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->Language_Selection_img_2, &guider_msg_data, gui_model_main_msg_language_selection_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->Language_Selection_img_3, &guider_msg_data, gui_model_main_msg_language_selection_img_3_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.WIFI_search) {
		lv_ui_WIFI_search * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_WIFI_SEARCH);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->WIFI_search_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->WIFI_search_img_1, &guider_msg_data, gui_model_main_msg_wifi_search_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->WIFI_search_img_2, &guider_msg_data, gui_model_main_msg_wifi_search_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.WIFI_connection) {
		lv_ui_WIFI_connection * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_WIFI_CONNECTION);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->WIFI_connection_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->WIFI_connection_img_1, &guider_msg_data, gui_model_main_msg_wifi_connection_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->WIFI_connection_img_2, &guider_msg_data, gui_model_main_msg_wifi_connection_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.seting) {
		lv_ui_seting * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SETING);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->seting_lbl_19, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->seting_img_1, &guider_msg_data, gui_model_main_msg_seting_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->seting_img_2, &guider_msg_data, gui_model_main_msg_seting_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.brightness) {
		lv_ui_brightness * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_BRIGHTNESS);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->brightness_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->brightness_img_1, &guider_msg_data, gui_model_main_msg_brightness_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->brightness_img_2, &guider_msg_data, gui_model_main_msg_brightness_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.volume) {
		lv_ui_volume * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VOLUME);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->volume_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->volume_img_1, &guider_msg_data, gui_model_main_msg_volume_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->volume_img_2, &guider_msg_data, gui_model_main_msg_volume_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.dormancy) {
		lv_ui_dormancy * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_DORMANCY);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->dormancy_lbl_5, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->dormancy_img_1, &guider_msg_data, gui_model_main_msg_dormancy_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->dormancy_img_2, &guider_msg_data, gui_model_main_msg_dormancy_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.image_size) {
		lv_ui_image_size * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_IMAGE_SIZE);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->image_size_lbl_6, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->image_size_img_1, &guider_msg_data, gui_model_main_msg_image_size_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->image_size_img_2, &guider_msg_data, gui_model_main_msg_image_size_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.TF_formatting) {
		lv_ui_TF_formatting * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_TF_FORMATTING);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->TF_formatting_lbl_2, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->TF_formatting_img_1, &guider_msg_data, gui_model_main_msg_tf_formatting_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->TF_formatting_img_2, &guider_msg_data, gui_model_main_msg_tf_formatting_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.TF_formatting_2) {
		lv_ui_TF_formatting_2 * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_TF_FORMATTING_2);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->TF_formatting_2_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->TF_formatting_2_img_1, &guider_msg_data, gui_model_main_msg_tf_formatting_2_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->TF_formatting_2_img_2, &guider_msg_data, gui_model_main_msg_tf_formatting_2_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.image_resolution) {
		lv_ui_image_resolution * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_IMAGE_RESOLUTION);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->image_resolution_lbl_6, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->image_resolution_img_1, &guider_msg_data, gui_model_main_msg_image_resolution_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->image_resolution_img_2, &guider_msg_data, gui_model_main_msg_image_resolution_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.Binding_device_code) {
		lv_ui_Binding_device_code * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_BINDING_DEVICE_CODE);
		gui_msg_setup_component(true, false, subject_friendship_qr_code, ui_scr->Binding_device_code_qrcode_1, &guider_msg_data, gui_msg_set_qrcode_qr_data_by_string_cb, GUI_MODEL_MAIN_MSG_ID_FRIENDSHIP_QR_CODE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->Binding_device_code_lbl_6, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->Binding_device_code_img_1, &guider_msg_data, gui_model_main_msg_binding_device_code_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->Binding_device_code_img_2, &guider_msg_data, gui_model_main_msg_binding_device_code_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_FRIENDSHIP_QR_CODE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.software_version) {
		lv_ui_software_version * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SOFTWARE_VERSION);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->software_version_lbl_6, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->software_version_img_1, &guider_msg_data, gui_model_main_msg_software_version_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->software_version_img_2, &guider_msg_data, gui_model_main_msg_software_version_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.Restore_factory) {
		lv_ui_Restore_factory * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_RESTORE_FACTORY);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->Restore_factory_lbl_2, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->Restore_factory_img_1, &guider_msg_data, gui_model_main_msg_restore_factory_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->Restore_factory_img_2, &guider_msg_data, gui_model_main_msg_restore_factory_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.Restore_factory_2) {
		lv_ui_Restore_factory_2 * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_RESTORE_FACTORY_2);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->Restore_factory_2_lbl_1, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->Restore_factory_2_img_1, &guider_msg_data, gui_model_main_msg_restore_factory_2_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->Restore_factory_2_img_2, &guider_msg_data, gui_model_main_msg_restore_factory_2_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.address_book) {
		lv_ui_address_book * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_ADDRESS_BOOK);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->address_book_lbl_19, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->address_book_img_1, &guider_msg_data, gui_model_main_msg_address_book_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->address_book_img_2, &guider_msg_data, gui_model_main_msg_address_book_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.video_resolution) {
		lv_ui_video_resolution * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_VIDEO_RESOLUTION);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->video_resolution_lbl_6, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->video_resolution_img_1, &guider_msg_data, gui_model_main_msg_video_resolution_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->video_resolution_img_2, &guider_msg_data, gui_model_main_msg_video_resolution_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.AI_Q_A) {
		lv_ui_AI_Q_A * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_AI_Q_A);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->AI_Q_A_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->AI_Q_A_img_1, &guider_msg_data, gui_model_main_msg_ai_q_a_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->AI_Q_A_img_2, &guider_msg_data, gui_model_main_msg_ai_q_a_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.Shut_down) {
		lv_ui_Shut_down * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SHUT_DOWN);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->Shut_down_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->Shut_down_img_3, &guider_msg_data, gui_model_main_msg_shut_down_img_3_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.AI_payment_code) {
		lv_ui_AI_payment_code * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_AI_PAYMENT_CODE);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->AI_payment_code_lbl_6, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->AI_payment_code_img_1, &guider_msg_data, gui_model_main_msg_ai_payment_code_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->AI_payment_code_img_2, &guider_msg_data, gui_model_main_msg_ai_payment_code_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.AI_Img_Rec) {
		lv_ui_AI_Img_Rec * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_AI_IMG_REC);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->AI_Img_Rec_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->AI_Img_Rec_img_1, &guider_msg_data, gui_model_main_msg_ai_img_rec_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->AI_Img_Rec_img_2, &guider_msg_data, gui_model_main_msg_ai_img_rec_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.chat_page) {
		lv_ui_chat_page * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_CHAT_PAGE);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->chat_page_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->chat_page_img_1, &guider_msg_data, gui_model_main_msg_chat_page_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->chat_page_img_2, &guider_msg_data, gui_model_main_msg_chat_page_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.Edit_Friend_Info) {
		lv_ui_Edit_Friend_Info * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_EDIT_FRIEND_INFO);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->Edit_Friend_Info_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->Edit_Friend_Info_img_1, &guider_msg_data, gui_model_main_msg_edit_friend_info_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->Edit_Friend_Info_img_2, &guider_msg_data, gui_model_main_msg_edit_friend_info_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.Add_friend) {
		lv_ui_Add_friend * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_ADD_FRIEND);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->Add_friend_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->Add_friend_img_1, &guider_msg_data, gui_model_main_msg_add_friend_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->Add_friend_img_2, &guider_msg_data, gui_model_main_msg_add_friend_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}
	if (guider_ui.call) {
		lv_ui_call * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_CALL);
		gui_msg_setup_component(true, false, subject_battery_percentage, ui_scr->call_lbl_3, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

		gui_msg_setup_component(true, false, subject_wifi_status, ui_scr->call_img_1, &guider_msg_data, gui_model_main_msg_call_img_1_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

		gui_msg_setup_component(true, false, subject_battery, ui_scr->call_img_2, &guider_msg_data, gui_model_main_msg_call_img_2_set_img_path_cb, GUI_MODEL_MAIN_MSG_ID_BATTERY, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);


		for (int i = 0; i < 13; i++) {
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS) {
				status[i].is_subscribe = 1;
			}
			if (status[i].msg_id == GUI_MODEL_MAIN_MSG_ID_BATTERY) {
				status[i].is_subscribe = 1;
			}
		}
	}

	for (int i = 0; i < 13; i++) {
		if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		} else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
		}
	}
	if (systime_timer_enable) {
		timer = lv_timer_create(gui_model_main_msg_systime_timer_cb, 1000, NULL);
		insert_timer(&timer_ll, timer);
	}
}

void gui_model_main_msg_unsubscribe()
{
	_gui_msg_status_t status[13] = {
		{GUI_MODEL_MAIN_MSG_ID_SYSTIME, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_SD_ICON, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_HEADLAMP, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_BATTERY, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS, 0, 0},
		{GUI_MODEL_MAIN_MSG_ID_FRIENDSHIP_QR_CODE, 0, 0},
	};
	for (int i = 0; i < 13; i++) {
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

	for (int i = 0; i < 13; i++) {
		if (status[i].is_unsubscribe == 1) {
			gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
		}
	}
}

gui_msg_status_t gui_model_main_msg_send(int32_t msg_id, void * value, int32_t len)
{
	if (msg_id == GUI_MODEL_MAIN_MSG_ID) {
	} else {
		gui_msg_data_type_t data_type = VALUE_INT;
		switch (msg_id) {
			case GUI_MODEL_MAIN_MSG_ID_SHOW_DEL_BTN:
			case GUI_MODEL_MAIN_MSG_ID_HIDE_DEL_BTN:
			case GUI_MODEL_MAIN_MSG_ID_SHOW_HOME_BTN:
			case GUI_MODEL_MAIN_MSG_ID_HIDE_HOME_BTN:
				{
					data_type = VALUE_INT;
					guider_msg_data.value_array.ptr = value;
					guider_msg_data.value_array.len = len;
				}
			break;
			case GUI_MODEL_MAIN_MSG_ID_HEADLAMP:
			case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT_SHOW:
				{
					data_type = VALUE_BOOL;
					guider_msg_data.value_array.ptr = value;
					guider_msg_data.value_array.len = len;
				}
			break;
			case GUI_MODEL_MAIN_MSG_ID_SD_ICON:
			case GUI_MODEL_MAIN_MSG_ID_BATTERY:
			case GUI_MODEL_MAIN_MSG_ID_WIFI_STATUS:
				{
					data_type = VALUE_INT;
					guider_msg_data.value_array.ptr = value;
					guider_msg_data.value_array.len = len;
				}
			break;
			case GUI_MODEL_MAIN_MSG_ID_SYS_PROMPT:
			case GUI_MODEL_MAIN_MSG_ID_BATTERY_PERCENTAGE:
			case GUI_MODEL_MAIN_MSG_ID_FRIENDSHIP_QR_CODE:
				{
					data_type = VALUE_STRING;
					guider_msg_data.value_array.ptr = value;
					guider_msg_data.value_array.len = len;
				}
			break;
			case GUI_MODEL_MAIN_MSG_ID_SYSTIME:
				{
					data_type = VALUE_TIME;
					if (value) guider_msg_data.value_time = *((struct tm *)value);
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
