#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "./common.h"
#include "./gui_fonts/gui_fonts.h"
#include "./gui_images/gui_images.h"
#include "./gui_scr/ui_scr_manager.h"
#include "./gui_scr/ui_style.h"
#include "./i18n/lv_i18n.h"

#ifdef JL_GUI_KERNEL_VERSION_MAJOR
#if GUI_CORE_VERSION_MAJOR > JL_GUI_KERNEL_VERSION_MAJOR
	#error "Current SDK Version is older than the kernel version. Please update the SDK version!"
#endif
#if GUI_CORE_VERSION_MAJOR < JL_GUI_KERNEL_VERSION_MAJOR
	#error "Current SDK Version is newer than the kernel version. Please update the kernel version!"
#endif
#if GUI_CORE_VERSION_MINOR > JL_GUI_KERNEL_VERSION_MINOR
	#warning "Current Kernel Version is too low, some features may not be available, please update the kernel version!"
#endif
#else
	#error "Current Kernel Version is not defined, please replace or upgrade the kernel!"
#endif

#ifndef LV_USE_GUIBUILDER_SIMULATOR
#if defined(COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MAJOR) && defined(COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MAJOR)
#if GUI_TEMPLATE_VERSION_MAJOR < COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MAJOR || GUI_TEMPLATE_VERSION_MAJOR > COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MAJOR
	#error "Current Project Template Version is not compatible with the SDK version. Please select a compatible SDK version!"
#endif
#if GUI_TEMPLATE_VERSION_MINOR < COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MINOR || GUI_TEMPLATE_VERSION_MINOR > COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MINOR
	#warning "Current Project Template Version has minor incompatibilities with the SDK. Some features may not be available. Consider updating the SDK version."
#endif
#endif
#endif

typedef struct {
	// Screen home_page
	lv_obj_t *home_page;
	bool      home_page_del;
	lv_obj_t *home_page_img_1;
	lv_obj_t *home_page_digitclock_1;
	lv_obj_t *home_page_lbl_1;
	lv_obj_t *home_page_lbl_2;
	lv_obj_t *home_page_view_9;
	lv_obj_t *home_page_view_7;
	lv_obj_t *home_page_img_12;
	lv_obj_t *home_page_lbl_9;
	lv_obj_t *home_page_view_8;
	lv_obj_t *home_page_img_13;
	lv_obj_t *home_page_lbl_10;
	lv_obj_t *home_page_view_5;
	lv_obj_t *home_page_img_10;
	lv_obj_t *home_page_lbl_7;
	lv_obj_t *home_page_view_6;
	lv_obj_t *home_page_img_11;
	lv_obj_t *home_page_lbl_8;
	lv_obj_t *home_page_view_3;
	lv_obj_t *home_page_img_8;
	lv_obj_t *home_page_lbl_5;
	lv_obj_t *home_page_view_4;
	lv_obj_t *home_page_img_9;
	lv_obj_t *home_page_lbl_6;
	lv_obj_t *home_page_view_10;
	lv_obj_t *home_page_img_14;
	lv_obj_t *home_page_lbl_12;
	lv_obj_t *home_page_lbl_4;
	lv_obj_t *home_page_img_7;
	lv_obj_t *home_page_view_1;
	lv_obj_t *home_page_lbl_3;
	lv_obj_t *home_page_img_2;
	lv_obj_t *home_page_img_3;
	lv_obj_t *home_page_view_11;
	lv_obj_t *home_page_img_17;
	lv_obj_t *home_page_img_18;
	lv_obj_t *home_page_img_19;
	lv_obj_t *home_page_btn_3;
	lv_obj_t *home_page_btn_3_label;
	lv_obj_t *home_page_lbl_13;
	lv_obj_t *home_page_view_2;
	lv_obj_t *home_page_img_4;
	lv_obj_t *home_page_img_6;
	lv_obj_t *home_page_img_5;
	lv_obj_t *home_page_btn_2;
	lv_obj_t *home_page_btn_2_label;
	lv_obj_t *home_page_lbl_11;
} lv_ui_home_page;

typedef struct {
	// Screen video_rec
	lv_obj_t *video_rec;
	bool      video_rec_del;
	lv_obj_t *video_rec_img_1;
	lv_obj_t *video_rec_btn_1;
	lv_obj_t *video_rec_btn_1_label;
	lv_obj_t *video_rec_img_2;
	lv_obj_t *video_rec_view_1;
	lv_obj_t *video_rec_img_9;
	lv_obj_t *video_rec_img_4;
	lv_obj_t *video_rec_img_3;
	lv_obj_t *video_rec_img_5;
	lv_obj_t *video_rec_img_6;
	lv_obj_t *video_rec_img_7;
	lv_obj_t *video_rec_img_8;
	lv_obj_t *video_rec_img_10;
} lv_ui_video_rec;

typedef struct {
	// Screen sys_prompt
	lv_obj_t *sys_prompt;
	bool      sys_prompt_del;
	lv_obj_t *sys_prompt_img_warn;
	lv_obj_t *sys_prompt_lbl_warn;
	lv_obj_t *sys_prompt_img_2;
	lv_obj_t *sys_prompt_img_1;
	lv_obj_t *sys_prompt_lbl_1;
} lv_ui_sys_prompt;

typedef struct {
	// Screen video_photo
	lv_obj_t *video_photo;
	bool      video_photo_del;
	lv_obj_t *video_photo_view_2;
	lv_obj_t *video_photo_img_3;
	lv_obj_t *video_photo_img_1;
	lv_obj_t *video_photo_img_2;
	lv_obj_t *video_photo_view_3;
	lv_obj_t *video_photo_img_6;
	lv_obj_t *video_photo_img_5;
	lv_obj_t *video_photo_img_4;
	lv_obj_t *video_photo_img_7;
	lv_obj_t *video_photo_img_8;
	lv_obj_t *video_photo_img_9;
	lv_obj_t *video_photo_img_10;
	lv_obj_t *video_photo_img_11;
	lv_obj_t *video_photo_view_1;
	lv_obj_t *video_photo_img_24;
	lv_obj_t *video_photo_img_13;
	lv_obj_t *video_photo_btn_1;
	lv_obj_t *video_photo_btn_1_label;
	lv_obj_t *video_photo_img_26;
	lv_obj_t *video_photo_img_25;
	lv_obj_t *video_photo_img_12;
	lv_obj_t *video_photo_img_27;
} lv_ui_video_photo;

