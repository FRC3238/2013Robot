#ifndef SHOOTER_H
#define SHOOTER_H

#include <WPILib.h>
#include "Portnums.h"
#include "Settings.h"
#include "ShootTach.h"
#include "Swag.h"

class Shooter {
public:
    // These methods are visable (callable) to anyone using this class
    // If you wish to add or remove any public methods, talk to Nick Papadakis

    // Constructor
    Shooter(Swag* theSwagIn, int shootIn, int tiltIn, int tachPortIn);
    
    //Initialization
    bool Init();
    
    //Gets the shooter up to full speed
    void StartShooter();
    
    //Stops the shooter
    void StopShooter();
    
    //Sets the shooter to a specific RPM
    void SetRPM(float rpm);
    
    //Set the shooter to a specific angle
    void SetAngle(float desiredAngle);
    
    //Allows for manual control of the tilting mechanism
    void ManualTilt(float power);
    
    //Fires one frisbee from the shooter
    void Shoot();
    
    //Gets the current angle of the shooter
    int GetAngle();

    // Gets current speed of shooter
    float GetRPM();
    
    //Checks if the shooter is up to speed
    bool ShooterUpToSpeed();
    
    //Checks to see if the angles is set
    bool IsAngleSet();
    
    //Checks to see if the shooter is done shooting a frisbee
    bool DoneShooting();
    
    //Sets the Jaguar of the shooter directly
    void SetRawPower(float power);

    // Does general processing and should be called every 20ms
    void Idle();
    
    // Turns off all motors controlled by this class
    void Disable();
<<<<<<< HEAD
	
||||||| merged common ancestors

=======

    void SetManualSpeed(float spd);
>>>>>>> e159e922308fc1d568ac5b3f5fad22d81b286086
private:
    // Put useful functions and variables here
	bool Initialized;
    float desiredRPM;
    float desiredAngle;
    float currentAngle;
    bool doneShooting;
	CANJaguar *shootJag;
	CANJaguar *tiltJag;
	Timer *shootTimer;
	AnalogChannel *anglePot;
	Servo *shootServo;
    DigitalInput *tachIn;
    ShootTach *tach;
    Swag* theSwag;
<<<<<<< HEAD
    bool useBangBang;
    float rawPower;
||||||| merged common ancestors
=======

    bool controlSpeed;
    float manualSpeed;
>>>>>>> e159e922308fc1d568ac5b3f5fad22d81b286086
};

#endif
