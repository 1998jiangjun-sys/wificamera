#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
#ifndef __AI_CHAT_HISTORY_H_
#define __AI_CHAT_HISTORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "lvgl.h"

/**
 * @brief 初始化聊天记录组件，在指定父容器下创建滚动聊天面板。
 *
 * @param parent   作为聊天面板的父容器，应为屏幕上的`AI_Q_A_view_5`。
 * @return true    创建成功。
 * @return false   创建失败或上下文无效。
 */
bool ai_chat_history_init(lv_obj_t *parent);

/**
 * @brief 释放聊天面板及内部资源。
 */
void ai_chat_history_deinit(void);

/**
 * @brief 立即在聊天面板中追加一条消息（需在LVGL线程中调用）。
 *
 * @param text        消息文本，UTF-8编码。
 * @param language    文本语言代码（如 "en"、"zh"），用于选择字体；可为NULL。
 * @param from_user   true表示用户消息（右对齐），false表示AI消息（左对齐）。
 * @return true       追加成功。
 */
bool ai_chat_history_add_message(const char *text, const char *language, bool from_user);

/**
 * @brief 异步追加消息，允许在非LVGL线程中调用。
 *        内部会复制文本并通过`lv_async_call`回到UI线程。
 *
 * @param text        消息文本，UTF-8编码。
 * @param language    文本语言代码（如 "en"、"zh"），用于选择字体；可为NULL。
 * @param from_user   true表示用户消息，false表示AI消息。
 * @return true       异步任务投递成功。
 */
bool ai_chat_history_post_message(const char *text, const char *language, bool from_user);

/**
 * @brief 清空聊天面板中的所有消息气泡。
 */
void ai_chat_history_clear(void);

/**
 * @brief 判断聊天面板是否已经初始化并处于有效状态。
 */
bool ai_chat_history_is_ready(void);

#ifdef __cplusplus
}
#endif

#endif /* __AI_CHAT_HISTORY_H_ */
#endif
