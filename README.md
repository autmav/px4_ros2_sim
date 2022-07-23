# Stand-Alone PX4 Simulation for ROS2

A full PX4 Autopilot simulation with all prerequisites integrated into a single project. No need to find and clone basic or additional dependencies. Just follow the given instructions to perform the simulation. 


## Setup

### Prerequisites

To run the system, you need to have the followings installed:

- ROS2 ([click for instructions]())

- Gazebo-11 ([click for instructions]())

- git ([click for instructions]())

Also, do the following:

```
wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add - 

sudo apt-get install curl

curl -s "https://get.sdkman.io" | bash

source "$HOME/.sdkman/bin/sdkman-init.sh"

sdk install gradle 6.3

```


### Cloning

First, clone the repo recursively.

```
git clone --recursive https://github.com/autmav/px4_ros2_sim.git
```

Configure and update submodules.

```
cd px4_ros2_sim

git config --global --add safe.directory '*'

git submodule sync --recursive

git submodule update --init --recursive --force
```

### Building the Packages

#### Installing the PX4 simulator:

Navigate to the local repository root. Then:

```
bash ./PX4-Autopilot/Tools/setup/ubuntu.sh

sudo reboot
```

#### Building requirements

Inside the folder `requirement`, lies some required packages for px4 simulation

For *foonathan_memory_vendor*, do:

```
# Starting in the root of repo

cd requirements/foonathan_memory_vendor

mkdir build && cd build

cmake ..

sudo cmake --build . --target install
```

For *Fast-DDS*, do:

```
# Starting in the root of repo

cd requirements/Fast-DDS

mkdir build && cd build

cmake -DTHIRDPARTY=ON -DSECURITY=ON ..

sudo make install
```

For *Fast-DDS-Gen*, do:

```
# Starting in the root of repo

cd requirements/Fast-DDS-Gen

gradle assemble

sudo env "PATH=$PATH" gradle install 
```

For *px4_msgs* and *px4_ros_com*, do:

```
# Starting in the root of repo

cd px4_ros_com_ros2/src/px4_ros_com/scripts

source build_ros2_workspace.bash
```

## Usage

To run the simulation and a sample mission, run the following parts.

### Running PX4 Simulation

```
# In a new termianl
# Starting in the root of repo

cd ~/PX4-Autopilot/

make px4_sitl_rtps gazebo
```

### Running micrortps

```
# In a new termianl
# Starting in the root of repo

source px4_ros_com_ros2/install/setup.bash

micrortps_agent -t UDP
```

### Running PX4 Simulation

```
# In a new termianl
# Starting in the root of repo

source px4_ros_com_ros2/install/setup.bash

ros2 run px4_ros_com offboard_control
```


## Acknowledgement


