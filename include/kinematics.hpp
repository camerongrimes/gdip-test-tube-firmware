#ifndef ROBOT_ARM_KINEMATICS_H
#define ROBOT_ARM_KINEMATICS_H


void calculateServoAngles(float x, float y, float z, float &baseAngle, float &shoulderAngle, float &elbowAngle, float &handAngle);

typedef struct
{

    double base;
    double humerus;
    double ulna;
    double wrist;

}armServoAngles_t;

typedef struct
{

    double x;
    double y;
    double z;
    double wristAngle;
    double gripAngle;

}armPositionData_t;

armServoAngles_t set_arm_position(armPositionData_t armPosition);

#endif // ROBOT_ARM_KINEMATICS_H
