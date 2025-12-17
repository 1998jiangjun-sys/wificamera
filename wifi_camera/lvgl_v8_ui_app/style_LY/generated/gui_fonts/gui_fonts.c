#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_fonts.h"
#include "../common.h"

lv_font_t lv_font_FangZhengKaiTiJianTi_1_54;
lv_font_t * lv_font_FangZhengKaiTiJianTi_1_54_ptr;
void lv_font_FangZhengKaiTiJianTi_1_54_file()
{
  if (lv_font_FangZhengKaiTiJianTi_1_54_ptr != NULL) {
    lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_54_ptr);
    lv_font_FangZhengKaiTiJianTi_1_54_ptr = NULL;
    memset(&lv_font_FangZhengKaiTiJianTi_1_54, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_FangZhengKaiTiJianTi_1_54_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
  lv_font_FangZhengKaiTiJianTi_1_54_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_54_TTF_FLASH));
#endif
  if (lv_font_FangZhengKaiTiJianTi_1_54_ptr != NULL) {
    lv_font_FangZhengKaiTiJianTi_1_54 = *lv_font_FangZhengKaiTiJianTi_1_54_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_54_TTF_FLASH));
#endif
    lv_font_FangZhengKaiTiJianTi_1_54 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_16;
lv_font_t * lv_font_FangZhengKaiTiJianTi_1_16_ptr;
void lv_font_FangZhengKaiTiJianTi_1_16_file()
{
  if (lv_font_FangZhengKaiTiJianTi_1_16_ptr != NULL) {
    lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_16_ptr);
    lv_font_FangZhengKaiTiJianTi_1_16_ptr = NULL;
    memset(&lv_font_FangZhengKaiTiJianTi_1_16, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_FangZhengKaiTiJianTi_1_16_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
  lv_font_FangZhengKaiTiJianTi_1_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF_FLASH));
#endif
  if (lv_font_FangZhengKaiTiJianTi_1_16_ptr != NULL) {
    lv_font_FangZhengKaiTiJianTi_1_16 = *lv_font_FangZhengKaiTiJianTi_1_16_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF_FLASH));
#endif
    lv_font_FangZhengKaiTiJianTi_1_16 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_48;
lv_font_t * lv_font_FangZhengKaiTiJianTi_1_48_ptr;
void lv_font_FangZhengKaiTiJianTi_1_48_file()
{
  if (lv_font_FangZhengKaiTiJianTi_1_48_ptr != NULL) {
    lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_48_ptr);
    lv_font_FangZhengKaiTiJianTi_1_48_ptr = NULL;
    memset(&lv_font_FangZhengKaiTiJianTi_1_48, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_FangZhengKaiTiJianTi_1_48_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
  lv_font_FangZhengKaiTiJianTi_1_48_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF_FLASH));
#endif
  if (lv_font_FangZhengKaiTiJianTi_1_48_ptr != NULL) {
    lv_font_FangZhengKaiTiJianTi_1_48 = *lv_font_FangZhengKaiTiJianTi_1_48_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF_FLASH));
#endif
    lv_font_FangZhengKaiTiJianTi_1_48 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simsun_28;
lv_font_t * lv_font_simsun_28_ptr;
void lv_font_simsun_28_file()
{
  if (lv_font_simsun_28_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_28_ptr);
    lv_font_simsun_28_ptr = NULL;
    memset(&lv_font_simsun_28, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simsun_28_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle");
#else
  lv_font_simsun_28_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_28_WOFF_FLASH));
#endif
  if (lv_font_simsun_28_ptr != NULL) {
    lv_font_simsun_28 = *lv_font_simsun_28_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_28_WOFF_FLASH));
#endif
    lv_font_simsun_28 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simsun_36;
lv_font_t * lv_font_simsun_36_ptr;
void lv_font_simsun_36_file()
{
  if (lv_font_simsun_36_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_36_ptr);
    lv_font_simsun_36_ptr = NULL;
    memset(&lv_font_simsun_36, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simsun_36_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle");
#else
  lv_font_simsun_36_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_36_WOFF_FLASH));
#endif
  if (lv_font_simsun_36_ptr != NULL) {
    lv_font_simsun_36 = *lv_font_simsun_36_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_36_WOFF_FLASH));
#endif
    lv_font_simsun_36 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simsun_20;
lv_font_t * lv_font_simsun_20_ptr;
void lv_font_simsun_20_file()
{
  if (lv_font_simsun_20_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_20_ptr);
    lv_font_simsun_20_ptr = NULL;
    memset(&lv_font_simsun_20, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simsun_20_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle");
#else
  lv_font_simsun_20_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_20_WOFF_FLASH));
#endif
  if (lv_font_simsun_20_ptr != NULL) {
    lv_font_simsun_20 = *lv_font_simsun_20_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_20_WOFF_FLASH));
#endif
    lv_font_simsun_20 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simsun_32;
lv_font_t * lv_font_simsun_32_ptr;
void lv_font_simsun_32_file()
{
  if (lv_font_simsun_32_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_32_ptr);
    lv_font_simsun_32_ptr = NULL;
    memset(&lv_font_simsun_32, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simsun_32_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle");
#else
  lv_font_simsun_32_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_32_WOFF_FLASH));
#endif
  if (lv_font_simsun_32_ptr != NULL) {
    lv_font_simsun_32 = *lv_font_simsun_32_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_32_WOFF_FLASH));
#endif
    lv_font_simsun_32 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_arialmt_38;
lv_font_t * lv_font_arialmt_38_ptr;
void lv_font_arialmt_38_file()
{
  if (lv_font_arialmt_38_ptr != NULL) {
    lv_font_free_bin(lv_font_arialmt_38_ptr);
    lv_font_arialmt_38_ptr = NULL;
    memset(&lv_font_arialmt_38, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_arialmt_38_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle");
#else
  lv_font_arialmt_38_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_ARIALMT_38_TTF_FLASH));
#endif
  if (lv_font_arialmt_38_ptr != NULL) {
    lv_font_arialmt_38 = *lv_font_arialmt_38_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_ARIALMT_38_TTF_FLASH));
#endif
    lv_font_arialmt_38 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_montserratMedium_24;
