#include "wct.h"
esp_timer_handle_t esp_tim_handle;                         

void wdt_init( uint64_t tps)
{
  
    esp_timer_create_args_t tim_periodic_arg = {
    .callback =	&wdt_isr_handler,                         
    .arg = NULL,                                           
    };

   
    esp_timer_create(&tim_periodic_arg, &esp_tim_handle);  
    esp_timer_start_periodic(esp_tim_handle, tps);         
}
void restart_timer(uint64_t timeout)
{
    esp_timer_restart(esp_tim_handle, timeout);           

}
void IRAM_ATTR wdt_isr_handler(void *arg)
{
    esp_restart();                                      
}