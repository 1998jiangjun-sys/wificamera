#ifndef WIFI_CAMERA_HTTP_UPLOAD_STATE_H
#define WIFI_CAMERA_HTTP_UPLOAD_STATE_H

#include "app_config.h"

#if defined(CONFIG_NET_ENABLE)

#include <stdbool.h>
#include <stddef.h>
#include "os/os_api.h"

/**
 * @brief 记录路径字符串的最大长度（含结尾\0）。
 */
#define HTTP_UPLOAD_STATE_PATH_MAX        256
/**
 * @brief 状态缓存中允许保存的最大记录条目数。
 */
#define HTTP_UPLOAD_STATE_MAX_ENTRIES     9999

/**
 * @brief 单条上传记录，用于描述已成功上传的文件信息。
 */
struct http_upload_state_entry {
    char path[HTTP_UPLOAD_STATE_PATH_MAX];   ///< 逻辑展示路径（通常是相对路径）。
    u32 size;                                ///< 文件大小，单位字节。
    u32 timestamp;                           ///< 文件时间戳（UTC秒）。
};

/**
 * @brief 上传状态管理结构体，负责在内存中维护去重信息并持久化到磁盘。
 */
struct http_upload_state {
    OS_MUTEX lock;                                                           ///< 互斥锁，保护内部数据一致性。
    struct http_upload_state_entry entries[HTTP_UPLOAD_STATE_MAX_ENTRIES];   ///< 环形缓冲区保存历史记录。
    unsigned int count;                                                      ///< 当前有效记录数量。
    unsigned int next_index;                                                 ///< 当记录满时下一次覆盖的位置。
    char persist_path[HTTP_UPLOAD_STATE_PATH_MAX];                           ///< 状态文件的持久化路径。
    bool initialized;                                                        ///< 标记模块是否初始化完成。
    bool persist_loaded;                                                     ///< 是否已成功从磁盘加载持久化数据。
    bool pending_reload;                                                     ///< 是否需要在存储就绪后重新加载。
};

/**
 * @brief 初始化上传状态模块并尝试从磁盘恢复历史记录。
 *
 * @param state        状态对象指针，调用者提供存储空间。
 * @param persist_path 状态文件路径，位于存储介质上。
 *
 * @return 0 表示成功，负值表示失败错误码。
 */
int http_upload_state_init(struct http_upload_state *state, const char *persist_path);

/**
 * @brief 判断指定文件是否已经上传过，从而避免重复推送。
 *
 * @param state     状态对象指针，需已初始化。
 * @param path      逻辑展示路径，用于唯一标识文件。
 * @param size      文件大小，字节。
 * @param timestamp 文件时间戳（UTC秒）。
 *
 * @return true 表示检测到重复记录，false 表示可继续上传。
 */
bool http_upload_state_is_duplicate(struct http_upload_state *state,
                                    const char *path,
                                    u32 size,
                                    u32 timestamp);

/**
 * @brief 在上传成功后记录文件信息并刷新到磁盘，供后续去重使用。
 *
 * @param state     状态对象指针，需已初始化。
 * @param path      逻辑展示路径，用于唯一标识文件。
 * @param size      文件大小，字节。
 * @param timestamp 文件时间戳（UTC秒）。
 *
 * @return 0 表示成功，负值表示失败错误码。
 */
int http_upload_state_record_success(struct http_upload_state *state,
                                     const char *path,
                                     u32 size,
                                     u32 timestamp);

/**
 * @brief 在存储介质就绪后重新从磁盘加载历史记录。
 *
 * @param state 状态对象指针，需已初始化。
 *
 * @return 0 表示成功，负值表示失败错误码。
 */
int http_upload_state_reload(struct http_upload_state *state);

/**
 * @brief 标记是否需要等待存储就绪后再尝试加载持久化数据。
 *
 * @param state   状态对象指针，需已初始化。
 * @param pending true 表示需要重新加载，false 表示不需要。
 */
void http_upload_state_set_pending_reload(struct http_upload_state *state, bool pending);

#endif /* CONFIG_NET_ENABLE */

#endif /* WIFI_CAMERA_HTTP_UPLOAD_STATE_H */
