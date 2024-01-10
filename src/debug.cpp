/**
 *
 * @file debug.c
 * @brief Debug/Uart comms for device.
 * @date 2023/10/10
 * @par GDIP Test Tube (Group D)
 *
 */

/**************************** LIB INCLUDES ******************************/

#include <ArduinoLog.h>
#include <Arduino.h>

/**************************** USER INCLUDES *****************************/
/******************************* DEFINES ********************************/

#define DEBUG_LOG_TAG "debug.c"

#define TEMP_RX 17 
#define TEMP_TX 18

/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/
/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/
/*************************** PUBLIC FUNCTIONS ***************************/

void debug_initialise(void)
{
    Serial.begin(9600, SERIAL_8N1, TEMP_RX, TEMP_TX);
}

/*************************** PRIVATE FUNCTIONS ***************************/