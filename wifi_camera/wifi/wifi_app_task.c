#include "wifi/wifi_connect.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "os/os_api.h"
#include "system/init.h"
#include "lwip.h"
#include "dhcp_srv/dhcp_srv.h"
#include "lwip/dns.h"
#include "device/device.h"
#include "system/app_core.h"
#include "server/server_core.h"
#include "action.h"
#include "system/timer.h"
#include "asm/debug.h"
#include "app_config.h"
#include "http/http_cli.h"
#include "system/timer.h"
#include "dev_desc.h"
#include "http/http_server.h"
#include "server/ctp_server.h"
#include "server/net_server.h"
#include "video_rt_tcp.h"
#include "ftpserver/stupid-ftpd.h"
#include "streaming_media_server/fenice_config.h"
#include "syscfg/syscfg_id.h"
#include "product_main.h"
#include "event/net_event.h"

#if TCFG_WIFI_ENABLE
// 添加LVGL异步调用支持，用于线程安全的UI更新
#include "lvgl.h"
#include <stdbool.h>
#include <string.h>

#ifdef CONFIG_NET_ENABLE
#define WIFI_APP_TASK_NAME "wifi_app_task"

// WiFi扫描结果异步更新数据结构
typedef struct {
    struct wifi_scan_ssid_info* scan_results;
    uint32_t count;
    u8 is_user_requested;
} wifi_scan_async_data_t;

// WiFi连接状态更新数据结构
typedef struct {
    char ssid[33];
    bool is_connected;
} wifi_status_update_data_t;

static char save_ssid_flag;
static volatile bool s_wifi_scan_ready = false;

static u16 s_wifi_user_scan_timer_id = 0;

static void wifi_user_scan_schedule_internal(u32 delay_ms);
static void wifi_user_scan_timeout_cb(void *priv);
bool wifi_is_scan_ready(void);


static void wifi_user_scan_timeout_cb(void *priv)
{
    (void)priv;

    s_wifi_user_scan_timer_id = 0;

    if (!wifi_is_scan_ready()) {
        printf("[WiFi Scan] Stack not ready, retry later\n");
        wifi_user_scan_schedule_internal(200);
        return;
    }

    printf("=== 开始WiFi搜索 ===\n");

    struct wifi_mode_info mode_info = {0};
    mode_info.mode = NONE_MODE;
    wifi_get_mode_cur_info(&mode_info);
    printf("[WiFi Scan] 当前WiFi模式: %d\n", mode_info.mode);

    int scan_ret = wifi_scan_req();
    if (scan_ret != 0) {
        printf("[WiFi Scan] wifi_scan_req failed, ret=%d\n", scan_ret);
        return;
    }

    printf("[WiFi Scan] 请求已发出，等待 WIFI_EVENT_STA_SCAN_COMPLETED\n");
}

static void wifi_user_scan_schedule_internal(u32 delay_ms)
{
    if (s_wifi_user_scan_timer_id) {
        sys_timeout_del(s_wifi_user_scan_timer_id);
        s_wifi_user_scan_timer_id = 0;
    }

    if (delay_ms == 0) {
        wifi_user_scan_timeout_cb(NULL);
        return;
    }

    u16 id = sys_timeout_add_to_task(WIFI_APP_TASK_NAME, NULL, wifi_user_scan_timeout_cb, delay_ms);
    if (id == 0) {
        printf("[WiFi Scan] schedule failed, run immediately\n");
        wifi_user_scan_timeout_cb(NULL);
        return;
    }

    s_wifi_user_scan_timer_id = id;
}

void wifi_user_scan_request_async(u32 delay_ms)
{
    wifi_user_scan_schedule_internal(delay_ms);
}

void wifi_user_scan_cancel_async(void)
{
    if (s_wifi_user_scan_timer_id) {
        sys_timeout_del(s_wifi_user_scan_timer_id);
        s_wifi_user_scan_timer_id = 0;
    }
}

bool wifi_is_scan_ready(void)
{
    static enum WIFI_MODE s_last_logged_mode = NONE_MODE;

    if (!wifi_is_on()) {
        return false;
    }

    if (!s_wifi_scan_ready) {
        return false;
    }

    struct wifi_mode_info info = {0};
    info.mode = NONE_MODE;
    wifi_get_mode_cur_info(&info);

    if (info.mode != STA_MODE) {
        if (s_last_logged_mode != info.mode) {
            printf("[WiFi Ready] Waiting for STA mode, current=%d\n", info.mode);
            s_last_logged_mode = info.mode;
        }
        return false;
    }

    s_last_logged_mode = STA_MODE;
    return true;
}

int wifi_get_connection_signal_strength_level(void)
{
    if (!wifi_is_on()) {
        return 0;
    }

    enum wifi_sta_connect_state connect_state = wifi_get_sta_connect_state();
    bool wifi_connected = false;

    switch (connect_state) {
    case WIFI_STA_CONNECT_SUCC:
    case WIFI_STA_NETWORK_STACK_DHCP_SUCC:
    case WIFI_STA_IP_GOT_IPV6_SUCC:
        wifi_connected = true;
        break;
    default:
        break;
    }

    if (!wifi_connected) {
        return 0;
    }

    struct wifi_mode_info mode_info = {0};
    char ssid_buf[33] = {0};
    char pwd_buf[65] = {0};
    mode_info.mode = STA_MODE;
    mode_info.ssid = ssid_buf;
    mode_info.pwd = pwd_buf;
    wifi_get_mode_cur_info(&mode_info);

    if (!mode_info.ssid || mode_info.ssid[0] == '\0') {
        return 0;
    }

    char rssi = wifi_get_rssi();

    if (rssi >= -50) {
        return 4;
    }
    if (rssi >= -60) {
        return 3;
    }
    if (rssi >= -70) {
        return 2;
    }

    return 1;
}

void wifi_sta_enable_save_after_connect(void)
{
    save_ssid_flag = 1;
}

#ifdef CONFIG_STATIC_IPADDR_ENABLE
static u8 use_static_ipaddr_flag;
#endif

extern char get_MassProduction(void);
static void wifi_set_lan_setting_info(void);

