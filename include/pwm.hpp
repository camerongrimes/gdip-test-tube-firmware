/**
 *
 * @file pwm.hpp
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
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/

void pwm_setup(void);
void pwm_write(int a, int b, int c, bool wifiSelect);
void pwm_write_test(armServoAngles_t servoAngle);
/******************************* GLOBALS ********************************/
/* Globals are to be avoided unless justified and documented */
/************************************************************************/