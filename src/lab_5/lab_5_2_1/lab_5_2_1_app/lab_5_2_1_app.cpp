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
    printf("Fan PID Control Started \r\n");

    ledSetup();
    Motor_Init(FAN_PWM_PIN);
    Tachometer_Init(FAN_TACH_PIN);

    PIDControl_Init(0.5, 0.05, 0);
    PIDControl_SetSetpoint(1000); // Default RPM target
}

void lab_5_2_1_app_loop() {
    static unsigned long lastUpdate = 0; // Initialization of lastUpdate
    const unsigned long interval = 500; // Update interval in milliseconds
    static int setpoint = 1000; // Default setpoint RPM
    const int step = 50; //
    const int minRPM = 10;
    const int maxRPM = 2000;

    // Handle user input
    if (Serial.available()) { // Check if there is user input
        char ch; // Variable to store user input
        scanf(" %c", &ch); // Read a character from the serial input
        if (ch == '+') {
            setpoint = min(setpoint + step, maxRPM); // Increase setpoint by step, but not above maxRPM
            PIDControl_SetSetpoint(setpoint);// Set the new setpoint in the PID controller
            printf("+Increased SetPoint to: %d RPM\r\n", setpoint); // Print the new setpoint
        } else if (ch == '-') {
            setpoint = max(setpoint - step, minRPM); // Decrease setpoint by step, but not below minRPM
            PIDControl_SetSetpoint(setpoint);
            printf("-Decreased SetPoint to: %d RPM\r\n", setpoint);
        }
    }

    // Run PID control loop periodically
    if (millis() - lastUpdate >= interval) { // Check if the interval has passed
        lastUpdate = millis(); // Update lastUpdate to current time

        int currentRPM = Tachometer_GetRPM(); // Get the current RPM from the tachometer
        PIDControl_SetInput(currentRPM); // Set the current RPM as input to the PID controller
        double pidOutput = PIDControl_Compute(); // Compute the PID output based on the current RPM and setpoint

        int pwmValue = (int)pidOutput; // Convert PID output to PWM value
        Motor_SetSpeed(pwmValue); // Set the motor speed using the PWM value


        // Motor_SetSpeed((int)pidOutput);

        printf("SetPoint: %d RPM, Measured: %d RPM, Output PWM: %d\r\n",
               setpoint, currentRPM, (int)pidOutput);

        float deviation = abs(currentRPM - setpoint); // Calculate the deviation from the setpoint
        if (deviation > ALERT_THRESHOLD) {
            ledOn(LED_BUILTIN);  // Alert ON
        } else {
            ledOff(LED_BUILTIN);   // Alert OFF
        }

    }
}