lv_font_t * lv_font_montserratMedium_24_ptr;
void lv_font_montserratMedium_24_file()
{
  if (lv_font_montserratMedium_24_ptr != NULL) {
    lv_font_free_bin(lv_font_montserratMedium_24_ptr);
    lv_font_montserratMedium_24_ptr = NULL;
    memset(&lv_font_montserratMedium_24, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_montserratMedium_24_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle");
#else
  lv_font_montserratMedium_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_24_TTF_FLASH));
#endif
  if (lv_font_montserratMedium_24_ptr != NULL) {
    lv_font_montserratMedium_24 = *lv_font_montserratMedium_24_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_24_TTF_FLASH));
#endif
    lv_font_montserratMedium_24 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_montserratMedium_12;
lv_font_t * lv_font_montserratMedium_12_ptr;
void lv_font_montserratMedium_12_file()
{
  if (lv_font_montserratMedium_12_ptr != NULL) {
    lv_font_free_bin(lv_font_montserratMedium_12_ptr);
    lv_font_montserratMedium_12_ptr = NULL;
    memset(&lv_font_montserratMedium_12, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_montserratMedium_12_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle");
#else
  lv_font_montserratMedium_12_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_12_TTF_FLASH));
#endif
  if (lv_font_montserratMedium_12_ptr != NULL) {
    lv_font_montserratMedium_12 = *lv_font_montserratMedium_12_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_12_TTF_FLASH));
#endif
    lv_font_montserratMedium_12 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_26;
lv_font_t * lv_font_FangZhengKaiTiJianTi_1_26_ptr;
void lv_font_FangZhengKaiTiJianTi_1_26_file()
{
  if (lv_font_FangZhengKaiTiJianTi_1_26_ptr != NULL) {
    lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_26_ptr);
    lv_font_FangZhengKaiTiJianTi_1_26_ptr = NULL;
    memset(&lv_font_FangZhengKaiTiJianTi_1_26, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_FangZhengKaiTiJianTi_1_26_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle");
#else
  lv_font_FangZhengKaiTiJianTi_1_26_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF_FLASH));
#endif
  if (lv_font_FangZhengKaiTiJianTi_1_26_ptr != NULL) {
    lv_font_FangZhengKaiTiJianTi_1_26 = *lv_font_FangZhengKaiTiJianTi_1_26_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF_FLASH));
#endif
    lv_font_FangZhengKaiTiJianTi_1_26 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_montserratMedium_16;
lv_font_t * lv_font_montserratMedium_16_ptr;
void lv_font_montserratMedium_16_file()
{
  if (lv_font_montserratMedium_16_ptr != NULL) {
    lv_font_free_bin(lv_font_montserratMedium_16_ptr);
    lv_font_montserratMedium_16_ptr = NULL;
    memset(&lv_font_montserratMedium_16, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_montserratMedium_16_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle");
#else
  lv_font_montserratMedium_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_16_TTF_FLASH));
#endif
  if (lv_font_montserratMedium_16_ptr != NULL) {
    lv_font_montserratMedium_16 = *lv_font_montserratMedium_16_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_16_TTF_FLASH));
#endif
    lv_font_montserratMedium_16 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_mangal_28;
lv_font_t * lv_font_mangal_28_ptr;
void lv_font_mangal_28_file()
{
  if (lv_font_mangal_28_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_28_ptr);
    lv_font_mangal_28_ptr = NULL;
    memset(&lv_font_mangal_28, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_mangal_28_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000c.rle");
#else
  lv_font_mangal_28_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MANGAL_28_TTF_FLASH));
#endif
  if (lv_font_mangal_28_ptr != NULL) {
    lv_font_mangal_28 = *lv_font_mangal_28_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000c.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MANGAL_28_TTF_FLASH));
#endif
    lv_font_mangal_28 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simpo_28;
lv_font_t * lv_font_simpo_28_ptr;
void lv_font_simpo_28_file()
{
  if (lv_font_simpo_28_ptr != NULL) {
    lv_font_free_bin(lv_font_simpo_28_ptr);
    lv_font_simpo_28_ptr = NULL;
    memset(&lv_font_simpo_28, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simpo_28_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000d.rle");
#else
  lv_font_simpo_28_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPO_28_TTF_FLASH));
#endif
  if (lv_font_simpo_28_ptr != NULL) {
    lv_font_simpo_28 = *lv_font_simpo_28_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000d.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPO_28_TTF_FLASH));
#endif
    lv_font_simpo_28 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simsun_24;
lv_font_t * lv_font_simsun_24_ptr;
void lv_font_simsun_24_file()
{
  if (lv_font_simsun_24_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_24_ptr);
    lv_font_simsun_24_ptr = NULL;
    memset(&lv_font_simsun_24, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simsun_24_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000e.rle");
#else
  lv_font_simsun_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_24_WOFF_FLASH));
#endif
  if (lv_font_simsun_24_ptr != NULL) {
    lv_font_simsun_24 = *lv_font_simsun_24_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000e.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_24_WOFF_FLASH));
#endif
    lv_font_simsun_24 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_leelawadeeui_32;
lv_font_t * lv_font_leelawadeeui_32_ptr;
void lv_font_leelawadeeui_32_file()
{
  if (lv_font_leelawadeeui_32_ptr != NULL) {
    lv_font_free_bin(lv_font_leelawadeeui_32_ptr);
    lv_font_leelawadeeui_32_ptr = NULL;
    memset(&lv_font_leelawadeeui_32, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_leelawadeeui_32_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000f.rle");
#else
  lv_font_leelawadeeui_32_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_LEELAWADEEUI_32_TTF_FLASH));
#endif
  if (lv_font_leelawadeeui_32_ptr != NULL) {
    lv_font_leelawadeeui_32 = *lv_font_leelawadeeui_32_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500000f.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_LEELAWADEEUI_32_TTF_FLASH));
#endif
    lv_font_leelawadeeui_32 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_fangsong_32;
lv_font_t * lv_font_fangsong_32_ptr;
void lv_font_fangsong_32_file()
{
  if (lv_font_fangsong_32_ptr != NULL) {
    lv_font_free_bin(lv_font_fangsong_32_ptr);
    lv_font_fangsong_32_ptr = NULL;
    memset(&lv_font_fangsong_32, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_fangsong_32_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000010.rle");
#else
  lv_font_fangsong_32_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGSONG_32_TTF_FLASH));
#endif
  if (lv_font_fangsong_32_ptr != NULL) {
    lv_font_fangsong_32 = *lv_font_fangsong_32_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000010.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGSONG_32_TTF_FLASH));
