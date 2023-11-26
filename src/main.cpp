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
#include "kinematics.hpp"

/******************************* DEFINES ********************************/



/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/

float baseAngle, joint1Angle, joint2Angle;

int servoPins[] = {2, 4, 5, 6, 7};
int servoNum = sizeof(servoPins) / sizeof(servoPins[0]);

servo_slider_values_t sliderValues;

// Published values for SG90 servos; adjust if needed


void pwm_setup(void);
void pwm_write(double S1, double S2, double S3);


/*************************** PUBLIC FUNCTIONS ***************************/

void setup() 
{
  debug_initialise();
  wifi_initialise();
  pwm_setup();
}


void loop() 
{ 
  calculateIK(wifi_get_slider_values().servo1, wifi_get_slider_values().servo2, wifi_get_slider_values().servo3, baseAngle, joint1Angle, joint2Angle);
  pwm_write(baseAngle, joint1Angle, joint2Angle);
}

/*************************** PRIVATE FUNCTIONS ***************************/


void pwm_setup(void) {
  for (int i = 0; i < servoNum; i++) {
    ledcSetup(i, 50, 14); // PWM frequency: 50 Hz, resolution: 16 bits
    ledcAttachPin(servoPins[i], i); // Attach PWM channel to pin
  }
}


void pwm_write(double S1, double S2, double S3)
{
  // Serial.println("Ang");
  // Serial.println(S1);
  // Serial.println(S2);
  // Serial.println(S3);
  // Serial.println("\n");

  delay(100);

  ledcWrite(0, map(S1, 0, 180, 500, 2000));
  ledcWrite(1, map(S2, 0, 180, 500, 2000));
  ledcWrite(2, map(S3, 0, 180, 500, 2000));
  ledcWrite(3, map(wifi_get_slider_values().servo4, 0, 180, 500, 2000));
  ledcWrite(4, map(wifi_get_slider_values().servo5, 0, 180, 500, 2000));
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






