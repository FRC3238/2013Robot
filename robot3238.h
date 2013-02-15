#ifndef ROBOT3238_H
#define ROBOT3238_H

#include <WPILib.h>
#include "Chassis.h"
#include "Climber.h"
#include "Collector.h"
#include "Shooter.h"
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

private:
	Chassis *theChassis;
    Climber *theClimber;
    Collector *theCollector;
    Shooter *theShooter;
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
    enum AutonomousState_t{
    	preparingToShoot,
    	droppingDisc,
    	shooting,
    };
    
    AutonomousState_t AutonomousState;
    long AutonomousAngle;
    long AutonomousRPM;
};

#endif
