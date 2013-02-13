#include <WPILib.h>
#include "robot3238.h"
#include "Settings.h"

robot3238::robot3238(void) : DS(DriverStation::GetInstance()),DSEIO(DS->GetEnhancedIO()){
	
    driveJoystick = new Joystick (DriveJoystickPort);
    shootJoystick = new Joystick (ShootJoystickPort);
    theChassis = new Chassis(ChassisLeftMtr, ChassisRightMtr, ChassisTiltMtr);
    theClimber = new Climber(ClimberLeftMtr, ClimberRightMtr, ClimberLeftEncoder, ClimberRightEncoder, ClimberDeployerLeftPort, ClimberDeployerRightPort);
    theCollector = new Collector(FloorOpenSwitchPort, FloorCloseSwitchPort, BucketSwitchPort);
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
    theCollector->Disable();
}

void robot3238::AutonomousInit(void) {

    theChassis->Init();
    theChassis->SetBrake();
}

void robot3238::TeleopInit(void) {

    theChassis->Init();
    theCollector->Init();
    //theCollector->start();
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

namespace TM {
    enum TeleopMode {NORMAL, CLIMB_P, CLIMB_MAN, };
}
TM::TeleopMode teleopMode;

void robot3238::TeleopPeriodic(void) {
    Periodic();

    if (driveJoystick->GetRawButton(10)) teleopMode = TM::NORMAL;
    else if (driveJoystick->GetRawButton(11)) teleopMode = TM::CLIMB_MAN;
    else if (driveJoystick->GetRawButton(12)) teleopMode = TM::CLIMB_P;

    float driveForward  = driveJoystick->GetRawAxis(2);
    float shootForward  = shootJoystick->GetRawAxis(2);
    float driveTwist    = driveJoystick->GetRawAxis(3);
    float driveThrottle = -(driveJoystick->GetRawAxis(4)/2 - .5);
    float chassisForward = 0, chassisTwist = 0, chassisThrottle = 0;
    float shootTiltPwr = shootForward;
    switch (teleopMode) {
    case TM::NORMAL:
        if (driveJoystick->GetRawButton(2))
             chassisThrottle = driveThrottle/2;
        else chassisThrottle = driveThrottle;
        chassisForward = -driveForward;
        chassisTwist = -driveTwist;
        theClimber->Disable();

        break;
    case TM::CLIMB_P:
        theClimber->ManualClimb(driveForward);
        break;
    case TM::CLIMB_MAN:
        //theClimber->ManualClimb(shootForward, driveForward);
        theClimber->ManualClimb(driveForward, driveForward);
        shootTiltPwr = 0;
        break;
    }
    bool chassisInvert = driveJoystick->GetRawButton(2);
    theChassis->ArcadeDrive(chassisForward, chassisTwist, chassisThrottle, chassisInvert);
    theShooter->ManualTilt(shootTiltPwr);

    bool deployClimber = driveJoystick->GetRawButton(3);
    theClimber->Deploy(deployClimber);

    bool shoot = shootJoystick->GetRawButton(1);
    if (shoot) {
        theShooter->Shoot();
    }
    bool dropFrisbee = shootJoystick->GetRawButton(2);
    if (dropFrisbee) theCollector->dropDisc();
    bool collectorReInit = shootJoystick->GetRawButton(9);
    if (collectorReInit) theCollector->Init();

    if (!DS->GetDigitalIn(4)) theShooter->RampUpToValue(0.75);
    else if (!DS->GetDigitalIn(6)) theShooter->RampUpToValue(0.875);
    else if (!DS->GetDigitalIn(8)) theShooter->RampUpToValue(1);
    else theShooter->RampUpToValue(0);
    bool startShooter = shootJoystick->GetRawButton(3);
    bool stopShooter = shootJoystick->GetRawButton(4);
    if (startShooter) theShooter->StartShooter();
    else if (stopShooter) theShooter->StopShooter();

    theChassis->ManualTilt(driveJoystick->GetRawAxis(6));
}

// Put things that should be done periodically in any mode here
void robot3238::Periodic(void) {
    SmartDashboard::PutNumber("RightEncoderValue", theChassis->GetRightEncoderValue());
    SmartDashboard::PutNumber("LeftEncoderValue", theChassis->GetLeftEncoderValue());
    SmartDashboard::PutNumber("RightEncoderDistance", theChassis->GetRightEncoderDistance());
    SmartDashboard::PutNumber("LeftEncoderDistance", theChassis->GetLeftEncoderDistance());
    SmartDashboard::PutNumber("ShooterRPM", theShooter->GetRPM());
    SmartDashboard::PutNumber("ShooterTilt", theShooter->GetAngle());

    SmartDashboard::PutBoolean("CollectorfloorClosed", theCollector->testFloorClosed());
    SmartDashboard::PutBoolean("CollectorfloorOpened", theCollector->testFloorOpened());
    SmartDashboard::PutBoolean("CollectorhaveFrisbee", theCollector->testHaveFrisbee());
    
    SmartDashboard::PutString("CollectorState", theCollector->getState());

    static int numLoops;
    SmartDashboard::PutNumber("Num Loops", numLoops++);

    //SmartDashboard::PutNumber("DSEIO.GetButtons", DSEIO.GetButtons());


    theChassis->Idle();
    theClimber->Idle();
    theCollector->Idle();
    theShooter->Idle();
    DriverStationLCD::GetInstance()->UpdateLCD();
}

void robot3238::AutonomousContinuous(void){
}

START_ROBOT_CLASS(robot3238);
