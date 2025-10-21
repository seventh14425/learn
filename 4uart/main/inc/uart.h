#ifndef _UART_H
#define _UART_H
#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/uart_select.h"
#include <string.h>

#define USART_UX        UART_NUM_0
#define USART_RX_PIN    GPIO_NUM_44
#define USART_TX_PIN    GPIO_NUM_43

#define buf_rx_size     1024
void uart_init(void);

#endif