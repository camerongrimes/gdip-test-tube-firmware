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

/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/

/******************************* VARIABLES ******************************/

int servoPins[] = {2, 4, 5, 6, 7};
int servoNum = sizeof(servoPins) / sizeof(servoPins[0]);

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

  ledcWrite(0, map(a, 0, 180, 500, 2000));
  ledcWrite(1, map(b, 0, 180, 500, 2000));
  ledcWrite(2, map(c, 0, 180, 500, 2000));
  ledcWrite(3, map(w, 0, 180, 500, 2000));
  ledcWrite(4, map(g, 0, 180, 500, 2000));

}


/*************************** PRIVATE FUNCTIONS ***************************/