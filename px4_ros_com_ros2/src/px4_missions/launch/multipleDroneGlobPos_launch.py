import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()

    node1=Node(
        package = 'mavros',
        executable = 'mavros_node',
        namespace = 'vhcl1/mavros',
        parameters=[
            {"fcu_url": "udp://:14540@"},
            {"tgt_system": 1}
        ]
    )
    node2=Node(
        package = 'px4_missions',
        executable = 'supervisedMission',
        name = 'drone1',
        parameters=[
            {"vehicleName": "/vhcl1"},
            {"takeOffHeight": 10.0},
            {"xyMaxVelocity": 10.0}
        ]
    )
    node3=Node(
        package = 'px4_missions',
        executable = 'missionSupervisor',
        namespace = 'vhcl1',
        parameters = [os.path.join(get_package_share_directory('px4_missions'), 'params', 'absMission1.yaml')]
    )

    ld.add_action(node1)
    ld.add_action(node2)
    ld.add_action(node3)
    return ld

