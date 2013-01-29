#ifndef ROBOT3238_H
#define ROBOT3238_H

#include <WPILib.h>
#include "Chassis.h"

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

private:
	Chassis *theChassis;
	Joystick *driveJoystick;
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
