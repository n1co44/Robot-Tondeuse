

void Set_Mode_PIXHAWK() {
  Mower_PIXHAWK = 1;
}



void Check_PIXHAWK() {

  if (PIXHAWK_Armed == 1) Serial.print(F("PIXHAWK | - ARMED - "));
  if (PIXHAWK_Armed == 0) Serial.print(F("PIXHAWK | Dis-Armed "));

// PIXHAWK Flight Control Modes
// 0 = Manual, 1 = Acro, 3 = Steering, 4 = Hold, 5 = Loiter, 6 = Follow, 7 = Simple, 10 =  Auto
// 11 = RTL, 12 = Smart_RTL, 15 = Guided

  if (Custom_Mode == 0) Serial.print(F(" | Manual | "));
  if (Custom_Mode == 1) Serial.print(F(" | Acro | "));
  if (Custom_Mode == 3) Serial.print(F(" | Steering | "));
  if (Custom_Mode == 4) Serial.print(F(" | Hold | "));
  if (Custom_Mode == 5) Serial.print(F(" | Loiter | "));
  if (Custom_Mode == 6) Serial.print(F(" | Follow | "));
  if (Custom_Mode == 7) Serial.print(F(" | Simple | "));
  if (Custom_Mode == 10) Serial.print(F(" | Auto | "));
  if (Custom_Mode == 11) Serial.print(F(" | RTL | "));
  if (Custom_Mode == 12) Serial.print(F(" | Smart_RTL |"));
  if (Custom_Mode == 15) Serial.print(F(" | Guided |"));
        
  // MAVLink
  /* The default UART header for your MCU */ 
 

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
 
  // Pack the message
  mavlink_msg_heartbeat_pack(System_ID, Component_ID, &msg, Type, Autopilot_Type, System_Mode, Custom_Mode, System_State);
 
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
 
  // Send the message with the standard UART send function
  // uart0_send might be named differently depending on
  // the individual microcontroller / library in use.
  unsigned long currentMillisMAVLink = millis();
  if (currentMillisMAVLink - previousMillisMAVLink >= next_interval_MAVLink) {
    // Guardamos la última vez que se cambió el modo
    previousMillisMAVLink = currentMillisMAVLink;

    Pixhawk_Serial.write(buf,len);


    //Mav_Request_Data();
    num_hbs_pasados++;
    if(num_hbs_pasados>=num_hbs) {
    
    // Request streams from Pixhawk
    Serial.println("Streams requested!");
    Mav_Request_Data();
    num_hbs_pasados=0;
    }

  }

  // Check reception buffer
  comm_receive();
}



void Mav_Request_Data()  {
//Serial.println("COM_Request");

    
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];


  // STREAMS that can be requested
  /*
   * Definitions are in common.h: enum MAV_DATA_STREAM
   *   
   * MAV_DATA_STREAM_ALL=0, // Enable all data streams
     MAV_DATA_STREAM_RAW_SENSORS=1, /* Enable IMU_RAW, GPS_RAW, GPS_STATUS packets.
   * MAV_DATA_STREAM_EXTENDED_STATUS=2, /* Enable GPS_STATUS, CONTROL_STATUS, AUX_STATUS
   * MAV_DATA_STREAM_RC_CHANNELS=3, /* Enable RC_CHANNELS_SCALED, RC_CHANNELS_RAW, SERVO_OUTPUT_RAW
   * MAV_DATA_STREAM_RAW_CONTROLLER=4, /* Enable ATTITUDE_CONTROLLER_OUTPUT, POSITION_CONTROLLER_OUTPUT, NAV_CONTROLLER_OUTPUT.
   * MAV_DATA_STREAM_POSITION=6, /* Enable LOCAL_POSITION, GLOBAL_POSITION/GLOBAL_POSITION_INT messages.
   * MAV_DATA_STREAM_EXTRA1=10, /* Dependent on the autopilot
   * MAV_DATA_STREAM_EXTRA2=11, /* Dependent on the autopilot
   * MAV_DATA_STREAM_EXTRA3=12, /* Dependent on the autopilot
   * MAV_DATA_STREAM_ENUM_END=13,
   * 
   * Data in PixHawk available in:
   *  - Battery, amperage and voltage (SYS_STATUS) in MAV_DATA_STREAM_EXTENDED_STATUS
   *  - Gyro info (IMU_SCALED) in MAV_DATA_STREAM_EXTRA1
   */

  // To be setup according to the needed information to be requested from the Pixhawk
  const int  maxStreams = 2;
  const uint8_t MAVStreams[maxStreams] = {MAV_DATA_STREAM_EXTENDED_STATUS, MAV_DATA_STREAM_EXTRA1};
  const uint16_t MAVRates[maxStreams] = {0x02,0x05};

    
  for (int i=0; i < maxStreams; i++) {
    /*
     * mavlink_msg_request_data_stream_pack(system_id, component_id, 
     *    &msg, 
     *    target_system, target_component, 
     *    MAV_DATA_STREAM_POSITION, 10000000, 1);
     *    
     * mavlink_msg_request_data_stream_pack(uint8_t system_id, uint8_t component_id, 
     *    mavlink_message_t* msg,
     *    uint8_t target_system, uint8_t target_component, uint8_t req_stream_id, 
     *    uint16_t req_message_rate, uint8_t start_stop)
     * 
     */
    mavlink_msg_request_data_stream_pack(2, 200, &msg, 1, 0, MAVStreams[i], MAVRates[i], 1);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);

    Serial.write(buf,len);
    //Pixhawk_Serial.write(buf, len);  //???

  }
  
  // Request: PARAM_REQUEST_LIST. Only for full log recording
  /*
   * Primitive: mavlink_msg_param_request_list_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                   uint8_t target_system, uint8_t target_component)
   */
