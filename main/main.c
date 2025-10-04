
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "nvs_flash.h"
#include "led.h"
#include "spilcd.h"
#include <stdio.h>
#include "esp_lvgl_port.h"
#include "lvgl.h"
/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 */
void app_main(void)
{
    spilcd_t lcd = spilcd_init();              /* SPILCD初始化 */


    // 1. 初始化 LVGL port
    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    lvgl_port_init(&lvgl_cfg);

    // 2. 注册 LCD 屏幕
    lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = lcd.io_handle,        // 你前面用 esp_lcd 创建的 io_handle
        .panel_handle = lcd.panel_handle,  // 你前面用 esp_lcd_new_panel_st7789 得到的 panel_handle
        .buffer_size = 160 * 80,         // 刷新 buffer 一次多少像素
        .double_buffer = true,         // 双 buffer（推荐）
        .hres = 80,
        .vres = 160,
    };
    lv_disp_t *disp = lvgl_port_add_disp(&disp_cfg);    // lvgl_port_add_disp会覆盖panel驱动的gap设置
    esp_lcd_panel_set_gap(lcd.panel_handle, 26, 1);  // 常见 ST7735 80x160 参数

    // === 3. 创建全屏黑色背景 ===
    lv_obj_t *bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(bg, 80, 160);
    lv_obj_set_pos(bg, 0, 0);
    lv_obj_set_style_bg_color(bg, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(bg, 0, LV_PART_MAIN);

    // === 4. 创建一个 Label 并居中显示 ===
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello");

    // 居中方式 1：最简单的 API
    lv_obj_center(label);




    // lv_obj_t *rect = lv_obj_create(lv_scr_act());
    // lv_obj_set_size(rect, 20, 20);
    // lv_obj_set_style_bg_color(rect, lv_color_hex(0xFF0000), LV_PART_MAIN);
    // lv_obj_set_pos(rect, 0, 0);   // 左上角

    
    // 第二个矩形（绿色）
    // lv_obj_t *rect2 = lv_obj_create(lv_scr_act());
    // lv_obj_set_size(rect2, 10, 10);   // 宽10，高10
    // lv_obj_set_pos(rect2, 90, 40);   // 放在屏幕右下角 (160-10, 80-10)
    // lv_obj_set_style_bg_color(rect2, lv_color_hex(0xFF0000), LV_PART_MAIN); // 绿色背景




    // spilcd_draw_line(0,0,159,79,RED);
    // spilcd_draw_line(0,0,159,0,RED);
    // spilcd_draw_line(0,0,0,80,RED);

    // spilcd_draw_line(0,79,159,79,GREEN);
    // spilcd_draw_line(156,0,156,80,GREEN);

    // while(1)
    // {
    //     switch (x)
    //     {
    //         case 0:
    //         {
    //             spilcd_clear(WHITE);
    //             break;
    //         }
    //         case 1:
    //         {
    //             spilcd_clear(BLACK);
    //             break;
    //         }
    //         case 2:
    //         {
    //             spilcd_clear(BLUE);
    //             break;
    //         }
    //         case 3:
    //         {
    //             spilcd_clear(RED);
    //             break;
    //         }
    //         case 4:
    //         {
    //             spilcd_clear(MAGENTA);
    //             break;
    //         }
    //         case 5:
    //         {
    //             spilcd_clear(GREEN);
    //             break;
    //         }
    //         case 6:
    //         {
    //             spilcd_clear(CYAN);
    //             break;
    //         }
    //         case 7:
    //         {
    //             spilcd_clear(YELLOW);
    //             break;
    //         }
    //         case 8:
    //         {
    //             spilcd_clear(BRRED);
    //             break;
    //         }
    //         case 9:
    //         {
    //             spilcd_clear(GRAY);
    //             break;
    //         }
    //         case 10:
    //         {
    //             spilcd_clear(LGRAY);
    //             break;
    //         }
    //         case 11:
    //         {
    //             spilcd_clear(BROWN);
    //             break;
    //         }
    //     }

    //     spilcd_show_string(0, 0, 150, 32, 32, "ESP32-S3", RED);
    //     spilcd_show_string(0, 33, 150, 24, 24, "SPILCD TEST", RED);
    //     spilcd_show_string(0, 60, 150, 16, 16, "ATOM@ALIENTEK", RED);

    //     x++;
    //     if (x == 12)
    //     {
    //         x = 0;
    //     }

    // //     LED0_TOGGLE();
    //     vTaskDelay(pdMS_TO_TICKS(500));
    // }
}
