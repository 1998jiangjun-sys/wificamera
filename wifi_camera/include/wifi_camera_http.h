#ifndef WIFI_CAMERA_HTTP_H
#define WIFI_CAMERA_HTTP_H

#include "app_config.h"

#if defined(CONFIG_NET_ENABLE)

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int wifi_camera_http_start(void);
void wifi_camera_http_stop(void);
void wifi_camera_http_trigger_scan(void);

int http_upload_manager_init(void);
int http_upload_manager_enqueue(const char *full_path, const char *display_path);
int http_upload_manager_request_scan(void);
void http_upload_manager_set_network_online(bool online);
void http_upload_manager_set_storage_ready(bool ready);
void http_upload_manager_set_ui_busy(bool busy);

enum wifi_camera_chat_content_type {
	WIFI_CAMERA_CHAT_CONTENT_TEXT  = 1,
	WIFI_CAMERA_CHAT_CONTENT_IMAGE = 2,
	WIFI_CAMERA_CHAT_CONTENT_VOICE = 3,
	WIFI_CAMERA_CHAT_CONTENT_EMOJI = 4,
};

struct wifi_camera_chat_message_params {
	const char *group_id;                 /**< 目标群组/好友 ID，必填。 */
	int group_type;                       /**< 群组类型，服务器协议提供。 */
	enum wifi_camera_chat_content_type content_type; /**< 消息内容类型。 */

	const char *content_text;             /**< 文本消息内容，可为空。 */
	const unsigned char *buffer;          /**< 若已在内存中提供二进制数据，指向数据的指针。 */
	size_t buffer_size;                   /**< buffer 的有效字节数。 */
	const char *file_path;                /**< 若需要从文件读取，上行内容文件路径。 */
	const char *upload_file_name;         /**< multipart 中的文件名缺省值。 */
	const char *mime_type;                /**< multipart 文件 MIME 类型，缺省自动推断。 */

	const char *display_name;             /**< 用于本地记录的显示名称，可选。 */
	const char *message_id;               /**< 自定义消息 ID，未提供则使用 ident。 */
	uint64_t timestamp_ms;                /**< 指定消息时间戳，0 表示使用当前时间。 */

	uint32_t audio_duration_ms;           /**< 语音时长（毫秒），语音类型必填。 */
	const char *audio_type;               /**< 语音编码类型（如 amr/mp3），语音类型可选。 */
	const char *bq_id;                    /**< 表情消息的 bqId，可选。 */

	bool request_return_url;              /**< 是否要求服务器返回远程 URL。 */
	char *out_remote_url;                 /**< 输出缓冲区，保存服务器返回的 URL。 */
	size_t out_remote_url_len;            /**< 输出缓冲区长度。 */
	const char *media_path_override;      /**< 本地记录使用的媒体路径覆盖，可选。 */

};

int wifi_camera_http_send_group_message(const struct wifi_camera_chat_message_params *params);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_NET_ENABLE */

#endif /* WIFI_CAMERA_HTTP_H */
