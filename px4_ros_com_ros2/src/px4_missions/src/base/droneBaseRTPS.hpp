#ifndef __DRONE_BASE_RTPS_HPP__
#define __DRONE_BASE_RTPS_HPP__

#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>
#include <px4_msgs/msg/timesync.hpp>
#include <px4_msgs/msg/position_setpoint_triplet.hpp>
#include <px4_msgs/msg/vehicle_odometry.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/vehicle_control_mode.hpp>
#include <px4_msgs/msg/vehicle_local_position_setpoint.hpp>
#include <px4_msgs/msg/home_position.hpp>
#include <px4_msgs/msg/vehicle_status.hpp>
#include <px4_msgs/msg/obstacle_distance.hpp>
#include <geometry_msgs/msg/twist.hpp>

#include <rclcpp/rclcpp.hpp>
#include <stdint.h>

#include <chrono>
#include <iostream>

using namespace std::chrono;
using namespace std::chrono_literals;
using namespace px4_msgs::msg;

class DroneRTPS : public rclcpp::Node
{
public:
	DroneRTPS();

	enum class FlightMode
	{ mOffboard, mTakeOff, mLand, mReturnToLaunch, mHold, mMission };

	enum class OffboardControl
	{ oRelPos, oVelocity };

	struct Odometry
	{ std::atomic<float> x, y, z, vx, vy, vz, rollspeed, pitchspeed, yawspeed; }odometry;

	struct SetPoint
	{ std::atomic<float> x, y, z, yaw ,vx, vy, vz, yawDOT; }SetPoint;

	struct vehiclecommandmode
	{ std::atomic<bool> flag_control_offboard_enabled; }vehiclecommandmode;

	struct vehiclestatus
	{ std::atomic<uint> arming_state, nav_state; }vehiclestatus;

	struct cmd_vel
	{ std::atomic <float> vx, vy, vz, rollDOT, pitchDOT, yawDOT;}cmd_vel;

	// struct HomePose
	// { std::atomic<float> x, y, z; }HomePose;
	HomePosition home_pose_msg{};

    void arm();
	void disarm();
	void set_home();
    void setFlightMode(FlightMode mode);

	void publish_offboard_control_mode(OffboardControl mode);
	void publish_offboard_control_mode_nav2();
	void publish_traj_setp_position(float x, float y, float z, float yaw);
	void publish_traj_setp_speed(float vx, float vy, float vz, float yawspeed);
	void publish_traj_setpoint(float x, float y, float z, float yaw,
							   float vx, float vy, float vz, float yawDOT);
	void publish_local_pose(float x, float y, float z, float yaw,
							   float vx, float vy, float vz, float yawDOT);
	void publish_local_obstacle_distance();

private:
	void publish_vehicle_command(uint16_t command, float param1 = 0.0, float param2 = 0.0, float param3 = 0.0, float param4 = 0.0, float param5 = 0.0, float param6 = 0.0, float param7 = 0.0);

	std::atomic<uint64_t> _timestamp;

	rclcpp::Publisher<OffboardControlMode>::SharedPtr _offboard_control_mode_publisher;
	rclcpp::Publisher<TrajectorySetpoint>::SharedPtr _trajectory_setpoint_publisher;
	rclcpp::Publisher<VehicleLocalPositionSetpoint>::SharedPtr _local_setpoint_publisher;
	rclcpp::Publisher<VehicleCommand>::SharedPtr _vehicle_command_publisher;
	rclcpp::Publisher<PositionSetpointTriplet>::SharedPtr _position_setpoint_triplet_publisher; // NOT YET WORKING
	rclcpp::Publisher<HomePosition>::SharedPtr _home_pose_publisher;

	rclcpp::Subscription<px4_msgs::msg::Timesync>::SharedPtr _timesync_sub;
	rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr _vehicle_odometry_sub;
	rclcpp::Subscription<px4_msgs::msg::VehicleControlMode>::SharedPtr _control_mode_sub;
	rclcpp::Subscription<px4_msgs::msg::VehicleStatus>::SharedPtr _vehicle_status_sub;
	rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr _nav2_bringup_sub;
	 
};


#endif /*__DRONE_BASE_RTPS_HPP__*/