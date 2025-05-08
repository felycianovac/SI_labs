#include <Arduino.h>
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../../lab_5_2/pid_control/pid_control.h"
#include "../../lab_5_1/sensor/potentiometer.h"
#include "../../../lab_2/lab_2_1/button/button.h"++
#include "../../../lab_1/led/led.h"
#include <Arduino_FreeRTOS.h>
#include "../srv_task_manager/srv_task_manager.h"
#include "../encoder/encoder.h"
#include "../tachometer/tachometer.h"
#include "../motor/motor.h"

#define FAN_PWM_PIN 9     // Blue wire (PWM)
#define FAN_TACH_PIN 2    // Yellow wire (Tachometer signal)
#define ALERT_THRESHOLD 200   // 20% deviation


void lab_5_2_1_app_setup() {
    service_serial_stdio_setup();
    printf("Fan PID Control - Lab 5.2.1 started.\r\n");

    ledSetup();
    Motor_Init(FAN_PWM_PIN);
    Tachometer_Init(FAN_TACH_PIN);

    PIDControl_Init(1.0, 0.2, 0.1);
    PIDControl_SetSetpoint(10); // Default RPM target
}

void lab_5_2_1_app_loop() {
    static unsigned long lastUpdate = 0;
    const unsigned long interval = 500;
    static int setpoint = 10;
    const int step = 50;
    const int minRPM = 10;
    const int maxRPM = 2000;

    // Handle user input
    if (Serial.available()) {
        char ch;
        scanf(" %c", &ch);
        if (ch == '+') {
            setpoint = min(setpoint + step, maxRPM);
            PIDControl_SetSetpoint(setpoint);
            printf("+Increased SetPoint to: %d RPM\r\n", setpoint);
        } else if (ch == '-') {
            setpoint = max(setpoint - step, minRPM);
            PIDControl_SetSetpoint(setpoint);
            printf("-Decreased SetPoint to: %d RPM\r\n", setpoint);
        }
    }

    // Run PID control loop periodically
    if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();

        int currentRPM = Tachometer_GetRPM();
        PIDControl_SetInput(currentRPM);
        double pidOutput = PIDControl_Compute();

        int pwmValue = (int)pidOutput;
        Motor_SetSpeed(pwmValue);


        // Motor_SetSpeed((int)pidOutput);

        printf("SetPoint: %d RPM, Measured: %d RPM, Output PWM: %d\r\n",
               setpoint, currentRPM, (int)pidOutput);

        float deviation = abs(currentRPM - setpoint);
        if (deviation > ALERT_THRESHOLD) {
            ledOn(LED_BUILTIN);  // Alert ON
        } else {
            ledOff(LED_BUILTIN);   // Alert OFF
        }

    }
}