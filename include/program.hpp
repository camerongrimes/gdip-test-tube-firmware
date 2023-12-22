#include <stdbool.h>
#include <stdint.h>

#include "kinematics.hpp"

#define MAX_CMDS 100

typedef enum
{

    PROGRAM_START,
    PROGRAM_RECORD,
    PROGRAM_END,
    PROGRAM_PLAY,
    PROGRAM_DELETE,

}programState_t;

typedef enum
{
    PROGRAM_ONE,
    PROGRAM_TWO,
    PROGRAM_THREE,
    PROGRAM_FOUR,
    PROGRAM_FIVE,

}programName_t;


typedef enum
{

    success,
    error,

}programError_t;


typedef struct
{

    armPositionData_t positions[MAX_CMDS];
    int usedCommands;
    bool programSaved;


}program_t;

programError_t program_state_machine(programName_t name, armPositionData_t gridPosition, programState_t state);
programError_t program_record_position(armPositionData_t currentGridPosition, programName_t name, uint8_t commandIndex);
programError_t program_play(programName_t name);
programError_t program_save(programName_t name);
programError_t program_delete(programName_t name);