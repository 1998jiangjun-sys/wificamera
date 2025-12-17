#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
#ifndef __UI_WIFI_LIST_H_
#define __UI_WIFI_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "custom.h"
#include "lvgl.h"

// 前向声明WiFi扫描结构体（避免循环包含）
struct wifi_scan_ssid_info;

// WiFi列表布局参数 (供外部使用)
#define WIFI_LIST_POS_X  16   // WiFi列表X位置
#define WIFI_LIST_POS_Y  304  // WiFi列表Y位置
#define WIFI_LIST_WIDTH  608  // WiFi列表宽度
#define WIFI_LIST_HEIGHT 350  // WiFi列表高度

// WiFi信息结构体
typedef struct {
    char ssid[33];           // SSID名称
    int rssi;                // 信号强度
    int snr;                 // 信噪比
    int channel_number;      // 频道号
    int auth_mode;           // 认证模式
    bool is_connected;       // 是否已连接
} wifi_item_info_t;

// WiFi列表管理结构体
typedef struct {
    lv_obj_t* wifi_list_cont;      // WiFi列表容器
    lv_obj_t* parent_screen;       // 父屏幕对象
    wifi_item_info_t* wifi_items;  // WiFi项目数组
    uint32_t wifi_count;           // WiFi数量
    bool is_visible;               // 是否可见
    lv_obj_t* focused_obj;         // 当前高亮对象
} wifi_list_manager_t;

// WiFi列表事件回调函数类型
typedef void (*wifi_item_click_cb_t)(const char* ssid, int rssi, int auth_mode);

// 函数声明
/**
 * @brief 初始化WiFi列表组件
 * @param parent 父屏幕对象
 * @return true 成功，false 失败
 */
bool wifi_list_init(lv_obj_t* parent);

/**
 * @brief 显示WiFi列表
 * @param x X坐标
 * @param y Y坐标
 * @param width 宽度
 * @param height 高度
 */
void wifi_list_show(lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height);

/**
 * @brief 隐藏WiFi列表
 */
void wifi_list_hide(void);

/**
 * @brief 更新WiFi列表数据
 * @param wifi_scan_results WiFi扫描结果数组
 * @param count WiFi数量
 */
void wifi_list_update_data(struct wifi_scan_ssid_info* wifi_scan_results, uint32_t count);

/**
 * @brief 清空WiFi列表
 */
void wifi_list_clear(void);

/**
 * @brief 设置WiFi项目点击回调函数
 * @param callback 回调函数
 */
void wifi_list_set_item_click_callback(wifi_item_click_cb_t callback);

/**
 * @brief 检查WiFi列表是否可见
 * @return true 可见，false 不可见
 */
bool wifi_list_is_visible(void);

/**
 * @brief 判断WiFi列表是否处于可接受异步更新的状态（线程安全）
 */
bool wifi_list_can_async_update(void);

/**
 * @brief 判断WiFi搜索界面是否仍然处于活动状态
 * @return true 界面仍是当前活动屏幕，可以安全更新UI；false 不在当前屏幕或已销毁
 */
bool wifi_list_is_screen_active(void);

/**
 * @brief 销毁WiFi列表
 */
void wifi_list_destroy(void);

/**
 * @brief 获取信号强度图标资源ID
 * @param rssi 信号强度值
 * @return 图标资源ID
 */
uint32_t wifi_list_get_signal_icon(int rssi);

/**
 * @brief 获取安全类型图标资源ID  
 * @param auth_mode 认证模式
 * @return 图标资源ID
 */
uint32_t wifi_list_get_security_icon(int auth_mode);

/**
 * @brief 更新指定SSID的连接状态
 * @param ssid WiFi网络名称
 * @param is_connected 连接状态（true=连接成功，false=连接失败）
 */
void wifi_list_update_connection_status(const char* ssid, bool is_connected);

/**
 * @brief 在WiFi列表中显示指定SSID的“连接中”状态
 * @param ssid WiFi网络名称
 */
bool wifi_list_show_connecting_status(const char* ssid);

/**
 * @brief 保存当前WiFi列表数据
 * @param wifi_scan_results WiFi扫描结果数组
 * @param count WiFi数量
 */
void wifi_list_save_persistent_data(struct wifi_scan_ssid_info* wifi_scan_results, uint32_t count);

/**
 * @brief 恢复保存的WiFi列表数据
 * @return true 成功恢复数据，false 没有保存的数据
 */
bool wifi_list_restore_persistent_data(void);

/**
 * @brief 清除保存的WiFi列表数据
 */
void wifi_list_clear_persistent_data(void);

/**
 * @brief 检查是否有保存的WiFi列表数据
 * @return true 有保存的数据，false 没有保存的数据
 */
bool wifi_list_has_persistent_data(void);

/**
 * @brief 将指定SSID的WiFi移动到列表顶部
 * @param ssid WiFi网络名称
 */
void wifi_list_move_to_top(const char* ssid);

#ifdef __cplusplus
}
#endif

#endif // __UI_WIFI_LIST_H_
#endif
