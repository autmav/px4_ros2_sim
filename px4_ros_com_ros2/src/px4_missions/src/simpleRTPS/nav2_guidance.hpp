#ifndef __NAV2_GUIDANCE__
#define __NAV2_GUIDANCE__

#include "../base/droneBaseRTPS.hpp"

class DroneSimple : public DroneRTPS
{
public:
	DroneSimple();

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


#endif /*__NAV2_GUIDANCE__*/