#include <Arduino.h>
#include "task_manager.h"
#include "command_queue.h"
#include "../relay/relay.h"
#include "../../../lab_1/led/led.h" 
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"

QueueHandle_t commandQueue;

// Task 1: Comenzi din terminal
void Task_CommandReader(void *pvParameters) {
    char buffer[20];
    char action[10];

    while (1) { //
        printf("> ");
        scanf("%19s", buffer);

        if (strcmp(buffer, "relay") == 0) { //if the first word is "relay"
            scanf("%9s", action);
            RelayCommand cmd = CMD_NONE; //set initial command to none

            if (strcmp(action, "on") == 0) cmd = CMD_RELAY_ON; //if the second word is "on"
            else if (strcmp(action, "off") == 0) cmd = CMD_RELAY_OFF;
            else {printf("Unknown command: %s\n", action);
            ledOn(RED_LED);
            delay(300);
            ledOff(RED_LED);
            }
            

            if (cmd != CMD_NONE)
                xQueueSend(commandQueue, &cmd, portMAX_DELAY);
        } else {
            ledOn(RED_LED);
            delay(300);
            ledOff(RED_LED);

            printf("Unknown command. Use: relay on / relay off\n");
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void Task_RelayControl(void *pvParameters) {
    RelayCommand cmd;

    while (1) {
        if (xQueueReceive(commandQueue, &cmd, portMAX_DELAY)) {
            switch (cmd) {
                case CMD_RELAY_ON:
                    relayOn();
                    printf("Relay Active (ON)\r\n");
                    break;

                case CMD_RELAY_OFF:
                    relayOff();
                    printf("Relay Inactive (OFF)\r\n"); //
                    break;

                default:
                    break;
            }
        }
    }
}

void Task_StatusReporter(void *pvParameters) {
    while (1) {
        printf("[INFO] Relay State: %s\r\n", relayGetState() ? "ON" : "OFF");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void TaskManager_StartTasks() {
    commandQueue = xQueueCreate(5, sizeof(RelayCommand));

    xTaskCreate(Task_CommandReader, "CommandReader", 2048, NULL, 1, NULL);
    xTaskCreate(Task_RelayControl, "RelayControl", 2048, NULL, 1, NULL);
    xTaskCreate(Task_StatusReporter, "StatusReporter", 2048, NULL, 1, NULL);
}
