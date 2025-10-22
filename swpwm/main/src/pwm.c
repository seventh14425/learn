#include "pwm.h"

void pwm_init(uint8_t resolution, uint16_t freq)
{
    /* 配置LEDC定时器 */                    //配置定时器0
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_PWM_TIMER,
        .duty_resolution  = resolution,
        .freq_hz          = freq,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    /* 配置LEDC通道 */                      //配置通道0并给到GPIO1
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_PWM_CH0_CHANNEL,
        .timer_sel      = LEDC_PWM_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_PWM_CH0_GPIO,
        .duty           = 0
    };
    ledc_channel_config(&ledc_channel);
}

void pwm_set_duty(uint16_t duty)
{
    /* 设置PWM占空比 */
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_PWM_CH0_CHANNEL, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_PWM_CH0_CHANNEL);
}