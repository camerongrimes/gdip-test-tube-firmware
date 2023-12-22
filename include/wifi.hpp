/**
 *
 * @file wifi.hpp
 * @brief UART for serial debug.
 * @date 2023/10/10
 * @par GDIP Test Tube (Group D)
 *
 */


/**************************** LIB INCLUDES ******************************/

#include <Arduino.h>

/**************************** USER INCLUDES *****************************/

#include "kinematics.hpp"

/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/

typedef enum
{

    PARK,
    START_RECORD,
    RECORD,
    END_RECORD,
    USER_INPUT,
    STEADY_STATE,

}wifi_cmd_state_t;

/****************************** TYPEDEFS ********************************/

typedef struct 
{

    float servo1 = 33;
    float servo2 = 231;
    float servo3 = 295;
    float servo4 = 90;
    float servo5 = 90;
    float servo6 = 90;

}servo_slider_values_t;

/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/

void wifi_initialise();
int wifi_get_colour_select(void);
int wifi_get_slider_value(void);

servo_slider_values_t wifi_get_slider_values(void);

wifi_cmd_state_t wifi_get_cmd_state(void);
void wifi_set_cmd_state(wifi_cmd_state_t updatedState);

armPositionData_t wifi_get_latest_grid_position(void);

String wifi_get_user_input_text(void);

/******************************* GLOBALS ********************************/
/* Globals are to be avoided unless justified and documented */
/************************************************************************/