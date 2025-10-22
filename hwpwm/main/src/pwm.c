#include "pwm.h"

void pwm_init(uint8_t resolution, uint16_t freq)
{
    /* 配置LEDC定时器 */                    //配置定时器0
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_PWM_MODE,
        .timer_num        = LEDC_PWM_TIMER,
        .duty_resolution  = resolution,
        .freq_hz          = freq,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    /* 配置LEDC通道 */                      //配置通道0并给到GPIO1
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_PWM_MODE,
        .channel        = LEDC_PWM_CH0_CHANNEL,
        .timer_sel      = LEDC_PWM_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_PWM_CH0_GPIO,
        .duty           = 0
    };
    ledc_channel_config(&ledc_channel);
    ledc_fade_func_install(0);   
}

void pwm_set_duty(uint16_t duty)
{
    ledc_set_fade_with_time(LEDC_PWM_MODE, LEDC_PWM_CH0_CHANNEL, duty, LEDC_PWM_FADE_TIME);   /* 设置占空比以及渐变时长 */
    ledc_fade_start(LEDC_PWM_MODE, LEDC_PWM_CH0_CHANNEL, LEDC_FADE_NO_WAIT);                  /* 开始渐变 */

    ledc_set_fade_with_time(LEDC_PWM_MODE, LEDC_PWM_CH0_CHANNEL, 0, LEDC_PWM_FADE_TIME);      /* 设置占空比以及渐变时长 */
    ledc_fade_start(LEDC_PWM_MODE, LEDC_PWM_CH0_CHANNEL, LEDC_FADE_NO_WAIT);                  /* 开始渐变 */
}