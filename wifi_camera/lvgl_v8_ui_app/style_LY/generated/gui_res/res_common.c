#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "../gui_guider.h"
#include <stdlib.h>
#include <string.h>
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR
#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) MAX2(MAX2(a, b), c)
#define MAX4(a, b, c, d) MAX2(MAX3(a, b, c), d)
#define MAX5(a, b, c, d, e) MAX2(MAX4(a, b, c, d), e)
#define MAX6(a, b, c, d, e, f) MAX2(MAX5(a, b, c, d, e), f)
#define MAX7(a, b, c, d, e, f, g) MAX2(MAX6(a, b, c, d, e, f), g)
#define MAX8(a, b, c, d, e, f, g, h) MAX2(MAX7(a, b, c, d, e, f, g), h)

const char flash_dir[] = "mnt/sdfile/EXT_RESERVED/uipackres/ui/";
const char sd_dir[] = "storage/sd0/C/ui/";
char path_buf[MAX2(sizeof(flash_dir), sizeof(sd_dir)) + 20];
#endif

char * gui_get_res_path(int32_t id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
	switch (id) {
		case GUI_RES_FANGZHENGKAITIJIANTI_1_54_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle";
		case GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle";
		case GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle";
		case GUI_RES_SIMSUN_28_WOFF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle";
		case GUI_RES_SIMSUN_36_WOFF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle";
		case GUI_RES_SIMSUN_20_WOFF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle";
		case GUI_RES_SIMSUN_32_WOFF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle";
		case GUI_RES_ARIALMT_38_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle";
		case GUI_RES_MONTSERRATMEDIUM_24_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle";
		case GUI_RES_MONTSERRATMEDIUM_12_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle";
		case GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle";
		case GUI_RES_MONTSERRATMEDIUM_16_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle";
		case GUI_RES_MANGAL_28_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000c.rle";
		case GUI_RES_SIMPO_28_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000d.rle";
		case GUI_RES_SIMSUN_24_WOFF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000e.rle";
		case GUI_RES_LEELAWADEEUI_32_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000f.rle";
		case GUI_RES_FANGSONG_32_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000010.rle";
		case GUI_RES_SIMSUN_26_WOFF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000011.rle";
		case GUI_RES_SIMSUN_16_WOFF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000012.rle";
		case GUI_RES_SIMSUN_12_WOFF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000013.rle";
		case GUI_RES_ARIALMT_56_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000014.rle";
		case GUI_RES_SIMSUN_25_WOFF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000015.rle";
		case GUI_RES_TIMESNEWROMANPSMT_36_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000016.rle";
		case GUI_RES_TIMESNEWROMANPSMT_30_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000017.rle";
		case GUI_RES_TIMESNEWROMANPSMT_40_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000018.rle";
		case GUI_RES_TIMESNEWROMANPSMT_32_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000019.rle";
		case GUI_RES_TIMESNEWROMANPSMT_12_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001a.rle";
		case GUI_RES_TIMESNEWROMANPSMT_28_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001b.rle";
		case GUI_RES_TIMESNEWROMANPSMT_24_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001c.rle";
		case GUI_RES_TIMESNEWROMANPSMT_29_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001d.rle";
		case GUI_RES_TIMESNEWROMANPSMT_26_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001e.rle";
		case GUI_RES_MANGAL_36_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001f.rle";
		case GUI_RES_MANGAL_12_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000020.rle";
		case GUI_RES_MANGAL_40_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000021.rle";
		case GUI_RES_MANGAL_30_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000022.rle";
		case GUI_RES_MANGAL_32_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000023.rle";
		case GUI_RES_MANGAL_24_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000024.rle";
		case GUI_RES_MANGAL_29_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000025.rle";
		case GUI_RES_MANGAL_33_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000026.rle";
		case GUI_RES_MANGAL_26_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000027.rle";
		case GUI_RES_TIMESNEWROMANPSMT_33_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000028.rle";
		case GUI_RES_TIMESNEWROMANPSMT_34_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000029.rle";
		case GUI_RES_SIMPLIFIEDARABIC_36_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002a.rle";
		case GUI_RES_SIMPLIFIEDARABIC_12_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002b.rle";
		case GUI_RES_SIMPLIFIEDARABIC_40_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002c.rle";
		case GUI_RES_SIMPLIFIEDARABIC_30_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002d.rle";
		case GUI_RES_SIMPLIFIEDARABIC_32_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002e.rle";
		case GUI_RES_SIMPLIFIEDARABIC_28_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002f.rle";
		case GUI_RES_SIMPLIFIEDARABIC_24_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000030.rle";
		case GUI_RES_SIMPLIFIEDARABIC_29_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000031.rle";
		case GUI_RES_SIMPLIFIEDARABIC_33_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000032.rle";
		case GUI_RES_SIMPLIFIEDARABIC_26_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000033.rle";
		case GUI_RES_FANGSONG_16_TTF_FLASH: return "D:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000034.rle";
		case GUI_RES_EZGIF_26D3AE8D7434C37A_GIF: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\gif\\ezgif_26d3ae8d7434c37a.gif";
		case GUI_RES_EZGIF_3A421AA367158DBB_GIF: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\gif\\ezgif_3a421aa367158dbb.gif";
		case GUI_RES_EZGIF_3F026D4EC0A484F1_GIF: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\gif\\ezgif_3f026d4ec0a484f1.gif";
		case GUI_RES_IMAGE_4215637_0_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\image_4215637_0.png";
		case GUI_RES_HOME_AI_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\home_ai.png";
		case GUI_RES_HOME_SETTING_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\home_setting.png";
		case GUI_RES_HOME_ALBUM_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\home_album.png";
		case GUI_RES_HOME_COMMUNICATION_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\home_communication.png";
		case GUI_RES_HOME_PHOTOGRAPH_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\home_photograph.png";
		case GUI_RES_HOME_RECORD_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\home_record.png";
		case GUI_RES_HOME_PHOTOGRAPH_1_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\photo\\home_photograph.png";
		case GUI_RES_HOME_IMG_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\home_img.png";
		case GUI_RES_WIFI_4_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\video_page\\battery\\mipmap_xhdpi\\wifi_4.png";
		case GUI_RES_3_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\3.png";
		case GUI_RES_BG_POP_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\bg_pop.png";
		case GUI_RES_IMAGE_7991533_0_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\image_7991533_0.png";
		case GUI_RES_HOME_REMIND_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\home_remind.png";
		case GUI_RES_HOME_WLAN_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\home_wlan.png";
		case GUI_RES_BACK_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\back.png";
		case GUI_RES_VIDEO_REC_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\video_rec.png";
		case GUI_RES_IMG_0_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\img_0.png";
		case GUI_RES_IMAGE_2154541_0_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\image_2154541_0.png";
		case GUI_RES_POP_UP_WINDOW_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\video_page\\pop_up_window.png";
		case GUI_RES_FLIG_ON_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\video_page\\flig_on.png";
		case GUI_RES_ASTERN_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\video_page\\astern.png";
		case GUI_RES_PHOTOGRAPH_CLOSE_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\photograph_close.png";
		case GUI_RES_PHOTOGRAPH_LEFT_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\photograph_left.png";
		case GUI_RES_PHOTOGRAPH_NEXT_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\photograph_next.png";
		case GUI_RES_STICKER_3_72_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\sticker_3_72.png";
		case GUI_RES_STICKER_2_72_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\sticker_2_72.png";
		case GUI_RES_STICKER_1_72_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\sticker_1_72.png";
		case GUI_RES_STICKER_4_72_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\sticker_4_72.png";
		case GUI_RES_STICKER_5_72_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\sticker_5_72.png";
		case GUI_RES_STICKER_6_72_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\sticker_6_72.png";
		case GUI_RES_STICKER_8_72_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\sticker_8_72.png";
		case GUI_RES_STICKER_7_72_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\sticker_7_72.png";
		case GUI_RES_PHOTOGRAPH_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\photograph.png";
		case GUI_RES_BACK_1_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\new_landscape_mode\\back.png";
		case GUI_RES_PHOTOGRAPH_NARROW_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\photograph_narrow.png";
		case GUI_RES_PHOTOGRAPH_ENLARGE_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\photograph_enlarge.png";
		case GUI_RES_HOME_STICK_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\home_stick.png";
		case GUI_RES_PHOTO_PLAY_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\photo_play.png";
		case GUI_RES_PHOTO_PAUSE_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\photo_pause.png";
		case GUI_RES_PHOTO_BEFORE_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\photo_before.png";
		case GUI_RES_PHOTO_NEXT_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\photo_next.png";
		case GUI_RES_SET_SPEAKER_W_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\set_speaker_w.png";
		case GUI_RES_SET_SPEAKER_UN_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\set_speaker_un.png";
		case GUI_RES_PHOTO_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\PHOTO.png";
		case GUI_RES_PHOTO_ON_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\photo_on.png";
		case GUI_RES_SELECT_NO_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\select_no.png";
		case GUI_RES_HINDI_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\hindi.png";
		case GUI_RES_SELECT_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\select.png";
		case GUI_RES_ENGLISH_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\english.png";
		case GUI_RES_FRENCH_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\french.png";
		case GUI_RES_PORTUGUESE_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\portuguese.png";
		case GUI_RES_SPAIN_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\spain.png";
		case GUI_RES_RUSSIA_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\russia.png";
		case GUI_RES_ARABIC_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\arabic.png";
		case GUI_RES_CHINA_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\china.png";
		case GUI_RES_BACK_2_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\back.png";
		case GUI_RES_WLAN_REFRESH_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\wlan_refresh.png";
		case GUI_RES_IMAGE_9998327_0_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\image_9998327_0.png";
		case GUI_RES_IMAGE_8787409_0_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\image_8787409_0.png";
		case GUI_RES_SET_VIDEO_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_video.png";
		case GUI_RES_SET_RECOVER_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_recover.png";
		case GUI_RES_SET_VERSION_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_version.png";
		case GUI_RES_SET_BINDING_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_binding.png";
		case GUI_RES_SET_PICTURE_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_picture.png";
		case GUI_RES_SET_TF_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_tf.png";
		case GUI_RES_SET_SIZE_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_size.png";
		case GUI_RES_SET_SCREEN_OFF_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_screen_off.png";
		case GUI_RES_SET_WIFI_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_wifi.png";
		case GUI_RES_SET_LANGUAGE_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_language.png";
		case GUI_RES_SET_VOLUME_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_volume.png";
		case GUI_RES_SET_BRIGHTNESS_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_brightness.png";
		case GUI_RES_BG_ADVANCED_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\bg_advanced.png";
		case GUI_RES_SET_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\set.png";
		case GUI_RES_SET_BRIGHTNESS_M_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_brightness_m.png";
		case GUI_RES_SET_BRIGHTNESS_B_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_brightness_b.png";
		case GUI_RES_SET_SPEAKER_UN_1_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_speaker_un.png";
		case GUI_RES_SET_SPEAKER_W_1_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_speaker_w.png";
		case GUI_RES_SET_SCREEN_W_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_screen_w.png";
		case GUI_RES_SET_SIZE_W_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\set_size_w.png";
		case GUI_RES_HOME_CARD_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\home_card.png";
		case GUI_RES_HOME_WARNING_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\home_warning.png";
		case GUI_RES_SET_OK_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\set_ok.png";
		case GUI_RES_LOGO_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\buchong\\logo.png";
		case GUI_RES_SET_OK_1_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\set_ok.png";
		case GUI_RES_COMMUNICATION_EDIT_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\communication_edit.png";
		case GUI_RES_COMMUNICATION_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\communication.png";
		case GUI_RES_AI_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\ai.png";
		case GUI_RES_HOME_ERROR_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\home_error.png";
		case GUI_RES_SHUTDOWN_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\shutdown.png";
		case GUI_RES_IMAGE_2242091_0_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\image_2242091_0.png";
		case GUI_RES_DELETED_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\new_landscape_mode\\deleted.png";
		case GUI_RES_BG_POP_1_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\bg_pop.png";
		case GUI_RES_SURE_BTN_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\sure_btn.png";
		case GUI_RES_CANCEL_BTN_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\cancel_btn.png";
		case GUI_RES_TEXT_COPYWRITING_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\text_copywriting.png";
		case GUI_RES_TEXT_TITLE_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\text_title.png";
		case GUI_RES_HOME_ALBUM_1_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\home_album.png";
		case GUI_RES_TEXT_DELETED_IMG_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\text_deleted_img.png";
		case GUI_RES_TEXT_LOADING_IMG_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\text_loading_img.png";
		case GUI_RES_IMAGE_3532909_0_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\image_3532909_0.png";
		case GUI_RES_ALBUM_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\album.png";
		case GUI_RES_CALL_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\call.png";
		case GUI_RES_COMMUNICATION_DOWN_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\new_slices\\communication_down.png";
		case GUI_RES_COMMUNICATION_HANG_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\communication_hang.png";
		case GUI_RES_COMMUNICATION_ANSWER_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\communication_answer.png";
		case GUI_RES_COMMUNICATION_MIC_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\communication_mic.png";
		case GUI_RES_COMMUNICATION_SPEAKER_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\communication_speaker.png";
		case GUI_RES_BACK_3_PNG: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\photo\\back.png";
		case RES_0: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\0.png";
		case RES_1: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\1.png";
		case RES_2: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\2.png";
		case RES_3: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\3.png";
		case RES_CHARGING: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\charging.png";
		case RES_FULL: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\full.png";
		case RES_IMG_1: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\img_1.png";
		case RES_IMG_2: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\img_2.png";
		case RES_IMG_3: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\img_3.png";
		case RES_IMG_4: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\img_4.png";
		case RES_IMG_5: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\img_5.png";
		case RES_IMG_6: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\img_6.png";
		case RES_IMG_7: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\img_7.png";
		case RES_IMG_8: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\img_8.png";
		case RES_IMG_9: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\img_9.png";
		case RES_WIFI_1: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\wifi_1.png";
		case RES_WIFI_2: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\wifi_2.png";
		case RES_WIFI_3: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\wifi_3.png";
		case RES_WIFI_4: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\wifi_4.png";
		case RES_WIFI_NO: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\wifi_no.png";
		case RES_IMAGE_2942849_0: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\slices\\image_2942849_0.png";
		case RES_IMAGE_2942849_1: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\slices\\image_2942849_1.png";
		case RES_IMAGE_2942849_2: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\slices\\image_2942849_2.png";
		case RES_IMAGE_2942849_3: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\slices\\image_2942849_3.png";
		case RES_IMAGE_2942849_4: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\slices\\image_2942849_4.png";
		case RES_IMAGE_2942849_5: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\slices\\image_2942849_5.png";
		case RES_IMAGE_2942849_6: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\slices\\image_2942849_6.png";
		case RES_IMAGE_2942849_7: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\slices\\image_2942849_7.png";
		case RES_VIDEO: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\video.png";
		case RES_IMAGE_3532909_0: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\480slices123\\image_3532909_0.png";
		case RES_IMAGE_2242091_0: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\mipmap_xhdpi\\mipmap_xhdpi\\image_2242091_0.png";
		case RES_ALBUM_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\Album_e.png";
		case RES_CANCEL_BTN_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\cancel_btn_e.png";
		case RES_CANCEL_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\cancel_e.png";
		case RES_CHOOSE_CANCEL_BTN_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\choose_cancel_btn_e.png";
		case RES_CHOOSE_SHARE_BTN_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\choose_share_btn_e.png";
		case RES_CHOOSE_TEXT_IMG_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\choose_text_img_e.png";
		case RES_SURE_BTN_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\sure_btn_e.png";
		case RES_SURE_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\sure_e.png";
		case RES_TEXT_CHOOSE_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_choose_e.png";
		case RES_TEXT_COPYWRITING_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_copywriting_e.png";
		case RES_TEXT_DELETED_IMG_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_deleted_img_e.png";
		case RES_TEXT_DELETED_TOAST_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_deleted_toast_e.png";
		case RES_TEXT_IMAGE_RECOGNITION_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_image_recognition_e.png";
		case RES_TEXT_LOADING_IMG_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_loading_img_e.png";
		case RES_TEXT_LOADING_TOAST_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_loading_toast_e.png";
		case RES_TEXT_ONEMORE_BTN_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_onemore_btn_e.png";
		case RES_TEXT_ONEMORE_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_onemore_e.png";
		case RES_TEXT_ONEMORE_IMG_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_onemore_img_e.png";
		case RES_TEXT_PHOTO_CONFIRM_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_photo_confirm_e.png";
		case RES_TEXT_PHOTO_IMG_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_photo_img_e.png";
		case RES_TEXT_SHARE_IMG_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_share_img_e.png";
		case RES_TEXT_SHARE_TOAST_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_share_toast_e.png";
		case RES_TEXT_TITLE_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_title_e.png";
		case RES_TEXT_UNDER_BTN_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_under_btn_e.png";
		case RES_TEXT_UNDER_E: return "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\import\\image\\mipmap_xhdpi\\rec\\mipmap_xhdpi\\text_under_e.png";
		default: return NULL;
	}
#else
	memset(path_buf, 0, sizeof(path_buf));
	if (id >= 0x30000000 && id < 0x30100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "ttf");
	} else if (id >= 0x30100000 && id < 0x30200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "ttf");
	} else if (id >= 0x31000000 && id < 0x31100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "woff");
	} else if (id >= 0x31100000 && id < 0x31200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "woff");
	} else if (id >= 0x32000000 && id < 0x32100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "woff2");
	} else if (id >= 0x32100000 && id < 0x32200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "woff2");
	} else if (id >= 0x33000000 && id < 0x33100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "otf");
	} else if (id >= 0x33100000 && id < 0x33200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "otf");
	} else if (id >= 0x34000000 && id < 0x34100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
	} else if (id >= 0x34100000 && id < 0x34200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
	} else if (id >= 0x35000000 && id < 0x35100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
	} else if (id >= 0x35100000 && id < 0x35200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
	} else if (id >= 0x36000000 && id < 0x36100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "fnt");
	} else if (id >= 0x36100000 && id < 0x36200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "fnt");
	} else if (id >= 0x37000000 && id < 0x37100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "lzw");
	} else if (id >= 0x37100000 && id < 0x37200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "lzw");
	} else if (id >= 0x39000000 && id < 0x39100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "json");
	} else if (id >= 0x39100000 && id < 0x39200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "json");
	} else if (id >= 0x3A000000 && id < 0x3A100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
	} else if (id >= 0x3A100000 && id < 0x3A200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
	} else if (id >= 0x3B000000 && id < 0x3B100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
	} else if (id >= 0x3B100000 && id < 0x3B200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
	} else if (id >= 0x3D000000 && id < 0x3D100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "mp4");
	} else if (id >= 0x3D100000 && id < 0x3D200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "mp4");
	} else if (id >= 0x3E000000 && id < 0x3E100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "avi");
	} else if (id >= 0x3E100000 && id < 0x3E200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "avi");
	} else if (id >= 0x3F000000 && id < 0x3F100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
	} else if (id >= 0x3F100000 && id < 0x3F200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
	} else if (id >= 0x40000000 && id < 0x40100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
	} else if (id >= 0x40100000 && id < 0x40200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
	} else if (id >= 0x42000000 && id < 0x42100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "gif");
	} else if (id >= 0x42100000 && id < 0x42200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "gif");
	} else if (id >= 0x43000000 && id < 0x43100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
	} else if (id >= 0x43100000 && id < 0x43200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
	} else if (id >= 0x46000000 && id < 0x46100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "png");
	} else if (id >= 0x46100000 && id < 0x46200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "png");
	} else if (id >= 0x47000000 && id < 0x47100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpg");
	} else if (id >= 0x47100000 && id < 0x47200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpg");
	} else if (id >= 0x48000000 && id < 0x48100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpeg");
	} else if (id >= 0x48100000 && id < 0x48200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpeg");
	} else if (id >= 0x49000000 && id < 0x49100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bmp");
	} else if (id >= 0x49100000 && id < 0x49200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bmp");
	} else if (id >= 0x4A000000 && id < 0x4A100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "svg");
	} else if (id >= 0x4A100000 && id < 0x4A200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "svg");
	} else if (id >= 0x4B000000 && id < 0x4B100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
	} else if (id >= 0x4B100000 && id < 0x4B200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
	} else if (id >= 0x6E000000 && id < 0x6E100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "png");
	} else if (id >= 0x6E100000 && id < 0x6E200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "png");
	} else if (id >= 0x6F000000 && id < 0x6F100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpg");
	} else if (id >= 0x6F100000 && id < 0x6F200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpg");
	} else if (id >= 0x70000000 && id < 0x70100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpeg");
	} else if (id >= 0x70100000 && id < 0x70200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpeg");
	} else if (id >= 0x71000000 && id < 0x71100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bmp");
	} else if (id >= 0x71100000 && id < 0x71200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bmp");
	} else if (id >= 0x72000000 && id < 0x72100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "svg");
	} else if (id >= 0x72100000 && id < 0x72200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "svg");
	} else if (id >= 0x74000000 && id < 0x74100000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
	} else if (id >= 0x74100000 && id < 0x74200000) {
		snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
	} else {
		return NULL;
	}
	return path_buf;
#endif
}

#endif
