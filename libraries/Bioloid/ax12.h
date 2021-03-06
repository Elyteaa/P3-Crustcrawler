/*
  ax12.h - ArbotiX library for AX/RX control.
  Copyright (c) 2008-2011 Michael E. Ferguson.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Arduino.h>

#ifndef ax12_h
#define ax12_h

#define AX12_MAX_SERVOS             30
#define AX12_BUFFER_SIZE            32

/** Configuration **/
#if defined(ARBOTIX)
  // no config needed
#elif defined(SERVO_STIK) || defined(ARBOTIX2)
  #define AX_RX_SWITCHED
  #define SET_RX_WR (PORTC |= 0x40)
  #define SET_AX_WR (PORTC |= 0x80)
  #define SET_RX_RD (PORTC = (PORTC & 0xBF) | 0x80)
  #define SET_AX_RD (PORTC = (PORTC & 0x7F) | 0x40)
  #define INIT_AX_RX DDRC |= 0xC0; PORTC |= 0xC0
#elif defined(ARBOTIX_1280)
  #define AX_RX_SWITCHED
  #define SET_RX_WR (PORTG |= 0x08)
  #define SET_AX_WR (PORTG |= 0x10)
  #define SET_RX_RD (PORTG = (PORTG&0xE7) | 0x10 )
  #define SET_AX_RD (PORTG = (PORTG&0xE7) | 0x08 )
  #define INIT_AX_RX DDRG |= 0x18; PORTG |= 0x18
#endif

/** EEPROM AREA **/
#define AX_MODEL_NUMBER               0
// #define MX_MODEL_NUMBER_H               1
#define AX_VERSION                      6
#define AX_ID                           7
#define AX_BAUD_RATE                    8
#define AX_RETURN_DELAY_TIME            9
#define AX_DRIVE_MODE                   10
#define AX_OPERATING_MODE               11
#define AX_SECONDARY_SHADOW_ID          12
#define AX_PROTOCOL_VERSION             13
#define AX_HOMING_OFFSET                20
#define AX_MOVING_THRESHOLD             24
//#define MX_CW_ANGLE_LIMIT_L             6
//#define MX_CW_ANGLE_LIMIT_H             7
//#define MX_CCW_ANGLE_LIMIT_L            8
//#define MX_CCW_ANGLE_LIMIT_H            9
#define AX_LIMIT_TEMPERATURE            31
#define AX_DOWN_LIMIT_VOLTAGE           34 //RE-CHECK
#define AX_UP_LIMIT_VOLTAGE             32 //RE-CHECK
#define AX_PWM_LIMIT                    36
#define AX_CURRENT_LIMIT                38
#define AX_ACCELERATION_LIMIT           40
#define AX_VELOCITY_LIMIT               44
#define AX_MAX_POSITION_LIMIT           48
#define AX_MIN_POSITION_LIMIT           52
//#define MX_MAX_TORQUE_L                 14
//#define MX_MAX_TORQUE_H                 15
//#define MX_RETURN_LEVEL                 16
//#define MX_ALARM_LED                    17
#define AX_ALARM_SHUTDOWN               63
//#define MX_MULTI_TURN_OFFSET_L          20
//#define MX_MULTI_TURN_OFFSET_H          21
//#define MX_RESOLUTION_DIVIDER           22
/** RAM AREA **/
#define AX_TORQUE_ENABLE                64
#define AX_LED                          65
#define AX_VELOCITY_I_GAIN              76 //PID GAINS SEPARETLY FOR VELOCITY & POSITION
#define AX_VELOCITY_P_GAIN              78
#define AX_POSITION_D_GAIN              80
#define AX_POSITION_I_GAIN              82
#define AX_POSITION_P_GAIN              84
#define AX_GOAL_POSITION_L              116
//#define MX_GOAL_POSITION_H              31
#define AX_GOAL_SPEED_L                 104
//#define MX_GOAL_SPEED_H                 33
//#define MX_TORQUE_LIMIT_L               34
//#define MX_TORQUE_LIMIT_H               35
#define AX_PRESENT_POSITION_L           132
//#define MX_PRESENT_POSITION_H           37
#define AX_PRESENT_SPEED                128
//#define MX_PRESENT_SPEED_H              39
//#define MX_PRESENT_LOAD                 40
//#define MX_PRESENT_LOAD_H               41
#define AX_PRESENT_VOLTAGE              144
#define AX_PRESENT_TEMPERATURE          146
#define AX_REGISTERED_INSTRUCTION       69
//#define MX_PAUSE_TIME                   45
#define AX_MOVING                       122
//#define MX_LOCK                         47
//#define MX_PUNCH_L                      48
//#define MX_PUNCH_H                      49
#define AX_CURRENT_L                    126
//#define MX_CURRENT_H                    69
//#define MX_TORQUE_CONTROL_MODE_ENABLE   70 //not sure
//#define MX_GOAL_TORQUE_L                71
//#define MX_GOAL_TORQUE_H                72
//#define MX_GOAL_ACCELERATION            73

