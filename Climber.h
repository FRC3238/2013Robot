#ifndef CLIMBER_H
#define CLIMBER_H

#include <WPILib.h>
#include "SettableCounter.h"
#include "Portnums.h"

class Climber {
public:
    // Tunables
    double syncP;
    INT32 TicksPerSweep;
    INT32 TicksAtEnd;
    double leftMtrFactor, rightMtrFactor;

    // These methods are visable (callable) to anyone using this class
    // If you wish to add or remove any public methods, talk to Nick Papadakis
    enum ClimberState { DEACTIVATED, TILTED, DEPLOYED, C1, C2, C3, C4, C5, C6, };

    // Constructor
    Climber(UINT8 leftLiftIn, UINT8 rightLiftIn, UINT32 leftEncIn, UINT32 rightEncIn, UINT8 flopDownIn);
    
    //Initialization
    bool Init();
    
    // Robot MUST already be tilted
    void StartClimb();

    ClimberState GetClimberState();

    // Turns off all motors controlled by this class
    void Disable();

    // Does general processing and should be called every 20ms
    void Idle();

private:
    // Put useful functions and variables here
    void AutoLift();

	bool initialized;
    ClimberState CS;
    UINT8 leftLiftPort, rightLiftPort, flopDownPort;
    UINT32 leftEncPort, rightEncPort;
    CANJaguar leftLift, rightLift;
    SettableCounter leftEnc, rightEnc;

    INT32 leftEncOffset, rightencOffset;
};

#endif