// WiFi扫描结果异步UI更新回调函数 - 在LVGL主线程中安全执行
static void wifi_scan_async_ui_update_cb(void *user_data);

static void wifi_notify_lvgl_async(void)
{
    int msg[2];
    msg[0] = UI_MSG_TIMER_TIMEOUT;
    msg[1] = 0;

    int err = task_queue_post_event(LVGL_TASK_NAME, msg, (int)(sizeof(msg) / sizeof(msg[0])));
    if (err != 0) {
        printf("[WiFi Thread Safety] Warning: failed to wake LVGL task (err=%d)\n", err);
    }
}

// WiFi连接状态异步UI更新回调函数 - 在LVGL主线程中安全执行
static void wifi_status_async_ui_update_cb(void *user_data)
{
    wifi_status_update_data_t *update_data = (wifi_status_update_data_t *)user_data;
    if (!update_data) {
        printf("[WiFi Status] Error: Invalid update data\n");
        return;
    }
    
    printf("[WiFi Status] Async UI update: SSID=%s, connected=%s\n", 
           update_data->ssid, update_data->is_connected ? "true" : "false");
    
    // 调用WiFi列表更新函数
    extern bool wifi_list_can_async_update(void);
    if (!wifi_list_can_async_update()) {
        printf("[WiFi Status] UI not ready on LVGL thread, skip update for %s\n", update_data->ssid);
        free(update_data);
        return;
    }

    extern void wifi_list_update_connection_status(const char* ssid, bool is_connected);
    wifi_list_update_connection_status(update_data->ssid, update_data->is_connected);
    
    // 释放内存
    free(update_data);
}

static void wifi_schedule_status_update(const char *ssid, bool is_connected)
{
    extern bool wifi_list_can_async_update(void);

    if (!ssid || ssid[0] == '\0') {
        printf("[WiFi Status] Skip async update - invalid ssid\n");
        return;
    }

    if (!wifi_list_can_async_update()) {
        printf("[WiFi Status] UI not ready, skip async update (ssid=%s, connected=%s)\n",
               ssid, is_connected ? "true" : "false");
        return;
    }

    wifi_status_update_data_t *status_data = malloc(sizeof(wifi_status_update_data_t));
    if (!status_data) {
        printf("[WiFi Status] Error: failed to allocate status update data\n");
        return;
    }

    strncpy(status_data->ssid, ssid, sizeof(status_data->ssid) - 1);
    status_data->ssid[sizeof(status_data->ssid) - 1] = '\0';
    status_data->is_connected = is_connected;

    lv_res_t res = lv_async_call(wifi_status_async_ui_update_cb, status_data);
    if (res != LV_RES_OK) {
        printf("[WiFi Status] Error: lv_async_call failed for status update\n");
        free(status_data);
    } else {
        wifi_notify_lvgl_async();
    }
}

// WiFi扫描结果异步UI更新回调函数 - 在LVGL主线程中安全执行
static void wifi_scan_async_ui_update_cb(void *user_data)
{
    wifi_scan_async_data_t *async_data = (wifi_scan_async_data_t *)user_data;
    
    if (!async_data) {
        printf("[WiFi Async] Error: async_data is NULL\n");
        return;
    }
    
    printf("[WiFi Async] 在LVGL主线程中安全更新UI，网络数量: %d\n", async_data->count);
    
    // 声明外部函数
    extern void show_wifi_scan_results(struct wifi_scan_ssid_info* scan_results, uint32_t count);
    extern void wifi_list_save_persistent_data(struct wifi_scan_ssid_info* wifi_scan_results, uint32_t count);
    
    // 保存WiFi列表数据以备恢复使用
    if (async_data->scan_results && async_data->count > 0) {
        printf("[WiFi Async] 保存WiFi列表持久化数据\n");
        wifi_list_save_persistent_data(async_data->scan_results, async_data->count);
    }
    
    extern bool wifi_list_is_screen_active(void);
    if (!wifi_list_is_screen_active()) {
        printf("[WiFi Async] WiFi search screen not active, skip UI update drawing\n");
    } else {
        // 在LVGL主线程中安全调用UI更新函数
        show_wifi_scan_results(async_data->scan_results, async_data->count);
    }
    
    // 清理资源
    if (async_data->scan_results) {
        // 清理WiFi扫描结果缓存
        extern void wifi_clear_scan_result(void);
        wifi_clear_scan_result();
        
        free(async_data->scan_results);
        async_data->scan_results = NULL;
    }
    
    // 如果是用户手动扫描，重置扫描标志
    if (async_data->is_user_requested) {
        extern void reset_user_scan_flag(void);
        reset_user_scan_flag();
        printf("[WiFi Async] 用户扫描完成，已重置扫描标志\n");
    }
    
    // 释放异步数据结构
    free(async_data);
    
    printf("[WiFi Async] UI更新完成\n");
}

static struct server *ctp = NULL;
static const struct ctp_server_info server_info = {
    .ctp_vaild = true,
    .ctp_port = CTP_CTRL_PORT,
    .cdp_vaild = true,
    .cdp_port = CDP_CTRL_PORT,
    .k_alive_type = CTP_ALIVE,
    /*.k_alive_type = CDP_ALIVE,*/
};


void get_ap_wifi_info(char *ssid, char *pwd)
{
    struct wifi_mode_info info;
    info.mode = AP_MODE;
    wifi_get_mode_cur_info(&info);
//    printf("ap get ssid:%s   pwd:%s  \n", info.ssid, info.pwd);
    memcpy(ssid, info.ssid, strlen(info.ssid));
    memcpy(pwd, info.pwd, strlen(info.pwd));
    printf("get ssid:%s   pwd:%s  \n", ssid, pwd);
}

