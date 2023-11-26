#ifndef ROBOT_ARM_KINEMATICS_H
#define ROBOT_ARM_KINEMATICS_H

#include <cmath>

// Constants for the arm dimensions
extern double baseLength;
extern double joint1Length;
extern double joint2Length;


// Function to calculate inverse kinematics
void calculateIK(float x, float y, float z, float& baseAngle, float& joint1Angle, float& joint2Angle);

#endif // ROBOT_ARM_KINEMATICS_H
