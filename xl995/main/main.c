#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "led.h"
#include "iic.h"
#include "xl9555.h"
i2c_obj_t i2c0_master;
void app_main(void)
{    uint8_t key;
    gpio_init();
    esp_err_t ret;
    
    ret = nvs_flash_init();         /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    gpio_init();
    i2c0_master = iic_init(I2C_NUM_0);  /* 初始化IIC0 */
    xl9555_init(i2c0_master);           /* 初始化XL9555 */
   
    while(1)
    {
        key = xl9555_key_scan(0);
        
        switch (key)
        {
            case KEY0_PRES:
            {
               
                xl9555_pin_write(BEEP_IO, 0);
                break;
            }
            case KEY1_PRES:
            {
               
                xl9555_pin_write(BEEP_IO, 1);
                break;
            }
            case KEY2_PRES:
            {
              
                LED(0);
                break;
            }
            case KEY3_PRES:
            {
               
                LED(1);
                break;
            }
            default:
            {
                break;
            }
        }

        if (XL9555_INT == 0)
        {
            printf("123");
        }
        vTaskDelay(200);
    }
    
}