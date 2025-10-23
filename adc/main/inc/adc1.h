

#ifndef __ADC_H_
#define __ADC_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"


#define ADC_ADCX_CHY   ADC1_CHANNEL_7 

/* 函数声明 */
void adc_init(void);                                            /* 初始化ADC */
uint32_t adc_get_result_average(uint32_t ch, uint32_t times);   /* 获取ADC转换且进行均值滤波后的结果 */

#endif
