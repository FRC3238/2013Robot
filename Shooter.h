#ifndef SHOOTER_H
#define SHOOTER_H

#include <WPILib.h>
#include "Portnums.h"

class Shooter {
public:
    // These methods are visable (callable) to anyone using this class
    // If you wish to add or remove any public methods, talk to Nick Papadakis

    // Constructor
    Shooter(int shootIn, int tiltIn);
    
    //Initialization
    bool Init();
    
    void StartShooter();
    
    void Tilt(float angle);
    
    bool IsTiltSet();
    
    void Shoot();
    
    float GetAngle();
    
    bool Loaded();

    // Turns off all motors controlled by this class
    void Disable();

    // Does general processing and should be called every 20ms
    void Idle();

private:
    // Put useful functions and variables here
	bool Initialized;
};

#endif
