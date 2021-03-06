#ifndef ROBOT3238_H
#define ROBOT3238_H

#include <WPILib.h>
#include "Chassis.h"
#include "Climber.h"
#include "Collector.h"
#include "Shooter.h"
#include "Swag.h"
#include "Toggle.h"
#include "TwoButtonToggle.h"
#include "InsightLT_CPP/InsightLT.h"
using namespace insight;

class robot3238 : public IterativeRobot {

public:
	robot3238(void);
	void RobotInit(void);
	void DisabledInit(void);
	void DisabledPeriodic(void);
	void AutonomousInit(void);
	void AutonomousPeriodic(void);
	void AutonomousContinuous(void);
	void TeleopInit(void);
	void TeleopPeriodic(void);
	void Periodic(void);
	bool IsReadyToFire();
private:
	Chassis *theChassis;
    Climber *theClimber;
    Collector *theCollector;
    Shooter *theShooter;
    Swag *theSwag;
	Joystick *driveJoystick;
    Joystick *shootJoystick;
	DriverStation *DS;
	DriverStationEnhancedIO &DSEIO;
	//SmartDashboard *smartdash;
	Preferences *robotpreferences;
	DriverStationLCD *dsLCD;
	Solenoid *LightSensorSolenoid;
	DigitalInput *LightSensorDarkInput;
	DigitalInput *LightSensorLightInput;
    InsightLT insight;
    IntegerData insight_shootRPM;
    IntegerData insight_shootAngle;
    Timer *dropTimer;
    enum AutonomousState_t{
    	preparingToShoot,
    	droppingDisc,
    	settlingDisc,
    	shooting,
    };
    struct TM {
        enum TeleopMode {NORMAL, CLIMB,};
    };
    TM::TeleopMode teleopMode;
    
    AutonomousState_t AutonomousState;
    long AutonomousAngle;
    long AutonomousRPM;
};

#endif
