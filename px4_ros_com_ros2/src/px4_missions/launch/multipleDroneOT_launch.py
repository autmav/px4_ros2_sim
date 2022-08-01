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
        executable = 'objectTracking',
        name = 'drone1',
        parameters=[
            {"vehicleName": "/vhcl1"},
            {"takeOffHeight": 10.0},
            {"xyMaxVelocity": 0.6}
        ]
    )

    node3=Node(
        package = 'mavros',
        executable = 'mavros_node',
        namespace = 'vhcl2/mavros',
        parameters=[
            {"fcu_url": "udp://:14541@"},
            {"tgt_system": 2}
        ]
    )

    node4=Node(
        package = 'px4_missions',
        executable = 'objectTracking',
        name = 'drone2',
        parameters=[
            {"vehicleName": "/vhcl2"},
            {"takeOffHeight": 12.5},
            {"xyMaxVelocity": 0.6}
        ]
    )

    node5=Node(
        package = 'mavros',
        executable = 'mavros_node',
        namespace = 'vhcl3/mavros',
        parameters=[
            {"fcu_url": "udp://:14542@"},
            {"tgt_system": 3}
        ]
    )

    node6=Node(
        package = 'px4_missions',
        executable = 'objectTracking',
        name = 'drone3',
        parameters=[
            {"vehicleName": "/vhcl3"},
            {"takeOffHeight": 15.0},
            {"xyMaxVelocity": 0.6}
        ]
    )


    ld.add_action(node1)
    ld.add_action(node2)
    ld.add_action(node3)
    ld.add_action(node4)
    ld.add_action(node5)
    ld.add_action(node6)
    return ld

