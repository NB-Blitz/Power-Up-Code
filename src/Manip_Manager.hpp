#ifndef SRC_MANIP_MANAGER_HPP_
#define SRC_MANIP_MANAGER_HPP_

#include "WPILIb.h"
#include "ctre/Phoenix.h"

namespace FRC
{
	class Manip_Manager
	{
	public:
		Manip_Manager();

		// Objects
		WPI_TalonSRX Manip_Motor;
		Relay Left_Spike, Right_Spike;

		// Methods
		void moveArms(double leftButton, double rightButton);
		void intake(bool leftButton, bool rightButton);
	};
}

#endif /* SRC_MANIP_MANAGER_HPP_ */