static void wifi_app_timer_func(void *p)
{
    if (wifi_is_on()) {
        /*stats_display(); //LWIP stats*/
#if 0
        printf("WIFI U= %d KB/s, D= %d KB/s\r\n", wifi_get_upload_rate() / 1024, wifi_get_download_rate() / 1024);

#ifndef CONFIG_WIFI_STA_MODE
        for (int i = 0; i < 8; i++) {
            char *rssi;
            u8 *evm, *mac;
            if (wifi_get_sta_entry_rssi(i, &rssi, &evm, &mac)) {
                break;
            }
            if (*rssi) {
                printf("MAC[%x:%x:%x:%x:%x:%x],RSSI=%d,EVM=%d \r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], *rssi, *evm);
            }
        }
#endif
        malloc_stats();
#endif
    }
}


static void wifi_sta_to_ap_mode_change(void)//用在STA模式密码不对或者找不到SSID，自动切换AP模式
{
    u8 mac_addr[6];
    char ssid[64];
    struct wifi_mode_info info;
    info.mode = AP_MODE;
    wifi_get_mode_cur_info(&info);
    if (!strcmp("", info.ssid)) {
        wifi_get_mac(mac_addr);
        sprintf((char *)ssid, AP_WIFI_CAM_PREFIX"%02x%02x%02x%02x%02x%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        info.ssid = ssid;
        info.pwd = AP_WIFI_CAM_WIFI_PWD;
    }

    wifi_set_lan_setting_info(); //STA转AP模式,需要重新配置一下IP信息和DHCP池起始分配地址
    wifi_enter_ap_mode(info.ssid, info.pwd);
    wifi_store_mode_info(AP_MODE, info.ssid, info.pwd);
}

#ifdef CONFIG_STATIC_IPADDR_ENABLE
struct sta_ip_info {
    u8 ssid[33];
    u32 ip;
    u32 gw;
    u32 netmask;
    u32 dns;
    u8 gw_mac[6];
    u8 local_mac[6];
    u8 chanel;
};

static void wifi_set_sta_ip_info(void)
{
    struct sta_ip_info  sta_ip_info;
    syscfg_read(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info));

    struct lan_setting lan_setting_info = {

        .WIRELESS_IP_ADDR0  = (u8)(sta_ip_info.ip >> 0),
        .WIRELESS_IP_ADDR1  = (u8)(sta_ip_info.ip >> 8),
        .WIRELESS_IP_ADDR2  = (u8)(sta_ip_info.ip >> 16),
        .WIRELESS_IP_ADDR3  = (u8)(sta_ip_info.ip >> 24),

        .WIRELESS_NETMASK0  = (u8)(sta_ip_info.netmask >> 0),
        .WIRELESS_NETMASK1  = (u8)(sta_ip_info.netmask >> 8),
        .WIRELESS_NETMASK2  = (u8)(sta_ip_info.netmask >> 16),
        .WIRELESS_NETMASK3  = (u8)(sta_ip_info.netmask >> 24),

        .WIRELESS_GATEWAY0   = (u8)(sta_ip_info.gw >> 0),
        .WIRELESS_GATEWAY1   = (u8)(sta_ip_info.gw >> 8),
        .WIRELESS_GATEWAY2   = (u8)(sta_ip_info.gw >> 16),
        .WIRELESS_GATEWAY3   = (u8)(sta_ip_info.gw >> 24),
    };

    net_set_lan_info(&lan_setting_info);
}

static int compare_dhcp_ipaddr(void)
{
    use_static_ipaddr_flag = 0;

    int ret;
    u8 local_mac[6];
    u8 gw_mac[6];
    u8 sta_channel;
    struct sta_ip_info  sta_ip_info;
    struct netif_info netif_info;
    ret = syscfg_read(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info));

    if (ret < 0) {
        puts("compare_dhcp_ipaddr NO VM_STA_IPADDR_INDEX\r\n");
        return -1;
    }

    lwip_get_netif_info(1, &netif_info);

    struct wifi_mode_info info;
    info.mode = STA_MODE;
    wifi_get_mode_cur_info(&info);

    sta_channel = wifi_get_channel();
    wifi_get_bssid(gw_mac);
    wifi_get_mac(local_mac);

    if (!strcmp(info.ssid, sta_ip_info.ssid)
        && !memcmp(local_mac, sta_ip_info.local_mac, 6)
        && !memcmp(gw_mac, sta_ip_info.gw_mac, 6)
        /*&& sta_ip_info.gw==sta_ip_info.dns//如果路由器没接网线/没联网,每次连接都去重新获取DHCP*/
       ) {
        use_static_ipaddr_flag = 1;
        puts("compare_dhcp_ipaddr Match\r\n");
        return 0;
    }

    printf("compare_dhcp_ipaddr not Match!!! [%s][%s],[0x%x,0x%x][0x%x,0x%x],[0x%x] \r\n", info.ssid, sta_ip_info.ssid, local_mac[0], local_mac[5], sta_ip_info.local_mac[0], sta_ip_info.local_mac[5], sta_ip_info.dns);

    return -1;
}

static void store_dhcp_ipaddr(void)
{
    struct sta_ip_info  sta_ip_info = {0};
    u8 sta_channel;
    u8 local_mac[6];
    u8 gw_mac[6];

    if (use_static_ipaddr_flag) { //记忆IP匹配成功,不需要重新保存
        return;
    }

    struct netif_info netif_info;
    lwip_get_netif_info(1, &netif_info);

    struct wifi_mode_info info;
    info.mode = STA_MODE;
    wifi_get_mode_cur_info(&info);

    sta_channel = wifi_get_channel();
    wifi_get_mac(local_mac);
    wifi_get_bssid(gw_mac);

    strcpy(sta_ip_info.ssid, info.ssid);
    memcpy(sta_ip_info.gw_mac, gw_mac, 6);
    memcpy(sta_ip_info.local_mac, local_mac, 6);
    sta_ip_info.ip =  netif_info.ip;
    sta_ip_info.netmask =  netif_info.netmask;
    sta_ip_info.gw =  netif_info.gw;
    sta_ip_info.chanel = sta_channel;
    sta_ip_info.dns = *(u32 *)dns_getserver(0);

    syscfg_write(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info));

    puts("store_dhcp_ipaddr\r\n");
}

void dns_set_server(u32 *dnsserver)
{
    struct sta_ip_info  sta_ip_info;
    if (syscfg_read(VM_STA_IPADDR_INDEX, (char *) &sta_ip_info, sizeof(struct sta_ip_info)) < 0) {
        *dnsserver = 0;
    } else {
        *dnsserver = sta_ip_info.dns;
    }
}

