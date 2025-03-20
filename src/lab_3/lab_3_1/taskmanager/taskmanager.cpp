#include "taskmanager.h"
#include "../sensor/sensor.h"
#include "../display/display.h"
#include "task.h"
#include "queue.h"

// Task handles
TaskHandle_t SensorTaskHandle;
TaskHandle_t DisplayTaskHandle;

// Queue handle
QueueHandle_t sensorQueue;

// Task function prototypes
void SensorTask(void *pvParameters);
void DisplayTask(void *pvParameters);

// Task Manager: Initializes all tasks and queue
void taskmanager_init() {
    // Create queue for storing sensor data
    sensorQueue = xQueueCreate(5, sizeof(SensorData));

    // Create tasks
    xTaskCreate(SensorTask, "SensorTask", 256, NULL, 2, &SensorTaskHandle);
    xTaskCreate(DisplayTask, "DisplayTask", 256, NULL, 1, &DisplayTaskHandle);
}

// Task to read sensor data at fixed intervals and push to queue
void SensorTask(void *pvParameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();  // Initialize lastWakeTime
    TickType_t interval = pdMS_TO_TICKS(500); // Set sensor task interval to 500ms

    while (1) { // Infinite loop
        SensorData data = sensor_read();  // Read sensor data

        if (xQueueSend(sensorQueue, &data, pdMS_TO_TICKS(50)) != pdTRUE) { // If queue is full, drop data
            printf("Queue full! Dropping data.\n");
        }

        vTaskDelayUntil(&lastWakeTime, interval); // Ensure precise 500ms execution
    }
}

// Task to display sensor data at fixed intervals with an initial offset
void DisplayTask(void *pvParameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();  // Initialize lastWakeTime
    TickType_t interval = pdMS_TO_TICKS(500); // Set display task interval to 500ms

    vTaskDelay(pdMS_TO_TICKS(200)); // Introduce an initial offset of 200ms

    // Adjust lastWakeTime after the initial delay to maintain proper periodicity
    lastWakeTime = xTaskGetTickCount();  

    while (1) { // Infinite loop
        SensorData receivedData;

        if (xQueueReceive(sensorQueue, &receivedData, 0) == pdTRUE) { // if data received from queue
            display_update(receivedData); // Display sensor data
        } else {
            printf("WARNING: No data received from queue!\n"); // Display warning if no data received
        }

        vTaskDelayUntil(&lastWakeTime, interval); // Ensure precise 500ms execution after initial delay
    }
}