#endif
    lv_font_fangsong_32 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simsun_26;
lv_font_t * lv_font_simsun_26_ptr;
void lv_font_simsun_26_file()
{
  if (lv_font_simsun_26_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_26_ptr);
    lv_font_simsun_26_ptr = NULL;
    memset(&lv_font_simsun_26, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simsun_26_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000011.rle");
#else
  lv_font_simsun_26_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_26_WOFF_FLASH));
#endif
  if (lv_font_simsun_26_ptr != NULL) {
    lv_font_simsun_26 = *lv_font_simsun_26_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000011.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_26_WOFF_FLASH));
#endif
    lv_font_simsun_26 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simsun_16;
lv_font_t * lv_font_simsun_16_ptr;
void lv_font_simsun_16_file()
{
  if (lv_font_simsun_16_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_16_ptr);
    lv_font_simsun_16_ptr = NULL;
    memset(&lv_font_simsun_16, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simsun_16_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000012.rle");
#else
  lv_font_simsun_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_16_WOFF_FLASH));
#endif
  if (lv_font_simsun_16_ptr != NULL) {
    lv_font_simsun_16 = *lv_font_simsun_16_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000012.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_16_WOFF_FLASH));
#endif
    lv_font_simsun_16 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simsun_12;
lv_font_t * lv_font_simsun_12_ptr;
void lv_font_simsun_12_file()
{
  if (lv_font_simsun_12_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_12_ptr);
    lv_font_simsun_12_ptr = NULL;
    memset(&lv_font_simsun_12, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simsun_12_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000013.rle");
#else
  lv_font_simsun_12_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_12_WOFF_FLASH));
#endif
  if (lv_font_simsun_12_ptr != NULL) {
    lv_font_simsun_12 = *lv_font_simsun_12_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000013.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_12_WOFF_FLASH));
#endif
    lv_font_simsun_12 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_arialmt_56;
lv_font_t * lv_font_arialmt_56_ptr;
void lv_font_arialmt_56_file()
{
  if (lv_font_arialmt_56_ptr != NULL) {
    lv_font_free_bin(lv_font_arialmt_56_ptr);
    lv_font_arialmt_56_ptr = NULL;
    memset(&lv_font_arialmt_56, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_arialmt_56_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000014.rle");
#else
  lv_font_arialmt_56_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_ARIALMT_56_TTF_FLASH));
#endif
  if (lv_font_arialmt_56_ptr != NULL) {
    lv_font_arialmt_56 = *lv_font_arialmt_56_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000014.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_ARIALMT_56_TTF_FLASH));
#endif
    lv_font_arialmt_56 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simsun_25;
lv_font_t * lv_font_simsun_25_ptr;
void lv_font_simsun_25_file()
{
  if (lv_font_simsun_25_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_25_ptr);
    lv_font_simsun_25_ptr = NULL;
    memset(&lv_font_simsun_25, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simsun_25_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000015.rle");
#else
  lv_font_simsun_25_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_25_WOFF_FLASH));
#endif
  if (lv_font_simsun_25_ptr != NULL) {
    lv_font_simsun_25 = *lv_font_simsun_25_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000015.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_25_WOFF_FLASH));
#endif
    lv_font_simsun_25 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_36;