/*
  // Configure
  uint8_t system_id=2;
  uint8_t component_id=200;
  // mavlink_message_t* msg;
  uint8_t target_system=1;
  uint8_t target_component=0;

  // Pack
  mavlink_msg_param_request_list_pack(system_id, component_id, &msg,
    target_system, target_component);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);

  // Send
#ifdef SOFT_SERIAL_DEBUGGING
    Pixhawk_Serial.write(buf,len);
#else
    Serial.write(buf, len);
#endif
*/
}

void comm_receive() {

  //Serial.println("COM_Receive");

  mavlink_message_t msg;
  mavlink_status_t status;
 
  // Echo for manual debugging
  // Serial.println("---Start---");


  while(Pixhawk_Serial.available()>0) {
    uint8_t c = Pixhawk_Serial.read();



    // Try to get a new message
    if(mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {

      // Handle message
      switch(msg.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:  // #0: Heartbeat
          {

          }
          break;

 case MAVLINK_MSG_ID_SYS_STATUS:  // #1: SYS_STATUS
          {
            /* Message decoding: PRIMITIVE
             *    mavlink_msg_sys_status_decode(const mavlink_message_t* msg, mavlink_sys_status_t* sys_status)
             */
            //mavlink_message_t* msg;
            mavlink_sys_status_t sys_status;
            mavlink_msg_sys_status_decode(&msg, &sys_status);
  
            float Battery_Volts = sys_status.voltage_battery;
                    
            Serial.print("Volts: ");
            Serial.print(Battery_Volts / 1000 );
            Serial.print(" Amps: ");
            Serial.print(sys_status.current_battery);
            //Serial.print(" Sensors: ");
            //Serial.print(sys_status.onboard_control_sensors_health);
            //Serial.print("], [Comms loss (%): ");
            //Serial.print(sys_status.drop_rate_comm);
            //Serial.print("] ");

          }
          break;

  case MAVLINK_MSG_ID_PARAM_VALUE:  // #22: PARAM_VALUE
          {
            /* Message decoding: PRIMITIVE
             *    mavlink_msg_param_value_decode(const mavlink_message_t* msg, mavlink_param_value_t* param_value)
             */
            //mavlink_message_t* msg;
            mavlink_param_value_t param_value;
            mavlink_msg_param_value_decode(&msg, &param_value);

            Serial.println("PX PARAM_VALUE");
            Serial.print(" Value: ");
            Serial.print(param_value.param_value);
            Serial.print(" Count: ");
            Serial.print(param_value.param_count);
            Serial.print(" Index: ");
            Serial.print(param_value.param_index);
            Serial.print(" ID: ");
            Serial.print(param_value.param_id);
            Serial.print(" Type: ");
            Serial.print(param_value.param_type);
          }
          break;

  case MAVLINK_MSG_ID_RAW_IMU:  // #27: RAW_IMU
          {
            /* Message decoding: PRIMITIVE
             *    static inline void mavlink_msg_raw_imu_decode(const mavlink_message_t* msg, mavlink_raw_imu_t* raw_imu)
             */
            mavlink_raw_imu_t raw_imu;
            mavlink_msg_raw_imu_decode(&msg, &raw_imu);
            //Serial.println("PX RAW IMU");
            //Serial.println(raw_imu.xacc);

          }
          break;

 case MAVLINK_MSG_ID_ATTITUDE:  // #30
          {
            /* Message decoding: PRIMITIVE
             *    mavlink_msg_attitude_decode(const mavlink_message_t* msg, mavlink_attitude_t* attitude)
             */
            mavlink_attitude_t attitude;
            mavlink_msg_attitude_decode(&msg, &attitude);

            Serial.print(" ROLL : ");
            Serial.print(attitude.roll);
            Serial.print(" YAW : ");
            Serial.print(attitude.yaw);
            Serial.print(" PITCH : ");
            Serial.println(attitude.pitch);
          }
          break;



      }
    }
  }
}








void Command_long_ARM(){

// Define the system type (see mavlinkTypes.h for list of possible types) 
  
  // Initialize the required buffers 
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  
                            // 1 = to arm the PIXHAWK
  CMD_LONG_param1  = 1;                             // 1 = to arm the PIXHAWK
  CMD_LONG_command = MAV_CMD_COMPONENT_ARM_DISARM;  // Arm/Disarm Command
  PIXHAWK_Armed = 1;
      
  // Pack the message
  //mavlink_msg_heartbeat_pack(1,0, &msg, type, autopilotType, system_mode, custom_mode, system_state);
  mavlink_msg_command_long_pack(System_ID, Component_ID, &msg, Target_System, Target_Component, CMD_LONG_command, CMD_LONG_confirmation, CMD_LONG_param1, CMD_LONG_param2, CMD_LONG_param3, CMD_LONG_param4, CMD_LONG_param5, CMD_LONG_param6, CMD_LONG_param7);
  
  // Copy the message to send buffer 

  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  // Send the message (.write sends as bytes) 
  Pixhawk_Serial.write(buf, len);

  // Arm the Mower
  Turn_On_Relay();
  SetPins_ToGoForwards();
  delay(1000);
  }


void Command_long_Disarm(){
  
  // Initialize the required buffers 
  mavlink_message_t msg; 
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  CMD_LONG_param1  = 0;                                 // 0 = to dis arm the PIXHAWK
  CMD_LONG_command = MAV_CMD_COMPONENT_ARM_DISARM;      // Arm/Disarm Command
  PIXHAWK_Armed = 0;
  
  // Pack the message
  mavlink_msg_command_long_pack(System_ID, Component_ID, &msg, Target_System, Target_Component, CMD_LONG_command, CMD_LONG_confirmation, CMD_LONG_param1, CMD_LONG_param2, CMD_LONG_param3, CMD_LONG_param4, CMD_LONG_param5, CMD_LONG_param6, CMD_LONG_param7);
   
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);   // Copy the message to send buffer 
  Pixhawk_Serial.write(buf, len);                         // Send the message (.write sends as bytes) 
 
  // Arm the Mower
  Turn_Off_Relay();
  Motor_Action_Stop_Motors();
  delay(1000);      
}


