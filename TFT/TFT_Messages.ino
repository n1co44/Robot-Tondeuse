

void Print_Battery_Graphic() {


if (Battery_Display == 1) {
  // Global Variable = Battery                              // Battery % remaining
  int Battery_Bar_Width = 60;                               // Width of the battery bar
  int Battery_Bar_Height = 20;                              // Height of the battery bar
  int Battery_Value = ( (60*10) / 100 ) * (Battery / 10);   // Calculates the width of the bar depending on the % remaining
  int Battery_Pos_X = 360;                                  // X Coordinate of the Battery Symbol
  int Battery_Pos_Y = 10;                                   // Y Coordinate of the Battery Symbol
  int Txt_Size_Label = 2;                                   // Text size of the battery % text
  
  //Serial.print("Battery Value");
  //Serial.println(Battery_Value);

  // Create a white Box (Border) as background to the Battery
  tft.fillRect((Battery_Pos_X - 1), (Battery_Pos_Y - 1), (Battery_Bar_Width + 2), (Battery_Bar_Height + 2) , WHITE); 
  // Create a grey background
  tft.fillRect((Battery_Pos_X), (Battery_Pos_Y), (Battery_Bar_Width), (Battery_Bar_Height) , GREY); 
  
   // X_Coord,  Y_Coord, W, H, Colour
  if (Battery_Value < 10)  tft.fillRect(Battery_Pos_X, Battery_Pos_Y, Battery_Value, Battery_Bar_Height, RED);  
  if (Battery_Value >= 10)  tft.fillRect(Battery_Pos_X, Battery_Pos_Y, Battery_Value, Battery_Bar_Height, YELLOW);       
  if (Battery_Value >= 20)  tft.fillRect(Battery_Pos_X, Battery_Pos_Y, Battery_Value, Battery_Bar_Height, GREEN);  

  tft.setTextSize(Txt_Size_Label); 
  tft.setTextColor(YELLOW, BLACK);      //Text Colour/ Background Colour
  tft.setCursor( (Battery_Pos_X + Battery_Bar_Width + 5), (Battery_Pos_Y + 4) );            // Text Coordinates X, Y
  tft.print(Battery); 
  tft.print(F("% "));
}

if (Battery_Display == 2) {
       tft.setTextSize(3); 
       tft.setCursor(362,10); 
       tft.setTextColor(BLACK, BLACK);     
       tft.print(Battery_Last);
       tft.setCursor(362,10); 
       Battery = Battery;
       if (Battery < 14.00)        tft.setTextColor(GREEN, BLACK); 
       if (Battery < 12.20)        tft.setTextColor(YELLOW, BLACK); 
       if (Battery < 11.80)        tft.setTextColor(RED, BLACK); 
       tft.print(Battery);
       tft.setCursor(455,10);
       tft.print("V");
       Battery_Last = Battery;
       
      }  
   
  
  }








// Print the eecived time to the TFT Menu.
void Print_Time_TFT() {
      tft.setTextSize(3); 
      tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
      tft.setCursor(385, 290);            // Text Coordinates X, Y
      tft.print(Time_Hour);
      tft.print(":");
      if (Time_Minute < 10) tft.print ("0");
      tft.println(Time_Minute);  
      }

// Print the eecived date to the TFT Menu.
void Print_Date_TFT() {
      tft.setTextSize(2);
      tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
      tft.setCursor(310, 270);            // Text Coordinates X, Y
      tft.print(Time_Year);
	  tft.print(F("-"));
	  if (Time_Month < 10) tft.print ("0");
	  tft.print(Time_Month);
	  tft.print(F("-"));
	  if (Time_Date < 10) tft.print ("0");
	  tft.print(Time_Date);
      char buf[4];
      snprintf(buf, sizeof(buf), " %s", dayAsString(Time_Day).c_str());
      tft.print(buf);
      }

void Run_Loop_Count() {
    Loop = Loop + 1;
    if (Loop > 59) Loop = 0;
    }

void Label_TFT_Loop_Info_Mowing() {
#if defined(LOOP_OPTIMIZE)
    // Loops text on TFT
    tft.setTextColor(GREEN, BLACK);      // Text Colour/ Background Colour
    tft.setTextSize(2);
    tft.setCursor(20, 250);            // Text Coordinates X, Y
    tft.print(F("Loops: "));
#endif
}

