/*
 * Auto_Manager.hpp
 *
 *  Created on: Feb 3, 2018
 *      Author: Sam
 */

#ifndef SRC_AUTO_MANAGER_HPP_
#define SRC_AUTO_MANAGER_HPP_

#include "WPILib.h"

namespace FRC
{
	class AutoManager
	{
	public:

		//Collision
		AutoManager();

		/* Checks to see if the robot will colide with an object with a given direction and distance, then returns which direction to go
		 * @parameters
		 * double sensorTheta = Direction of sensor reading
		 * double sensorDistance = Distance reading from sensor
		 * double joyStickX = MecanumDrive x-axis command
		 * double joyStickY = mecanumDrive y-axis command
		 * double joyStickTheta = Direction of turn from mecanumDrive
		 *
		 * @returns
		 * Boolean stating if current path will result in a collision or not
		 */
		bool checkCollision(double sensorTheta, double sensorDistance[], double joyStickX, double joyStickY, double joyStickTheta);

		bool sonicCheckCollision(int distance, double joyStickX, double joyStickY, double joyStickTheta);


		/* Returns Direction for nav-x board to send the robot if it cant go forwards
		 *
		 *@returns
		 *0 - continue forwards
		 *1 - go to the right
		 *2 - go to the left
		 *3 - forwards, left, and right will cause collision
		 */
		int avoidCollision(double sensorTheta, double sensorDistance[], double joyStickX, double joyStickY, double joyStickTheta);

		int sonicAvoidCollision(int frontSonic, int rightSonic, int leftSonic, double joyStickX, double joyStickY, double joyStickTheta);

		//Utility
		 double convertMB1220SonicVoltageToInches(double voltage);

		 double convertMB1013SonicVoltageToInches(double voltage);

		 double convertMB1010SonicVoltageToInches(double voltage);

	private:

		const double MINIMUM_DISTANCE = 24; //The Distance in meters that is the closest the robot can go to an obstacle without override

	};
}




#endif /* SRC_AUTO_MANAGER_HPP_ */
