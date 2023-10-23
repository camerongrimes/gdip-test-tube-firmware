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

#define SERVO_1_PWM 2
#define SERVO_2_PWM 3
#define SERVO_3_PWM 0
#define SERVO_4_PWM 1
#define SERVO_5_PWM 6
#define SERVO_6_PWM 5

/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/

int led = 6;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

servo_slider_values_t sliderValues;

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


void pwm_setup(void)
{

    pinMode(SERVO_1_PWM, OUTPUT);  // sets the pin as output

    pinMode(SERVO_2_PWM, OUTPUT);  // sets the pin as output

    pinMode(SERVO_3_PWM, OUTPUT);  // sets the pin as output

    pinMode(SERVO_4_PWM, OUTPUT);  // sets the pin as output

    pinMode(SERVO_5_PWM, OUTPUT);  // sets the pin as output

  /*
    ledcSetup(0, 5000, 8); // Configure PWM channel, frequency, and resolution
    ledcAttachPin(SERVO_1_PWM, 0); // Attach the channel to the pin

    ledcSetup(1, 5000, 8); // Configure PWM channel, frequency, and resolution
    ledcAttachPin(SERVO_2_PWM, 1); // Attach the channel to the pin

    ledcSetup(2, 5000, 8); // Configure PWM channel, frequency, and resolution
    ledcAttachPin(SERVO_3_PWM, 2); // Attach the channel to the pin

    ledcSetup(3, 5000, 8); // Configure PWM channel, frequency, and resolution
    ledcAttachPin(SERVO_4_PWM, 3); // Attach the channel to the pin

    ledcSetup(4, 5000, 8); // Configure PWM channel, frequency, and resolution
    ledcAttachPin(SERVO_5_PWM, 4); // Attach the channel to the pin

    ledcSetup(5, 5000, 8); // Configure PWM channel, frequency, and resolution
    ledcAttachPin(SERVO_6_PWM, 5); // Attach the channel to the pin
    */

}

void pwm_write(void)
{
  analogWrite(SERVO_1_PWM, wifi_get_slider_values().servo1);

  analogWrite(SERVO_2_PWM, wifi_get_slider_values().servo2*2.55);

  analogWrite(SERVO_3_PWM, wifi_get_slider_values().servo3*2.55);

  analogWrite(SERVO_4_PWM, wifi_get_slider_values().servo4*2.55);

  analogWrite(SERVO_5_PWM, wifi_get_slider_values().servo5*2.55);

}

