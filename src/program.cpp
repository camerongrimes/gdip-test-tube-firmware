/**
 *
 * @file program.cpp
 * @brief main
 * @date 2023/10/10
 * @par GDIP Test Tube (Group D)
 *
 */

/**************************** LIB INCLUDES ******************************/

#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**************************** USER INCLUDES *****************************/

#include "program.hpp"
#include "kinematics.hpp"
#include "debug.hpp"
#include "pwm.hpp"

/******************************* DEFINES ********************************/

#define CMD_START_POSITION   0

#define CMD_INDEX_ARRAY_SIZE 0

#define CMD_INDEX_PROG_ONE   0
#define CMD_INDEX_PROG_TWO   1
#define CMD_INDEX_PROG_THREE 2
#define CMD_INDEX_PROG_FOUR  3
#define CMD_INDEX_PROG_FIVE  4

#define DONT_RESET           false
#define RESET                true

/******************************** ENUMS *********************************/
/***************************** STRUCTURES *******************************/

typedef struct
{

    program_t PROG1;
    program_t PROG2;
    program_t PROG3;
    program_t PROG4;
    program_t PROG5;
    int usedCommands;

}program_bank_t;

/************************** FUNCTION PROTOTYPES *************************/

static void store_command(program_t *program, armPositionData_t currentGridPosition, uint8_t cmdIndex);
static programError_t check_and_record_command(program_t *prog, armPositionData_t currentGridPosition, uint8_t cmdIndex);
static programError_t save(program_t *program);
static programError_t clear(program_t *program);
static void increment_cmd_position(programName_t name, bool reset);
static uint8_t get_cmd_position(programName_t name);

/******************************* CONSTANTS ******************************/

const armPositionData_t parkingPosition = { .x = 33.0f, .y = 231.37f, .z = 295.0f };

/******************************* VARIABLES ******************************/

programState_t programState;

program_bank_t programBank;

uint8_t cmdIndexStateMachine = 0;

uint8_t programCmdCount[CMD_INDEX_ARRAY_SIZE];

/*************************** PUBLIC FUNCTIONS ***************************/


/**
 *
 * @brief program state machine.

 * @return n/a
 *
 * @note n/a
 *
 */

programError_t program_state_machine(programName_t name, armPositionData_t gridPosition, programState_t state)
{

    programError_t status = error;
    programState = state;

    switch ( state )
    {

        case PROGRAM_START:
        {


            Serial.printf("PROGRAM_START\n");

            program_delete(name);

            /* Moved to parked position */
            status = program_record_position(gridPosition, name, get_cmd_position(name));

            /* Once parked positon has been recorded allow user to record there positions */
            increment_cmd_position(name, DONT_RESET);

            break;

        }

        case PROGRAM_RECORD:
        {

            Serial.printf("PROGRAM_RECORD\n");

            status = program_record_position(gridPosition, name, get_cmd_position(name));

            increment_cmd_position(name, DONT_RESET);

            break;

        }

        case PROGRAM_END:
        {

            Serial.printf("PROGRAM_END\n");

            status = program_save(name);

            increment_cmd_position(name, RESET);

            break;

        }

        case PROGRAM_PLAY:
        {

            Serial.printf("PROGRAM_PLAY\n");

            program_play(name);

            break;

        }

        case PROGRAM_DELETE:
        {
            Serial.printf("PROGRAM_DELETE\n");

            increment_cmd_position(name, RESET);

            program_delete(name);

            break;
        }

        default:
        {
            /* Do nothing */
        }



    }

    return status;

}


/**
 *
 * @brief program record machine.

 * @return n/a
 *
 * @note n/a
 *
 */

programError_t program_record_position(armPositionData_t currentGridPosition, programName_t name, uint8_t commandIndex)
{

    programError_t status = error;

    switch (name)
    {
        case PROGRAM_ONE:
        {
            status = check_and_record_command(&programBank.PROG1, currentGridPosition, commandIndex);
            break;
        }

        case PROGRAM_TWO:
        {
            status = check_and_record_command(&programBank.PROG2, currentGridPosition, commandIndex);
            break;
        }

        case PROGRAM_THREE:
        {
            status = check_and_record_command(&programBank.PROG3, currentGridPosition, commandIndex);
            break;
        }

        case PROGRAM_FOUR:
        {
            status = check_and_record_command(&programBank.PROG4, currentGridPosition, commandIndex);
            break;
        }

        case PROGRAM_FIVE:
        {
            status = check_and_record_command(&programBank.PROG5, currentGridPosition, commandIndex);
            break;
        }
    }

    return status;

}


