#include "Shooter.h"
#include "Portnums.h"
#include "Settings.h"
#include <cmath> //So we can use an absolute value function
float totalSpoolUpTime = 2.0;
float tiltStopDistance = 5.0;
float tiltSpeed = 1.0;
float servoPush = 0.05;
float servoPull = 0.32;
float shootSpeedFactor = 1.0;
double PConst = 1.0/3700.0;
double IConst = 0.0;
double DConst = 0.0;

Shooter::Shooter(int shootIn, int tiltIn, int tachPortIn){
	
	Initialized = false;
	shootJag = new CANJaguar(shootIn);
	tiltJag = new CANJaguar(tiltIn);
	spoolUpTimer = new Timer();
	anglePot = new AnalogChannel(AnglePotPort);
	shootServo = new Servo(ShooterServoPort);
	shootTimer = new Timer();
    tachIn = new DigitalInput(tachPortIn);
    tach = new ShootTach(tachIn);
    shooterPID = new PIDController(PConst, IConst, DConst, tach, shootJag);
    doneShooting = true;
}

bool Shooter::Init(){ //Resetting the timer used for spooling up the shooter
	spoolUpTimer->Reset();
	tach->SetMaxPeriod(0.05);
    tach->Start();
    tach->Reset();
	shootServo->Set(servoPull);
	Initialized = true;
	return Initialized;
}

void Shooter::StartShooter(){ //Look in idle for how the shooter actually spools up
	spoolUpTimer->Start();
	StartingShooter = true;
    setSpeed = 1;
}

void Shooter::StopShooter(){
	shootJag->Set(0);
	spoolUpTimer->Reset();
	StartingShooter = false;
}

void Shooter::RampUpToValue(float spd) {
	spoolUpTimer->Start();
	StartingShooter = true;
    setSpeed = spd;
}

void Shooter::SetSpeedPID(float speed){
	shooterPID->Enable();
	shooterPID->SetSetpoint(speed);
}

void Shooter::DisablePID(){
	shooterPID->Disable();
}

void Shooter::SetRPM(float rpm){
	if (rpm > GetRPM()) shootJag->Set(1.0);
	else shootJag->Set(0.0);
	SmartDashboard::PutNumber("rpm", rpm);
	desiredRPM = rpm;
}

void Shooter::SetAngle(float wantedAngle){
	//Scale angles to match
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

float Shooter::GetAngle(){
	float Angle = anglePot->GetAverageValue();
	//Place mapper in this function
	return Angle;
}

void Shooter::Disable(){
	StopShooter();
	spoolUpTimer->Reset();
}

void Shooter::Idle(){
    //Settings.Get
    //float servoPush = 0.25;
    //float servoPull = 0.80;

	double spoolUpTime = spoolUpTimer->Get(); //This is where the action happens for the shooter starting
	double shootTime = shootTimer->Get();
	if(StartingShooter){
        float spd = spoolUpTime/totalSpoolUpTime;
        if (spd > setSpeed) spd = setSpeed;
        //shootJag->Set(shootSpeedFactor*spd);
	}
	if(shootTime > 0.5){ //The timing for the servo feeding frisbees into the shooter
		shootServo->Set(servoPull);
		shootTimer->Reset();
		shootTimer->Stop();
		doneShooting = true;
	}
	
	PConst = Settings.getDouble("ShootP", PConst, true);
	IConst = Settings.getDouble("ShootI", IConst, true);
	DConst = Settings.getDouble("ShootD", DConst, true);
}

float Shooter::GetRPM() {
    SmartDashboard::PutBoolean("Tach curVal", tachIn->Get());
    SmartDashboard::PutNumber("ShooterTachNum", tach->Get());
    return 60/(tach->GetPeriod());
}

bool Shooter::ShooterUpToSpeed() {
	if(abs(GetRPM() - desiredRPM) < 10){
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
