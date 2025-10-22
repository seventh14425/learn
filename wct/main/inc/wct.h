#ifndef __WDT_H_
#define __WDT_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"


#define TWDT_TIMEOUT_MS         3000
#define TASK_RESET_PERIOD_MS    2000
#define MAIN_DELAY_MS           10000

void wdt_init( uint64_t tps);  /* 初始化独立看门狗 */
void restart_timer(uint64_t timeout);       /*  */
void IRAM_ATTR wdt_isr_handler(void *arg);

#endif