typedef struct {
	// Screen video_play
	lv_obj_t *video_play;
	bool      video_play_del;
	lv_obj_t *video_play_view_1;
	lv_obj_t *video_play_lbl_cur_time;
	lv_obj_t *video_play_imgbtn_pause;
	lv_obj_t *video_play_imgbtn_pause_label;
	lv_obj_t *video_play_img_prev_file;
	lv_obj_t *video_play_img_next_file;
	lv_obj_t *video_play_imgbtn_loud;
	lv_obj_t *video_play_imgbtn_loud_label;
	lv_obj_t *video_play_lbl_total_time;
	lv_obj_t *video_play_ddlist_multi_spped;
	lv_obj_t *video_play_bar_process;
	lv_obj_t *video_play_imgbtn_1;
	lv_obj_t *video_play_imgbtn_1_label;
	lv_obj_t *video_play_lbl_msg;
	lv_obj_t *video_play_img_1;
} lv_ui_video_play;

typedef struct {
	// Screen sys_popwin
	lv_obj_t *sys_popwin;
	bool      sys_popwin_del;
	lv_obj_t *sys_popwin_view_1;
	lv_obj_t *sys_popwin_lbl_1;
	lv_obj_t *sys_popwin_btn_1;
	lv_obj_t *sys_popwin_btn_1_label;
	lv_obj_t *sys_popwin_btn_2;
	lv_obj_t *sys_popwin_btn_2_label;
} lv_ui_sys_popwin;

typedef struct {
	// Screen usb_slave
	lv_obj_t *usb_slave;
	bool      usb_slave_del;
	lv_obj_t *usb_slave_img_1;
	lv_obj_t *usb_slave_gif_1;
} lv_ui_usb_slave;

typedef struct {
	// Screen Language_Selection
	lv_obj_t *Language_Selection;
	bool      Language_Selection_del;
	lv_obj_t *Language_Selection_img_1;
	lv_obj_t *Language_Selection_view_12;
	lv_obj_t *Language_Selection_view_3;
	lv_obj_t *Language_Selection_view_5;
	lv_obj_t *Language_Selection_img_6;
	lv_obj_t *Language_Selection_lbl_4;
	lv_obj_t *Language_Selection_img_7;
	lv_obj_t *Language_Selection_view_4;
	lv_obj_t *Language_Selection_img_5;
	lv_obj_t *Language_Selection_lbl_3;
	lv_obj_t *Language_Selection_img_4;
	lv_obj_t *Language_Selection_view_6;
	lv_obj_t *Language_Selection_img_8;
	lv_obj_t *Language_Selection_lbl_5;
	lv_obj_t *Language_Selection_img_9;
	lv_obj_t *Language_Selection_view_7;
	lv_obj_t *Language_Selection_img_10;
	lv_obj_t *Language_Selection_lbl_6;
	lv_obj_t *Language_Selection_img_11;
	lv_obj_t *Language_Selection_view_8;
	lv_obj_t *Language_Selection_img_12;
	lv_obj_t *Language_Selection_lbl_7;
	lv_obj_t *Language_Selection_img_13;
	lv_obj_t *Language_Selection_view_9;
	lv_obj_t *Language_Selection_img_14;
	lv_obj_t *Language_Selection_lbl_8;
	lv_obj_t *Language_Selection_img_15;
	lv_obj_t *Language_Selection_view_10;
	lv_obj_t *Language_Selection_img_16;
	lv_obj_t *Language_Selection_lbl_9;
	lv_obj_t *Language_Selection_img_17;
	lv_obj_t *Language_Selection_view_11;
	lv_obj_t *Language_Selection_img_18;
	lv_obj_t *Language_Selection_lbl_10;
	lv_obj_t *Language_Selection_img_19;
	lv_obj_t *Language_Selection_view_1;
	lv_obj_t *Language_Selection_btn_1;
	lv_obj_t *Language_Selection_btn_1_label;
	lv_obj_t *Language_Selection_view_2;
	lv_obj_t *Language_Selection_lbl_2;
	lv_obj_t *Language_Selection_img_2;
	lv_obj_t *Language_Selection_img_3;
	lv_obj_t *Language_Selection_lbl_1;
} lv_ui_Language_Selection;

typedef struct {
	// Screen WIFI_search
	lv_obj_t *WIFI_search;
	bool      WIFI_search_del;
	lv_obj_t *WIFI_search_view_2;
	lv_obj_t *WIFI_search_lbl_1;
	lv_obj_t *WIFI_search_img_3;
	lv_obj_t *WIFI_search_view_3;
	lv_obj_t *WIFI_search_imgbtn_2;
	lv_obj_t *WIFI_search_imgbtn_2_label;
	lv_obj_t *WIFI_search_lbl_2;
	lv_obj_t *WIFI_search_view_1;
	lv_obj_t *WIFI_search_lbl_3;
	lv_obj_t *WIFI_search_img_1;
	lv_obj_t *WIFI_search_img_2;
	lv_obj_t *WIFI_search_lbl_4;
	lv_obj_t *WIFI_search_lbl_5;
} lv_ui_WIFI_search;

typedef struct {
	// Screen WIFI_connection
	lv_obj_t *WIFI_connection;
	bool      WIFI_connection_del;
	lv_obj_t *WIFI_connection_view_2;
	lv_obj_t *WIFI_connection_lbl_2;
	lv_obj_t *WIFI_connection_img_3;
	lv_obj_t *WIFI_connection_btnm_1;
	lv_obj_t *WIFI_connection_edit_2;
	lv_obj_t *WIFI_connection_btnm_2;
	lv_obj_t *WIFI_connection_btn_1;
	lv_obj_t *WIFI_connection_btn_1_label;
	lv_obj_t *WIFI_connection_btnm_3;
	lv_obj_t *WIFI_connection_btn_2;
	lv_obj_t *WIFI_connection_btn_2_label;
	lv_obj_t *WIFI_connection_btnm_4;
	lv_obj_t *WIFI_connection_btnm_5;
	lv_obj_t *WIFI_connection_view_1;
	lv_obj_t *WIFI_connection_lbl_1;
	lv_obj_t *WIFI_connection_img_1;
	lv_obj_t *WIFI_connection_img_2;
	lv_obj_t *WIFI_connection_lbl_3;
} lv_ui_WIFI_connection;

