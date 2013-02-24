#include "Climber.h"
#include "Settings.h"

Climber::Climber(UINT8 leftLiftIn, UINT8 rightLiftIn, UINT32 leftEncIn, UINT32 rightEncIn, UINT32 deployerLeftIn, UINT32 deployerRightIn) : 
    
	leftLiftPort(leftLiftIn), rightLiftPort(rightLiftIn),
    deployerLeftPort(deployerLeftIn), deployerRightPort(deployerRightIn),
    leftEncPort(leftEncIn), rightEncPort(rightEncIn),
    leftLift(leftLiftPort), rightLift(rightLiftPort),
    deployerLeft(deployerLeftPort), deployerRight(deployerRightPort),
    leftEnc(leftEncPort), rightEnc(rightEncPort)
    {
    // Set initial values for tunables
    syncP = 0.05;
    initialized = false;
}

bool Climber::Init() {
    leftEnc.Start();
    rightEnc.Start();
    leftEnc.Reset();
    rightEnc.Reset();
    leftLift.SetSafetyEnabled(false);
    rightLift.SetSafetyEnabled(false);
    initialized = true;
    return initialized;
}

void Climber::Disable() {
    leftLift .Set(0);
    rightLift.Set(0);
}

void Climber::ManualClimb(double left, double right) {
    leftLift.Set(left);
    rightLift.Set(right);
}

void Climber::ManualClimb(double spd) {
    INT32 lEncD = leftEnc.Get(), rEncD = rightEnc.Get();
    double adj = syncP * (lEncD - rEncD);
    SmartDashboard::PutNumber("ClimbLEnc", lEncD);
    SmartDashboard::PutNumber("ClimbREnc", rEncD);
    SmartDashboard::PutNumber("ClimbAdj", adj);
    SmartDashboard::PutNumber("Given spd", spd);
    SmartDashboard::PutNumber("climb_syncP", syncP);
    if (spd < -0.1) {
         leftLift.Set(spd);
        rightLift.Set(spd);
    }
    else if (spd > 0.1) {
         leftLift.Set(spd + adj);
        rightLift.Set(spd - adj);
    }
    else {
         leftLift.Set(0);
        rightLift.Set(0);
    }     
}

void Climber::Deploy(bool deploy) {
    deployerLeft.Set(deploy);
    deployerRight.Set(deploy);
}

void Climber::RaiseHooks(bool move){
	if(move){
		if (leftLift.GetReverseLimitOK()){
			leftLift.Set(-1);
		}
		else {
			leftLift.Set(0);
		}
		if (rightLift.GetReverseLimitOK()){
			rightLift.Set(-1);
		}
		else {
			rightLift.Set(0);
			move = false;
		}
	}
	else{}
}

void Climber::Idle() {
//    INT32 lEncD = leftEnc.Get(), rEncD = rightEnc.Get();
//    SmartDashboard::PutNumber("Climb_LeftEnc", lEncD);
//    SmartDashboard::PutNumber("Climb_RightEnc", rEncD);

    syncP = Settings.getDouble("Climb_syncP", syncP, false);
    if (!leftLift.GetReverseLimitOK() && !rightLift.GetReverseLimitOK()) {
    	leftEnc.Reset();
    	rightEnc.Reset();
    }
}