/** Status Return Levels **/
#define AX_RETURN_NONE              0
#define AX_RETURN_READ              1
#define AX_RETURN_ALL               2

/** Instruction Set **/
#define AX_PING                     1
#define AX_READ_DATA                2
#define AX_WRITE_DATA               3
#define AX_REG_WRITE                4
#define AX_ACTION                   5
#define AX_RESET                    6
#define AX_SYNC_WRITE               131

/** Error Levels **/
#define ERR_NONE                    0
//#define ERR_VOLTAGE                 1
//#define ERR_ANGLE_LIMIT             2
//#define ERR_OVERHEATING             4
#define ERR_RANGE                   4
#define ERR_CHECKSUM                5
//#define ERR_OVERLOAD                32
#define ERR_INSTRUCTION             2

/** AX-S1 **/
#define AX_LEFT_IR_DATA             26
#define AX_CENTER_IR_DATA           27
#define AX_RIGHT_IR_DATA            28
#define AX_LEFT_LUMINOSITY          29
#define AX_CENTER_LUMINOSITY        30
#define AX_RIGHT_LUMINOSITY         31
#define AX_OBSTACLE_DETECTION       32
#define AX_BUZZER_INDEX             40

void ax12Init(long baud);

void setTXall();     // for sync write
void setTX(int id);
void setRX(int id);

void ax12write(unsigned char data);
void ax12writeB(unsigned char data);

int ax12ReadPacket(int length);
int ax12GetRegister(int id, int regstart, int length);
void ax12SetRegister(int id, int regstart, int data);
void ax12SetRegister2(int id, int regstart, int data);
int ax12GetLastError();

extern unsigned char ax_rx_buffer[AX12_BUFFER_SIZE];
extern unsigned char ax_tx_buffer[AX12_BUFFER_SIZE];
extern unsigned char ax_rx_int_buffer[AX12_BUFFER_SIZE];
#if defined(AX_RX_SWITCHED)
// Need to stow type of servo (which bus it's on)
extern unsigned char dynamixel_bus_config[AX12_MAX_SERVOS];
#endif

#define SetPosition(id, pos) (ax12SetRegister2(id, AX_GOAL_POSITION_L, pos))
#define GetPosition(id) (ax12GetRegister(id, AX_PRESENT_POSITION_L, 2))
#define TorqueOn(id) (ax12SetRegister(id, AX_TORQUE_ENABLE, 1))
#define Relax(id) (ax12SetRegister(id, AX_TORQUE_ENABLE, 0))

#define GetLeftIRData(id) (ax12GetRegister(id, AX_LEFT_IR_DATA))
#define GetCenterIRData(id) (ax12GetRegister(id, AX_CENTER_IR_DATA))
#define GetRightIRData(id) (ax12GetRegister(id, AX_RIGHT_IR_DATA))
#define GetObstacles(id) (ax12GetRegister(id, OBSTACLE_DETECTION))

#define PlayTone(id, note) (ax12SetRegister(id, AX_BUZZER_INDEX, note))

#endif
