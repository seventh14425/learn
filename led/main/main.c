#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
void app_main(void)
{
    gpio_init();
    while (1)
    {
        gpio_set_level(GPIO_NUM_1,1);
        vTaskDelay(1000);
        gpio_set_level(GPIO_NUM_1,0);
        vTaskDelay(1000);
    }
    
}