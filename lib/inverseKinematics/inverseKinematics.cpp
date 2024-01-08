#include "inverseKinematics.hpp"
#include <cmath>

void calculateServoAngles(float x, float y, float z, float &baseAngle, float &shoulderAngle, float &elbowAngle, float &handAngle) {
    //Define linkage lengths
    float L1 = 193.0;
    float L2 = 250.0;
    // Calculate angle at base joint (rotation in XY plane)
    baseAngle = atan2(y, x) * 180.0 / M_PI;
    // Calculate the distance to the desired end effector position in 3D space
    float distanceXYZ = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    shoulderAngle = (acos((pow(L1, 2) + pow(distanceXYZ, 2) - pow(L2, 2)) / (2 * L1 * distanceXYZ)) + asin(z/distanceXYZ)) * 180.0 / M_PI;

    elbowAngle = (acos((pow(L1, 2) - pow(distanceXYZ, 2) + pow(L2, 2)) / (2 * L1 * L2))) * 180.0 / M_PI;

    handAngle = 270 - (shoulderAngle + elbowAngle + 45);
}