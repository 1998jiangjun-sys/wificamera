#ifndef _RECORDER_H_
#define _RECORDER_H_

#include "server/audio_server.h"
#include "server/server_core.h"
#include "system/app_core.h"
#include "generic/circular_buf.h"
#include "os/os_api.h"
#include "app_config.h"
#include "syscfg/syscfg_id.h"
#include "event/key_event.h"
#include "storage_device.h"
#include "fs/fs.h"
#include <time.h>
#include "system/timer.h"
#include "media/spectrum/SpectrumShow_api.h"
#include "network_download/net_audio_buf.h"

#define VOLUME_STEP 5
#define MIN_VOLUME_VALUE	5
#define MAX_VOLUME_VALUE	100
#define INIT_VOLUME_VALUE  	50
#define GAIN_STEP           5

#define CONFIG_AUDIO_ENC_SAMPLE_SOURCE      AUDIO_ENC_SAMPLE_SOURCE_MIC    //录音输入源选择
#define CONFIG_AUDIO_DEC_PLAY_SOURCE        "dac"                          //播放输出源选择
#define CONFIG_AUDIO_RECORDER_SAMPLERATE    48000//16000                          //录音采样率
#define CONFIG_AUDIO_RECORDER_CHANNEL       1                              //录音通道数
#define CONFIG_AUDIO_RECORDER_DURATION      (30 * 1000)                    //录音时长ms
#define CONFIG_AUDIO_RECORDER_SAVE_FORMAT   "aac"                          //录音文件保存格式
#define CONFIG_AUDIO_RECORDER_PLAY_FORMAT   "aac"                          //自编自解格式仅支持pcm/mp3/aac/jla/amr/opus/ogg/speex格式

#define CONFIG_AUDIO_ADC_CHANNEL_L          0        //左mic/aux通道
#define CONFIG_AUDIO_ADC_CHANNEL_R          1        //右mic/aux通道
#define CONFIG_UAC_MIC_ADC_CHANNEL          0        //UAC mic通道
#define CONFIG_AUDIO_ADC_GAIN               100      //mic/aux增益

/**
 * @description: 打开录音模式,打开录音后，录音会通过dac播放
 * @return {*}
 */
int recorder_mode_init(void);


/**
 * @description: 关闭录音模式
 * @return {*}
 */
void recorder_mode_exit(void);
/**
 * @description: 调节音量
 * @param {int} step
 * @return {*}
 */
int recorder_dec_volume_change(int step);

/**
 * @description: 录音保存到文件，需要先关闭录音
 * @param {int} sample_rate
 * @param {u8} channel
 * @param {char} *format
 * @return {*}
 */
int recorder_to_file(int sample_rate, u8 channel, const char *format);

/**
 * @description: 停止录音
 * @return {*}
 */
void recorder_play_pause(void);



/**
 * @description: 关闭录音
 * @return {*}
 */
int recorder_close(void);



#endif /* _RECORDER_H_ */
