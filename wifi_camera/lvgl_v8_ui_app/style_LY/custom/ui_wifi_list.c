#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/**
 * @file ui_wifi_list.c
 *
 * WiFi列表显示组件
 * 
 * 参考multi_language.c实现
 * 用于显示搜索到的WiFi网络列表
 *
 * BY AI ASSISTANT 
 * 2024
 */

#include "ui_wifi_list.h"
#include "gui_images.h"  // 包含图片资源定义
#include "gui_fonts.h"   // 包含字体定义
#include "multi_language.h"
#include <stdlib.h>      // 包含malloc/free
#include <string.h>      // 包含字符串操作
#include <stdint.h>
#include <stdio.h>       // 包含printf

// 需要包含WiFi扫描结构体定义
#ifdef CONFIG_NET_ENABLE
#include "wifi/wifi_connect.h"
#endif

// WiFi列表布局参数
#define WIFI_LIST_POS_X  16   // WiFi列表X位置
#define WIFI_LIST_POS_Y  304  // WiFi列表Y位置
#define WIFI_LIST_WIDTH  448  // WiFi列表宽度
#define WIFI_LIST_HEIGHT 350  // WiFi列表高度

#define WIFI_ITEM_WIDTH  448   // 每个WiFi项的宽度
#define WIFI_ITEM_HEIGHT 104   // 每个WiFi项的高度
#define WIFI_ITEM_RADIUS 16   // WiFi项的圆角
#define WIFI_ITEM_SPACING 8   // WiFi项的上下间隔
#define WIFI_ITEM_PADDING 0   // WiFi项的内边距设为0，使用自定义布局
#define WIFI_ICON_SIZE 64     // WiFi图标大小 - 64x64
#define WIFI_TEXT_LEFT_MARGIN 24   // WiFi名字左边距
#define WIFI_TEXT_TOP_MARGIN 18    // WiFi名字上下边距
#define WIFI_ICON_RIGHT_MARGIN 24  // WiFi图标右边距
#define WIFI_ICON_TOP_MARGIN 16    // WiFi图标上下边距


// 全局WiFi列表管理器
static wifi_list_manager_t wifi_manager = {0};
static wifi_item_click_cb_t item_click_callback = NULL;

static bool s_has_pending_connecting = false;
static char s_pending_connecting_ssid[33] = {0};

static inline uintptr_t encode_status_label_index(uint32_t index)
{
    return ((uintptr_t)index << 1) | 1u;
}

static inline bool decode_status_label_index(lv_obj_t *obj, uint32_t *out_index)
{
    uintptr_t raw = (uintptr_t)lv_obj_get_user_data(obj);
    if ((raw & 1u) == 0) {
        return false;
    }
    if (out_index) {
        *out_index = (uint32_t)(raw >> 1);
    }
    return true;
}

// WiFi列表持久化数据管理
typedef struct {
    wifi_item_info_t* saved_items;  // 保存的WiFi项目数组
    uint32_t saved_count;           // 保存的WiFi数量
    bool has_saved_data;            // 是否有保存的数据
} wifi_persistent_data_t;

static wifi_persistent_data_t persistent_data = {0};

// 函数声明
static void wifi_item_event_handler(lv_event_t* e);
static void wifi_list_scroll_event_handler(lv_event_t* e);
static lv_obj_t* create_wifi_item(lv_obj_t* parent, const wifi_item_info_t* wifi_info);
static void update_wifi_item_content(lv_obj_t* item, const wifi_item_info_t* wifi_info);
static const char* get_auth_mode_text(int auth_mode);
static lv_color_t get_signal_color(int rssi);
static bool wifi_list_apply_connecting_status(void);
static void wifi_list_cleanup(bool detach_parent);
static int wifi_list_get_current_language(void);
static void wifi_status_label_apply_font(lv_obj_t *label, int lang_id);
static void wifi_status_label_update(lv_obj_t *label, multi_language_text_key_t key, lv_color_t color);
static void wifi_status_label_clear(lv_obj_t *label, lv_color_t color);

static bool wifi_list_is_ui_context_ready(void)
{
    if (!wifi_manager.wifi_list_cont) {
        return false;
    }

    if (!lv_obj_is_valid(wifi_manager.wifi_list_cont)) {
        printf("[WiFi List] Warning: list container invalid, clearing reference\n");
        wifi_manager.wifi_list_cont = NULL;
        wifi_manager.is_visible = false;
        return false;
    }

    if (lv_obj_has_flag(wifi_manager.wifi_list_cont, LV_OBJ_FLAG_HIDDEN)) {
        return false;
    }

    return true;
}

bool wifi_list_can_async_update(void)
{
    if (!wifi_manager.is_visible) {
        return false;
    }

    if (!wifi_manager.wifi_list_cont || !lv_obj_is_valid(wifi_manager.wifi_list_cont)) {
        return false;
    }

    return wifi_list_is_screen_active();
}

static int wifi_list_get_current_language(void)
{
    return db_select("lag");
}

