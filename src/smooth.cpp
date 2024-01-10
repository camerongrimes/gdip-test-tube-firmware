/**************************** LIB INCLUDES ******************************/

#include <Arduino.h>

/**************************** USER INCLUDES *****************************/
#include "smooth.hpp"
#include "kinematics.hpp"
#include "wifi.hpp"
#include "pwm.hpp"

/*************************** PUBLIC FUNCTIONS ***************************/

void smoothMotion() 
{

    armPositionData_t current  = wifi_get_latest_grid_position();
    armPositionData_t previous = wifi_get_previous_grid_position();

    double xDiff = abs(current.x - previous.x);
    double yDiff = abs(current.y - previous.y);
    double zDiff = abs(current.z - previous.z);

    double maxDiff = max(xDiff, max(yDiff, zDiff));

    int steps = maxDiff;

    double xStep = xDiff / steps;
    double yStep = yDiff / steps;
    double zStep = zDiff / steps;

    for (size_t i = 0; i < steps; i++)
    {
        pwm_write_test(calculateServoAngles(previous.x, previous.y, previous.z));
        
        previous.x += xStep;
        previous.y += yStep;
        previous.z += zStep;

        sleep(10);
    }

    pwm_write_test(calculateServoAngles(current.x, current.y, current.z));
    
}

/*************************** PRIVATE FUNCTIONS ***************************/

// double maxCoordinateDifference(armPositionData_t current, armPositionData_t previous, double &maxDiff, double &xDiff, double &yDiff, double &zDiff) {
//     double xDiff = abs(current.x - previous.x);
//     double yDiff = abs(current.y - previous.y);
//     double zDiff = abs(current.z - previous.z);

//     double maxDiff = max(xDiff, max(yDiff, zDiff));
// }