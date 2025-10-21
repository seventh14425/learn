#include "esptimer.h"


void esptim_int_init(uint64_t tps)
{
    esp_timer_handle_t my_timer;                      /* 定时器回调函数句柄 */

    /* 定义一个定时器结构体 */
    esp_timer_create_args_t tim_periodic_arg = {
        .callback = &esptim_callback,                       /* 设置回调函数 */
        .arg = NULL,                                        /* 不携带参数 */
    };

    esp_timer_create(&tim_periodic_arg, &my_timer);   /* 创建一个事件 */
    esp_timer_start_periodic(my_timer, tps);          /* 每周期内触发一次 */
}

void esptim_callback(void *arg)
{
    LED_TOGGLE();
}