/**
 *
 * @brief program record machine.

 * @return n/a
 *
 * @note n/a
 *
 */

programError_t program_save(programName_t name)
{
    programError_t status = error;

    switch (name)
    {
        case PROGRAM_ONE:
        {
            save(&programBank.PROG1);
            break;
        }

        case PROGRAM_TWO:
        {
            save(&programBank.PROG2);
            break;
        }

        case PROGRAM_THREE:
        {
            save(&programBank.PROG3);
            break;
        }

        case PROGRAM_FOUR:
        {
            save(&programBank.PROG4);
            break;
        }

        case PROGRAM_FIVE:
        {
            save(&programBank.PROG5);
            break;
        }
    }

    return status;
}


/**
 *
 * @brief program play.

 * @return n/a
 *
 * @note n/a
 *
 */

programError_t program_play(programName_t name)
{

    switch (name)
    {
        case PROGRAM_ONE:
        {

            Serial.printf("\nProgram 1\n");

            for(int commandIndex = 0; commandIndex <= programBank.PROG1.usedCommands; commandIndex++)
            {

                armPositionData_t testPacket;
                armServoAngles_t calculatedAngles;

                calculatedAngles = set_arm_position(programBank.PROG1.positions[commandIndex]);

                pwm_write(calculatedAngles.base, calculatedAngles.shoulder, calculatedAngles.elbow, programBank.PROG1.positions[commandIndex].wristAngle, programBank.PROG1.positions[commandIndex].gripAngle);

                Serial.printf("Command [%d]: [x]: %.2f; [y]: %.2f; [z]: %.2f\n", 
                commandIndex,
                programBank.PROG1.positions[commandIndex].x,
                programBank.PROG1.positions[commandIndex].y,
                programBank.PROG1.positions[commandIndex].z);

                delay(1000);
            }

            break;
        }
    }

    return success;

}


programError_t program_delete(programName_t name)
{
    programError_t status = error;

    switch (name)
    {
        case PROGRAM_ONE:
        {
            clear(&programBank.PROG1);
            break;
        }

        case PROGRAM_TWO:
        {
            clear(&programBank.PROG2);
            break;
        }

        case PROGRAM_THREE:
        {
            clear(&programBank.PROG3);
            break;
        }

        case PROGRAM_FOUR:
        {
            clear(&programBank.PROG4);
            break;
        }

        case PROGRAM_FIVE:
        {
            clear(&programBank.PROG5);
            break;
        }
    }

    return status;
}

/*************************** PRIVATE FUNCTIONS **************************/


/**
 *
 * @brief save program.

 * @return n/a
 *
 * @note n/a
 *
 */

static programError_t save(program_t *program)
{

    programError_t status = error;

    program->programSaved = true;

    return success;


}


static programError_t clear(program_t *program)
{

    programError_t status;

    program->programSaved = false;
    program->usedCommands = CMD_START_POSITION;

    for(uint8_t index = 0; index < MAX_CMDS; index++)
    {
        program->positions->x = 0;
        program->positions->y = 0;
        program->positions->z = 0;
        program->positions->wristAngle = 0;
        program->positions->gripAngle = 0;
    }

    status = success;

    return status;

}


/**
 *
 * @brief save program.

 * @return n/a
 *
 * @note n/a
 *
 */

static programError_t check_and_record_command(program_t *program, armPositionData_t currentGridPosition, uint8_t cmdIndex)
{

    programError_t status = error;

    if(cmdIndex > MAX_CMDS || program->programSaved == true)
    {
        /* Checks if over MAX_CMDS or if this program has already been filled. */
        status = error;
    }
    else
    {
        if(cmdIndex == CMD_START_POSITION)
        {
            /* For better repeatability we make sure that each program starts at a parked position. */

            store_command(program, parkingPosition, cmdIndex);

            status = success;
        }
        else
        {
            /* Else start adding commands to the program, these will be from the user input. */

            store_command(program, currentGridPosition, cmdIndex);

            status = success;
        }
    }

    return status;

}


