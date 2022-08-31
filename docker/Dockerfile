From ros:foxy-ros1-bridge-focal

RUN apt-get update

RUN apt install vim -y

RUN apt-get install software-properties-common -y

RUN mkdir -p ./ros2_ws/src


RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE

RUN add-apt-repository "deb https://librealsense.intel.com/Debian/apt-repo $(lsb_release -cs) main" -u 

RUN apt-get install librealsense2-dkms -y

RUN apt-get install librealsense2-utils -y

RUN apt-get install librealsense2-dev -y

RUN apt-get install librealsense2-dbg -y

RUN cd ..

RUN rosdep update

RUN apt-get install ros-foxy-realsense2-camera -y

RUN export ROS1_INSTALL_PATH=/opt/ros/noetic

RUN export ROS2_INSTALL_PATH=~/ros2_rolling/install


COPY . ./ros2_ws