#endif

static void wifi_set_lan_setting_info(void)
{
    struct lan_setting lan_setting_info = {

        .WIRELESS_IP_ADDR0  = 192,
        .WIRELESS_IP_ADDR1  = 168,
        .WIRELESS_IP_ADDR2  = 1,
        .WIRELESS_IP_ADDR3  = 1,

        .WIRELESS_NETMASK0  = 255,
        .WIRELESS_NETMASK1  = 255,
        .WIRELESS_NETMASK2  = 255,
        .WIRELESS_NETMASK3  = 0,

        .WIRELESS_GATEWAY0  = 192,
        .WIRELESS_GATEWAY1  = 168,
        .WIRELESS_GATEWAY2  = 1,
        .WIRELESS_GATEWAY3  = 1,

        .SERVER_IPADDR1  = 192,
        .SERVER_IPADDR2  = 168,
        .SERVER_IPADDR3  = 1,
        .SERVER_IPADDR4  = 1,

        .CLIENT_IPADDR1  = 192,
        .CLIENT_IPADDR2  = 168,
        .CLIENT_IPADDR3  = 1,
        .CLIENT_IPADDR4  = 2,

        .SUB_NET_MASK1   = 255,
        .SUB_NET_MASK2   = 255,
        .SUB_NET_MASK3   = 255,
        .SUB_NET_MASK4   = 0,
    };
    net_set_lan_info(&lan_setting_info);
}

static void wifi_sta_save_ssid(void)
{
    if (save_ssid_flag) {
        save_ssid_flag = 0;

        struct wifi_mode_info info;
        info.mode = STA_MODE;
        wifi_get_mode_cur_info(&info);
        wifi_store_mode_info(STA_MODE, info.ssid, info.pwd);
    }
}
static int wifi_connect_sta_mac(int offset, u8 *mac, int len, int index)//存储、查找、删除连接的STA设备的mac
{
    static u8 store_mac[6 * 5] = {0};
    int i;
    offset = offset < sizeof(store_mac) ? offset : sizeof(store_mac);
    for (i = offset; i < sizeof(store_mac); i += 6) { //只支持6个mac地址
        if (index == 0) { //写入
            if (store_mac[i] == 0 || !memcmp(&store_mac[i], mac, len)) {
                memcpy(&store_mac[i], mac, len);
                break;
            }
        } else if (index == 1) { //读取
            if (store_mac[i] != 0) {
                memcpy(mac, &store_mac[i], len);
                return i + len;
            }
        } else if (index == 2) { //清空
            if (!memcmp(&store_mac[i], mac, len)) {
                memset(&store_mac[i], 0, len);
                break;
            }
        }
    }
    return 0;
}
void wifi_all_sta_discon(void)//AP模式下主动断开所有MAC的STA
{
    int i = 0;
    u8 cnt = 0;
    u8 mac[6];
    do {
        i = wifi_connect_sta_mac(i, &mac, 6, 1);
        if (i) {
            wifi_disconnect_station(&mac, 8);
            printf("Disconned Sta Mac : %02x:%02x:%02x:%02x:%02x:%02x:\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        }
    } while (i != 0);
}
static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event)
{
    int ret = 0;
    struct net_event net = {0};
    switch (event) {

    case WIFI_EVENT_MODULE_INIT:

        wifi_set_smp_cfg_timeout(30);       //配置MONITOR模式超时后事件回调通知时间

        struct wifi_store_info wifi_default_mode_parm;
        memset(&wifi_default_mode_parm, 0, sizeof(struct wifi_store_info));

#if (defined CONFIG_WIFI_STA_MODE)
        wifi_set_sta_connect_timeout(30);   //配置STA模式连接超时后事件回调通知时间
        wifi_default_mode_parm.mode = STA_MODE;
        if (wifi_default_mode_parm.mode == AP_MODE || wifi_default_mode_parm.mode == STA_MODE) {
            strncpy((char *)wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE],
                    (const char *)STA_WIFI_SSID,
                    sizeof(wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE]) - 1);
            strncpy((char *)wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE],
                    (const char *)STA_WIFI_PWD,
                    sizeof(wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE]) - 1);
        }
        wifi_default_mode_parm.connect_best_network = 0;
#else
        u8 mac_addr[6];
        char ssid[64];
        int init_net_device_mac_addr(char *macaddr, char ap_mode); //如果AP模式需要配置SSID和MAC地址相关,需要在这里先产生MAC地址,否则就不用
        wifi_set_lan_setting_info();
        init_net_device_mac_addr((char *)mac_addr, 1);

        sprintf((char *)ssid, AP_WIFI_CAM_PREFIX"%02x%02x%02x%02x%02x%02x",
                mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);

        wifi_default_mode_parm.mode = AP_MODE;
        if (wifi_default_mode_parm.mode == AP_MODE || wifi_default_mode_parm.mode == STA_MODE) {
            strncpy((char *)wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE],
                    (const char *)ssid,
                    sizeof(wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE]) - 1);
            strncpy((char *)wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE],
                    (const char *)AP_WIFI_CAM_WIFI_PWD,
                    sizeof(wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE]) - 1);
        }
#endif

#ifndef CONFIG_DOUBLE_BANK_ENABLE
        wifi_set_default_mode(&wifi_default_mode_parm, 0, 1); //配置STA模式情况下,把默>    认配置SSID也存储起来,以后即使保存过其他SSID,也不会覆盖丢失,使用连接最优信号SSID策略的情况下可以匹配连接
        /* wifi_set_default_mode(&wifi_default_mode_parm, 1, 1); //配置STA模式情况下,把默>    认配置SSID也存储起来,以后即使保存过其他SSID,也不会覆盖丢失,使用连接最优信号SSID策略的情况下可以匹配连接 */
#else
        wifi_set_default_mode(&wifi_default_mode_parm, 0, wifi_default_mode_parm.mode == STA_MODE); //配置STA模式情况下,把默>    认配置SSID也存储起来,以后即使保存过其他SSID,也不会覆盖丢失,使用连接最优信号SSID策略的情况下可以匹配连接
