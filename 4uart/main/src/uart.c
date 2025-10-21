#include "uart.h"

void uart_init(void)
{
    uart_config_t uart_Structure;
    uart_Structure.baud_rate = 115200;
    uart_Structure.data_bits = UART_DATA_8_BITS;
    uart_Structure.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_Structure.parity = UART_PARITY_DISABLE;
    uart_Structure.stop_bits = UART_STOP_BITS_1;
    uart_Structure.source_clk = UART_SCLK_APB;
    //uart_Structure.rx_flow_ctrl_thresh = 122;              /* 硬件控制流阈值 */
    uart_param_config(USART_UX, &uart_Structure);

    uart_set_pin(USART_UX, USART_TX_PIN, USART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(USART_UX, buf_rx_size * 2, buf_rx_size * 2, 0, NULL, 0);
}