typedef struct {
	// Screen seting
	lv_obj_t *seting;
	bool      seting_del;
	lv_obj_t *seting_img_26;
	lv_obj_t *seting_view_3;
	lv_obj_t *seting_view_15;
	lv_obj_t *seting_lbl_21;
	lv_obj_t *seting_img_28;
	lv_obj_t *seting_img_29;
	lv_obj_t *seting_lbl_22;
	lv_obj_t *seting_view_14;
	lv_obj_t *seting_lbl_18;
	lv_obj_t *seting_img_23;
	lv_obj_t *seting_img_24;
	lv_obj_t *seting_view_13;
	lv_obj_t *seting_lbl_17;
	lv_obj_t *seting_img_21;
	lv_obj_t *seting_img_22;
	lv_obj_t *seting_view_12;
	lv_obj_t *seting_lbl_16;
	lv_obj_t *seting_img_19;
	lv_obj_t *seting_img_20;
	lv_obj_t *seting_view_11;
	lv_obj_t *seting_lbl_14;
	lv_obj_t *seting_img_17;
	lv_obj_t *seting_img_18;
	lv_obj_t *seting_lbl_15;
	lv_obj_t *seting_view_10;
	lv_obj_t *seting_lbl_13;
	lv_obj_t *seting_img_15;
	lv_obj_t *seting_img_16;
	lv_obj_t *seting_view_9;
	lv_obj_t *seting_lbl_10;
	lv_obj_t *seting_img_13;
	lv_obj_t *seting_img_14;
	lv_obj_t *seting_lbl_12;
	lv_obj_t *seting_view_8;
	lv_obj_t *seting_lbl_9;
	lv_obj_t *seting_img_11;
	lv_obj_t *seting_img_12;
	lv_obj_t *seting_lbl_11;
	lv_obj_t *seting_view_7;
	lv_obj_t *seting_lbl_7;
	lv_obj_t *seting_img_9;
	lv_obj_t *seting_img_10;
	lv_obj_t *seting_lbl_8;
	lv_obj_t *seting_view_6;
	lv_obj_t *seting_img_7;
	lv_obj_t *seting_img_8;
	lv_obj_t *seting_lbl_6;
	lv_obj_t *seting_lbl_23;
	lv_obj_t *seting_view_5;
	lv_obj_t *seting_lbl_3;
	lv_obj_t *seting_img_5;
	lv_obj_t *seting_img_6;
	lv_obj_t *seting_lbl_4;
	lv_obj_t *seting_view_4;
	lv_obj_t *seting_lbl_1;
	lv_obj_t *seting_img_4;
	lv_obj_t *seting_img_3;
	lv_obj_t *seting_lbl_2;
	lv_obj_t *seting_view_17;
	lv_obj_t *seting_img_33;
	lv_obj_t *seting_lbl_24;
	lv_obj_t *seting_view_2;
	lv_obj_t *seting_lbl_20;
	lv_obj_t *seting_img_27;
	lv_obj_t *seting_view_1;
	lv_obj_t *seting_lbl_19;
	lv_obj_t *seting_img_1;
	lv_obj_t *seting_img_2;
	lv_obj_t *seting_img_25;
} lv_ui_seting;

typedef struct {
	// Screen brightness
	lv_obj_t *brightness;
	bool      brightness_del;
	lv_obj_t *brightness_view_2;
	lv_obj_t *brightness_lbl_2;
	lv_obj_t *brightness_img_6;
	lv_obj_t *brightness_view_3;
	lv_obj_t *brightness_lbl_1;
	lv_obj_t *brightness_img_3;
	lv_obj_t *brightness_slider_1;
	lv_obj_t *brightness_img_4;
	lv_obj_t *brightness_view_1;
	lv_obj_t *brightness_lbl_3;
	lv_obj_t *brightness_img_1;
	lv_obj_t *brightness_img_2;
	lv_obj_t *brightness_img_5;
} lv_ui_brightness;

typedef struct {
	// Screen volume
	lv_obj_t *volume;
	bool      volume_del;
	lv_obj_t *volume_view_2;
	lv_obj_t *volume_lbl_1;
	lv_obj_t *volume_img_6;
	lv_obj_t *volume_view_3;
	lv_obj_t *volume_lbl_2;
	lv_obj_t *volume_img_3;
	lv_obj_t *volume_slider_1;
	lv_obj_t *volume_img_4;
	lv_obj_t *volume_view_1;
	lv_obj_t *volume_lbl_3;
	lv_obj_t *volume_img_1;
	lv_obj_t *volume_img_2;
	lv_obj_t *volume_img_5;
	lv_obj_t *volume_view_4;
	lv_obj_t *volume_lbl_4;
	lv_obj_t *volume_img_7;
} lv_ui_volume;

typedef struct {
	// Screen dormancy
	lv_obj_t *dormancy;
	bool      dormancy_del;
	lv_obj_t *dormancy_view_2;
	lv_obj_t *dormancy_lbl_1;
	lv_obj_t *dormancy_img_10;
	lv_obj_t *dormancy_view_3;
	lv_obj_t *dormancy_view_6;
	lv_obj_t *dormancy_img_7;
	lv_obj_t *dormancy_lbl_4;
	lv_obj_t *dormancy_img_8;
	lv_obj_t *dormancy_view_5;
	lv_obj_t *dormancy_img_5;
	lv_obj_t *dormancy_lbl_3;
	lv_obj_t *dormancy_img_6;
	lv_obj_t *dormancy_view_4;
	lv_obj_t *dormancy_img_4;
	lv_obj_t *dormancy_lbl_2;
	lv_obj_t *dormancy_img_3;
	lv_obj_t *dormancy_view_1;
	lv_obj_t *dormancy_lbl_5;
	lv_obj_t *dormancy_img_1;
	lv_obj_t *dormancy_img_2;
	lv_obj_t *dormancy_img_9;
} lv_ui_dormancy;

