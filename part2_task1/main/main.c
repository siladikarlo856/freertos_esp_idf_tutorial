#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Pins
static const int ciLedPin = 2;

/**
 * @brief Blinky fuction 
 * 
 * @param pvParameter void pointer parameter
 */
void vToggleLED(void *pvParameter) {
    // Configure pin
    gpio_reset_pin(ciLedPin);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(ciLedPin, GPIO_MODE_OUTPUT);

    while(1) {
        gpio_set_level(ciLedPin, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(ciLedPin, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void) {

    // Task to run forever
    xTaskCreatePinnedToCore(    // Use xTaskCreate() in vanilla FreeRTOS
        vToggleLED,             //Function to be called
        "Toggle LED",           // Name of task
        2048,                   // stack size (bytes in ESP32, words in FreeRTOS)
        NULL,                   // Parameter to pass to function
        1,                      // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,                   // Task handle
        app_cpu);               // Run on one cor dore demo purposes (ESP32 only);

    // If this was vanilla FreeRTOS, you'd want to call vTaskStartScheduler() in
    // main after setting your tasks.
}
