# Stand-Alone PX4 Simulation for ROS2

A full PX4 Autopilot simulation with all prerequisites integrated into a single project. No need to find and clone basic or additional dependencies. Just follow the given instructions to perform the simulation. 


## Setup

### Prerequisites

To run the system, you need to have the followings installed:

- ROS2 ([click for instructions](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html)). The system is tested with ROS2-foxy

- Gazebo ([click for instructions](https://classic.gazebosim.org/tutorials?tut=install_ubuntu)). The system is tested with Gazebo-11

- git (`sudo apt-get install git`)

- curl (`sudo apt-get install curl`)

Also, do the following:

```
wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add - 
```

#### Gradle Build Tool

```
curl -s "https://get.sdkman.io" | bash

source "$HOME/.sdkman/bin/sdkman-init.sh"

sdk install gradle 6.3

```

#### ROS2 Dependencies

```
sudo apt-get install ros-foxy-geographic-msgs

sudo apt-get install ros-foxy-mavros-msgs #incase using Mavros with ROS2
```

#### Colcon Build Tools

```
sudo apt install python3-colcon-common-extensions

sudo apt update

sudo apt install ros-foxy-eigen3-cmake-module

sudo apt update

sudo apt install python3-testresources

sudo apt update

sudo pip3 install -U empy pyros-genmsg setuptools
```

#### Additional Required Libraries

```
sudo apt install libasio-dev libtinyxml2-dev

sudo apt install libp11-dev libengine-pkcs11-openssl

pip install -U colcon-common-extensions vcstool
```

### Cloning

First, clone the repo recursively.

```
git clone --recursive https://github.com/autmav/px4_ros2_sim.git
```

### Build and Install

#### Installing the PX4 simulator:

Navigate to the local repository root. Then:

```
cd px4_ros2_sim

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

cd px4_ros_com_ros2/

source src/px4_ros_com/scripts/build_ros2_workspace.bash 
```

#### Installation of QGround

To install the *QGround* ground station software, do:

```
sudo usermod -a -G dialout $USER

sudo apt-get remove modemmanager -y

sudo apt install gstreamer1.0-plugins-bad gstreamer1.0-libav gstreamer1.0-gl -y

wget https://d176tv9ibo4jno.cloudfront.net/latest/QGroundControl.AppImage

sudo chmod +x ./QGroundControl.AppImage
```


## Acknowledgement


