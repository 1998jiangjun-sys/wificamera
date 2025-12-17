#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/**
 * @file C
 *
 * BY HUANG YEJIAN
 *
 * 20241203
 */


#include <stddef.h>
#include "multi_language.h"
#include "gui_images.h"  // 包含图片资源定义
#include "gui_fonts.h"   // 包含字体定义
#include "../generated/gui_events/i18n_handler.h"  // 包含国际化处理函数

typedef struct {
    multi_language_text_key_t key;
    const char *translations[MULTI_LANGUAGE_LANG_COUNT];
} multi_language_entry_t;

static size_t clamp_language_index(int lang_id)
{
    if (lang_id < MULTI_LANGUAGE_LANG_MIN || lang_id > MULTI_LANGUAGE_LANG_MAX) {
        return 0;
    }
    return (size_t)(lang_id - MULTI_LANGUAGE_LANG_MIN);
}

static const multi_language_entry_t multi_language_table[] = {
    {
        .key = LANG_TEXT_SHUTTING_DOWN,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "关机中",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "Shutting down",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Выключение",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Extinction",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "Apagando",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Desligando",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "جاري إيقاف التشغيل",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "बंद हो रहा है",
        },
    },
    {
        .key = LANG_TEXT_DORMANCY_ALWAYS_ON,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "常亮",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "Always",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Всегда включён",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Toujours allumé",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "Siempre encendido",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Sempre ligado",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "تشغيل دائم",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "हमेशा चालू",
        },
    },
    {
        .key = LANG_TEXT_DORMANCY_1_MIN,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "1分钟",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "1 minute",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "1 минута",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "1 minute",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "1 minuto",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "1 minuto",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "دقيقة واحدة",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "1 मिनट",
        },
    },
    {
        .key = LANG_TEXT_DORMANCY_3_MIN,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "3分钟",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "3 minutes",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "3 минуты",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "3 minutes",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "3 minutos",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "3 minutos",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "3 دقائق",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "3 मिनट",
        },
    },
    {
        .key = LANG_TEXT_WIFI_CONNECTED,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "已连接",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "already",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Подключено",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Connecté",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "Conectado",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Conectado",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "متصل",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "कनेक्टेड है",
        },
    },
    {
        .key = LANG_TEXT_WIFI_DISCONNECTED,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "未连接",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "not yet",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Не подключено",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Non connecté",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "No conectado",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Não conectado",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "غير متصل",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "कनेक्टेड नहीं है",
        },
    },
    {
        .key = LANG_TEXT_WIFI_CONNECTING,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "连接中...",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "Connecting...",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Подключение...",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Connexion...",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "Conectando...",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Conectando...",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "جاري الاتصال...",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "कनेक्ट हो रहा है...",
        },
    },
    {
        .key = LANG_TEXT_WIFI_CONNECT_SUCCESS,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "连接成功",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "Connected",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Подключено",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Connecté",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "Conectado",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Conectado",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "متصل",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "कनेक्ट हो गया",
        },
    },
    {
        .key = LANG_TEXT_WIFI_CONNECT_FAIL,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "连接失败",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "Connection failed",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Подключение не удалось",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Échec de connexion",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "Error de conexión",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Falha na conexão",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "فشل الاتصال",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "कनेक्शन विफल",
        },
    },
    {
        .key = LANG_TEXT_PHOTO_QUALITY_LOW,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "低",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "Low",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Низкое",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Faible",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "Baja",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Baixa",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "منخفض",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "निम्न",
        },
    },
    {
        .key = LANG_TEXT_PHOTO_QUALITY_MEDIUM,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "中",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "Medium",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Среднее",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Moyen",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "Media",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Média",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "متوسط",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "मध्यम",
        },
    },
    {
        .key = LANG_TEXT_PHOTO_QUALITY_HIGH,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "高",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "High",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Высокое",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Élevé",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "Alta",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Alta",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "عالٍ",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "उच्च",
        },
    },
    {
        .key = LANG_TEXT_LANGUAGE_NAME_CURRENT,
        .translations = {
            [LANG_ZH_CN - MULTI_LANGUAGE_LANG_MIN] = "中文",
            [LANG_ENGLISH_1 - MULTI_LANGUAGE_LANG_MIN] = "English",
            [LANG_RU - MULTI_LANGUAGE_LANG_MIN] = "Русский",
            [LANG_FR - MULTI_LANGUAGE_LANG_MIN] = "Français",
            [LANG_ES - MULTI_LANGUAGE_LANG_MIN] = "Español",
            [LANG_PT - MULTI_LANGUAGE_LANG_MIN] = "Português",
            [LANG_AR - MULTI_LANGUAGE_LANG_MIN] = "العربية",
            [LANG_HI - MULTI_LANGUAGE_LANG_MIN] = "हिन्दी",
        },
    },
};

