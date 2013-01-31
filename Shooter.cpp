#include "Shooter.h"
#include "Portnums.h"

Shooter::Shooter(int shootIn, int tiltIn){
	
	shootJag = new CANJaguar(shootIn);
	tiltRelay = new Relay(tiltIn);
	spoolUpTimer = new Timer();
	Initialized = false;
}

bool Shooter::Init(){
	spoolUpTimer->Reset();
	Initialized = true;
	return Initialized;
}

void Shooter::StartShooter(){
	StartingShooter = true;
}

void Shooter::StopShooter(){
	StartingShooter = false;
	shootJag->Set(0);
}

void Shooter::Disable(){
	StopShooter();
}

void Shooter::Idle(){
	float spoolUpTime = spoolUpTimer->Get();
	if(StartingShooter){
	if(spoolUpTime < 3.0){
		spoolUpTimer->Start();
		shootJag->Set(spoolUpTime * 0.33);
	}
	else{
		spoolUpTimer->Stop();
		shootJag->Set(1.0);
	}
	}
}