void Acro_Mode() {


// PIXHAWK Flight Control Modes
// 0 = Manual, 1 = Acro, 3 = Steering, 4 = Hold, 5 = Loiter, 6 = Follow, 7 = Simple, 10 =  Auto
// 11 = RTL, 12 = Smart_RTL, 15 = Guided



  Custom_Mode       = 1;                           ///< Custom mode, can be defined by user/adopter

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_set_mode_pack(System_ID, Component_ID, &msg, Target_System, Base_Mode, Custom_Mode);
 
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  Pixhawk_Serial.write(buf,len);

  
  }


void Manual_Mode() {


// PIXHAWK Flight Control Modes
// 0 = Manual, 1 = Acro, 3 = Steering, 4 = Hold, 5 = Loiter, 6 = Follow, 7 = Simple, 10 =  Auto
// 11 = RTL, 12 = Smart_RTL, 15 = Guided



  Custom_Mode       = 0;                           ///< Custom mode, can be defined by user/adopter

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_set_mode_pack(System_ID, Component_ID, &msg, Target_System, Base_Mode, Custom_Mode);
 
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  Pixhawk_Serial.write(buf,len);

  
  }

//https://www.locarbftw.com/arduino-mavlink-library-changing-flight-modes/

void Auto_Mode() {


// PIXHAWK Flight Control Modes
// 0 = Manual, 1 = Acro, 3 = Steering, 4 = Hold, 5 = Loiter, 6 = Follow, 7 = Simple, 10 =  Auto
// 11 = RTL, 12 = Smart_RTL, 15 = Guided



  Custom_Mode       = 10;                           ///< Custom mode, can be defined by user/adopter

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_set_mode_pack(System_ID, Component_ID, &msg, Target_System, Base_Mode, Custom_Mode);
 
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  Pixhawk_Serial.write(buf,len);

  
  }


void Follow_Mode() {


// PIXHAWK Flight Control Modes
// 0 = Manual, 1 = Acro, 3 = Steering, 4 = Hold, 5 = Loiter, 6 = Follow, 7 = Simple, 10 =  Auto
// 11 = RTL, 12 = Smart_RTL, 15 = Guided



  Custom_Mode       = 6;                           ///< Custom mode, can be defined by user/adopter

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_set_mode_pack(System_ID, Component_ID, &msg, Target_System, Base_Mode, Custom_Mode);
 
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  Pixhawk_Serial.write(buf,len);

  
  }

void Guided_Mode() {


// PIXHAWK Flight Control Modes
// 0 = Manual, 1 = Acro, 3 = Steering, 4 = Hold, 5 = Loiter, 6 = Follow, 7 = Simple, 10 =  Auto
// 11 = RTL, 12 = Smart_RTL, 15 = Guided



  Custom_Mode       = 15;                           ///< Custom mode, can be defined by user/adopter

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_set_mode_pack(System_ID, Component_ID, &msg, Target_System, Base_Mode, Custom_Mode);
 
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  Pixhawk_Serial.write(buf,len);

  
  }