static const char *multi_language_table_lookup(multi_language_text_key_t key, int lang_id)
{
    const size_t lang_index = clamp_language_index(lang_id);
    for (size_t i = 0; i < sizeof(multi_language_table) / sizeof(multi_language_table[0]); ++i) {
        if (multi_language_table[i].key != key) {
            continue;
        }
        const char *text = NULL;
        if (lang_index < MULTI_LANGUAGE_LANG_COUNT) {
            text = multi_language_table[i].translations[lang_index];
        }
        if (text && text[0] != '\0') {
            return text;
        }
        break;
    }
    return NULL;
}

const char *multi_language_get_text(multi_language_text_key_t key, int lang_id)
{
    const char *text = multi_language_table_lookup(key, lang_id);
    if (text) {
        return text;
    }

    text = multi_language_table_lookup(key, LANG_ENGLISH_1);
    if (text) {
        return text;
    }

    text = multi_language_table_lookup(key, LANG_ZH_CN);
    if (text) {
        return text;
    }

    return "";
}

static const lv_font_t *multi_language_font_large(int lang_id)
{
    switch (lang_id) {
    case LANG_ZH_CN:
        return &lv_font_simsun_32;
    case LANG_ENGLISH_1:
    case LANG_FR:
    case LANG_ES:
    case LANG_PT:
    case LANG_RU:
        return &lv_font_timesnewromanpsmt_32;
    case LANG_AR:
        return &lv_font_simpo_28;
    case LANG_HI:
        return &lv_font_mangal_28;
    default:
        return &lv_font_timesnewromanpsmt_32;
    }
}

static const lv_font_t *multi_language_font_medium(int lang_id)
{
    switch (lang_id) {
    case LANG_ZH_CN:
        return &lv_font_simsun_28;
    case LANG_ENGLISH_1:
    case LANG_FR:
    case LANG_ES:
    case LANG_PT:
    case LANG_RU:
        return &lv_font_timesnewromanpsmt_29;
    case LANG_AR:
        return &lv_font_simpo_28;
    case LANG_HI:
        return &lv_font_mangal_28;
    default:
        return &lv_font_timesnewromanpsmt_29;
    }
}

const lv_font_t *multi_language_pick_font(multi_language_text_key_t key, int lang_id)
{
    switch (key) {
    case LANG_TEXT_SHUTTING_DOWN:
        return multi_language_font_large(lang_id);
    case LANG_TEXT_DORMANCY_ALWAYS_ON:
    case LANG_TEXT_DORMANCY_1_MIN:
    case LANG_TEXT_DORMANCY_3_MIN:
    case LANG_TEXT_WIFI_CONNECTED:
    case LANG_TEXT_WIFI_DISCONNECTED:
    case LANG_TEXT_PHOTO_QUALITY_LOW:
    case LANG_TEXT_PHOTO_QUALITY_MEDIUM:
    case LANG_TEXT_PHOTO_QUALITY_HIGH:
    case LANG_TEXT_LANGUAGE_NAME_CURRENT:
        return multi_language_font_medium(lang_id);
    case LANG_TEXT_WIFI_CONNECTING:
    case LANG_TEXT_WIFI_CONNECT_SUCCESS:
    case LANG_TEXT_WIFI_CONNECT_FAIL:
        if (lang_id == LANG_ZH_CN) {
            return &lv_font_simsun_32;
        }
        return multi_language_font_medium(lang_id);
    default:
        break;
    }

    return multi_language_font_medium(lang_id);
}


