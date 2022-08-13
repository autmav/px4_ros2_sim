## Setup

### Use uORB custom messages with ROS2
If you want to use other msgs beside default rtps msgs for ROS2, add them to urtps_bridge_topics.yaml, in:

```
cd px4_ros2_sim/PX4-Autopilot/msg/tools
```
Also the list of msgs are in
```
cd px4_ros2_sim/px4_ros_com_ros2/src/px4_msgs
```

Then fallow the instructions below

## Usage

To run the simulation and a sample mission, run the following parts.

### Running PX4 Simulation

```
# In a new termianl
# Starting in the root of repo

cd ~/px4_ros2_sim/PX4-Autopilot/

make px4_sitl_rtps gazebo
```

### Running micrortps

```
# In a new termianl

cd px4_ros2_sim/px4_ros_com_ros2/ #Or Where ever the file is and then cd

source install/setup.bash

micrortps_agent -t UDP
```

### Running a Sample Mission

```
# In a new termianl

cd px4_ros2_sim/px4_ros_com_ros2/ #Or Where ever the file is and then cd

source install/setup.bash

#For Vel CMD
ros2 run px4_missions offBoardRTPS_Vel

#For Vel Pose
ros2 run px4_missions offBoardRTPS_Pose
```


## Acknowledgement


