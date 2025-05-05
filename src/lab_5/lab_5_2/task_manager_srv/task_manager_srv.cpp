#include "task_manager_srv.h"

#include "../pid_control/pid_control.h"
#include "../../../lab_4/lab_4_2/motor/motor_control.h"
#include "../../lab_5_1/sensor/potentiometer.h"
#include "../../../lab_2/lab_2_1/button/button.h"
#include "../../../lab_1/led/led.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"

#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define ALERT_LED 13

QueueHandle_t queueReporter = NULL;

// --- Queue Initialization ---
void ReportQueue_Init() {
    queueReporter = xQueueCreate(5, sizeof(ReportData));
}

// --- PID Control Task ---
static int saturationCounter = 0;
static const int saturationThreshold = 10;

void Task_PID_Control(void* pvParameters) {
    while (true) {
        int position = potentiotemeter_readPosition();

        if (isButtonPressed(BUTTON_UP))
            PIDControl_SetSetpoint(min(PIDControl_GetSetpoint() + 5, 1023)); // increase setpoint by 5, max 1023
        if (isButtonPressed(BUTTON_DOWN))
            PIDControl_SetSetpoint(max(PIDControl_GetSetpoint() - 5, 0));

        PIDControl_SetInput(position);// set input for PID control
        PIDControl_Compute(); // compute PID output
        int power = (int)PIDControl_GetOutput(); // get PID output
        Motor_SetPower(power); // set motor power

        if (power >= 255 || power <= -255)
            saturationCounter++;
        else
            saturationCounter = 0;

        //switch to led onoff functions
        if (saturationCounter >= saturationThreshold) {
            ledOn(ALERT_LED); // turn on alert LED
        } else {
            ledOff(ALERT_LED); // turn off alert LED
        }

        ReportData data = { PIDControl_GetSetpoint(), position, power }; // create report data
        xQueueSend(queueReporter, &data, portMAX_DELAY); // send data to queue

        vTaskDelay(pdMS_TO_TICKS(100)); // delay for 100ms
    }
}

void Task_ReportPlot(void* pvParameters) {
    ReportData data;
    while (true) {
        if (xQueueReceive(queueReporter, &data, portMAX_DELAY) == pdPASS) {
            printf("SetPoint: %d\tPosition: %d\tOutput: %d\n",
                   data.setPoint, data.position, data.power);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}