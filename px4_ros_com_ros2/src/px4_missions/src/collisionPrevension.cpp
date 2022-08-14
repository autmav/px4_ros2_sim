#include <px4_msgs/msg/obstacle_distance.hpp>
#include <rclcpp/rclcpp.hpp>
#include <stdint.h>

#include <chrono>
#include <iostream>

using namespace std::chrono;
using namespace std::chrono_literals;
using namespace px4_msgs::msg;

class CollisionPrevension : public rclcpp::Node {
public:
	CollisionPrevension() : Node("collision_prevension")
	 {
		obstacle_distance_publisher_ =
			this->create_publisher<ObstacleDistance>("fmu/obstacle_distance/in", 10);

		// get common timestamp
		timesync_sub_ =
			this->create_subscription<px4_msgs::msg::Timesync>("fmu/timesync/out", 10,
				[this](const px4_msgs::msg::Timesync::UniquePtr msg) 
				{
					timestamp_.store(msg->timestamp);
				});

		auto timer_callback = [this]() -> void {

				// Change to Offboard mode after 10 setpoints
			}
			1
		};

		timer_ = this->create_wall_timer(100ms, timer_callback);
	}

	void set_data() const;

private:
	rclcpp::TimerBase::SharedPtr timer_;

	rclcpp::Publisher<ObstacleDistance>::SharedPtr obstacle_distance_publisher_ ;
	rclcpp::Subscription<px4_msgs::msg::Timesync>::SharedPtr timesync_sub_;

	std::atomic<uint64_t> timestamp_;   //!< common synced timestamped


	void get_data() const;

};



void CollisionPrevension::get_data() const {


	//RCLCPP_INFO(this->get_logger(), "Data recived");
}
void CollisionPrevension::set_data() const {

	//RCLCPP_INFO(this->get_logger(), "Data sent");
}


/**
 * @brief Publish the offboard control mode.
 *        For this example, only position and altitude controls are active.
 */
void CollisionPrevension::publish_offboard_control_mode() const {
	ObstacleDistance msg{};
	msg.timestamp = timestamp_.load();
	msg.frame = MAV_FRAME_LOCAL_NED;
	msg.sensor_type = MAV_DISTANCE_SENSOR_INFRARED;
	msg.acceleration = false;
	msg.attitude = false;
	msg.body_rate = false;

	offboard_control_mode_publisher_->publish(msg);
}



int main(int argc, char* argv[]) {
	std::cout << "Starting collision prevension node..." << std::endl;
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<CollisionPrevension>());

	rclcpp::shutdown();
	return 0;
}
