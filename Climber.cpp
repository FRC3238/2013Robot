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
}

bool Climber::Init() {
    initialized = true;

     leftEnc.Start();
    rightEnc.Start();
     leftEnc.Reset();
    rightEnc.Reset();
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
    if (spd > 0) {
         leftLift.Set(spd - adj);
        rightLift.Set(spd + adj);
    }
    else if (spd < 0) {
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

void Climber::Idle() {
    INT32 lEncD = leftEnc.Get(), rEncD = rightEnc.Get();
    SmartDashboard::PutNumber("Climb_LeftEnc", lEncD);
    SmartDashboard::PutNumber("Climb_RightEnc", rEncD);

    syncP = Settings.getDouble("Climb_syncP", syncP, true);
}