typedef struct {
	// Screen image_size
	lv_obj_t *image_size;
	bool      image_size_del;
	lv_obj_t *image_size_view_2;
	lv_obj_t *image_size_lbl_1;
	lv_obj_t *image_size_img_12;
	lv_obj_t *image_size_view_6;
	lv_obj_t *image_size_view_3;
	lv_obj_t *image_size_img_3;
	lv_obj_t *image_size_lbl_2;
	lv_obj_t *image_size_img_4;
	lv_obj_t *image_size_view_4;
	lv_obj_t *image_size_img_5;
	lv_obj_t *image_size_lbl_3;
	lv_obj_t *image_size_img_6;
	lv_obj_t *image_size_view_5;
	lv_obj_t *image_size_img_7;
	lv_obj_t *image_size_lbl_4;
	lv_obj_t *image_size_img_8;
	lv_obj_t *image_size_view_1;
	lv_obj_t *image_size_lbl_6;
	lv_obj_t *image_size_img_1;
	lv_obj_t *image_size_img_2;
	lv_obj_t *image_size_img_11;
} lv_ui_image_size;

typedef struct {
	// Screen TF_formatting
	lv_obj_t *TF_formatting;
	bool      TF_formatting_del;
	lv_obj_t *TF_formatting_view_4;
	lv_obj_t *TF_formatting_view_7;
	lv_obj_t *TF_formatting_lbl_3;
	lv_obj_t *TF_formatting_btn_1;
	lv_obj_t *TF_formatting_btn_1_label;
	lv_obj_t *TF_formatting_img_4;
	lv_obj_t *TF_formatting_view_3;
	lv_obj_t *TF_formatting_img_5;
	lv_obj_t *TF_formatting_lbl_5;
	lv_obj_t *TF_formatting_lbl_4;
	lv_obj_t *TF_formatting_img_6;
	lv_obj_t *TF_formatting_btn_2;
	lv_obj_t *TF_formatting_btn_2_label;
	lv_obj_t *TF_formatting_btn_3;
	lv_obj_t *TF_formatting_btn_3_label;
	lv_obj_t *TF_formatting_img_7;
	lv_obj_t *TF_formatting_view_5;
	lv_obj_t *TF_formatting_view_6;
	lv_obj_t *TF_formatting_img_8;
	lv_obj_t *TF_formatting_lbl_6;
	lv_obj_t *TF_formatting_view_2;
	lv_obj_t *TF_formatting_lbl_1;
	lv_obj_t *TF_formatting_img_9;
	lv_obj_t *TF_formatting_view_1;
	lv_obj_t *TF_formatting_lbl_2;
	lv_obj_t *TF_formatting_img_1;
	lv_obj_t *TF_formatting_img_2;
	lv_obj_t *TF_formatting_img_3;
} lv_ui_TF_formatting;

typedef struct {
	// Screen TF_formatting_2
	lv_obj_t *TF_formatting_2;
	bool      TF_formatting_2_del;
	lv_obj_t *TF_formatting_2_view_2;
	lv_obj_t *TF_formatting_2_lbl_2;
	lv_obj_t *TF_formatting_2_img_5;
	lv_obj_t *TF_formatting_2_view_3;
	lv_obj_t *TF_formatting_2_gif_1;
	lv_obj_t *TF_formatting_2_lbl_3;
	lv_obj_t *TF_formatting_2_bar_1;
	lv_obj_t *TF_formatting_2_view_1;
	lv_obj_t *TF_formatting_2_lbl_1;
	lv_obj_t *TF_formatting_2_img_1;
	lv_obj_t *TF_formatting_2_img_2;
	lv_obj_t *TF_formatting_2_img_3;
	lv_obj_t *TF_formatting_2_view_4;
	lv_obj_t *TF_formatting_2_img_4;
	lv_obj_t *TF_formatting_2_lbl_4;
} lv_ui_TF_formatting_2;

typedef struct {
	// Screen image_resolution
	lv_obj_t *image_resolution;
	bool      image_resolution_del;
	lv_obj_t *image_resolution_view_2;
	lv_obj_t *image_resolution_lbl_1;
	lv_obj_t *image_resolution_img_12;
	lv_obj_t *image_resolution_view_6;
	lv_obj_t *image_resolution_view_3;
	lv_obj_t *image_resolution_img_3;
	lv_obj_t *image_resolution_lbl_2;
	lv_obj_t *image_resolution_view_4;
	lv_obj_t *image_resolution_img_5;
	lv_obj_t *image_resolution_lbl_3;
	lv_obj_t *image_resolution_view_5;
	lv_obj_t *image_resolution_img_7;
	lv_obj_t *image_resolution_lbl_4;
	lv_obj_t *image_resolution_view_1;
	lv_obj_t *image_resolution_lbl_6;
	lv_obj_t *image_resolution_img_1;
	lv_obj_t *image_resolution_img_2;
	lv_obj_t *image_resolution_img_11;
} lv_ui_image_resolution;

typedef struct {
	// Screen Binding_device_code
	lv_obj_t *Binding_device_code;
	bool      Binding_device_code_del;
	lv_obj_t *Binding_device_code_view_2;
	lv_obj_t *Binding_device_code_lbl_1;
	lv_obj_t *Binding_device_code_img_12;
	lv_obj_t *Binding_device_code_view_6;
	lv_obj_t *Binding_device_code_qrcode_1;
	lv_obj_t *Binding_device_code_view_1;
	lv_obj_t *Binding_device_code_lbl_6;
	lv_obj_t *Binding_device_code_img_1;
	lv_obj_t *Binding_device_code_img_2;
	lv_obj_t *Binding_device_code_img_11;
} lv_ui_Binding_device_code;

typedef struct {
	// Screen software_version
	lv_obj_t *software_version;
	bool      software_version_del;
	lv_obj_t *software_version_view_2;
	lv_obj_t *software_version_lbl_1;
	lv_obj_t *software_version_img_12;
	lv_obj_t *software_version_view_6;
	lv_obj_t *software_version_img_3;
	lv_obj_t *software_version_btn_1;
	lv_obj_t *software_version_btn_1_label;
	lv_obj_t *software_version_lbl_2;
	lv_obj_t *software_version_lbl_4;
	lv_obj_t *software_version_lbl_3;
	lv_obj_t *software_version_view_1;
	lv_obj_t *software_version_lbl_6;
	lv_obj_t *software_version_img_1;
	lv_obj_t *software_version_img_2;
	lv_obj_t *software_version_img_11;
} lv_ui_software_version;

