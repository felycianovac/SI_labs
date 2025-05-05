#include "task_pid_control.h"
#include "../pid_control/pid_control.h"
#include "../../../lab_4/lab_4_2/motor/motor_control.h"
#include "../../lab_5_1/sensor/potentiometer.h"
#include "../../../lab_2/lab_2_1/button/button.h"
#include "../report_queue/report_queue.h"

#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define ALERT_LED 13

static int saturationCounter = 0;
static const int saturationThreshold = 10; 

void Task_PID_Control(void* pvParameters) {

    while (true) {
        int position = potentiotemeter_readPosition();

        if (isButtonPressed(BUTTON_UP)) PIDControl_SetSetpoint(min(PIDControl_GetSetpoint() + 5, 1023));
        if (isButtonPressed(BUTTON_DOWN)) PIDControl_SetSetpoint(max(PIDControl_GetSetpoint() - 5, 0));

        PIDControl_SetInput(position);
        PIDControl_Compute();
        int power = (int)PIDControl_GetOutput();
        Motor_SetPower(power);

        if (power >= 255 || power <= -255) {
            saturationCounter++;
        } else {
            saturationCounter = 0;
        }

        if (saturationCounter >= saturationThreshold) {
            digitalWrite(ALERT_LED, HIGH);
        } else {
            digitalWrite(ALERT_LED, LOW);
        }

        ReportData data = { PIDControl_GetSetpoint(), position, power };
        xQueueSend(queueReporter, &data, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
