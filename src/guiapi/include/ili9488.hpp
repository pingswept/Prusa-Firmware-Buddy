// ili9488.hpp
#pragma once

#include "stm32f4xx_hal.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>
#include "guitypes.hpp"
#include <img_resources.hpp>
#include "Rect16.h"
#include "guiconfig.h"
#include "display_math_helper.h"

// public flags (config)
#define ILI9488_FLG_DMA  0x08 // DMA enabled
#define ILI9488_FLG_MISO 0x10 // MISO enabled
#define ILI9488_FLG_SAFE 0x20 // SAFE mode (no DMA and safe delay)

#define ILI9488_DEF_COLMOD 0x66 // interface pixel format (6-6-6, hi-color)
#define ILI9488_DEF_MADCTL 0xE0 // memory data access control (mirror XY)

#define ILI9488_COLS      480 //
#define ILI9488_ROWS      320 //
#define ILI9488_BUFF_ROWS 4 // Buffer size needs to fit at least one character of the largest font

inline constexpr uint8_t ILI9488_MAX_COMMAND_READ_LENGHT = 4;

typedef struct _ili9488_config_t {
    SPI_HandleTypeDef *phspi; // spi handle pointer
    uint8_t flg; // flags (DMA, MISO)
    uint8_t colmod; // interface pixel format
    uint8_t madctl; // memory data access control

    uint8_t gamma;
    uint8_t brightness;
    uint8_t is_inverted;
    uint8_t control;
    uint8_t pwm_inverted;
} ili9488_config_t;

inline uint32_t color_to_666(uint32_t clr) {
    return ((clr >> 16) & 0x00FC) | (clr & 0xFC00) | ((clr << 16) & 0xFC0000);
}

inline uint32_t color_from_666(uint32_t clr666) {
    return ((clr666 >> 16) & 0x00FC) | (clr666 & 0xFC00) | ((clr666 << 16) & 0xFC0000);
}

extern void ili9488_init(void);
extern void ili9488_cmd_dispon(void);
extern void ili9488_cmd_dispoff(void);
extern void ili9488_done(void);
extern void ili9488_clear(uint32_t clr666);
extern void ili9488_wr(uint8_t *pdata, uint16_t size);
extern void ili9488_fill_rect_colorFormat666(uint16_t rect_x, uint16_t rect_y, uint16_t rect_w, uint16_t rect_h, uint32_t clr666);

/**
 * @brief Draw QOI image from file.
 * @param pf pointer to file, it has to be open and pointing to the qoi header
 * @param point_x x coordinate of the top left corner of the image
 * @param point_y y coordinate of the top left corner of the image
 * @param back_color background color, (back_color >> 16) & 0xff is blue, (back_color >> 8) & 0xff is green, back_color & 0xff is red
 * @param rop raster operations as defined in display_math_helper.h and qoi_decoder.h
 * @param subrect subrectangle of the image to draw
 */
void ili9488_draw_qoi_ex(FILE *pf, uint16_t point_x, uint16_t point_y, uint32_t back_color, uint8_t rop, Rect16 subrect);

extern void ili9488_inversion_on(void);
extern void ili9488_inversion_off(void);
extern void ili9488_inversion_tgl(void);
extern uint8_t ili9488_inversion_get(void);

extern void ili9488_gamma_next(void);
extern void ili9488_gamma_prev(void);
extern void ili9488_gamma_set(uint8_t gamma);
extern uint8_t ili9488_gamma_get(void);

extern void ili9488_brightness_set(uint8_t brightness);
extern uint8_t ili9488_brightness_get(void);

extern void ili9488_brightness_enable(void);
extern void ili9488_brightness_disable(void);

extern uint8_t *ili9488_get_block(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);

extern uint32_t ili9488_get_pixel_colorFormat666(uint16_t point_x, uint16_t point_y);
extern void ili9488_set_pixel(uint16_t point_x, uint16_t point_y, uint32_t clr666);

extern ili9488_config_t ili9488_config;

/**
 * @brief Borrow display buffer.
 * @note This can be used only from the gui thread.
 * @note The buffer needs to be returned before it is used by display.
 * @return Pointer to display buffer.
 */
uint8_t *ili9488_borrow_buffer();

/**
 * @brief Return display buffer so it can be used by display or someone else.
 */
void ili9488_return_buffer();

/**
 * @brief Get size of display buffer.
 * @return size of display buffer in bytes
 */
size_t ili9488_buffer_size();

extern void ili9488_enable_safe_mode(void);
extern void ili9488_draw_from_buffer(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

extern void ili9488_spi_tx_complete(void);
extern void ili9488_spi_rx_complete(void);
extern void ili9488_cmd_madctlrd(uint8_t *pdata);

extern void ili9488_set_complete_lcd_reinit();

extern void ili9488_power_down();
