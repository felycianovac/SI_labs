#include "task_manager.h"
#include "../button/button.h"
#include "../../../lab_1/led/led.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../globals/globals.h"
#include <queue.h>
#include <semphr.h>

void handleButton(void* params) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    const TickType_t interval = pdMS_TO_TICKS(BUTTON_CHECK_INTERVAL);

    while (1) {
        if (isButtonPressed()) {
            ledOn(GREEN_LED);
            xSemaphoreGive(buttonTrigger);
            vTaskDelay(pdMS_TO_TICKS(GREEN_LED_DURATION));
            ledOff(GREEN_LED);
        }
        vTaskDelayUntil(&lastWakeTime, interval);
    }
}

void handleSync(void* params) {
    while (1) {
        if (xSemaphoreTake(buttonTrigger, portMAX_DELAY)) {
            // Increment the button press counter
            if (xSemaphoreTake(counterLock, portMAX_DELAY) == pdTRUE) {
                buttonPresses++;
                xSemaphoreGive(counterLock);
            }

            // Send numbers to the queue
            for (uint8_t i = 1; i <= buttonPresses; i++) {
                xQueueSendToFront(numberQueue, &i, portMAX_DELAY);
            }

            // Blink the red LED
            for (uint8_t i = 0; i < buttonPresses; i++) {
                ledOn(RED_LED);
                vTaskDelay(pdMS_TO_TICKS(RED_LED_ON_TIME));
                ledOff(RED_LED);
                vTaskDelay(pdMS_TO_TICKS(RED_LED_OFF_TIME));
            }

            vTaskDelay(pdMS_TO_TICKS(SYNC_TASK_WAIT));
        }
    }
}

void handleAsync(void* params) {
    uint8_t receivedNumber;

    while (1) {
        if (xQueueReceive(numberQueue, &receivedNumber, portMAX_DELAY)) {
            if (xSemaphoreTake(serialLock, portMAX_DELAY) == pdTRUE) {
                if (containsZero(receivedNumber) && receivedNumber != 0) {
                    printf("\n\r"); // Start a new line before printing the number
                }

                printf("%d ", receivedNumber); // Print the received number
                xSemaphoreGive(serialLock);
            }
        }
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