#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <WPILib.h>

class Collector {
public:
    // These methods are visable (callable) to anyone using this class
    // If you wish to add or remove any public methods, talk to Nick Papadakis

    // Constructor
    Collector(UINT32 BotFloorOpenSwitch, UINT32 BotFloorCloseSwitch, UINT32 bucketThingy);
    
    //Initializes
    void Init();

    //Checks to see if we're done dropping a disc
    bool doneDropping();
    
    //Drops a disc
    void dropDisc();
    
    //Changes the floor control to manual mode
    void manualMode(bool mode);
    
    //Manual control of the collector
    void manualFloorControl(int direction);
    
    //Various test functions for debugging
    string getState();
    
    bool isFloorOpen()    { return BottomFloorOpenSwitch->Get(); }
    bool isFloorClosed()  { return BottomFloorCloseSwitch->Get(); }
    bool isFrisbeeReady() { return bucketStatusSwitch->Get(); }

    void lockServos()   { lockingServos = true; }
    void unlockServos() { lockingServos = false;}
    void closeFloor()   { closingFloor = true; openingFloor = false; }
    void openFloor()    { openingFloor = true; closingFloor = false; }
    void stopFloor()    { closingFloor = false; openingFloor = false; }

    //General processing
    void Idle();
    
    //Shuts off motors, empties Queue
    void Disable();

private:
    struct ST {
    	enum CollectorState { READY, SERVOS_LOCK, FLOOR_OPEN, FLOOR_WAIT, FLOOR_CLOSE, SERVOS_UNLOCK, };
    };
    ST::CollectorState CS;
    
	bool Initialized;
	bool manual;
	DigitalInput *bucketStatusSwitch; 
	DigitalInput *BottomFloorOpenSwitch;
	DigitalInput *BottomFloorCloseSwitch;
	Relay *FloorDrive;
	Servo *ServoLockRight;
	Servo *ServoLockLeft;
	
	Timer *AllPurposeTimer;

	bool lockingServos, closingFloor, openingFloor;
};

#endif
