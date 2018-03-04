#include "Auto_Manager.hpp"
#include "WPILib.h"

FRC::Auto_Manager::Auto_Manager():
	drive_Man(),
	camera_Man()
{

}

void FRC::Auto_Manager::autoInit()
{
	gameData = "LLL";//frc::DriverStation::GetInstance().GetGameSpecificMessage();
	SmartDashboard::PutString("gameData", gameData);

	std::string startingPos = "Left";//SmartDashboard::GetString("Autonomous Starting Position", "Center");
	SmartDashboard::PutString("starting Position", startingPos);

	std::string autoTarget = "Switch";//SmartDashboard::GetString("Autonomous Destination Selector", "Switch");
	SmartDashboard::PutString("auto Target", autoTarget);


	if(startingPos == "Center")
	{
		fieldPos = 'C';
	}
	else if(startingPos == "Left")
	{
		fieldPos = 'L';
	}
	else if(startingPos == "Right")
	{
		fieldPos = 'R';
	}

	if(autoTarget == "Switch")
	{
		autoGoal = 0;
	}
	else if(autoTarget == "Scale")
	{
		autoGoal = 1;
	}

	SmartDashboard::PutNumber("Auto Goal: ", autoGoal);
	SmartDashboard::PutString("Game Specific Data:", gameData);


	if(fieldPos == gameData[autoGoal])
	{
		camera_Man.setPanPos(90);
	}
	else if(fieldPos == 'L')
	{
		if(autoGoal == 0)
		{
			camera_Man.setPanPos(camera_Man.LEFT_SWITCH_PAN);
			camera_Man.setTiltPos(camera_Man.DEFAULT_SWITCH_TILT);
		}
		else if(autoGoal == 1)
		{
			camera_Man.setPanPos(camera_Man.LEFT_SCALE_PAN);
			camera_Man.setTiltPos(camera_Man.DEFAULT_SWITCH_TILT);
		}
	}
	else if(fieldPos == 'C' && gameData[autoGoal] == 'L')
	{
		if(autoGoal == 0)
		{
			camera_Man.setPanPos(camera_Man.CENTER_SWITCH_LEFT_PAN);
			camera_Man.setTiltPos(camera_Man.DEFAULT_SWITCH_TILT);
		}
		else if(autoGoal == 1)
		{
			camera_Man.setPanPos(camera_Man.CENTER_SCALE_LEFT_PAN);
			camera_Man.setTiltPos(camera_Man.DEFAULT_SWITCH_TILT);
		}
	}
	else if(fieldPos == 'C' && gameData[autoGoal] == 'R')
	{
		if(autoGoal == 0)
		{
			camera_Man.setPanPos(camera_Man.CENTER_SWITCH_RIGHT_PAN);
			camera_Man.setTiltPos(camera_Man.DEFAULT_SWITCH_TILT);
		}
		else if(autoGoal == 1)
		{
			camera_Man.setPanPos(camera_Man.CENTER_SCALE_RIGHT_PAN);
			camera_Man.setTiltPos(camera_Man.DEFAULT_SWITCH_TILT);
		}
	}
	else if(fieldPos == 'R')
	{
		if(autoGoal == 0)
		{
			camera_Man.setPanPos(camera_Man.RIGHT_SWITCH_PAN);
			camera_Man.setTiltPos(camera_Man.DEFAULT_SWITCH_TILT);
		}
		else if(autoGoal == 1)
		{
			camera_Man.setPanPos(camera_Man.RIGHT_SCALE_PAN);
			camera_Man.setTiltPos(camera_Man.DEFAULT_SWITCH_TILT);
		}
	}

}

void FRC::Auto_Manager::driveToCam(double speed, int angle, bool targetFound)
{
	double rotation = 0;

	if(angle > 10)
	{
		rotation = -.1;
	}
	else if(angle < -10)
	{
		rotation = .1;
	}

	if(!targetFound)
	{
		rotation = 0;
		speed = 0;
	}

	drive_Man.mecanumDrive(0, speed, rotation);
	SmartDashboard::PutNumber("Auto Rotation", rotation);
}

double FRC::Auto_Manager::convertMB1220SonicVoltageToInches(double voltage)
{
	return (((voltage / 0.0049)) / 2.54);
}

double FRC::Auto_Manager::convertMB1013SonicVoltageToInches(double voltage)
{
	return (voltage / (0.00488 / 5) / 25.4);
}

double FRC::Auto_Manager::convertMB1010SonicVoltageToInches(double voltage)
{
	return voltage / 0.0098;
}
