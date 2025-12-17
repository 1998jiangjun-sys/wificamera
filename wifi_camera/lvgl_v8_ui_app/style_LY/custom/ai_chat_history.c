#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 

#include "ai_chat_history.h"
#include "gui_fonts.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define AI_CHAT_PANEL_SIDE_PADDING      16
#define AI_CHAT_PANEL_TOP_OFFSET        120
#define AI_CHAT_PANEL_BOTTOM_OFFSET     120
#define AI_CHAT_BUBBLE_WIDTH            360
#define AI_CHAT_BUBBLE_RADIUS           16
#define AI_CHAT_BUBBLE_PAD              12
#define AI_CHAT_BUBBLE_COLOR            0x5F93E8
#define AI_CHAT_MESSAGE_MAX             64

typedef enum {
    AI_CHAT_ROLE_USER = 0,
    AI_CHAT_ROLE_AI   = 1,
} ai_chat_role_t;

typedef struct {
    lv_obj_t *parent;
    lv_obj_t *panel;
    lv_obj_t *list;
    uint16_t  message_count;
} ai_chat_history_ctx_t;

static ai_chat_history_ctx_t s_chat_ctx = {0};

typedef struct ai_chat_async_msg {
    char *text;
    char *language;
    ai_chat_role_t role;
    struct ai_chat_async_msg *next;
} ai_chat_async_msg_t;

static ai_chat_async_msg_t *s_async_head = NULL;
static ai_chat_async_msg_t *s_async_tail = NULL;
static bool s_async_flush_pending = false;

static bool ai_chat_history_add_message_internal(const char *text, const char *language, ai_chat_role_t role, bool scroll_to_end);
static ai_chat_async_msg_t *ai_chat_history_async_pop(void);
static void ai_chat_history_async_handler(void *user_data);
static void ai_chat_history_trim(void);
static void ai_chat_history_scroll_to_bottom(lv_obj_t *target, bool animate);

static bool ai_chat_history_language_equals(const char *lhs, const char *rhs)
{
    if (!lhs || !rhs) {
        return false;
    }

    while (*lhs && *rhs) {
        if (tolower((unsigned char)*lhs) != tolower((unsigned char)*rhs)) {
            return false;
        }
        lhs++;
        rhs++;
    }

    return (*lhs == '\0') && (*rhs == '\0');
}

static const lv_font_t *ai_chat_history_pick_font(const char *language)
{
    if (!language || language[0] == '\0') {
        return &lv_font_simpo_28;
    }

    if (ai_chat_history_language_equals(language, "es")) 
    {
        return &lv_font_simpo_28;
    } 
    else if (ai_chat_history_language_equals(language, "zh")) 
    {
        return &lv_font_simsun_32;
    } 
    else if (ai_chat_history_language_equals(language, "en")) {
        return &lv_font_simsun_32;
    } 
    else if ( ai_chat_history_language_equals(language, "fr"))
    {
        return &lv_font_simpo_28;
    }
    else if (ai_chat_history_language_equals(language, "pt") )
    {
        return &lv_font_simpo_28;
    }
    else if (ai_chat_history_language_equals(language, "hi")) 
    {
        return &lv_font_mangal_28;
    }
    else if (ai_chat_history_language_equals(language, "ru")) 
    {
        return &lv_font_timesnewromanpsmt_28;
    }
    else if (ai_chat_history_language_equals(language, "ar")) 
    {
        return &lv_font_simpo_28;
    }
    
    /* 默认字体 */
    return &lv_font_simpo_28;
}

bool ai_chat_history_is_ready(void)
{
    return s_chat_ctx.list != NULL && lv_obj_is_valid(s_chat_ctx.list);
}

