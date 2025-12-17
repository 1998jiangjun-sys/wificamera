#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#ifndef GUI_IMAGES_H_
#define GUI_IMAGES_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// Image Declare
LV_IMG_DECLARE(_mipmap_xhdpi_mipmap_xhdpi_set_fail_alpha160x160);
LV_IMG_DECLARE(_mipmap_xhdpi_480slices123_sticker_1_120_alpha120x120);
LV_IMG_DECLARE(_mipmap_xhdpi_480slices123_sticker_2_120_alpha120x120);
LV_IMG_DECLARE(_mipmap_xhdpi_480slices123_sticker_3_120_alpha120x120);
LV_IMG_DECLARE(_mipmap_xhdpi_480slices123_sticker_4_120_alpha120x120);
LV_IMG_DECLARE(_mipmap_xhdpi_480slices123_sticker_6_120_alpha120x120);
LV_IMG_DECLARE(_mipmap_xhdpi_480slices123_sticker_7_120_alpha120x120);
LV_IMG_DECLARE(_mipmap_xhdpi_480slices123_sticker_8_120_alpha120x120);
LV_IMG_DECLARE(_mipmap_xhdpi_480slices123_sticker_5_120_alpha120x120);
LV_IMG_DECLARE(_new_slices_select_alpha32x32);
LV_IMG_DECLARE(_new_slices_select_no_alpha32x32);
LV_IMG_DECLARE(_new_slices_wlan_wifi1_alpha64x64);
LV_IMG_DECLARE(_new_slices_wlan_wifi2_alpha64x64);
LV_IMG_DECLARE(_new_slices_wlan_wifi3_alpha64x64);
LV_IMG_DECLARE(_new_slices_wlan_wifi4_alpha64x64);

#define RES_C_SET_FAIL 1
#define RES_C_STICKER_1_120 2
#define RES_C_STICKER_2_120 3
#define RES_C_STICKER_3_120 4
#define RES_C_STICKER_4_120 5
#define RES_C_STICKER_6_120 6
#define RES_C_STICKER_7_120 7
#define RES_C_STICKER_8_120 8
#define RES_C_STICKER_5_120 9
#define RES_C_SELECT_1 10
#define RES_C_SELECT_NO_1 11
#define RES_C_SELECT 12
#define RES_C_SELECT_NO 13
#define RES_C_WLAN_WIFI1 14
#define RES_C_WLAN_WIFI2 15
#define RES_C_WLAN_WIFI3 16
#define RES_C_WLAN_WIFI4 17

#define GUI_GET_C_IMAGE(id) \
	((id == RES_C_SET_FAIL) ? &_mipmap_xhdpi_mipmap_xhdpi_set_fail_alpha160x160 : \
	((id == RES_C_STICKER_1_120) ? &_mipmap_xhdpi_480slices123_sticker_1_120_alpha120x120 : \
	((id == RES_C_STICKER_2_120) ? &_mipmap_xhdpi_480slices123_sticker_2_120_alpha120x120 : \
	((id == RES_C_STICKER_3_120) ? &_mipmap_xhdpi_480slices123_sticker_3_120_alpha120x120 : \
	((id == RES_C_STICKER_4_120) ? &_mipmap_xhdpi_480slices123_sticker_4_120_alpha120x120 : \
	((id == RES_C_STICKER_6_120) ? &_mipmap_xhdpi_480slices123_sticker_6_120_alpha120x120 : \
	((id == RES_C_STICKER_7_120) ? &_mipmap_xhdpi_480slices123_sticker_7_120_alpha120x120 : \
	((id == RES_C_STICKER_8_120) ? &_mipmap_xhdpi_480slices123_sticker_8_120_alpha120x120 : \
	((id == RES_C_STICKER_5_120) ? &_mipmap_xhdpi_480slices123_sticker_5_120_alpha120x120 : \
	((id == RES_C_SELECT_1) ? &_new_slices_select_alpha32x32 : \
	((id == RES_C_SELECT_NO_1) ? &_new_slices_select_no_alpha32x32 : \
	((id == RES_C_SELECT) ? &_new_slices_select_alpha32x32 : \
	((id == RES_C_SELECT_NO) ? &_new_slices_select_no_alpha32x32 : \
	((id == RES_C_WLAN_WIFI1) ? &_new_slices_wlan_wifi1_alpha64x64 : \
	((id == RES_C_WLAN_WIFI2) ? &_new_slices_wlan_wifi2_alpha64x64 : \
	((id == RES_C_WLAN_WIFI3) ? &_new_slices_wlan_wifi3_alpha64x64 : \
	((id == RES_C_WLAN_WIFI4) ? &_new_slices_wlan_wifi4_alpha64x64 : \
	NULL)))))))))))))))))

// Lottie Declare
#define LV_LOT_DECLARE(array_name) extern const uint8_t array_name[];

#ifdef __cplusplus
}
#endif
#endif /* GUI_IMAGES_H_ */

#endif
