#include "Chassis.h"
#include "Portnums.h"

Chassis::Chassis(int inLeft, int inRight) {

		Initialized = false;
		LeftJag = new CANJaguar(inLeft);
		RightJag = new CANJaguar(inRight);
		drivetrain = new RobotDrive(LeftJag, RightJag);
		drivetrain->SetInvertedMotor(RobotDrive::kFrontRightMotor , true);
		LeftEncoder = new Encoder(LeftEncoderPortA, LeftEncoderPortB, true, Encoder::k4X);
		RightEncoder = new Encoder(RightEncoderPortA, RightEncoderPortB, false, Encoder::k4X); //one encoder needs to be inverted so they don't go in opposite directions
		float distancePerCount = (0.666*3.14) / 660.0; //setting encoders to read in feet, 8 inch wheels = 0.666 feet
		LeftEncoder->SetDistancePerPulse(distancePerCount);
		RightEncoder->SetDistancePerPulse(distancePerCount);
//		RightDistancePID = new PIDController(0.00833, 0, 0, (PIDSource*)RightEncoder, (PIDOutput*)RightJag);
//		LeftDistancePID = new PIDController(0.00833, 0, 0, (PIDSource*)LeftEncoder, (PIDOutput*)LeftJag);
//		RightDistancePID->SetOutputRange(-1, 1);
//		LeftDistancePID->SetOutputRange(-1, 1);
}

	
bool Chassis::Init() {
	LeftEncoder->Start();
	RightEncoder->Start();
	Initialized = true;
	return Initialized;
}
	
void Chassis::TankDrive(float inLeft, float inRight, float throttle, bool invert){
//	RightDistancePID->Disable();
//	LeftDistancePID->Disable();
	if (invert) {
		drivetrain->TankDrive(-inRight * throttle, -inLeft * throttle);
	}
	else {
		drivetrain->TankDrive(inLeft * throttle, inRight * throttle);
	}
}

void Chassis::ArcadeDrive(float forward, float turn, float throttle, bool invert) {
//	RightDistancePID->Disable();
//	LeftDistancePID->Disable();
	if (invert) {
		drivetrain->ArcadeDrive(-forward * throttle, turn * throttle, true);
	}
	else {
		drivetrain->ArcadeDrive(forward * throttle, turn * throttle, true);
	}
}

void Chassis::SetSpeedTank(float leftSpeed, float rightSpeed){
	
}

void Chassis::MoveDistanceTank(float leftDistance, float rightDistance) {
//	RightDistancePID->Enable();
//	LeftDistancePID->Enable();
//	LeftDistancePID->SetSetpoint(leftDistance);
//	RightDistancePID->SetSetpoint(rightDistance);
}

int Chassis::GetRightEncoderValue(){
	int RightEncoderValue = RightEncoder->Get();
	return RightEncoderValue;
}

int Chassis::GetLeftEncoderValue(){
	int LeftEncoderValue = LeftEncoder->Get();
	return LeftEncoderValue;
}

double Chassis::GetRightEncoderDistance(){
	double RightEncoderDistance = RightEncoder->GetDistance();
	return RightEncoderDistance;
}

double Chassis::GetLeftEncoderDistance(){
	double LeftEncoderDistance = LeftEncoder->GetDistance();
	return LeftEncoderDistance;
}

void Chassis::ResetEncoders(){
	LeftEncoder->Reset();
	RightEncoder->Reset();
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
//	RightDistancePID->Disable();
//	LeftDistancePID->Disable();
	LeftEncoder->Reset();
	RightEncoder->Reset();
	drivetrain->Drive(0,0);
}

void Chassis::Idle(){
	
}
