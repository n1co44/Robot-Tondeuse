/*
 * WebValues.ino
 *
 *
 */




String getJson_index()
{
	String jsonData;
#if defined(WEBSERVER)
	jsonData = "";
	jsonData += "{";

	jsonData += "\"MowerMode\":\"" + MowerMode() + "\"";
	jsonData += ",\"BatteryVoltage\":" + String(BatteryVoltage);
	jsonData += ",\"ChargeAmps\":" + String(Amps);
	jsonData += ",\"MowerTime\":\"" + MowerTime + "\"";

	jsonData += "}";

#endif //-(WEBSERVER)-
	return jsonData;
}


String getJson_setup()
{
	String jsonData;
#if defined(WEBSERVER)
	jsonData = "";
	jsonData += "{";

	jsonData += "\"Compass_Activate\":" + String(Compass_Activate);
	jsonData += ",\"Compass_Heading_Hold_Enabled\":" + String(Compass_Heading_Hold_Enabled);
	jsonData += ",\"GYRO_Enabled\":" + String(GYRO_Enabled);
	jsonData += ",\"Sonar_1_Activate\":" + String(Sonar_1_Activate);
	jsonData += ",\"Sonar_2_Activate\":" + String(Sonar_2_Activate);
	jsonData += ",\"Sonar_3_Activate\":" + String(Sonar_3_Activate);
	jsonData += ",\"Bumper_Activate_Frnt\":" + String(Bumper_Activate_Frnt);
	jsonData += ",\"Alarm_1_ON\":" + String(Alarm_1_ON);
	jsonData += ",\"Alarm_2_ON\":" + String(Alarm_2_ON);
	jsonData += ",\"Alarm_3_ON\":" + String(Alarm_3_ON);
	jsonData += ",\"GPS_Enabled\":" + String(GPS_Enabled);
	jsonData += ",\"Angle_Sensor_Enabled\":" + String(Angle_Sensor_Enabled);
	jsonData += ",\"Tip_Over_Sensor_Enabled\":" + String(Tip_Over_Sensor_Enabled);
	jsonData += ",\"Wheel_Amp_Sensor_ON\":" + String(Wheel_Amp_Sensor_ON);
	jsonData += ",\"Wheels_Activate\":" + String(Wheels_Activate);
	jsonData += ",\"Ramp_Motor_ON\":" + String(Ramp_Motor_ON); // not in EEPROM
	jsonData += ",\"MAG_Speed_Adjustment\":" + String(MAG_Speed_Adjustment); //** Experimental
	jsonData += ",\"Perimeter_Wire_Enabled\":" + String(Perimeter_Wire_Enabled);
	jsonData += ",\"Use_Charging_Station\":" + String(Use_Charging_Station);

	jsonData += "}";

#endif //-(WEBSERVER)-
	return jsonData;
}


String getJson_test()
{
	String jsonData;
#if defined(WEBSERVER)
	jsonData = "";
	jsonData += "{";

	jsonData += "\"BatteryVoltage\":" + String(BatteryVoltage);
	jsonData += ",\"ChargeAmps\":" + String(Amps);
	jsonData += ",\"WheelAmps\":" + String(WheelAmps);
	jsonData += ",\"distance1\":" + String(distance1);
	jsonData += ",\"distance2\":" + String(distance2);
	jsonData += ",\"distance3\":" + String(distance3);
	jsonData += ",\"Sonar_Status\":" + String(Sonar_Status);
	jsonData += ",\"Outside_Wire\":" + String(Outside_Wire);
	jsonData += ",\"Bumper\":" + String(Bumper);
	jsonData += ",\"Tilt_Angle_Sensed\":" + String(Tilt_Angle_Sensed);
	jsonData += ",\"GPS_Inside_Fence\":" + String(GPS_Inside_Fence);
	jsonData += ",\"Rain_Detected\":" + String(Rain_Detected);
	jsonData += ",\"Wheel_Blocked_Status\":" + String(Wheel_Blocked_Status);
	jsonData += ",\"Fake_All_Settings\":" + String(Fake_All_Settings);
	jsonData += ",\"Fake_Loops\":" + String(Fake_Loops);
	jsonData += ",\"Fake_Wire\":" + String(Fake_Wire);
	jsonData += ",\"Fake_WheelAmp\":" + String(Fake_WheelAmp);
	//jsonData += ",\"\":" + String();


	jsonData += "}";

#endif //-(WEBSERVER)-
	return jsonData;
}


String getJson_remoteCtrl()
{
	String jsonData;
#if defined(WEBSERVER)
	jsonData = "";
	jsonData += "{";

	jsonData += "\"MowerMode\":\"" + MowerMode() + "\"";
	//jsonData += ",\"\":" + String();


	jsonData += "}";

#endif //-(WEBSERVER)-
	return jsonData;
}


String getJson_runData()
{
	String jsonData;
#if defined(WEBSERVER)
	jsonData = "";
	jsonData += "{";

	jsonData += "\"BatteryVoltage\":" + String(BatteryVoltage);
	jsonData += ",\"ChargeAmps\":" + String(Amps);

	jsonData += ",\"Loop_Cycle_Mowing\":" + String(Loop_Cycle_Mowing);
	jsonData += ",\"Robot_Status_Value\":" + String(Robot_Status_Value);
	jsonData += ",\"Mower_Error_Value\":" + String(Mower_Error_Value);
	jsonData += ",\"Compass_Steering_Status\":" + String(Compass_Steering_Status);
	jsonData += ",\"Compass_Heading_Degrees\":" + String(Compass_Heading_Degrees);
	jsonData += ",\"MAG_Now\":" + String(MAG_Now);
	jsonData += ",\"Compass_Error\":" + String(Compass_Error);
	jsonData += ",\"PWM_Right\":" + String(PWM_Right);
	jsonData += ",\"PWM_Left\":" + String(PWM_Left);
	jsonData += ",\"Mower_RunBack\":" + String(Mower_RunBack);
	jsonData += ",\"Manouver_Turn_Around_Phase\":" + String(Manouver_Turn_Around_Phase);
	jsonData += ",\"Manouver_Turn_Around_Sonar_Phase\":" + String(Manouver_Turn_Around_Sonar_Phase);

	jsonData += ",\"WheelAmps\":" + String(WheelAmps);
	jsonData += ",\"distance1\":" + String(distance1);
	jsonData += ",\"distance2\":" + String(distance2);
	jsonData += ",\"distance3\":" + String(distance3);
	jsonData += ",\"Sonar_Status\":" + String(Sonar_Status);
	jsonData += ",\"Outside_Wire\":" + String(Outside_Wire);
	jsonData += ",\"Bumper\":" + String(Bumper);
	jsonData += ",\"Tilt_Angle_Sensed\":" + String(Tilt_Angle_Sensed);
	jsonData += ",\"GPS_Inside_Fence\":" + String(GPS_Inside_Fence);
	jsonData += ",\"Rain_Detected\":" + String(Rain_Detected);
	jsonData += ",\"Wheel_Blocked_Status\":" + String(Wheel_Blocked_Status);
	//jsonData += ",\"\":" + String();


	jsonData += "}";

#endif //-(WEBSERVER)-
	return jsonData;
}
