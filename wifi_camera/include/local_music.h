#ifndef __LOCAL_MUSIC_H__
#define __LOCAL_MUSIC_H__
#include "server/audio_server.h"
#include "server/server_core.h"
#include "app_config.h"
#include "storage_device.h"
#include "event/key_event.h"
#include "event/device_event.h"
#include "syscfg/syscfg_id.h"
#include "system/wait.h"
#include "system/app_core.h"
#include "fs/fs.h"

#define VOLUME_STEP 5
#define MIN_VOLUME_VALUE	5
#define MAX_VOLUME_VALUE	100
#define INIT_VOLUME_VALUE  	50

/**
 * @description: 暂停/继续播放
 * @return {*}
 */
int local_music_dec_play_pause(void);

/**
 * @description: 停止播放
 * @return {*}
 */
int local_music_dec_stop(void);

/**
 * @description: 播放本地文件
 * @param {FILE} *file文件句柄
 * @return {*}
 */
int local_music_dec_file(FILE *file);

/**
 * @description: 初始化本地播放模式
 * @return {*}
 */
int local_music_mode_init(void);

/**
 * @description: 退出本地播放模式
 * @return {*}
 */
void local_music_mode_exit(void);


/**
 * @description: 切换文件夹
 * @param {int} fsel_mode
 * @return {*}
 */
int local_music_dec_switch_dir(int fsel_mode);

/**
 * @description: 切换文件 上一首或下一首
 * @param {int} fsel_mode
 * @return {*}
 */
int local_music_dec_switch_file(int fsel_mode);


/**
 * @description: 快进快退,单位是秒,暂时只支持MP3格式
 * @param {int} seek_step
 * @return {*}
 */
int local_music_dec_seek(int seek_step);

/**
 * @description: 获取解码器状态
 * @return {*}
 */
int local_music_get_dec_status(void);

/**
 * @description: 设置解码器音量
 * @param {int} step
 * @return {*}
 */
int local_music_set_dec_volume(int step);

/**
 * @description: 获取断点数据
 * @param {audio_dec_breakpoint} *bp
 * @return {*}
 */
int local_music_get_dec_breakpoint(struct audio_dec_breakpoint *bp);


#endif /* __LOCAL_MUSIC_H__ */
