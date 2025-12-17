#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
#include "custom.h"
#include "lvgl.h"
#include "gui_guider.h"
#include <stdint.h>

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR

#define CONFIG_FONT_JPEG_PATH "mnt/sdfile/EXT_RESERVED/uipackres/ui/poweron.jpg"

#include "system/includes.h"
#include "pipeline_core.h"
#include "asm/jpeg_codec.h"
#include "app_config.h"
#include "server/video_server.h"//app_struct
#include "server/video_dec_server.h"//dec_struct

#ifdef CONFIG_VIDEO_ENABLE

struct _jpeg_disp_f_t {
    struct server *dec_server;
};
struct _jpeg_disp_f_t map_jpeg_disp_fh = {0};
#define __this   (&map_jpeg_disp_fh)
#define JPG_MAX_SIZE 100*1024

int map_jpeg_disp_one_frame(u16 width, u16 height, u8 *buf, int len)
{
    union video_dec_req dec_req = {0};
    dec_req.dec.fb = "fb1";
    dec_req.dec.left = 0;
    dec_req.dec.top = 0;
    dec_req.dec.width = width;//屏幕的宽高
    dec_req.dec.height = height;
    dec_req.dec.thm_first = 0;
    dec_req.dec.pctl = NULL;
    dec_req.dec.preview = 0;
    dec_req.dec.image.buf = buf;
    dec_req.dec.image.size = len;
    return server_request(__this->dec_server, VIDEO_REQ_DEC_IMAGE, &dec_req);
}

int map_jpeg_disp_frame_init(void)
{
    memset(__this, 0x00, sizeof(struct _jpeg_disp_f_t));

    if (!__this->dec_server) {
        struct video_dec_arg arg = {0};
        arg.dev_name = "video_dec";
        arg.video_buf_size = JPG_MAX_SIZE;
        __this->dec_server = server_open("video_dec_server", &arg);
        if (!__this->dec_server) {
            printf("open video_dec_server fail");
            return -EFAULT;
        }
    }

    return 0;
}

int map_jpeg_disp_frame_uninit(void)
{
    union video_dec_req dec_req = {0};
    server_request(__this->dec_server, VIDEO_REQ_DEC_STOP, &dec_req);
    server_close(__this->dec_server);
    __this->dec_server = NULL;
    return 0;
}

#endif

extern lv_ui guider_ui;// Screen page_map

static lv_obj_t *page_map_info_lbl_7;
static lv_obj_t *page_map_info_lbl_9;

static void page_map_update_debug_label(int label_id, const char *text)
{
//     lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
//     if (!ui_scr || !ui_scr->page_map) {
//         return;
//     }

//     lv_obj_t **slot = (label_id == 7) ? &page_map_info_lbl_7 : &page_map_info_lbl_9;
//     lv_obj_t *label = *slot;

//     if (label && !lv_obj_is_valid(label)) {
//         *slot = NULL;
//         label = NULL;
//     }

//     if (!label) {
//         lv_obj_t *parent = ui_scr->page_map_view_3 ? ui_scr->page_map_view_3 : ui_scr->page_map;
//         label = lv_label_create(parent);
//         lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
//         lv_obj_set_style_bg_opa(label, LV_OPA_40, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_bg_color(label, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_pad_left(label, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_pad_right(label, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_pad_top(label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_pad_bottom(label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_style_text_font(label, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
//         lv_obj_set_width(label, 260);
//         if (label_id == 7) {
//             lv_obj_set_pos(label, 500, 150);
//         } else {
//             lv_obj_set_pos(label, 500, 190);
//         }
//         *slot = label;
//     }

//     lv_label_set_text(label, text ? text : "");
}

static void page_map_update_debug_label_proxy(int label_id, int text_ptr)
{
    const char *text = (const char *)(uintptr_t)text_ptr;
    page_map_update_debug_label(label_id, text);
}

void update_text_lbl_1(const char *str){
    // lv_ui_page_map * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    // lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_1 , str);
}
void update_text_lbl_2(const char *str){
    // lv_ui_page_map * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    // lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_2 , str);
}
void update_text_lbl_3(const char *str){
    //  lv_ui_page_map * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    //  lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_3 , str);
}
void update_text_lbl_4(const char *str){
    // lv_ui_page_map * ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    // lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_4 , str);
}

void update_text_lbl_7(const char *str){
    lvgl_rpc_post_func(page_map_update_debug_label_proxy, 2, 7, (int)(uintptr_t)str);
}
void update_text_lbl_9(const char *str){
    lvgl_rpc_post_func(page_map_update_debug_label_proxy, 2, 9, (int)(uintptr_t)str);
}

#endif
#endif
