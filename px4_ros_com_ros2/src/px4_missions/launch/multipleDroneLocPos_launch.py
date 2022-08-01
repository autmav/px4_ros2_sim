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
        parameters = [os.path.join(get_package_share_directory('px4_missions'), 'params', 'locMission1.yaml')]
    )



    node4=Node(
        package = 'mavros',
        executable = 'mavros_node',
        namespace = 'vhcl2/mavros',
        parameters=[
            {"fcu_url": "udp://:14541@"},
            {"tgt_system": 2}
        ]
    )
    node5=Node(
        package = 'px4_missions',
        executable = 'supervisedMission',
        name = 'drone2',
        parameters=[
            {"vehicleName": "/vhcl2"},
            {"takeOffHeight": 12.5},
            {"xyMaxVelocity": 10.0}
        ]
    )
    node6=Node(
        package = 'px4_missions',
        executable = 'missionSupervisor',
        namespace = 'vhcl2',
        parameters = [os.path.join(get_package_share_directory('px4_missions'), 'params', 'locMission2.yaml')]
    )



    node7=Node(
        package = 'mavros',
        executable = 'mavros_node',
        namespace = 'vhcl3/mavros',
        parameters=[
            {"fcu_url": "udp://:14542@"},
            {"tgt_system": 3}
        ]
    )
    node8=Node(
        package = 'px4_missions',
        executable = 'supervisedMission',
        name = 'drone3',
        parameters=[
            {"vehicleName": "/vhcl3"},
            {"takeOffHeight": 15.0},
            {"xyMaxVelocity": 10.0}
        ]
    )
    node9=Node(
        package = 'px4_missions',
        executable = 'missionSupervisor',
        namespace = 'vhcl3',
        parameters = [os.path.join(get_package_share_directory('px4_missions'), 'params', 'locMission3.yaml')]
    )



    ld.add_action(node1)
    ld.add_action(node2)
    ld.add_action(node3)
    ld.add_action(node4)
    ld.add_action(node5)
    ld.add_action(node6)
    ld.add_action(node7)
    ld.add_action(node8)
    ld.add_action(node9)
    return ld