lv_font_t * lv_font_timesnewromanpsmt_36_ptr;
void lv_font_timesnewromanpsmt_36_file()
{
  if (lv_font_timesnewromanpsmt_36_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_36_ptr);
    lv_font_timesnewromanpsmt_36_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_36, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_36_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000016.rle");
#else
  lv_font_timesnewromanpsmt_36_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_36_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_36_ptr != NULL) {
    lv_font_timesnewromanpsmt_36 = *lv_font_timesnewromanpsmt_36_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000016.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_36_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_36 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_30;
lv_font_t * lv_font_timesnewromanpsmt_30_ptr;
void lv_font_timesnewromanpsmt_30_file()
{
  if (lv_font_timesnewromanpsmt_30_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_30_ptr);
    lv_font_timesnewromanpsmt_30_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_30, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_30_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000017.rle");
#else
  lv_font_timesnewromanpsmt_30_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_30_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_30_ptr != NULL) {
    lv_font_timesnewromanpsmt_30 = *lv_font_timesnewromanpsmt_30_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000017.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_30_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_30 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_40;
lv_font_t * lv_font_timesnewromanpsmt_40_ptr;
void lv_font_timesnewromanpsmt_40_file()
{
  if (lv_font_timesnewromanpsmt_40_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_40_ptr);
    lv_font_timesnewromanpsmt_40_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_40, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_40_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000018.rle");
#else
  lv_font_timesnewromanpsmt_40_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_40_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_40_ptr != NULL) {
    lv_font_timesnewromanpsmt_40 = *lv_font_timesnewromanpsmt_40_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000018.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_40_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_40 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_32;
lv_font_t * lv_font_timesnewromanpsmt_32_ptr;
void lv_font_timesnewromanpsmt_32_file()
{
  if (lv_font_timesnewromanpsmt_32_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_32_ptr);
    lv_font_timesnewromanpsmt_32_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_32, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_32_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000019.rle");
#else
  lv_font_timesnewromanpsmt_32_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_32_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_32_ptr != NULL) {
    lv_font_timesnewromanpsmt_32 = *lv_font_timesnewromanpsmt_32_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000019.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_32_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_32 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_12;
lv_font_t * lv_font_timesnewromanpsmt_12_ptr;
void lv_font_timesnewromanpsmt_12_file()
{
  if (lv_font_timesnewromanpsmt_12_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_12_ptr);
    lv_font_timesnewromanpsmt_12_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_12, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_12_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001a.rle");
#else
  lv_font_timesnewromanpsmt_12_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_12_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_12_ptr != NULL) {
    lv_font_timesnewromanpsmt_12 = *lv_font_timesnewromanpsmt_12_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001a.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_12_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_12 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_28;
lv_font_t * lv_font_timesnewromanpsmt_28_ptr;
void lv_font_timesnewromanpsmt_28_file()
{
  if (lv_font_timesnewromanpsmt_28_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_28_ptr);
    lv_font_timesnewromanpsmt_28_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_28, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_28_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001b.rle");
#else
  lv_font_timesnewromanpsmt_28_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_28_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_28_ptr != NULL) {
    lv_font_timesnewromanpsmt_28 = *lv_font_timesnewromanpsmt_28_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001b.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_28_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_28 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_24;
lv_font_t * lv_font_timesnewromanpsmt_24_ptr;
void lv_font_timesnewromanpsmt_24_file()
{
  if (lv_font_timesnewromanpsmt_24_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_24_ptr);
    lv_font_timesnewromanpsmt_24_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_24, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_24_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001c.rle");
#else
  lv_font_timesnewromanpsmt_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_24_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_24_ptr != NULL) {
    lv_font_timesnewromanpsmt_24 = *lv_font_timesnewromanpsmt_24_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001c.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_24_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_24 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_29;
lv_font_t * lv_font_timesnewromanpsmt_29_ptr;
void lv_font_timesnewromanpsmt_29_file()
{
  if (lv_font_timesnewromanpsmt_29_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_29_ptr);
    lv_font_timesnewromanpsmt_29_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_29, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_29_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001d.rle");
#else
  lv_font_timesnewromanpsmt_29_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_29_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_29_ptr != NULL) {
    lv_font_timesnewromanpsmt_29 = *lv_font_timesnewromanpsmt_29_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001d.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_29_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_29 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_26;
lv_font_t * lv_font_timesnewromanpsmt_26_ptr;
void lv_font_timesnewromanpsmt_26_file()
{
  if (lv_font_timesnewromanpsmt_26_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_26_ptr);
    lv_font_timesnewromanpsmt_26_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_26, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_26_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001e.rle");
#else
  lv_font_timesnewromanpsmt_26_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_26_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_26_ptr != NULL) {
    lv_font_timesnewromanpsmt_26 = *lv_font_timesnewromanpsmt_26_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001e.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_26_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_26 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_mangal_36;
lv_font_t * lv_font_mangal_36_ptr;
void lv_font_mangal_36_file()
{
  if (lv_font_mangal_36_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_36_ptr);
    lv_font_mangal_36_ptr = NULL;
    memset(&lv_font_mangal_36, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_mangal_36_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001f.rle");
#else
  lv_font_mangal_36_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MANGAL_36_TTF_FLASH));
#endif
  if (lv_font_mangal_36_ptr != NULL) {
    lv_font_mangal_36 = *lv_font_mangal_36_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500001f.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MANGAL_36_TTF_FLASH));
#endif
    lv_font_mangal_36 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_mangal_12;
lv_font_t * lv_font_mangal_12_ptr;
void lv_font_mangal_12_file()
{
  if (lv_font_mangal_12_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_12_ptr);
    lv_font_mangal_12_ptr = NULL;
    memset(&lv_font_mangal_12, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_mangal_12_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000020.rle");
#else
  lv_font_mangal_12_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MANGAL_12_TTF_FLASH));
#endif
  if (lv_font_mangal_12_ptr != NULL) {
    lv_font_mangal_12 = *lv_font_mangal_12_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000020.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MANGAL_12_TTF_FLASH));
#endif
    lv_font_mangal_12 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_mangal_40;
lv_font_t * lv_font_mangal_40_ptr;
void lv_font_mangal_40_file()
{
  if (lv_font_mangal_40_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_40_ptr);
    lv_font_mangal_40_ptr = NULL;
    memset(&lv_font_mangal_40, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_mangal_40_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000021.rle");
#else
  lv_font_mangal_40_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MANGAL_40_TTF_FLASH));
#endif
  if (lv_font_mangal_40_ptr != NULL) {
    lv_font_mangal_40 = *lv_font_mangal_40_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000021.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MANGAL_40_TTF_FLASH));
#endif
    lv_font_mangal_40 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_mangal_30;
lv_font_t * lv_font_mangal_30_ptr;
void lv_font_mangal_30_file()
{
  if (lv_font_mangal_30_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_30_ptr);
    lv_font_mangal_30_ptr = NULL;
    memset(&lv_font_mangal_30, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_mangal_30_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000022.rle");
#else
  lv_font_mangal_30_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MANGAL_30_TTF_FLASH));
#endif
  if (lv_font_mangal_30_ptr != NULL) {
    lv_font_mangal_30 = *lv_font_mangal_30_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000022.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MANGAL_30_TTF_FLASH));
#endif
    lv_font_mangal_30 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_mangal_32;
lv_font_t * lv_font_mangal_32_ptr;
void lv_font_mangal_32_file()
{
  if (lv_font_mangal_32_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_32_ptr);
    lv_font_mangal_32_ptr = NULL;
    memset(&lv_font_mangal_32, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_mangal_32_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000023.rle");
#else
  lv_font_mangal_32_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MANGAL_32_TTF_FLASH));
#endif
  if (lv_font_mangal_32_ptr != NULL) {
    lv_font_mangal_32 = *lv_font_mangal_32_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000023.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MANGAL_32_TTF_FLASH));
#endif
    lv_font_mangal_32 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_mangal_24;
lv_font_t * lv_font_mangal_24_ptr;
void lv_font_mangal_24_file()
{
  if (lv_font_mangal_24_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_24_ptr);
    lv_font_mangal_24_ptr = NULL;
    memset(&lv_font_mangal_24, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_mangal_24_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000024.rle");
#else
  lv_font_mangal_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MANGAL_24_TTF_FLASH));
#endif
  if (lv_font_mangal_24_ptr != NULL) {
    lv_font_mangal_24 = *lv_font_mangal_24_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000024.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MANGAL_24_TTF_FLASH));
#endif
    lv_font_mangal_24 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_mangal_29;
lv_font_t * lv_font_mangal_29_ptr;
void lv_font_mangal_29_file()
{
  if (lv_font_mangal_29_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_29_ptr);
    lv_font_mangal_29_ptr = NULL;
    memset(&lv_font_mangal_29, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_mangal_29_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000025.rle");
#else
  lv_font_mangal_29_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MANGAL_29_TTF_FLASH));
#endif
  if (lv_font_mangal_29_ptr != NULL) {
    lv_font_mangal_29 = *lv_font_mangal_29_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000025.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MANGAL_29_TTF_FLASH));
#endif
    lv_font_mangal_29 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_mangal_33;
lv_font_t * lv_font_mangal_33_ptr;
void lv_font_mangal_33_file()
{
  if (lv_font_mangal_33_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_33_ptr);
    lv_font_mangal_33_ptr = NULL;
    memset(&lv_font_mangal_33, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_mangal_33_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000026.rle");
#else
  lv_font_mangal_33_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MANGAL_33_TTF_FLASH));
#endif
  if (lv_font_mangal_33_ptr != NULL) {
    lv_font_mangal_33 = *lv_font_mangal_33_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000026.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MANGAL_33_TTF_FLASH));
#endif
    lv_font_mangal_33 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_mangal_26;
lv_font_t * lv_font_mangal_26_ptr;
void lv_font_mangal_26_file()
{
  if (lv_font_mangal_26_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_26_ptr);
    lv_font_mangal_26_ptr = NULL;
    memset(&lv_font_mangal_26, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_mangal_26_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000027.rle");
#else
  lv_font_mangal_26_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_MANGAL_26_TTF_FLASH));
#endif
  if (lv_font_mangal_26_ptr != NULL) {
    lv_font_mangal_26 = *lv_font_mangal_26_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000027.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MANGAL_26_TTF_FLASH));
