#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/**
 * @file chat_friend_history.h
 * @brief 聊天页面消息气泡面板接口。
 */
#ifndef CHAT_FRIEND_HISTORY_H
#define CHAT_FRIEND_HISTORY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "lvgl.h"
#include "chat_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 语音气泡的播放上下文信息。
 */
struct chat_friend_voice_info {
    char group_id[CHAT_MANAGER_MAX_GROUP_ID_LEN];       /**< 对应的好友/群组 ID。 */
    char message_id[CHAT_MANAGER_MAX_MESSAGE_ID_LEN];   /**< 消息唯一 ID。 */
    char media_path[CHAT_MANAGER_MAX_MEDIA_PATH_LEN];   /**< 语音文件的路径（本地或远程）。 */
    const unsigned char *media_buffer;                  /**< 内存中的语音数据指针（若可用，可为 NULL）。 */
    size_t media_buffer_len;                            /**< 语音缓冲区字节数。 */
    float duration;                                     /**< 语音时长（秒）。 */
    uint32_t size_bytes;                                /**< 数据大小（字节）。 */
    uint64_t timestamp_ms;                              /**< 时间戳（毫秒）。 */
    enum chat_message_direction direction;              /**< 消息方向。 */
};

/**
 * @brief 初始化聊天记录面板（需要在 chat_page 屏幕就绪后调用）。
 *
 * @param parent 作为消息列表父容器的 LVGL 对象。
 * @return true  初始化成功。
 */
bool chat_friend_history_init(lv_obj_t *parent);

/**
 * @brief 判断聊天记录面板是否已经完成初始化。
 */
bool chat_friend_history_is_ready(void);

/**
 * @brief 销毁聊天记录面板并释放内部资源。
 */
void chat_friend_history_deinit(void);

/**
 * @brief 设置当前激活的好友/群组并刷新列表。
 *
 * @param group_id 目标好友或群组 ID；传入 NULL 或空串将清空列表。
 */
void chat_friend_history_set_active_group(const char *group_id);

/**
 * @brief 主动刷新当前激活好友的消息。
 *
 * @param scroll_to_end 是否在渲染后滚动至最新消息。
 */
void chat_friend_history_refresh_active(bool scroll_to_end);

/**
 * @brief 在收到新的聊天消息（本地或远程）后调用，触发异步刷新。
 *
 * @param group_id      消息所属的好友/群组 ID。
 * @param scroll_to_end 刷新完成后是否滚动至底部。
 */
void chat_friend_history_notify_data_changed(const char *group_id, bool scroll_to_end);

/**
 * @brief 语音气泡点击时触发的回调，默认仅打印日志，可由业务层重写实现播放。
 */
void chat_friend_history_play_voice(const struct chat_friend_voice_info *info);

#ifdef __cplusplus
}
#endif

#endif /* CHAT_FRIEND_HISTORY_H */

#endif
