#ifndef COLLECTOR_H
#define COLLECTOR_H

#include <WPILib.h>
#include "Portnums.h"

enum {
	limbo,
	isEmpty,
	loaded,
	running,
};

enum {
	stepCloseFloor,
	stepOpenFloor, 
	stepCloseIris,
	stepOpenIris,
	stepModeEmpty,
	stepModeLoaded,
};

const double IrisTime = 1.0;
const float unlockRight = 1;
const float unlockLeft = 1;
const float lockRight = 1;
const float lockLeft = 1;
const float lockLipVal = 1;
const float unlockLipVal = 1;

class QueueItem{
public:
	
	QueueItem(int data);
	~QueueItem();
	void AddItem(QueueItem* list);
	int mData;
	QueueItem* next;
};


class Queue {
public:
	
	Queue();
	void push(int data);
	void pop();
	bool empty();
	void dump();
	int top();
	QueueItem* list;
};


class Collector : public Queue {
public:
    // These methods are visable (callable) to anyone using this class
    // If you wish to add or remove any public methods, talk to Nick Papadakis

    // Constructor
    Collector(UINT32 BotFloorOpenSwitch, UINT32 BotFloorCloseSwitch, UINT32 bucketThingy);
    void Init();
    void start();
    bool isFrisbeeReady();
    void dropDisc();
    
    void testOpenIris();
    void testCloseIris();
    void testUnlockLip();
    void testLockLip();
    void testOpenFloor();
    void testCloseFloor();
    bool testFloorClosed();
    bool testFloorOpened();
    bool testHaveFrisbee();
    
    
    void Disable();
    
    void Idle();

private:
    // Put useful functions and variables here
	void unlockLip();
	void lockLip();
	void openFloor();
	void openIris();
	void closeIris();
	void shutoffFloor();
	void closeFloor();
	void checkStep();
	void startStep();
	bool isFloorClose();
	bool isFloorOpen();
	bool Initialized;
	DigitalInput *bucketStatusSwitch; 
	DigitalInput *BottomFloorOpenSwitch;
	DigitalInput *BottomFloorCloseSwitch;
	Relay *FloorDrive;
	Servo *IrisServoRight;
	Servo *IrisServoLeft;
	Timer *IrisTimer;
	Servo *lipDrive;
	int state;
};

#endif
