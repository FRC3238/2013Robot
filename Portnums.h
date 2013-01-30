#ifndef PORTNUMS_H
#define PORTNUMS_H
#include <WPILib.h>

#define ROBOT real

/* Constant naming:
 * SubsystemDescription
 * 
 * All portnumbers should be in this file, so they are easy to change
 * If you need to add another category to this file, talk to Nick Papadakis
 * 
 * Everything in this file should be const
 */
 
// Jaguar CAN IDs
#if ROBOT == real
const UINT8 ChassisLeftMtr = 1;
const UINT8 ClimberLeftMtr = 2;
const UINT8 ChassisRightMtr = 3;
const UINT8 ClimberRightMtr = 4;
#endif

// GPIO Ports
#if ROBOT == real
const UINT32 ClimberLeftEncoder = 1;
const UINT32 ClimberRightEncoder = 2;
const UINT32 LeftEncoderPortA = 3;
const UINT32 LeftEncoderPortB = 4;
const UINT32 RightEncoderPortA = 5;
const UINT32 RightEncoderPortB = 6;
#endif

// Relay Ports
#if ROBOT == real
#endif

// PWM Ports (Servo AND PWM Jaguars)
#if ROBOT == real
#endif

// I2C Addresses
#if ROBOT == real
#endif

// Analog Ports
#if ROBOT == real
#endif

// Solenoid Ports
#if ROBOT == real
#endif

// Operator Console Ports
#if ROBOT == real
#endif

// USB HID Ports
#if ROBOT == real
const UINT8 DriveJoystickPort = 1;
#endif

#endif
