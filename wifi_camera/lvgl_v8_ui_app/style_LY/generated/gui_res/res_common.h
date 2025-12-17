#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#ifndef __RES_COMMON_H__
#define __RES_COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#if LV_USE_GUIBUILDER_SIMULATOR
	#define GUI_WEAKREF __attribute__((weakref))
	#define GUI_WEAK __attribute__((weak))
#else
	#define GUI_WEAKREF
	#define GUI_WEAK __attribute__((weak))
#endif

#define CONV_RES_ID(id) (((id) >> 24) | ((id) & 0x00FFFFFF) << 8)
typedef enum {
	GUI_RES_FANGZHENGKAITIJIANTI_1_54_TTF_FLASH = 0x35000000,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000000.rle
	GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF_FLASH = 0x35000001,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000001.rle
	GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF_FLASH = 0x35000002,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000002.rle
	GUI_RES_SIMSUN_28_WOFF_FLASH = 0x35000003,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000003.rle
	GUI_RES_SIMSUN_36_WOFF_FLASH = 0x35000004,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000004.rle
	GUI_RES_SIMSUN_20_WOFF_FLASH = 0x35000005,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000005.rle
	GUI_RES_SIMSUN_32_WOFF_FLASH = 0x35000006,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000006.rle
	GUI_RES_ARIALMT_38_TTF_FLASH = 0x35000007,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000007.rle
	GUI_RES_MONTSERRATMEDIUM_24_TTF_FLASH = 0x35000008,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000008.rle
	GUI_RES_MONTSERRATMEDIUM_12_TTF_FLASH = 0x35000009,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000009.rle
	GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF_FLASH = 0x3500000A,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500000a.rle
	GUI_RES_MONTSERRATMEDIUM_16_TTF_FLASH = 0x3500000B,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500000b.rle
	GUI_RES_MANGAL_28_TTF_FLASH = 0x3500000C,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500000c.rle
	GUI_RES_SIMPO_28_TTF_FLASH = 0x3500000D,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500000d.rle
	GUI_RES_SIMSUN_24_WOFF_FLASH = 0x3500000E,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500000e.rle
	GUI_RES_LEELAWADEEUI_32_TTF_FLASH = 0x3500000F,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500000f.rle
	GUI_RES_FANGSONG_32_TTF_FLASH = 0x35000010,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000010.rle
	GUI_RES_SIMSUN_26_WOFF_FLASH = 0x35000011,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000011.rle
	GUI_RES_SIMSUN_16_WOFF_FLASH = 0x35000012,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000012.rle
	GUI_RES_SIMSUN_12_WOFF_FLASH = 0x35000013,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000013.rle
	GUI_RES_ARIALMT_56_TTF_FLASH = 0x35000014,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000014.rle
	GUI_RES_SIMSUN_25_WOFF_FLASH = 0x35000015,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000015.rle
	GUI_RES_TIMESNEWROMANPSMT_36_TTF_FLASH = 0x35000016,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000016.rle
	GUI_RES_TIMESNEWROMANPSMT_30_TTF_FLASH = 0x35000017,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000017.rle
	GUI_RES_TIMESNEWROMANPSMT_40_TTF_FLASH = 0x35000018,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000018.rle
	GUI_RES_TIMESNEWROMANPSMT_32_TTF_FLASH = 0x35000019,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000019.rle
	GUI_RES_TIMESNEWROMANPSMT_12_TTF_FLASH = 0x3500001A,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500001a.rle
	GUI_RES_TIMESNEWROMANPSMT_28_TTF_FLASH = 0x3500001B,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500001b.rle
	GUI_RES_TIMESNEWROMANPSMT_24_TTF_FLASH = 0x3500001C,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500001c.rle
	GUI_RES_TIMESNEWROMANPSMT_29_TTF_FLASH = 0x3500001D,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500001d.rle
	GUI_RES_TIMESNEWROMANPSMT_26_TTF_FLASH = 0x3500001E,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500001e.rle
	GUI_RES_MANGAL_36_TTF_FLASH = 0x3500001F,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500001f.rle
	GUI_RES_MANGAL_12_TTF_FLASH = 0x35000020,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000020.rle
	GUI_RES_MANGAL_40_TTF_FLASH = 0x35000021,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000021.rle
	GUI_RES_MANGAL_30_TTF_FLASH = 0x35000022,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000022.rle
	GUI_RES_MANGAL_32_TTF_FLASH = 0x35000023,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000023.rle
	GUI_RES_MANGAL_24_TTF_FLASH = 0x35000024,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000024.rle
	GUI_RES_MANGAL_29_TTF_FLASH = 0x35000025,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000025.rle
	GUI_RES_MANGAL_33_TTF_FLASH = 0x35000026,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000026.rle
	GUI_RES_MANGAL_26_TTF_FLASH = 0x35000027,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000027.rle
	GUI_RES_TIMESNEWROMANPSMT_33_TTF_FLASH = 0x35000028,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000028.rle
	GUI_RES_TIMESNEWROMANPSMT_34_TTF_FLASH = 0x35000029,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000029.rle
	GUI_RES_SIMPLIFIEDARABIC_36_TTF_FLASH = 0x3500002A,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500002a.rle
	GUI_RES_SIMPLIFIEDARABIC_12_TTF_FLASH = 0x3500002B,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500002b.rle
	GUI_RES_SIMPLIFIEDARABIC_40_TTF_FLASH = 0x3500002C,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500002c.rle
	GUI_RES_SIMPLIFIEDARABIC_30_TTF_FLASH = 0x3500002D,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500002d.rle
	GUI_RES_SIMPLIFIEDARABIC_32_TTF_FLASH = 0x3500002E,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500002e.rle
	GUI_RES_SIMPLIFIEDARABIC_28_TTF_FLASH = 0x3500002F,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\3500002f.rle
	GUI_RES_SIMPLIFIEDARABIC_24_TTF_FLASH = 0x35000030,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000030.rle
	GUI_RES_SIMPLIFIEDARABIC_29_TTF_FLASH = 0x35000031,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000031.rle
	GUI_RES_SIMPLIFIEDARABIC_33_TTF_FLASH = 0x35000032,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000032.rle
	GUI_RES_SIMPLIFIEDARABIC_26_TTF_FLASH = 0x35000033,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000033.rle
	GUI_RES_FANGSONG_16_TTF_FLASH = 0x35000034,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\sdk\ui_res\flash\rle\font\35000034.rle

	GUI_RES_EZGIF_26D3AE8D7434C37A_GIF = 0x42000035,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\gif\ezgif_26d3ae8d7434c37a.gif
	GUI_RES_EZGIF_3A421AA367158DBB_GIF = 0x42000036,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\gif\ezgif_3a421aa367158dbb.gif
	GUI_RES_EZGIF_3F026D4EC0A484F1_GIF = 0x42000037,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\gif\ezgif_3f026d4ec0a484f1.gif

	GUI_RES_IMAGE_4215637_0_PNG = 0x4B000038,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\image_4215637_0.png
	GUI_RES_HOME_AI_PNG = 0x4B000039,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\home_ai.png
	GUI_RES_HOME_SETTING_PNG = 0x4B00003A,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\home_setting.png
	GUI_RES_HOME_ALBUM_PNG = 0x4B00003B,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\home_album.png
	GUI_RES_HOME_COMMUNICATION_PNG = 0x4B00003C,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\home_communication.png
	GUI_RES_HOME_PHOTOGRAPH_PNG = 0x4B00003D,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\home_photograph.png
	GUI_RES_HOME_RECORD_PNG = 0x4B00003E,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\home_record.png
	GUI_RES_HOME_PHOTOGRAPH_1_PNG = 0x4B00003F,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\photo\home_photograph.png
	GUI_RES_HOME_IMG_PNG = 0x4B000040,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\home_img.png
	GUI_RES_WIFI_4_PNG = 0x4B000041,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\video_page\battery\mipmap_xhdpi\wifi_4.png
	GUI_RES_3_PNG = 0x4B000042,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\3.png
	GUI_RES_BG_POP_PNG = 0x4B000043,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\bg_pop.png
	GUI_RES_IMAGE_7991533_0_PNG = 0x4B000044,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\image_7991533_0.png
	GUI_RES_HOME_REMIND_PNG = 0x4B000045,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\home_remind.png
	GUI_RES_HOME_WLAN_PNG = 0x4B000046,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\home_wlan.png
	GUI_RES_BACK_PNG = 0x4B000047,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\back.png
	GUI_RES_VIDEO_REC_PNG = 0x4B000048,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\video_rec.png
	GUI_RES_IMG_0_PNG = 0x4B000049,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\img_0.png
	GUI_RES_IMAGE_2154541_0_PNG = 0x4B00004A,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\image_2154541_0.png
	GUI_RES_POP_UP_WINDOW_PNG = 0x4B00004B,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\video_page\pop_up_window.png
	GUI_RES_FLIG_ON_PNG = 0x4B00004C,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\video_page\flig_on.png
	GUI_RES_ASTERN_PNG = 0x4B00004D,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\video_page\astern.png
	GUI_RES_PHOTOGRAPH_CLOSE_PNG = 0x4B00004E,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\photograph_close.png
	GUI_RES_PHOTOGRAPH_LEFT_PNG = 0x4B00004F,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\photograph_left.png
	GUI_RES_PHOTOGRAPH_NEXT_PNG = 0x4B000050,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\photograph_next.png
	GUI_RES_STICKER_3_72_PNG = 0x4B000051,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\sticker_3_72.png
	GUI_RES_STICKER_2_72_PNG = 0x4B000052,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\sticker_2_72.png
	GUI_RES_STICKER_1_72_PNG = 0x4B000053,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\sticker_1_72.png
	GUI_RES_STICKER_4_72_PNG = 0x4B000054,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\sticker_4_72.png
	GUI_RES_STICKER_5_72_PNG = 0x4B000055,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\sticker_5_72.png
	GUI_RES_STICKER_6_72_PNG = 0x4B000056,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\sticker_6_72.png
	GUI_RES_STICKER_8_72_PNG = 0x4B000057,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\sticker_8_72.png
	GUI_RES_STICKER_7_72_PNG = 0x4B000058,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\sticker_7_72.png
	GUI_RES_PHOTOGRAPH_PNG = 0x4B000059,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\photograph.png
	GUI_RES_BACK_1_PNG = 0x4B00005A,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\new_landscape_mode\back.png
	GUI_RES_PHOTOGRAPH_NARROW_PNG = 0x4B00005B,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\photograph_narrow.png
	GUI_RES_PHOTOGRAPH_ENLARGE_PNG = 0x4B00005C,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\photograph_enlarge.png
	GUI_RES_HOME_STICK_PNG = 0x4B00005D,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\home_stick.png
	GUI_RES_PHOTO_PLAY_PNG = 0x4B00005E,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\photo_play.png
	GUI_RES_PHOTO_PAUSE_PNG = 0x4B00005F,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\photo_pause.png
	GUI_RES_PHOTO_BEFORE_PNG = 0x4B000060,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\photo_before.png
	GUI_RES_PHOTO_NEXT_PNG = 0x4B000061,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\photo_next.png
	GUI_RES_SET_SPEAKER_W_PNG = 0x4B000062,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\set_speaker_w.png
	GUI_RES_SET_SPEAKER_UN_PNG = 0x4B000063,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\set_speaker_un.png
	GUI_RES_PHOTO_PNG = 0x4B000064,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\PHOTO.png
	GUI_RES_PHOTO_ON_PNG = 0x4B000065,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\photo_on.png
	GUI_RES_SELECT_NO_PNG = 0x4B000066,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\select_no.png
	GUI_RES_HINDI_PNG = 0x4B000067,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\hindi.png
	GUI_RES_SELECT_PNG = 0x4B000068,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\select.png
	GUI_RES_ENGLISH_PNG = 0x4B000069,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\english.png
	GUI_RES_FRENCH_PNG = 0x4B00006A,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\french.png
	GUI_RES_PORTUGUESE_PNG = 0x4B00006B,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\portuguese.png
	GUI_RES_SPAIN_PNG = 0x4B00006C,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\spain.png
	GUI_RES_RUSSIA_PNG = 0x4B00006D,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\russia.png
	GUI_RES_ARABIC_PNG = 0x4B00006E,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\arabic.png
	GUI_RES_CHINA_PNG = 0x4B00006F,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\china.png
	GUI_RES_BACK_2_PNG = 0x4B000070,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\back.png
	GUI_RES_WLAN_REFRESH_PNG = 0x4B000071,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\wlan_refresh.png
	GUI_RES_IMAGE_9998327_0_PNG = 0x4B000072,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\image_9998327_0.png
	GUI_RES_IMAGE_8787409_0_PNG = 0x4B000073,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\image_8787409_0.png
	GUI_RES_SET_VIDEO_PNG = 0x4B000074,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_video.png
	GUI_RES_SET_RECOVER_PNG = 0x4B000075,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_recover.png
	GUI_RES_SET_VERSION_PNG = 0x4B000076,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_version.png
	GUI_RES_SET_BINDING_PNG = 0x4B000077,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_binding.png
	GUI_RES_SET_PICTURE_PNG = 0x4B000078,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_picture.png
	GUI_RES_SET_TF_PNG = 0x4B000079,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_tf.png
	GUI_RES_SET_SIZE_PNG = 0x4B00007A,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_size.png
	GUI_RES_SET_SCREEN_OFF_PNG = 0x4B00007B,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_screen_off.png
	GUI_RES_SET_WIFI_PNG = 0x4B00007C,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_wifi.png
	GUI_RES_SET_LANGUAGE_PNG = 0x4B00007D,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_language.png
	GUI_RES_SET_VOLUME_PNG = 0x4B00007E,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_volume.png
	GUI_RES_SET_BRIGHTNESS_PNG = 0x4B00007F,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_brightness.png
	GUI_RES_BG_ADVANCED_PNG = 0x4B000080,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\bg_advanced.png
	GUI_RES_SET_PNG = 0x4B000081,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\set.png
	GUI_RES_SET_BRIGHTNESS_M_PNG = 0x4B000082,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_brightness_m.png
	GUI_RES_SET_BRIGHTNESS_B_PNG = 0x4B000083,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_brightness_b.png
	GUI_RES_SET_SPEAKER_UN_1_PNG = 0x4B000084,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_speaker_un.png
	GUI_RES_SET_SPEAKER_W_1_PNG = 0x4B000085,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_speaker_w.png
	GUI_RES_SET_SCREEN_W_PNG = 0x4B000086,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_screen_w.png
	GUI_RES_SET_SIZE_W_PNG = 0x4B000087,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\set_size_w.png
	GUI_RES_HOME_CARD_PNG = 0x4B000088,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\home_card.png
	GUI_RES_HOME_WARNING_PNG = 0x4B000089,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\home_warning.png
	GUI_RES_SET_OK_PNG = 0x4B00008A,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\set_ok.png
	GUI_RES_LOGO_PNG = 0x4B00008B,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\buchong\logo.png
	GUI_RES_SET_OK_1_PNG = 0x4B00008C,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\set_ok.png
	GUI_RES_COMMUNICATION_EDIT_PNG = 0x4B00008D,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\communication_edit.png
	GUI_RES_COMMUNICATION_PNG = 0x4B00008E,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\communication.png
	GUI_RES_AI_PNG = 0x4B00008F,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\ai.png
	GUI_RES_HOME_ERROR_PNG = 0x4B000090,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\home_error.png
	GUI_RES_SHUTDOWN_PNG = 0x4B000091,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\shutdown.png
	GUI_RES_IMAGE_2242091_0_PNG = 0x4B000092,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\image_2242091_0.png
	GUI_RES_DELETED_PNG = 0x4B000093,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\new_landscape_mode\deleted.png
	GUI_RES_BG_POP_1_PNG = 0x4B000094,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\bg_pop.png
	GUI_RES_SURE_BTN_PNG = 0x4B000095,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\sure_btn.png
	GUI_RES_CANCEL_BTN_PNG = 0x4B000096,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\cancel_btn.png
	GUI_RES_TEXT_COPYWRITING_PNG = 0x4B000097,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\text_copywriting.png
	GUI_RES_TEXT_TITLE_PNG = 0x4B000098,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\text_title.png
	GUI_RES_HOME_ALBUM_1_PNG = 0x4B000099,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\home_album.png
	GUI_RES_TEXT_DELETED_IMG_PNG = 0x4B00009A,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\text_deleted_img.png
	GUI_RES_TEXT_LOADING_IMG_PNG = 0x4B00009B,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\text_loading_img.png
	GUI_RES_IMAGE_3532909_0_PNG = 0x4B00009C,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\image_3532909_0.png
	GUI_RES_ALBUM_PNG = 0x4B00009D,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\album.png
	GUI_RES_CALL_PNG = 0x4B00009E,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\call.png
	GUI_RES_COMMUNICATION_DOWN_PNG = 0x4B00009F,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\new_slices\communication_down.png
	GUI_RES_COMMUNICATION_HANG_PNG = 0x4B0000A0,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\communication_hang.png
	GUI_RES_COMMUNICATION_ANSWER_PNG = 0x4B0000A1,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\communication_answer.png
	GUI_RES_COMMUNICATION_MIC_PNG = 0x4B0000A2,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\communication_mic.png
	GUI_RES_COMMUNICATION_SPEAKER_PNG = 0x4B0000A3,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\communication_speaker.png
	GUI_RES_BACK_3_PNG = 0x4B0000A4,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\photo\back.png
} GUI_RES_ID;

