/**
 *
 * @file pwm.cpp
 * @brief Control of 
 * @date 2023/10/10
 * @par GDIP Test Tube (Group D)
 *
 */

/**************************** LIB INCLUDES ******************************/

#include <Arduino.h>

/**************************** USER INCLUDES *****************************/

#include "wifi.hpp"
#include "kinematics.hpp"

/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/


/******************************* VARIABLES ******************************/

int servoPins[] = {2, 4, 5, 6, 7};
int servoNum = sizeof(servoPins) / sizeof(servoPins[0]);

float angleState[4];

/*************************** PUBLIC FUNCTIONS ***************************/

void pwm_setup(void) 
{
  for (int i = 0; i < servoNum; i++) 
  {
    ledcSetup(i, 50, 14); // PWM frequency: 50 Hz, resolution: 16 bits
    ledcAttachPin(servoPins[i], i); // Attach PWM channel to pin

  }
}

void pwm_write(int a, int b, int c, int w, int g)
{

  calculateServoAngles(wifi_get_slider_values().servo1,wifi_get_slider_values().servo2,wifi_get_slider_values().servo3,angleState[0],angleState[1],angleState[2],angleState[3]);

  ledcWrite(0, map(angleState[0], 0, 180, 520, 2036));
  ledcWrite(1, map(angleState[1]+20, 0, 180, 500, 1850));
  ledcWrite(2, map(angleState[2], 180, 0, 500, 1850));
  ledcWrite(3, map(angleState[3], 0, 180, 500, 1850));

}


/*************************** PRIVATE FUNCTIONS ***************************/