#endif
    lv_font_mangal_26 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_33;
lv_font_t * lv_font_timesnewromanpsmt_33_ptr;
void lv_font_timesnewromanpsmt_33_file()
{
  if (lv_font_timesnewromanpsmt_33_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_33_ptr);
    lv_font_timesnewromanpsmt_33_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_33, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_33_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000028.rle");
#else
  lv_font_timesnewromanpsmt_33_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_33_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_33_ptr != NULL) {
    lv_font_timesnewromanpsmt_33 = *lv_font_timesnewromanpsmt_33_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000028.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_33_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_33 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_timesnewromanpsmt_34;
lv_font_t * lv_font_timesnewromanpsmt_34_ptr;
void lv_font_timesnewromanpsmt_34_file()
{
  if (lv_font_timesnewromanpsmt_34_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_34_ptr);
    lv_font_timesnewromanpsmt_34_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_34, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_timesnewromanpsmt_34_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000029.rle");
#else
  lv_font_timesnewromanpsmt_34_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_34_TTF_FLASH));
#endif
  if (lv_font_timesnewromanpsmt_34_ptr != NULL) {
    lv_font_timesnewromanpsmt_34 = *lv_font_timesnewromanpsmt_34_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000029.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_34_TTF_FLASH));
#endif
    lv_font_timesnewromanpsmt_34 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simplifiedarabic_36;
lv_font_t * lv_font_simplifiedarabic_36_ptr;
void lv_font_simplifiedarabic_36_file()
{
  if (lv_font_simplifiedarabic_36_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_36_ptr);
    lv_font_simplifiedarabic_36_ptr = NULL;
    memset(&lv_font_simplifiedarabic_36, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simplifiedarabic_36_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002a.rle");
#else
  lv_font_simplifiedarabic_36_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_36_TTF_FLASH));
#endif
  if (lv_font_simplifiedarabic_36_ptr != NULL) {
    lv_font_simplifiedarabic_36 = *lv_font_simplifiedarabic_36_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002a.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_36_TTF_FLASH));
#endif
    lv_font_simplifiedarabic_36 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simplifiedarabic_12;
lv_font_t * lv_font_simplifiedarabic_12_ptr;
void lv_font_simplifiedarabic_12_file()
{
  if (lv_font_simplifiedarabic_12_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_12_ptr);
    lv_font_simplifiedarabic_12_ptr = NULL;
    memset(&lv_font_simplifiedarabic_12, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simplifiedarabic_12_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002b.rle");
#else
  lv_font_simplifiedarabic_12_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_12_TTF_FLASH));
#endif
  if (lv_font_simplifiedarabic_12_ptr != NULL) {
    lv_font_simplifiedarabic_12 = *lv_font_simplifiedarabic_12_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002b.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_12_TTF_FLASH));
#endif
    lv_font_simplifiedarabic_12 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simplifiedarabic_40;
lv_font_t * lv_font_simplifiedarabic_40_ptr;
void lv_font_simplifiedarabic_40_file()
{
  if (lv_font_simplifiedarabic_40_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_40_ptr);
    lv_font_simplifiedarabic_40_ptr = NULL;
    memset(&lv_font_simplifiedarabic_40, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simplifiedarabic_40_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002c.rle");
#else
  lv_font_simplifiedarabic_40_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_40_TTF_FLASH));
#endif
  if (lv_font_simplifiedarabic_40_ptr != NULL) {
    lv_font_simplifiedarabic_40 = *lv_font_simplifiedarabic_40_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002c.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_40_TTF_FLASH));
#endif
    lv_font_simplifiedarabic_40 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simplifiedarabic_30;
lv_font_t * lv_font_simplifiedarabic_30_ptr;
void lv_font_simplifiedarabic_30_file()
{
  if (lv_font_simplifiedarabic_30_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_30_ptr);
    lv_font_simplifiedarabic_30_ptr = NULL;
    memset(&lv_font_simplifiedarabic_30, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simplifiedarabic_30_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002d.rle");
#else
  lv_font_simplifiedarabic_30_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_30_TTF_FLASH));
#endif
  if (lv_font_simplifiedarabic_30_ptr != NULL) {
    lv_font_simplifiedarabic_30 = *lv_font_simplifiedarabic_30_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002d.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_30_TTF_FLASH));
#endif
    lv_font_simplifiedarabic_30 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simplifiedarabic_32;
lv_font_t * lv_font_simplifiedarabic_32_ptr;
void lv_font_simplifiedarabic_32_file()
{
  if (lv_font_simplifiedarabic_32_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_32_ptr);
    lv_font_simplifiedarabic_32_ptr = NULL;
    memset(&lv_font_simplifiedarabic_32, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simplifiedarabic_32_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002e.rle");
#else
  lv_font_simplifiedarabic_32_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_32_TTF_FLASH));
#endif
  if (lv_font_simplifiedarabic_32_ptr != NULL) {
    lv_font_simplifiedarabic_32 = *lv_font_simplifiedarabic_32_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002e.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_32_TTF_FLASH));
#endif
    lv_font_simplifiedarabic_32 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simplifiedarabic_28;
