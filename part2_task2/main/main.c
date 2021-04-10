/**
 * @file main.c
 * @author Siladi (developersiladi@gmail.com)
 * @brief Solution to 02 - Blinky chalenge
 * @version 0.1
 * @date 2021-04-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// LED rates
static const BaseType_t rate_1 = 500; // ms
static const BaseType_t rate_2 = 333; // ms

// Pins
static const BaseType_t ciLedPin = 2;

/**
 * @brief Blinky fuction 
 * 
 * @param pvParameter void pointer parameter
 */
void vToggleLED1(void *pvParameter) {
    while(1) {
        gpio_set_level(ciLedPin, 1);
        vTaskDelay(rate_1 / portTICK_PERIOD_MS);
        gpio_set_level(ciLedPin, 0);
        vTaskDelay(rate_1 / portTICK_PERIOD_MS);
    }
}

/**
 * @brief Blinky fuction wit another period
 * 
 * @param pvParameter void pointer parameter
 */
void vToggleLED2(void *pvParameter) {
    while(1) {
        gpio_set_level(ciLedPin, 1);
        vTaskDelay(rate_2 / portTICK_PERIOD_MS);
        gpio_set_level(ciLedPin, 0);
        vTaskDelay(rate_2 / portTICK_PERIOD_MS);
    }
}

void app_main(void) {
    /* Configuration is moved here to run only once*/

    /* Configure pin */
    gpio_reset_pin(ciLedPin);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(ciLedPin, GPIO_MODE_OUTPUT);

    /* Task to run forever */
    xTaskCreatePinnedToCore(    // Use xTaskCreate() in vanilla FreeRTOS
        vToggleLED1,            //Function to be called
        "Toggle LED",           // Name of task
        2048,                   // stack size (bytes in ESP32, words in FreeRTOS)
        NULL,                   // Parameter to pass to function
        1,                      // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,                   // Task handle
        app_cpu);               // Run on one cor dore demo purposes (ESP32 only);

    /* Task to run forever */
    xTaskCreatePinnedToCore(    // Use xTaskCreate() in vanilla FreeRTOS
        vToggleLED2,            //Function to be called
        "Toggle LED",           // Name of task
        2048,                   // stack size (bytes in ESP32, words in FreeRTOS)
        NULL,                   // Parameter to pass to function
        1,                      // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,                   // Task handle
        app_cpu);               // Run on one cor dore demo purposes (ESP32 only);

    // If this was vanilla FreeRTOS, you'd want to call vTaskStartScheduler() in
    // main after setting your tasks.
}
