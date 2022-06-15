// All the recieved information functions

void Receive_All_From_MEGA () {
#if not defined(NODELAY_SERIALCOM)
  String NodeMCU_RX_Value  = "";                                              // changed to string

  while (NodeMCU.available() > 0) {
    
    char recieved = NodeMCU.read();
    if ( recieved != '\g'  && recieved != '\c' && recieved != '\d' && recieved != '\z' && recieved != '\y' && recieved != '\o' && recieved != '\m' ) {   
      NodeMCU_RX_Value = NodeMCU_RX_Value +  (char)recieved;          // hack to joining chars in correct way to Serial1_Rx_Value
      } 

      else if (recieved == '\g') {
      val_VoltNow = NodeMCU_RX_Value.toFloat();                                 // if end of value found, set AmpsTX and clear Serial1_Rx_Value temp var Serial1_Rx_Value used for holding value until \q or \j
      NodeMCU_RX_Value = ""; // changed to string
      } 
      else if (recieved == '\c') {
      Loop_Cycle_Mowing = NodeMCU_RX_Value.toInt();                                // updates loop cycle 
      NodeMCU_RX_Value = "";
      } 
      else if (recieved == '\d') {
      Mower_Docked = NodeMCU_RX_Value.toInt();                               // updates if mower is docked
      NodeMCU_RX_Value = "";
      } 
      else if (recieved == '\z') {
      Mower_Running = NodeMCU_RX_Value.toInt();                               // updates is mower is running
      NodeMCU_RX_Value = "";
      } 
      else if (recieved == '\y') {
      Mower_Parked = NodeMCU_RX_Value.toInt();                               // updates if mower is parked
      NodeMCU_RX_Value = "";
      } 
      else if (recieved == '\o') {
      Charge_Detected = NodeMCU_RX_Value.toInt();                               // updates if mower is charging
      NodeMCU_RX_Value = "";
      } 
      else if (recieved == '\m') {
      Tracking_Wire = NodeMCU_RX_Value.toInt();                               // updates if tracking
      NodeMCU_RX_Value = "";
      } 
    else SerialDebug.print("No Data Received|");
  }
#else
  #if not defined(WEBSERVER)
	byte recvBuff [10] = {0};
  #else
	byte recvBuff [50] = {0};
  #endif // -(WEBSERVER)-

	int recvVal = 0;

	if (NodeMCUCom.update ())
	{
	  byte length = NodeMCUCom.getLength ();
	  if (length > sizeof (recvBuff)) length = sizeof (recvBuff);
	  memcpy (&recvBuff, NodeMCUCom.getData (), length);

	  val_VoltNow =   recvBuff[0] | recvBuff[1] << 8;
	  Loop_Cycle_Mowing =  recvBuff[2] | recvBuff[3] << 8;
	  Mower_Docked = recvBuff[4];
	  Mower_Running =   recvBuff[5];
	  Mower_Parked =   recvBuff[6];
	  Charge_Detected =   recvBuff[7];
	  Tracking_Wire =   recvBuff[8];

	#if defined(WEBSERVER)
		Mower_RunBack = recvBuff[9];
		Robot_Status_Value = recvBuff[10];
		Mower_Error_Value = recvBuff[11];
		Compass_Steering_Status = recvBuff[12];
		int WheelAmpsRX = recvBuff[13] | recvBuff[14] << 8;
		WheelAmps = (float)WheelAmpsRX / 100;
		int Compass_Heading_DegreesRX = recvBuff[15] | recvBuff[16] << 8;
		Compass_Heading_Degrees = (float)Compass_Heading_DegreesRX;
		Manouver_Turn_Around_Phase = recvBuff[17];
		Manouver_Turn_Around_Sonar_Phase = recvBuff[18];
		//reserve = recvBuff[19];
		PWM_Right = recvBuff[20];
		PWM_Left = recvBuff[21];
		int Compass_ErrorRX = recvBuff[22] | recvBuff[23] << 8;
		Compass_Error = ((float)Compass_ErrorRX - 1000) / 100;
		int AmpsRX = (recvBuff[25] << 8) | recvBuff[24] ;
		Amps = ((float)AmpsRX - 1000) / 100;

		distance1 = recvBuff[26] | recvBuff[27] << 8;
		distance2 = recvBuff[28] | recvBuff[29] << 8;
		distance3 = recvBuff[30] | recvBuff[31] << 8;

		Sonar_Status = bitRead(recvBuff[32],0);
		Outside_Wire = bitRead(recvBuff[32],1);
		Bumper = bitRead(recvBuff[32],2);
		Tilt_Angle_Sensed = bitRead(recvBuff[32],3);
		GPS_Inside_Fence = bitRead(recvBuff[32],4);
		Tilt_Orientation_Sensed = bitRead(recvBuff[32],5);
		Rain_Detected = bitRead(recvBuff[32],6);
		Wheel_Blocked_Status = bitRead(recvBuff[32],7);

		Wheels_Activate = bitRead(recvBuff[33],0);
		Ramp_Motor_ON = bitRead(recvBuff[33],1);
		MAG_Speed_Adjustment = bitRead(recvBuff[33],2);
		Perimeter_Wire_Enabled = bitRead(recvBuff[33],3);
		Use_Charging_Station = bitRead(recvBuff[33],4);
		Wire_Detected = bitRead(recvBuff[33],5);
		Blade_flagRun = bitRead(recvBuff[33],6);
		// = bitRead(recvBuff[33],7);


		Fake_All_Settings = bitRead(recvBuff[34],0);
		Fake_Loops = bitRead(recvBuff[34],1);
		Fake_Wire = bitRead(recvBuff[34],2);
		Fake_WheelAmp = bitRead(recvBuff[34],3);
		// = bitRead(recvBuff[34],4);

		Time_Year = recvBuff[35] | recvBuff[36] << 8;
		Time_Month = recvBuff[37];
		Time_Date = recvBuff[38];
		Time_Hour = recvBuff[39];
		Time_Minute = recvBuff[40];
		Time_Second = recvBuff[41];
		Time_Day = recvBuff[42];

		Wheel_Status_Value = recvBuff[43];
		MAG_Now = recvBuff[44] | recvBuff[45] << 8;
		Sonar_Hit_1_Total = recvBuff[46];
		Sonar_Hit_2_Total = recvBuff[47];
		Sonar_Hit_3_Total = recvBuff[48];

		Low_Battery_Detected = recvBuff[49];

		RX_data_from_Mega_updated = true;
	#endif // -(WEBSERVER)-
	}  // end if something received

#endif

	#if not defined(NODELAY_SERIALCOM)
        BatteryVoltage = val_VoltNow;
	#else
        BatteryVoltage = val_VoltNow/100;
	#endif
        if(RX_data_from_Mega_updated) {
        SerialDebug.print(F("|Time:"));
		if (Time_Hour < 10) SerialDebug.print("0");
		SerialDebug.print(Time_Hour);
		SerialDebug.print(F(":"));
		if (Time_Minute < 10) SerialDebug.print("0");
		SerialDebug.print(Time_Minute);

        SerialDebug.print("|A:");
        SerialDebug.print(Amps);

        SerialDebug.print("|V:");
        SerialDebug.print(BatteryVoltage);
        SerialDebug.print("|");

        if 		(Robot_Status_Value == 1) SerialDebug.print(F("Docked:1|"));
        else if (Robot_Status_Value == 2) SerialDebug.print(F("Parked:1|"));
        else if (Robot_Status_Value == 4) SerialDebug.print(F("Mower Error:1|"));
        else if (Robot_Status_Value == 5) SerialDebug.print(F("Running:1|"));
        else if (Robot_Status_Value == 6) SerialDebug.print(F("Manuel Mode:1|"));
        else if (Robot_Status_Value == 7) SerialDebug.print(F("Tracking_Wire:1|"));
        else if (Robot_Status_Value == 9) SerialDebug.print(F("Exiting_Dock:1|"));
        //else if (Robot_Status_Value == 1) SerialDebug.print(F("Park_Low_Batt:1|")); //TODO

        if (Mower_Running == 1) {
			SerialDebug.print("|VLow:");
			SerialDebug.print(Low_Battery_Detected);
        }

/*
        SerialDebug.print("|Docked:");
        SerialDebug.print(Mower_Docked);
        
        SerialDebug.print("|Running:");
        SerialDebug.print(Mower_Running);

        SerialDebug.print("|Parked:");
        SerialDebug.print(Mower_Parked);
*/
        if (Mower_Docked == 1 || Mower_Parked == 1) {
			SerialDebug.print("|Charging:");
			SerialDebug.print(Charge_Detected);
        }
/*
        SerialDebug.print("|Tracking:");
        SerialDebug.print(Tracking_Wire);
        */
        SerialDebug.print("|MAG:");
        SerialDebug.print(MAG_Now);

        SerialDebug.print(F("|Wire:"));
        if (Perimeter_Wire_Enabled) {
            if (Wire_Detected == 0) SerialDebug.print(F("OFF"));
            if (Wire_Detected == 1) SerialDebug.print(F("ON"));
        } else SerialDebug.print(F("DISABLED"));

        if (Mower_Running == 1) {
			SerialDebug.print("|A:");
			SerialDebug.print(Tilt_Angle_Sensed);

			SerialDebug.print("|O:");
			SerialDebug.print(Tilt_Orientation_Sensed);

			SerialDebug.print("|WA:");
			SerialDebug.print(WheelAmps);

			SerialDebug.print("|S2:");
			SerialDebug.print(distance2);
			SerialDebug.print("cm/");
			SerialDebug.print(Sonar_Hit_2_Total);

			SerialDebug.print("|S1:");
			SerialDebug.print(distance1);
			SerialDebug.print("cm/");
			SerialDebug.print(Sonar_Hit_1_Total);

			SerialDebug.print("|S3:");
			SerialDebug.print(distance3);
			SerialDebug.print("cm/");
			SerialDebug.print(Sonar_Hit_3_Total);

        }
  
        SerialDebug.print(F("|Wheel:"));
        if 		(Wheel_Status_Value == 1) SerialDebug.print(F("FULL"));
        else if (Wheel_Status_Value == 2) SerialDebug.print(F("R-FULL"));
        else if (Wheel_Status_Value == 3) SerialDebug.print(F("S-FULL"));
        else if (Wheel_Status_Value == 4) SerialDebug.print(F("SLOW"));
        else if (Wheel_Status_Value == 5) SerialDebug.print(F("For"));
        else if (Wheel_Status_Value == 6) SerialDebug.print(F("Rev"));
        else if (Wheel_Status_Value == 7) SerialDebug.print(F("OFF"));
        else if (Wheel_Status_Value == 8) SerialDebug.print(F("TL_"));
        else if (Wheel_Status_Value == 9) SerialDebug.print(F("TR_"));
        else if (Wheel_Status_Value == 10) SerialDebug.print(F("CIRCLE"));
        SerialDebug.print("|");

        if (Mower_Running == 1) {
			SerialDebug.print("|Loop:");
			SerialDebug.print(Loop_Cycle_Mowing);
        }

        if (Mower_Running == 1 && Loop_Cycle_Mowing % 20 == 0) {
			SerialDebug.print(F("|Comp°:"));
			SerialDebug.print(Compass_Heading_Degrees);
			SerialDebug.print(F("|C_Err:"));
			SerialDebug.print(Compass_Error);
			if (Compass_Error < 0) { Serial.print(F("|SR")); }  // Steer right
			else { Serial.print(F("|SL")); }                    // Steer left
			SerialDebug.print(F("|PWM_R:"));
			SerialDebug.print(PWM_Right);
			SerialDebug.print(F("|PWM_L:"));
			SerialDebug.print(PWM_Left);
        }
        if      (Loop_Cycle_Mowing < 50) { Serial.print(F("C-Lock:OFF")); }
        else if (Loop_Cycle_Mowing > 50) { Serial.print(F("C-Lock:ON_")); }

        SerialDebug.print(F("|Blades:"));
        if (Blade_flagRun) SerialDebug.print(F("ON_"));
        else SerialDebug.print(F("OFF"));

        SerialDebug.print(F("|ME:"));
        SerialDebug.print(Mower_Error_Value);

        //RX_data_from_Mega_updated = false;
        }

  Calculate_Filtered_Mower_Status();
}


