#ifndef ROBOT3238_H
#define ROBOT3238_H

#include <WPILib.h>
#include "Chassis.h"
#include "Climber.h"
#include "Collector.h"
#include "Shooter.h"
#include "Toggle.h"

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
	SmartDashboard *smartdash;
	Preferences *robotpreferences;
	DriverStationLCD *dsLCD;
	Solenoid *LightSensorSolenoid;
	DigitalInput *LightSensorDarkInput;
	DigitalInput *LightSensorLightInput;
};

#endif
