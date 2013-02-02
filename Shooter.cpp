#include "Shooter.h"
#include "Portnums.h"
#include <cmath>
float totalSpoolUpTime = 3.0;

Shooter::Shooter(int shootIn, int tiltIn){
	
	Initialized = false;
	shootJag = new CANJaguar(shootIn);
	tiltJag = new CANJaguar(tiltIn);
	spoolUpTimer = new Timer();
	anglePot = new AnalogChannel(AnglePotPort);
	shootServo = new Servo(ShooterServoPort);
	shootTimer = new Timer();
}

bool Shooter::Init(){ //Resetting the timer used for spooling up the shooter
	spoolUpTimer->Reset();
	Initialized = true;
	return Initialized;
}

void Shooter::StartShooter(){ //Look in idle for how the shooter actually spools up
	StartingShooter = true;
}

void Shooter::StopShooter(){
	StartingShooter = false;
	shootJag->Set(0);
} 

void Shooter::SetAngle(float desiredAngle){
	// scale angles to match
	currentAngle = GetAngle();
	if(desiredAngle < currentAngle){
		motorDirection = -1;
	}
	else{
		motorDirection = 1;
	}
	if(abs(desiredAngle - currentAngle) < 1.0){ // Make this a constant or something
		tiltJag->Set(0);
	}
	else{
		tiltJag->Set(1*motorDirection);
		// set some state to say we're running angle motor.
	}
}

void Shooter::Shoot(){
	shootServo->Set(40);
	shootTimer->Start(); // Where's the state that says we're doing a shoot?
}

float Shooter::GetAngle(){
	Angle = anglePot->GetAverageVoltage();
	// might be a good place for a mapper?
	return Angle;
}

void Shooter::Disable(){
	StopShooter();
	spoolUpTimer->Reset();
}

void Shooter::Idle(){
	double spoolUpTime = spoolUpTimer->Get(); //This is where the action happens for the shooter starting
	double shootTime = shootTimer->Get();
	if(StartingShooter){
		if(spoolUpTime < totalSpoolUpTime){
			spoolUpTimer->Start();
			shootJag->Set(spoolUpTime * 1.0/totalSpoolUpTime);
		}
		else{
			spoolUpTimer->Stop();
			shootJag->Set(1.0); // Constant
		}
	}
	if(0.0 < shootTime < 3.0){
		shootServo->Set(40); // didn't you already set this?
	}
	else{
		shootServo->Set(-40);
	}
	// When do we shut off the angle motor? Oh not too late! you broke the machine.
}
