#pragma config(Sensor, in1,    potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl3,  pistonLock1,    sensorDigitalOut)
#pragma config(Sensor, dgtl4,  pistonLock2,    sensorDigitalOut)
#pragma config(Sensor, dgtl5,  touchSensor,    sensorTouch)
#pragma config(Motor,  port1,           frontRightMotor, tmotorVex393, openLoop)
#pragma config(Motor,  port2,           backRightMotor, tmotorVex393, openLoop)
#pragma config(Motor,  port3,           backLeftMotor, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           bottomRightTower, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           bottomLeftTower, tmotorVex393, openLoop)
#pragma config(Motor,  port6,           takeLeft,      tmotorVex393, openLoop)
#pragma config(Motor,  port7,           takeRight,     tmotorVex393, openLoop)
#pragma config(Motor,  port8,           topLeftTower,  tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           topRightTower, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          frontLeftMotor, tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define FULL_POWER 127
#define HALF_POWER 63
#define STOP 0

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

string mainBattery;
string backupBattery;

short programChoice;

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c" � //Main competition background code...do not modify!

// Move drive at full power for �timer� milliseconds either forward (1) or backward (-1)
void moveDrive(int direction, int timer=0) {
	// Check for function input error
	if(direction == 1 || direction == -1 || direction == 0){
		// Move at 100% power
		motor[frontRightMotor]	 = FULL_POWER * direction;
		motor[frontLeftMotor] 	 = FULL_POWER * direction;
		motor[backRightMotor]	   = FULL_POWER * direction;
		motor[backLeftMotor]	   = FULL_POWER * direction;
	}

	if(timer != 0) {
		// Wait �timer� ms
		wait1Msec(timer);

		// Stop
		motor[frontRightMotor]	 = STOP;
		motor[frontLeftMotor] 	 = STOP;
		motor[backRightMotor]	   = STOP;
		motor[backLeftMotor]	   = STOP;
	}
}

// Move arm at full power for �timer� milliseconds either forward (1) or backward (-1)
void moveArm(int direction, int timer=0) {
	// Check for function input error
	if(direction == 1 || direction == -1 || direction == 0){
		// Move at 100% power
		motor[topRightTower]	   = FULL_POWER * direction;
		motor[topLeftTower] 	   = FULL_POWER * direction;
		motor[bottomRightTower]  = FULL_POWER * direction;
		motor[bottomLeftTower]   = FULL_POWER * direction;
	}

	if(timer != 0) {
		// Wait �timer� ms
		wait1Msec(timer);

		// Stop
		motor[topRightTower]	   = STOP;
		motor[topLeftTower] 	   = STOP;
		motor[bottomRightTower]  = STOP;
		motor[bottomLeftTower]   = STOP;
	}
}

// Move intake motors at full power in specified direction /*
void moveIntake(int direction) {
	// Check for function input error
	if (direction == 1 || direction == -1 || direction == 0){
		// Move at 100% power
		motor[takeLeft]	   = FULL_POWER * direction;
		motor[takeRight]   = FULL_POWER * direction;
	}
}
//Spin drive motors in opp. directions
void turnDrive(int direction, int timer=0) {
	// Check for function input error
	if(direction == 1 || direction == -1 || direction == 0){
		// Default Left Turn
		motor[frontRightMotor]	 = FULL_POWER * direction;
		motor[frontLeftMotor] 	 = -FULL_POWER * direction;
		motor[backRightMotor]	 = FULL_POWER * direction;
		motor[backLeftMotor]	 = -FULL_POWER * direction;
	}

	if(timer != 0) {
		// Wait ?timer? ms
		wait1Msec(timer);

		// Stop
		motor[frontRightMotor]   = STOP;
		motor[frontLeftMotor]  	 = STOP;
		motor[backRightMotor]    = STOP;
		motor[backLeftMotor]     = STOP;
	}
}
/*
// Move arm to user specified position
void armToPos(int setpoint) {
int cur = SensorValue(potentiometer);

// While the current value is not close to the threshold
while(cur < setpoint - 0.05 || cur > setpoint + 0.05) {
cur = SensorValue(potentiometer);

if(cur < setpoint) {
moveArm(1);
}
else if(cur > setpoint) {
moveArm(-1);
}
*/



