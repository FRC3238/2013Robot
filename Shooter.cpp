#include "Shooter.h"
#include "Portnums.h"
#include "Settings.h"
#include <cmath> //So we can use an absolute value function
float tiltStopDistance = 5.0;
float tiltSpeed = 1.0;
float servoPush = 0.05;
float servoPull = 0.32;

Shooter::Shooter(int shootIn, int tiltIn, int tachPortIn){
	
	Initialized = false;
	shootJag = new CANJaguar(shootIn);
	tiltJag = new CANJaguar(tiltIn);
	anglePot = new AnalogChannel(AnglePotPort);
	shootServo = new Servo(ShooterServoPort);
	shootTimer = new Timer();
    tachIn = new DigitalInput(tachPortIn);
    tach = new ShootTach(tachIn);
    doneShooting = true;
}

bool Shooter::Init(){ //Resetting the timer used for spooling up the shooter;
	tach->SetMaxPeriod(0.05);
    tach->Start();
    tach->Reset();
	shootServo->Set(servoPull);
	anglePot->SetAverageBits(8);
	shootJag->SetSafetyEnabled(false);
	tiltJag->SetSafetyEnabled(false);
	Initialized = true;
	return Initialized;
}

void Shooter::StopShooter(){
	shootJag->Set(0);
}

void Shooter::SetRPM(float rpm){
//	SmartDashboard::PutNumber("SetRPM", rpm);
	desiredRPM = rpm;
}

void Shooter::SetAngle(float wantedAngle){
	float currentAngle = GetAngle();
	float motorDirection;
	if(wantedAngle < currentAngle){ //Finds which direction the tilt motor needs to run
		motorDirection = -1.0;
	}
	else{
		motorDirection = 1.0;
	}
	if(abs(wantedAngle - currentAngle) < tiltStopDistance){ //Determines when to stop the motor based on the "slop" value
		ManualTilt(0);
	}
	else{
		ManualTilt(tiltSpeed*motorDirection);
	}
	desiredAngle = wantedAngle;
}

void Shooter::ManualTilt(float power){
	tiltJag->Set(power);
}

void Shooter::Shoot(){
	shootServo->Set(servoPush);
	shootTimer->Start();
	doneShooting = false;
}

int Shooter::GetAngle(){
	int Angle = anglePot->GetAverageValue();
	return Angle;
}

float Shooter::GetRPM() {
//    SmartDashboard::PutBoolean("Tach curVal", tachIn->Get());
//    SmartDashboard::PutNumber("ShooterTachNum", tach->Get());
    return 60/(tach->GetPeriod());
}

bool Shooter::ShooterUpToSpeed() {
	if(abs(GetRPM() - desiredRPM) < 5){
		return true;
	}
	else {
		return false;
	}
}

bool Shooter::IsAngleSet(){
	currentAngle = GetAngle();
	if(abs(desiredAngle - currentAngle) < tiltStopDistance){
		return true;
	}
	else{
		return false;
	}
}

bool Shooter::DoneShooting(){
	return doneShooting;
}

void Shooter::Idle(){
	if (desiredRPM > GetRPM()) shootJag->Set(1.0);
	else shootJag->Set(0.0);
//	SmartDashboard::PutNumber("desiredRPMInIdle", desiredRPM);
//	SmartDashboard::PutNumber("GetRPMInIdle", GetRPM());
//	SmartDashboard::PutNumber("ShootJagSpeed", shootJag->Get());
	double shootTime = shootTimer->Get();
	if(shootTime > 0.5){ //The timing for the servo feeding frisbees into the shooter
		shootServo->Set(servoPull);
		shootTimer->Reset();
		shootTimer->Stop();
		doneShooting = true;
	}
}

void Shooter::Disable(){
	StopShooter();
}
