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
    
    //Gets the shooter up to full speed
    void StartShooter();
    
    //Stops the shooter
    void StopShooter();
    
    //Set the shooter to a specific angle
    void SetAngle(float desiredAngle);
    
    //Allows for manual control of the tilting mechanism
    void ManualAngle(float power);
    
    //Fires one frisbee from the shooter
    void Shoot();
    
    //Gets the current angle of the shooter
    float GetAngle();

    // Turns off all motors controlled by this class
    void Disable();

    // Does general processing and should be called every 20ms
    void Idle();

private:
    // Put useful functions and variables here
	bool Initialized;
	bool StartingShooter;
	float Angle;
	int motorDirection;
	float currentAngle;
	bool shooting;
	float totalSpoolUpTime;
	CANJaguar *shootJag;
	CANJaguar *tiltJag;
	Timer *spoolUpTimer;
	Timer *shootTimer;
	AnalogChannel *anglePot;
	Servo *shootServo;
};

#endif
