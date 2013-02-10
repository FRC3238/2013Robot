#ifndef PORTNUMS_H
#define PORTNUMS_H
#include <WPILib.h>

#define ROBOT 'r'
//#define ROBOT 'p'

/* Constant naming:
 * SubsystemDescription
 * 
 * All portnumbers should be in this file, so they are easy to change
 * If you need to add another category to this file, talk to Nick Papadakis
 * 
 * Everything in this file should be const
 */
 
// Jaguar CAN IDs
#if ROBOT == 'r'
const UINT8 ShooterShooterMtr = 1;
const UINT8 ChassisRightMtr = 2;
const UINT8 ShooterTiltMtr = 3;
const UINT8 ChassisTiltMtr = 4;
const UINT8 ClimberLeftMtr = 5;
const UINT8 ClimberRightMtr = 6;
const UINT8 ChassisLeftMtr = 7;
#endif

// GPIO Ports
#if ROBOT == 'r'
const UINT32 ClimberLeftEncoder = 1;
const UINT32 ClimberRightEncoder = 2;
const UINT32 LeftEncoderPortA = 3;
const UINT32 LeftEncoderPortB = 4;
const UINT32 RightEncoderPortA = 5;
const UINT32 RightEncoderPortB = 6;
const UINT32 FloorCloseSwitchPort = 7;
const UINT32 FloorOpenSwitchPort = 8;
const UINT32 BucketSwitchPort = 9;
const UINT32 ShooterTach = 10;
#endif

// Relay Ports
#if ROBOT == 'r'
const UINT32 FloorMotorRelay = 1;
#endif

// PWM Ports (Servo AND PWM Jaguars)
#if ROBOT == 'r'
const UINT32 ShooterServoPort = 1;
const UINT32 IrisServoRightPort = 2;
const UINT32 IrisServoLeftPort = 3;
const UINT32 LipServo = 4;
#endif

// I2C Addresses
#if ROBOT == 'r'
#endif

// Analog Ports
#if ROBOT == 'r'
const UINT32 AnglePotPort = 1;
#endif

// Solenoid Ports
#if ROBOT == 'r'
const UINT32 ClimberDeployerLeftPort = 1;
const UINT32 ClimberDeployerRightPort = 2;
#endif

// Operator Console Ports
#if ROBOT == 'r'
#endif

// USB HID Ports
#if ROBOT == 'r'
const UINT8 DriveJoystickPort = 1;
const UINT8 ShootJoystickPort = 2;
#endif

#endif