// 直接字体名称到字体对象的映射函数
static const lv_font_t* get_font_by_name(const char* font_name) {
    if (!font_name) return NULL;
    
    // 直接映射字体名称到已加载的字体对象
    if (strcmp(font_name, "lv_font_fangsong_16") == 0) {
        return &lv_font_fangsong_16;
    }
    else if (strcmp(font_name, "lv_font_timesnewromanpsmt_16") == 0) {
        //return &lv_font_timesnewromanpsmt_16;
    }
    else if (strcmp(font_name, "lv_font_segoeui_16") == 0) {
        //return &lv_font_segoeui_16;
    }
    else if (strcmp(font_name, "lv_font_mangal_12") == 0) {
        return &lv_font_mangal_12;
    }
    
    return NULL;  // 如果没有找到匹配的字体，返回NULL
}

  //多国语言18语字体映射表
static const excel_font_mapping_t excel_font_mapping[] = {
    {"lv_font_fangsong_16", "一", "zh_cn", LANG_ZH_CN},
    {"lv_font_timesnewromanpsmt_16", "English", "en", LANG_ENGLISH_1},
    {"lv_font_mangal_12", "हिन्दी", "hi", LANG_HI},
    {"lv_font_timesnewromanpsmt_16", "Русский язык", "ru", LANG_RU},
    {"lv_font_segoeui_16", "اللغة العربية", "ar_sa", LANG_AR},
    {"lv_font_segoeui_16", "Français", "fr", LANG_FR},
    {"lv_font_segoeui_16", "Español", "es", LANG_ES},
    {"lv_font_segoeui_16", "Português", "pt", LANG_PT},
    {NULL, NULL, NULL, NULL} // End mark
};

// 语言到国旗图片映射表
static const uint8_t language_flag_mapping[] = {
//   RES_C_CHINA,       // LANG_ZH_CN -> 中文 -> 中国旗
//   RES_C_ENGLISH,     // LANG_ENGLISH_1 -> 英语 -> 英国/美国旗  
//     RES_C_HINDI,       // LANG_HI -> 印地语 -> 印度旗
//   RES_C_RUSSIA,      // LANG_RU -> 俄语 -> 俄国旗
//   RES_C_ARABIC,      // LANG_AR -> 阿拉伯语 -> 阿拉伯旗
//   RES_C_FRENCH,      // LANG_FR -> 法语 -> 法国旗
//   RES_C_SPAIN,       // LANG_ES -> 西班牙语 -> 西班牙旗
//   RES_C_PORTUGUESE,  // LANG_PT -> 葡萄牙语 -> 葡萄牙旗
};


#define FLEX_POS_X  20   // 调整X位置，使其居中
#define FLEX_POS_Y  20   // 调整Y位置，从顶部开始
#define FLEX_WIDTH  600  // 增加宽度以容纳576px的标签
#define FLEX_HEIGHT  440 // 增加高度以容纳更多语言项，覆盖整个界面高度

// 移除按键导航相关的外部变量声明
// 如果需要按键导航支持，请取消注释以下代码：
// #if !LV_USE_GUIBUILDER_SIMULATOR
// extern lv_group_t* def_group;
// extern lv_group_t* group_list;
// extern lv_indev_t* indev_keypad;
// #endif

static lv_obj_t* flex_cont = 0;
static lv_obj_t* focused_obj = 0;//记录当前高亮对象

// 函数声明
static void scroll_event_handler(lv_event_t* e);
static void screen_scroll_protection_handler(lv_event_t* e);
static void flex_cont_event_handler(lv_event_t* e);

