/**
 *
 * @file wifi.c
 * @brief main
 * @date 2023/10/10
 * @par GDIP Test Tube (Group D)
 *
 */

/**************************** LIB INCLUDES ******************************/

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"

/**************************** USER INCLUDES *****************************/

#include "wifi.hpp"
#include "kinematics.hpp"

/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/

const char* ssid = "ARM";
const char* password = "12345678";

/******************************* VARIABLES ******************************/

AsyncWebServer server(80);

int wifiSliderValue = 0;
int wifiColourSelect = 0;

servo_slider_values_t servoSliderValues;

wifi_cmd_state_t state = STEADY_STATE;

String userText;

/*************************** PUBLIC FUNCTIONS ***************************/

void wifi_initialise()
{
  // Set Wi-Fi mode to AP mode
  WiFi.mode(WIFI_AP);

  // Configure ESP32 to act as an AP
  WiFi.softAP(ssid, password);

  // Obtain and print the ESP32's IP address
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("IP address: ");
  Serial.println(apIP);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Serve HTML page from SPIFFS
  server.onNotFound([](AsyncWebServerRequest *request)
{
  // Serve the HTML page when the client accesses any path
  request->send(SPIFFS, "/index.html", "text/html");
});

  // Handle AJAX request to check for changes
  server.on("/check", HTTP_GET, [](AsyncWebServerRequest *request)
  {
  
    // Implement your logic to check for changes here
    // For demonstration purposes, we'll return a static message
    //request->send(200, "text/plain", "No changes yet.");
  
  });

  // Handle AJAX request to update the slider value
  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    
    if (request->hasParam("value")) 
    {

      switch(request->getParam("servo")->value().toInt())
      {

        case 1:
        {

          int sliderValue = request->getParam("value")->value().toInt();
          // Output the slider value over UART

          servoSliderValues.servo1 = sliderValue;

          Serial.printf("Grid position: %.2f %.2f %.2f\n", servoSliderValues.servo1, servoSliderValues.servo2, servoSliderValues.servo3);

          break;
        }

        case 2:
        {

          int sliderValue = request->getParam("value")->value().toInt();

          servoSliderValues.servo2 = sliderValue;

          Serial.printf("Grid position: %.2f %.2f %.2f\n", servoSliderValues.servo1, servoSliderValues.servo2, servoSliderValues.servo3);

          
          break;
        }

        case 3:
        {
          int sliderValue = request->getParam("value")->value().toInt();

          servoSliderValues.servo3 = sliderValue;

          Serial.printf("Grid position: %.2f %.2f %.2f\n", servoSliderValues.servo1, servoSliderValues.servo2, servoSliderValues.servo3);

          break;
        }

        case 4:
        {
          Serial.println("Slider 4");
          int sliderValue = request->getParam("value")->value().toInt();
          Serial.print("Slider Value: ");
          Serial.println(sliderValue);

          servoSliderValues.servo4 = sliderValue;

          break;
        }

        case 5:
        {
          Serial.println("Slider 5");
          int sliderValue = request->getParam("value")->value().toInt();
          Serial.print("Slider Value: ");
          Serial.println(sliderValue);

          servoSliderValues.servo5 = sliderValue;

          break;
        }

        case 6:
        {
          Serial.println("Slider 6");
          int sliderValue = request->getParam("value")->value().toInt();
          Serial.print("Slider Value: ");
          Serial.println(sliderValue);

          servoSliderValues.servo6 = sliderValue;

          break;
        }

        default:
        {
          /* Do nothing*/
          break;
        }

      }

    }
    
    request->send(200, "text/plain", "OK");

  });

  
  server.on("/button_click_park_arm", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    // Your code to handle the button click should go here
    // For demonstration purposes, let's just turn on an LED on pin 13
    Serial.println("Parking ARM, changing state");

    state = PARK;

    // Respond to the client
    request->send(200, "text/plain", "Button Clicked");
  });


  server.on("/button_click_start_record", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    // Your code to handle the button click should go here
    // For demonstration purposes, let's just turn on an LED on pin 13
    state = START_RECORD;
    
    // Respond to the client
    request->send(200, "text/plain", "Button Clicked");
  });


  server.on("/button_click_record", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    // Your code to handle the button click should go here
    // For demonstration purposes, let's just turn on an LED on pin 13
    state = RECORD;
    
    // Respond to the client
    request->send(200, "text/plain", "Button Clicked");
  });

    server.on("/button_click_end_record", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    // Your code to handle the button click should go here
    // For demonstration purposes, let's just turn on an LED on pin 13
    state = END_RECORD;
    
    // Respond to the client
    request->send(200, "text/plain", "Button Clicked");
  });


    // Handle AJAX request to send user input to ESP32
  server.on("/send_input", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    if (request->hasParam("text")) 
    {
      
      userText = request->getParam("text")->value();

      state = USER_INPUT;

      // Display the user input on the ESP32's UART
      Serial.print("User Input: ");
      Serial.println(userText);
      request->send(200, "text/plain", "Input received" + userText);
    } 
    else 
    {
      request->send(400, "text/plain", "Bad Request");
    }
  });

  // Start server
  server.begin();

}


 armPositionData_t  wifi_get_latest_grid_position(void)
 {
    armPositionData_t data;

    data.x = servoSliderValues.servo1;
    data.y = servoSliderValues.servo2;
    data.z = servoSliderValues.servo3;
    data.wristAngle = servoSliderValues.servo4;
    data.gripAngle = servoSliderValues.servo5;

    return data;

 }

int wifi_get_slider_value(void)
{
    return wifiSliderValue;
}

int wifi_get_colour_select(void)
{
    return wifiColourSelect;
}


servo_slider_values_t wifi_get_slider_values(void)
{
  return servoSliderValues;
}

wifi_cmd_state_t wifi_get_cmd_state(void)
{
  return state;
}


void wifi_set_cmd_state(wifi_cmd_state_t updatedState)
{
  state = updatedState;
}

String wifi_get_user_input_text(void)
{
  return userText;
}


/*************************** PRIVATE FUNCTIONS ***************************/