void Clear_TFT_Loop_Info_Mowing() {
    // Loops Info
    tft.setTextColor(BLACK, BLACK);      // Text Colour/ Background Colour
    tft.setTextSize(2);
#if not defined(LOOP_OPTIMIZE)
    tft.setCursor(20, 250);            // Text Coordinates X, Y
    tft.print(F("Loops: "));
#endif
    tft.setCursor(100, 250);            // Text Coordinates X, Y
#if not defined(LOOP_OPTIMIZE)
    tft.print(Loops);  
#else
    tft.print(Loops_Last);
#endif
    }

void Update_TFT_Loop_Info_Mowing() {

    // Loops Info
    tft.setTextColor(GREEN, BLACK);      // Text Colour/ Background Colour
    tft.setTextSize(2); 
#if not defined(LOOP_OPTIMIZE)
    tft.setCursor(20, 250);            // Text Coordinates X, Y
    tft.print(F("Loops: "));
#else
    Loops_Last = Loops;
#endif
    tft.setCursor(100, 250);            // Text Coordinates X, Y
    tft.print(Loops);  

}


void Print_Confirmation_Text_ERROR() {
      
      bool Error_Found = 0;
      Menu_Complete_Mowing = true;
      Menu_Complete_Main = true;
      if (Error_Printed_1 == 0) {                        // if already printed dont print again
        tft.fillScreen(BLACK);
        Print_Battery_Graphic();                      // Shows the battery value
        delay(200);  
        Serial.println("Printing Error Graphic");
        // Draw Red Circle with !
        tft.fillCircle(70, 150, 70, RED);             // X, Y, Radius
        tft.fillRect(60, 105, 20, 60 , WHITE);        // X, Y, Width, Height
        tft.fillRect(60, 175, 20, 20 , WHITE);        // X, Y, Width, Height  
        }   


      if ((Mower_Error_Value == 1) && (Error_Printed_1 == 0)) {
            tft.setTextSize(6); 
            tft.setTextColor(GREEN, BLACK);               //Text Colour/ Background Colour
            tft.setCursor(160, 100);                      // Text Coordinates X, Y
            tft.print(F("ERROR"));  
            tft.setTextColor(YELLOW, BLACK); 
            tft.setCursor(160, 160);              // Text Coordinates X, Y
            tft.print(F("WIRE OFF")); 
            //delay(4000);
            Error_Found = 1;
            Error_Printed_1 = 1;
            }
      if (Mower_Error_Value == 2) {
            tft.setTextSize(6); 
            tft.setTextColor(WHITE, BLACK);               //Text Colour/ Background Colour
            tft.setCursor(160, 100);                      // Text Coordinates X, Y
            tft.print(F("PARKED"));  
            tft.setTextColor(YELLOW, BLACK); 
            tft.setCursor(160, 160);              // Text Coordinates X, Y
            tft.print(F("LOW BATT")); 
            //delay(4000);
            Error_Found = 1;
            }
      if (Mower_Error_Value == 3) {
            tft.setTextSize(6); 
            tft.setTextColor(WHITE, BLACK);               //Text Colour/ Background Colour
            tft.setCursor(160, 100);                      // Text Coordinates X, Y
            tft.print(F("PARKED"));  
            tft.setTextColor(YELLOW, BLACK); 
            tft.setCursor(160, 160);              // Text Coordinates X, Y
            tft.print(F("TIP OVER")); 
            //delay(4000);
            Error_Found = 1;
            }
      
      if (Error_Found == 4) {
            tft.setTextSize(6); 
            tft.setTextColor(YELLOW, BLACK);               //Text Colour/ Background Colour
            tft.setCursor(160, 100);                      // Text Coordinates X, Y
            tft.print(F("ERROR"));  
            tft.setTextColor(YELLOW, BLACK); 
            tft.setCursor(160, 160);              // Text Coordinates X, Y
            tft.print(F("UNKNOWN")); 
            delay(4000);
            Error_Found = 1;
            }
      Serial.println("Error Graphic Done");
      }


void Label_TFT_Mower_Messages_Mowing() {
#if defined(LOOP_OPTIMIZE)
 tft.setTextSize(3);
 tft.setTextColor(GREEN, BLACK);
 tft.setCursor(20, 280);
 tft.print("W:  S: ");

 if (Robot_Type == 1) {
	 tft.print(" B: ");
	 }

 if (Robot_Type == 2) {
	 tft.print(" D: ");
	 }

 tft.print(" RS:  T:");



 // Wheel amps, and Compass °
 tft.setTextSize(2);
 tft.setCursor(160, 250);
 tft.print("WA:");
 tft.setCursor(290, 250);
 tft.print("CH:");
#endif
}


