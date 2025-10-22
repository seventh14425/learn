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
    uint8_t dir = 1; 
    uint16_t ledpwmval = 0;  
    gpio_init();
    pwm_init(10, 5000);            /* 初始化PWM，分辨率10位，频率5KHz */
    while (1)
    { 
      /*   if(fangxiang)
        {
            for(CH0_duty = 0; CH0_duty < 1024; CH0_duty += 10)
            {
                pwm_set_duty(CH0_duty);   
                vTaskDelay(10 );
            }
            fangxiang = 0;
        }
        else
        {
            for(CH0_duty = 1023; CH0_duty > 0; CH0_duty -= 10)
            {
                pwm_set_duty(CH0_duty);   
                vTaskDelay(10 );
            }
            fangxiang = 1;
        } 
        */
        //在mian中一直跑（也算是freertos的一个任务，看门狗会让他卡死几秒）得放到独立任务里面
        
        vTaskDelay(10);

        if (dir == 1)
        {
            ledpwmval += 5; /* dir==1 ledpwmval递增 */
        }
        else
        {
            ledpwmval -= 5; /* dir==0 ledpwmval递减 */
        }

        if (ledpwmval > 1005)
        {
            dir = 0;        /* ledpwmval到达1005后，方向为递减 */
        }

        if (ledpwmval < 5)
        {
            dir = 1;        /* ledpwmval递减到5后，方向改为递增 */
        }

        /* 设置占空比 */
        pwm_set_duty(ledpwmval);
        //没有for ，阻塞时间不长 不会被强制中断

    }
    
}