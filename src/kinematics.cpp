#include "kinematics.hpp"
#include <cmath>


armServoAngles_t calculateServoAngles(float x, float y, float z) 
{

    armServoAngles_t servoAngles;

    //Define linkage lengths
    float L1 = 210.0;
    float L2 = 290.0;

    // Calculate angle at base joint (rotation in XY plane)
    servoAngles.base = atan2(y, x) * 180.0 / M_PI;
    // Calculate the distance to the desired end effector position in 3D space
    float distanceXYZ = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    servoAngles.shoulder = (acos((pow(L1, 2) + pow(distanceXYZ, 2) - pow(L2, 2)) / (2 * L1 * distanceXYZ)) + asin(z/distanceXYZ)) * 180.0 / M_PI;

    servoAngles.elbow = (acos((pow(L1, 2) - pow(distanceXYZ, 2) + pow(L2, 2)) / (2 * L1 * L2))) * 180.0 / M_PI;

    servoAngles.gripper = 270 - (servoAngles.shoulder + servoAngles.elbow + 45);

    return servoAngles;

}