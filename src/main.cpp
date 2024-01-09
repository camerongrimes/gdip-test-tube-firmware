/**
 *
 * @file main.c
 * @brief main
 * @date 2023/10/10
 * @par GDIP Test Tube (Group D)
 *
 */

/****************************** INCLUDES ********************************/

#include <Arduino.h>
#include <math.h>

#include "wifi.hpp"
#include "inverseKinematics.hpp"

servo_slider_values_t sliderValues;

int servoPins[] = {4, 5, 6, 2, 42};
int numOfPins = 5;

float angleState[] = {90,90,90,45};
float xyzState[] = {0,50,250};
float xyzTarget[] = {200,50,250};

void pwm_setup(void);
void pwm_write(void);
// void calculateServoAngles(float x, float y, float z, float &baseAngle, float &shoulderAngle, float &elbowAngle, float &handAngle);
// void smoothTranslate(float XZY[3]);

void setup() 
{
  Serial.begin(115200);
  while(!Serial);

  wifi_initialise();
  pwm_setup();
}


void loop() 
{
  // smoothTranslate(xyzTarget);
  pwm_write();
}


void pwm_setup(void) {
  for (int i = 0; i < numOfPins; i++) {
    ledcSetup(i, 50, 14); // PWM frequency: 50 Hz, resolution: 14 bits
    ledcAttachPin(servoPins[i], i); // Attach PWM channel to pin
  }
}

void pwm_write(void)
{
  calculateServoAngles(wifi_get_slider_values().servo1,wifi_get_slider_values().servo2,wifi_get_slider_values().servo3,angleState[0],angleState[1],angleState[2],angleState[3]);
  // calculateServoAngles(xyzState[0],xyzState[1],xyzState[2],angleState[0],angleState[1],angleState[2],angleState[3]);

  Serial.print(wifi_get_slider_values().servo1);
  Serial.print(" : ");
  Serial.print(wifi_get_slider_values().servo2);
  Serial.print(" : ");
  Serial.println(wifi_get_slider_values().servo3);


  ledcWrite(0, map(angleState[0], 0, 180, 520, 2036));
  ledcWrite(1, map(angleState[1], 0, 180, 500, 1850));
  ledcWrite(2, map(angleState[2], 180, 0, 500, 1850));
  ledcWrite(3, map(angleState[3], 0, 180, 500, 1850));

  // ledcWrite(0, map(wifi_get_slider_values().servo1, 0, 180, 520, 2036));
  // ledcWrite(1, map(wifi_get_slider_values().servo2, 0, 180, 500, 1850));
  // ledcWrite(2, map(wifi_get_slider_values().servo3, 0, 180, 500, 1850));
  // ledcWrite(3, map(wifi_get_slider_values().servo4, 0, 180, 500, 1850));
  // ledcWrite(4, map(wifi_get_slider_values().servo5, 0, 180, 520, 2036));
}

// // Function to calculate servo angles from XYZ position
// void calculateServoAngles(float x, float y, float z, float &baseAngle, float &shoulderAngle, float &elbowAngle, float &handAngle) {
//   //Define linkage lengths
//   float L1 = 193.0;
//   float L2 = 250.0;
//   // Calculate angle at base joint (rotation in XY plane)
//   baseAngle = atan2(y, x) * 180.0 / M_PI;
//   // Calculate the distance to the desired end effector position in 3D space
//   float distanceXYZ = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

//   shoulderAngle = (acos((pow(L1, 2) + pow(distanceXYZ, 2) - pow(L2, 2)) / (2 * L1 * distanceXYZ)) + asin(z/distanceXYZ)) * 180.0 / M_PI;

//   elbowAngle = (acos((pow(L1, 2) - pow(distanceXYZ, 2) + pow(L2, 2)) / (2 * L1 * L2))) * 180.0 / M_PI;

//   handAngle = 270 - (shoulderAngle + elbowAngle + 45);
// }

// void smoothTranslate(float XYZ[3]) {
//   float diffX = abs(XYZ[0] - xyzState[0]);
//   float diffY = abs(XYZ[1] - xyzState[1]);
//   float diffZ = abs(XYZ[2] - xyzState[2]);
//   float steps = max(max(diffX, diffY), diffZ);

//   if (steps != 0)
//   {
//     Serial.print("Step info: ");
//     Serial.print(steps);
//     Serial.print(" : ");

//     float stepX = (XYZ[0] - xyzState[0]) / (steps - 1);
//     float stepY = (XYZ[1] - xyzState[1]) / (steps - 1);
//     float stepZ = (XYZ[2] - xyzState[2]) / (steps - 1);

//     Serial.print(stepX);
//     Serial.print(" : ");
//     Serial.print(stepY);
//     Serial.print(" : ");
//     Serial.println(stepZ);

//     for (size_t i = 0; i < steps; i++)
//     {
//       xyzState[0] = xyzState[0] + stepX;
//       xyzState[1] = xyzState[1] + stepY;
//       xyzState[2] = xyzState[2] + stepZ;

//       Serial.print("Slow move info: ");
//       Serial.print(xyzState[0]);
//       Serial.print(" : ");
//       Serial.print(xyzState[1]);
//       Serial.print(" : ");
//       Serial.println(xyzState[2]);

//       pwm_write();

//       delay(10);
//     }
//   } 

// }