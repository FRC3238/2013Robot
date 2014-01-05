#include "Shooter.h"
#include "Portnums.h"
#include "Settings.h"
#include <cmath> //So we can use an absolute value function
float tiltStopDistance = 5.0;
float tiltSpeed = 1.0;
float servoPush = 0.05;
float servoPull = 0.32;

Shooter::Shooter(Swag* theSwagIn, int shootIn, int tiltIn, int tachPortIn){
    theSwag = theSwagIn;
	
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
    controlSpeed = true;
    manualSpeed = 0;
	return Initialized;
}

void Shooter::StopShooter(){
	shootJag->Set(0);
}

void Shooter::SetRPM(float rpm){
//	SmartDashboard::PutNumber("SetRPM", rpm);
	desiredRPM = rpm;
<<<<<<< HEAD
	useBangBang = true;
||||||| merged common ancestors
=======
    controlSpeed = true;
}

void Shooter::SetManualSpeed(float spd){
    controlSpeed = false;
    manualSpeed = spd;
>>>>>>> e159e922308fc1d568ac5b3f5fad22d81b286086
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
    theSwag->FireFrisbee();
	doneShooting = false;
}

int Shooter::GetAngle(){
	int Angle = anglePot->GetAverageValue();
	return Angle;
}

float Shooter::GetRPM() {
    return 60/(tach->GetPeriod());
}

bool Shooter::ShooterUpToSpeed() {
	 return abs(GetRPM() - desiredRPM) < 5;
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

void Shooter::SetRawPower(float power){
	useBangBang = false;
	rawPower = power;
	shootJag->Set(power);
}

void Shooter::Idle(){
    float curRPM = GetRPM();
<<<<<<< HEAD
    if (useBangBang) {
		// Don't go full power until it's somewhat up to speed to avoid
		//  overcurrent faults
		if (desiredRPM > curRPM) shootJag->Set(curRPM < 1000? 0.75 : 1.0);
		else shootJag->Set(0.0);
    }
    else {
    	shootJag->Set(rawPower);
    }
||||||| merged common ancestors
    // Don't go full power until it's somewhat up to speed to avoid
    //  overcurrent faults
	if (desiredRPM > curRPM) shootJag->Set(curRPM < 1000? 0.75 : 1.0);
	else shootJag->Set(0.0);
=======
    // Don't go full power until it's somewhat up to speed to avoid
    //  overcurrent faults
    if (controlSpeed) {
        if (desiredRPM > curRPM) manualSpeed = curRPM < 1000? 0.75 : 1.0;
        else manualSpeed = 0;
    }
    shootJag->Set(manualSpeed);
>>>>>>> e159e922308fc1d568ac5b3f5fad22d81b286086
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
