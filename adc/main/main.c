#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "led.h"
#include "iic.h"
#include "xl9555.h"
#include "lcd.h"
#include "adc1.h"
i2c_obj_t i2c0_master;
void app_main(void)
{   uint16_t    adc_value = 0;
    float       adc_voltage = 0.0;
    int8_t      temp=0;
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
    lcd_init();                       /* 初始化LCD */
    adc_init();                    
    
    lcd_show_string(10, 110, 200, 16, 16, "ADC1_CH7_VAL:0", BLUE);
    lcd_show_string(10, 130, 200, 16, 16, "ADC1_CH7_VOL:0.000V", BLUE);
    while(1)
    {
        adc_value = adc_get_result_average(ADC_ADCX_CHY, 10); /* 获取ADC转换且进行均值滤波后的结果 */
        lcd_show_xnum(114, 110, adc_value, 5, 16, 0, BLUE);       /* 显示ADC采样后的原始值 */
        adc_voltage = adc_value * (3.3 / 4095.0);              /* 计算电压值 */
        temp=adc_voltage;
        lcd_show_xnum(114, 130, temp, 1, 16, 0, BLUE);  
        adc_voltage = adc_voltage - temp;
        adc_voltage = adc_voltage * 1000;
        lcd_show_xnum(130, 130, adc_voltage, 3, 16, 0x80, BLUE); 
        LED_TOGGLE();                                           /* LED翻转函数 */
        vTaskDelay(100);
    }
}

