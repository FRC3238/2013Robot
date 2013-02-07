#include "Climber.h"
#include "Settings.h"

// TODO: Add code for flopper (servo?)
// TODO: Add code for driver override
// TODO: Test, tune tunables
// Find sensor that can act as encoder
// Add code to differentiate between "done" and "disabled" for victory lights, etc
// Put PID loop in to make both sides run same speed

Climber::Climber(UINT8 leftLiftIn, UINT8 rightLiftIn, UINT32 leftEncIn, UINT32 rightEncIn, UINT8 flopDownIn) : 
    initialized(false),
    CS(DEACTIVATED),
    leftLiftPort(leftLiftIn), rightLiftPort(rightLiftIn),
    flopDownPort(flopDownIn),
    leftEncPort(leftEncIn), rightEncPort(rightEncIn),
    leftLift(leftLiftPort), rightLift(rightLiftPort),
    leftEnc(leftEncPort), rightEnc(rightEncPort)
    {

    // Set initial values for tunables
    syncP = 0.05;
    TicksAtBeginning = 100;
    TicksAtEnd = 50;
    leftMtrFactor = 0.75, rightMtrFactor = 0.75;
    
}

bool Climber::Init() {
    initialized = true;

     leftEnc.Start();
    rightEnc.Start();
     leftEnc.Reset();
    rightEnc.Reset();
    return initialized;
}

void Climber::StartClimb(bool start) {
    // All work done in Idle()
    if (start && CS == DEACTIVATED) CS = SHOOTER_RAISED;
}

void Climber::DoneTilting(bool done) {
    if (done && CS == WAITING_FOR_TILT) CS = TILTED;
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
    INT32 lEncD = leftEnc.Get(), rEncD = rightEnc.Get();
    SmartDashboard::PutNumber("Climb_LeftEnc", lEncD);
    SmartDashboard::PutNumber("Climb_RightEnc", rEncD);

    syncP =          Settings.getDouble("Climb_syncP", syncP, true);
    TicksAtEnd =     Settings.getLong  ("Climb_TicksAtEnd", TicksAtEnd, true);
    leftMtrFactor =  Settings.getDouble("Climb_leftMtrFactor", leftMtrFactor, true);
    rightMtrFactor = Settings.getDouble("Climb_rightMtrFactor", rightMtrFactor, true);
}

void Climber::AutoLift() {

    /* Every "up" or "down" is based on the upper hook
    lv: 
     0  0) Start down with 4 frisbees and raised shooter when button is pressed
     0  1) Move up a little
     0  2) Wait for drivers to line up, tilt, and press button
     1  3) Move down to pass off rung 1
     1  4) Move up to grab rung 2
     2  5) Move down to pass off rung 2
     2  7) Move up to grab rung 3
     3  7) Move down to finish
     */

    INT32 lEncD = leftEnc.Get(), rEncD = rightEnc.Get();
    float liftSpd = 0.0;
    switch(CS) {
    case DEACTIVATED:
        liftSpd = 0;
        break;
    case SHOOTER_RAISED:
        // TODO
        liftSpd = 1.0;
        if (lEncD > TicksAtBeginning || rEncD > TicksAtBeginning) CS = WAITING_FOR_TILT;
        break;
    case WAITING_FOR_TILT:
        // wait for signal from 
        liftSpd = 0;
        break;
    case TILTED:
        liftSpd = 0;
        // deploy
        CS = DEPLOYED;
        break;
    case DEPLOYED:
        // ??? Line up further? Wait for driver signal?
        liftSpd = 1.0;
        CS = C1;
    case C1: case C3: case C5:
        // Down
        if (!leftLift.GetForwardLimitOK() || !rightLift.GetForwardLimitOK()) {
            CS = (ClimberState)(CS + 1);
            if (CS > C5) CS = DEACTIVATED;
            liftSpd = -1.0;
        }
        break;
    case C2: case C4:
        // Down
        if (!leftLift.GetReverseLimitOK() || !rightLift.GetReverseLimitOK()) {
            CS = (ClimberState)(CS + 1);
            liftSpd = 1.0;
        }
        break;
    }
    double adj = syncP * (lEncD - rEncD);
    if (liftSpd > 0) {
         leftLift.Set( leftMtrFactor*(liftSpd - adj));
        rightLift.Set(rightMtrFactor*(liftSpd + adj));
    }
    else {
         leftLift.Set( leftMtrFactor*(liftSpd + adj));
        rightLift.Set(rightMtrFactor*(liftSpd - adj));
    }
}
