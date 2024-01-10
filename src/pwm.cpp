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

armServoAngles_t servoAngles;

/*************************** PUBLIC FUNCTIONS ***************************/

void pwm_setup(void) 
{
  for (int i = 0; i < servoNum; i++) 
  {
    ledcSetup(i, 50, 14); // PWM frequency: 50 Hz, resolution: 16 bits
    ledcAttachPin(servoPins[i], i); // Attach PWM channel to pin

  }
}

armServoAngles_t pwm_write(int a, int b, int c, bool wifiSelect)
{

  if(wifiSelect)
  {
      servoAngles = calculateServoAngles(wifi_get_latest_grid_position().x, wifi_get_latest_grid_position().y, wifi_get_latest_grid_position().x);

      ledcWrite(0, map(servoAngles.base, 0, 180, 520, 2036));
      ledcWrite(1, map(servoAngles.shoulder + 20, 0, 180, 500, 1850));
      ledcWrite(2, map(servoAngles.elbow, 180, 0, 500, 1850));

      if(wifi_get_latest_grid_position().gripper == true)
      {
        ledcWrite(3, map(180, 0, 180, 500, 1850));
      }
      else
      {
        ledcWrite(3, map(0, 0, 180, 500, 1850));
      }

    }
  else
  {
      servoAngles = calculateServoAngles(a, b, c);
      ledcWrite(0, map(servoAngles.base, 0, 180, 520, 2036));
      ledcWrite(1, map(servoAngles.shoulder + 20, 0, 180, 500, 1850));
      ledcWrite(2, map(servoAngles.elbow, 180, 0, 500, 1850));
      ledcWrite(3, map(servoAngles.gripper, 0, 180, 500, 1850));
  }



  return servoAngles;

}




/*************************** PRIVATE FUNCTIONS ***************************/