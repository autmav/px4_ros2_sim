/*
 * TO PROPERLY SET OFFBOARD MODE:
 * COM_RCL_EXCEPT is set to 4
 * https://github.com/PX4/PX4-Autopilot/issues/18957
 * 
 */

#include <stdint.h>
#include <iostream>
#include <rclcpp/rclcpp.hpp>

#include "simpleRTPS/velCommandDrone.hpp"

int main(int argc, char* argv[])
{
	std::cout << "Starting mission 1 offboard control node..." << std::endl;
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<DroneSimple>());
	rclcpp::shutdown();
	return 0;
}
