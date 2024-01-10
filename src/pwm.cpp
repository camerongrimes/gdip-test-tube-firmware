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
#include "smooth.hpp"
#include "kinematics.hpp"

/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/

/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/

int servoPins[] = {4, 5, 6, 2, 42};
int servoNum = sizeof(servoPins) / sizeof(servoPins[0]);

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


void pwm_write_test(armServoAngles_t servoAngle)
{
    ledcWrite(0, map(servoAngle.base, 0, 180, 520, 2036));
    ledcWrite(1, map(servoAngle.shoulder+15, 0, 180, 500, 1850));
    ledcWrite(2, map(servoAngle.elbow, 180, 0, 500, 1850));
    ledcWrite(3, map(servoAngle.wrist, 0, 180, 500, 1850));
}



armServoAngles_t pwm_write(int a, int b, int c, bool wifiSelect)
{

  
      char buffer[50];

      sprintf(buffer, "x: %d, y: %d, z: %d", a, b, c);

      wifi_send_message(buffer);

  if(wifiSelect)
  {

    // smoothMotion(wifi_get_latest_grid_position().x, wifi_get_latest_grid_position().y, wifi_get_latest_grid_position().z);

    servoAngles = calculateServoAngles(wifi_get_latest_grid_position().x, wifi_get_latest_grid_position().y, wifi_get_latest_grid_position().z);

      if(wifi_get_latest_grid_position().gripper == true)
      {
        ledcWrite(4, map(180, 0, 180, 500, 1850));
      }
      else
      {
        ledcWrite(4, map(0, 0, 180, 500, 1850));
      }
  }
  else
  {
      // smoothMotion(wifi_get_latest_grid_position().x, wifi_get_latest_grid_position().y, wifi_get_latest_grid_position().z);

      servoAngles = calculateServoAngles(wifi_get_latest_grid_position().x, wifi_get_latest_grid_position().y, wifi_get_latest_grid_position().z);
  }

  // pwm_write_test(servoAngles);
 
  return servoAngles;

}




/*************************** PRIVATE FUNCTIONS ***************************/