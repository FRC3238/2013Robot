#include <WPILib.h>
#include "robot3238.h"
#include "Settings.h"

robot3238::robot3238(void) : DS(DriverStation::GetInstance()),DSEIO(DS->GetEnhancedIO()){
	
	driveJoystick = new Joystick (DriveJoystickPort);
	shootJoystick = new Joystick (ShootJoystickPort);
	theChassis = new Chassis(ChassisLeftMtr,ChassisRightMtr);
    theClimber = new Climber(ClimberLeftMtr, ClimberRightMtr, ClimberLeftEncoder, ClimberRightEncoder, -1);
    //theCollector = new Collector(FloorOpenSwitchPort, FloorCloseSwitchPort, BucketSwitchPort);
    theShooter = new Shooter(ShooterShooterMtr, ShooterTiltMtr, ShooterTach);
}
	
void robot3238::RobotInit(void) {
    SmartDashboard::init();

    theChassis->Init();
    theClimber->Init();
    theShooter->Init();

    DriverStationLCD::GetInstance()->PrintfLine(DriverStationLCD::kUser_Line1, __DATE__ " " __TIME__);
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
    Periodic();
    Settings.rehash();
    theChassis->SetBrake();
}

void robot3238::AutonomousPeriodic(void) {
    Periodic();
    theChassis->SetBrake();
}

void robot3238::TeleopPeriodic(void) {
    Periodic();

    float forward  = - driveJoystick->GetRawAxis(2); //getting forward and backward value from movement joystick
    float twist    = - driveJoystick->GetRawAxis(3); //getting the turning(twist) value from movement joystick
    float throttle = -(driveJoystick->GetRawAxis(4)/2 - .5);
    bool invert = driveJoystick->GetRawButton(2);
    theChassis->ArcadeDrive(forward, twist, throttle, invert);
    if(driveJoystick->GetRawButton(7) == 1){
        theChassis->ResetEncoders();
    }
    if(driveJoystick->GetRawButton(8) == 1){
        theClimber->StartClimb();
    }

    float shootPwr = shootJoystick->GetRawAxis(2);
    theShooter->ManualTilt(shootPwr);

    bool shoot = shootJoystick->GetRawButton(1);
    if (shoot) {
        theShooter->Shoot();
    }

    bool startShooter = shootJoystick->GetRawButton(3);
    bool stopShooter = shootJoystick->GetRawButton(4);
    if (startShooter) theShooter->StartShooter();
    else if (stopShooter) theShooter->StopShooter();
}

// Put things that should be done periodically in any mode here
void robot3238::Periodic(void) {
    SmartDashboard::PutNumber("RightEncoderValue", theChassis->GetRightEncoderValue());
    SmartDashboard::PutNumber("LeftEncoderValue", theChassis->GetLeftEncoderValue());
    SmartDashboard::PutNumber("RightEncoderDistance", theChassis->GetRightEncoderDistance());
    SmartDashboard::PutNumber("LeftEncoderDistance", theChassis->GetLeftEncoderDistance());
    SmartDashboard::PutNumber("ShooterRPM", theShooter->GetRPM());

    theChassis->Idle();
    theClimber->Idle();
    theShooter->Idle();
    DriverStationLCD::GetInstance()->UpdateLCD();
}

void robot3238::AutonomousContinuous(void){
}

START_ROBOT_CLASS(robot3238);
