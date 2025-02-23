#include <Arduino.h>
#include "lab_1/lab_1_1/lab_1_1_app/lab_1_1_app.h"
#include "lab_1/lab_1_2/lab_1_2_app/lab_1_2_app.h"

#define APP_NAME LAB_1_2


void setup() {
  #if APP_NAME == LAB_1_1
    lab_1_1_app_setup();
  #endif
  #if APP_NAME == LAB_1_2
    lab_1_2_app_setup();
  #endif
}

void loop() {
  #if APP_NAME == LAB_1_1
    lab_1_1_app_loop();
  #endif
  #if APP_NAME == LAB_1_2
    lab_1_2_app_loop();
  #endif
}

