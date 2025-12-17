#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t * setup_scr_usb_slave(lv_ui *ui)
{
	lv_ui_usb_slave * ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
	if (ui_scr == NULL) {
		ui_scr = lv_mem_alloc(sizeof(lv_ui_usb_slave));
		if (ui_scr == NULL) return NULL;
		memset(ui_scr, 0, sizeof(lv_ui_usb_slave));
		ui->usb_slave = ui_scr;
	}

	//Write codes usb_slave
	ui_scr->usb_slave = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui_scr->usb_slave, LV_SCROLLBAR_MODE_OFF);
	ui_style_set(ui_scr->usb_slave, GUI_CTRL_SCR);

	//Set style for usb_slave. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui_scr->usb_slave, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_scr->usb_slave, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes usb_slave_img_1
	ui_scr->usb_slave_img_1 = lv_img_create(ui_scr->usb_slave);
	lv_img_set_src(ui_scr->usb_slave_img_1, gui_get_res_path(GUI_RES_IMAGE_4215637_0_PNG));
	lv_img_set_pivot(ui_scr->usb_slave_img_1, 0, 0);
	lv_img_set_angle(ui_scr->usb_slave_img_1, 0);
	lv_img_set_zoom(ui_scr->usb_slave_img_1, 256);
	lv_obj_set_pos(ui_scr->usb_slave_img_1, 0, 0);
	lv_obj_set_size(ui_scr->usb_slave_img_1, 480, 640);
	lv_obj_add_flag(ui_scr->usb_slave_img_1, LV_OBJ_FLAG_CLICKABLE);
	ui_style_set(ui_scr->usb_slave_img_1, GUI_CTRL_IMG);

	//Set style for usb_slave_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_opa(ui_scr->usb_slave_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_scr->usb_slave_img_1, 128, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes usb_slave_gif_1
	ui_scr->usb_slave_gif_1 = lv_gif_create(ui_scr->usb_slave);
	lv_obj_set_pos(ui_scr->usb_slave_gif_1, 80, 258);
	lv_obj_set_size(ui_scr->usb_slave_gif_1, 320, 240);
	lv_obj_set_scrollbar_mode(ui_scr->usb_slave_gif_1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_state(ui_scr->usb_slave_gif_1, LV_STATE_HOVERED);
	lv_gif_set_src(ui_scr->usb_slave_gif_1, gui_get_res_path(GUI_RES_EZGIF_26D3AE8D7434C37A_GIF));

	lv_obj_update_layout(ui_scr->usb_slave);
	ui_scr->usb_slave_del = false;
	i18n_refresh_texts(GUI_SCREEN_USB_SLAVE);

	//Init events for screen
	events_init_usb_slave(ui);
	return ui_scr->usb_slave;
}
void unload_scr_usb_slave(lv_ui *ui)
{
	ui_free_scr_ptr(ui, GUI_SCREEN_USB_SLAVE);
}

#endif
