#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hardware/adc.h"
#include "pico/multicore.h"

void Led_Task_Code( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. 
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    */
   const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        vTaskDelay(50);
        gpio_put(LED_PIN, 0);
        vTaskDelay(50);
        printf("LED TASK ,run is cpu%d\r\n",get_core_num());
    }

}

void CheckCPU_Task_Code( void * pvParameters )
{
    while (true) {
    printf("Check CPU Task ,run is cpu%d\r\n",get_core_num());
     vTaskDelay(500);
    }
}

void Print_Task_Code( void * pvParameters )
{
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
    while (true) {
        float adc = (float)adc_read() * 3.3/4096;
        float tempC = 27.0f - (adc - 0.706f) / 0.001721f;
        printf("temperature:%.2f run is cpu%d\r\n",tempC,get_core_num());
        vTaskDelay(500);
    }
}

int main(void) {

stdio_init_all();
TaskHandle_t LedTask_Handle = NULL;
TaskHandle_t PrintTask_Handle = NULL;
TaskHandle_t CheckCPUTask_Handle = NULL;
/* Create the task, storing the handle. */
 xTaskCreate(
                    Led_Task_Code,       /* Function that implements the task. */
                    "Led task",   /* Text name for the task. */
                    512,             /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    &LedTask_Handle );   
 xTaskCreate(
                    Print_Task_Code,       /* Function that implements the task. */
                    "Print task",   /* Text name for the task. */
                    512,             /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    &PrintTask_Handle );   

 xTaskCreate(
                    CheckCPU_Task_Code,       /* Function that implements the task. */
                    "CheckCPU task",   /* Text name for the task. */
                    512,             /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    &CheckCPUTask_Handle ); 


//multicore_launch_core1(cpu_1_code);

vTaskStartScheduler();
while (1)
{
        configASSERT(0); /* We should never get here */

}
}
