#include "Collector.h"
#include "Portnums.h"

Collector::Collector(Swag* theSwagIn, UINT32 BotFloorOpenSwitch, UINT32  BotFloorCloseSwitch, UINT32  bucketThingy) {
    theSwag = theSwagIn;
	
	BottomFloorOpenSwitch = new DigitalInput(BotFloorOpenSwitch);
	BottomFloorCloseSwitch = new DigitalInput(BotFloorCloseSwitch);
	bucketStatusSwitch = new DigitalInput(bucketThingy); 
	FloorDrive = new Relay(FloorMotorRelay);
	ServoLockRight = new Servo(IrisServoRightPort);
	ServoLockLeft = new Servo(IrisServoLeftPort);
	AllPurposeTimer = new Timer();
	AllPurposeTimer->Start();
}

void Collector::Init(){
	CS = ST::READY;
	lockingServos = closingFloor = openingFloor = false;
}

bool Collector::doneDropping(){
	return CS == ST::READY || CS == ST::FLOOR_CLOSE || CS == ST::SERVOS_UNLOCK;
}

void Collector::manualMode(bool mode){
	if(mode) manual = true;
	else manual = false;
}

void Collector::manualFloorControl(int direction){
	if (manual) {
		if (direction > 0)	openFloor();
		else if (direction < 0) closeFloor();
		else stopFloor();
	}
}

string Collector::getState(){
	switch(CS){
	case ST::READY:			return "READY";	break;	
	case ST::SERVOS_LOCK:	return "SERVOS_LOCK";	break;		
	case ST::FLOOR_OPEN:	return "FLOOR_OPEN";	break;	
	case ST::FLOOR_WAIT:	return "FLOOR_WAIT";	break;
	case ST::FLOOR_CLOSE:	return "FLOOR_CLOSE";	break;
	case ST::SERVOS_UNLOCK:	return "SERVOS_UNLOCK"; break;
	default:				return "wat";			break;
	}
}

void Collector::dropDisc(){
	if (CS == ST::READY) {
		CS = ST::SERVOS_LOCK;
		AllPurposeTimer->Reset();
        theSwag->DropFrisbee();
	}
}

static const float servoUnlockTime = 0.2;
static const float servoLockTime = 0.2;
static const float floorWaitTime = 0.1;

void Collector::Idle(){
	switch (CS) {
	case ST::READY:
		break;
	case ST::SERVOS_LOCK:
		lockServos();
		stopFloor();
		if (AllPurposeTimer->HasPeriodPassed(servoLockTime)) {
			CS = ST::FLOOR_OPEN;
		}
		break;
	case ST::FLOOR_OPEN:
		openFloor();
		if (isFloorOpen()) {
			CS = ST::FLOOR_WAIT;
			AllPurposeTimer->Reset();
		}
		break;
	case ST::FLOOR_WAIT:
		stopFloor();
		if (AllPurposeTimer->HasPeriodPassed(floorWaitTime)) {
			CS = ST::FLOOR_CLOSE;
		}
		break;
	case ST::FLOOR_CLOSE:
		closeFloor();
		if (isFloorClosed()) {
			CS = ST::SERVOS_UNLOCK;
			AllPurposeTimer->Reset();
		}
		break;
	case ST::SERVOS_UNLOCK:
		unlockServos();
		stopFloor();
		if (AllPurposeTimer->HasPeriodPassed(servoUnlockTime)) {
			CS = ST::READY;
		}
		break;
	}
	
	if (lockingServos) {
		ServoLockRight->Set(1);
		ServoLockLeft->Set(0);
	}
	else {
		ServoLockRight->Set(0);
		ServoLockLeft->Set(1);
	}
	if (closingFloor) {
		if (isFloorClosed()) {
			FloorDrive->Set(Relay::kOff);
			closingFloor = false;
		}
		else FloorDrive->Set(Relay::kReverse);
	}
	else if (openingFloor) {
		if (BottomFloorOpenSwitch->Get()) {
			openingFloor = false;
			FloorDrive->Set(Relay::kOff);
		}
		else FloorDrive->Set(Relay::kForward);
	}
	else {
		FloorDrive->Set(Relay::kOff);
	}
}

void Collector::Disable(){
	
}
