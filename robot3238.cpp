#include <WPILib.h>
#include "robot3238.h"

robot3238::robot3238(void) : DS(DriverStation::GetInstance()),DSEIO(DS->GetEnhancedIO()){
	
	driveJoystick = new Joystick (DriveJoystickPort);
	theChassis = new Chassis(ChassisLeftMtr,ChassisRightMtr);
    theClimber = new Climber(ClimberLeftMtr, ClimberRightMtr, ClimberLeftEncoder, ClimberRightEncoder, -1);
}
	
	void robot3238::RobotInit(void) {
		
		theChassis->Init();
        theClimber->Init();
		SmartDashboard::init();
		printf("RobotInit() Completed\n");
	}
	
	void robot3238::DisabledInit(void) {
	
		theChassis->Init();
		theChassis->SetBrake();
	}

	void robot3238::AutonomousInit(void) {
	
		theChassis->Init();
		theChassis->SetBrake();
	}

	void robot3238::TeleopInit(void) {
	
		theChassis->Init();
	}
	
	void robot3238::DisabledPeriodic(void)  {
	
	    theChassis->Idle();
	    theChassis->SetBrake();
	}

	void robot3238::AutonomousPeriodic(void) {
	
	    theChassis->Idle();
	    theChassis->SetBrake();
		theChassis->MoveDistanceTank(60, 60);
	}
	
	void robot3238::TeleopPeriodic(void) {
	
	    theChassis->Idle();
	    float forward = -driveJoystick->GetRawAxis(2); //getting forward and backward value from movement joystick
	    float twist = -driveJoystick->GetRawAxis(3); //getting the turning(twist) value from movement joystick
	    float throttle = -(driveJoystick->GetRawAxis(4)/2 - .5);
		bool invert = driveJoystick->GetRawButton(2);
	    theChassis->ArcadeDrive(forward, twist, throttle, invert);
	    SmartDashboard::PutNumber("RightEncoderValue", theChassis->GetRightEncoderValue());
	    SmartDashboard::PutNumber("LeftEncoderValue", theChassis->GetLeftEncoderValue());
	    SmartDashboard::PutNumber("RightEncoderDistance", theChassis->GetRightEncoderDistance());
	    SmartDashboard::PutNumber("LeftEncoderDistance", theChassis->GetLeftEncoderDistance());
	    if(driveJoystick->GetRawButton(7) == 1){
	    	theChassis->ResetEncoders();
	    }
	    if(driveJoystick->GetRawButton(8) == 1){
            theClimber->StartClimb();
        }
        theClimber->Idle();
        DriverStationLCD::GetInstance()->UpdateLCD();
	}
	
	void robot3238::AutonomousContinuous(void){
	}

START_ROBOT_CLASS(robot3238);
