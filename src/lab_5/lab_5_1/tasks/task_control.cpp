#include "task_control.h"
#include "../../../lab_4/lab_4_2/motor/motor_control.h"
#include "../sensor/potentiometer.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../../../lab_2/lab_2_1/button/button.h"
#include "../../../lab_1/led/led.h"


#define SENSOR_PIN A0
#define BUTTON_UP_PIN 2
#define BUTTON_DOWN_PIN 3
#define ALERT_LED_PIN 13

QueueHandle_t queueReport = NULL; 

static int setPoint = 512;
static const int hysteresis = 60;
static const int alertThreshold = 200;

void ControlTask_Init() {
    potentiometer_init(SENSOR_PIN);
    setupButtons();
    ledSetup();
}

void Task_ControlLoop(void* pvParameters) {

    queueReport = xQueueCreate(5, sizeof(ReportData));

    if (queueReport == NULL) {
        printf("Queue creation failed!");
        while (1); // stop execution
    }

    while (true) {
        int position = potentiotemeter_readPosition();

        // Adjust setPoint
        if (isButtonPressed(BUTTON1))
            // printf("Button  pressed\r\n");
            setPoint = min(setPoint + 5, 1023);
        if (isButtonPressed(BUTTON2))
            // printf("Button  pressed\r\n");
            setPoint = max(setPoint - 5, 0);

        // ON-OFF with hysteresis
        int lower = setPoint - hysteresis;
        int upper = setPoint + hysteresis;

        if (position < lower) {
            Motor_SetPower(50);
        } else if (position > upper) {
            Motor_SetPower(-50);
        } else {
            Motor_Stop();
        }

        if (abs(position - setPoint) > alertThreshold) {
            ledOn(RED_LED);
        } else {
            ledOff(RED_LED);
        }
        // Prepare and send data to the queue
        ReportData data = { setPoint, position, Motor_GetPower() };
        xQueueSend(queueReport, &data, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void Task_Reporter(void* pvParameters) {
    service_serial_stdio_setup();
    ReportData data;

    while (true) {
        if (xQueueReceive(queueReport, &data, portMAX_DELAY) == pdPASS) {
            printf("[REPORT] SetPoint: %d | Position: %d | Power: %d\r\n",
                   data.setPoint, data.position, data.power);
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}