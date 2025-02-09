/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2025 m0xter4ik on GitHub
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <pico/stdlib.h>
#include <stdint.h>

#include "probe_config.h"

#ifdef PROBE_WS8212_LED
#include "ws2812.pio.h"

#define PROBE_WS8212_PIO    pio0
#define PROBE_WS8212_SM     ((PROBE_SM) + 1)

static uint8_t usb_connected, dap_connected, dap_running;

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t) (r) << 8) | ((uint32_t) (g) << 16) | (uint32_t) (b);
}

static inline void put_pixel(uint32_t pixel_grb) {
    if(pio_sm_is_tx_fifo_empty(PROBE_WS8212_PIO, PROBE_WS8212_SM)) {
        pio_sm_put(PROBE_WS8212_PIO, PROBE_WS8212_SM, pixel_grb << 8u);
    }
}
#endif

void ext_led_init(void) {
#ifdef PROBE_WS8212_LED
    uint offset = pio_add_program(PROBE_WS8212_PIO, &ws2812_program);
    ws2812_program_init(PROBE_WS8212_PIO, PROBE_WS8212_SM, offset, PROBE_WS8212_LED, 800000, false);
#endif
}

void ext_led_update_status() {
#ifdef PROBE_WS8212_LED
    uint32_t color = 0;
    uint8_t bright = 32;

    if (dap_connected && dap_running) {
        color = urgb_u32(0, bright, bright);
    } else if(dap_running) {
        color = urgb_u32(0, bright, 0);
    } else if (dap_connected) {
        color = urgb_u32(0, 0, bright);
    } else if (usb_connected) {
        color = urgb_u32(bright, 0, 0);
    } else {
        color = urgb_u32(0, 0, 0);
    }
    put_pixel(color);
#endif
}

void ext_led_usb_connected(uint32_t bit) {
#ifdef PROBE_WS8212_LED
    usb_connected = bit ? 1 : 0;
#endif
}

void ext_led_dap_connected(uint32_t bit) {
#ifdef PROBE_WS8212_LED
    dap_connected = bit ? 1 : 0;
#endif
}

void ext_led_dap_running(uint32_t bit) {
#ifdef PROBE_WS8212_LED
    dap_running = bit ? 1 : 0;
#endif
}