typedef struct {
	// Screen Restore_factory
	lv_obj_t *Restore_factory;
	bool      Restore_factory_del;
	lv_obj_t *Restore_factory_view_4;
	lv_obj_t *Restore_factory_view_7;
	lv_obj_t *Restore_factory_lbl_3;
	lv_obj_t *Restore_factory_btn_1;
	lv_obj_t *Restore_factory_btn_1_label;
	lv_obj_t *Restore_factory_img_4;
	lv_obj_t *Restore_factory_view_3;
	lv_obj_t *Restore_factory_img_5;
	lv_obj_t *Restore_factory_lbl_5;
	lv_obj_t *Restore_factory_lbl_4;
	lv_obj_t *Restore_factory_img_6;
	lv_obj_t *Restore_factory_btn_2;
	lv_obj_t *Restore_factory_btn_2_label;
	lv_obj_t *Restore_factory_btn_3;
	lv_obj_t *Restore_factory_btn_3_label;
	lv_obj_t *Restore_factory_img_7;
	lv_obj_t *Restore_factory_view_2;
	lv_obj_t *Restore_factory_lbl_1;
	lv_obj_t *Restore_factory_img_9;
	lv_obj_t *Restore_factory_view_1;
	lv_obj_t *Restore_factory_lbl_2;
	lv_obj_t *Restore_factory_img_1;
	lv_obj_t *Restore_factory_img_2;
	lv_obj_t *Restore_factory_img_3;
} lv_ui_Restore_factory;

typedef struct {
	// Screen Restore_factory_2
	lv_obj_t *Restore_factory_2;
	bool      Restore_factory_2_del;
	lv_obj_t *Restore_factory_2_view_2;
	lv_obj_t *Restore_factory_2_lbl_2;
	lv_obj_t *Restore_factory_2_view_3;
	lv_obj_t *Restore_factory_2_gif_1;
	lv_obj_t *Restore_factory_2_lbl_3;
	lv_obj_t *Restore_factory_2_bar_1;
	lv_obj_t *Restore_factory_2_view_1;
	lv_obj_t *Restore_factory_2_lbl_1;
	lv_obj_t *Restore_factory_2_img_1;
	lv_obj_t *Restore_factory_2_img_2;
	lv_obj_t *Restore_factory_2_img_3;
	lv_obj_t *Restore_factory_2_view_4;
	lv_obj_t *Restore_factory_2_img_4;
	lv_obj_t *Restore_factory_2_lbl_4;
} lv_ui_Restore_factory_2;

typedef struct {
	// Screen address_book
	lv_obj_t *address_book;
	bool      address_book_del;
	lv_obj_t *address_book_img_26;
	lv_obj_t *address_book_view_3;
	lv_obj_t *address_book_view_14;
	lv_obj_t *address_book_lbl_18;
	lv_obj_t *address_book_img_23;
	lv_obj_t *address_book_view_13;
	lv_obj_t *address_book_lbl_17;
	lv_obj_t *address_book_img_21;
	lv_obj_t *address_book_view_12;
	lv_obj_t *address_book_lbl_16;
	lv_obj_t *address_book_img_19;
	lv_obj_t *address_book_view_11;
	lv_obj_t *address_book_lbl_14;
	lv_obj_t *address_book_img_17;
	lv_obj_t *address_book_view_10;
	lv_obj_t *address_book_lbl_13;
	lv_obj_t *address_book_img_15;
	lv_obj_t *address_book_view_9;
	lv_obj_t *address_book_lbl_10;
	lv_obj_t *address_book_img_13;
	lv_obj_t *address_book_view_8;
	lv_obj_t *address_book_lbl_9;
	lv_obj_t *address_book_img_11;
	lv_obj_t *address_book_view_7;
	lv_obj_t *address_book_lbl_7;
	lv_obj_t *address_book_img_9;
	lv_obj_t *address_book_view_6;
	lv_obj_t *address_book_lbl_5;
	lv_obj_t *address_book_img_7;
	lv_obj_t *address_book_view_5;
	lv_obj_t *address_book_lbl_3;
	lv_obj_t *address_book_img_5;
	lv_obj_t *address_book_view_2;
	lv_obj_t *address_book_lbl_20;
	lv_obj_t *address_book_img_27;
	lv_obj_t *address_book_view_1;
	lv_obj_t *address_book_lbl_19;
	lv_obj_t *address_book_img_1;
	lv_obj_t *address_book_img_2;
	lv_obj_t *address_book_img_25;
	lv_obj_t *address_book_view_4;
	lv_obj_t *address_book_btn_1;
	lv_obj_t *address_book_btn_1_label;
	lv_obj_t *address_book_lbl_1;
} lv_ui_address_book;

typedef struct {
	// Screen video_resolution
	lv_obj_t *video_resolution;
	bool      video_resolution_del;
	lv_obj_t *video_resolution_view_2;
	lv_obj_t *video_resolution_lbl_1;
	lv_obj_t *video_resolution_img_12;
	lv_obj_t *video_resolution_view_1;
	lv_obj_t *video_resolution_lbl_6;
	lv_obj_t *video_resolution_img_1;
	lv_obj_t *video_resolution_img_2;
	lv_obj_t *video_resolution_img_11;
	lv_obj_t *video_resolution_view_6;
	lv_obj_t *video_resolution_view_4;
	lv_obj_t *video_resolution_img_4;
	lv_obj_t *video_resolution_lbl_3;
	lv_obj_t *video_resolution_view_5;
	lv_obj_t *video_resolution_img_5;
	lv_obj_t *video_resolution_lbl_4;
} lv_ui_video_resolution;

typedef struct {
	// Screen AI_Q_A
	lv_obj_t *AI_Q_A;
	bool      AI_Q_A_del;
	lv_obj_t *AI_Q_A_view_5;
	lv_obj_t *AI_Q_A_view_4;
	lv_obj_t *AI_Q_A_view_2;
	lv_obj_t *AI_Q_A_lbl_1;
	lv_obj_t *AI_Q_A_img_6;
	lv_obj_t *AI_Q_A_view_1;
	lv_obj_t *AI_Q_A_lbl_3;
	lv_obj_t *AI_Q_A_img_1;
	lv_obj_t *AI_Q_A_img_2;
	lv_obj_t *AI_Q_A_img_5;
	lv_obj_t *AI_Q_A_btn_1;
	lv_obj_t *AI_Q_A_btn_1_label;
	lv_obj_t *AI_Q_A_view_3;
	lv_obj_t *AI_Q_A_gif_1;
	lv_obj_t *AI_Q_A_view_6;
	lv_obj_t *AI_Q_A_img_3;
	lv_obj_t *AI_Q_A_lbl_2;
	lv_obj_t *AI_Q_A_img_4;
	lv_obj_t *AI_Q_A_btn_3;
	lv_obj_t *AI_Q_A_btn_3_label;
	lv_obj_t *AI_Q_A_img_7;
} lv_ui_AI_Q_A;

