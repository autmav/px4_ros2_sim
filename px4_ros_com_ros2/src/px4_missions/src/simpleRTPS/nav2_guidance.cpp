#include "nav2_guidance.hpp"

DroneSimple::DroneSimple() : DroneRTPS()

{
	_timer = this->create_wall_timer(100ms, std::bind(&DroneSimple::flight_mode_timer_callback, this));
}


void DroneSimple::flight_mode_timer_callback()
{
	// SWITCHING BETWEEN STATES
	switch(state)
	{
		case 0:

			break;

		case 10:
			if(stateCounter >= 30)
				state = 20;
			break;

		case 20:
			RCLCPP_INFO( this->get_logger(), "Error Z %f ",1 + odometry.z.load() );
			if(-odometry.z.load() >= 1 - 0.2 )
				state = 30;
			break;

		case 30:
			if(stateCounter >= 20)
				state = 40;
			break;

		case 40:
			if(vehiclecommandmode.flag_control_offboard_enabled.load()==true)
			{
				state = 50;
				RCLCPP_INFO(this->get_logger(), "Offboard flight mode Set");
			}
			else
			{
				this->setFlightMode(FlightMode::mOffboard);
				RCLCPP_INFO(this->get_logger(), "Offboard flight mode did not set retry ...");
			}

			break;

		case 50:
			RCLCPP_INFO( this->get_logger(), "Listening to NAV2 Bringup" );
			RCLCPP_INFO( this->get_logger(), "vx: %f vy: %f vz: %f yawDot:%f ",
						cmd_vel.vx.load(),cmd_vel.vy.load(),cmd_vel.vz.load(),cmd_vel.yawDOT.load() );

			if(cmd_vel.yawDOT.load()==1)
			{
				RCLCPP_INFO( this->get_logger(), "NAV Faild" );
			
				if(vehiclecommandmode.flag_control_offboard_enabled.load()==false)
				{
					
					if(vehiclecommandmode.flag_control_offboard_enabled.load()==true)
					{
						state = 60;
						RCLCPP_INFO(this->get_logger(), "Offboard flight mode Set");
					}
					else
					{
						this->setFlightMode(FlightMode::mOffboard);
						RCLCPP_INFO(this->get_logger(), "Offboard flight mode did not set retry ...");
					}
				}
			}
			break;

		case 60:
			if(abs(odometry.z.load()) <= 0.25) //Change to home Z or Land detection
				state = 70;
			break;
		case 70:
			RCLCPP_INFO(this->get_logger(), "Finished");
			break;
	}


	// BEHAVIOUR OF STATES
	switch(state)
	{
		case 0:
			// if(stateCounter == 0)
			// {
			// 	vehiclestatus.arming_state.store(3.00);
			// 	RCLCPP_INFO(this->get_logger(), "First time arming check");
			// }
			RCLCPP_INFO(this->get_logger(), "Trying to Connect ... ");
			if(vehiclestatus.arming_state.load() == 0 || vehiclestatus.arming_state.load() == 1 || vehiclestatus.arming_state.load() == 2)
			{
				RCLCPP_INFO(this->get_logger(), "Connected");
				state = 10;
			}
			else
			{
				RCLCPP_INFO(this->get_logger(), "Not Connected");
				stateCounter = stateCounter - 1;
			}

			break;

		case 10:
			// TakeOff flight mode command send
			if(stateCounter == 1)
			{
				RCLCPP_INFO(this->get_logger(), "Initiate ... ");
				SetPoint.x = std::numeric_limits<float>::quiet_NaN();
				SetPoint.y = std::numeric_limits<float>::quiet_NaN();
				SetPoint.z = -0.05;
				SetPoint.yaw = std::numeric_limits<float>::quiet_NaN();
				SetPoint.vx = 0;
				SetPoint.vy = 0;
				SetPoint.vz = std::numeric_limits<float>::quiet_NaN() ;
				SetPoint.yawDOT = 0;
				set_home();
			}
			break;

		case 20:
			// Arm command send
			if(stateCounter == 1)
			{
                this->setFlightMode(FlightMode::mTakeOff);
                this->arm();
				if(vehiclestatus.arming_state.load() == 0){
					stateCounter = stateCounter - 1;
					RCLCPP_INFO(this->get_logger(), "Not Armed. Retry ...");
				}
				else if(vehiclestatus.arming_state.load() == 1)
					RCLCPP_INFO(this->get_logger(), "Vehicle Armed");
				else
					RCLCPP_INFO(this->get_logger(), "Not Connected to Vehicle");
		
			}
				
				
			break;

		case 30:
			//if(stateCounter == 1)
				//publish_offboard_control_mode(OffboardControl::oVelocity);
			break;

		case 40:
			// Offboard flight mode command send

			
			break;

		case 50:
			SetPoint.x		= std::numeric_limits<float>::quiet_NaN();
			SetPoint.y		= std::numeric_limits<float>::quiet_NaN();
			SetPoint.z		= odometry.z.load();
			SetPoint.yaw	= std::numeric_limits<float>::quiet_NaN();
			SetPoint.vx 	= cmd_vel.vy.load();
			SetPoint.vy 	= cmd_vel.vx.load();
			SetPoint.vz 	= std::numeric_limits<float>::quiet_NaN();
			SetPoint.yawDOT = -cmd_vel.yawDOT.load();
			if (cmd_vel.yawDOT.load() >= 1.00)
			{
				SetPoint.yawDOT = -0.1;
				RCLCPP_INFO(this->get_logger(), "Max YawDot");
			}
			else
			{
				SetPoint.yawDOT = -cmd_vel.yawDOT.load();
			}	
				
			publish_offboard_control_mode(OffboardControl::oVelocity);
			break;

		case 60:
			publish_offboard_control_mode(OffboardControl::oRelPos);
			if(stateCounter == 1)
			{
				//publish_offboard_control_mode(OffboardControl::oRelPos);
				SetPoint.x = 0;
				SetPoint.y = 0;
				SetPoint.z = std::numeric_limits<float>::quiet_NaN();
				SetPoint.yaw = std::numeric_limits<float>::quiet_NaN();
				SetPoint.vx = std::numeric_limits<float>::quiet_NaN();
				SetPoint.vy = std::numeric_limits<float>::quiet_NaN();
				SetPoint.vz = std::numeric_limits<float>::quiet_NaN();
				SetPoint.yawDOT = std::numeric_limits<float>::quiet_NaN();
				this->setFlightMode(FlightMode::mLand);
			}
			break;

		case 70:
			if(stateCounter == 1)
			{
				this->disarm();
				if(vehiclestatus.arming_state.load() == 2){
					stateCounter = stateCounter -1;
					RCLCPP_INFO(this->get_logger(), "Not Disarmed. Retry ...");
				}
				else
					RCLCPP_INFO(this->get_logger(), "Vehicle Disarmed");
			}
			break;
	}


	// OFFBOARD SETPOINTS SEND

	publish_offboard_control_mode_nav2(); //OffboardControl::oVelocity			
	publish_traj_setpoint(SetPoint.x, SetPoint.y, SetPoint.z, SetPoint.yaw, SetPoint.vx, SetPoint.vy, SetPoint.vz, SetPoint.yawDOT);

	// RESET STATE COUNTER
	if(state != stateOld)
		stateCounter = 0;

	stateOld = state;

	stateCounter++;
	//programCounter++;

}
