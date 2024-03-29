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
#include "cmds.hpp"
#include "kinematics.hpp"
#include "program.hpp"
#include "pwm.hpp"
#include "misc.hpp"
#include "sevenseg.hpp"
#include "smooth.hpp"

/******************************* DEFINES ********************************/
/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/
/************************** FUNCTION PROTOTYPES *************************/


void pwm_set_test_range(int channel, int stepTime, int startingAngle, int endAngle);
void pwm_test_full_range(int channel);
void wait_check_for_commands(void);
void wifi_test_grid_pos(void);
void state_machine(wifi_cmd_state_t state);


/******************************* CONSTANTS ******************************/
/******************************* VARIABLES ******************************/

uint32_t commandIndex;
uint32_t programLength;
double values[5] = {90, 90, 90, 90, 90};  // Assuming there are 5 values in the command
String command;

armPositionData_t armStateXYZ;

/*************************** PUBLIC FUNCTIONS ***************************/


void setup() 
{
  sevenseg_initialise();
  debug_initialise();
  wifi_initialise();
  pwm_setup();

  sevenseg_display_char('R');

  armStateXYZ = wifi_get_latest_grid_position();

}

void loop() 
{
    state_machine(wifi_get_cmd_state());

   // 
    
    delay(10);
}


/*************************** PRIVATE FUNCTIONS ***************************/

userPrograms_t recoredPrograms;



void state_machine(wifi_cmd_state_t state)
{
  switch(state)
  {
    case PARK:
    {
      
      armPositionData_t park =
      {
        .x = 0,
        .y = 150,
        .z = 200,
      };

      wifi_set_latest_grid_position(park);

      smoothMotion();

      pwm_write(wifi_get_latest_grid_position().x, wifi_get_latest_grid_position().y,
                wifi_get_latest_grid_position().z, false);

      wifi_set_cmd_state(STEADY_STATE);



      wifi_send_message("READY");

      break;
    }

    case START_RECORD:
    {

      Serial.println("START");
      Serial.println("Starting recording starting with arm parked.");

      program_state_machine(PROGRAM_ONE, wifi_get_latest_grid_position(), PROGRAM_START);

      wifi_set_cmd_state(STEADY_STATE);

      wifi_send_message("START RECORDING");


      break;
    }

    
    case RECORD:
    {

      program_state_machine(PROGRAM_ONE, wifi_get_latest_grid_position(), PROGRAM_RECORD);

      wifi_set_cmd_state(STEADY_STATE);

      wifi_send_message("RECORD");

      break;
    }
    

    case END_RECORD:
    {

      program_state_machine(PROGRAM_ONE, wifi_get_latest_grid_position(), PROGRAM_END);

      wifi_set_cmd_state(STEADY_STATE);

      wifi_send_message("END RECORD");

      break;
    }

    case USER_INPUT:
    {
      
      
      Serial.printf("USER_INPUT: %s\n", wifi_get_user_input_text());
 
      if(wifi_get_user_input_text() == "PROG1 PLAY")
      {

        for(int index = 0; index < 4; index++)
        {
          sevenseg_display_char('P');
          delay(500);
          sevenseg_display_number(1);
          delay(500);
        }

        sevenseg_clear();

        wifi_send_message("MOVING");

        program_state_machine(PROGRAM_ONE, wifi_get_latest_grid_position(), PROGRAM_PLAY);  

        wifi_send_message("READY");


      }
      else if(wifi_get_user_input_text() == "GODFATHER")
      {
        sevenseg_display_char('F');
        misc_play_song();
      }
      else
      {
        sevenseg_display_char('E');
      }

      
      wifi_set_cmd_state(STEADY_STATE);

      break;

    }

    case STEADY_STATE:
    {

      smoothMotion();

      pwm_write(wifi_get_latest_grid_position().x, wifi_get_latest_grid_position().y,
                wifi_get_latest_grid_position().z, false);
  
      break;
    }

    default:
    {
      break;
    }
  }
}













void wait_check_for_commands(void)
{
    // Check if there is data available to read
  if (Serial.available() > 0) {
    // Read the incoming data
    command = Serial.readStringUntil('\n');
    
    // Print the received command
    Serial.print("Received command: ");
    Serial.println(command);

    // Split the command into individual numbers
    int count = sscanf(command.c_str(), "%lf %lf %lf %lf %lf", &values[0], &values[1], &values[2], &values[3], &values[4]);


   // pwm_write(calculatedAngles.base, calculatedAngles.humerus, calculatedAngles.ulna);
  }
}