#endif
        break;

    case WIFI_EVENT_MODULE_START:
        s_wifi_scan_ready = false;
        if (!get_MassProduction()) {



            u32  tx_rate_control_tab = // 不需要哪个速率就删除掉,可以动态设定
                0
                | BIT(0) //0:CCK 1M
                | BIT(1) //1:CCK 2M
                | BIT(2) //2:CCK 5.5M
                | BIT(3) //3:OFDM 6M
                | BIT(4) //4:MCS0/7.2M
                | BIT(5) //5:OFDM 9M
                | BIT(6) //6:CCK 11M
                | BIT(7) //7:OFDM 12M
                | BIT(8) //8:MCS1/14.4M
                | BIT(9) //9:OFDM 18M
                | BIT(10) //10:MCS2/21.7M
                | BIT(11) //11:OFDM 24M
                | BIT(12) //12:MCS3/28.9M
                | BIT(13) //13:OFDM 36M
                | BIT(14) //14:MCS4/43.3M
                | BIT(15) //15:OFDM 48M
                | BIT(16) //16:OFDM 54M
                | BIT(17) //17:MCS5/57.8M
                | BIT(18) //18:MCS6/65.0M
                | BIT(19) //19:MCS7/72.2M
                ;
            wifi_set_tx_rate_control_tab(tx_rate_control_tab);

        }
#if 0
        wifi_set_pwr(0);
#endif
        break;
    case WIFI_EVENT_MODULE_STOP:
        s_wifi_scan_ready = false;
        puts("|network_user_callback->WIFI_EVENT_MODULE_STOP\n");
        break;

    case WIFI_EVENT_AP_START:
        s_wifi_scan_ready = false;
        printf("|network_user_callback->WIFI_EVENT_AP_START,CH=%d\n", wifi_get_channel());
        //wifi_rxfilter_cfg(7); //过滤广播+多播+not_my_bssid
        break;
    case WIFI_EVENT_AP_STOP:
        s_wifi_scan_ready = false;
        puts("|network_user_callback->WIFI_EVENT_AP_STOP\n");
        break;

    case WIFI_EVENT_STA_START:
        s_wifi_scan_ready = true;
        puts("|network_user_callback->WIFI_EVENT_STA_START\n");
        break;
    case WIFI_EVENT_MODULE_START_ERR:
        puts("|network_user_callback->WIFI_EVENT_MODULE_START_ERR\n");
        break;
    case WIFI_EVENT_STA_STOP:
        s_wifi_scan_ready = false;
        puts("|network_user_callback->WIFI_EVENT_STA_STOP\n");
        break;
    case WIFI_EVENT_STA_DISCONNECT:
        puts("|network_user_callback->WIFI_STA_DISCONNECT\n");
        net.event = NET_EVENT_DISCONNECTED;
        net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;
    case WIFI_EVENT_STA_SCAN_COMPLETED:
        puts("|network_user_callback->WIFI_STA_SCAN_COMPLETED\n");
        // 检查是否为用户手动扫描请求
        extern u8 is_user_scan_requested(void);
        
        if (is_user_scan_requested()) {
            printf("=== WiFi扫描完成，准备线程安全更新UI ===\n");
            
            // 获取扫描结果
            u32 ssid_count = 0;
            struct wifi_scan_ssid_info *scan_results = wifi_get_scan_result(&ssid_count);
            
            // 打印扫描结果到控制台（这部分可以在任何线程中安全执行）
            if (!scan_results) {
                printf("获取WiFi扫描结果失败\n");
            } else {
                printf("发现 %d 个WiFi网络：\n", ssid_count);
                for (u32 i = 0; i < ssid_count; i++) {
                    printf("  [%d] SSID: %s\n", i + 1, scan_results[i].ssid);
                    printf("      信号强度: %d dBm\n", scan_results[i].rssi);
                    printf("      信噪比: %d\n", scan_results[i].snr);
                    printf("      频道: %d\n", scan_results[i].channel_number);
                    printf("      ----------------\n");
                }
            }
            
            // 创建异步数据结构
            wifi_scan_async_data_t *async_data = (wifi_scan_async_data_t *)malloc(sizeof(wifi_scan_async_data_t));
            if (!async_data) {
                printf("[WiFi Thread Safety] Error: 无法分配异步数据内存\n");
                // 清理扫描结果
                extern void wifi_clear_scan_result(void);
                wifi_clear_scan_result();
                if (scan_results) {
                    free(scan_results);
                }
                return 0;
            }
            
            // 准备异步数据
            async_data->scan_results = scan_results;
            async_data->count = ssid_count;
            async_data->is_user_requested = 1;
            
            // 使用LVGL异步调用来安全更新UI
            printf("[WiFi Thread Safety] 使用 lv_async_call 调度UI更新\n");
            lv_res_t res = lv_async_call(wifi_scan_async_ui_update_cb, async_data);
            
            if (res != LV_RES_OK) {
                printf("[WiFi Thread Safety] Error: lv_async_call 失败，回退到直接清理\n");
                // 如果异步调用失败，直接清理资源
                extern void wifi_clear_scan_result(void);
                extern void reset_user_scan_flag(void);
                wifi_clear_scan_result();
                if (scan_results) {
                    free(scan_results);
                }
                reset_user_scan_flag();
                free(async_data);
            } else {
                printf("[WiFi Thread Safety] lv_async_call 调度成功，UI将在LVGL主线程中更新\n");
                wifi_notify_lvgl_async();
            }
            
            printf("=== WiFi扫描线程安全处理完成 ===\n");
        }
        break;
    case WIFI_EVENT_STA_CONNECT_SUCC:
        printf("|network_user_callback->WIFI_STA_CONNECT_SUCC,CH=%d\r\n", wifi_get_channel());
        
        // 更新WiFi列表中的连接状态为成功
        {
            struct wifi_mode_info info;
            info.mode = STA_MODE;
            wifi_get_mode_cur_info(&info);
            if (info.ssid) {
                printf("[WiFi Status] 连接成功，更新UI状态: SSID=%s\n", info.ssid);
                wifi_schedule_status_update(info.ssid, true);
            }
        }
        
