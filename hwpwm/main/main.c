#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "led.h"
#include "pwm.h"
void app_main(void)
{
 
    
    esp_err_t ret;
    
    ret = nvs_flash_init();         /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    //uint8_t dir = 1; 
    //uint16_t ledpwmval = 0;  
    gpio_init();
    pwm_init(13, 5000);            /* 初始化PWM，分辨率13位，频率5KHz */
    while (1)
    { 
        vTaskDelay(10);
        pwm_set_duty(LEDC_PWM_DUTY);     /* 设置PWM占空比 */
    } 
    
}