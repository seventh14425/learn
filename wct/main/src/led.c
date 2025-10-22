#include "led.h"

void gpio_init(void)
{
    gpio_config_t gpio_cfg= {0};
    gpio_cfg.intr_type=GPIO_INTR_DISABLE;
    gpio_cfg.mode=GPIO_MODE_INPUT_OUTPUT;
    gpio_cfg.pin_bit_mask=1ull << GPIO_NUM_1;
    gpio_cfg.pull_down_en=GPIO_PULLDOWN_DISABLE;
    gpio_cfg.pull_up_en=GPIO_PULLUP_DISABLE;
    gpio_config(&gpio_cfg);
}
