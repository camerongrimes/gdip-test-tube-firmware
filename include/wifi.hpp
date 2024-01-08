/**
 *
 * @file wifi.hpp
 * @brief UART for serial debug.
 * @date 2023/10/10
 * @par GDIP Test Tube (Group D)
 *
 */


/**************************** LIB INCLUDES ******************************/
/**************************** USER INCLUDES *****************************/
/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/****************************** TYPEDEFS ********************************/

typedef struct 
{

    int servo1 = 0;
    int servo2 = 100;
    int servo3 = 150;
    int servo4;
    int servo5;
    int servo6;

}servo_slider_values_t;

/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/

void wifi_initialise();
int wifi_get_colour_select(void);
int wifi_get_slider_value(void);
servo_slider_values_t wifi_get_slider_values(void);

/******************************* GLOBALS ********************************/
/* Globals are to be avoided unless justified and documented */
/************************************************************************/