#ifdef CONFIG_STATIC_IPADDR_ENABLE
        if (0 == compare_dhcp_ipaddr()) {
            wifi_set_sta_ip_info();
            ret = 1;
        }
#endif
        break;

    case WIFI_EVENT_MP_TEST_START:
        puts("|network_user_callback->WIFI_EVENT_MP_TEST_START\n");
        break;
    case WIFI_EVENT_MP_TEST_STOP:
        puts("|network_user_callback->WIFI_EVENT_MP_TEST_STOP\n");
        break;

    case WIFI_EVENT_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        puts("|network_user_callback->WIFI_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID\n");
        
        // 更新WiFi列表中的连接状态为失败
        {
            struct wifi_mode_info info;
            info.mode = STA_MODE;
            wifi_get_mode_stored_info(&info);
            if (info.ssid) {
                printf("[WiFi Status] 连接失败(未找到SSID)，更新UI状态: SSID=%s\n", info.ssid);
                wifi_schedule_status_update(info.ssid, false);
            }
        }
    net.event = NET_CONNECT_TIMEOUT_NOT_FOUND_SSID;
    net_event_notify(NET_EVENT_FROM_WIFI, &net);
        
#if 0	//打开STA模式扫描连接扫描不到wifi名称，自动切回AP模式，防止死循环扫描无法回AP模式
        static u8 cnt = 0;
        cnt++;

        if (cnt >= 2) {
            sys_timeout_add(NULL, wifi_sta_to_ap_mode_change, 100);//回调不能直接切换，此处放在app_core切换
        }

#endif
        break;

    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_FAIL:
        puts("|network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_FAIL .....\n");
        
        // 更新WiFi列表中的连接状态为失败
        {
            struct wifi_mode_info info;
            info.mode = STA_MODE;
            wifi_get_mode_stored_info(&info);
            if (info.ssid) {
                printf("[WiFi Status] 连接失败(关联失败)，更新UI状态: SSID=%s\n", info.ssid);
                wifi_schedule_status_update(info.ssid, false);
            }
        }
    net.event = NET_CONNECT_ASSOCIAT_FAIL;
    net_event_notify(NET_EVENT_FROM_WIFI, &net);
        
#if 0	//打开STA模式连接路由器密码错误，自动切回AP模式，防止死循环连接路由器
        sys_timeout_add(NULL, wifi_sta_to_ap_mode_change, 100);//回调不能直接切换，此处放在app_core切换
#endif
        break;

    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_TIMEOUT:
        puts("|network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_TIMEOUT .....\n");
        break;

    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_SUCC:
        puts("|network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_SUCC\n");
        //有些使用了加密的路由器刚获取IP地址后前几个包都会没响应，怀疑路由器没转发成功
        void connect_broadcast(void);
        connect_broadcast();

        wifi_sta_save_ssid();

        /* wifi_backoff_cfg(3); //设置最大backoff范围  */

#ifdef CONFIG_STATIC_IPADDR_ENABLE
        store_dhcp_ipaddr();
#endif

#ifdef CONFIG_MASS_PRODUCTION_ENABLE
        extern void cWF_wifi_cont_flog(u8 cont_flog);
        cWF_wifi_cont_flog(1);
#endif

#ifndef CONFIG_RTSP_TEST_ENABLE
        void network_mssdp_init(void);
        network_mssdp_init();
#endif

#ifdef CONFIG_VOLC_RTC_ENABLE
        int VolcEngineRTCDemo();
        thread_fork("VolcRtc_demo", 4, 3 * 1024, 0 * 1024, 0, VolcEngineRTCDemo, NULL);
#endif

#ifdef CONFIG_VOLC_ONESDK_ENABLE
        int realtime_demo();
        thread_fork("realtime_demo", 4, 5 * 1024, 0, 0, realtime_demo, NULL);
#endif
    net.event = NET_EVENT_CONNECTED;
    net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_TIMEOUT\n");
        break;

    case WIFI_EVENT_P2P_START:
        puts("|network_user_callback->WIFI_EVENT_P2P_START\n");
        break;
    case WIFI_EVENT_P2P_STOP:
        puts("|network_user_callback->WIFI_EVENT_P2P_STOP\n");
        break;
    case WIFI_EVENT_P2P_GC_CONNECTED:
        puts("network_user_callback->WIFI_EVENT_P2P_GC_CONNECTED");
        break;
    case WIFI_EVENT_P2P_GC_DISCONNECTED:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_DISCONNECTED\n");
        wifi_enter_p2p_mode(P2P_GC_MODE, WIFI_P2P_DEVICE_NAME);
        net.event = NET_SCR_EVENT_DISCONNECTED;
        net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;
    case WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_SUCC:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_SUCC\n");
        void connect_to_server_port_8888(void);
        connect_to_server_port_8888();
        break;
    case WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_TIMEOUT\n");
        break;
    case WIFI_EVENT_P2P_GO_STA_CONNECTED:
        puts("network_user_callback->WIFI_EVENT_P2P_GO_STA_CONNECTED");
        break;
    case WIFI_EVENT_P2P_GO_STA_DISCONNECTED:
        puts("network_user_callback->WIFI_EVENT_P2P_GO_STA_DISCONNECTED");
        wifi_enter_p2p_mode(P2P_GO_MODE, WIFI_P2P_DEVICE_NAME);
        net.event = NET_SCR_EVENT_DISCONNECTED;
        net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;

    case WIFI_EVENT_P2P_WSC_OPERATION:
        PP2P_GO_STA_INFO info = (PP2P_GO_STA_INFO)network_ctx;
        printf("WIFI_EVENT_P2P_WSC_OPERATION device name[%d] = %.*s, mac = %02x:%02x:%02x:%02x:%02x:%02x\n",
               info->dev_name_len, info->dev_name_len, info->dev_name,
               info->dev_addr[0], info->dev_addr[1], info->dev_addr[2], info->dev_addr[3], info->dev_addr[4], info->dev_addr[5]);
        void p2p_wsc_trigger(void);
        p2p_wsc_trigger();
        break;

    case WIFI_EVENT_SMP_CFG_START:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_START\n");
        break;
    case WIFI_EVENT_SMP_CFG_STOP:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_STOP\n");
        break;
    case WIFI_EVENT_SMP_CFG_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_TIMEOUT\n");
    net.event = NET_EVENT_SMP_CFG_TIMEOUT;
    net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;
    case WIFI_EVENT_SMP_CFG_COMPLETED:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_COMPLETED\n");
    net.event = NET_SMP_CFG_COMPLETED;
    net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;

    case WIFI_EVENT_PM_SUSPEND:
        puts("|network_user_callback->WIFI_EVENT_PM_SUSPEND\n");
        break;
    case WIFI_EVENT_PM_RESUME:
        puts("|network_user_callback->WIFI_EVENT_PM_RESUME\n");
        break;
    case WIFI_EVENT_AP_ON_ASSOC:
        ;