typedef struct {
	// Screen Shut_down
	lv_obj_t *Shut_down;
	bool      Shut_down_del;
	lv_obj_t *Shut_down_img_1;
	lv_obj_t *Shut_down_view_1;
	lv_obj_t *Shut_down_lbl_3;
	lv_obj_t *Shut_down_img_2;
	lv_obj_t *Shut_down_img_3;
	lv_obj_t *Shut_down_view_2;
	lv_obj_t *Shut_down_lbl_1;
	lv_obj_t *Shut_down_img_4;
	lv_obj_t *Shut_down_img_5;
} lv_ui_Shut_down;

typedef struct {
	// Screen video_dir_landscape_mode
	lv_obj_t *video_dir_landscape_mode;
	bool      video_dir_landscape_mode_del;
	lv_obj_t *video_dir_landscape_mode_img_6;
	lv_obj_t *video_dir_landscape_mode_view_2;
	lv_obj_t *video_dir_landscape_mode_img_1;
	lv_obj_t *video_dir_landscape_mode_img_2;
	lv_obj_t *video_dir_landscape_mode_img_7;
	lv_obj_t *video_dir_landscape_mode_view_4;
	lv_obj_t *video_dir_landscape_mode_view_1;
	lv_obj_t *video_dir_landscape_mode_img_8;
	lv_obj_t *video_dir_landscape_mode_img_3;
	lv_obj_t *video_dir_landscape_mode_img_4;
	lv_obj_t *video_dir_landscape_mode_img_12;
	lv_obj_t *video_dir_landscape_mode_img_11;
	lv_obj_t *video_dir_landscape_mode_img_9;
	lv_obj_t *video_dir_landscape_mode_img_10;
	lv_obj_t *video_dir_landscape_mode_img_13;
	lv_obj_t *video_dir_landscape_mode_img_14;
	lv_obj_t *video_dir_landscape_mode_img_15;
	lv_obj_t *video_dir_landscape_mode_btn_1;
	lv_obj_t *video_dir_landscape_mode_btn_1_label;
} lv_ui_video_dir_landscape_mode;

typedef struct {
	// Screen AI_payment_code
	lv_obj_t *AI_payment_code;
	bool      AI_payment_code_del;
	lv_obj_t *AI_payment_code_view_2;
	lv_obj_t *AI_payment_code_lbl_1;
	lv_obj_t *AI_payment_code_img_12;
	lv_obj_t *AI_payment_code_view_6;
	lv_obj_t *AI_payment_code_img_3;
	lv_obj_t *AI_payment_code_view_1;
	lv_obj_t *AI_payment_code_lbl_6;
	lv_obj_t *AI_payment_code_img_1;
	lv_obj_t *AI_payment_code_img_2;
	lv_obj_t *AI_payment_code_img_11;
} lv_ui_AI_payment_code;

typedef struct {
	// Screen AI_Img_Rec
	lv_obj_t *AI_Img_Rec;
	bool      AI_Img_Rec_del;
	lv_obj_t *AI_Img_Rec_view_5;
	lv_obj_t *AI_Img_Rec_view_4;
	lv_obj_t *AI_Img_Rec_btn_1;
	lv_obj_t *AI_Img_Rec_btn_1_label;
	lv_obj_t *AI_Img_Rec_view_2;
	lv_obj_t *AI_Img_Rec_lbl_1;
	lv_obj_t *AI_Img_Rec_img_6;
	lv_obj_t *AI_Img_Rec_view_1;
	lv_obj_t *AI_Img_Rec_lbl_3;
	lv_obj_t *AI_Img_Rec_img_1;
	lv_obj_t *AI_Img_Rec_img_2;
	lv_obj_t *AI_Img_Rec_img_5;
	lv_obj_t *AI_Img_Rec_lbl_4;
	lv_obj_t *AI_Img_Rec_img_8;
	lv_obj_t *AI_Img_Rec_view_6;
	lv_obj_t *AI_Img_Rec_img_3;
	lv_obj_t *AI_Img_Rec_lbl_2;
	lv_obj_t *AI_Img_Rec_img_4;
	lv_obj_t *AI_Img_Rec_btn_3;
	lv_obj_t *AI_Img_Rec_btn_3_label;
	lv_obj_t *AI_Img_Rec_img_7;
} lv_ui_AI_Img_Rec;

typedef struct {
	// Screen text
	lv_obj_t *text;
	bool      text_del;
	lv_obj_t *text_btn_1;
	lv_obj_t *text_btn_1_label;
	lv_obj_t *text_btn_2;
	lv_obj_t *text_btn_2_label;
	lv_obj_t *text_btn_3;
	lv_obj_t *text_btn_3_label;
	lv_obj_t *text_btn_4;
	lv_obj_t *text_btn_4_label;
} lv_ui_text;

typedef struct {
	// Screen chat_page
	lv_obj_t *chat_page;
	bool      chat_page_del;
	lv_obj_t *chat_page_view_5;
	lv_obj_t *chat_page_view_4;
	lv_obj_t *chat_page_view_2;
	lv_obj_t *chat_page_lbl_1;
	lv_obj_t *chat_page_img_6;
	lv_obj_t *chat_page_img_8;
	lv_obj_t *chat_page_view_1;
	lv_obj_t *chat_page_lbl_3;
	lv_obj_t *chat_page_img_1;
	lv_obj_t *chat_page_img_2;
	lv_obj_t *chat_page_img_5;
	lv_obj_t *chat_page_btn_1;
	lv_obj_t *chat_page_btn_1_label;
	lv_obj_t *chat_page_view_3;
	lv_obj_t *chat_page_gif_1;
	lv_obj_t *chat_page_view_6;
	lv_obj_t *chat_page_img_3;
	lv_obj_t *chat_page_lbl_2;
	lv_obj_t *chat_page_img_4;
	lv_obj_t *chat_page_btn_3;
	lv_obj_t *chat_page_btn_3_label;
	lv_obj_t *chat_page_img_7;
} lv_ui_chat_page;

