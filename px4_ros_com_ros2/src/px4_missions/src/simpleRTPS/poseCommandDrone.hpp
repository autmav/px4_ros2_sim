#ifndef __Pose_Command_Drone_HPP__
#define __Pose_Command_Drone_HPP__

#include "../base/droneBaseRTPS.hpp"

class DroneSimple : public DroneRTPS
{
public:
	DroneSimple();

/* STATE:
00 -> Wait x sec
10 -> TakeOff mode set
20 -> Arm command send
30 -> Wait for TakeOff end
40 -> Offboard mode send
50 -> Fly to waypoints
60 -> Land mode send
*/
	int state = 0;
	int stateOld = 0;
	uint64_t stateCounter = 0;
	uint64_t programCounter = 0;

	float holdLat;
	float holdLon;
	float holdAlt;

private:
	void flight_mode_timer_callback();
	rclcpp::TimerBase::SharedPtr _timer;
};


#endif /*__DRONE_SIMPLE_HPP__*/