/**
 *
 * @brief save program.

 * @return n/a
 *
 * @note n/a
 *
 */

static void store_command(program_t *program, armPositionData_t currentGridPosition, uint8_t cmdIndex)
{

    program->usedCommands = cmdIndex;
    program->positions[cmdIndex].x = currentGridPosition.x;
    program->positions[cmdIndex].y = currentGridPosition.y;
    program->positions[cmdIndex].z = currentGridPosition.z;
    program->positions[cmdIndex].wristAngle = currentGridPosition.wristAngle;
    program->positions[cmdIndex].gripAngle = currentGridPosition.gripAngle;

    Serial.printf("[store_command]: [cmdIndex: %d], [x: %.2f], [y: %.2f], [z: %.2f], [wristAngle: %.2f], [gripAngle: %.2f]\n", program->usedCommands,
                                                                                                                               program->positions[cmdIndex].x,
                                                                                                                               program->positions[cmdIndex].y,
                                                                                                                               program->positions[cmdIndex].z,
                                                                                                                               program->positions[cmdIndex].wristAngle,
                                                                                                                               program->positions[cmdIndex].gripAngle);

}


/**
 *
 * @brief save program.

 * @return n/a
 *
 * @note n/a
 *
 */

static void increment_cmd_position(programName_t name, bool reset)
{
    switch (name)
    {
        case PROGRAM_ONE:
        {

            if(reset == true)
            {
                programCmdCount[CMD_INDEX_PROG_ONE] = CMD_START_POSITION;
            }
            else
            {
                programCmdCount[CMD_INDEX_PROG_ONE]++;

            }

            break;
        }

        case PROGRAM_TWO:
        {
            if(reset == true)
            {
                programCmdCount[CMD_INDEX_PROG_TWO] = CMD_START_POSITION;
            }
            else
            {
                programCmdCount[CMD_INDEX_PROG_TWO]++;
            }

            break;
        }

        case PROGRAM_THREE:
        {
            if(reset == true)
            {
                programCmdCount[CMD_INDEX_PROG_THREE] = CMD_START_POSITION;
            }
            else
            {
                programCmdCount[CMD_INDEX_PROG_THREE]++;
            }

            break;
        }

        case PROGRAM_FOUR:
        {
            if(reset == true)
            {
                programCmdCount[CMD_INDEX_PROG_FOUR] = CMD_START_POSITION;
            }
            else
            {
                programCmdCount[CMD_INDEX_PROG_FOUR]++;
            }

            break;
        }

        case PROGRAM_FIVE:
        {
            if(reset == true)
            {
                programCmdCount[CMD_INDEX_PROG_FIVE] = CMD_START_POSITION;
            }
            else
            {
                programCmdCount[CMD_INDEX_PROG_FIVE]++;
            }

            break;
        }
    }
}


/**
 *
 * @brief save program.

 * @return n/a
 *
 * @note n/a
 *
 */

static uint8_t get_cmd_position(programName_t name)
{

    uint8_t currentCommandPos;

    switch (name)
    {
        case PROGRAM_ONE:
        {
            currentCommandPos = programCmdCount[CMD_INDEX_PROG_ONE];
            break;
        }

        case PROGRAM_TWO:
        {
            currentCommandPos = programCmdCount[CMD_INDEX_PROG_TWO];
            break;
        }

        case PROGRAM_THREE:
        {
            currentCommandPos = programCmdCount[CMD_INDEX_PROG_THREE];
            break;
        }

        case PROGRAM_FOUR:
        {
            currentCommandPos = programCmdCount[CMD_INDEX_PROG_FOUR];
            break;
        }

        case PROGRAM_FIVE:
        {
            currentCommandPos = programCmdCount[CMD_INDEX_PROG_FIVE];
            break;
        }
    }

    return currentCommandPos;

}
