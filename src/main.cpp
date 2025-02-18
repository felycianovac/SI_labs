#include <Arduino.h>
#include "lab_1_1_app/lab_1_1_app.h"

#define APP_NAME LAB_1_1


void setup() {
  #if APP_NAME == LAB_1_1
    lab_1_1_app_setup();
  #endif
}

void loop() {
  #if APP_NAME == LAB_1_1
    lab_1_1_app_loop();
  #endif
}

