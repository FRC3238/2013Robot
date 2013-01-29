#include "Climber.h"
using namespace ClimberTunables;

// TODO: Add code for flopper (servo?)
// TODO: Add code for driver override
// TODO: Test, tune ClimberTunables
// Find sensor that can act as encoder
// Add code to differentiate between "done" and "disabled" for victory lights, etc
// Put PID loop in to make both sides run same speed

Climber::Climber(UINT8 leftLiftIn, UINT8 rightLiftIn, UINT8 leftEncIn, UINT8 rightEncIn, UINT8 flopDownIn) : 
    initialized(false),
    leftLiftPort(leftLiftIn), rightLiftPort(rightLiftIn),
    leftEncPort(leftEncIn), rightEncPort(rightEncIn),
    flopDownPort(flopDownIn),
    leftLift(leftLiftPort), rightLift(rightLiftPort),
    leftEnc(leftEncPort), rightEnc(rightEncPort)
    {
    
}

bool Climber::Init() {
    initialized = true;
    return initialized;
}

void Climber::StartClimb() {
    // All work done in Idle()
    CS = TILTED;
}

Climber::ClimberState Climber::GetClimberState() {
    return CS;
}

void Climber::Disable() {
    leftLift.Disable();
    rightLift.Disable();
}

void Climber::Idle() {
    if (CS != DEACTIVATED) AutoLift();
    else {
        leftLift.Disable();
        rightLift.Disable();
    }
}

void Climber::AutoLift() {

    /* Every "up" or "down" is based on the upper hook
    lv: 
     0  0) Start down
     0  1) Move up to grab rung 1
     1  2) Move down to pass off rung 1
     1  3) Move up to grab rung 2
     2  4) Move down to pass off rung 2
     2  5) Move up to grab rung 3
     3  6) Move down to finish
     */

    INT32 lEncD = leftEnc.Get(), rEncD = rightEnc.Get();
    static float liftSpd = 0.0;
    switch(CS) {
    case DEACTIVATED:
        break;
    case TILTED:
        // deploy
        CS = DEPLOYED;
    case DEPLOYED:
        // ??? Line up further? Wait for driver signal?
        liftSpd = 1.0;
        CS = C1;
    case C1: case C2: case C3: case C4: case C5: case C6: 
        if (lEncD > TicksPerSweep && rEncD > TicksPerSweep) {
             leftEnc.IncreaseOffset(TicksPerSweep);
            rightEnc.IncreaseOffset(TicksPerSweep);
            CS = (ClimberState)(CS + 1);
            if (CS > C6) CS = DEACTIVATED;
            liftSpd = -liftSpd;
        }
        break;
    }
    double adj = syncP * (lEncD - rEncD);
    if (liftSpd > 0) {
         leftLift.Set(liftSpd - adj);
        rightLift.Set(liftSpd + adj);
    }
    else {
         leftLift.Set(liftSpd + adj);
        rightLift.Set(liftSpd - adj);
    }
}
