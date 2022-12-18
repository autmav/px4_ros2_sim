from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument, ExecuteProcess, SetEnvironmentVariable

def generate_launch_description():

    return LaunchDescription([
        # Node(
        #     package='px4_missions',
        #     executable='nav2_guidance',
        #     name='guidance_node'
        # ),

        ExecuteProcess(
            cwd="/home/parsa/px4_ros2_sim/PX4-Autopilot",
            cmd=['make', 'px4_sitl_rtps', 'gazebo'],
            output='screen'),
        ExecuteProcess(
            cmd=['micrortps_agent', '-t', 'UDP'],
            output='screen'),

        # Node(
        #     package='turtlesim',
        #     executable='turtlesim_node',
        #     name='sim'
        # ),
        # Node(
        #     package='turtlesim',
        #     executable='mimic',
        #     name='mimic',
        #     remappings=[
        #         ('/input/pose', '/turtlesim1/turtle1/pose'),
        #         ('/output/cmd_vel', '/turtlesim2/turtle1/cmd_vel'),
        #     ]
        # )
    ])
