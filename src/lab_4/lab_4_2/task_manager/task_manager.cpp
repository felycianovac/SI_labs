#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include "task_manager.h"
#include "../motor/motor_control.h"
#include "../L298Driver/L298Driver.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include <queue.h>
#include "motor_command.h"

QueueHandle_t motorCommandQueue; 

void Task_CommandInput(void *pvParameters);
void Task_MotorControl(void *pvParameters);
void Task_ReportStatus(void *pvParameters);

void TaskManager_Init() {
    motorCommandQueue = xQueueCreate(5, sizeof(MotorCommand));
    xTaskCreate(Task_CommandInput, "CommandInput", 256, NULL, 1, NULL);
    xTaskCreate(Task_MotorControl, "MotorControl", 256, NULL, 2, NULL);
    xTaskCreate(Task_ReportStatus, "ReportStatus", 256, NULL, 1, NULL);
}


void Task_CommandInput(void *pvParameters) {
    MotorCommand cmd;
    char input[64];

    while (true) {
        printf("> ");
        fflush(stdout);

        // Read everything until '!' (excluding '!')
        scanf(" %[^\n!]", input);  // read until newline or '!'
        getchar(); // consume the '!' or newline

        // Parse the command
        char action[16];
        int value;
        int parsed = sscanf(input, "%s", action);

        if (parsed == 1 && strcmp(action, "motor") == 0) {
            char subcommand[16];
            parsed = sscanf(input + strlen("motor"), "%s", subcommand);

            // Parse full string for more precision
            if (strstr(input, "set") != NULL) {
                parsed = sscanf(input, "motor set %d", &value);
                if (parsed == 1) {
                    printf("\r\n");
                    printf("Setting motor power to %d%%\r\n", value);
                    value = constrain(value, -100, 100);
                    cmd.power = value;
                    xQueueSend(motorCommandQueue, &cmd, portMAX_DELAY);
                }
            } else if (strstr(input, "stop") != NULL) {
                printf("\r\n");
                printf("Stopping motor.\r\n");
                cmd.power = 0;
                xQueueSend(motorCommandQueue, &cmd, portMAX_DELAY);
            } else if (strstr(input, "max") != NULL) {
                printf("\r\n");
                printf("Setting motor to max power.\r\n");
                int current = Motor_GetPower();
                cmd.power = (current >= 0) ? 100 : -100;
                xQueueSend(motorCommandQueue, &cmd, portMAX_DELAY);
            } else if (strstr(input, "inc") != NULL) {
                printf("\r\n");
                printf("Increasing motor power.\r\n");
                int current = Motor_GetPower();
                cmd.power = constrain(current + ((current >= 0) ? 10 : -10), -100, 100);
                xQueueSend(motorCommandQueue, &cmd, portMAX_DELAY);
            } else if (strstr(input, "dec") != NULL) {
                printf("\r\n");
                printf("Decreasing motor power.\r\n");
                int current = Motor_GetPower();
                cmd.power = constrain(current + ((current >= 0) ? -10 : 10), -100, 100);
                xQueueSend(motorCommandQueue, &cmd, portMAX_DELAY);
            } else {
                printf("\r\n");
                printf("Unknown motor command.\r\n");
            }
        } else {
            printf("\r\n");
            printf("Invalid command.\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


void Task_MotorControl(void *pvParameters) {
    MotorCommand cmd;

    while (true) {
        if (xQueueReceive(motorCommandQueue, &cmd, portMAX_DELAY) == pdPASS) {
            Motor_SetPower(cmd.power);
        }
    }
}

void Task_ReportStatus(void *pvParameters) {
    int lastPower = 999;

    while (true) {
        int current = Motor_GetPower();
        if (current != lastPower) {
            printf("[STATUS] Motor: %s | Power: %d%%\r\n",
                   current > 0 ? "Forward" :
                   current < 0 ? "Reverse" : "Stopped",
                   abs(current));
            lastPower = current;
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
