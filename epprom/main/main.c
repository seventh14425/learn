#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "led.h"
#include "iic.h"
#include "xl9555.h"
#include "lcd.h"
#include "24cxx.h"
i2c_obj_t i2c0_master;

const uint8_t g_text_buf[] = {"eeprom test"};  
#define TEXT_SIZE   sizeof(g_text_buf)            

void app_main(void)
{   
    uint16_t i = 0;
    uint8_t err = 0;
    uint8_t key;
    uint8_t datatemp[TEXT_SIZE];
    esp_err_t ret;
    
    ret = nvs_flash_init();         /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    gpio_init();
    i2c0_master = iic_init(I2C_NUM_0);  /* 初始化IIC0 */
    spi2_init();                       /* 初始化SPI2 */
    xl9555_init(i2c0_master);           /* 初始化XL9555 */
    at24cxx_init(i2c0_master);       
    lcd_init();                       /* 初始化LCD */
   
    err = at24cxx_check();              /* 检测AT24C02 */
    
    if (err != 0)
    {
        while (1)                       /* 检测不到24c02 */
        {
            lcd_show_string(10,30,120,16,16,"24c02 err!",RED);
            vTaskDelay(500);
            LED_TOGGLE();               /* LED闪烁 */
        }
    }

    while(1)
    {   key=xl9555_key_scan(0);
        switch (key)
        {
            case KEY0_PRES:
            {   lcd_clear(WHITE);
                at24cxx_write(0, (uint8_t *)g_text_buf, TEXT_SIZE);
                lcd_show_string(10,50,120,16,16,(char *)g_text_buf,RED);
                break;
            }
            case KEY1_PRES:
            {   lcd_clear(WHITE);
                at24cxx_read(0, datatemp, TEXT_SIZE);
                lcd_show_string(10,70,120,16,16,(char *)datatemp,RED);
                break;
            }
            
            default:
            {
                break;
            }
        }

        i++;

        if (i == 20)
        {
            LED_TOGGLE();               /* LED闪烁 */
            i = 0;
        }
        
        vTaskDelay(10);
    
    
    }
}