void Update_TFT_Mower_Messages_Mowing() {

     bool Skip_Message = 0;
     bool Show_Update = 1;

     if (Show_Update == 1) {
#if not defined(LOOP_OPTIMIZE)
         tft.setTextSize(3);
         tft.setCursor(20, 280);
         tft.print("W:");
         tft.print(Wire_Status);
         tft.print(" S:");
         tft.print(Sonar_Status);
         
         if (Robot_Type == 1) {
             tft.print(" B:");
             tft.print(Bumper_Status);
             }

         if (Robot_Type == 2) {
             tft.print(" D:");
             tft.print(Drill_Status);
             }

         tft.print(" RS:");
         tft.print(Robot_Status_Value);
         tft.print(" T:");
         tft.print(Tilt_Angle_Sensed);

#else
         tft.setTextSize(3);
         tft.setTextColor(GREEN, BLACK);
	 if (Wire_Status != Wire_Status_Last || refreshTFT) {
         tft.setCursor(56, 280);
         tft.print(Wire_Status);
         //Wire_Status_Last = Wire_Status;
     }
	 if (Sonar_Status != Sonar_Status_Last || refreshTFT) {
         tft.setCursor(128, 280);
         tft.print(Sonar_Status);
         //Sonar_Status_Last = Sonar_Status;
	 }

	 if (Robot_Type == 1 && (Bumper_Status != Bumper_Status_Last  || refreshTFT)) {
		 tft.setCursor(200, 280);
		 tft.print(Bumper_Status);
		 //Bumper_Status_Last = Bumper_Status;
		 }

	 if (Robot_Type == 2 && (Drill_Status != Drill_Status_Last  || refreshTFT)) {
		 tft.setCursor(200, 280);
		 tft.print(Drill_Status);
		 //Drill_Status_Last = Drill_Status;
		 }

	 if (Robot_Status_Value != Robot_Status_Value_Last || refreshTFT) {
         tft.setCursor(290, 280);
         tft.print(Robot_Status_Value);
         Robot_Status_Value_Last = Robot_Status_Value;
	 }
	 if (Tilt_Angle_Sensed != Tilt_Angle_Sensed_Last || refreshTFT) {
         tft.setCursor(360, 280);
         tft.print(Tilt_Angle_Sensed);
         //Tilt_Angle_Sensed_Last = Tilt_Angle_Sensed;
	 }

	 // Wheel amps, and Compass °
	 tft.setTextSize(2);
	 if (WheelAmpsRX != WheelAmpsRX_Last || refreshTFT) {
		 tft.fillRect(200, 250, 80, 16 , BLACK);        // X, Y, Width, Height
		 tft.setTextColor(GREEN, BLACK);
         tft.setCursor(200, 250);
         float WheelAmps = (float)WheelAmpsRX / 100;
		 tft.print(WheelAmps);
         WheelAmpsRX_Last = WheelAmpsRX;
	 }

	 if (Compass_Heading_Degrees != Compass_Heading_Degrees_Last || refreshTFT) {
         tft.setCursor(325, 250);
         //tft.setTextColor(BLACK, BLACK);
         //tft.print(Compass_Heading_Degrees_Last);
         tft.fillRect(320, 250, 60, 16 , BLACK);        // X, Y, Width, Height
         tft.setTextColor(GREEN, BLACK);
		 tft.print(Compass_Heading_Degrees);
         Compass_Heading_Degrees_Last = Compass_Heading_Degrees;
	 }
#endif // -(LOOP_OPTIMIZE)-

     if (GPS_Enabled == 1) {
         if (GPS_In_Out_TX == 1) {
          tft.setCursor(330, 50);
          tft.setTextColor(BLACK, BLACK);
          tft.print("GPS:OUT");
          tft.setCursor(330, 50);
          tft.setTextColor(GREEN, BLACK);
          tft.print("GPS:IN");
          }
         
         if (GPS_In_Out_TX == 0) {
          tft.setCursor(330, 50);
          tft.setTextColor(GREEN, BLACK);
          tft.print("GPS:OUT");   
          }
         
         
         tft.setCursor(330, 80);
         tft.setTextColor(GREEN, BLACK);
         tft.print("FIX:");
         if (GPS_Lock_OK_TX == 1) tft.print("RTK");
         if (GPS_Lock_OK_TX == 0) tft.print("FIX");
         }

     }
     
     tft.setTextSize(8);
    
#if defined(LOOP_OPTIMIZE)
     if (Sonar_Status != Sonar_Status_Last) {
#endif // -(LOOP_OPTIMIZE)-
     if ((Sonar_Status == 0) && (Skip_Message == 0)) {
       tft.setCursor(180,100); 
       tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour  
       tft.print("SONAR");      
       }
     if ((Sonar_Status == 1)  && (Skip_Message == 0)){
       tft.setCursor(180,100); 
       tft.setTextColor(YELLOW, BLACK); 
       tft.print("SONAR");
       Skip_Message = 1;
       }
#if defined(LOOP_OPTIMIZE)
     Sonar_Status_Last = Sonar_Status;
     }
#endif // -(LOOP_OPTIMIZE)-
    
     if (Perimeter_Wire_Enabled == 1) {
	#if defined(LOOP_OPTIMIZE)
		 if (Wire_Status != Wire_Status_Last) {
	#endif // -(LOOP_OPTIMIZE)-
         if ((Wire_Status == 0) && (Skip_Message == 0)) {
           tft.setCursor(180,100); 
           tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour 
           tft.print("WIRE");       
           }
         if ((Wire_Status == 1)  && (Skip_Message == 0)){
           tft.setCursor(180,100); 
           tft.setTextColor(YELLOW, BLACK); 
           tft.print("WIRE");
           Skip_Message = 1;
           }
	#if defined(LOOP_OPTIMIZE)
		 Wire_Status_Last = Wire_Status;
		 }
	#endif // -(LOOP_OPTIMIZE)-
        }

   if (Robot_Type == 1) {
	#if defined(LOOP_OPTIMIZE)
		 if (Bumper_Status != Bumper_Status_Last) {
	#endif // -(LOOP_OPTIMIZE)-
     if ((Bumper_Status == 0) && (Skip_Message == 0)) {
       tft.setCursor(180,100); 
       tft.setTextColor(BLACK, BLACK);     
       tft.print("BUMP");
       }
     if ((Bumper_Status == 1)  && (Skip_Message == 0)) {
       tft.setCursor(180,100); 
       tft.setTextColor(YELLOW, BLACK); 
       tft.print("BUMP");
       Skip_Message = 1;
       }
	#if defined(LOOP_OPTIMIZE)
		 Bumper_Status_Last = Bumper_Status;
		 }
	#endif // -(LOOP_OPTIMIZE)-
   }

   if (Robot_Type == 2) {
     if ((Drill_Status == 0) && (Skip_Message == 0)) {
       tft.setTextSize(7);
       tft.setCursor(180,100); 
       tft.setTextColor(BLACK, BLACK);     
       tft.print("RETRACT");
       tft.setCursor(180,100); 
       tft.setTextColor(BLACK, BLACK);     
       tft.print("DRILL");
       }
     if ((Drill_Status == 1)  && (Skip_Message == 0)) {
       tft.setTextSize(7);
       tft.setCursor(180,100); 
       tft.setTextColor(YELLOW, BLACK); 
       tft.print("DRILL");
       Skip_Message = 1;
       }
     if ((Drill_Status == 2)  && (Skip_Message == 0)) {
       tft.setTextSize(7);
       tft.setTextColor(BLACK, BLACK);     
       tft.setCursor(180,100); 
       tft.print("DRILL");
       tft.setCursor(180,100); 
       tft.setTextColor(YELLOW, BLACK); 
       tft.print("RETRACT");
       Skip_Message = 1;
       }
   }
   
#if defined(LOOP_OPTIMIZE)
	 if (Tilt_Angle_Sensed != Tilt_Angle_Sensed_Last) {
#endif // -(LOOP_OPTIMIZE)-
     if ((Tilt_Angle_Sensed == 1) && (Skip_Message == 0)) {
       tft.setTextSize(8);
       tft.setCursor(180,100); 
       tft.setTextColor(BLACK, BLACK);     
       tft.print("TILT");
       }
     if ((Tilt_Angle_Sensed == 0)  && (Skip_Message == 0)) {
       tft.setTextSize(8);
       tft.setCursor(180,100); 
       tft.setTextColor(YELLOW, BLACK); 
       tft.print("TILT");
       Skip_Message = 1;
       }
#if defined(LOOP_OPTIMIZE)
	 Tilt_Angle_Sensed_Last = Tilt_Angle_Sensed;
	 }
#endif // -(LOOP_OPTIMIZE)-

     if (GPS_Enabled == 1) {
         if ((GPS_Lock_OK_TX == 1)  && (Skip_Message == 0)) {
           tft.setTextSize(8);
           tft.setCursor(180,100); 
           tft.setTextColor(BLACK, BLACK); 
           tft.print("FIX");
           Skip_Message = 1;
           }
         if ((GPS_Lock_OK_TX == 0)  && (Skip_Message == 0)) {
           tft.setTextSize(8);
           tft.setCursor(180,100); 
           tft.setTextColor(YELLOW, BLACK); 
           tft.print("FIX");
           Skip_Message = 1;
           }
         if ((GPS_In_Out_TX == 1)  && (Skip_Message == 0)) {
           tft.setTextSize(8);
           tft.setCursor(160,100); 
           tft.setTextColor(BLACK, BLACK); 
           tft.print("GPS");
           Skip_Message = 1;
           }
         if ((GPS_In_Out_TX == 0)  && (Skip_Message == 0)) {
           tft.setTextSize(8);
           tft.setCursor(160,100); 
           tft.setTextColor(YELLOW, BLACK); 
           tft.print("GPS");
           Skip_Message = 1;
           }

     }

#if defined(LOOP_OPTIMIZE)
  if (Wheel_Blocked_Status != Wheel_Blocked_Status_Last) {
     if ((Wheel_Blocked_Status == 0) && (Skip_Message == 0)) {
       tft.setTextSize(6);
       tft.setTextColor(BLACK, BLACK);
       tft.setCursor(180,80);
       tft.print("WHEELS");
       tft.setCursor(180,140);
	   tft.print("BLOCKED");
       }
     if ((Wheel_Blocked_Status == 1)  && (Skip_Message == 0)) {
       tft.setTextSize(6);
       tft.setTextColor(YELLOW, BLACK);
       tft.setCursor(180,80);
	   tft.print("WHEELS");
	   tft.setCursor(180,140);
	   tft.print("BLOCKED");
       Skip_Message = 1;
       }
     Wheel_Blocked_Status_Last = Wheel_Blocked_Status;
  }
#endif // -(LOOP_OPTIMIZE)-



    int left_arrow = 180;
    int right_arrow = 380;
    int y_level = 100;
       
#if defined(LOOP_OPTIMIZE)
   if (Compass_Steering_Status != Compass_Steering_Status_Last) {
#endif // -(LOOP_OPTIMIZE)-
     if ((Compass_Steering_Status == 0)  && (Skip_Message == 0)) {
       tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour     
       tft.setCursor(left_arrow,y_level);   
       tft.print("<");
       tft.setCursor(right_arrow, y_level); 
       tft.print(">");
       }
     if ((Compass_Steering_Status == 1)  && (Skip_Message == 0)){
       tft.setTextColor(YELLOW, BLACK); 
       tft.setCursor(left_arrow, y_level); 
       tft.print("<");
       tft.setCursor(right_arrow, y_level); 
       tft.print(">");

       Skip_Message = 1;
       }
     if ((Compass_Steering_Status == 2)  && (Skip_Message == 0)){
       tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour     
       tft.setCursor(left_arrow,y_level);   
       tft.print("<");
       //tft.setCursor(right_arrow, y_level);
       //tft.print(">");
       
       tft.setCursor(right_arrow, y_level); 
       tft.setTextColor(YELLOW, BLACK); 
       tft.print(">");
       Skip_Message = 1;
       }
     if ((Compass_Steering_Status == 3)  && (Skip_Message == 0)){
       tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour     
       //tft.setCursor(left_arrow,y_level);
       //tft.print("<");
       tft.setCursor(right_arrow, y_level); 
       tft.print(">");
       
       tft.setCursor(left_arrow, y_level); 
       tft.setTextColor(YELLOW, BLACK); 
       tft.print("<");
       Skip_Message = 1;
       }
	#if defined(LOOP_OPTIMIZE)
	   Compass_Steering_Status_Last = Compass_Steering_Status;
   	   } // -(LOOP_OPTIMIZE)-
	#endif
}