lv_font_t * lv_font_simplifiedarabic_28_ptr;
void lv_font_simplifiedarabic_28_file()
{
  if (lv_font_simplifiedarabic_28_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_28_ptr);
    lv_font_simplifiedarabic_28_ptr = NULL;
    memset(&lv_font_simplifiedarabic_28, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simplifiedarabic_28_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002f.rle");
#else
  lv_font_simplifiedarabic_28_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_28_TTF_FLASH));
#endif
  if (lv_font_simplifiedarabic_28_ptr != NULL) {
    lv_font_simplifiedarabic_28 = *lv_font_simplifiedarabic_28_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\3500002f.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_28_TTF_FLASH));
#endif
    lv_font_simplifiedarabic_28 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simplifiedarabic_24;
lv_font_t * lv_font_simplifiedarabic_24_ptr;
void lv_font_simplifiedarabic_24_file()
{
  if (lv_font_simplifiedarabic_24_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_24_ptr);
    lv_font_simplifiedarabic_24_ptr = NULL;
    memset(&lv_font_simplifiedarabic_24, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simplifiedarabic_24_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000030.rle");
#else
  lv_font_simplifiedarabic_24_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_24_TTF_FLASH));
#endif
  if (lv_font_simplifiedarabic_24_ptr != NULL) {
    lv_font_simplifiedarabic_24 = *lv_font_simplifiedarabic_24_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000030.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_24_TTF_FLASH));
#endif
    lv_font_simplifiedarabic_24 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simplifiedarabic_29;
lv_font_t * lv_font_simplifiedarabic_29_ptr;
void lv_font_simplifiedarabic_29_file()
{
  if (lv_font_simplifiedarabic_29_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_29_ptr);
    lv_font_simplifiedarabic_29_ptr = NULL;
    memset(&lv_font_simplifiedarabic_29, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simplifiedarabic_29_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000031.rle");
#else
  lv_font_simplifiedarabic_29_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_29_TTF_FLASH));
#endif
  if (lv_font_simplifiedarabic_29_ptr != NULL) {
    lv_font_simplifiedarabic_29 = *lv_font_simplifiedarabic_29_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000031.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_29_TTF_FLASH));
#endif
    lv_font_simplifiedarabic_29 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simplifiedarabic_33;
lv_font_t * lv_font_simplifiedarabic_33_ptr;
void lv_font_simplifiedarabic_33_file()
{
  if (lv_font_simplifiedarabic_33_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_33_ptr);
    lv_font_simplifiedarabic_33_ptr = NULL;
    memset(&lv_font_simplifiedarabic_33, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simplifiedarabic_33_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000032.rle");
#else
  lv_font_simplifiedarabic_33_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_33_TTF_FLASH));
#endif
  if (lv_font_simplifiedarabic_33_ptr != NULL) {
    lv_font_simplifiedarabic_33 = *lv_font_simplifiedarabic_33_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000032.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_33_TTF_FLASH));
#endif
    lv_font_simplifiedarabic_33 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_simplifiedarabic_26;
lv_font_t * lv_font_simplifiedarabic_26_ptr;
void lv_font_simplifiedarabic_26_file()
{
  if (lv_font_simplifiedarabic_26_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_26_ptr);
    lv_font_simplifiedarabic_26_ptr = NULL;
    memset(&lv_font_simplifiedarabic_26, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_simplifiedarabic_26_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000033.rle");
#else
  lv_font_simplifiedarabic_26_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_26_TTF_FLASH));
#endif
  if (lv_font_simplifiedarabic_26_ptr != NULL) {
    lv_font_simplifiedarabic_26 = *lv_font_simplifiedarabic_26_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000033.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMPLIFIEDARABIC_26_TTF_FLASH));
#endif
    lv_font_simplifiedarabic_26 = *LV_FONT_DEFAULT;
  }
}
lv_font_t lv_font_fangsong_16;
lv_font_t * lv_font_fangsong_16_ptr;
void lv_font_fangsong_16_file()
{
  if (lv_font_fangsong_16_ptr != NULL) {
    lv_font_free_bin(lv_font_fangsong_16_ptr);
    lv_font_fangsong_16_ptr = NULL;
    memset(&lv_font_fangsong_16, 0, sizeof(lv_font_t));
  }
#if LV_USE_GUIBUILDER_SIMULATOR
  lv_font_fangsong_16_ptr = lv_font_load_bin("A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000034.rle");
#else
  lv_font_fangsong_16_ptr = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGSONG_16_TTF_FLASH));
#endif
  if (lv_font_fangsong_16_ptr != NULL) {
    lv_font_fangsong_16 = *lv_font_fangsong_16_ptr;
  } else {
#if LV_USE_GUIBUILDER_SIMULATOR
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\zyf_workspace\\child_carme\\zyf_test\\3.0.8\\fw-AC792_SDK\\ui_prj\\Application1\\sdk\\ui_res\\flash\\rle\\font\\35000034.rle");
#else
    LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGSONG_16_TTF_FLASH));
#endif
    lv_font_fangsong_16 = *LV_FONT_DEFAULT;
  }
}

void init_gui_fonts()
{
  lv_font_FangZhengKaiTiJianTi_1_54_file();
  lv_font_FangZhengKaiTiJianTi_1_16_file();
  lv_font_FangZhengKaiTiJianTi_1_48_file();
  lv_font_simsun_28_file();
  lv_font_simsun_36_file();
  lv_font_simsun_20_file();
  lv_font_simsun_32_file();
  lv_font_arialmt_38_file();
  lv_font_montserratMedium_24_file();
  lv_font_montserratMedium_12_file();
  lv_font_FangZhengKaiTiJianTi_1_26_file();
  lv_font_montserratMedium_16_file();
  lv_font_mangal_28_file();
  lv_font_simpo_28_file();
  lv_font_simsun_24_file();
  lv_font_leelawadeeui_32_file();
  lv_font_fangsong_32_file();
  lv_font_simsun_26_file();
  lv_font_simsun_16_file();
  lv_font_simsun_12_file();
  lv_font_arialmt_56_file();
  lv_font_simsun_25_file();
  lv_font_timesnewromanpsmt_36_file();
  lv_font_timesnewromanpsmt_30_file();
  lv_font_timesnewromanpsmt_40_file();
  lv_font_timesnewromanpsmt_32_file();
  lv_font_timesnewromanpsmt_12_file();
  lv_font_timesnewromanpsmt_28_file();
  lv_font_timesnewromanpsmt_24_file();
  lv_font_timesnewromanpsmt_29_file();
  lv_font_timesnewromanpsmt_26_file();
  lv_font_mangal_36_file();
  lv_font_mangal_12_file();
  lv_font_mangal_40_file();
  lv_font_mangal_30_file();
  lv_font_mangal_32_file();
  lv_font_mangal_24_file();
  lv_font_mangal_29_file();
  lv_font_mangal_33_file();
  lv_font_mangal_26_file();
  lv_font_timesnewromanpsmt_33_file();
  lv_font_timesnewromanpsmt_34_file();
  lv_font_simplifiedarabic_36_file();
  lv_font_simplifiedarabic_12_file();
  lv_font_simplifiedarabic_40_file();
  lv_font_simplifiedarabic_30_file();
  lv_font_simplifiedarabic_32_file();
  lv_font_simplifiedarabic_28_file();
  lv_font_simplifiedarabic_24_file();
  lv_font_simplifiedarabic_29_file();
  lv_font_simplifiedarabic_33_file();
  lv_font_simplifiedarabic_26_file();
  lv_font_fangsong_16_file();


}