bool ai_chat_history_init(lv_obj_t *parent)
{
    if (!parent || !lv_obj_is_valid(parent)) {
        printf("[AI Chat] invalid parent\n");
        return false;
    }

    ai_chat_history_deinit();
    memset(&s_chat_ctx, 0, sizeof(s_chat_ctx));
    s_chat_ctx.parent = parent;

    lv_coord_t parent_width = lv_obj_get_width(parent);
    lv_coord_t parent_height = lv_obj_get_height(parent);

    if (parent_width <= 0) {
        parent_width = 480;
    }
    if (parent_height <= 0) {
        parent_height = 640;
    }

    lv_coord_t panel_width = parent_width - (AI_CHAT_PANEL_SIDE_PADDING * 2);
    lv_coord_t panel_height = parent_height - AI_CHAT_PANEL_TOP_OFFSET - AI_CHAT_PANEL_BOTTOM_OFFSET;
    if (panel_width <= 0) {
        panel_width = parent_width;
    }
    if (panel_height < 200) {
        panel_height = parent_height / 2;
    }

    lv_obj_t *panel = lv_obj_create(parent);
    if (!panel) {
        printf("[AI Chat] failed to create panel\n");
        return false;
    }

    s_chat_ctx.panel = panel;

    lv_obj_remove_style_all(panel);
    lv_obj_set_pos(panel, AI_CHAT_PANEL_SIDE_PADDING, AI_CHAT_PANEL_TOP_OFFSET);
    lv_obj_set_size(panel, panel_width, panel_height);
    lv_obj_set_scroll_dir(panel, LV_DIR_VER);
    lv_obj_set_scrollbar_mode(panel, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_set_style_bg_opa(panel, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(panel, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(panel, 0, LV_PART_MAIN);

    lv_obj_t *list = lv_obj_create(panel);
    if (!list) {
        printf("[AI Chat] failed to create list\n");
        ai_chat_history_deinit();
        return false;
    }

    s_chat_ctx.list = list;

    lv_obj_remove_style_all(list);
    lv_obj_set_width(list, lv_pct(100));
    lv_obj_set_height(list, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(list, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(list, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(list, 12, LV_PART_MAIN);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(list, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    s_chat_ctx.message_count = 0;

    printf("[AI Chat] panel initialized (width:%d height:%d)\n", panel_width, panel_height);
    return true;
}

void ai_chat_history_deinit(void)
{
    ai_chat_async_msg_t *pending = ai_chat_history_async_pop();
    while (pending) {
        if (pending->text) {
            lv_mem_free(pending->text);
        }
        lv_mem_free(pending);
        pending = ai_chat_history_async_pop();
    }
    s_async_flush_pending = false;

    if (s_chat_ctx.panel && lv_obj_is_valid(s_chat_ctx.panel)) {
        lv_obj_del(s_chat_ctx.panel);
    }
    memset(&s_chat_ctx, 0, sizeof(s_chat_ctx));
}

void ai_chat_history_clear(void)
{
    if (!ai_chat_history_is_ready()) {
        return;
    }
    lv_obj_clean(s_chat_ctx.list);
    s_chat_ctx.message_count = 0;
}

static void ai_chat_history_trim(void)
{
    if (!ai_chat_history_is_ready()) {
        return;
    }
    while (s_chat_ctx.message_count >= AI_CHAT_MESSAGE_MAX) {
        lv_obj_t *child = lv_obj_get_child(s_chat_ctx.list, 0);
        if (!child) {
            break;
        }
        lv_obj_del(child);
        if (s_chat_ctx.message_count > 0) {
            s_chat_ctx.message_count--;
        }
    }
}

static void ai_chat_history_scroll_to_bottom(lv_obj_t *target, bool animate)
{
    if (!ai_chat_history_is_ready()) {
        return;
    }

    if (!s_chat_ctx.panel || !lv_obj_is_valid(s_chat_ctx.panel)) {
        return;
    }

    lv_obj_update_layout(s_chat_ctx.list);
    lv_obj_update_layout(s_chat_ctx.panel);

    lv_coord_t bottom = lv_obj_get_scroll_bottom(s_chat_ctx.panel);
    if (bottom > 0) {
        lv_obj_scroll_by(s_chat_ctx.panel, 0, -bottom, animate ? LV_ANIM_ON : LV_ANIM_OFF);
    } else if (target && lv_obj_is_valid(target)) {
        lv_obj_scroll_to_view(target, animate ? LV_ANIM_ON : LV_ANIM_OFF);
    }
}

//lv_font_simpo_28 
static bool ai_chat_history_add_message_internal(const char *text, const char *language, ai_chat_role_t role, bool scroll_to_end)
{
    if (!text || text[0] == '\0') {
        return false;
    }
    if (!ai_chat_history_is_ready()) {
        printf("[AI Chat] add_message failed: not ready\n");
        return false;
    }

    ai_chat_history_trim();

    lv_obj_t *row = lv_obj_create(s_chat_ctx.list);
    if (!row) {
        printf("[AI Chat] failed to create row\n");
        return false;
    }

    lv_obj_remove_style_all(row);
    lv_obj_set_width(row, lv_pct(100));
    lv_obj_set_height(row, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(row, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(row, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(row, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(row, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(row, 0, LV_PART_MAIN);
    lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
    if (role == AI_CHAT_ROLE_USER) {
        lv_obj_set_flex_align(row, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    } else {
        lv_obj_set_flex_align(row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    }

    lv_obj_t *bubble = lv_obj_create(row);
    if (!bubble) {
        printf("[AI Chat] failed to create bubble\n");
        lv_obj_del(row);
        return false;
    }

    lv_obj_remove_style_all(bubble);
    if (role == AI_CHAT_ROLE_USER) {
        lv_obj_set_width(bubble, LV_SIZE_CONTENT);
    } else {
        lv_obj_set_width(bubble, AI_CHAT_BUBBLE_WIDTH);
    }
    lv_obj_set_height(bubble, LV_SIZE_CONTENT);
    lv_obj_set_style_radius(bubble, AI_CHAT_BUBBLE_RADIUS, LV_PART_MAIN);
    lv_obj_set_style_bg_color(bubble, lv_color_hex(AI_CHAT_BUBBLE_COLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bubble, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(bubble, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(bubble, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(bubble, AI_CHAT_BUBBLE_PAD, LV_PART_MAIN);
    lv_obj_set_style_pad_right(bubble, AI_CHAT_BUBBLE_PAD, LV_PART_MAIN);
    lv_obj_set_style_pad_top(bubble, AI_CHAT_BUBBLE_PAD, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(bubble, AI_CHAT_BUBBLE_PAD, LV_PART_MAIN);
    if (role == AI_CHAT_ROLE_USER) {
        lv_obj_set_style_max_width(bubble, AI_CHAT_BUBBLE_WIDTH, LV_PART_MAIN);
    } else {
        lv_obj_set_style_max_width(bubble, LV_COORD_MAX, LV_PART_MAIN);
    }

    lv_obj_t *label = lv_label_create(bubble);
    if (!label) {
        printf("[AI Chat] failed to create label\n");
        lv_obj_del(bubble);
        return false;
    }

    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    if (role == AI_CHAT_ROLE_USER) {
        lv_obj_set_width(label, LV_SIZE_CONTENT);
        lv_obj_set_style_max_width(label,
                                   AI_CHAT_BUBBLE_WIDTH - (AI_CHAT_BUBBLE_PAD * 2),
                                   LV_PART_MAIN | LV_STATE_DEFAULT);
    } else {
        lv_obj_set_width(label, AI_CHAT_BUBBLE_WIDTH - (AI_CHAT_BUBBLE_PAD * 2));
        lv_obj_set_style_max_width(label, LV_COORD_MAX, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    const lv_font_t *font = ai_chat_history_pick_font(language);
    if (!font) {
        font = &lv_font_simpo_28;
    }
    lv_obj_set_style_text_font(label, font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label,
                                (role == AI_CHAT_ROLE_USER) ? LV_TEXT_ALIGN_RIGHT : LV_TEXT_ALIGN_LEFT,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(label, text);

    ai_chat_history_scroll_to_bottom(row, scroll_to_end);

    s_chat_ctx.message_count++;
    return true;
}

bool ai_chat_history_add_message(const char *text, const char *language, bool from_user)
{
    return ai_chat_history_add_message_internal(text, language, from_user ? AI_CHAT_ROLE_USER : AI_CHAT_ROLE_AI, true);
}

static ai_chat_async_msg_t *ai_chat_history_async_pop(void)
{
    ai_chat_async_msg_t *msg = s_async_head;
    if (msg) {
        s_async_head = msg->next;
        if (!s_async_head) {
            s_async_tail = NULL;
        }
    }
    return msg;
}

static void ai_chat_history_async_handler(void *user_data)
{
    (void)user_data;

    while (true) {
        ai_chat_async_msg_t *msg = ai_chat_history_async_pop();
        if (!msg) {
            break;
        }

        bool scroll_to_end = (s_async_head == NULL);
        if (msg->text) {
            ai_chat_history_add_message_internal(msg->text, msg->language, msg->role, scroll_to_end);
            lv_mem_free(msg->text);
        }
        if (msg->language) {
            lv_mem_free(msg->language);
        }
        lv_mem_free(msg);
    }

    s_async_flush_pending = false;

    if (s_async_head && !s_async_flush_pending) {
        s_async_flush_pending = true;
        lv_res_t res = lv_async_call(ai_chat_history_async_handler, NULL);
        if (res != LV_RES_OK) {
            s_async_flush_pending = false;
            printf("[AI Chat] lv_async_call retry failed (%d)\n", res);
        }
    }
}

bool ai_chat_history_post_message(const char *text, const char *language, bool from_user)
{
    if (!text || text[0] == '\0') {
        return false;
    }

    ai_chat_async_msg_t *msg = lv_mem_alloc(sizeof(ai_chat_async_msg_t));
    if (!msg) {
        printf("[AI Chat] async alloc struct failed\n");
        return false;
    }
    memset(msg, 0, sizeof(ai_chat_async_msg_t));
    size_t len = strlen(text);
    msg->text = lv_mem_alloc(len + 1);
    if (!msg->text) {
        printf("[AI Chat] async alloc text failed\n");
        lv_mem_free(msg);
        return false;
    }
    memcpy(msg->text, text, len + 1);
    msg->language = NULL;
    if (language && language[0] != '\0') {
        size_t lang_len = strlen(language);
        msg->language = lv_mem_alloc(lang_len + 1);
        if (msg->language) {
            memcpy(msg->language, language, lang_len + 1);
        } else {
            printf("[AI Chat] async alloc language failed\n");
        }
    }
    msg->role = from_user ? AI_CHAT_ROLE_USER : AI_CHAT_ROLE_AI;
    msg->next = NULL;

    if (!s_async_head) {
        s_async_head = msg;
    } else {
        s_async_tail->next = msg;
    }
    s_async_tail = msg;

    if (!s_async_flush_pending) {
        s_async_flush_pending = true;
        lv_res_t res = lv_async_call(ai_chat_history_async_handler, NULL);
        if (res != LV_RES_OK) {
            printf("[AI Chat] lv_async_call failed (%d)\n", res);
            ai_chat_async_msg_t *prev = NULL;
            if (s_async_head == msg) {
                s_async_head = msg->next;
            } else {
                prev = s_async_head;
                while (prev && prev->next != msg) {
                    prev = prev->next;
                }
                if (prev) {
                    prev->next = msg->next;
                }
            }
            if (s_async_tail == msg) {
                s_async_tail = prev;
            }
            lv_mem_free(msg->text);
            if (msg->language) {
                lv_mem_free(msg->language);
            }
            lv_mem_free(msg);
            s_async_flush_pending = false;
            return false;
        }
    }

    return true;
}

#endif
