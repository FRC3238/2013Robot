#include <WPILib.h>
#include "robot3238.h"
#include "Settings.h"

robot3238::robot3238(void) : DS(DriverStation::GetInstance()),DSEIO(DS->GetEnhancedIO()), insight(FOUR_ZONES){
	
    theSwag = new Swag(1, SwagArduinoNum);
    driveJoystick = new Joystick (DriveJoystickPort);
    shootJoystick = new Joystick (ShootJoystickPort);
    theChassis = new Chassis(ChassisLeftMtr, ChassisRightMtr, ChassisTiltMtr);
    theClimber = new Climber(ClimberLeftMtr, ClimberRightMtr, ClimberLeftEncoder, ClimberRightEncoder, ClimberDeployerLeftPort, ClimberDeployerRightPort);
    theCollector = new Collector(theSwag, FloorOpenSwitchPort, FloorCloseSwitchPort, BucketSwitchPort);
    theShooter = new Shooter(theSwag, ShooterShooterMtr, ShooterTiltMtr, ShooterTach);
    dropTimer = new Timer();
}
	
void robot3238::RobotInit(void) {
    SmartDashboard::init();

    theChassis->Init();
    theClimber->Init();
    theShooter->Init();
    insight_shootRPM.setHeader("RPM:");
    insight_shootAngle.setHeader("Ang:");
    insight.registerData(insight_shootRPM, 1);
    insight.registerData(insight_shootAngle, 2);
    insight.startDisplay();

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
    theCollector->Init();
    theChassis->SetBrake();
    dropTimer->Start();
    AutonomousState = preparingToShoot;
}

void robot3238::TeleopInit(void) {

    theChassis->Init();
    theCollector->Init();
    teleopMode = TM::NORMAL;
}

void robot3238::DisabledPeriodic(void)  {
    Periodic();
    Settings.rehash();
    theChassis->SetBrake();
}

bool robot3238::IsReadyToFire() {
	return theShooter->ShooterUpToSpeed() && theShooter->DoneShooting() && theCollector->isFrisbeeReady();
}

void robot3238::AutonomousPeriodic(void) {
    Periodic();
    AutonomousAngle = Settings.getLong("AutonomousAngle", AutonomousAngle, true);
    AutonomousRPM = Settings.getLong("AutonomousRPM", AutonomousRPM, true);
    theChassis->SetBrake();
    theChassis->TankDrive(0, 0, 0);
    theShooter->SetRPM(AutonomousRPM);
    switch (AutonomousState){
    
    case preparingToShoot:
    	if(IsReadyToFire()) {
        	theCollector->dropDisc();
    		AutonomousState = droppingDisc;
    	}
    break;
    
    case droppingDisc:
    	if(theCollector->doneDropping()){
    		dropTimer->Reset();
    		AutonomousState = settlingDisc;
    	}
    break;
    
    case settlingDisc:
    	if(dropTimer->Get() > 0.5){
        	AutonomousState = shooting;
    	}
    	break;
    
    case shooting:
    	theShooter->Shoot();
    	AutonomousState = preparingToShoot;
    break;
    }
}

void robot3238::TeleopPeriodic(void) {
    Periodic();

    static TM::TeleopMode lastMode = TM::NORMAL;
    if (!DS->GetDigitalIn(2)) teleopMode = TM::NORMAL;
    else teleopMode = TM::CLIMB;
    //if (teleopMode == TM::CLIMB && lastMode != TM::CLIMB) {
    if (teleopMode != lastMode) {
        theSwag->StartClimb(teleopMode == TM::CLIMB);
        lastMode = teleopMode;
    }
    if (driveJoystick->GetRawButton(4)) theSwag->DoneClimb();
    if (driveJoystick->GetRawButton(12)) theSwag->ResetSwag();

    bool raiseHooks = driveJoystick->GetRawButton(3);
    theClimber->RaiseHooks(raiseHooks);
    
    float driveForward  = driveJoystick->GetRawAxis(2);
    float shootForward  = shootJoystick->GetRawAxis(6);
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
        break;
    case TM::CLIMB:
        theClimber->ManualClimb(driveForward);
        break;
//    case TM::CLIMB_MAN:
//        //theClimber->ManualClimb(shootForward, driveForward);
//        theClimber->ManualClimb(driveForward, driveForward);
//        shootTiltPwr = 0;
//        break;
    }
    bool chassisInvert = driveJoystick->GetRawButton(2);

    theChassis->ArcadeDrive(chassisForward, chassisTwist, chassisThrottle, chassisInvert);
    theShooter->ManualTilt(shootTiltPwr);

    bool deployClimber = driveJoystick->GetRawButton(1);
    theClimber->Deploy(deployClimber);

    bool shoot = shootJoystick->GetRawButton(1);
    if (shoot) theShooter->Shoot();
    static TwoButtonToggle collectortoggle;
    theCollector->manualMode(collectortoggle.Set(shootJoystick->GetRawButton(11), shootJoystick->GetRawButton(12)));
    theCollector->manualFloorControl((int)shootJoystick->GetRawAxis(5));
    bool dropFrisbee = shootJoystick->GetRawButton(2);
    if (dropFrisbee) theCollector->dropDisc();
    bool collectorReInit = shootJoystick->GetRawButton(3);
    if (collectorReInit) theCollector->Init();

