#ifndef ROBOT_ARM_KINEMATICS_H
#define ROBOT_ARM_KINEMATICS_H






typedef struct
{

    double x;
    double y;
    double z;
    double wristAngle;
    double gripAngle;

}armPositionData_t;



typedef struct angleStates
{

  float base;
  float shoulder;
  float elbow;
  float gripper;

}armServoAngles_t;


armServoAngles_t set_arm_position(armPositionData_t armPosition);
armServoAngles_t calculateServoAngles(float x, float y, float z);

#endif // ROBOT_ARM_KINEMATICS_H
