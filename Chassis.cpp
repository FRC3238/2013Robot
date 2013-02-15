#include "Chassis.h"
#include "Portnums.h"

Chassis::Chassis(int inLeft, int inRight, int inTilt) {

	Initialized = false;
	LeftJag = new CANJaguar(inLeft);
	RightJag = new CANJaguar(inRight);
	TiltJag = new CANJaguar(inTilt);
	drivetrain = new RobotDrive(LeftJag, RightJag);
	drivetrain->SetInvertedMotor(RobotDrive::kFrontRightMotor , true);
}

	
bool Chassis::Init() {
	Initialized = true;
	return Initialized;
}
	
void Chassis::TankDrive(float inLeft, float inRight, float throttle, bool invert){
	if (invert) {
		drivetrain->TankDrive(-inRight * throttle, -inLeft * throttle);
	}
	else {
		drivetrain->TankDrive(inLeft * throttle, inRight * throttle);
	}
}

void Chassis::ArcadeDrive(float forward, float turn, float throttle, bool invert) {
	if (invert) {
		drivetrain->ArcadeDrive(-forward * throttle, turn * throttle, true);
	}
	else {
		drivetrain->ArcadeDrive(forward * throttle, turn * throttle, true);
	}
}

void Chassis::SetBrake() {
	LeftJag->ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);
	RightJag->ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);
}

void Chassis::SetCoast() {
	LeftJag->ConfigNeutralMode(CANJaguar::kNeutralMode_Coast);
	RightJag->ConfigNeutralMode(CANJaguar::kNeutralMode_Coast);
}

void Chassis::Disable() {
	drivetrain->Drive(0,0);
}

void Chassis::Idle(){
	
}

void Chassis::ManualTilt(float speed) {
    TiltJag->Set(speed);
}
