#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "nvs_flash.h"
#include "esp_lvgl_port.h"
#include "led.h"
#include "lvgl.h"
#include "main_screen_gen.h"
#include "spilcd.h"
#include <stdio.h>

/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 */
void app_main(void)
{
    spilcd_t lcd = spilcd_init(); /* SPILCD初始化 */

    // 1. 初始化 LVGL port
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    lvgl_port_init(&lvgl_cfg);

    // 2. 注册 LCD 屏幕
    lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = lcd.io_handle,       // 你前面用 esp_lcd 创建的 io_handle
        .panel_handle = lcd.panel_handle, // 你前面用 esp_lcd_new_panel_st7789 得到的 panel_handle
        .buffer_size = 160 * 80,          // 刷新 buffer 一次多少像素
        .double_buffer = true,            // 双 buffer（推荐）
        .hres = 160,
        .vres = 80,
    };
    lv_disp_t *disp = lvgl_port_add_disp(&disp_cfg);     // lvgl_port_add_disp会覆盖panel驱动的gap设置
    esp_lcd_panel_swap_xy(lcd.panel_handle, true);       // 交换X/Y → 横屏
    esp_lcd_panel_mirror(lcd.panel_handle, true, false); // 可根据显示微调
    esp_lcd_panel_set_gap(lcd.panel_handle, 1, 26);      // 常见 ST7735 80x160 参数

    // === LVGL EDITOR 创建的UI界面 DEMO （可选：替换3和4）===
    // lv_obj_t *scr = main_screen_create();
    // lv_scr_load(scr);

    // === 3. 创建全屏黑色背景 ===
    lv_obj_t *bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(bg, 160, 80);
    lv_obj_set_pos(bg, 0, 0);
    lv_obj_set_style_bg_color(bg, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(bg, 0, LV_PART_MAIN);

    // === 4. 创建一个 Label 并居中显示 ===
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello");
    // 居中方式 1：最简单的 API
    lv_obj_center(label);
}
