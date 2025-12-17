#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
#ifndef __MULTI_LANGUAGE_H_
#define __MULTI_LANGUAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "lvgl.h"
#include "custom.h"


    typedef struct {
        const char* font_name;
        const char* ture_name;//对应excel表suplanguage的字体字号
        const char* origin_text;//对应excel表origin_text
        int id;//id宏 写flash用
    } excel_font_mapping_t;



    /*
          中文: 中文
          繁体中文: 繁體中文
          英语: English
          俄语: Русский язык
          泰语: ภาษาไทย
          阿拉伯语: اللغة العربية
          德语: Deutsch
          法语: Français
          韩语: 한국어
          日语: 日本語
          西班牙语: Español
          葡萄牙语: Português
          捷克语: Čeština
          波兰语: Polski
          意大利语: Italiano
          荷兰语: Nederlands
          瑞典语: Svenska
          丹麦语: Dansk
    */
    enum {                  //语言
        LANG_ZH_CN = 1,    // 中文
        LANG_ENGLISH_1,      // 英语
        LANG_RU,           // 俄语
        LANG_FR,           // 法语
        LANG_ES,           // 西班牙语
        LANG_PT,           // 葡萄牙语
        LANG_AR,           // 阿拉伯语
        LANG_HI,           // 印地语
    };

#define MULTI_LANGUAGE_LANG_MIN   (LANG_ZH_CN)
#define MULTI_LANGUAGE_LANG_MAX   (LANG_HI)
#define MULTI_LANGUAGE_LANG_COUNT (MULTI_LANGUAGE_LANG_MAX - MULTI_LANGUAGE_LANG_MIN + 1)

    typedef enum {
        LANG_TEXT_SHUTTING_DOWN = 0,
        LANG_TEXT_DORMANCY_ALWAYS_ON,
        LANG_TEXT_DORMANCY_1_MIN,
        LANG_TEXT_DORMANCY_3_MIN,
        LANG_TEXT_WIFI_CONNECTED,
        LANG_TEXT_WIFI_DISCONNECTED,
        LANG_TEXT_WIFI_CONNECTING,
        LANG_TEXT_WIFI_CONNECT_SUCCESS,
        LANG_TEXT_WIFI_CONNECT_FAIL,
        LANG_TEXT_PHOTO_QUALITY_LOW,
        LANG_TEXT_PHOTO_QUALITY_MEDIUM,
        LANG_TEXT_PHOTO_QUALITY_HIGH,
        LANG_TEXT_LANGUAGE_NAME_CURRENT,
        LANG_TEXT_MAX
    } multi_language_text_key_t;

    const char *multi_language_get_text(multi_language_text_key_t key, int lang_id);
    const lv_font_t *multi_language_pick_font(multi_language_text_key_t key, int lang_id);

    /*
    *   根据flash语言设置刷新所有UI的字体样式
    *   返回值：对应excel表的origin_text
    */
    char* refresh_all_obj_language_style(void);

    /*
    *   根据传入的locale字符串设置语言，刷新UI并写入持久化存储
    *   返回值：true表示成功匹配并应用，false表示locale未在映射表中找到
    */
    bool multi_language_apply_locale(const char *locale);


    /*
    *   弹性布局放置18语 label列表并根据语言映射表设置对应的字体样式
    *
    */
    void flex_language_list(void);


    /*
    *   隐藏弹性布局放置18语 label列表
    *
    */
    void hide_flex_language_list(void);


#ifdef __cplusplus
}
#endif
#endif /* __MULTI_LANGUAGE_H_ */


#endif