// 滚动事件处理器，防止滚动事件传播
static void scroll_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    
    if (code == LV_EVENT_SCROLL) {
        //printf("[chili]: %s scroll event on obj=%p\n", __func__, target);
        
        // 确认滚动只发生在 flex_cont 内部
        if (target == flex_cont) {
            // 只允许在flex_cont内部滚动，阻止传播到其他对象
            lv_event_stop_processing(e);
            lv_event_stop_bubbling(e);
            
            // 获取当前滚动位置，确保滚动在合理范围内
            lv_coord_t scroll_y = lv_obj_get_scroll_y(flex_cont);
            lv_coord_t scroll_top = lv_obj_get_scroll_top(flex_cont);
            lv_coord_t scroll_bottom = lv_obj_get_scroll_bottom(flex_cont);
            
            //printf("[chili]: %s scroll_y=%d, top=%d, bottom=%d\n", 
                   //__func__, scroll_y, scroll_top, scroll_bottom);
                   
            // 如果滚动超出边界，则限制在边界内
            if (scroll_y < 0) {
                lv_obj_scroll_to_y(flex_cont, 0, LV_ANIM_OFF);
            } else if (scroll_bottom < 0) {
                lv_obj_scroll_to_y(flex_cont, scroll_y + scroll_bottom, LV_ANIM_OFF);
            }
        } else {
            // 如果不是在flex_cont上的滚动事件，则阻止处理
            //printf("[chili]: %s blocking scroll on non-flex object=%p\n", __func__, target);
            lv_event_stop_processing(e);
            lv_event_stop_bubbling(e);
        }
    }
}

// 整个屏幕的滚动保护处理器
static void screen_scroll_protection_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    
    if (code == LV_EVENT_SCROLL) {
        // 只允许flex_cont进行滚动，阻止其他所有对象的滚动
        if (target != flex_cont) {
            //printf("[chili]: %s blocking scroll on protected object=%p (not flex_cont=%p)\n", 
            //       __func__, target, flex_cont);
            lv_event_stop_processing(e);
            lv_event_stop_bubbling(e);
        }
    }
    
    // 对于其他可能影响滚动的事件也进行保护
    if (code == LV_EVENT_SCROLL_BEGIN || code == LV_EVENT_SCROLL_END) {
        if (target != flex_cont) {
            //printf("[chili]: %s blocking scroll begin/end on protected object=%p\n", __func__, target);
            lv_event_stop_processing(e);
            lv_event_stop_bubbling(e);
        }
    }
}


static void flex_cont_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    //lv_ui* ui = (lv_ui*)lv_event_get_user_data(e);
    lv_obj_t* src = lv_event_get_target(e);  // 获取触发事件的对象（语言项容器）
    char label_str[128] = { 0 };  // 存储标签文本的缓冲区

    switch (code) {
    case LV_EVENT_CLICKED: {  // 处理点击事件
        // 获取语言文本（从语言标签中获取）
        lv_obj_t* lang_label = lv_obj_get_child(src, 1);  // 获取语言标签（第二个子对象，索引为1）
        if (lang_label) {
            const char* lang_text = lv_label_get_text(lang_label);
            if (lang_text) {
                strcpy(label_str, lang_text);
            }
        }

        // 首先将所有语言项的选择图片设置为未选中状态
        if (focused_obj && focused_obj != src) {
            // 找到之前选中项的选择图片（第三个子对象，索引为2）
            lv_obj_t* prev_select = lv_obj_get_child(focused_obj, 2);
            if (prev_select) {
                lv_img_set_src(prev_select, GUI_GET_C_IMAGE(RES_C_SELECT_NO));  // 设置为未选中图片
            }
        }

        // 设置当前点击项的选择图片为选中状态
        if (src) {
            lv_obj_t* curr_select = lv_obj_get_child(src, 2);  // 获取选择图片（第三个子对象，索引为2）
            if (curr_select) {
                lv_img_set_src(curr_select, GUI_GET_C_IMAGE(RES_C_SELECT));  // 设置为选中图片
            }
            focused_obj = src;  // 记录当前选中的容器对象
        }

        // 遍历语言映射表，查找匹配的语言项
        for (uint16_t i = 0; excel_font_mapping[i].ture_name != NULL; i++) {
            if (strcmp(label_str, excel_font_mapping[i].ture_name) == 0)  // 如果标签文本匹配
            {
                // 将选中的语言ID保存到数据库
                db_update("lag", excel_font_mapping[i].id);
                // 设置国际化本地化语言
                lv_i18n_set_locale(excel_font_mapping[i].origin_text);
                break;  // 找到匹配项后退出循环
            }        }
        
        // 刷新所有UI文本，使语言设置立即生效
        i18n_refresh_all_texts();
        
        // 刷新系统菜单子页面的标题信息
       // my_sysmenu_subpage.icon_res_id = (void*)RES_LANGUAGES;  // 设置语言图标资源
       // my_sysmenu_subpage.title = (void*)_("language");  // 设置标题为当前语言的"语言"文本

        // 显示更新后的系统菜单子页面
        //sysmenu_subpage_show(&my_sysmenu_subpage);
        
        // 按键导航组管理已移除，如需要请参考原代码
        
        // 获取系统设置界面指针
        //lv_ui_sys_setting * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYS_SETTING);
        //if(!ui_scr) return;  // 如果获取失败则返回
        
        // 将焦点设置到系统设置界面的特定图标对象上
        //lv_group_focus_obj(ui_scr->sys_setting_img_5);

    }
    break;
    default:
        break;  // 其他事件类型不处理
    }
}

