#include <Arduino.h>
#include "lab_1/lab_1_1/lab_1_1_app/lab_1_1_app.h"
#include "lab_1/lab_1_2/lab_1_2_app/lab_1_2_app.h"
#include "lab_2/lab_2_1/lab_2_1_app/lab_2_1_app.h"
#include "lab_2/lab_2_2/lab_2_2_app/lab_2_2_app.h"
#include "lab_3/lab_3_1/lab_3_1_app/lab_3_1_app.h"
#include "lab_3/lab_3_2/lab_3_2_app/lab_3_2_app.h"
#include "lab_4/lab_4_1/lab_4_1_app/lab_4_1_app.h"
#include "lab_4/lab_4_2/lab_4_2_app/lab_4_2_app.h"

#define LAB_1_1 11
#define LAB_1_2 12
#define LAB_2_1 21
#define LAB_2_2 22
#define LAB_3_1 31
#define LAB_3_2 32
#define LAB_4_1 41
#define LAB_4_2 42

#define APP_USED LAB_4_2



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
  #if APP_USED == LAB_2_2
    lab_2_2_app_setup();
  #endif
  #if APP_USED == LAB_3_1
    lab_3_1_app_setup();
  #endif
  #if APP_USED == LAB_3_2
    lab_3_2_app_setup();
  #endif
  #if APP_USED == LAB_4_1
  lab_4_1_app_setup();
#endif
#if APP_USED == LAB_4_2
    lab_4_2_app_setup();
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
  #if APP_USED == LAB_2_2
    lab_2_2_app_loop();
  #endif
  #if APP_USED == LAB_3_1
    lab_3_1_app_loop();
  #endif
  #if APP_USED == LAB_3_2
    lab_3_2_app_loop();
  #endif
  #if APP_USED == LAB_4_1
  lab_4_1_app_loop();
#endif
#if APP_USED == LAB_4_2
    lab_4_2_app_loop();
  #endif
}