void Print_Error_Messages_Docked() {

#if defined(LOOP_OPTIMIZE)
   if ((Mower_Error_Value_Last != Mower_Error_Value) || refreshTFT) {
#endif // -(LOOP_OPTIMIZE)-
  // Mower_Error 1 = No Wire Detected.
  if (Mower_Error_Value == 1) {
       // Draw Red Circle with !
       tft.fillCircle(300, 58, 16, RED);           // X, Y, Radius
       tft.fillRect(298, 45, 4, 15 , WHITE);       // X, Y, Width, Height
       tft.fillRect(298, 64, 4, 5 , WHITE);        // X, Y, Width, Height 
       
       tft.setTextSize(3); 
       tft.setCursor(330,48); 
       tft.setTextColor(YELLOW, BLACK); 
       tft.print("WIRE OFF");
       }
  
  // Erases over the Red circle and text with black versions of the same thing.
  if (Mower_Error_Value != 1) {
       tft.fillCircle(300, 58, 16, BLACK);        // X, Y, Radius
       tft.setTextSize(3); 
       tft.setCursor(330,48); 
       tft.setTextColor(BLACK, BLACK); 
       tft.print("WIRE OFF");
       }
  }
#if defined(LOOP_OPTIMIZE)
   Mower_Error_Value_Last = Mower_Error_Value;
   }