/*
*   弹性布局放置18语 label列表并根据语言映射表设置对应的字体样式
*
*/
void flex_language_list(void)
{
    const lv_font_t* font_tmp = NULL;  // 临时字体指针，用于存储当前语言对应的字体

    // 安全删除现有容器
    if (flex_cont != NULL) {
        // 检查对象是否有效
        if (lv_obj_is_valid(flex_cont)) {
            lv_obj_del(flex_cont);
        }
        flex_cont = NULL;
    }
    // 获取系统设置界面的指针
    lv_ui_Language_Selection * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_LANGUAGE_SELECTION);
    if(!ui_scr) {
        return;
    }
    
    // 在系统设置子页面中创建弹性布局容器
    flex_cont = lv_obj_create(ui_scr->Language_Selection);
    if (!flex_cont) {
        return;
    }
    
    // 设置语言列表容器位置，覆盖整个界面区域但层级在底层
    lv_coord_t cont_x = 16;   // 设置X位置为16
    lv_coord_t cont_y = 120;  // 设置Y位置为120
    
    // 设置容器的位置和大小
    lv_obj_set_pos(flex_cont, cont_x, cont_y);            // 设置位置为(16, 120)
    lv_obj_set_size(flex_cont, FLEX_WIDTH, FLEX_HEIGHT);  // 设置容器大小：宽=600, 高=440
    
    // 将语言列表容器移动到倒数第二层，背景图片在最底层，view_1和btn_1在上方
    lv_obj_move_to_index(flex_cont, 1);
    
    // 设置容器的样式属性
    lv_obj_set_style_pad_all(flex_cont, 16, 0);           // 设置内边距为16px
    lv_obj_set_style_arc_width(flex_cont, 0, 0);          // 设置圆弧宽度为0（无圆角）
    lv_obj_set_flex_flow(flex_cont, LV_FLEX_FLOW_COLUMN); // 设置弹性布局为列排列
    lv_obj_set_style_bg_color(flex_cont, lv_color_white(), 0);  // 设置背景色为白色
    lv_obj_set_style_border_width(flex_cont, 0, 0);       // 设置边框宽度为0（无边框）
    lv_obj_set_style_radius(flex_cont, 24, 0);            // 设置圆角为24像素
    
    // 设置滚动属性，限制滚动只在此容器内生效
    lv_obj_add_flag(flex_cont, LV_OBJ_FLAG_SCROLLABLE);   // 使容器可滚动
    lv_obj_set_scroll_dir(flex_cont, LV_DIR_VER);         // 设置垂直滚动
    lv_obj_set_scroll_snap_y(flex_cont, LV_SCROLL_SNAP_NONE); // 禁用滚动捕捉
    
    // *** 关键：禁用滚动链，防止滚动传播到父对象 ***
    lv_obj_clear_flag(flex_cont, LV_OBJ_FLAG_SCROLL_CHAIN_HOR); // 禁用水平滚动链
    lv_obj_clear_flag(flex_cont, LV_OBJ_FLAG_SCROLL_CHAIN_VER); // 禁用垂直滚动链
    
    // 设置滚动条样式，使其更精确控制
    lv_obj_set_style_pad_row(flex_cont, 8, 0);            // 设置行间距
    lv_obj_set_scrollbar_mode(flex_cont, LV_SCROLLBAR_MODE_AUTO); // 自动显示滚动条
    
    // 确保父容器不会被滚动影响
    lv_obj_clear_flag(ui_scr->Language_Selection, LV_OBJ_FLAG_SCROLLABLE); // 确保父容器不可滚动
    
    // 确保其他UI元素不受滚动影响
    if (ui_scr->Language_Selection_img_1) {
        lv_obj_clear_flag(ui_scr->Language_Selection_img_1, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_clear_flag(ui_scr->Language_Selection_img_1, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
        lv_obj_clear_flag(ui_scr->Language_Selection_img_1, LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    }
    
    if (ui_scr->Language_Selection_view_1) {
        lv_obj_clear_flag(ui_scr->Language_Selection_view_1, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_clear_flag(ui_scr->Language_Selection_view_1, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
        lv_obj_clear_flag(ui_scr->Language_Selection_view_1, LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    }
    
    if (ui_scr->Language_Selection_btn_1) {
        lv_obj_clear_flag(ui_scr->Language_Selection_btn_1, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_clear_flag(ui_scr->Language_Selection_btn_1, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
        lv_obj_clear_flag(ui_scr->Language_Selection_btn_1, LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    }
    
    // if (ui_scr->Language_Selection_edit_1) {
    //     lv_obj_clear_flag(ui_scr->Language_Selection_edit_1, LV_OBJ_FLAG_SCROLLABLE);
    //     lv_obj_clear_flag(ui_scr->Language_Selection_edit_1, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    //     lv_obj_clear_flag(ui_scr->Language_Selection_edit_1, LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    // }
    
    // 添加滚动事件处理器，确保滚动不会影响其他页面元素
    lv_obj_add_event_cb(flex_cont, scroll_event_handler, LV_EVENT_SCROLL, NULL);
    
    // 遍历语言映射表，为每种语言创建对应的标签容器
    for (uint16_t i = 0; excel_font_mapping[i].ture_name != NULL; i++) {
        // 为每个语言项创建一个容器，用于放置圆形选择框和语言标签
        lv_obj_t* lang_item_cont = lv_obj_create(flex_cont);
        lv_obj_set_size(lang_item_cont, 576, 80);  // 设置标签大小为576*80
        lv_obj_set_style_bg_color(lang_item_cont, lv_color_make(0x5F, 0x93, 0xE8), 0);  // 蓝色背景
        lv_obj_set_style_border_width(lang_item_cont, 0, 0);
        lv_obj_set_style_radius(lang_item_cont, 16, 0);  // 设置圆角为16px
        lv_obj_set_style_pad_all(lang_item_cont, 0, 0);
        lv_obj_set_style_pad_left(lang_item_cont, 20, 0);   // 增加左侧内边距
        lv_obj_set_style_pad_right(lang_item_cont, 20, 0);  // 增加右侧内边距
        lv_obj_set_style_pad_top(lang_item_cont, 0, 0);     // 顶部内边距为0
        lv_obj_set_style_pad_bottom(lang_item_cont, 8, 0);  // 底部内边距作为项目间距
        lv_obj_clear_flag(lang_item_cont, LV_OBJ_FLAG_SCROLLABLE); // 明确禁用子容器滚动
        lv_obj_clear_flag(lang_item_cont, LV_OBJ_FLAG_GESTURE_BUBBLE); // 禁用手势事件冒泡
        
        // 设置弹性布局，确保子元素垂直居中，国旗在左侧，语言标签在中间，选择图片在右侧
        lv_obj_set_flex_flow(lang_item_cont, LV_FLEX_FLOW_ROW);
        lv_obj_set_style_flex_main_place(lang_item_cont, LV_FLEX_ALIGN_SPACE_BETWEEN, 0);  // 主轴两端对齐
        lv_obj_set_style_flex_cross_place(lang_item_cont, LV_FLEX_ALIGN_CENTER, 0);       // 交叉轴居中（垂直居中）
        lv_obj_set_style_flex_track_place(lang_item_cont, LV_FLEX_ALIGN_CENTER, 0);       // 轨道居中
        lv_obj_set_flex_align(lang_item_cont, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        // 创建国旗图片（左侧）
        lv_obj_t* flag_img = lv_img_create(lang_item_cont);
        //lv_img_set_src(flag_img, GUI_GET_C_IMAGE(language_flag_mapping[i]));  // 使用对应的国旗图片
        lv_obj_set_style_flex_grow(flag_img, 0, 0);  // 国旗图片大小固定，不扩展
        lv_obj_clear_flag(flag_img, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_clear_flag(flag_img, LV_OBJ_FLAG_CLICKABLE);

        // 在弹性容器中创建语言标签（中间）
        lv_obj_t* langu_label = lv_label_create(lang_item_cont);
        
        // 设置标签显示的语言文本
        lv_label_set_text(langu_label, excel_font_mapping[i].ture_name);
        
        // 禁用标签的滚动功能
        lv_obj_clear_flag(langu_label, LV_OBJ_FLAG_SCROLLABLE);
        
        //====== 设置标签的样式 ======
        lv_obj_set_style_text_color(langu_label, lv_color_white(), 0);  // 白色文字
        lv_obj_set_style_text_align(langu_label, LV_TEXT_ALIGN_LEFT, 0);  // 左对齐
        // 移除自定义对齐设置，让弹性布局自动处理垂直居中
        lv_obj_set_style_pad_all(langu_label, 0, 0);  // 确保文本标签无内边距

        // 创建选择图片指示器（右侧）
        lv_obj_t* select_img = lv_img_create(lang_item_cont);
        lv_obj_set_style_flex_grow(select_img, 0, 0);  // 选择图片大小固定，不扩展
        lv_obj_clear_flag(select_img, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_clear_flag(select_img, LV_OBJ_FLAG_CLICKABLE);
        
        //====== 设置标签的样式 ======
        lv_obj_set_style_text_color(langu_label, lv_color_white(), 0);  // 白色文字
        lv_obj_set_style_text_align(langu_label, LV_TEXT_ALIGN_LEFT, 0);  // 左对齐
        // 确保文本标签无内边距，并设置为flex grow为1，让它占据剩余空间
        lv_obj_set_style_pad_all(langu_label, 0, 0);
        lv_obj_set_style_flex_grow(langu_label, 1, 0);  // 让语言标签占据剩余空间，推动选择图片到右侧
          //====== 根据当前设置的语言，选中对应的语言标签 ======
        // 如果当前标签对应的语言ID与数据库中保存的语言ID匹配
        if (db_select("lag") == excel_font_mapping[i].id) {
            // 设置选择图片为选中状态
            lv_img_set_src(select_img, GUI_GET_C_IMAGE(RES_C_SELECT));
            focused_obj = lang_item_cont;  // 记录当前选中的对象
        } else {
            // 未选中状态：显示未选中图片
            lv_img_set_src(select_img, GUI_GET_C_IMAGE(RES_C_SELECT_NO));
        }        //====== 为每个语言标签设置对应的字体样式 ======
        // 根据语言映射表获取对应的字体，使用我们的直接映射函数
        font_tmp = get_font_by_name(excel_font_mapping[i].font_name);
        
        // 如果字体获取成功且标签对象有效，则设置字体
        if (font_tmp && langu_label) {
            lv_obj_set_style_text_font(langu_label, font_tmp, LV_STATE_DEFAULT);  // 设置默认状态下的字体
            lv_obj_set_style_text_font(langu_label, font_tmp, LV_STATE_ANY);     // 设置所有状态下的字体
        }
        
        //====== 为语言项容器添加交互功能 ======
        lv_obj_add_flag(lang_item_cont, LV_OBJ_FLAG_CLICKABLE);  // 使容器可点击
        // 为容器添加点击事件回调函数
        lv_obj_add_event_cb(lang_item_cont, flex_cont_event_handler, LV_EVENT_CLICKED, NULL);
          // 将语言文本作为用户数据存储到容器中，便于事件处理时获取
        lv_obj_set_user_data(lang_item_cont, (void*)excel_font_mapping[i].ture_name);
        
        //lv_obj_update_layout(flex_cont);  // 可选：刷新容器布局

        // 按键导航支持已移除，如需要请参考原代码
    }    // 按键导航组管理已移除，如需要请参考原代码

    // *** 最终确保滚动完全隔离 ***
    
    // 为整个Language_Selection屏幕添加滚动监听，确保只有flex_cont可以滚动
    lv_obj_add_event_cb(ui_scr->Language_Selection, screen_scroll_protection_handler, LV_EVENT_ALL, NULL);
    
    // 强制更新布局，确保所有设置生效
    lv_obj_update_layout(ui_scr->Language_Selection);
    lv_obj_update_layout(flex_cont);
}

/*
*   隐藏弹性布局放置18语 label列表
*
*/
void hide_flex_language_list(void)
{
    // 安全删除弹性容器
    if (flex_cont != NULL) {
        // 检查对象是否有效
        if (lv_obj_is_valid(flex_cont)) {
            lv_obj_del(flex_cont);
        }
        
        // 将容器指针设置为NULL，防止产生悬空指针
        flex_cont = NULL;
        
        // 注释掉的代码：原本使用隐藏标志来隐藏容器
        // 现在改为直接删除容器，更彻底地释放资源
        //lv_obj_add_flag(flex_cont, LV_OBJ_FLAG_HIDDEN);
    }
}

/*
*   根据flash语言设置刷新所有UI的字体样式
*   返回值：对应excel表的origin_text
*/
char* refresh_all_obj_language_style(void)
{
    uint16_t i = 0;  // 循环索引变量，用于遍历语言映射表
    
    int saved_lang_id = db_select("lag");
    //printf("refresh_all_obj_language_style: saved_lang_id=%d\n", saved_lang_id);
    
    // 遍历语言映射表，查找与数据库中保存的语言ID匹配的项
    for (i = 0; excel_font_mapping[i].ture_name != NULL; i++) {
        // 从数据库读取保存的语言ID，与映射表中的语言ID进行比较
        if (saved_lang_id == excel_font_mapping[i].id) {
            // 设置LVGL国际化库的本地化语言环境
            // 使用映射表中对应的origin_text作为语言代码（如"zh_cn", "en"等）
            lv_i18n_set_locale(excel_font_mapping[i].origin_text);
            //printf("refresh_all_obj_language_style: matched lang at index %d, id=%d, locale=%s, name=%s\n", 
                   //i, excel_font_mapping[i].id, excel_font_mapping[i].origin_text, excel_font_mapping[i].ture_name);
            
            // 找到匹配项后立即退出循环，避免不必要的遍历
            break;
        }
    }
    
    if (excel_font_mapping[i].ture_name == NULL) {
        // 如果没有找到匹配的语言，使用第一个语言作为默认
        //printf("refresh_all_obj_language_style: no match found, using default lang at index 0\n");
        i = 0;
        lv_i18n_set_locale(excel_font_mapping[0].origin_text);
    }
    
    // 刷新所有UI界面的文本内容，使新的语言设置立即生效
    // 这个函数会遍历所有已注册的UI对象并更新其显示文本
    i18n_refresh_all_texts();

    // 返回当前设置的语言代码字符串
    return excel_font_mapping[i].origin_text;
}

bool multi_language_apply_locale(const char *locale)
{
    if (!locale) {
        return false;
    }

    for (uint16_t i = 0; excel_font_mapping[i].ture_name != NULL; i++) {
        if (strcmp(locale, excel_font_mapping[i].origin_text) == 0) {
            if (db_select("lag") != excel_font_mapping[i].id) {
                db_update("lag", excel_font_mapping[i].id);
            }
            lv_i18n_set_locale(locale);
            i18n_refresh_all_texts();
            return true;
        }
    }

    lv_i18n_set_locale(locale);
    i18n_refresh_all_texts();
    return false;
}
#endif
