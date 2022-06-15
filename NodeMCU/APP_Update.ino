

void Update_Blynk_App_With_Status() {
#if not defined(LOOP_OPTIMIZE)
         if (Mower_Docked_Filter == 2)   {
           //App Buttons
           Blynk.virtualWrite(V10,LOW);       // Exit Dock Button
           Blynk.virtualWrite(V0, LOW);       // Quick Start Button
           Blynk.virtualWrite(V2, LOW);       // Pause/Stop Button
           Blynk.virtualWrite(V1, LOW);       // Go To Dock Button
           }
         
        if (Mower_Running_Filter == 2)   {
           //App Buttons
           Blynk.virtualWrite(V10,LOW);       // Exit Dock Button
           Blynk.virtualWrite(V0, LOW);       // Quick Start Button
           Blynk.virtualWrite(V2, LOW);       // Pause/Stop Button
           Blynk.virtualWrite(V1, LOW);       // Go To Dock Button
           Wire_ON();
           }

        if (Manuel_Mode == 1)   {
           //App Buttons
           Blynk.virtualWrite(V10,LOW);       // Exit Dock Button 
           Blynk.virtualWrite(V0, LOW);       // Quick Start Button
           Blynk.virtualWrite(V2, LOW);       // Pause/Stop Button
           Blynk.virtualWrite(V1, LOW);       // Go To Dock Button
           
           Blynk.virtualWrite(V6, 0);
           Blynk.virtualWrite(V7, 0);
           Blynk.virtualWrite(V9, 0);     
           Blynk.virtualWrite(V8, 0);
           Wire_ON();
           }

        if (Mower_Parked == 1)   {
           //App Buttons
           Blynk.virtualWrite(V10,LOW);       // Exit Dock Button 
           Blynk.virtualWrite(V0, LOW);       // Quick Start Button
           Blynk.virtualWrite(V2, LOW);       // Pause/Stop Button
           Blynk.virtualWrite(V1, LOW);       // Go To Dock Button
        }

        if (Compass_Activate == 1) Blynk.virtualWrite(V20, 1);
		if (Compass_Activate == 0) Blynk.virtualWrite(V20, 2);

		if (Compass_Heading_Hold_Enabled == 1) Blynk.virtualWrite(V21, 1);
		if (Compass_Heading_Hold_Enabled == 0) Blynk.virtualWrite(V21, 2);

		if (GYRO_Enabled == 1) Blynk.virtualWrite(V22, 1);
		if (GYRO_Enabled == 0) Blynk.virtualWrite(V22, 2);

		if (Sonar_1_Activate == 1) Blynk.virtualWrite(V24, 1);
		if (Sonar_1_Activate == 0) Blynk.virtualWrite(V24, 2);
		if (Sonar_2_Activate == 1) Blynk.virtualWrite(V25, 1);
		if (Sonar_2_Activate == 0) Blynk.virtualWrite(V25, 2);
		if (Sonar_3_Activate == 1) Blynk.virtualWrite(V26, 1);
		if (Sonar_3_Activate == 0) Blynk.virtualWrite(V26, 2);

		if (Bumper_Activate_Frnt == 1) Blynk.virtualWrite(V29, 1);
		if (Bumper_Activate_Frnt == 0) Blynk.virtualWrite(V29, 2);

		if (Alarm_1_ON == 1) Blynk.virtualWrite(V30, 1);
		if (Alarm_1_ON == 0) Blynk.virtualWrite(V30, 2);
		if (Alarm_2_ON == 1) Blynk.virtualWrite(V31, 1);
		if (Alarm_2_ON == 0) Blynk.virtualWrite(V31, 2);
		if (Alarm_3_ON == 1) Blynk.virtualWrite(V32, 1);
		if (Alarm_3_ON == 0) Blynk.virtualWrite(V32, 2);
		if (GPS_Enabled == 1) Blynk.virtualWrite(V33, 1);
		if (GPS_Enabled == 0) Blynk.virtualWrite(V33, 2);
		if (Angle_Sensor_Enabled == 1) Blynk.virtualWrite(V34, 1);
		if (Angle_Sensor_Enabled == 0) Blynk.virtualWrite(V34, 2);
		if (Tip_Over_Sensor_Enabled == 1) Blynk.virtualWrite(V35, 1);
		if (Tip_Over_Sensor_Enabled == 0) Blynk.virtualWrite(V35, 2);
		if (Wheel_Amp_Sensor_ON == 1) Blynk.virtualWrite(V36, 1);
		if (Wheel_Amp_Sensor_ON == 0) Blynk.virtualWrite(V36, 2);


		if (Charge_Detected == 4)          Blynk.virtualWrite(V12, 1023);     // Charging LED ON
		if (Charge_Detected == 0)          Blynk.virtualWrite(V12, 0);        // Charging LED OFF
		if (Tracking_Wire == 1)            Blynk.virtualWrite(V9, 1023);      // Tracking LED ON
		if (Tracking_Wire == 0)            Blynk.virtualWrite(V9, 0);         // Tracking LED OFF
		if (Mower_Parked == 1)             Blynk.virtualWrite(V6, 1023);      // Parked LED
		if (Mower_Parked == 0)             Blynk.virtualWrite(V6, 0);         // Parked LED
		if (Mower_Running_Filter == 2)     Blynk.virtualWrite(V7, 1023);      // Mowing LED
		if (Mower_Running_Filter != 2)     Blynk.virtualWrite(V7, 0);         // Mowing LED
		if (Mower_Docked_Filter == 2)      Blynk.virtualWrite(V8, 1023);      // Docked LED
		if (Mower_Docked_Filter != 2)      Blynk.virtualWrite(V8, 0);         // Docked LED

#else
   if (Mower_Docked_Filter == 2 || Mower_Running_Filter == 2 || Manuel_Mode == 1 || Mower_Parked == 1) {
        if (V10_Last) Blynk.virtualWrite(V10,LOW);       // Exit Dock Button
        if (V0_Last) Blynk.virtualWrite(V0, LOW);       // Quick Start Button
        if (V2_Last) Blynk.virtualWrite(V2, LOW);       // Pause/Stop Button
        if (V1_Last) Blynk.virtualWrite(V1, LOW);       // Go To Dock Button

        if (Manuel_Mode == 1)   {
           Blynk.virtualWrite(V6, 0);
           Blynk.virtualWrite(V7, 0);
           Blynk.virtualWrite(V9, 0);
           Blynk.virtualWrite(V8, 0);
        }

        if (Mower_Running_Filter == 2 || Manuel_Mode == 1)   {
        	Wire_ON();
        }
   }
   // #if defined(LOOP_OPTIMIZE) - code below include comparison between actual and last value to avoid continuous writing to blink which consume a lot of time
     if (Compass_Activate != Compass_Activate_Last) {
        if (Compass_Activate == 1) Blynk.virtualWrite(V20, 1);  
        if (Compass_Activate == 0) Blynk.virtualWrite(V20, 2);
        Compass_Activate_Last = Compass_Activate;
     }
     if (Compass_Heading_Hold_Enabled != Compass_Heading_Hold_Enabled_Last) {
        if (Compass_Heading_Hold_Enabled == 1) Blynk.virtualWrite(V21, 1);  
        if (Compass_Heading_Hold_Enabled == 0) Blynk.virtualWrite(V21, 2);
        Compass_Heading_Hold_Enabled_Last = Compass_Heading_Hold_Enabled;
     }
     if (GYRO_Enabled != GYRO_Enabled_Last) {
        if (GYRO_Enabled == 1) Blynk.virtualWrite(V22, 1);  
        if (GYRO_Enabled == 0) Blynk.virtualWrite(V22, 2);
        GYRO_Enabled_Last = GYRO_Enabled;
     }
	 if (Sonar_1_Activate != Sonar_1_Activate_Last) {
        if (Sonar_1_Activate == 1) Blynk.virtualWrite(V24, 1);  
        if (Sonar_1_Activate == 0) Blynk.virtualWrite(V24, 2);
        Sonar_1_Activate_Last = Sonar_1_Activate;
     }
     if (Sonar_2_Activate != Sonar_2_Activate_Last) {
        if (Sonar_2_Activate == 1) Blynk.virtualWrite(V25, 1);  
        if (Sonar_2_Activate == 0) Blynk.virtualWrite(V25, 2);
        Sonar_2_Activate_Last = Sonar_2_Activate;
      }
	  if (Sonar_3_Activate != Sonar_3_Activate_Last) {
        if (Sonar_3_Activate == 1) Blynk.virtualWrite(V26, 1);  
        if (Sonar_3_Activate == 0) Blynk.virtualWrite(V26, 2);
        Sonar_3_Activate_Last = Sonar_3_Activate;
       }
      if (Bumper_Activate_Frnt != Bumper_Activate_Frnt_Last) {
        if (Bumper_Activate_Frnt == 1) Blynk.virtualWrite(V29, 1);  
        if (Bumper_Activate_Frnt == 0) Blynk.virtualWrite(V29, 2); 
        Bumper_Activate_Frnt_Last = Bumper_Activate_Frnt;
      }
      if (Alarm_1_ON != Alarm_1_ON_Last) {
        if (Alarm_1_ON == 1) Blynk.virtualWrite(V30, 1);  
        if (Alarm_1_ON == 0) Blynk.virtualWrite(V30, 2);
        Alarm_1_ON_Last = Alarm_1_ON;
      }
      if (Alarm_2_ON != Alarm_2_ON_Last) {
        if (Alarm_2_ON == 1) Blynk.virtualWrite(V31, 1);  
        if (Alarm_2_ON == 0) Blynk.virtualWrite(V31, 2);
        Alarm_2_ON_Last = Alarm_2_ON;
      }
      if (Alarm_3_ON != Alarm_3_ON_Last) {
        if (Alarm_3_ON == 1) Blynk.virtualWrite(V32, 1);  
        if (Alarm_3_ON == 0) Blynk.virtualWrite(V32, 2);
        Alarm_3_ON_Last = Alarm_3_ON;
      }
      if (GPS_Enabled != GPS_Enabled_Last) {
        if (GPS_Enabled == 1) Blynk.virtualWrite(V33, 1);  
        if (GPS_Enabled == 0) Blynk.virtualWrite(V33, 2);
        GPS_Enabled_Last = GPS_Enabled;
      }
      if (Angle_Sensor_Enabled != Angle_Sensor_Enabled_Last) {
        if (Angle_Sensor_Enabled == 1) Blynk.virtualWrite(V34, 1);  
        if (Angle_Sensor_Enabled == 0) Blynk.virtualWrite(V34, 2);
        Angle_Sensor_Enabled_Last = Angle_Sensor_Enabled;
      }
      if (Tip_Over_Sensor_Enabled != Tip_Over_Sensor_Enabled_Last) {
        if (Tip_Over_Sensor_Enabled == 1) Blynk.virtualWrite(V35, 1);  
        if (Tip_Over_Sensor_Enabled == 0) Blynk.virtualWrite(V35, 2);
        Tip_Over_Sensor_Enabled_Last = Tip_Over_Sensor_Enabled;
      }
      if (Wheel_Amp_Sensor_ON != Wheel_Amp_Sensor_ON_Last) {
        if (Wheel_Amp_Sensor_ON == 1) Blynk.virtualWrite(V36, 1);  
        if (Wheel_Amp_Sensor_ON == 0) Blynk.virtualWrite(V36, 2);
        Wheel_Amp_Sensor_ON_Last = Wheel_Amp_Sensor_ON;
      }
      if (Charge_Detected != Charge_Detected_Last) {
        if (Charge_Detected == 4)          Blynk.virtualWrite(V12, 1023);     // Charging LED ON
        if (Charge_Detected == 0)          Blynk.virtualWrite(V12, 0);        // Charging LED OFF
        Charge_Detected_Last = Charge_Detected;
      }
      if (Tracking_Wire != Tracking_Wire_Last) {
        if (Tracking_Wire == 1)            Blynk.virtualWrite(V9, 1023);      // Tracking LED ON
        if (Tracking_Wire == 0)            Blynk.virtualWrite(V9, 0);         // Tracking LED OFF
        Tracking_Wire_Last = Tracking_Wire;
      }
      if (Mower_Parked != Mower_Parked_Last) {
        if (Mower_Parked == 1)             Blynk.virtualWrite(V6, 1023);      // Parked LED
        if (Mower_Parked == 0)             Blynk.virtualWrite(V6, 0);         // Parked LED
        Mower_Parked_Last = Mower_Parked;
      }
      if (Mower_Running_Filter != Mower_Running_Filter_Last) {
        if (Mower_Running_Filter == 2)     Blynk.virtualWrite(V7, 1023);      // Mowing LED
        if (Mower_Running_Filter != 2)     Blynk.virtualWrite(V7, 0);         // Mowing LED
        Mower_Running_Filter_Last = Mower_Running_Filter;
      }
      if (Mower_Docked_Filter != Mower_Docked_Filter_Last) {
        if (Mower_Docked_Filter == 2)      Blynk.virtualWrite(V8, 1023);      // Docked LED
        if (Mower_Docked_Filter != 2)      Blynk.virtualWrite(V8, 0);         // Docked LED
        Mower_Docked_Filter_Last = Mower_Docked_Filter;
      }
#endif
	}






void Clear_APP() {
  Blynk.virtualWrite(V0, LOW);   // Start Mowing Buton OFF
  Blynk.virtualWrite(V1, LOW);  // Go-Home Button OFF
  Blynk.virtualWrite(V2, LOW);  // Stop Button OFF
  Blynk.virtualWrite(V3, 0);    // Reset Voltage
  Blynk.virtualWrite(V5, 0);    // Loops
  Blynk.virtualWrite(V7, 0);    // Mow LED
  Blynk.virtualWrite(V8, 0);    // Dock LED Off
  Blynk.virtualWrite(V9, 0);    // TrackingLED OFF
  Blynk.virtualWrite(V10, LOW); // Dock Button OFF
  Blynk.virtualWrite(V11, 0);   // Compass LED OFF  
  Blynk.virtualWrite(V12, 0);   // Charging LED OFF  
  Blynk.virtualWrite(V12, 0);   // Charging LED OFF  
}
