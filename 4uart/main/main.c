#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "uart.h"
#include "nvs_flash.h"
void app_main(void)
{
   
    esp_err_t ret;   
    
    uint8_t     len = 0;
    uint16_t    time = 0;
    unsigned char data[buf_rx_size]={0};
    gpio_init();
    uart_init();
    
    ret = nvs_flash_init(); /* 初始化NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    while (1)
    {
        uart_get_buffered_data_len(USART_UX, (size_t*)&len);
        if(len>0)
        {
            memset(data,0,buf_rx_size);
        
            uart_read_bytes(USART_UX, data, len, 100);
            uart_write_bytes(USART_UX, (const char*)data, strlen((const char*)data));
        }
        else
        {
            time++;
            if(time % 5000 == 0)
            {
                
                
            }
            if(time % 30 ==0)
            {
                LED_TOGGLE();
            }
            vTaskDelay(10);
        }

    }
    
}