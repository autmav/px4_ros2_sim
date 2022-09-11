From ros:foxy-ros1-bridge-focal

RUN apt-get update

	apt install vim -y \

    apt-get install udev -y \	

	apt-get install software-properties-common -y \	

	mkdir -p ./ros2_ws/src \	

	apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE\	

	add-apt-repository "deb https://librealsense.intel.com/Debian/apt-repo $(lsb_release -cs) main" -u \	

	apt-get install librealsense2-dkms -y \
	
	apt-get install librealsense2-utils -y \
	
	apt-get install librealsense2-dev -y \
	
	apt-get install librealsense2-dbg -y \
	
	cd .. \
	
	rosdep update \
	
	apt-get install ros-foxy-realsense2-camera -y \
	
	export ROS1_INSTALL_PATH=/opt/ros/noetic \
	
	export ROS2_INSTALL_PATH=opt/ros/foxy \

	source /opt/ros/foxy/setup.bash
 

COPY . ./ros2_ws



