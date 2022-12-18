#include <stdint.h>
#include <iostream>
#include <rclcpp/rclcpp.hpp>

#include "simpleRTPS/nav2_guidance.hpp"

int main(int argc, char* argv[])
{
	std::cout << "Starting Nav2 Guidance in offboard control mode..." << std::endl;
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<DroneSimple>());
	rclcpp::shutdown();
	return 0;
}