static void wifi_status_label_apply_font(lv_obj_t *label, int lang_id)
{
    if (!label) {
        return;
    }

    const lv_font_t *status_font = multi_language_pick_font(LANG_TEXT_WIFI_CONNECT_SUCCESS, lang_id);
    if (status_font) {
        lv_obj_set_style_text_font(label, status_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

static void wifi_status_label_update(lv_obj_t *label, multi_language_text_key_t key, lv_color_t color)
{
    if (!label) {
        return;
    }

    int lang_id = wifi_list_get_current_language();
    wifi_status_label_apply_font(label, lang_id);
    lv_label_set_text(label, multi_language_get_text(key, lang_id));
    lv_obj_set_style_text_color(label, color, LV_PART_MAIN);
}

static void wifi_status_label_clear(lv_obj_t *label, lv_color_t color)
{
    if (!label) {
        return;
    }

    int lang_id = wifi_list_get_current_language();
    wifi_status_label_apply_font(label, lang_id);
    lv_label_set_text(label, "");
    lv_obj_set_style_text_color(label, color, LV_PART_MAIN);
}

/**
 * @brief 初始化WiFi列表组件
 */
bool wifi_list_init(lv_obj_t* parent)
{
    if (!parent) {
        printf("[WiFi List] Error: parent is NULL\n");
        return false;
    }

    // 保存父屏幕对象
    wifi_manager.parent_screen = parent;
    wifi_manager.wifi_list_cont = NULL;
    wifi_manager.wifi_items = NULL;
    wifi_manager.wifi_count = 0;
    wifi_manager.is_visible = false;
    wifi_manager.focused_obj = NULL;

    printf("[WiFi List] Initialized successfully\n");
    return true;
}

/**
 * @brief 显示WiFi列表
 */
void wifi_list_show(lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height)
{
    if (!wifi_manager.parent_screen) {
        printf("[WiFi List] Error: not initialized\n");
        return;
    }

    // 如果容器已经存在且有效，只需要显示它
    if (wifi_manager.wifi_list_cont && lv_obj_is_valid(wifi_manager.wifi_list_cont)) {
        // 显示容器并更新位置和尺寸
        lv_obj_clear_flag(wifi_manager.wifi_list_cont, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_pos(wifi_manager.wifi_list_cont, x, y);
        lv_obj_set_size(wifi_manager.wifi_list_cont, width, height);
        lv_obj_set_scroll_dir(wifi_manager.wifi_list_cont, LV_DIR_VER);
        lv_obj_scroll_to_x(wifi_manager.wifi_list_cont, 0, LV_ANIM_OFF);
        lv_obj_clear_flag(wifi_manager.wifi_list_cont, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
        lv_obj_clear_flag(wifi_manager.wifi_list_cont, LV_OBJ_FLAG_SCROLL_CHAIN_VER);
        wifi_manager.is_visible = true;
        wifi_list_apply_connecting_status();
        printf("[WiFi List] WiFi list container shown (reusing existing)\n");
        return;
    }

    // 如果容器不存在或无效，创建新的
    wifi_manager.wifi_list_cont = lv_obj_create(wifi_manager.parent_screen);
    if (!wifi_manager.wifi_list_cont) {
        printf("[WiFi List] Error: failed to create container\n");
        return;
    }

    // 设置容器位置和尺寸
    lv_obj_set_pos(wifi_manager.wifi_list_cont, x, y);
    lv_obj_set_size(wifi_manager.wifi_list_cont, width, height);// 设置容器样式 - 透明背景
    lv_obj_set_style_bg_opa(wifi_manager.wifi_list_cont, 0, LV_PART_MAIN);  // 完全透明
    lv_obj_set_style_border_width(wifi_manager.wifi_list_cont, 0, LV_PART_MAIN);  // 移除边框
    lv_obj_set_style_shadow_width(wifi_manager.wifi_list_cont, 0, LV_PART_MAIN);  // 移除阴影
    lv_obj_set_style_pad_all(wifi_manager.wifi_list_cont, 0, LV_PART_MAIN);  // 设置内边距为0    // 设置布局为flex column
    lv_obj_set_flex_flow(wifi_manager.wifi_list_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(wifi_manager.wifi_list_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(wifi_manager.wifi_list_cont, WIFI_ITEM_SPACING, LV_PART_MAIN);  // 设置项目间隔
    lv_obj_clear_flag(wifi_manager.wifi_list_cont, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    lv_obj_clear_flag(wifi_manager.wifi_list_cont, LV_OBJ_FLAG_SCROLL_CHAIN_VER);

    // 设置滚动条
    lv_obj_set_scrollbar_mode(wifi_manager.wifi_list_cont, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_set_scroll_dir(wifi_manager.wifi_list_cont, LV_DIR_VER);

    // 添加滚动事件处理
    lv_obj_add_event_cb(wifi_manager.wifi_list_cont, wifi_list_scroll_event_handler, LV_EVENT_ALL, NULL);

    // 设置为可见
    wifi_manager.is_visible = true;
    wifi_list_apply_connecting_status();

    printf("[WiFi List] WiFi list container created and shown\n");
}

/**
 * @brief 隐藏WiFi列表
 */
void wifi_list_hide(void)
{
    printf("[WiFi List] wifi_list_hide() called\n");

    wifi_list_cleanup(false);

    printf("[WiFi List] WiFi list cleaned (hidden)\n");
}

/**
 * @brief 更新WiFi列表数据
 */
void wifi_list_update_data(struct wifi_scan_ssid_info* wifi_scan_results, uint32_t count)
{
    printf("[WiFi List] wifi_list_update_data called with count=%d\n", count);
    
    // 检查WiFi管理器是否已初始化
    if (!wifi_manager.parent_screen) {
        printf("[WiFi List] Error: WiFi manager not initialized, cannot update\n");
        return;
    }
    
    if (!wifi_scan_results || count == 0) {
        printf("[WiFi List] No WiFi data to update\n");
        wifi_list_clear();
        return;
    }

    if (!wifi_manager.wifi_list_cont || !lv_obj_is_valid(wifi_manager.wifi_list_cont)) {
        printf("[WiFi List] WiFi list container not available, creating with default position\n");
        // 如果容器不存在或无效，创建默认位置的容器
        wifi_list_show(20, 80, 440, 400);  // 使用默认位置和尺寸
        
        if (!wifi_manager.wifi_list_cont) {
            printf("[WiFi List] Error: Failed to create WiFi list container\n");
            return;
        }
    }

    // 检查父屏幕是否仍然有效
    if (!lv_obj_is_valid(wifi_manager.parent_screen)) {
        printf("[WiFi List] Error: parent screen is invalid, cannot update WiFi list\n");
        wifi_list_clear();
        return;
    }

    // 检查WiFi列表容器是否仍然有效
    if (!lv_obj_is_valid(wifi_manager.wifi_list_cont)) {
        printf("[WiFi List] Error: WiFi list container is invalid, cannot update\n");
        wifi_manager.wifi_list_cont = NULL;
        wifi_list_clear();
        return;
    }

    // 添加数量限制，防止内存问题
    if (count > 50) {
        printf("[WiFi List] Warning: Too many WiFi networks (%d), limiting to 50\n", count);
        count = 50;
    }

    // 清空现有内容
    wifi_list_clear();

    // 分配内存存储WiFi信息
    printf("[WiFi List] Allocating memory for %d WiFi items\n", count);
    wifi_manager.wifi_items = (wifi_item_info_t*)malloc(count * sizeof(wifi_item_info_t));
    if (!wifi_manager.wifi_items) {
        printf("[WiFi List] Error: failed to allocate memory for WiFi items\n");
        return;
    }

    wifi_manager.wifi_count = count;

    // 转换并存储WiFi信息
    for (uint32_t i = 0; i < count; i++) {
        strncpy(wifi_manager.wifi_items[i].ssid, wifi_scan_results[i].ssid, 32);
        wifi_manager.wifi_items[i].ssid[32] = '\0';
        wifi_manager.wifi_items[i].rssi = wifi_scan_results[i].rssi;
        wifi_manager.wifi_items[i].snr = wifi_scan_results[i].snr;
        wifi_manager.wifi_items[i].channel_number = wifi_scan_results[i].channel_number;
        wifi_manager.wifi_items[i].auth_mode = wifi_scan_results[i].auth_mode;
        wifi_manager.wifi_items[i].is_connected = false; // 默认未连接
    }

    printf("[WiFi List] WiFi items updated\n");
    // 按rssi从高到低排序
    for (uint32_t i = 0; i < count; i++) {
        for (uint32_t j = i + 1; j < count; j++) {
            if (wifi_manager.wifi_items[j].rssi > wifi_manager.wifi_items[i].rssi) {
                wifi_item_info_t tmp = wifi_manager.wifi_items[i];
                wifi_manager.wifi_items[i] = wifi_manager.wifi_items[j];
                wifi_manager.wifi_items[j] = tmp;
            }
        }
    }
    printf("[WiFi List] WiFi items end\n");
    // 创建WiFi项UI
    for (uint32_t i = 0; i < count; i++) {
        printf("[WiFi List] Creating UI for WiFi item %d\n", i);
        lv_obj_t* wifi_item = create_wifi_item(wifi_manager.wifi_list_cont, &wifi_manager.wifi_items[i]);
        if (!wifi_item) {
            printf("[WiFi List] Error: failed to create WiFi item %d\n", i);
            continue;
        }
    }

    wifi_list_apply_connecting_status();

    // 保存排序后的数据到持久化存储
    wifi_list_save_persistent_data(NULL, 0);  // 传NULL让函数使用已排序的wifi_manager.wifi_items

    printf("[WiFi List] Updated WiFi list with %d items\n", count);
}

/**
 * @brief 清空WiFi列表
 */
void wifi_list_clear(void)
{
    // 方案3：先清理UI对象（会自动移除事件回调），再释放数据内存
    if (wifi_manager.wifi_list_cont && lv_obj_is_valid(wifi_manager.wifi_list_cont)) {
        lv_obj_clean(wifi_manager.wifi_list_cont);
    } else if (wifi_manager.wifi_list_cont) {
        // 如果对象无效，将指针置为NULL
        printf("[WiFi List] WiFi list container is invalid, clearing pointer\n");
        wifi_manager.wifi_list_cont = NULL;
    }

    // 然后释放数据内存
    if (wifi_manager.wifi_items) {
        free(wifi_manager.wifi_items);
        wifi_manager.wifi_items = NULL;
    }

    wifi_manager.wifi_count = 0;
    wifi_manager.focused_obj = NULL;

    printf("[WiFi List] WiFi list cleared\n");
}

/**
 * @brief 设置WiFi项目点击回调函数
 */
void wifi_list_set_item_click_callback(wifi_item_click_cb_t callback)
{
    item_click_callback = callback;
}

/**
 * @brief 检查WiFi列表是否可见
 */
bool wifi_list_is_visible(void)
{
    return wifi_manager.is_visible;
}

/**
 * @brief 销毁WiFi列表
 */
void wifi_list_destroy(void)
{
    printf("[WiFi List] wifi_list_destroy() called\n");

    wifi_list_cleanup(true);

    printf("[WiFi List] WiFi list destroyed\n");
}

/**
 * @brief 创建单个WiFi项
 */
static lv_obj_t* create_wifi_item(lv_obj_t* parent, const wifi_item_info_t* wifi_info)
{
    if (!parent || !wifi_info) {
        printf("[WiFi List] Error: Invalid parameters for create_wifi_item\n");
        return NULL;
    }

    // 检查父对象是否有效
    if (!lv_obj_is_valid(parent)) {
        printf("[WiFi List] Error: parent object is invalid\n");
        return NULL;
    }

    printf("[WiFi List] Creating simple WiFi item for SSID: %s\n", wifi_info->ssid);

    // 创建WiFi项容器 - 简化版本
    lv_obj_t* item = lv_obj_create(parent);
    if (!item) {
        printf("[WiFi List] Error: Failed to create item container\n");
        return NULL;
    }
    
    // 设置基本尺寸
    lv_obj_set_size(item, WIFI_ITEM_WIDTH, WIFI_ITEM_HEIGHT);
    
    // 设置WiFi项样式 - 使用新的设计参数
    lv_obj_set_style_bg_color(item, lv_color_hex(0x5F93E8), LV_PART_MAIN);  // #5F93E8背景色
    lv_obj_set_style_bg_opa(item, 255, LV_PART_MAIN);
    lv_obj_set_style_border_width(item, 0, LV_PART_MAIN);  // 移除边框
    lv_obj_set_style_radius(item, WIFI_ITEM_RADIUS, LV_PART_MAIN);  // 16px圆角
    lv_obj_set_style_pad_all(item, WIFI_ITEM_PADDING, LV_PART_MAIN);

    // 按压时的样式 - 稍微亮一些的蓝色
    lv_obj_set_style_bg_color(item, lv_color_hex(0x7FA8EB), LV_PART_MAIN | LV_STATE_PRESSED);

    // 移除flex布局，使用绝对定位
    lv_obj_clear_flag(item, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);

    // 创建SSID标签 - 左对齐
    lv_obj_t* ssid_label = lv_label_create(item);
    lv_label_set_text(ssid_label, wifi_info->ssid);
    // 在create_wifi_item函数中
    const lv_font_t* font_to_use = &lv_font_leelawadeeui_32;
    if (font_to_use == NULL || font_to_use->get_glyph_bitmap == NULL) {
        font_to_use = LV_FONT_DEFAULT;  // 使用默认字体
        printf("[WiFi List] Warning: Using default font instead of leelawadeeui_32\n");
    }
    lv_obj_set_style_text_font(ssid_label, font_to_use, LV_PART_MAIN);
    lv_obj_set_style_text_color(ssid_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);  // 白色字体
    lv_obj_set_pos(ssid_label, WIFI_TEXT_LEFT_MARGIN, WIFI_TEXT_TOP_MARGIN);  // 左边距24px，上边距18px

    // 创建信号强度图标 - 右对齐
    lv_obj_t* signal_icon = lv_img_create(item);
    lv_obj_set_size(signal_icon, WIFI_ICON_SIZE, WIFI_ICON_SIZE);  // 64x64

    printf("[WiFi List] Creating signal icon for SSID: %s\n", wifi_info->ssid);

    // 使用LVGL图片指针而不是ID
    const void* wifi_icon_res = &_new_slices_wlan_wifi1_alpha64x64;
    if (wifi_info->rssi >= -50) {
        wifi_icon_res = &_new_slices_wlan_wifi4_alpha64x64;
    } else if (wifi_info->rssi >= -60) {
        wifi_icon_res = &_new_slices_wlan_wifi3_alpha64x64;
    } else if (wifi_info->rssi >= -70) {
        wifi_icon_res = &_new_slices_wlan_wifi2_alpha64x64;
    } else {
        wifi_icon_res = &_new_slices_wlan_wifi1_alpha64x64;
    }
    if (!wifi_icon_res) {
        printf("[WiFi List] Error: wifi_icon_res is NULL!\n");
        return NULL;
    }
    lv_img_set_src(signal_icon, wifi_icon_res);
    lv_obj_set_style_bg_opa(signal_icon, 0, LV_PART_MAIN); // 图片背景透明
    lv_obj_set_style_radius(signal_icon, 8, LV_PART_MAIN);  // 增大圆角

    printf("[WiFi List]  dcq   Creating signal icon for SSID: %s\n", wifi_info->ssid);

    // 右对齐：右边距24px，上边距16px
    lv_obj_set_pos(signal_icon, WIFI_ITEM_WIDTH - WIFI_ICON_SIZE - WIFI_ICON_RIGHT_MARGIN, WIFI_ICON_TOP_MARGIN);
    
    // 创建连接状态标签 - 位于信号强度图标的左边
    lv_obj_t* status_label = lv_label_create(item);
    if (wifi_info->is_connected) {
        wifi_status_label_update(status_label, LANG_TEXT_WIFI_CONNECT_SUCCESS, lv_color_hex(0x00FF00));
    } else {
        wifi_status_label_clear(status_label, lv_color_hex(0xFF0000));
    }
    
    // 将状态标签放置在SSID标签下方，保持左对齐
    lv_obj_align_to(status_label, ssid_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 6);
    
    // 设置可点击
    lv_obj_add_flag(item, LV_OBJ_FLAG_CLICKABLE);
    
    // 添加事件处理 - 传递索引而不是指针，避免悬挂指针问题
    // 将wifi_info在数组中的索引作为用户数据传递
    uint32_t item_index = (uint32_t)(wifi_info - wifi_manager.wifi_items);
    lv_obj_add_event_cb(item, wifi_item_event_handler, LV_EVENT_ALL, (void*)(uintptr_t)item_index);
    
    // 设置状态标签的用户数据，用于后续更新
    lv_obj_set_user_data(status_label, (void*)encode_status_label_index(item_index));

    return item;
}

/**
 * @brief WiFi项事件处理函数
 */
static void wifi_item_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    
    // 获取索引并进行安全检查
    uint32_t item_index = (uint32_t)(uintptr_t)lv_event_get_user_data(e);
    
    // 安全检查：确保数据有效
    if (!wifi_manager.wifi_items || item_index >= wifi_manager.wifi_count) {
        printf("[WiFi List] Warning: Invalid item index %d or data unavailable\n", item_index);
        return;
    }
    
    wifi_item_info_t* wifi_info = &wifi_manager.wifi_items[item_index];

    switch (code) {
    case LV_EVENT_CLICKED:
        printf("[WiFi List] WiFi item clicked: %s\n", wifi_info->ssid);
        
        // 调用回调函数
        if (item_click_callback) {
            item_click_callback(wifi_info->ssid, wifi_info->rssi, wifi_info->auth_mode);
        }
        break;
        
    case LV_EVENT_FOCUSED:
        wifi_manager.focused_obj = target;
        // 设置焦点样式 - 更亮的蓝色
        lv_obj_set_style_bg_color(target, lv_color_hex(0x7FA8EB), LV_PART_MAIN);
        break;

    case LV_EVENT_DEFOCUSED:
        // 恢复默认样式 - 原来的蓝色
        lv_obj_set_style_bg_color(target, lv_color_hex(0x5F93E8), LV_PART_MAIN);
        break;

    default:
        break;
    }
}

/**
 * @brief WiFi列表滚动事件处理函数
 */
static void wifi_list_scroll_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    
    if (code == LV_EVENT_SCROLL) {
        // 确认滚动只发生在WiFi列表容器内部
        if (target == wifi_manager.wifi_list_cont) {
            // 只允许在WiFi列表容器内部滚动，阻止传播到其他对象
            lv_event_stop_processing(e);
            lv_event_stop_bubbling(e);
            
            // 获取当前滚动位置，确保滚动在合理范围内
            lv_coord_t scroll_x = lv_obj_get_scroll_x(wifi_manager.wifi_list_cont);
            lv_coord_t scroll_y = lv_obj_get_scroll_y(wifi_manager.wifi_list_cont);
            lv_coord_t scroll_top = lv_obj_get_scroll_top(wifi_manager.wifi_list_cont);
            lv_coord_t scroll_bottom = lv_obj_get_scroll_bottom(wifi_manager.wifi_list_cont);
            
            // 禁止左右滚动，强制回到X=0
            if (scroll_x != 0) {
                lv_obj_scroll_to_x(wifi_manager.wifi_list_cont, 0, LV_ANIM_OFF);
            }

            // 如果滚动超出边界，则限制在边界内
            if (scroll_y < 0) {
                lv_obj_scroll_to_y(wifi_manager.wifi_list_cont, 0, LV_ANIM_OFF);
            } else if (scroll_bottom < 0) {
                lv_obj_scroll_to_y(wifi_manager.wifi_list_cont, scroll_y + scroll_bottom, LV_ANIM_OFF);
            }
        }
    } else if (code == LV_EVENT_GESTURE) {
        if (target == wifi_manager.wifi_list_cont) {
            lv_indev_t * indev = lv_event_get_indev(e);
            if (indev) {
                lv_dir_t dir = lv_indev_get_gesture_dir(indev);
                if (dir & (LV_DIR_LEFT | LV_DIR_RIGHT)) {
                    lv_event_stop_processing(e);
                    lv_event_stop_bubbling(e);
                    lv_obj_scroll_to_x(wifi_manager.wifi_list_cont, 0, LV_ANIM_OFF);
                }
            }
        }
    }
}

/**
 * @brief 获取认证模式文本
 */
static const char* get_auth_mode_text(int auth_mode)
{
    switch (auth_mode) {
        case 0: return "开放";      // WIFI_AUTH_MODE_OPEN
        case 1: return "WEP";       // WIFI_AUTH_MODE_WEP
        case 2: return "WAPI";      // WIFI_AUTH_MODE_WAPI
        case 3: return "WPA";       // WIFI_AUTH_MODE_WPA
        case 4: return "WPA2";      // WIFI_AUTH_MODE_WPA2PSK
        case 5: return "WPA/WPA2";  // WIFI_AUTH_MODE_WPAWPA2PSK
        case 6: return "WPA3";      // WIFI_AUTH_MODE_WPA3SAE
        case 7: return "WPA2/WPA3"; // WIFI_AUTH_MODE_WPA2PSKWPA3SAE
        case 8: return "WPA3";      // WIFI_AUTH_MODE_WPA3H2E
        default: return "未知";
    }
}

/**
 * @brief 根据信号强度获取颜色
 */
static lv_color_t get_signal_color(int rssi)
{
    if (rssi >= -50) {
        return lv_color_hex(0x00AA00);  // 强信号 - 绿色
    } else if (rssi >= -70) {
        return lv_color_hex(0xFFAA00);  // 中等信号 - 橙色
    } else {
        return lv_color_hex(0xFF3300);  // 弱信号 - 红色
    }
}

/**
 * @brief 获取信号强度图标资源ID
 */
uint32_t wifi_list_get_signal_icon(int rssi)
{
    // 根据信号强度返回不同的图标资源ID
    // 这里需要根据实际的图片资源来设置
    if (rssi >= -50) {
        return 0; // GUI_RES_WIFI_SIGNAL_STRONG;
    } else if (rssi >= -70) {
        return 0; // GUI_RES_WIFI_SIGNAL_MEDIUM;
    } else {
        return 0; // GUI_RES_WIFI_SIGNAL_WEAK;
    }
}

/**
 * @brief 获取安全类型图标资源ID
 */
uint32_t wifi_list_get_security_icon(int auth_mode)
{
    // 根据认证模式返回安全图标
    if (auth_mode == 0) { // 开放网络
        return 0; // GUI_RES_WIFI_OPEN;
    } else {
        return 0; // GUI_RES_WIFI_SECURE;
    }
}

/**
 * @brief 更新指定SSID的连接状态
 */
static bool wifi_list_apply_connecting_status(void)
{
    if (!s_has_pending_connecting) {
        return false;
    }

    if (!wifi_manager.wifi_items || wifi_manager.wifi_count == 0) {
        return false;
    }

    if (!wifi_list_is_ui_context_ready()) {
        return false;
    }

    int target_index = -1;
    for (uint32_t i = 0; i < wifi_manager.wifi_count; i++) {
        if (strcmp(wifi_manager.wifi_items[i].ssid, s_pending_connecting_ssid) == 0) {
            target_index = (int)i;
            break;
        }
    }

    if (target_index < 0) {
        return false;
    }

    if (target_index != 0) {
        wifi_list_move_to_top(s_pending_connecting_ssid);
        return false;
    }

    uint32_t child_cnt = lv_obj_get_child_cnt(wifi_manager.wifi_list_cont);
    for (uint32_t j = 0; j < child_cnt; j++) {
        lv_obj_t* item = lv_obj_get_child(wifi_manager.wifi_list_cont, j);
        if (!item) {
            continue;
        }

        uint32_t item_child_cnt = lv_obj_get_child_cnt(item);
        for (uint32_t k = 0; k < item_child_cnt; k++) {
            lv_obj_t* child = lv_obj_get_child(item, k);
            if (!child) {
                continue;
            }

            if (lv_obj_check_type(child, &lv_label_class)) {
                uint32_t decoded_index = 0;
                if (decode_status_label_index(child, &decoded_index) && decoded_index == 0) {
                    wifi_status_label_update(child, LANG_TEXT_WIFI_CONNECTING, lv_color_hex(0xFFFF00));
                    s_has_pending_connecting = false;
                    printf("[WiFi List] Displayed connecting status for SSID: %s\n", s_pending_connecting_ssid);
                    return true;
                }
            }
        }
    }

    return false;
}

void wifi_list_update_connection_status(const char* ssid, bool is_connected)
{
    if (!ssid) {
        printf("[WiFi List] Warning: Cannot update connection status - ssid is NULL\n");
        return;
    }

    if (!wifi_manager.is_visible) {
        printf("[WiFi List] Skip status update for %s - list not visible\n", ssid);
        return;
    }

    if (!wifi_list_is_ui_context_ready()) {
        printf("[WiFi List] Skip status update for %s - UI context not ready\n", ssid);
        return;
    }

    if (!wifi_manager.wifi_items || wifi_manager.wifi_count == 0) {
        printf("[WiFi List] Warning: WiFi data not initialized, cannot update status for %s\n", ssid);
        return;
    }
    
    printf("[WiFi List] Updating connection status for SSID: %s, connected: %s\n", 
           ssid, is_connected ? "true" : "false");
    
    if (s_has_pending_connecting && strcmp(ssid, s_pending_connecting_ssid) == 0) {
        s_has_pending_connecting = false;
        s_pending_connecting_ssid[0] = '\0';
    }

    // 查找对应的WiFi项
    for (uint32_t i = 0; i < wifi_manager.wifi_count; i++) {
        if (strcmp(wifi_manager.wifi_items[i].ssid, ssid) == 0) {
            // 找到对应的WiFi项，更新数据结构中的状态
            wifi_manager.wifi_items[i].is_connected = is_connected;
            
            // 如果连接成功，将这个WiFi移动到列表顶部
            if (is_connected) {
                printf("[WiFi List] Connection successful - moving WiFi to top of list\n");
                wifi_list_move_to_top(ssid);
                return;  // 移动到顶部后UI已经重新创建，直接返回
            }
            
            // 查找对应的UI控件并更新状态标签
            // 遍历WiFi列表容器的子控件
            uint32_t child_cnt = lv_obj_get_child_cnt(wifi_manager.wifi_list_cont);
            for (uint32_t j = 0; j < child_cnt; j++) {
                lv_obj_t* item = lv_obj_get_child(wifi_manager.wifi_list_cont, j);
                if (!item) continue;
                
                // 遍历WiFi项的子控件，查找状态标签
                uint32_t item_child_cnt = lv_obj_get_child_cnt(item);
                for (uint32_t k = 0; k < item_child_cnt; k++) {
                    lv_obj_t* child = lv_obj_get_child(item, k);
                    if (!child) continue;
                    
                    // 检查是否是标签控件
                    if (lv_obj_check_type(child, &lv_label_class)) {
                        uint32_t child_index = 0;
                        if (decode_status_label_index(child, &child_index) && child_index == i) {
                            // 找到对应的状态标签，更新文本和颜色
                            if (is_connected) {
                                wifi_status_label_update(child, LANG_TEXT_WIFI_CONNECT_SUCCESS, lv_color_hex(0x00FF00));
                            } else {
                                wifi_status_label_update(child, LANG_TEXT_WIFI_CONNECT_FAIL, lv_color_hex(0xFF0000));
                            }
                            printf("[WiFi List] Updated status label for SSID: %s\n", ssid);
                            return;
                        }
                    }
                }
            }
            
            printf("[WiFi List] Warning: Status label not found for SSID: %s\n", ssid);
            return;
        }
    }
    
    printf("[WiFi List] WiFi item not found for SSID: %s\n", ssid);
}

bool wifi_list_show_connecting_status(const char* ssid)
{
    if (!ssid || strlen(ssid) == 0) {
        s_has_pending_connecting = false;
        s_pending_connecting_ssid[0] = '\0';
        return false;
    }

    strncpy(s_pending_connecting_ssid, ssid, sizeof(s_pending_connecting_ssid) - 1);
    s_pending_connecting_ssid[sizeof(s_pending_connecting_ssid) - 1] = '\0';
    s_has_pending_connecting = true;

    if (!wifi_list_apply_connecting_status()) {
        printf("[WiFi List] WiFi list not ready, pending connecting status for SSID: %s\n", s_pending_connecting_ssid);
        return false;
    }

    return true;
}

/**
 * @brief 保存当前WiFi列表数据 - 保存已排序的数据
 */
void wifi_list_save_persistent_data(struct wifi_scan_ssid_info* wifi_scan_results, uint32_t count)
{
    printf("[WiFi List] Saving persistent data with %d WiFi items\n", count);
    
    // 清除之前保存的数据
    wifi_list_clear_persistent_data();
    
    // 优先保存已排序的wifi_manager.wifi_items，如果没有则使用原始数据
    if (wifi_manager.wifi_items && wifi_manager.wifi_count > 0) {
        printf("[WiFi List] Saving sorted WiFi data from manager\n");
        
        // 分配内存保存WiFi信息
        persistent_data.saved_items = (wifi_item_info_t*)malloc(wifi_manager.wifi_count * sizeof(wifi_item_info_t));
        if (!persistent_data.saved_items) {
            printf("[WiFi List] Error: Failed to allocate memory for persistent data\n");
            return;
        }
        
        // 直接复制已排序的数据
        memcpy(persistent_data.saved_items, wifi_manager.wifi_items, wifi_manager.wifi_count * sizeof(wifi_item_info_t));
        persistent_data.saved_count = wifi_manager.wifi_count;
        persistent_data.has_saved_data = true;
        
        printf("[WiFi List] Successfully saved %d sorted WiFi items to persistent data\n", wifi_manager.wifi_count);
        return;
    }
    
    // 如果没有管理器数据，则处理原始扫描结果
    if (!wifi_scan_results || count == 0) {
        printf("[WiFi List] No data to save\n");
        return;
    }
    
    // 添加数量限制，防止内存问题
    if (count > 50) {
        printf("[WiFi List] Warning: Too many WiFi networks (%d), limiting to 50\n", count);
        count = 50;
    }
    
    // 分配内存保存WiFi信息
    persistent_data.saved_items = (wifi_item_info_t*)malloc(count * sizeof(wifi_item_info_t));
    if (!persistent_data.saved_items) {
        printf("[WiFi List] Error: Failed to allocate memory for persistent data\n");
        return;
    }
    
    // 转换并保存WiFi信息
    for (uint32_t i = 0; i < count; i++) {
        strncpy(persistent_data.saved_items[i].ssid, wifi_scan_results[i].ssid, 32);
        persistent_data.saved_items[i].ssid[32] = '\0';
        persistent_data.saved_items[i].rssi = wifi_scan_results[i].rssi;
        persistent_data.saved_items[i].snr = wifi_scan_results[i].snr;
        persistent_data.saved_items[i].channel_number = wifi_scan_results[i].channel_number;
        persistent_data.saved_items[i].auth_mode = wifi_scan_results[i].auth_mode;
        persistent_data.saved_items[i].is_connected = false; // 默认未连接
    }
    
    // 对保存的数据进行排序（按rssi从高到低）
    for (uint32_t i = 0; i < count; i++) {
        for (uint32_t j = i + 1; j < count; j++) {
            if (persistent_data.saved_items[j].rssi > persistent_data.saved_items[i].rssi) {
                wifi_item_info_t tmp = persistent_data.saved_items[i];
                persistent_data.saved_items[i] = persistent_data.saved_items[j];
                persistent_data.saved_items[j] = tmp;
            }
        }
    }
    
    persistent_data.saved_count = count;
    persistent_data.has_saved_data = true;
    
    printf("[WiFi List] Successfully saved and sorted %d WiFi items to persistent data\n", count);
}

/**
 * @brief 恢复保存的WiFi列表数据
 */
bool wifi_list_restore_persistent_data(void)
{
    printf("[WiFi List] Attempting to restore persistent data\n");
    
    if (!persistent_data.has_saved_data || !persistent_data.saved_items || persistent_data.saved_count == 0) {
        printf("[WiFi List] No persistent data to restore\n");
        return false;
    }
    
    // 检查WiFi管理器是否已初始化
    if (!wifi_manager.parent_screen) {
        printf("[WiFi List] Error: WiFi manager not initialized, cannot restore\n");
        return false;
    }
    
    // 确保WiFi列表容器存在
    if (!wifi_manager.wifi_list_cont || !lv_obj_is_valid(wifi_manager.wifi_list_cont)) {
        printf("[WiFi List] WiFi list container not available, creating with default position\n");
        wifi_list_show(WIFI_LIST_POS_X, WIFI_LIST_POS_Y, WIFI_LIST_WIDTH, WIFI_LIST_HEIGHT);
        
        if (!wifi_manager.wifi_list_cont) {
            printf("[WiFi List] Error: Failed to create WiFi list container\n");
            return false;
        }
    }
    
    // 清空现有内容
    wifi_list_clear();
    
    // 分配内存存储WiFi信息
    wifi_manager.wifi_items = (wifi_item_info_t*)malloc(persistent_data.saved_count * sizeof(wifi_item_info_t));
    if (!wifi_manager.wifi_items) {
        printf("[WiFi List] Error: Failed to allocate memory for WiFi items\n");
        return false;
    }
    
    wifi_manager.wifi_count = persistent_data.saved_count;
    
    // 复制保存的WiFi信息
    memcpy(wifi_manager.wifi_items, persistent_data.saved_items, persistent_data.saved_count * sizeof(wifi_item_info_t));
    
    // 创建WiFi项UI
    for (uint32_t i = 0; i < persistent_data.saved_count; i++) {
        printf("[WiFi List] Creating UI for restored WiFi item %d: %s\n", i, wifi_manager.wifi_items[i].ssid);
        lv_obj_t* wifi_item = create_wifi_item(wifi_manager.wifi_list_cont, &wifi_manager.wifi_items[i]);
        if (!wifi_item) {
            printf("[WiFi List] Error: Failed to create WiFi item %d\n", i);
            continue;
        }
    }

    wifi_list_apply_connecting_status();
    
    printf("[WiFi List] Successfully restored %d WiFi items from persistent data\n", persistent_data.saved_count);
    return true;
}

/**
 * @brief 清除保存的WiFi列表数据
 */
void wifi_list_clear_persistent_data(void)
{
    if (persistent_data.saved_items) {
        free(persistent_data.saved_items);
        persistent_data.saved_items = NULL;
    }
    
    persistent_data.saved_count = 0;
    persistent_data.has_saved_data = false;
    
    printf("[WiFi List] Persistent data cleared\n");
}

/**
 * @brief 检查是否有保存的WiFi列表数据
 */
bool wifi_list_has_persistent_data(void)
{
    return persistent_data.has_saved_data && persistent_data.saved_items && persistent_data.saved_count > 0;
}

/**
 * @brief 将指定SSID的WiFi移动到列表顶部
 */
void wifi_list_move_to_top(const char* ssid)
{
    if (!ssid || !wifi_manager.wifi_items || wifi_manager.wifi_count == 0) {
        printf("[WiFi List] Cannot move to top - invalid parameters\n");
        return;
    }
    
    printf("[WiFi List] Moving WiFi '%s' to top of list\n", ssid);
    
    // 查找要移动的WiFi项的索引
    int target_index = -1;
    for (uint32_t i = 0; i < wifi_manager.wifi_count; i++) {
        if (strcmp(wifi_manager.wifi_items[i].ssid, ssid) == 0) {
            target_index = i;
            break;
        }
    }
    
    if (target_index == -1) {
        printf("[WiFi List] WiFi '%s' not found in list\n", ssid);
        return;
    }
    
    // 保存要移动的WiFi项
    wifi_item_info_t target_item = wifi_manager.wifi_items[target_index];
    
    // 将其他项目向后移动
    for (int i = target_index; i > 0; i--) {
        wifi_manager.wifi_items[i] = wifi_manager.wifi_items[i - 1];
    }
    
    // 将目标项放到第一位
    wifi_manager.wifi_items[0] = target_item;
    // 确保移动到顶部的WiFi项连接状态为true
    //wifi_manager.wifi_items[0].is_connected = true;
    printf("[WiFi List] Successfully moved WiFi '%s' to top of list\n", ssid);
    
    // 同时更新持久化数据中的顺序
    if (persistent_data.has_saved_data && persistent_data.saved_items && persistent_data.saved_count > 0) {
        // 查找持久化数据中对应的WiFi项
        int persistent_target_index = -1;
        for (uint32_t i = 0; i < persistent_data.saved_count; i++) {
            if (strcmp(persistent_data.saved_items[i].ssid, ssid) == 0) {
                persistent_target_index = i;
                break;
            }
        }
        
        if (persistent_target_index != -1 && persistent_target_index != 0) {
            // 保存要移动的WiFi项
            wifi_item_info_t persistent_target_item = persistent_data.saved_items[persistent_target_index];
            
            // 将其他项目向后移动
            for (int i = persistent_target_index; i > 0; i--) {
                persistent_data.saved_items[i] = persistent_data.saved_items[i - 1];
            }
            
            // 将目标项放到第一位
            persistent_data.saved_items[0] = persistent_target_item;
            
            printf("[WiFi List] Also updated persistent data order\n");
        }
    }
    
    // 重新创建UI以反映新的顺序
    if (wifi_manager.wifi_list_cont && lv_obj_is_valid(wifi_manager.wifi_list_cont)) {
        printf("[WiFi List] Recreating UI to reflect new order\n");
        
        // 清理现有的UI
        lv_obj_clean(wifi_manager.wifi_list_cont);
        
        // 重新创建WiFi项UI
        for (uint32_t i = 0; i < wifi_manager.wifi_count; i++) {
            lv_obj_t* wifi_item = create_wifi_item(wifi_manager.wifi_list_cont, &wifi_manager.wifi_items[i]);
            if (!wifi_item) {
                printf("[WiFi List] Error: Failed to recreate WiFi item %d\n", i);
                continue;
            }
        }
        
        printf("[WiFi List] UI recreated with new order\n");
    }
}

static void wifi_list_cleanup(bool detach_parent)
{
    if (wifi_manager.wifi_list_cont) {
        if (lv_obj_is_valid(wifi_manager.wifi_list_cont)) {
            lv_obj_del(wifi_manager.wifi_list_cont);
        }
        wifi_manager.wifi_list_cont = NULL;
    }

    if (wifi_manager.wifi_items) {
        free(wifi_manager.wifi_items);
        wifi_manager.wifi_items = NULL;
    }

    wifi_manager.wifi_count = 0;
    wifi_manager.is_visible = false;
    wifi_manager.focused_obj = NULL;

    s_has_pending_connecting = false;
    s_pending_connecting_ssid[0] = '\0';

    if (detach_parent) {
        wifi_manager.parent_screen = NULL;
    }
}

bool wifi_list_is_screen_active(void)
{
    if (!wifi_manager.parent_screen) {
        return false;
    }

    if (!lv_obj_is_valid(wifi_manager.parent_screen)) {
        wifi_manager.parent_screen = NULL;
        wifi_manager.is_visible = false;
        return false;
    }

    lv_obj_t *active_screen = lv_scr_act();
    lv_obj_t *parent_screen = lv_obj_get_screen(wifi_manager.parent_screen);

    return active_screen == parent_screen;
}
#endif
