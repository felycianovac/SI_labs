#include "task_manager.h"
#include "../button/button.h"
#include "../../../lab_1/led/led.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../globals/globals.h"
#include <queue.h>
#include <semphr.h>

void handleButton(void* params) {
    // Initialize the last wake time
    TickType_t lastWakeTime = xTaskGetTickCount();
    // Set the interval for checking the button
    const TickType_t interval = pdMS_TO_TICKS(BUTTON_CHECK_INTERVAL);

    // Check the button state
    while (1) {
        // Check if the button is pressed
        if (isButtonPressed()) {
            // Blink the green LED
            ledOn(GREEN_LED);
            // Give the semaphore to trigger the sync task
            xSemaphoreGive(buttonTrigger);
            // Wait for the green LED duration
            vTaskDelay(pdMS_TO_TICKS(GREEN_LED_DURATION));
            // Turn off the green LED
            ledOff(GREEN_LED);
        }
        // Delay until the next button check
        vTaskDelayUntil(&lastWakeTime, interval);
    }
}

void handleSync(void* params) {
    // Initialize the button press counter
    while (1) {
        // check if the button trigger semaphore is available
        if (xSemaphoreTake(buttonTrigger, portMAX_DELAY)) {
            // check if the counter lock is available
            if (xSemaphoreTake(counterLock, portMAX_DELAY) == pdTRUE) {
                // Increment the button press counter
                buttonPresses++;
                // Release the counter lock
                xSemaphoreGive(counterLock);
            }

            // traverse the button press counter
            for (uint8_t i = 1; i <= buttonPresses; i++) {
                // Send the number to the number queue
                xQueueSendToFront(numberQueue, &i, portMAX_DELAY);
            }

            // traverse the button press counter
            for (uint8_t i = 0; i < buttonPresses; i++) {
                // Blink the red LED
                ledOn(RED_LED);
                // Wait for the red LED on time
                vTaskDelay(pdMS_TO_TICKS(RED_LED_ON_TIME));
                // Turn off the red LED
                ledOff(RED_LED);
                // Wait for the red LED off time
                vTaskDelay(pdMS_TO_TICKS(RED_LED_OFF_TIME));
            }

            // ensure the serial lock is available
            vTaskDelay(pdMS_TO_TICKS(SYNC_TASK_WAIT));
        }
    }
}

void handleAsync(void* params) {
    // Initialize the received number
    uint8_t receivedNumber;

    while (1) {
        // Check if the number queue is available
        if (xQueueReceive(numberQueue, &receivedNumber, portMAX_DELAY)) {
            // Check if the serial lock is available
            if (xSemaphoreTake(serialLock, portMAX_DELAY) == pdTRUE) {
               // Check if the received number contains '0'
                if (containsZero(receivedNumber) && receivedNumber != 0) {
                    printf("\n\r"); // Start a new line before printing the number
                }
                // Print the received number
                printf("%d ", receivedNumber); // Print the received number
                // Release the serial lock
                xSemaphoreGive(serialLock);
            }
        }
        // Delay for the async task wait time
        vTaskDelay(pdMS_TO_TICKS(ASYNC_TASK_WAIT));
    }
}

bool containsZero(uint8_t number) {
    while (number > 0) {
        if (number % 10 == 0) {
            return true; // Return true if any digit is '0'
        }
        number /= 10;
    }
    return false; // Return false if no digit is '0'
}