typedef struct {
	// Screen Edit_Friend_Info
	lv_obj_t *Edit_Friend_Info;
	bool      Edit_Friend_Info_del;
	lv_obj_t *Edit_Friend_Info_view_5;
	lv_obj_t *Edit_Friend_Info_view_2;
	lv_obj_t *Edit_Friend_Info_lbl_1;
	lv_obj_t *Edit_Friend_Info_img_6;
	lv_obj_t *Edit_Friend_Info_view_1;
	lv_obj_t *Edit_Friend_Info_lbl_3;
	lv_obj_t *Edit_Friend_Info_img_1;
	lv_obj_t *Edit_Friend_Info_img_2;
	lv_obj_t *Edit_Friend_Info_img_5;
	lv_obj_t *Edit_Friend_Info_view_7;
	lv_obj_t *Edit_Friend_Info_btn_2;
	lv_obj_t *Edit_Friend_Info_btn_2_label;
	lv_obj_t *Edit_Friend_Info_btn_1;
	lv_obj_t *Edit_Friend_Info_btn_1_label;
	lv_obj_t *Edit_Friend_Info_edit_1;
	lv_obj_t *Edit_Friend_Info_img_4;
	lv_obj_t *Edit_Friend_Info_ddlist_1;
} lv_ui_Edit_Friend_Info;

typedef struct {
	// Screen Add_friend
	lv_obj_t *Add_friend;
	bool      Add_friend_del;
	lv_obj_t *Add_friend_view_5;
	lv_obj_t *Add_friend_view_4;
	lv_obj_t *Add_friend_btn_1;
	lv_obj_t *Add_friend_btn_1_label;
	lv_obj_t *Add_friend_view_2;
	lv_obj_t *Add_friend_lbl_1;
	lv_obj_t *Add_friend_img_6;
	lv_obj_t *Add_friend_view_1;
	lv_obj_t *Add_friend_lbl_3;
	lv_obj_t *Add_friend_img_1;
	lv_obj_t *Add_friend_img_2;
	lv_obj_t *Add_friend_img_5;
	lv_obj_t *Add_friend_view_6;
	lv_obj_t *Add_friend_img_3;
	lv_obj_t *Add_friend_lbl_2;
	lv_obj_t *Add_friend_img_4;
	lv_obj_t *Add_friend_btn_3;
	lv_obj_t *Add_friend_btn_3_label;
	lv_obj_t *Add_friend_img_7;
	lv_obj_t *Add_friend_view_3;
	lv_obj_t *Add_friend_lbl_5;
	lv_obj_t *Add_friend_lbl_4;
	lv_obj_t *Add_friend_lbl_6;
} lv_ui_Add_friend;

typedef struct {
	// Screen call
	lv_obj_t *call;
	bool      call_del;
	lv_obj_t *call_view_5;
	lv_obj_t *call_lbl_4;
	lv_obj_t *call_view_1;
	lv_obj_t *call_lbl_3;
	lv_obj_t *call_img_1;
	lv_obj_t *call_img_2;
	lv_obj_t *call_img_5;
	lv_obj_t *call_view_6;
	lv_obj_t *call_img_3;
	lv_obj_t *call_lbl_2;
	lv_obj_t *call_img_4;
	lv_obj_t *call_btn_3;
	lv_obj_t *call_btn_3_label;
	lv_obj_t *call_img_7;
	lv_obj_t *call_view_3;
	lv_obj_t *call_lbl_1;
	lv_obj_t *call_img_8;
	lv_obj_t *call_img_9;
	lv_obj_t *call_img_10;
	lv_obj_t *call_img_11;
	lv_obj_t *call_img_12;
	lv_obj_t *call_img_13;
} lv_ui_call;

typedef struct {
	// Screen zyf_ai_page
	lv_obj_t *zyf_ai_page;
	bool      zyf_ai_page_del;
	lv_obj_t *zyf_ai_page_view_1;
	lv_obj_t *zyf_ai_page_img_1;
	lv_obj_t *zyf_ai_page_btn_1;
	lv_obj_t *zyf_ai_page_btn_1_label;
} lv_ui_zyf_ai_page;

// generate lv_ui gui_guider
typedef struct {
	lv_ui_home_page *home_page;
	lv_ui_video_rec *video_rec;
	lv_ui_sys_prompt *sys_prompt;
	lv_ui_video_photo *video_photo;
	lv_ui_video_play *video_play;
	lv_ui_sys_popwin *sys_popwin;
	lv_ui_usb_slave *usb_slave;
	lv_ui_Language_Selection *Language_Selection;
	lv_ui_WIFI_search *WIFI_search;
	lv_ui_WIFI_connection *WIFI_connection;
	lv_ui_seting *seting;
	lv_ui_brightness *brightness;
	lv_ui_volume *volume;
	lv_ui_dormancy *dormancy;
	lv_ui_image_size *image_size;
	lv_ui_TF_formatting *TF_formatting;
	lv_ui_TF_formatting_2 *TF_formatting_2;
	lv_ui_image_resolution *image_resolution;
	lv_ui_Binding_device_code *Binding_device_code;
	lv_ui_software_version *software_version;
	lv_ui_Restore_factory *Restore_factory;
	lv_ui_Restore_factory_2 *Restore_factory_2;
	lv_ui_address_book *address_book;
	lv_ui_video_resolution *video_resolution;
	lv_ui_AI_Q_A *AI_Q_A;
	lv_ui_Shut_down *Shut_down;
	lv_ui_video_dir_landscape_mode *video_dir_landscape_mode;
	lv_ui_AI_payment_code *AI_payment_code;
	lv_ui_AI_Img_Rec *AI_Img_Rec;
	lv_ui_text *text;
	lv_ui_chat_page *chat_page;
	lv_ui_Edit_Friend_Info *Edit_Friend_Info;
	lv_ui_Add_friend *Add_friend;
	lv_ui_call *call;
	lv_ui_zyf_ai_page *zyf_ai_page;
	
	lv_group_t *default_group;
} lv_ui;

void ui_load_scr_anim(lv_ui *ui, gui_scr_t *screen, lv_scr_load_anim_t anim_type,	uint32_t time,
											uint32_t delay, bool is_clean, bool auto_del, bool is_push_satck);

void ui_scr_stack_pop_anim(lv_ui *ui, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay,
														bool is_clean, bool auto_del, bool is_push_satck);