#endif // -(LOOP_OPTIMIZE)-


void Print_Mower_Status() {
	#if defined(LOOP_OPTIMIZE)
       if ((Robot_Status_Value_Last != Robot_Status_Value) || refreshTFT) {
	#endif
       tft.setTextSize(2); 
       tft.setCursor(30,295); 
       tft.setTextColor(GREEN, BLACK); 
       if (Robot_Status_Value == 1) tft.print("Docked");
       if (Robot_Status_Value == 2) tft.print("Parked");
	#if defined(LOOP_OPTIMIZE)
	   Robot_Status_Value_Last = Robot_Status_Value;
       }
    #endif // -(LOOP_OPTIMIZE)-

	#if defined(LOOP_OPTIMIZE)
       if ((Charging != Charging_Last) || refreshTFT) {
	#endif // -(LOOP_OPTIMIZE)-
       if (Charging == 4) {
           tft.setTextSize(2); 
           tft.setCursor(100,295); 
           tft.setTextColor(GREEN, BLACK); 
           tft.print("   - Charging");
           }
       if ((Charging == 0) || (Charging != 4)) {
           tft.setTextSize(2); 
           tft.setCursor(100,295); 
           tft.setTextColor(BLACK, BLACK); 
           tft.print("   - Charging");
           }
	#if defined(LOOP_OPTIMIZE)
       Charging_Last = Charging;
       }
	#endif // -(LOOP_OPTIMIZE)-

	#if defined(LOOP_OPTIMIZE)
	   if ((GPS_Enabled != GPS_Enabled_Last) || refreshTFT) {
	#endif // -(LOOP_OPTIMIZE)-
       if (GPS_Enabled == 0) {
           tft.setTextSize(2); 
           tft.setCursor(170,50); 
           tft.setTextColor(BLACK, BLACK); 
           tft.print("GPS:");
           }    
       if (GPS_Enabled == 1) {
           tft.setTextSize(2); 
           tft.setCursor(170,50); 
           tft.setTextColor(GREEN, BLACK); 
           tft.print("GPS:");
           }
	#if defined(LOOP_OPTIMIZE)
       GPS_Enabled_Last = GPS_Enabled;
	   }
	#endif // -(LOOP_OPTIMIZE)-
       if (GPS_Enabled == 1) {
             if (GPS_Lock_OK_TX == 0) {
                 tft.print("    ");
                 }    
             if (GPS_Lock_OK_TX == 5) {
                 tft.print("RTK");
                 }     
             if (GPS_Lock_OK_TX == 2) {
                 tft.print("   ");
                 }  
             }
       }
       

void Calculate_TFT_Time() {
/*
  time = millis();
  int Seconds_Passed = (time / 1000 ) - (60 * Minutes_Passed);
  if (Seconds_Passed > 59) {
    Minutes_Passed = Minutes_Passed + 1;
    Time_Minute = Time_Minute + 1;
    if (Time_Minute > 59) {
      Time_Minute = 0;
      Time_Hour = Time_Hour + 1;
      if (Time_Hour > 23) {
       Time_Hour = 0; 
       }    
    }
  }*/
	/*
  Serial.print(F("|Time:"));
  Serial.print(Time_Hour);
  Serial.print(F(":"));
  if (Time_Minute < 10) Serial.print("0");
  Serial.print(Time_Minute);   
  Serial.print(":");
  //if (Seconds_Passed < 10) Serial.print("0");
  //Serial.println(Seconds_Passed); //prints time since program started
  if (Time_Second < 10) Serial.print("0");
  Serial.println(Time_Second); //prints time since program started
  */
  Serial.print(F("|"));
  PrintTimeToSerial(0, 0, 0, 0, Time_Hour, Time_Minute, Time_Second, 0, 1);
  }