void free_gui_fonts()
{
  if (lv_font_FangZhengKaiTiJianTi_1_54_ptr != NULL) {
    lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_54_ptr);
    lv_font_FangZhengKaiTiJianTi_1_54_ptr = NULL;
    memset(&lv_font_FangZhengKaiTiJianTi_1_54, 0, sizeof(lv_font_t));
  }
  if (lv_font_FangZhengKaiTiJianTi_1_16_ptr != NULL) {
    lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_16_ptr);
    lv_font_FangZhengKaiTiJianTi_1_16_ptr = NULL;
    memset(&lv_font_FangZhengKaiTiJianTi_1_16, 0, sizeof(lv_font_t));
  }
  if (lv_font_FangZhengKaiTiJianTi_1_48_ptr != NULL) {
    lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_48_ptr);
    lv_font_FangZhengKaiTiJianTi_1_48_ptr = NULL;
    memset(&lv_font_FangZhengKaiTiJianTi_1_48, 0, sizeof(lv_font_t));
  }
  if (lv_font_simsun_28_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_28_ptr);
    lv_font_simsun_28_ptr = NULL;
    memset(&lv_font_simsun_28, 0, sizeof(lv_font_t));
  }
  if (lv_font_simsun_36_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_36_ptr);
    lv_font_simsun_36_ptr = NULL;
    memset(&lv_font_simsun_36, 0, sizeof(lv_font_t));
  }
  if (lv_font_simsun_20_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_20_ptr);
    lv_font_simsun_20_ptr = NULL;
    memset(&lv_font_simsun_20, 0, sizeof(lv_font_t));
  }
  if (lv_font_simsun_32_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_32_ptr);
    lv_font_simsun_32_ptr = NULL;
    memset(&lv_font_simsun_32, 0, sizeof(lv_font_t));
  }
  if (lv_font_arialmt_38_ptr != NULL) {
    lv_font_free_bin(lv_font_arialmt_38_ptr);
    lv_font_arialmt_38_ptr = NULL;
    memset(&lv_font_arialmt_38, 0, sizeof(lv_font_t));
  }
  if (lv_font_montserratMedium_24_ptr != NULL) {
    lv_font_free_bin(lv_font_montserratMedium_24_ptr);
    lv_font_montserratMedium_24_ptr = NULL;
    memset(&lv_font_montserratMedium_24, 0, sizeof(lv_font_t));
  }
  if (lv_font_montserratMedium_12_ptr != NULL) {
    lv_font_free_bin(lv_font_montserratMedium_12_ptr);
    lv_font_montserratMedium_12_ptr = NULL;
    memset(&lv_font_montserratMedium_12, 0, sizeof(lv_font_t));
  }
  if (lv_font_FangZhengKaiTiJianTi_1_26_ptr != NULL) {
    lv_font_free_bin(lv_font_FangZhengKaiTiJianTi_1_26_ptr);
    lv_font_FangZhengKaiTiJianTi_1_26_ptr = NULL;
    memset(&lv_font_FangZhengKaiTiJianTi_1_26, 0, sizeof(lv_font_t));
  }
  if (lv_font_montserratMedium_16_ptr != NULL) {
    lv_font_free_bin(lv_font_montserratMedium_16_ptr);
    lv_font_montserratMedium_16_ptr = NULL;
    memset(&lv_font_montserratMedium_16, 0, sizeof(lv_font_t));
  }
  if (lv_font_mangal_28_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_28_ptr);
    lv_font_mangal_28_ptr = NULL;
    memset(&lv_font_mangal_28, 0, sizeof(lv_font_t));
  }
  if (lv_font_simpo_28_ptr != NULL) {
    lv_font_free_bin(lv_font_simpo_28_ptr);
    lv_font_simpo_28_ptr = NULL;
    memset(&lv_font_simpo_28, 0, sizeof(lv_font_t));
  }
  if (lv_font_simsun_24_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_24_ptr);
    lv_font_simsun_24_ptr = NULL;
    memset(&lv_font_simsun_24, 0, sizeof(lv_font_t));
  }
  if (lv_font_leelawadeeui_32_ptr != NULL) {
    lv_font_free_bin(lv_font_leelawadeeui_32_ptr);
    lv_font_leelawadeeui_32_ptr = NULL;
    memset(&lv_font_leelawadeeui_32, 0, sizeof(lv_font_t));
  }
  if (lv_font_fangsong_32_ptr != NULL) {
    lv_font_free_bin(lv_font_fangsong_32_ptr);
    lv_font_fangsong_32_ptr = NULL;
    memset(&lv_font_fangsong_32, 0, sizeof(lv_font_t));
  }
  if (lv_font_simsun_26_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_26_ptr);
    lv_font_simsun_26_ptr = NULL;
    memset(&lv_font_simsun_26, 0, sizeof(lv_font_t));
  }
  if (lv_font_simsun_16_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_16_ptr);
    lv_font_simsun_16_ptr = NULL;
    memset(&lv_font_simsun_16, 0, sizeof(lv_font_t));
  }
  if (lv_font_simsun_12_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_12_ptr);
    lv_font_simsun_12_ptr = NULL;
    memset(&lv_font_simsun_12, 0, sizeof(lv_font_t));
  }
  if (lv_font_arialmt_56_ptr != NULL) {
    lv_font_free_bin(lv_font_arialmt_56_ptr);
    lv_font_arialmt_56_ptr = NULL;
    memset(&lv_font_arialmt_56, 0, sizeof(lv_font_t));
  }
  if (lv_font_simsun_25_ptr != NULL) {
    lv_font_free_bin(lv_font_simsun_25_ptr);
    lv_font_simsun_25_ptr = NULL;
    memset(&lv_font_simsun_25, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_36_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_36_ptr);
    lv_font_timesnewromanpsmt_36_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_36, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_30_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_30_ptr);
    lv_font_timesnewromanpsmt_30_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_30, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_40_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_40_ptr);
    lv_font_timesnewromanpsmt_40_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_40, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_32_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_32_ptr);
    lv_font_timesnewromanpsmt_32_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_32, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_12_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_12_ptr);
    lv_font_timesnewromanpsmt_12_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_12, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_28_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_28_ptr);
    lv_font_timesnewromanpsmt_28_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_28, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_24_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_24_ptr);
    lv_font_timesnewromanpsmt_24_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_24, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_29_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_29_ptr);
    lv_font_timesnewromanpsmt_29_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_29, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_26_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_26_ptr);
    lv_font_timesnewromanpsmt_26_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_26, 0, sizeof(lv_font_t));
  }
  if (lv_font_mangal_36_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_36_ptr);
    lv_font_mangal_36_ptr = NULL;
    memset(&lv_font_mangal_36, 0, sizeof(lv_font_t));
  }
  if (lv_font_mangal_12_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_12_ptr);
    lv_font_mangal_12_ptr = NULL;
    memset(&lv_font_mangal_12, 0, sizeof(lv_font_t));
  }
  if (lv_font_mangal_40_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_40_ptr);
    lv_font_mangal_40_ptr = NULL;
    memset(&lv_font_mangal_40, 0, sizeof(lv_font_t));
  }
  if (lv_font_mangal_30_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_30_ptr);
    lv_font_mangal_30_ptr = NULL;
    memset(&lv_font_mangal_30, 0, sizeof(lv_font_t));
  }
  if (lv_font_mangal_32_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_32_ptr);
    lv_font_mangal_32_ptr = NULL;
    memset(&lv_font_mangal_32, 0, sizeof(lv_font_t));
  }
  if (lv_font_mangal_24_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_24_ptr);
    lv_font_mangal_24_ptr = NULL;
    memset(&lv_font_mangal_24, 0, sizeof(lv_font_t));
  }
  if (lv_font_mangal_29_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_29_ptr);
    lv_font_mangal_29_ptr = NULL;
    memset(&lv_font_mangal_29, 0, sizeof(lv_font_t));
  }
  if (lv_font_mangal_33_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_33_ptr);
    lv_font_mangal_33_ptr = NULL;
    memset(&lv_font_mangal_33, 0, sizeof(lv_font_t));
  }
  if (lv_font_mangal_26_ptr != NULL) {
    lv_font_free_bin(lv_font_mangal_26_ptr);
    lv_font_mangal_26_ptr = NULL;
    memset(&lv_font_mangal_26, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_33_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_33_ptr);
    lv_font_timesnewromanpsmt_33_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_33, 0, sizeof(lv_font_t));
  }
  if (lv_font_timesnewromanpsmt_34_ptr != NULL) {
    lv_font_free_bin(lv_font_timesnewromanpsmt_34_ptr);
    lv_font_timesnewromanpsmt_34_ptr = NULL;
    memset(&lv_font_timesnewromanpsmt_34, 0, sizeof(lv_font_t));
  }
  if (lv_font_simplifiedarabic_36_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_36_ptr);
    lv_font_simplifiedarabic_36_ptr = NULL;
    memset(&lv_font_simplifiedarabic_36, 0, sizeof(lv_font_t));
  }
  if (lv_font_simplifiedarabic_12_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_12_ptr);
    lv_font_simplifiedarabic_12_ptr = NULL;
    memset(&lv_font_simplifiedarabic_12, 0, sizeof(lv_font_t));
  }
  if (lv_font_simplifiedarabic_40_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_40_ptr);
    lv_font_simplifiedarabic_40_ptr = NULL;
    memset(&lv_font_simplifiedarabic_40, 0, sizeof(lv_font_t));
  }
  if (lv_font_simplifiedarabic_30_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_30_ptr);
    lv_font_simplifiedarabic_30_ptr = NULL;
    memset(&lv_font_simplifiedarabic_30, 0, sizeof(lv_font_t));
  }
  if (lv_font_simplifiedarabic_32_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_32_ptr);
    lv_font_simplifiedarabic_32_ptr = NULL;
    memset(&lv_font_simplifiedarabic_32, 0, sizeof(lv_font_t));
  }
  if (lv_font_simplifiedarabic_28_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_28_ptr);
    lv_font_simplifiedarabic_28_ptr = NULL;
    memset(&lv_font_simplifiedarabic_28, 0, sizeof(lv_font_t));
  }
  if (lv_font_simplifiedarabic_24_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_24_ptr);
    lv_font_simplifiedarabic_24_ptr = NULL;
    memset(&lv_font_simplifiedarabic_24, 0, sizeof(lv_font_t));
  }
  if (lv_font_simplifiedarabic_29_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_29_ptr);
    lv_font_simplifiedarabic_29_ptr = NULL;
    memset(&lv_font_simplifiedarabic_29, 0, sizeof(lv_font_t));
  }
  if (lv_font_simplifiedarabic_33_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_33_ptr);
    lv_font_simplifiedarabic_33_ptr = NULL;
    memset(&lv_font_simplifiedarabic_33, 0, sizeof(lv_font_t));
  }
  if (lv_font_simplifiedarabic_26_ptr != NULL) {
    lv_font_free_bin(lv_font_simplifiedarabic_26_ptr);
    lv_font_simplifiedarabic_26_ptr = NULL;
    memset(&lv_font_simplifiedarabic_26, 0, sizeof(lv_font_t));
  }
  if (lv_font_fangsong_16_ptr != NULL) {
    lv_font_free_bin(lv_font_fangsong_16_ptr);
    lv_font_fangsong_16_ptr = NULL;
    memset(&lv_font_fangsong_16, 0, sizeof(lv_font_t));
  }
}


#endif
