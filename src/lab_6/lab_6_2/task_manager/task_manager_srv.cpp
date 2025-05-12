#include "task_manager_srv.h"
#include "../globals/globals.h"
#include "../../../lab_2/lab_2_1/button/button.h"
#include "../fsm_actions/fsm_actions.h"
#include "../finite_state_machine/finite_state_machine.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// Shared variables with proper synchronization
volatile bool nsRequest = false;
volatile int currentFSMState = STATE_EW_GREEN;  // Start with EW GREEN state
SemaphoreHandle_t stateMutex;  // Mutex for state access

int state = STATE_EW_GREEN;
bool switching = false;

volatile bool nightModeActive = false;


// --- Task: NS Button Request ---
void Task_NS_RequestHandler(void* pvParameters) {
    setupButtons();
    while (true) {
        if (isButtonPressed(BUTTON_NS_REQUEST)) {
            nsRequest = true;
            // Small delay to debounce button
            vTaskDelay(pdMS_TO_TICKS(200));
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void Task_TrafficController(void* pvParameters) {
    TickType_t lastWake = xTaskGetTickCount();
    int state = STATE_EW_GREEN;
    bool fsmSuspendedForNight = false;

    FSM[state].OutputAction();

    while (true) {
        // --- PAUSE FSM IN NIGHT MODE ---
        if (nightModeActive) {
            if (!fsmSuspendedForNight) {
                printf("FSM paused for Night Mode\n");
                fsmSuspendedForNight = true;
            }
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }

        // --- RESUME FSM WHEN NIGHT MODE TURNS OFF ---
        if (fsmSuspendedForNight) {
            printf("FSM resumed from Night Mode\n");
            lastWake = xTaskGetTickCount();       // realign FSM delay
            FSM[state].OutputAction();            // re-activate LEDs
            fsmSuspendedForNight = false;
        }

        // Normal FSM loop
        xSemaphoreTake(stateMutex, pdMS_TO_TICKS(10));
        currentFSMState = state;
        xSemaphoreGive(stateMutex);

        FSM[state].OutputAction();
        vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(FSM[state].Time));

        // FSM transition logic
        switch (state) {
            case STATE_EW_GREEN:
                if (nsRequest) {
                    state = STATE_EW_YELLOW;
                    nsRequest = false;
                }
                break;
            case STATE_EW_YELLOW:
                state = STATE_NS_ENTRY_YELLOW;
                break;
            case STATE_NS_ENTRY_YELLOW:
                state = STATE_NS_GREEN;
                break;
            case STATE_NS_GREEN:
                state = STATE_NS_YELLOW;
                break;
            case STATE_NS_YELLOW:
                state = STATE_EW_ENTRY_YELLOW;
                break;
            case STATE_EW_ENTRY_YELLOW:
                state = STATE_EW_GREEN;
                break;
        }
    }
}



void Task_NightModeToggle(void* pvParameters) {
    pinMode(BUTTON_NIGHTMODE, INPUT_PULLUP);
    bool previous = HIGH;

    while (true) {
        bool current = digitalRead(BUTTON_NIGHTMODE);
        if (previous == HIGH && current == LOW) {
            nightModeActive = !nightModeActive;
            printf(nightModeActive ? "NIGHT MODE ON\r\n" : "NIGHT MODE OFF\r\n");
            vTaskDelay(pdMS_TO_TICKS(300)); // debounce
        }
        previous = current;
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}


void Task_NightBlinker(void* pvParameters) {
    while (true) {
        if (nightModeActive) {
            Action_NightModeBlink();
            vTaskDelay(pdMS_TO_TICKS(500));
        } else {
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}




// --- Task Manager Entry ---
void TaskManager_Initialize() {
    // Create mutex for state access
    stateMutex = xSemaphoreCreateMutex();
    
    if (stateMutex == NULL) {
        // Handle mutex creation failure
        printf("Failed to create mutex\n");
        return;
    }
    
    // Create a single traffic controller task instead of separate EW and NS tasks
    xTaskCreate(Task_TrafficController, "TrafficControl", 256, NULL, 2, NULL);
    xTaskCreate(Task_NS_RequestHandler, "Task_Request", 128, NULL, 1, NULL);
    xTaskCreate(Task_NightModeToggle, "Task_NightMode", 128, NULL, 1, NULL);
    xTaskCreate(Task_NightBlinker, "Task_NightBlinker", 128, NULL, 1, NULL);
}