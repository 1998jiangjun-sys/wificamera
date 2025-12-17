#ifndef __NET_MUSIC_H__
#define __NET_MUSIC_H__

#include "server/audio_server.h"
#include "server/server_core.h"
#include "app_config.h"
#include "storage_device.h"
#include "event/key_event.h"
#include "event/device_event.h"
#include "event/net_event.h"
#include "syscfg/syscfg_id.h"
#include "system/wait.h"
#include "system/app_core.h"
#include "lwip.h"

#include "server/ai_server.h"
#include "network_download/net_download.h"

#include "debug.h"

#define VOLUME_STEP 5
#define MIN_VOLUME_VALUE	5
#define MAX_VOLUME_VALUE	100
#define INIT_VOLUME_VALUE  	50

#define LOG_TAG             "[NET_MUSIC]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE

/// @brief 初始化网络音乐模式
/// @param
/// @return
int net_music_mode_init(void);

/// @brief 下载网络音乐文件并播放
/// @param url 音乐文件url
/// @return
int net_music_dec_file(const char *url);

/// @brief 暂停/继续播放
/// @param notify是否需要通知云端暂停
/// @return
int net_music_dec_play_pause(u8 notify);


/// @brief 暂停音乐播放
/// @param
/// @return
int net_music_dec_stop(void);

/// @brief 退出网络音乐模式
/// @param
void net_music_mode_exit(void);

#endif