#ifdef TCFG_WIFI_ENABLE
        lwip_set_default_netif(WIFI_NETIF);   //设置本地网卡为默认模块,兼容双网卡
#endif
        struct eth_addr *hwaddr = (struct eth_addr *)network_ctx;
        printf("WIFI_EVENT_AP_ON_ASSOC hwaddr = %02x:%02x:%02x:%02x:%02x:%02x \r\n\r\n",
               hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5]);
        wifi_connect_sta_mac(0,  hwaddr->addr, 6, 0);//存储mac
        break;
    case WIFI_EVENT_AP_ON_DISCONNECTED:
        hwaddr = (struct eth_addr *)network_ctx;
        struct ip4_addr ipaddr;
        dhcps_get_ipaddr(hwaddr->addr, &ipaddr);
        printf("WIFI_EVENT_AP_ON_DISCONNECTED hwaddr = %02x:%02x:%02x:%02x:%02x:%02x, ipaddr = [%d.%d.%d.%d] \r\n\r\n",
               hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5],
               ip4_addr1(&ipaddr), ip4_addr2(&ipaddr), ip4_addr3(&ipaddr), ip4_addr4(&ipaddr));
        ctp_keep_alive_find_dhwaddr_disconnect((struct eth_addr *)hwaddr->addr);
        cdp_keep_alive_find_dhwaddr_disconnect((struct eth_addr *)hwaddr->addr);
        wifi_connect_sta_mac(0,  hwaddr->addr, 6, 2);//清空mac
        net.event = NET_SCR_EVENT_DISCONNECTED;
        net_event_notify(NET_EVENT_FROM_WIFI, &net);
        break;
    case WIFI_EVENT_STA_IP_GOT_IPV6_SUCC:
        puts("network_user_callback->WIFI_EVENT_STA_IP_GOT_IPV6_SUCC");
        break;
    default:
        break;
    }

    return ret;
}


void net_app_init(void)
{
#ifdef CONFIG_MASS_PRODUCTION_ENABLE
    if (get_MassProduction()) {
        wifi_enter_sta_mode(STA_WIFI_SSID, STA_WIFI_PWD);
#if 0
        /*     **代码段功能:修改RTSP的URL */
        /* **默认配置  :URL为rtsp://192.168.1.1/avi_pcm_rt/front.sd,//(avi_pcma_rt 传G7111音频)传JPEG实时流 */
        /* ** */
        /* * */
        const char *user_custom_name = "avi_pcm_rt";
        const char *user_custom_content =
            "stream\r\n"\
            "file_ext_name avi\r\n"\
            "media_source live\r\n"\
            "priority 1\r\n"\
            "payload_type 26\r\n"\
            "clock_rate 90000\r\n"\
            "encoding_name JPEG\r\n"\
            "coding_type frame\r\n"\
            "byte_per_pckt 1458\r\n"\
            "stream_end\r\n"\
            "stream\r\n"\
            "file_ext_name pcm\r\n"\
            "media_source live\r\n"\
            "priority 1\r\n"\
            "payload_type 8\r\n"\
            "encoding_name PCMA\r\n"\
            "clock_rate 8000\r\n"\
            "stream_end";
        extern void rtsp_modify_url(const char *user_custom_name, const char *user_custom_content);
        rtsp_modify_url(user_custom_name, user_custom_content);
#endif
        extern int stream_media_server_init(struct fenice_config * conf);
        extern int fenice_get_video_info(struct fenice_source_info * info);
        extern int fenice_get_audio_info(struct fenice_source_info * info);
        extern int fenice_set_media_info(struct fenice_source_info * info);
        extern int fenice_video_rec_setup(void);
        extern int fenice_video_rec_exit(void);
        struct fenice_config conf = {0};

        strncpy(conf.protocol, "UDP", 3);
        conf.exit = fenice_video_rec_exit;
        conf.setup = fenice_video_rec_setup;
        conf.get_video_info = fenice_get_video_info;
        conf.get_audio_info = fenice_get_audio_info;
        conf.set_media_info = fenice_set_media_info;
        conf.port = RTSP_PORT;  // 当为0时,用默认端口554
        stream_media_server_init(&conf);
    } else
#endif
#ifdef CONFIG_RTSP_TEST_ENABLE
        extern int stream_media_server_init(struct fenice_config * conf);
    extern int fenice_get_video_info(struct fenice_source_info * info);
    extern int fenice_get_audio_info(struct fenice_source_info * info);
    extern int fenice_set_media_info(struct fenice_source_info * info);
    extern int fenice_video_rec_setup(void);
    extern int fenice_video_rec_exit(void);
    struct fenice_config conf = {0};

    strncpy(conf.protocol, "UDP", 3);
    conf.exit = fenice_video_rec_exit;
    conf.setup = fenice_video_rec_setup;
    conf.get_video_info = fenice_get_video_info;
    conf.get_audio_info = fenice_get_audio_info;
    conf.set_media_info = fenice_set_media_info;
    conf.port = RTSP_PORT;  // 当为0时,用默认端口554
    stream_media_server_init(&conf);
#else
    {
        ctp = server_open("ctp_server", (void *)&server_info);
        if (!ctp) {
            printf("ctp server fail\n");
        }
        puts("http server init\n");
        extern int http_virfile_reg(const char *path, const char *contents, unsigned long len);

        http_virfile_reg(DEV_DESC_PATH, DEV_DESC_CONTENT, strlen(DEV_DESC_CONTENT)); //注册虚拟文件描述文档,可在dev_desc.h修改
        http_get_server_init(HTTP_PORT); //8080
        video_rt_tcp_server_init(2229);
#ifdef CONFIG_ENABLE_VLIST
        preview_init(VIDEO_PREVIEW_PORT, NULL); //2226
        playback_init(VIDEO_PLAYBACK_PORT, NULL);
#endif

        /* printf("ftpd server init \n"); */
        /*extern void ftpd_vfs_interface_cfg(void);*/
        /*ftpd_vfs_interface_cfg();*/
        /*stupid_ftpd_init("MAXUSERS=2\nUSER=FTPX 12345678     0:/      2   A\n", NULL);*/

        /* void ftpd_server_init(const char *user, const char *pass, const char *ota_name, int fifo_size); */
        /* ftpd_server_init("FTPX", "12345678", "update-ota.ufw", 4096); */
    }
#endif
#ifdef CONFIG_IPERF_ENABLE
//网络测试工具，使用iperf
    extern void iperf_test(void);
    iperf_test();
#endif
}

