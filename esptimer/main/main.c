#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "esptimer.h"
#include "nvs_flash.h"
void app_main(void)
{
     esp_err_t ret;
    
    ret = nvs_flash_init();         /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    gpio_init();                    /* 初始化LED引脚 */
    esptim_int_init(1000000);      /* 初始化高分辨率定时器，设置1秒周期 */
    
}