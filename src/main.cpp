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


/*************************** PUBLIC FUNCTIONS ***************************/




// Array to store the values
int valuesServo[5];

void setup() 
{
  debug_initialise();
  wifi_initialise();
  pwm_setup();
 // wifi_test_grid_pos();

  

}



void loop() 
{ 
  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the input string
    String inputString = Serial.readStringUntil('\n');

    // Use a temporary variable for parsing
    String tempString;
    int index = 0;

    // Parse the input string and store values in the array
    for (int i = 0; i < inputString.length(); i++) {
      char c = inputString.charAt(i);

      // Check for space or newline to separate values
      if (c == ' ' || c == '\n') {
        // Convert the temporary string to an integer and store in the array
        valuesServo[index] = tempString.toInt();

        // Clear the temporary string for the next value
        tempString = "";

        // Move to the next index in the array
        index++;

        // Break the loop if we have read all values
        if (index >= 5) {
          break;
        }
      } else {
        // Append the character to the temporary string
        tempString += c;
      }
    }

    // Print the values to Serial for verification
    for (int i = 0; i < 5; i++) 
    {
      Serial.println(valuesServo[i]);
    }

    pwm_write(valuesServo[0], valuesServo[1], valuesServo[2], valuesServo[3], valuesServo[4]);

  }
    //state_machine(wifi_get_cmd_state());
   // delay(10);
}

/*************************** PRIVATE FUNCTIONS ***************************/

userPrograms_t recoredPrograms;



void state_machine(wifi_cmd_state_t state)
{
  switch(state)
  {
    case PARK:
    {


      delay(5000);

      wifi_set_cmd_state(STEADY_STATE);

      break;
    }

    case START_RECORD:
    {

      Serial.println("START");
      Serial.println("Starting recording starting with arm parked.");

      //program_state_machine(PROGRAM_ONE, wifi_get_latest_grid_position(), PROGRAM_START);

      wifi_set_cmd_state(STEADY_STATE);


      break;
    }

    
    case RECORD:
    {

     // program_state_machine(PROGRAM_ONE, wifi_get_latest_grid_position(), PROGRAM_RECORD);

      wifi_set_cmd_state(STEADY_STATE);

      break;
    }
    

    case END_RECORD:
    {

      //program_state_machine(PROGRAM_ONE, wifi_get_latest_grid_position(), PROGRAM_END);

      wifi_set_cmd_state(STEADY_STATE);

      break;
    }

    case USER_INPUT:
    {
      
      //Serial.printf("USER_INPUT: %s\n", wifi_get_user_input_text());

      if(wifi_get_user_input_text() == "PROG1 PLAY")
      {
       // program_state_machine(PROGRAM_ONE, wifi_get_latest_grid_position(), PROGRAM_PLAY);  
      }

      wifi_set_cmd_state(STEADY_STATE);

      break;

    }

    case STEADY_STATE:
    {
      wifi_test_grid_pos();
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


