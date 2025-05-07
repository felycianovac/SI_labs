#include "srv_task_manager.h"
#include "../../../lab_4/lab_4_2/motor/motor_control.h"
#include "../encoder/encoder.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../../../lab_2/lab_2_1/button/button.h"
#include "../../../lab_1/led/led.h"
#include "../../lab_5_2/pid_control/pid_control.h"
#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define ENCODER_PIN 2
#define BUTTON_UP_PIN 3
#define BUTTON_DOWN_PIN 4
#define ALERT_LED_PIN 13

QueueHandle_t queueReporter_ = NULL;

static int setSpeed = 300; // desired speed in pulses per second
static const int alertThreshold = 150;

void Queue_Init() {
    queueReporter_ = xQueueCreate(5, sizeof(ReportData));
}

void PIDControlTask_Init() {
    encoder_init(ENCODER_PIN);
    setupButtons();
    ledSetup();
    Motor_Init(8, 9, 10); // IN1, IN2, EN
    PIDControl_Init(2.0, 0.5, 1.0); // kp, ki, kd
}

void Task_PIDControl(void* pvParameters) {
    queueReporter_ = xQueueCreate(5, sizeof(ReportData));

    if (queueReporter_ == NULL) {
        printf("Queue creation failed!");
        while (1);
    }

    while (true) {
        int speed = get_speed(); // Read current speed

        if (isButtonPressed(BUTTON1))
            setSpeed = min(setSpeed + 20, 1000);
        if (isButtonPressed(BUTTON2))
            setSpeed = max(setSpeed - 20, 0);

        PIDControl_SetSetpoint(setSpeed);
        PIDControl_SetInput(speed);
        int power = (int)PIDControl_Compute(); // Get control output
        Motor_SetPower(power); // Apply to motor

        if (abs(speed - setSpeed) > alertThreshold) {
            ledOn(RED_LED);
        } else {
            ledOff(RED_LED);
        }

        ReportData data = { setSpeed, speed, Motor_GetPower() };
        xQueueSend(queueReporter_, &data, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void Task_Reporting(void* pvParameters) {
    service_serial_stdio_setup();
    ReportData data;

    while (true) {
        if (xQueueReceive(queueReporter_, &data, portMAX_DELAY) == pdPASS) {
            printf("[REPORT] SetSpeed: %d | Speed: %d | Power: %d\r\n",
                   data.setPoint, data.position, data.power);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}