/**
 * @file chat_manager.h
 * @brief 好友聊天管理模块对外接口声明。
 *
 * 职责：
 * 1. 维护设备侧的好友列表（最多 10 位）。
 * 2. 为每个好友保存最近 20 条聊天记录（环形缓存自动淘汰最早记录）。
 * 3. 暴露统一的初始化、数据更新与查询接口给业务层或 UI 层调用。
 */
#ifndef WIFI_CAMERA_CHAT_MANAGER_H
#define WIFI_CAMERA_CHAT_MANAGER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cJSON; /**< 前向声明：用于 JSON 解析的 cJSON 结构体。*/

/** 好友列表与消息缓存的上限配置。 */
#define CHAT_MANAGER_MAX_FRIENDS                 10
#define CHAT_MANAGER_MAX_MESSAGES_PER_FRIEND     20
#define CHAT_MANAGER_MAX_GROUP_ID_LEN            64
#define CHAT_MANAGER_MAX_NAME_LEN                48
#define CHAT_MANAGER_MAX_URL_LEN                 128
#define CHAT_MANAGER_MAX_OPENID_LEN              96
#define CHAT_MANAGER_MAX_MESSAGE_ID_LEN          64
#define CHAT_MANAGER_MAX_CONTENT_LEN             256
#define CHAT_MANAGER_MAX_MEDIA_PATH_LEN          160

enum chat_manager_friend_source {
    CHAT_MANAGER_FRIEND_SOURCE_GROUP_LIST = 1 << 0,
    CHAT_MANAGER_FRIEND_SOURCE_SYNC_FRIEND = 1 << 1,
    CHAT_MANAGER_FRIEND_SOURCE_PP_MESSAGE = 1 << 2,
};

/**
 * @brief 消息内容类型枚举，与服务器协议字段 contentType 对应。
 */
enum chat_message_content_type {
    CHAT_MESSAGE_CONTENT_TEXT   = 1,
    CHAT_MESSAGE_CONTENT_IMAGE  = 2,
    CHAT_MESSAGE_CONTENT_VOICE  = 3,
    CHAT_MESSAGE_CONTENT_EMOJI  = 4,
};

/**
 * @brief 消息方向：区分对方消息与本地发送的消息。
 */
enum chat_message_direction {
    CHAT_MESSAGE_DIRECTION_INCOMING = 0, /**< 来源于好友/服务器的下行消息。 */
    CHAT_MESSAGE_DIRECTION_OUTGOING = 1, /**< 本地设备发送给好友的上行消息。 */
};

/**
 * @brief 好友（群组）信息结构体，对应服务器返回的 groupList 节点。
 */
struct chat_friend_entry {
    bool in_use;                                               /**< 当前槽位是否被占用。 */
    char group_id[CHAT_MANAGER_MAX_GROUP_ID_LEN];              /**< 群组/好友唯一 ID（IMEI 或群 ID）。 */
    int group_type;                                            /**< 0=群聊，1=单聊，2=碰碰交友。 */
    int relationship_image_id;                                 /**< 好友头像 ID。 */
    char group_name[CHAT_MANAGER_MAX_NAME_LEN];                /**< 好友昵称或群名称。 */
    char group_image[CHAT_MANAGER_MAX_URL_LEN];                /**< 群头像 URL（允许为空）。 */
    char call_openid[CHAT_MANAGER_MAX_OPENID_LEN];             /**< 通话 openid，单聊场景使用。 */
    bool can_video;                                            /**< 是否支持语音/视频通话。 */
    uint8_t source_mask;                                       /**< 好友来源标记，参见 chat_manager_friend_source 按位标记。 */
};

/**
 * @brief 单条聊天消息结构体，用于缓存最近的聊天记录。
 */
struct chat_message_record {
    uint8_t content_type;                                      /**< 消息类型，参见 chat_message_content_type，数值 1=文本、2=图片、3=语音、4=表情。 */
    uint8_t direction;                                         /**< 消息方向，参见 chat_message_direction，0=好友下行，1=本地上行。 */
    char relationship[CHAT_MANAGER_MAX_NAME_LEN];              /**< 发送者关系或昵称，用于聊天列表展示。 */
    char content[CHAT_MANAGER_MAX_CONTENT_LEN];                /**< 文本内容或表情 ID；语音/图片消息留空。 */
    char message_id[CHAT_MANAGER_MAX_MESSAGE_ID_LEN];          /**< 消息唯一 ID，用于去重和服务器回执。 */
    char media_path[CHAT_MANAGER_MAX_MEDIA_PATH_LEN];          /**< 图片/语音对应的本地缓存路径或远程 URL；下行语音初始为远程 URL，后台下载完成后会更新为 CONFIG_ROOT_PATH/chat_voice/ 下的本地文件路径。 */
    unsigned char *media_buffer;                               /**< 本地缓存的媒体数据指针，主要用于上行语音；由 chat_manager 管理生命周期。 */
    size_t media_buffer_len;                                   /**< 媒体数据缓冲区的字节数，media_buffer 为空时为 0。 */
    float duration;                                            /**< 媒体资源时长（秒），非媒体消息为 0。 */
    uint32_t size_bytes;                                       /**< 媒体资源大小（字节），文本为空时为 0。 */
    uint64_t timestamp_ms;                                     /**< 消息时间戳（毫秒），用于排序展示。 */
};

/** 初始化聊天管理模块，创建互斥量并清空缓存。 */
void chat_manager_init(void);
/** 主动向服务器发送 upGetChatUserList 请求。 */
int chat_manager_request_group_list(void);
int chat_manager_request_sync_friend(void);
/** 解析服务器返回的 downGetChatUserList 数据并刷新本地好友列表。 */
int chat_manager_handle_group_list_json(const struct cJSON *root);
int chat_manager_handle_sync_friend_json(const struct cJSON *root);
/** 解析服务器推送的 downChatVoice 消息并写入本地缓存。 */
int chat_manager_handle_down_chat_voice(const struct cJSON *root);
/** 解析服务器推送的 downPPmessage 消息并写入本地缓存。 */
int chat_manager_handle_down_pp_message(const struct cJSON *root);
/** 记录本地设备发送给好友的消息（写入环形缓存）。 */
int chat_manager_record_local_message(const char *group_id,
                                      enum chat_message_content_type content_type,
                                      const char *content,
                                      const char *message_id,
                                      uint64_t timestamp_ms,
                                      const char *media_path,
                                      uint32_t size_bytes,
                                      float duration,
                                      const char *display_name,
                                      const unsigned char *media_buffer,
                                      size_t media_buffer_len);

/** 获取当前已缓存的好友数量。 */
size_t chat_manager_get_friend_count(void);
/** 按索引获取好友信息指针（只读）。 */
const struct chat_friend_entry *chat_manager_get_friend(size_t index);
/**
 * @brief 获取指定好友的最近消息。
 *
 * @param group_id   好友或群组 ID。
 * @param out_records 输出缓冲区，可为 NULL 表示仅统计数量。
 * @param max_records 输出缓冲区的最大条目数。
 * @return 实际拷贝（或可用）的消息条目数。
 */
size_t chat_manager_get_friend_messages(const char *group_id,
                                        struct chat_message_record *out_records,
                                        size_t max_records);

#ifdef __cplusplus
}
#endif

#endif /* WIFI_CAMERA_CHAT_MANAGER_H */
