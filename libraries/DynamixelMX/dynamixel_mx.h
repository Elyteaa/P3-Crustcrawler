#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H

/** EEPROM AREA **/
#define MX_MODEL_NUMBER               0
// #define MX_MODEL_NUMBER_H               1
#define MX_VERSION                      6
#define MX_ID                           7
#define MX_BAUD_RATE                    8
#define MX_RETURN_DELAY_TIME            9
#define MX_DRIVE_MODE                   10
#define MX_OPERATING_MODE               11
#define MX_SECONDARY_SHADOW_ID          12
#define MX_PROTOCOL_VERSION             13
#define MX_HOMING_OFFSET                20
#define MX_MOVING_THRESHOLD             24
//#define MX_CW_ANGLE_LIMIT_L             6
//#define MX_CW_ANGLE_LIMIT_H             7
//#define MX_CCW_ANGLE_LIMIT_L            8
//#define MX_CCW_ANGLE_LIMIT_H            9
#define MX_LIMIT_TEMPERATURE            31
#define MX_DOWN_LIMIT_VOLTAGE           34 //RE-CHECK
#define MX_UP_LIMIT_VOLTAGE             32 //RE-CHECK
#define MX_PWM_LIMIT                    36
#define MX_CURRENT_LIMIT                38
#define MX_ACCELERATION_LIMIT           40
#define MX_VELOCITY_LIMIT               44
#define MX_MAX_POSITION_LIMIT           48
#define MX_MIN_POSITION_LIMIT           52
//#define MX_MAX_TORQUE_L                 14
//#define MX_MAX_TORQUE_H                 15
//#define MX_RETURN_LEVEL                 16
//#define MX_ALARM_LED                    17
#define MX_ALARM_SHUTDOWN               63
//#define MX_MULTI_TURN_OFFSET_L          20
//#define MX_MULTI_TURN_OFFSET_H          21
//#define MX_RESOLUTION_DIVIDER           22
/** RAM AREA **/
#define MX_TORQUE_ENABLE                64
#define MX_LED                          65
#define MX_VELOCITY_I_GAIN              76 //PID GAINS SEPARETLY FOR VELOCITY & POSITION
#define MX_VELOCITY_P_GAIN              78
#define MX_POSITION_D_GAIN              80
#define MX_POSITION_I_GAIN              82
#define MX_POSITION_P_GAIN              84
#define MX_GOAL_POSITION                116
//#define MX_GOAL_POSITION_H              31
#define MX_GOAL_SPEED                   104
//#define MX_GOAL_SPEED_H                 33
//#define MX_TORQUE_LIMIT_L               34
//#define MX_TORQUE_LIMIT_H               35
#define MX_PRESENT_POSITION             132
//#define MX_PRESENT_POSITION_H           37
#define MX_PRESENT_SPEED_L              128
//#define MX_PRESENT_SPEED_H              39
//#define MX_PRESENT_LOAD                 40
//#define MX_PRESENT_LOAD_H               41
#define MX_PRESENT_VOLTAGE              144
#define MX_PRESENT_TEMPERATURE          146
#define MX_REGISTERED_INSTRUCTION       69
//#define MX_PAUSE_TIME                   45
#define MX_MOVING                       122
//#define MX_LOCK                         47
//#define MX_PUNCH_L                      48
//#define MX_PUNCH_H                      49
#define MX_CURRENT_L                    126
//#define MX_CURRENT_H                    69
//#define MX_TORQUE_CONTROL_MODE_ENABLE   70 //not sure
//#define MX_GOAL_TORQUE_L                71
//#define MX_GOAL_TORQUE_H                72
//#define MX_GOAL_ACCELERATION            73

// Set the PID gains of an MX servo.
void SetPidGains(int id, float p_gain, float i_gain, float d_gain);

// Get the voltage supplied to an MX servo.
float GetVoltage(int id);

// Get the current consumption of an MX servo.
float GetCurrent(int id);

// Get the present speed of an MX servo.
float GetSpeed(int id);

// Set the torque setpoint.
//void SetTorque(int id, float torque);

#define GetLowerAngleLimit(id) (ax12GetRegister(id, MX_CW_ANGLE_LIMIT_L, 2))
#define GetUpperAngleLimit(id) (ax12GetRegister(id, MX_CCW_ANGLE_LIMIT_L, 2))

#define TorqueControlEnable(id) (ax12SetRegister(id, MX_TORQUE_CONTROL_MODE_ENABLE, 1))
#define TorqueControlDisable(id) (ax12SetRegister(id, MX_TORQUE_CONTROL_MODE_ENABLE, 0))

#endif //DYNAMIXEL_H
