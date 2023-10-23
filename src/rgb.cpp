/**
 *
 * @file rgb.cpp
 * @brief Control of 
 * @date 2023/10/10
 * @par GDIP Test Tube (Group D)
 *
 */

/**************************** LIB INCLUDES ******************************/

//#include <Adafruit_NeoPixel.h>

/**************************** USER INCLUDES *****************************/

#include "wifi.hpp"
#include "rgb.hpp"

/******************************* DEFINES ********************************/

#define PIN        8
#define NUMPIXELS  1
#define DELAYVAL 100

/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/

//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int lastValue = 0;

/*************************** PUBLIC FUNCTIONS ***************************/

/*
void rgb_initialise(void)
{
    pixels.begin();
}

void rgb_select_colour(int pos)
{
  switch(pos)
  {
    case 0:
    {
      int value = wifi_get_slider_value();

      if (lastValue != value) 
      {
        Serial.println(value);
        lastValue = value;
      }

      pixels.clear();
      for(int i=0; i<NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(value, 0, 0));
        pixels.show(); 
        delay(DELAYVAL);
      }
      break;
    }

    case 1:
    {
      int value = wifi_get_slider_value();

      if (lastValue != value) 
      {
        Serial.println(value);
        lastValue = value;
      }

      pixels.clear();
      for(int i=0; i<NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, value, 0));
        pixels.show(); 
        delay(DELAYVAL);
      }
      break;
    }

    case 2:
    {
      int value = wifi_get_slider_value();

      if (lastValue != value) 
      {
        Serial.println(value);
        lastValue = value;
      }

      pixels.clear();
      for(int i=0; i<NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, value));
        pixels.show(); 
        delay(DELAYVAL);
      }
      break;
    }
  }
}
*/

/*************************** PRIVATE FUNCTIONS ***************************/