gui_scr_t * ui_get_scr(int32_t scr_id);
gui_scr_t * ui_get_setup_scr(int32_t scr_id);
lv_obj_t * ui_get_setup_scr_obj(int32_t scr_id);
void * ui_get_scr_ptr(lv_ui *ui, int32_t scr_id);
void ui_free_scr_ptr(lv_ui *ui, int32_t scr_id);
bool ui_is_act_scr(int32_t scr_id);
void ui_init_style(lv_style_t * style);
void setup_ui(lv_ui *ui);
#include "./gui_msg/gui_msg.h"
extern lv_ui guider_ui;// Screen home_page
lv_obj_t * setup_scr_home_page(lv_ui *ui);
void unload_scr_home_page(lv_ui *ui);
/*DigitalClock*/
void clock_count_with_year(int *year, int *month, int *day, int *hour, int *min, int *sec);
// Screen video_rec
lv_obj_t * setup_scr_video_rec(lv_ui *ui);
void unload_scr_video_rec(lv_ui *ui);
// Screen sys_prompt
lv_obj_t * setup_scr_sys_prompt(lv_ui *ui);
void unload_scr_sys_prompt(lv_ui *ui);
// Screen video_photo
lv_obj_t * setup_scr_video_photo(lv_ui *ui);
void unload_scr_video_photo(lv_ui *ui);
// Screen video_play
lv_obj_t * setup_scr_video_play(lv_ui *ui);
void unload_scr_video_play(lv_ui *ui);
// Screen sys_popwin
lv_obj_t * setup_scr_sys_popwin(lv_ui *ui);
void unload_scr_sys_popwin(lv_ui *ui);
// Screen usb_slave
lv_obj_t * setup_scr_usb_slave(lv_ui *ui);
void unload_scr_usb_slave(lv_ui *ui);
// Screen Language_Selection
lv_obj_t * setup_scr_Language_Selection(lv_ui *ui);
void unload_scr_Language_Selection(lv_ui *ui);
// Screen WIFI_search
lv_obj_t * setup_scr_WIFI_search(lv_ui *ui);
void unload_scr_WIFI_search(lv_ui *ui);
// Screen WIFI_connection
lv_obj_t * setup_scr_WIFI_connection(lv_ui *ui);
void unload_scr_WIFI_connection(lv_ui *ui);
// Screen seting
lv_obj_t * setup_scr_seting(lv_ui *ui);
void unload_scr_seting(lv_ui *ui);
// Screen brightness
lv_obj_t * setup_scr_brightness(lv_ui *ui);
void unload_scr_brightness(lv_ui *ui);
// Screen volume
lv_obj_t * setup_scr_volume(lv_ui *ui);
void unload_scr_volume(lv_ui *ui);
// Screen dormancy
lv_obj_t * setup_scr_dormancy(lv_ui *ui);
void unload_scr_dormancy(lv_ui *ui);
// Screen image_size
lv_obj_t * setup_scr_image_size(lv_ui *ui);
void unload_scr_image_size(lv_ui *ui);
// Screen TF_formatting
lv_obj_t * setup_scr_TF_formatting(lv_ui *ui);
void unload_scr_TF_formatting(lv_ui *ui);
// Screen TF_formatting_2
lv_obj_t * setup_scr_TF_formatting_2(lv_ui *ui);
void unload_scr_TF_formatting_2(lv_ui *ui);
// Screen image_resolution
lv_obj_t * setup_scr_image_resolution(lv_ui *ui);
void unload_scr_image_resolution(lv_ui *ui);
// Screen Binding_device_code
lv_obj_t * setup_scr_Binding_device_code(lv_ui *ui);
void unload_scr_Binding_device_code(lv_ui *ui);
// Screen software_version
lv_obj_t * setup_scr_software_version(lv_ui *ui);
void unload_scr_software_version(lv_ui *ui);
// Screen Restore_factory
lv_obj_t * setup_scr_Restore_factory(lv_ui *ui);
void unload_scr_Restore_factory(lv_ui *ui);
// Screen Restore_factory_2
lv_obj_t * setup_scr_Restore_factory_2(lv_ui *ui);
void unload_scr_Restore_factory_2(lv_ui *ui);
// Screen address_book
lv_obj_t * setup_scr_address_book(lv_ui *ui);
void unload_scr_address_book(lv_ui *ui);
// Screen video_resolution
lv_obj_t * setup_scr_video_resolution(lv_ui *ui);
void unload_scr_video_resolution(lv_ui *ui);
// Screen AI_Q_A
lv_obj_t * setup_scr_AI_Q_A(lv_ui *ui);
void unload_scr_AI_Q_A(lv_ui *ui);
// Screen Shut_down
lv_obj_t * setup_scr_Shut_down(lv_ui *ui);
void unload_scr_Shut_down(lv_ui *ui);
// Screen video_dir_landscape_mode
lv_obj_t * setup_scr_video_dir_landscape_mode(lv_ui *ui);
void unload_scr_video_dir_landscape_mode(lv_ui *ui);
// Screen AI_payment_code
lv_obj_t * setup_scr_AI_payment_code(lv_ui *ui);
void unload_scr_AI_payment_code(lv_ui *ui);
// Screen AI_Img_Rec
lv_obj_t * setup_scr_AI_Img_Rec(lv_ui *ui);
void unload_scr_AI_Img_Rec(lv_ui *ui);
// Screen text
lv_obj_t * setup_scr_text(lv_ui *ui);
void unload_scr_text(lv_ui *ui);
// Screen chat_page
lv_obj_t * setup_scr_chat_page(lv_ui *ui);
void unload_scr_chat_page(lv_ui *ui);
// Screen Edit_Friend_Info
lv_obj_t * setup_scr_Edit_Friend_Info(lv_ui *ui);
void unload_scr_Edit_Friend_Info(lv_ui *ui);
// Screen Add_friend
lv_obj_t * setup_scr_Add_friend(lv_ui *ui);
void unload_scr_Add_friend(lv_ui *ui);
// Screen call
lv_obj_t * setup_scr_call(lv_ui *ui);
void unload_scr_call(lv_ui *ui);
// Screen zyf_ai_page
lv_obj_t * setup_scr_zyf_ai_page(lv_ui *ui);
void unload_scr_zyf_ai_page(lv_ui *ui);
#ifdef __cplusplus
}
#endif
#endif

#endif