void Calculate_Filtered_Mower_Status() {

    if (Mower_Docked == 1) {
      Mower_Docked_Filter = Mower_Docked_Filter + 1;
      if (Mower_Docked_Filter == 3) Mower_Docked_Filter = 2;
      if (Auto_Wire == 1) PCBWire_WEMOSD1.virtualWrite(V1, 2, 1000);
    }
    else Mower_Docked_Filter = 0;
    
    if (Mower_Running == 1) {
      Mower_Running_Filter = Mower_Running_Filter + 1;
      if (Mower_Running_Filter == 3) Mower_Running_Filter = 2;
      if (Auto_Wire == 1) PCBWire_WEMOSD1.virtualWrite(V1, 1, 1000);
    }
    else Mower_Running_Filter = 0;
    
}




void Recieve_App_Button_Status_1 () {

  String NodeMCU_RX_Value  = "";                                              // changed to string

  while (NodeMCU.available() > 0) {
    
    char recieved = NodeMCU.read();
    if ( recieved != '\a'  && recieved != '\b' && recieved != '\c' &&
    recieved != '\d'  && recieved != '\e' && recieved != '\f' && recieved != '\g' ) {   
      NodeMCU_RX_Value = NodeMCU_RX_Value +  (char)recieved;          // hack to joining chars in correct way to Serial1_Rx_Value
      } 

      else if (recieved == '\a') {
      Compass_Activate = NodeMCU_RX_Value.toInt();                                 // if end of value found, set AmpsTX and clear Serial1_Rx_Value temp var Serial1_Rx_Value used for holding value until \q or \j
      NodeMCU_RX_Value = ""; // changed to string
      } 
      else if (recieved == '\b') {
      Compass_Heading_Hold_Enabled = NodeMCU_RX_Value.toInt();                                // same as upper but for VoltsTX, 
      NodeMCU_RX_Value = "";
      } 
      else if (recieved == '\c') {
      GYRO_Enabled = NodeMCU_RX_Value.toInt();                               // same as upper but for VoltsTX
      NodeMCU_RX_Value = "";
      }
      else if (recieved == '\d') {
      Sonar_1_Activate = NodeMCU_RX_Value.toInt();                               // same as upper but for VoltsTX
      NodeMCU_RX_Value = "";
      }
      else if (recieved == '\e') {
      Sonar_2_Activate = NodeMCU_RX_Value.toInt();                               // same as upper but for VoltsTX
      NodeMCU_RX_Value = "";
      }
      else if (recieved == '\f') {
      Sonar_3_Activate = NodeMCU_RX_Value.toInt();                               // same as upper but for VoltsTX
      NodeMCU_RX_Value = "";
      }
      else if (recieved == '\g') {
      Bumper_Activate_Frnt = NodeMCU_RX_Value.toInt();                               // same as upper but for VoltsTX
      NodeMCU_RX_Value = "";
      }
    
    
    else SerialDebug.print("No Data Received|");
  }
        SerialDebug.println("");
        SerialDebug.print("Compass_Activate :");
        SerialDebug.println(Compass_Activate);
        SerialDebug.print("Heading Hold TX :");
        SerialDebug.println(Compass_Heading_Hold_Enabled);
        SerialDebug.print("GYRO TX :");
        SerialDebug.println(GYRO_Enabled);
        SerialDebug.print("Sonar 1 ON :");
        SerialDebug.println(Sonar_1_Activate);
        SerialDebug.print("Sonar 2 ON :");
        SerialDebug.println(Sonar_2_Activate);
        SerialDebug.print("Sonar 3 ON :");
        SerialDebug.println(Sonar_3_Activate);
        SerialDebug.print("Bumper ON:");
        SerialDebug.println(Bumper_Activate_Frnt);
        SerialDebug.println("");

}






