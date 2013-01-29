#ifndef CHASSIS_H
#define CHASSIS_H

#include <WPILib.h>
#include "Portnums.h"

class Chassis {
public:
    // These methods are visable (callable) to anyone using this class
    // If you wish to add or remove any public methods, talk to Nick Papadakis

    // Constructor
    Chassis(int inLeft, int inRight);
    
    //Initialization
    bool Init();

    // Drives the chassis with two values: one for the right motor and one for the left
    // Arguments: left - Speed of left motor; -1 to 1. right - Speed of right motor; -1 to 1
    void TankDrive(float inLeft, float inRight, float throttle = 1, bool invert = false);

    // Drives the chassis with two values: a forward speed and a turn speed
    // Arguments: forward - Speed at which to move forward; -1 to 1. turn - Speed to turn; -1 to 1
    void ArcadeDrive(float forward, float turn, float throttle = 1, bool invert = false);
    
    void SetSpeedTank(float leftSpeed, float rightSpeed);
    
    //Drives the chassis with two values: one distance for the left side and one distance for the right side
    void MoveDistanceTank(float leftDistance, float rightDistance);
    
    int GetRightEncoderValue();
    
    int GetLeftEncoderValue();
    
    double GetRightEncoderDistance();
    
    double GetLeftEncoderDistance();

    void ResetEncoders();
    
    void SetBrake();
    
    void SetCoast();

    // Turns off all motors controlled by this class
    void Disable();

    // Does general processing and should be called every 20ms
    void Idle();

private:
    // Put useful functions and variables here
	bool Initialized;
	CANJaguar *LeftJag;
	CANJaguar *RightJag;
	RobotDrive *drivetrain;
	Encoder *RightEncoder;
	Encoder *LeftEncoder;
//	PIDController *RightDistancePID;
//	PIDController *LeftDistancePID;
};

#endif