void net_app_uninit(void)
{
    puts("ctp server uninit\n");
    server_close(ctp);
    puts("http server uninit\n");
    http_get_server_uninit(); //8080
    stupid_ftpd_uninit();
    video_rt_tcp_server_uninit();
    preview_uninit(); //2226
    playback_uninit();
#ifdef CONFIG_MASS_PRODUCTION_ENABLE
    extern void stream_media_server_uninit(void);
    stream_media_server_uninit();
#endif
}

static void wifi_app_task(void *priv)
{
    int msg[32];
    int res;

#ifdef PRODUCT_TEST_ENABLE
    u8 product_enter_check(void);
    if (product_enter_check()) {
        //进入产测模式后，将直接退出
        return;
    }
#endif
    wifi_set_store_ssid_cnt(NETWORK_SSID_INFO_CNT);
    wifi_set_event_callback(wifi_event_callback);
    wifi_on();
    wifi_set_long_retry(4);
    wifi_set_short_retry(7);

#if WIFI_ENTER_P2P_MODE
    wifi_enter_p2p_mode(P2P_GO_MODE, WIFI_P2P_DEVICE_NAME);
#endif
    //非量产模式下的AP和ST设置
#ifndef CONFIG_MASS_PRODUCTION_ENABLE
    //以下在wifi启动之后可以设置模式、名称、密码，不使用则是默认AP模式、wifi_camera_wl8x_xxxx、12345678
#ifdef CONFIG_WIFI_STA_MODE
    bool use_default_sta = true;
    struct wifi_mode_info stored_sta_info = {0};
    char stored_ssid[33] = {0};
    char stored_pwd[65] = {0};

    stored_sta_info.mode = STA_MODE;
    stored_sta_info.ssid = stored_ssid;
    stored_sta_info.pwd = stored_pwd;

    if (wifi_get_mode_stored_info(&stored_sta_info) == 0 &&
        stored_sta_info.mode == STA_MODE &&
        stored_sta_info.ssid && stored_sta_info.ssid[0] != '\0') {
        printf("[WiFi Boot] Found stored STA credentials: %s\n", stored_sta_info.ssid);
        wifi_enter_sta_mode(stored_sta_info.ssid, stored_sta_info.pwd);
        use_default_sta = false;
    }

    if (use_default_sta) {
        printf("[WiFi Boot] No stored STA credentials, using defaults\n");
        wifi_enter_sta_mode(STA_WIFI_SSID, STA_WIFI_PWD);//设置wifi进入STA模式以及STA名称和密码
        wifi_store_mode_info(STA_MODE, STA_WIFI_SSID, STA_WIFI_PWD);//保存默认模式
    }
#else
    //设置WIFI模式和名称密码，注意：不同AP和STA模式需要对应的库
    /*wifi_enter_ap_mode("test_123456", "12345678");//设置wifi进入AP模式以及AP名称和密码*/
    /*wifi_store_mode_info(AP_MODE, "test_123456", "12345678");//保存默认模式*/
#endif
#endif

#if defined BT_MUSIC
#if defined CONFIG_BT_ENABLE
    extern void bt_ble_module_init(void);
    bt_ble_module_init();
#endif
#endif

    net_app_init();
    sys_timer_add_to_task("sys_timer", NULL, wifi_app_timer_func, 5 * 1000);
}

#ifdef CONFIG_WIFI_ENABLE
int wireless_net_init(void)//主要是create wifi 线程的
{
    return thread_fork(WIFI_APP_TASK_NAME, 10, 1500, 64, 0, wifi_app_task, NULL);
}
late_initcall(wireless_net_init);
#endif

const char *get_root_path(void)
{
    return CONFIG_ROOT_PATH;
}
#if defined CONFIG_ENABLE_VLIST
unsigned short DUMP_PORT()
{
    return _DUMP_PORT;
}

unsigned short FORWARD_PORT()
{
    return _FORWARD_PORT;
}

unsigned short BEHIND_PORT()
{
    return _BEHIND_PORT;
}

const char *get_rec_path_0()
{
    return NULL;
}
const char *get_rec_path_1()
{
    return CONFIG_REC_PATH_0;
}
const char *get_rec_path_2()
{
    return CONFIG_REC_PATH_1;
}
const char *get_rec_path_3()
{
    return CONFIG_REC_PATH_2;
}
const char *get_rec_emr_path_1()
{
#ifdef CONFIG_EMR_REC_PATH_0
    return CONFIG_EMR_REC_PATH_0;
#else
    return NULL;
#endif
}
const char *get_rec_emr_path_2()
{
#ifdef CONFIG_EMR_REC_PATH_1
    return CONFIG_EMR_REC_PATH_1;
#else
    return NULL;
#endif
}
const char *get_rec_emr_path_3()
{
#ifdef CONFIG_EMR_REC_PATH_2
    return CONFIG_EMR_REC_PATH_2;
#else
    return NULL;
#endif
}
#endif

#endif
#endif
