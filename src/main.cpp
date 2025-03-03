#include <Arduino.h>
#include "lab_1/lab_1_1/lab_1_1_app/lab_1_1_app.h"
#include "lab_1/lab_1_2/lab_1_2_app/lab_1_2_app.h"
#include "lab_2/lab_2_1/lab_2_1_app/lab_2_1_app.h"

#define LAB_1_1 11
#define LAB_1_2 12
#define LAB_2_1 21

#define APP_USED LAB_2_1



void setup() {
  #if APP_USED == LAB_1_1
    lab_1_1_app_setup();
  #endif
  #if APP_USED == LAB_1_2
    lab_1_2_app_setup();
  #endif
  #if APP_USED == LAB_2_1
    lab_2_1_app_setup();
  #endif

}

void loop() {
  #if APP_USED == LAB_1_1
    lab_1_1_app_loop();
  #endif
  #if APP_USED == LAB_1_2
    lab_1_2_app_loop();
  #endif
  #if APP_USED == LAB_2_1
    lab_2_1_app_loop();
  #endif
}

