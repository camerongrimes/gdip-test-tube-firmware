#include <math.h>

#include "kinematics.hpp"

/* Servo control for AL5D arm */

/* Arm dimensions( mm ) */
#define BASE_HGT 67.31      //base hight 2.65"
#define HUMERUS 146.05      //shoulder-to-elbow "bone" 5.75"
#define ULNA 187.325        //elbow-to-wrist "bone" 7.375"
#define GRIPPER 100.00          //gripper (incl.heavy duty wrist rotate mechanism) length 3.94"

/* pre-calculations */
float hum_sq = HUMERUS*HUMERUS;
float uln_sq = ULNA*ULNA;

armServoAngles_t set_arm_position(armPositionData_t armPosition)
{

    armServoAngles_t servoAngles;

    // Grip angle in radians for use in calculations
    double grip_angle_r =  68 * M_PI / 180.0;

    // Base angle and radial distance from x, y coordinates
    double bas_angle_r = atan2(armPosition.x, armPosition.y);
    double rdist = sqrt((armPosition.x * armPosition.x) + (armPosition.y * armPosition.y));

    // rdist is y coordinate for the arm
    armPosition.y = rdist;

    // Grip offsets calculated based on grip angle
    double grip_off_z = sin(grip_angle_r) * GRIPPER;
    double grip_off_y = cos(grip_angle_r) * GRIPPER;

    // Wrist position
    double wrist_z = (armPosition.z - grip_off_z) - BASE_HGT;
    double wrist_y = armPosition.y - grip_off_y;

    // Shoulder to wrist distance (AKA sw)
    double s_w = (wrist_z * wrist_z) + (wrist_y * wrist_y);
    double s_w_sqrt = sqrt(s_w);

    // sw angle to ground
    double a1 = atan2(wrist_z, wrist_y);
    
    double a2 = acos(((hum_sq - uln_sq) + s_w) / (2 * HUMERUS * s_w_sqrt));

    // Shoulder angle
    double shl_angle_r = a1 + a2;
    double shl_angle_d = shl_angle_r * 180.0 / M_PI;

    // Elbow angle
    double elb_angle_r = acos((hum_sq + uln_sq - s_w) / (2 * HUMERUS * ULNA));
    double elb_angle_d = elb_angle_r * 180.0 / M_PI;
    double elb_angle_dn = -(180.0 - elb_angle_d);

    double bas_angle_d = bas_angle_r * (180.0 / M_PI);

    float wri_angle_d = ( armPosition.gripAngle - elb_angle_dn ) - shl_angle_d;

    servoAngles.base = bas_angle_d * 11.1;
    servoAngles.humerus = ( shl_angle_d - 90.0 ) * 6.6;
    servoAngles.ulna = ( elb_angle_d - 90.0 ) * 6.6;
    servoAngles.wrist = ( wri_angle_d  * 11.1 );

    return servoAngles;
}