#ifndef BOARD_PICO_ZERO_H_
#define BOARD_PICO_ZERO_H_

/* Select one of these. */
/* Direct connection - SWCLK/SWDIO on two GPIOs */
#define PROBE_IO_RAW
/* SWCLK connected to a GPIO, SWDO driven from a GPIO, SWDI sampled via a level shifter */
//#define PROBE_IO_SWDI
/* Level-shifted SWCLK, SWDIO with separate SWDO, SWDI and OE_N pin */
//#define PROBE_IO_OEN

/* Include CDC interface to bridge to target UART. Omit if not used. */
#define PROBE_CDC_UART

/* Board implements hardware flow control for UART RTS/CTS instead of ACM control */
// #define PROBE_UART_HWFC

/* Target reset GPIO (active-low). Omit if not used.*/
#define PROBE_PIN_RESET 12

#define PROBE_SM 0
#define PROBE_PIN_OFFSET 13
/* PIO config for PROBE_IO_RAW */
#if defined(PROBE_IO_RAW)
#define PROBE_PIN_SWCLK (PROBE_PIN_OFFSET + 0)
#define PROBE_PIN_SWDIO (PROBE_PIN_OFFSET + 1)
#endif

/* PIO config for PROBE_IO_SWDI */
#if defined(PROBE_IO_SWDI)
#define PROBE_PIN_SWCLK (PROBE_PIN_OFFSET + 0)
#define PROBE_PIN_SWDIO (PROBE_PIN_OFFSET + 1)
#define PROBE_PIN_SWDI  (PROBE_PIN_OFFSET + 2)
#endif

/* PIO config for PROBE_IO_OEN - note that SWDIOEN and SWCLK are both side_set signals, so must be consecutive. */
#if defined(PROBE_IO_OEN)
#define PROBE_PIN_SWDIOEN (PROBE_PIN_OFFSET + 0)
#define PROBE_PIN_SWCLK (PROBE_PIN_OFFSET + 1)
#define PROBE_PIN_SWDIO (PROBE_PIN_OFFSET + 2)
#define PROBE_PIN_SWDI (PROBE_PIN_OFFSET + 3)
#endif

#if defined(PROBE_CDC_UART)
#define PROBE_UART_TX 8
#define PROBE_UART_RX 9
#define PROBE_UART_INTERFACE uart1
#define PROBE_UART_BAUDRATE 115200

#if defined(PROBE_UART_HWFC)
/* Hardware flow control - see 1.4.3 in the RP2040 datasheet for valid pin settings */
#define PROBE_UART_CTS 10
#define PROBE_UART_RTS 11
#else
/* Software flow control - RTS and DTR can be omitted if not used */
#define PROBE_UART_RTS 10
#define PROBE_UART_DTR 11
#endif

#endif

/* LED config - some or all of these can be omitted if not used */
//#define PROBE_USB_CONNECTED_LED 2
//#define PROBE_DAP_CONNECTED_LED 15
//#define PROBE_DAP_RUNNING_LED 16
//#define PROBE_UART_RX_LED 7
//#define PROBE_UART_TX_LED 8

/* Pinout
 * 8    TX
 * 9    RX
 * 10   RTS
 * 11   DTR
 * 12   RESET
 * 13   SWCLK
 * 14   SWDIO
 */

#define PROBE_PRODUCT_STRING "Debugprobe on PicoZ (CMSIS-DAP)"

#endif
