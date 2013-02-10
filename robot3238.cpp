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

void robot3238::TeleopPeriodic(void) {
    Periodic();

    float forward;
    float twist;
    float throttle;
    static Toggle joysticksAsClimberToggle;
    if (joysticksAsClimberToggle.Set(driveJoystick->GetRawButton(12))) {
        forward = twist = throttle = 0;
        theClimber->ManualClimb(driveJoystick->GetRawAxis(2), shootJoystick->GetRawAxis(2));
    } else {
        forward  = - driveJoystick->GetRawAxis(2); //getting forward and backward value from movement joystick
        twist    = - driveJoystick->GetRawAxis(3); //getting the turning(twist) value from movement joystick
        throttle = -(driveJoystick->GetRawAxis(4)/2 - .5);
    }
    SmartDashboard::PutBoolean("Climb Mode", joysticksAsClimberToggle.Get());
    bool invert = driveJoystick->GetRawButton(2);
    theChassis->ArcadeDrive(forward, twist, throttle, invert);
    if(driveJoystick->GetRawButton(7) == 1){
        theChassis->ResetEncoders();
    }
    //static bool climbing = false;
    //if (!climbing) {
    //    if (driveJoystick->GetRawButton(8)){
    //        theClimber->StartClimb();
    //        climbing = true;
    //    }
    //} else if (theClimber->IsReadyToTilt() && driveJoystick->GetRawButton(9)) {
    //    theClimber->DoneTilting();
    //}

    float shootPwr = shootJoystick->GetRawAxis(2);
    theShooter->ManualTilt(shootPwr);

    //bool dropFrisbee = shootJoystick->GetRawButton(2);
    //if (dropFrisbee) {
    //    theCollector->dropDisc();
    //}
    
    bool shoot = shootJoystick->GetRawButton(1);
    if (shoot) {
        theShooter->Shoot();
    }

//    if (theCollector->testHaveFrisbee()) {
//        theCollector->testOpenIris();
//    }
//    else {
//        theCollector->testCloseIris();
//    }
//
//    float colfloorval = driveJoystick->GetRawAxis(6);
//    if(colfloorval > 0.5)
//        theCollector->FloorDrive->Set(Relay::kForward);
//    else if (colfloorval < -0.5)
//        theCollector->FloorDrive->Set(Relay::kReverse);
//    else
//        theCollector->FloorDrive->Set(Relay::kOff);

    bool dropFrisbee = shootJoystick->GetRawButton(9);
    if (dropFrisbee) theCollector->dropDisc();
    bool collectorReInit = shootJoystick->GetRawButton(10);
    if (collectorReInit) theCollector->Init();
    theCollector->Idle();
    bool startShooter = shootJoystick->GetRawButton(3);
    bool stopShooter = shootJoystick->GetRawButton(4);
    if (startShooter) theShooter->StartShooter();
    else if (stopShooter) theShooter->StopShooter();
    theChassis->ManualTilt(shootJoystick->GetRawAxis(6));
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


    theChassis->Idle();
    theClimber->Idle();
    //theCollector->Idle();
    theShooter->Idle();
    DriverStationLCD::GetInstance()->UpdateLCD();
}

void robot3238::AutonomousContinuous(void){
}

START_ROBOT_CLASS(robot3238);
