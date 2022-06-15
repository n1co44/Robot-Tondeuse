void Calculate_Wheel_Amps() {
  // Calculate Amp Value from Wheel Amp sensor
 int mVperAmp = 185;
 int ACSoffset = 2500; 
 double VoltageAmp = 0;
 //double Amps = 0;
 VoltageAmp = (RawWheelAmp / 1024.0) * 5000; // Gets you mV
 WheelAmps =  ((VoltageAmp - ACSoffset) / mVperAmp);
 if (WheelAmps < 0) WheelAmps = WheelAmps * - 1;
 if (WheelAmps > 10) WheelAmps = 0;
 if (Fake_WheelAmp) WheelAmps = 4.0; // RVES added
 Serial.print(("|WA:"));
 Serial.print(WheelAmps);
 Serial.print(F("|"));

 }


void Check_Wheel_Amps() {
  Calculate_Wheel_Amps();
  if (Wheel_Amp_Sensor_ON == 1) {
		if (Mower_RunBack > 1) Wheel_Blocked_Count_Max = 10;  // CT during backward is very fast (<15ms), values are readed 2x than changed
		else Wheel_Blocked_Count_Max = 3;
      
        if (WheelAmps >= Max_Wheel_Amps) {
            Wheel_Blocked_Count = Wheel_Blocked_Count + 1;
            if (Wheel_Blocked_Count > Wheel_Blocked_Count_Max) {    
                Serial.println(F(""));
                Serial.print(F("   Wheel Amps: "));
                Serial.print(WheelAmps);
                Serial.print(F("   Wheel Blocked Count: "));
                Serial.print(Wheel_Blocked_Count);
                Serial.print(F("   Max Wheel Amps: "));
                Serial.println(Max_Wheel_Amps);                  
                Serial.println(F(""));
                Serial.println(F("!! Wheel_Blocked !!"));
                Serial.print(F("|")); 
                Wheel_Blocked = 4;
                Print_LCD_Wheel_Blocked(); // RVES added
				#if not defined(NODELAY_BACKWARD)
                Manouver_Turn_Around();
				#endif // -(NODELAY_BACKWARD)-
                }
           }
        else {
          Wheel_Blocked = 0;
          Wheel_Blocked_Count = 0;
          }

		#if defined(NODELAY_BACKWARD)
          if (Wheel_Blocked == 0) Wheel_Blocked_Status = false;
		  if (Wheel_Blocked == 4) Wheel_Blocked_Status = true;
		#endif // -(NODELAY_BACKWARD)-
  }
}



void Test_Check_Wheel_Amps() {

        Serial.print(F("   Wheel Amps: "));
        Serial.print(WheelAmps);
        Serial.print(F("   Wheel Blocked Count: "));
        Serial.print(Wheel_Blocked_Count);
        Serial.print(F("   Max Wheel Amps: "));
        Serial.println(Max_Wheel_Amps);
        
        if (WheelAmps > Max_Wheel_Amps) {
            Wheel_Blocked_Count = Wheel_Blocked_Count + 1;
            if (Wheel_Blocked_Count > Wheel_Blocked_Count_Max) {
                Serial.println(F(""));
                Serial.print("!! Wheel_Blocked !!");
                Serial.print(F("|")); 
                Wheel_Blocked = 4;
                }
            }
        else {
          Wheel_Blocked = 0;
          Wheel_Blocked_Count = 0;
          }
}
