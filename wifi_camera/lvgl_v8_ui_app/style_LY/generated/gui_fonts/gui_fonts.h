#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
#ifndef GUIDER_FONTS_H
#define GUIDER_FONTS_H
#ifdef __cplusplus
extern "C" {
#endif

#if LVGL_VERSION_MAJOR == 7
#include "lv_font/lv_font.h"
#else
#include "src/font/lv_font.h"
#endif

extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_54;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_16;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_48;
extern lv_font_t lv_font_simsun_28;
extern lv_font_t lv_font_simsun_36;
extern lv_font_t lv_font_simsun_20;
extern lv_font_t lv_font_simsun_32;
extern lv_font_t lv_font_arialmt_38;
extern lv_font_t lv_font_montserratMedium_24;
extern lv_font_t lv_font_montserratMedium_12;
extern lv_font_t lv_font_FangZhengKaiTiJianTi_1_26;
extern lv_font_t lv_font_montserratMedium_16;
extern lv_font_t lv_font_mangal_28;
extern lv_font_t lv_font_simpo_28;
extern lv_font_t lv_font_simsun_24;
extern lv_font_t lv_font_leelawadeeui_32;
extern lv_font_t lv_font_fangsong_32;
extern lv_font_t lv_font_simsun_26;
extern lv_font_t lv_font_simsun_16;
extern lv_font_t lv_font_simsun_12;
extern lv_font_t lv_font_arialmt_56;
extern lv_font_t lv_font_simsun_25;
extern lv_font_t lv_font_timesnewromanpsmt_36;
extern lv_font_t lv_font_timesnewromanpsmt_30;
extern lv_font_t lv_font_timesnewromanpsmt_40;
extern lv_font_t lv_font_timesnewromanpsmt_32;
extern lv_font_t lv_font_timesnewromanpsmt_12;
extern lv_font_t lv_font_timesnewromanpsmt_28;
extern lv_font_t lv_font_timesnewromanpsmt_24;
extern lv_font_t lv_font_timesnewromanpsmt_29;
extern lv_font_t lv_font_timesnewromanpsmt_26;
extern lv_font_t lv_font_mangal_36;
extern lv_font_t lv_font_mangal_12;
extern lv_font_t lv_font_mangal_40;
extern lv_font_t lv_font_mangal_30;
extern lv_font_t lv_font_mangal_32;
extern lv_font_t lv_font_mangal_24;
extern lv_font_t lv_font_mangal_29;
extern lv_font_t lv_font_mangal_33;
extern lv_font_t lv_font_mangal_26;
extern lv_font_t lv_font_timesnewromanpsmt_33;
extern lv_font_t lv_font_timesnewromanpsmt_34;
extern lv_font_t lv_font_simplifiedarabic_36;
extern lv_font_t lv_font_simplifiedarabic_12;
extern lv_font_t lv_font_simplifiedarabic_40;
extern lv_font_t lv_font_simplifiedarabic_30;
extern lv_font_t lv_font_simplifiedarabic_32;
extern lv_font_t lv_font_simplifiedarabic_28;
extern lv_font_t lv_font_simplifiedarabic_24;
extern lv_font_t lv_font_simplifiedarabic_29;
extern lv_font_t lv_font_simplifiedarabic_33;
extern lv_font_t lv_font_simplifiedarabic_26;
extern lv_font_t lv_font_fangsong_16;

void init_gui_fonts();
void free_gui_fonts();

#ifdef __cplusplus
}
#endif
#endif
#endif
