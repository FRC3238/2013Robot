#ifndef CLIMBER_H
#define CLIMBER_H

#include <WPILib.h>
#include "SettableCounter.h"
#include "Portnums.h"

class Climber {
public:
    // Tunables
    double syncP;

    // Constructor
    Climber(UINT8 leftLiftIn, UINT8 rightLiftIn, UINT32 leftEncIn, UINT32 rightEncIn, UINT32 deployerLeftIn, UINT32 deployerRightIn);
    
    //Initialization
    bool Init();
    
    // Climbs manually keeping the sides in sync with a P loop
    void ManualClimb(double spd);
    
    // Runs each motor with the given values
    void ManualClimb(double left, double right);

    //Releases the solenoids to deploy the climber
    void Deploy(bool deploy);
    
    //Raises the hooks all the way
    void RaiseHooks() { raisingHooks = true; }
    bool IsRaisingHooks() { return raisingHooks; }
    void StopRaisingHooks() { raisingHooks = false; }

    // Turns off all motors controlled by this class
    void Disable();

    // Does general processing and should be called every 20ms
    void Idle();

private:
    // Put useful functions and variables here

	bool initialized;
    UINT8 leftLiftPort, rightLiftPort;
    UINT32 deployerLeftPort, deployerRightPort;
    UINT32 leftEncPort, rightEncPort;
    CANJaguar leftLift, rightLift;
    Solenoid deployerLeft, deployerRight;
    Counter leftEnc, rightEnc;

    bool raisingHooks;
};

#endif