//    SmartDashboard::PutBoolean("Ds digital 4", DS->GetDigitalIn(4));
<<<<<<< HEAD
    if(shootJoystick->GetRawButton(7)){
    	theShooter->SetRawPower(-1.0);
    }
    else{
    	if (!DS->GetDigitalIn(4))      theShooter->SetRPM(2800); //theShooter->RampUpToValue(0.75);
    	else if (!DS->GetDigitalIn(6)) theShooter->SetRPM(3300); //theShooter->RampUpToValue(0.875);
    	else if (!DS->GetDigitalIn(8)) theShooter->SetRPM(10000); //theShooter->RampUpToValue(1);
    	else                           theShooter->SetRPM(0);    //theShooter->RampUpToValue(0);
    }
||||||| merged common ancestors
    if (!DS->GetDigitalIn(4))      theShooter->SetRPM(2800); //theShooter->RampUpToValue(0.75);
    else if (!DS->GetDigitalIn(6)) theShooter->SetRPM(3300); //theShooter->RampUpToValue(0.875);
    else if (!DS->GetDigitalIn(8)) theShooter->SetRPM(10000); //theShooter->RampUpToValue(1);
    else                           theShooter->SetRPM(0);    //theShooter->RampUpToValue(0);
    
=======
    //if (!DS->GetDigitalIn(4))      theShooter->SetRPM(2800); //theShooter->RampUpToValue(0.75);
    //else if (!DS->GetDigitalIn(6)) theShooter->SetRPM(3300); //theShooter->RampUpToValue(0.875);
    //else if (!DS->GetDigitalIn(8)) theShooter->SetRPM(10000); //theShooter->RampUpToValue(1);
    //else                           theShooter->SetRPM(0);    //theShooter->RampUpToValue(0);

    if (!DS->GetDigitalIn(4))      theShooter->SetManualSpeed(0.25);
    else if (!DS->GetDigitalIn(6)) theShooter->SetRPM(3300);
    else if (!DS->GetDigitalIn(8)) theShooter->SetManualSpeed(1.0);
    else                           theShooter->SetManualSpeed(0.0);
    
>>>>>>> e159e922308fc1d568ac5b3f5fad22d81b286086
//    static Toggle shootSpeedToggle;
//    if(shootSpeedToggle.Set(shootJoystick->GetRawButton(7))) theShooter->SetRPM(3500);
//    else theShooter->SetRPM(0);

    theChassis->ManualTilt(driveJoystick->GetRawAxis(6));
}

// Put things that should be done periodically in any mode here
void robot3238::Periodic(void) {
    int shootRPM = (int)theShooter->GetRPM();
    SmartDashboard::PutNumber("ShooterRPM", shootRPM);
    insight_shootRPM.setData(shootRPM);
    int shootAngle = (int)theShooter->GetAngle();
    SmartDashboard::PutNumber("ShooterTilt", shootAngle);
    insight_shootAngle.setData(shootAngle);

    static bool hadFrisbeeReady = false;
    bool haveFrisbeeReady = theCollector->isFrisbeeReady();
    if (hadFrisbeeReady != haveFrisbeeReady) {
        theSwag->HaveFrisbee(haveFrisbeeReady);
        hadFrisbeeReady = haveFrisbeeReady;
    }
    SmartDashboard::PutBoolean("hadfrisbee", hadFrisbeeReady);
    SmartDashboard::PutBoolean("havefrisbee", haveFrisbeeReady);
    
//    SmartDashboard::PutBoolean("CollectorfloorClosed", theCollector->isFloorClosed());
//    SmartDashboard::PutBoolean("CollectorfloorOpened", theCollector->isFloorOpen());
//    SmartDashboard::PutBoolean("CollectorhaveFrisbee", theCollector->isFrisbeeReady());
//    SmartDashboard::PutBoolean("CollectorReadyToFire", theCollector->doneDropping());
//    SmartDashboard::PutString("CollectorState", theCollector->getState());
    
//    SmartDashboard::PutBoolean("ShooterUpToSpeed", theShooter->ShooterUpToSpeed());
//    SmartDashboard::PutBoolean("AngleSet", theShooter->IsAngleSet());
//    SmartDashboard::PutBoolean("DoneShooting", theShooter->DoneShooting());
//    SmartDashboard::PutNumber("AutonomousState", (int)AutonomousState);

//    static int numLoops;
//    SmartDashboard::PutNumber("Num Loops", numLoops++);
    
//    SmartDashboard::PutNumber("DSEIO.GetButtons", DSEIO.GetButtons());
    
    SmartDashboard::PutBoolean("IsReadyToFire", IsReadyToFire());

    theChassis->Idle();
    theClimber->Idle();
    theCollector->Idle();
    theShooter->Idle();
    DriverStationLCD::GetInstance()->UpdateLCD();
}

START_ROBOT_CLASS(robot3238);
