#include <px4_msgs/msg/timesync.hpp>
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
		timesync_sub_ =
			this->create_subscription<px4_msgs::msg::Timesync>("fmu/timesync/out", 10,
				[this](const px4_msgs::msg::Timesync::UniquePtr msg) 
				{
					timestamp_.store(msg->timestamp);
				});

		auto timer_callback = [this]() -> void {

				this->set_data(distances_arrey);
		};

		timer_ = this->create_wall_timer(100ms, timer_callback);
		

	}


private:
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<ObstacleDistance>::SharedPtr obstacle_distance_publisher_ ;
	rclcpp::Subscription<px4_msgs::msg::Timesync>::SharedPtr timesync_sub_;

	uint16_t max_sensor_distance=400; 
	std::atomic<uint64_t> timestamp_;   //!< common synced timestamped
	std::atomic<uint16_t> distances_arrey[72];
	
	void get_data() const;
	void set_data(std::atomic<short unsigned int> *distances_arrey) const;

};



void CollisionPrevension::get_data() const {


	//RCLCPP_INFO(this->get_logger(), "Data recived");
}

void CollisionPrevension::set_data(std::atomic<short unsigned int> *distances_arrey) const 
{
	ObstacleDistance msg{};
	msg.timestamp = timestamp_.load();
	msg.frame = 12;
	msg.sensor_type = 2;
	msg.distances = distances_arrey->load();
	msg.increment = 5;
	msg.min_distance = 20;
	msg.max_distance = 400;
	obstacle_distance_publisher_->publish(msg);

	//RCLCPP_INFO(this->get_logger(), "Data sent");
}



int main(int argc, char* argv[]) {
	std::cout << "Starting collision prevension node..." << std::endl;
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<CollisionPrevension>());

	rclcpp::shutdown();
	return 0;
}
