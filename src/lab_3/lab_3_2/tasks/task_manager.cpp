#include "task_manager.h"
#include "../sensor/joystick_sensor.h"
#include "../filters/filters.h"
#include "../conversion/conversion.h"
#include "../display/display.h"
#include <task.h>

#define FILTER_WINDOW 5

// Buffere și index pentru filtre
static uint16_t buffer_x[FILTER_WINDOW] = {0};
static uint16_t buffer_y[FILTER_WINDOW] = {0};
static uint8_t idx_x = 0;
static uint8_t idx_y = 0;

// Coada pentru comunicarea între task-uri
QueueHandle_t displayQueue;

// === Joystick Task ===
void joystick_task(void *pvParameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    const TickType_t period = pdMS_TO_TICKS(1500);

    while (1) {
        SensorRawData raw_data = read_sensor();
// Apply both filters for X
        uint16_t clean_x = filter_salt_and_pepper(raw_data.x_raw, 'x');
        uint16_t filtered_x = moving_average(clean_x, 'x');
        float voltage_x = adc_to_voltage(filtered_x);
        float percent_x = voltage_to_physical_parameter(voltage_x);

        uint16_t clean_y = filter_salt_and_pepper(raw_data.y_raw, 'y');
        uint16_t filtered_y = moving_average(clean_y, 'y');
        float voltage_y = adc_to_voltage(filtered_y);

        float percent_y = voltage_to_physical_parameter(voltage_y);

        // Umplem structura de display
        DisplayData data;
        data.raw_x = raw_data.x_raw;
        data.raw_y = raw_data.y_raw;
        data.filtered_x = filtered_x;
        data.filtered_y = filtered_y;
        data.voltage_x = voltage_x;
        data.voltage_y = voltage_y;
        data.percent_x = percent_x;
        data.percent_y = percent_y;
        data.button_state = raw_data.button_state;
        data.timestamp = raw_data.timestamp;

        // Trimitem la coadă
        xQueueSend(displayQueue, &data, portMAX_DELAY);

        vTaskDelayUntil(&lastWakeTime, period);
    }
}

// === Display Task ===
void display_task(void *pvParameters) {
    DisplayData received_data;

    while (1) {
        if (xQueueReceive(displayQueue, &received_data, portMAX_DELAY) == pdTRUE) {
            display_full_status(&received_data);
        }
    }
}

// === Funcție pentru lansarea task-urilor ===
void start_tasks() {
    // Inițializăm coada
    displayQueue = xQueueCreate(5, sizeof(DisplayData));

    // Creăm task-ul pentru joystick
    xTaskCreate(
        joystick_task,
        "JoystickTask",
        2048,
        NULL,
        1,
        NULL
    );

    // Creăm task-ul pentru display
    xTaskCreate(
        display_task,
        "DisplayTask",
        2048,
        NULL,
        1,
        NULL
    );
}