//Wait for Press--------------------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{

	bLCDBacklight = true;	// Turn on LCD Backlight

	clearLCDLine(0);
	clearLCDLine(1);

	//Display the Primary Robot battery voltage
	displayLCDString(0, 0, "Primary: ");
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0, 'V'); //Build the value to be displayed
	displayNextLCDString(mainBattery);

	//Display the Backup battery voltage
	displayLCDString(1, 0, "Backup: ");
	sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
	displayNextLCDString(backupBattery);

	//Short delay for the LCD refresh rate
	waitForPress();

	// Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);

	wait1Msec(500);

	//displayLCDCenteredString(0, "Test");
	//Declare count variable to keep track of our choice

	int count = 0;

	while(nLCDButtons != centerButton)
	{
		//Switch case that allows the user to choose from 2 different options
		switch(count){
		case 0: //Display first choice
			displayLCDCenteredString(0, "Goal Auto");
			displayLCDCenteredString(1, "<     Enter    >");
			waitForPress();

			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 2;
			}

			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 1;
			}
			break;

		case 1: //Display second choice
			displayLCDCenteredString(0, " Blue Hang auto");
			displayLCDCenteredString(1, "<     Enter    >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton) {
				waitForRelease();
				count = 0;
			}

			else if(nLCDButtons == rightButton) {
				waitForRelease();
				count = 2;
			}
			break;

		case 2: //display 3rd choice
			displayLCDCenteredString(0, "Red Hang auto");
			displayLCDCenteredString(1, "<     Enter    >");


			if(nLCDButtons == leftButton) {
				waitForRelease();
				count = 1;
			}
			else if(nLCDButtons == rightButton) {
				waitForRelease();
				count = 0;
			}
			break;

		default:
			count = 0;
			break;
		}
	}

	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);

	switch(count) {  //pick auto, display
	case 0: //Choice 1 from LCD
		displayLCDCenteredString(0, "Goal Side Auto");
		displayLCDCenteredString(1, "is running!");
		programChoice = 1;
		break;

	case 1: //Choice 2 from LCD
		displayLCDCenteredString(0, "Blue Hang Auto");
		displayLCDCenteredString(1, "is running!");
		programChoice = 2;
		break;

	case 2: //Choice 3 from LCD
		displayLCDCenteredString(0, "Red Hang Auto");
		displayLCDCenteredString(1, "is running!");
		programChoice = 3;
		break;

	default:
		displayLCDCenteredString(0, "No valid choice");
		displayLCDCenteredString(1, "was made!");
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//
// Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
task autonomous()
{


	// goal side auto (auto 1)
	if(programChoice == 1){

		// Move forward
		moveDrive(1, 250);

		//move back to pop out intake
		moveDrive(-1,250);

		//move to first position
		moveDrive(1,500);

		// Move arm up
		moveArm(1,750);

		// Move forward to second point
		moveDrive(1, 500);

		// Wait a secound so that big ball is out of the way
		wait1Msec(750);

		// Outtake preload
		moveIntake(-1);
		wait1Msec(2000);

		// Drive back to starting square
		moveDrive(-1, 1000);

		//stop robot for button press to reposition
		/* moveDrive(0,3000); */

		while (SensorValue[touchSensor] != 1){}

		//move robot forward at new angle
		moveDrive(1,1300);



	}

	// Blue side hanging bar side of bump auto (auto 2)
	else if(programChoice == 2) {

		// Move forward
		moveDrive(1, 250);

		//move back to pop out intake
		moveDrive(-1,250);

		//move to first position
		moveDrive(1,500);

		//stop Robot and intake balls
		moveIntake(1);

		wait1Msec(750);

		//move robot back to starting square
		moveDrive(-1, 750);

		//Stop robot for reposition 90 degrees
		//moveDrive(0, 3000);
		while (SensorValue[touchSensor] != 1){}


		//Move robot in new direction
		moveDrive(1, 750);

		//robot Turn 90 degrees left
		turnDrive(1, 750);

		//Lift arm up a tig
		moveArm(1,500);

		//Move robot forward over the bump
		moveDrive(1,1500);

		//lift the arm all the way
		moveArm(1,750);

		//move forward alittle
		moveDrive(1,250);

		//outtake preload
		moveIntake(1);
		wait1Msec(2000);
	}
	//Red side hanging bar side of bump auto (auto 3)
	else if(programChoice ==3) {

		// Move forward
		moveDrive(1, 250);

		//move back to pop out intake
		moveDrive(-1,250);

		//move to first position
		moveDrive(1,500);

		//stop Robot and intake balls
		moveIntake(1);
		wait1Msec(750);

		//move drive back to original starting space
		moveDrive(-1, 750);

		//Stop robot for reposition 90 degrees
		//moveDrive(0, 3000);
		while (SensorValue[touchSensor] != 1){}

		//Move robot in new direction
		moveDrive(1, 750);

		//robot Turn 90 degrees Right
		turnDrive(-1, 750);

		//Lift arm up a tig
		moveArm(1,500);

		//Move robot forward over the bump
		moveDrive(1,1500);

		//move arm all the way up
		moveArm(1,750);

		//move arm up just a tig
		moveDrive(1,250);

		//outtake preload
		moveIntake(1);
		wait1Msec(2000);
	}
}



/////////////////////////////////////////////////////////////////////////////////////////
//
// User Control Task
//
// Functions for lift, drive, intake, and pneumatics.
//
/////////////////////////////////////////////////////////////////////////////////////////


task usercontrol() {
	while(1 == 1) {

		/* Drivetrain */

		//Right side of the robot is controlled by the right joystick, Y-axis
		motor[frontRightMotor]	= vexRT[Ch2];
		motor[backRightMotor] 	= vexRT[Ch2];

		//Left side of the robot is controlled by the left joystick, Y-axis
		motor[frontLeftMotor]   = vexRT[Ch3];
		motor[backLeftMotor]    = vexRT[Ch3];



		/* Button Control */

		// Arm

		if(vexRT[Btn5U]) {
			moveArm(1); // Move arm up
		}
		else if(vexRT[Btn5D]) {
			moveArm(-1); // Move arm down
		}
		// If neither buttons 5U or 5D are pressed
		else {
			// Stop bottom tower movement (i.e. don't move arm up or down)
			motor[topRightTower]    = STOP;
			motor[topLeftTower]     = STOP;
			motor[bottomRightTower]	= STOP;
			motor[bottomLeftTower]  = STOP;
		}


		// Intake

		if (vexRT[Btn6U]) {
			moveIntake(1); //runs intake, pull
		}
		else if (vexRT[Btn6D]) {
			moveIntake(-1); //runs intake, push
		}
		else {
			moveIntake(0);
		}

		//*Pnumatics*//

		if(vexRT[Btn7U]) {
			//activate lock
			SensorValue[pistonLock1] = 1;
			SensorValue[pistonLock2] = 1;
		}
		else if(vexRT[Btn7D]) {
			SensorValue[pistonLock1] = 0;
			SensorValue[pistonLock2] = 0;
		}

		if(vexRT[Btn8U]==1)
		{
			if(SensorValue(potentiometer) < 1700){
				motor[topRightTower] = 127;
				motor[topLeftTower] = 127;
				motor[bottomLeftTower]= 127;
				motor[bottomRightTower] = 127;
			}
			else if(SensorValue(potentiometer) > 1700){
				motor[topRightTower] = 70;
				motor[topLeftTower] = 70;
				motor[bottomLeftTower]= 70;
				motor[bottomRightTower] = 70;
			}
		}
		else if(vexRT[Btn8D]==1)
		{
			if(SensorValue(potentiometer) < 1700){
				motor[topRightTower] = -127;
				motor[topLeftTower] = -127;
				motor[bottomLeftTower]= -127;
				motor[bottomRightTower] = -127;
			}
			else if(SensorValue(potentiometer) > 1700){
				motor[topRightTower] = -70;
				motor[topLeftTower] = -70;
				motor[bottomLeftTower]= -70;
				motor[bottomRightTower] = -70;
			}
		}
		else
		{
			motor[topRightTower] = 10;
			motor[topLeftTower] = 10;
			motor[bottomLeftTower]= 10;
			motor[bottomRightTower] = 10;
		}


	}
}