// Second Group of APP Settings Received from Mower
void Recieve_App_Button_Status_2 () {

  String NodeMCU_RX_Value  = "";                                              // changed to string

  while (NodeMCU.available() > 0) {
    
    char recieved = NodeMCU.read();
    if ( recieved != '\a'  && recieved != '\b' && recieved != '\c' &&
    recieved != '\d'  && recieved != '\e' && recieved != '\f' && recieved != '\g' ) {   
      NodeMCU_RX_Value = NodeMCU_RX_Value +  (char)recieved;          // hack to joining chars in correct way to Serial1_Rx_Value
      } 

      else if (recieved == '\a') {
      Alarm_1_ON = NodeMCU_RX_Value.toInt();                                 // if end of value found, set AmpsTX and clear Serial1_Rx_Value temp var Serial1_Rx_Value used for holding value until \q or \j
      NodeMCU_RX_Value = ""; // changed to string
      } 
      else if (recieved == '\b') {
      Alarm_2_ON  = NodeMCU_RX_Value.toInt();                                // same as upper but for VoltsTX, 
      NodeMCU_RX_Value = "";
      } 
      else if (recieved == '\c') {
      Alarm_3_ON  = NodeMCU_RX_Value.toInt();                               // same as upper but for VoltsTX
      NodeMCU_RX_Value = "";
      }
      else if (recieved == '\d') {
      GPS_Enabled = NodeMCU_RX_Value.toInt();                               // same as upper but for VoltsTX
      NodeMCU_RX_Value = "";
      }
      else if (recieved == '\e') {
      Angle_Sensor_Enabled  = NodeMCU_RX_Value.toInt();                               // same as upper but for VoltsTX
      NodeMCU_RX_Value = "";
      }
      else if (recieved == '\f') {
      Tip_Over_Sensor_Enabled = NodeMCU_RX_Value.toInt();                               // same as upper but for VoltsTX
      NodeMCU_RX_Value = "";
      }
      else if (recieved == '\g') {
      Wheel_Amp_Sensor_ON = NodeMCU_RX_Value.toInt();                               // same as upper but for VoltsTX
      NodeMCU_RX_Value = "";
      }
    
    
    else SerialDebug.print("No Data Received|");
  }
      SerialDebug.println("");
      SerialDebug.print(F("Alarm 1 ON :"));
      SerialDebug.println(Alarm_1_ON);
      SerialDebug.print(F("Alarm 2 ON :"));
      SerialDebug.println(Alarm_2_ON);
      SerialDebug.print(F("Alarm 3 ON :"));
      SerialDebug.println(Alarm_3_ON);
      SerialDebug.print(F("GPS Enabled :"));
      SerialDebug.println(GPS_Enabled);
      SerialDebug.print(F("Angle Sensor :"));
      SerialDebug.println(Angle_Sensor_Enabled );
      SerialDebug.print(F("Tip Over Sensor :"));
      SerialDebug.println(Tip_Over_Sensor_Enabled);
      SerialDebug.print(F("Wheel Amp Sensor ON:"));
      SerialDebug.println(Wheel_Amp_Sensor_ON);
      SerialDebug.println("");

}
