
#include <Arduino.h>
#include "kinematics.hpp"

#define MAX_CMDS 100

typedef enum
{
    
    PROG1,
    PROG2,
    PROG3,
    PROG4,
    PROG5,

}programSelect_t;

typedef struct
{

    armPositionData_t PROG1[MAX_CMDS];
    armPositionData_t PROG2[MAX_CMDS];
    armPositionData_t PROG3[MAX_CMDS];
    armPositionData_t PROG4[MAX_CMDS];
    armPositionData_t PROG5[MAX_CMDS];

}userPrograms_t;


void cmds_record_program_data(armPositionData_t data, programSelect_t program, uint32_t cmdIndex);
armPositionData_t cmds_get_program_data(programSelect_t program, uint32_t cmdIndex);