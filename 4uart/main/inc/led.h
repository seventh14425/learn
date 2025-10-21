#ifndef _LED_H
#define _LED_H

#include "driver/gpio.h"
#define LED_GPIO_PIN    GPIO_NUM_1   /* LED连接的GPIO口 */
#define LED_TOGGLE()    do { gpio_set_level(LED_GPIO_PIN, !gpio_get_level(LED_GPIO_PIN)); } while(0)  /* LED翻转 */

void gpio_init(void);
#endif