typedef enum {
	RES_0 = 0x740000A5,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\0.png 32x32
	RES_1 = 0x740000A6,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\1.png 32x32
	RES_2 = 0x740000A7,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\2.png 32x32
	RES_3 = 0x740000A8,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\3.png 32x32
	RES_CHARGING = 0x740000A9,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\charging.png 32x32
	RES_FULL = 0x740000AA,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\full.png 32x32
	RES_IMG_1 = 0x740000AB,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\img_1.png 16x12
	RES_IMG_2 = 0x740000AC,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\img_2.png 16x12
	RES_IMG_3 = 0x740000AD,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\img_3.png 16x12
	RES_IMG_4 = 0x740000AE,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\img_4.png 16x12
	RES_IMG_5 = 0x740000AF,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\img_5.png 16x12
	RES_IMG_6 = 0x740000B0,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\img_6.png 16x12
	RES_IMG_7 = 0x740000B1,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\img_7.png 16x12
	RES_IMG_8 = 0x740000B2,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\img_8.png 16x12
	RES_IMG_9 = 0x740000B3,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\img_9.png 16x12
	RES_WIFI_1 = 0x740000B4,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\wifi_1.png 32x32
	RES_WIFI_2 = 0x740000B5,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\wifi_2.png 32x32
	RES_WIFI_3 = 0x740000B6,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\wifi_3.png 32x32
	RES_WIFI_4 = 0x740000B7,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\wifi_4.png 32x32
	RES_WIFI_NO = 0x740000B8,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\wifi_no.png 32x32
	RES_IMAGE_2942849_0 = 0x740000B9,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\slices\image_2942849_0.png 240x240
	RES_IMAGE_2942849_1 = 0x740000BA,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\slices\image_2942849_1.png 240x240
	RES_IMAGE_2942849_2 = 0x740000BB,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\slices\image_2942849_2.png 240x240
	RES_IMAGE_2942849_3 = 0x740000BC,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\slices\image_2942849_3.png 240x240
	RES_IMAGE_2942849_4 = 0x740000BD,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\slices\image_2942849_4.png 240x240
	RES_IMAGE_2942849_5 = 0x740000BE,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\slices\image_2942849_5.png 240x240
	RES_IMAGE_2942849_6 = 0x740000BF,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\slices\image_2942849_6.png 240x240
	RES_IMAGE_2942849_7 = 0x740000C0,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\slices\image_2942849_7.png 240x240
	RES_VIDEO = 0x740000C1,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\video.png 24x24
	RES_IMAGE_3532909_0 = 0x740000C2,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\480slices123\image_3532909_0.png 48x48
	RES_IMAGE_2242091_0 = 0x740000C3,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\mipmap_xhdpi\mipmap_xhdpi\image_2242091_0.png 34x70
	RES_ALBUM_E = 0x740000C4,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\Album_e.png 28x103
	RES_CANCEL_BTN_E = 0x740000C5,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\cancel_btn_e.png 66x180
	RES_CANCEL_E = 0x740000C6,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\cancel_e.png 22x83
	RES_CHOOSE_CANCEL_BTN_E = 0x740000C7,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\choose_cancel_btn_e.png 66x292
	RES_CHOOSE_SHARE_BTN_E = 0x740000C8,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\choose_share_btn_e.png 66x292
	RES_CHOOSE_TEXT_IMG_E = 0x740000C9,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\choose_text_img_e.png 94x640
	RES_SURE_BTN_E = 0x740000CA,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\sure_btn_e.png 66x180
	RES_SURE_E = 0x740000CB,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\sure_e.png 22x98
	RES_TEXT_CHOOSE_E = 0x740000CC,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_choose_e.png 28x229
	RES_TEXT_COPYWRITING_E = 0x740000CD,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_copywriting_e.png 59x305
	RES_TEXT_DELETED_IMG_E = 0x740000CE,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_deleted_img_e.png 129x244
	RES_TEXT_DELETED_TOAST_E = 0x740000CF,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_deleted_toast_e.png 19x188
	RES_TEXT_IMAGE_RECOGNITION_E = 0x740000D0,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_image_recognition_e.png 34x287
	RES_TEXT_LOADING_IMG_E = 0x740000D1,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_loading_img_e.png 129x156
	RES_TEXT_LOADING_TOAST_E = 0x740000D2,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_loading_toast_e.png 23x100
	RES_TEXT_ONEMORE_BTN_E = 0x740000D3,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_onemore_btn_e.png 76x596
	RES_TEXT_ONEMORE_E = 0x740000D4,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_onemore_e.png 27x241
	RES_TEXT_ONEMORE_IMG_E = 0x740000D5,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_onemore_img_e.png 104x640
	RES_TEXT_PHOTO_CONFIRM_E = 0x740000D6,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_photo_confirm_e.png 79x404
	RES_TEXT_PHOTO_IMG_E = 0x740000D7,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_photo_img_e.png 121x504
	RES_TEXT_SHARE_IMG_E = 0x740000D8,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_share_img_e.png 129x240
	RES_TEXT_SHARE_TOAST_E = 0x740000D9,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_share_toast_e.png 19x182
	RES_TEXT_TITLE_E = 0x740000DA,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_title_e.png 25x282
	RES_TEXT_UNDER_BTN_E = 0x740000DB,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_under_btn_e.png 66x372
	RES_TEXT_UNDER_E = 0x740000DC,   //D:\zyf_workspace\child_carme\zyf_test\3.0.8\fw-AC792_SDK\ui_prj\Application1\import\image\mipmap_xhdpi\rec\mipmap_xhdpi\text_under_e.png 27x312
} RES_ID;

extern char * gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

#endif
