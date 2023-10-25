/**
 *
 * @file main.c
 * @brief main
 * @date 2023/10/10
 * @par GDIP Test Tube (Group D)
 *
 */

/**************************** LIB INCLUDES ******************************/

#include <Arduino.h>

/**************************** USER INCLUDES *****************************/

#include "wifi.hpp"
#include "rgb.hpp"
#include "debug.hpp"

/******************************* DEFINES ********************************/



/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/


int servoPins[] = {2, 4, 5, 6, 7};
int servoNum = sizeof(servoPins) / sizeof(servoPins[0]);

servo_slider_values_t sliderValues;

// Published values for SG90 servos; adjust if needed


void pwm_setup(void);
void pwm_write(void);


/*************************** PUBLIC FUNCTIONS ***************************/

void setup() 
{
  debug_initialise();
  wifi_initialise();
  pwm_setup();
}


void loop() 
{
  pwm_write();
}

/*************************** PRIVATE FUNCTIONS ***************************/


void pwm_setup(void) {
  for (int i = 0; i < servoNum; i++) {
    ledcSetup(i, 50, 14); // PWM frequency: 50 Hz, resolution: 16 bits
    ledcAttachPin(servoPins[i], i); // Attach PWM channel to pin
  }
}


void pwm_write(void)
{
  // Serial.println(wifi_get_slider_values().servo1);

  ledcWrite(0, wifi_get_slider_values().servo1);
  ledcWrite(1, wifi_get_slider_values().servo2);
  ledcWrite(2, wifi_get_slider_values().servo3);
  ledcWrite(3, wifi_get_slider_values().servo4);
  ledcWrite(4, wifi_get_slider_values().servo5);

  // delay(10);
}







// #include <Arduino.h>

// const int numServos = 5;
// int servoPins[numServos] = {2, 4, 5, 6, 7};
// int minAngle = 60; // Minimum angle in degrees
// int maxAngle = 100; // Maximum angle in degrees
// int delayTime = 10; // Delay in milliseconds for each step
// int stepSize = 1; // Step size for sweeping

// void setup() {
//   for (int i = 0; i < numServos; i++) {
//     ledcSetup(i, 50, 14); // PWM frequency: 50 Hz, resolution: 16 bits
//     ledcAttachPin(servoPins[i], i); // Attach PWM channel to pin
//   }
// }

// void loop() {
//   for (int angle = minAngle; angle <= maxAngle; angle += stepSize) {
//     for (int i = 0; i < numServos; i++) {
//       int dutyCycle = map(angle, 0, 180, 500, 2500); // Map angle to PWM duty cycle
//       ledcWrite(i, dutyCycle);
//     }
//     delay(delayTime);
//   }
  
//   for (int angle = maxAngle; angle >= minAngle; angle -= stepSize) {
//     for (int i = 0; i < numServos; i++) {
//       int dutyCycle = map(angle, 0, 180, 500, 2500); // Map angle to PWM duty cycle
//       ledcWrite(i, dutyCycle);
//     }
//     delay(delayTime);
//   }
// }






