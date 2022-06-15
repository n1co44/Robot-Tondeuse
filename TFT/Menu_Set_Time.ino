void Print_Set_Time_Menu() {  

     // Framework for the buttons - setting the start position of the Quick start button wil automatically then space the other buttons
    tft.fillScreen(BLACK);
    int Label_Time_Spacing = 30;          // Space between the text and the -ve button
    int Label_Date_Spacing = 20;          // Space between the text and the -ve button
    int Button_W = 50;                // width of the button
    int Button_H = 40;                // height of the button
    int Button_Spacing = 5;           // Space between the -ve and +ve buttons
    int Time_Spacing = 150;            // Distance between the Hours and Minutes Number
    int Date_Spacing = 50;            // Distance between the Year, Month and Date Number
    Offset_Btn = 25;
    int Time_Button_Spacing = 100;
    int Date_Button_Spacing = 50;

    // Main Menu Title
    tft.setTextSize(2); 
    tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
    tft.setCursor(10, 10);            // Text Coordinates X, Y
    tft.print(F("Set Clock Menu"));  
    
    // Framework for the + - buttons - setting the start position of the + button wil automatically then space the - button

    // Top left position of the first menu item.    
    Pos_X1   = 60; //60
    Pos_Y1   = 40; //80

    
    // Size of the Time Label
    tft.setTextSize(2); 
    tft.setTextColor(YELLOW, BLACK);      //Text Colour/ Background Colour
    tft.setCursor(Pos_X1, Pos_Y1);            // Text Coordinates X, Y
    tft.print(F("Mower Clock Time"));  

    // Size of the Time Numbers
    tft.setTextSize(9); 
    tft.setTextColor(RED, BLACK);      //Text Colour/ Background Colour

    // Hours X 10 
    Pos_X1 = Pos_X1;
    Pos_Y1 = Pos_Y1 + Label_Time_Spacing;  
    tft.setCursor(Pos_X1, Pos_Y1);            // Text Coordinates X, Y
        if (Time_Hour > 9) tft.print(Time_Hour);
        if (Time_Hour < 10) {
          tft.print("0");
          tft.print(Time_Hour);
        }

    Pos_X3 = Pos_X1 + 100;
    Pos_Y3 = Pos_Y1;  
    tft.setCursor(Pos_X3, Pos_Y3);            // Text Coordinates X, Y
    tft.print(":");     


    // Minutes X 10 
    Pos_X2 = Pos_X1 + Time_Spacing;
    Pos_Y2 = Pos_Y1;  
    tft.setCursor(Pos_X2, Pos_Y2);            // Text Coordinates X, Y
        if (Time_Minute > 9) tft.print(Time_Minute);
        if (Time_Minute < 10) {
          tft.print("0");
          tft.print(Time_Minute);
        }
    
    // + - Hour Value
    int Button_X = Pos_X1 + (0.5 * Button_W);
    int Button_Y = Pos_Y1 + Time_Button_Spacing;
 
    UP1_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "+", 2);
    DOWN1_BTN.initButton(&tft, (Button_X + (Button_W + Button_Spacing)), Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "-", 2);

    UP1_BTN.drawButton(false);
    DOWN1_BTN.drawButton(false);

    // + - Minute Value
    Button_X = Pos_X2 + (0.5 * Button_W);
    Button_Y = Pos_Y2 + Time_Button_Spacing;
 
    UP2_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "+", 2);
    DOWN2_BTN.initButton(&tft, (Button_X + (Button_W + Button_Spacing)), Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "-", 2);

    UP2_BTN.drawButton(false);
    DOWN2_BTN.drawButton(false);


    // *********************************************************
    // Size of the Date Label
    Pos_Y4 = 200;
    Pos_X4 = Pos_X1-Pos_X1;
    tft.setTextSize(2);
    tft.setTextColor(YELLOW, BLACK);      //Text Colour/ Background Colour
    tft.setCursor(Pos_X4, Pos_Y4);            // Text Coordinates X, Y
    tft.print(F("Mower Date"));

    // Size of the Time Numbers
    tft.setTextSize(4);
    tft.setTextColor(RED, BLACK);      //Text Colour/ Background Colour


    // Year X 10
    Pos_X4 = Pos_X4;
    Pos_Y4 = Pos_Y4 + Label_Date_Spacing;
    tft.setCursor(Pos_X4, Pos_Y4);            // Text Coordinates X, Y
    if      (Time_Year <  10)                      tft.print("000");
    else if (Time_Year >= 10  && Time_Year < 100)  tft.print("00");
	else if (Time_Year >= 100 && Time_Year < 1000) tft.print("0");
    tft.print(Time_Year);

    Pos_X3 = Pos_X4 + Date_Spacing * 2;
    Pos_Y3 = Pos_Y4;
    tft.setCursor(Pos_X3, Pos_Y3);            // Text Coordinates X, Y
    tft.print("-");

    // Month X 10
    Pos_X5 = Pos_X4 + Date_Spacing * 2.5;
    Pos_Y5 = Pos_Y4;
    tft.setCursor(Pos_X5, Pos_Y5);            // Text Coordinates X, Y
        if (Time_Month > 9) tft.print(Time_Month);
        if (Time_Month < 10) {
          tft.print("0");
          tft.print(Time_Month);
        }

    Pos_X3 = Pos_X5 + Date_Spacing;
    Pos_Y3 = Pos_Y4;
    tft.setCursor(Pos_X3, Pos_Y3);            // Text Coordinates X, Y
    tft.print("-");

    // Date X 10
    Pos_X6 = Pos_X5 + Date_Spacing * 1.5;
    Pos_Y6 = Pos_Y4;
    tft.setCursor(Pos_X6, Pos_Y6);            // Text Coordinates X, Y
        if (Time_Date > 9) tft.print(Time_Date);
        if (Time_Date < 10) {
          tft.print("0");
          tft.print(Time_Date);
        }

	// Day
	Pos_X7 = Pos_X6 + Date_Spacing * 4;
	Pos_Y7 = Pos_Y4;
	tft.setCursor(Pos_X7, Pos_Y7);            // Text Coordinates X, Y
	char buf[3];
    snprintf(buf, sizeof(buf), "%s", dayAsString(Time_Day).c_str());
    //tft.print(Time_Day);
    tft.print(buf);


    // + - Year Value
    Button_X = Pos_X4 + (0.5 * Button_W);
    Button_Y = Pos_Y4 + Date_Button_Spacing;

    UP3_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "+", 2);
    DOWN3_BTN.initButton(&tft, (Button_X + (Button_W + Button_Spacing)), Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "-", 2);

    UP3_BTN.drawButton(false);
    DOWN3_BTN.drawButton(false);

    // + - Month Value
    Button_X = Pos_X5 + (0.5 * Button_W);
    Button_Y = Pos_Y5 + Date_Button_Spacing;

    UP4_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "+", 2);
    DOWN4_BTN.initButton(&tft, (Button_X + (Button_W + Button_Spacing)), Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "-", 2);

    UP4_BTN.drawButton(false);
    DOWN4_BTN.drawButton(false);

    // + - Date Value
    Button_X = Pos_X6 + (1.5 * Button_W);
    Button_Y = Pos_Y6 + Date_Button_Spacing;

    UP5_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "+", 2);
    DOWN5_BTN.initButton(&tft, (Button_X + (Button_W + Button_Spacing)), Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "-", 2);

    UP5_BTN.drawButton(false);
    DOWN5_BTN.drawButton(false);

    // + - Day Value
    Button_X = Pos_X7;
    Button_Y = Pos_Y7 + Date_Button_Spacing;

    UP6_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "+", 2);
    DOWN6_BTN.initButton(&tft, (Button_X + (Button_W + Button_Spacing)), Button_Y, Button_W, Button_H, WHITE, CYAN, BLACK, "-", 2);

    UP6_BTN.drawButton(false);
    DOWN6_BTN.drawButton(false);
    // *********************************************************

// Done Button

    //SAVE4_BTN.initButton(&tft, 410, 275, 80, 40, WHITE, CYAN, BLACK, "Save", 2);
    SAVE4_BTN.initButton(&tft, 410, 60, 80, 40, WHITE, CYAN, BLACK, "Save", 2);
    SAVE4_BTN.drawButton(false);


}



void React_to_Button_Set_Time() {

  //If the Button Time_Hour is pressed (up or down)
   if ((UP1_BTN.justPressed() )  || (DOWN1_BTN.justPressed())) {
        Value_All = Time_Hour;
        Label_X = Pos_X1;
        Label_Y = Pos_Y1;
    
    // Actions if UP is pressed
    if (UP1_BTN.justPressed()) {
        Clear_Old_Value_Set_Time(1, 9);
        UP1_BTN.drawButton(true);
        Value_All = Value_All + 1;
        if (Value_All > 23) Value_All = 0;
        Time_Hour = Value_All;
        Print_New_Value_Set_Time(1, 9);
        }


    // Action if down is pressed
    if (DOWN1_BTN.justPressed()) {
        Clear_Old_Value_Set_Time(1, 9);
        DOWN1_BTN.drawButton(true);
        Value_All = Value_All - 1;
        if (Value_All < 0) Value_All = 23;
        Time_Hour = Value_All;
        Print_New_Value_Set_Time(1, 9);
        }
    
    }

  //If the Time_Minute is pressed (up or down)
   if ((UP2_BTN.justPressed() )  || (DOWN2_BTN.justPressed())) {
        Value_All = Time_Minute;
        Label_X   = Pos_X2;
        Label_Y   = Pos_Y2;
    
    // Actions if UP is pressed
    if (UP2_BTN.justPressed()) {
        Clear_Old_Value_Set_Time(1, 9);
        UP2_BTN.drawButton(true);
        Value_All = Value_All + 1;
        if (Value_All > 59) Value_All = 0;
        Time_Minute = Value_All;
        Print_New_Value_Set_Time(1, 9);
        }


    // Action if down is pressed
    if (DOWN2_BTN.justPressed()) {
        Clear_Old_Value_Set_Time(1, 9);
        DOWN2_BTN.drawButton(true);
        Value_All = Value_All - 1;
        if (Value_All < 0) Value_All = 59;
        Time_Minute = Value_All;
        Print_New_Value_Set_Time(1, 9);
        }
    
    }


   //If the Time_Year is pressed (up or down)
    if ((UP3_BTN.justPressed() )  || (DOWN3_BTN.justPressed())) {
         Value_All = Time_Year;
         Label_X   = Pos_X4;
         Label_Y   = Pos_Y4;

     // Actions if UP is pressed
     if (UP3_BTN.justPressed()) {
         Clear_Old_Value_Set_Time(1, 4);
         UP3_BTN.drawButton(true);
         Value_All = Value_All + 1;
         if (Value_All > 2099 || Value_All < 2000) Value_All = 2000;
         Time_Year = Value_All;
         Print_New_Value_Set_Time(1, 4);
         }


     // Action if down is pressed
     if (DOWN3_BTN.justPressed()) {
         Clear_Old_Value_Set_Time(1, 4);
         DOWN3_BTN.drawButton(true);
         Value_All = Value_All - 1;
         if (Value_All < 2000) Value_All = 2099;
         Time_Year = Value_All;
         Print_New_Value_Set_Time(1, 4);
         }

     }


   //If the Time_Month is pressed (up or down)
    if ((UP4_BTN.justPressed() )  || (DOWN4_BTN.justPressed())) {
         Value_All = Time_Month;
         Label_X   = Pos_X5;
         Label_Y   = Pos_Y5;

     // Actions if UP is pressed
     if (UP4_BTN.justPressed()) {
         Clear_Old_Value_Set_Time(1, 4);
         UP4_BTN.drawButton(true);
         Value_All = Value_All + 1;
         if (Value_All > 12) Value_All = 0;
         Time_Month = Value_All;
         Print_New_Value_Set_Time(1, 4);
         }


     // Action if down is pressed
     if (DOWN4_BTN.justPressed()) {
         Clear_Old_Value_Set_Time(1, 4);
         DOWN4_BTN.drawButton(true);
         Value_All = Value_All - 1;
         if (Value_All < 0) Value_All = 12;
         Time_Month = Value_All;
         Print_New_Value_Set_Time(1, 4);
         }

     }


    //If the Time_Date is pressed (up or down)
     if ((UP5_BTN.justPressed() )  || (DOWN5_BTN.justPressed())) {
          Value_All = Time_Date;
          Label_X   = Pos_X6;
          Label_Y   = Pos_Y6;

      // Actions if UP is pressed
      if (UP5_BTN.justPressed()) {
          Clear_Old_Value_Set_Time(1, 4);
          UP5_BTN.drawButton(true);
          Value_All = Value_All + 1;
          if (Value_All > 31) Value_All = 0;
          Time_Date = Value_All;
          Print_New_Value_Set_Time(1, 4);
          }


      // Action if down is pressed
      if (DOWN5_BTN.justPressed()) {
          Clear_Old_Value_Set_Time(1, 4);
          DOWN5_BTN.drawButton(true);
          Value_All = Value_All - 1;
          if (Value_All < 0) Value_All = 31;
          Time_Date = Value_All;
          Print_New_Value_Set_Time(1, 4);
          }

      }


     //If the Time_Day is pressed (up or down)
	  if ((UP6_BTN.justPressed() )  || (DOWN6_BTN.justPressed())) {
		   Value_All = Time_Day;
		   Label_X   = Pos_X7;
		   Label_Y   = Pos_Y7;

	   // Actions if UP is pressed
	   if (UP6_BTN.justPressed()) {
		   Clear_Old_Value_Set_Time(2, 4);
		   UP6_BTN.drawButton(true);
		   Value_All = Value_All + 1;
		   if (Value_All > 7) Value_All = 1;
		   Time_Day = Value_All;
		   Print_New_Value_Set_Time(2, 4);
		   }


	   // Action if down is pressed
	   if (DOWN6_BTN.justPressed()) {
		   Clear_Old_Value_Set_Time(2, 4);
		   DOWN6_BTN.drawButton(true);
		   Value_All = Value_All - 1;
		   if (Value_All < 1) Value_All = 7;
		   Time_Day = Value_All;
		   Print_New_Value_Set_Time(2, 4);
		   }

	   }


 // Action if DateTime Save is pressed
 if (SAVE4_BTN.justPressed()) {
         Menu_Complete_Set_Time = true;
         tft.fillScreen(BLACK);
         Serial.println(F("DateTime Saved and TX"));
         Menu_Active = 923;
         Send_Menu_Selected_To_Mower_MEGA();
         Transmit_Save_Set_Time_Values();              
         Print_Time_Menu();
         }

}


void Clear_Old_Value_Set_Time(byte type, byte textSize) {
        // Draws over the previous Value in Black text to clear it.... !?
        tft.setTextSize(textSize);
        tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour
        tft.setCursor(Label_X, Label_Y);            // Text Coordinates X, Y
        if (type == 1) {
			if (Value_All > 9) tft.print(Value_All);
			if (Value_All < 10) {
			  tft.print("0");
			  tft.print(Value_All);
			}
        } else if (type == 2) {
        	char buf[3];
            snprintf(buf, sizeof(buf), "%s", dayAsString(Value_All).c_str());
            tft.print(buf);
        }
}


void Print_New_Value_Set_Time(byte type, byte textSize) {

        tft.setTextSize(textSize);
        tft.setTextColor(RED, BLACK);      //Text Colour/ Background Colour
        tft.setCursor(Label_X, Label_Y);            // Text Coordinates X, Y
        if (type == 1) {
			if (Value_All > 9) tft.print(Value_All);
			if (Value_All < 10) {
			  tft.print("0");
			  tft.print(Value_All);
			}
        } else if (type == 2) {
        	char buf[3];
            snprintf(buf, sizeof(buf), "%s", dayAsString(Value_All).c_str());
            tft.print(buf);
        }
}




void Sense_Button_Set_Time() {
    down = Touch_getXY();
    UP1_BTN.press             (down && UP1_BTN.contains(pixel_x, pixel_y));
    DOWN1_BTN.press           (down && DOWN1_BTN.contains(pixel_x, pixel_y));
    UP2_BTN.press             (down && UP2_BTN.contains(pixel_x, pixel_y));
    DOWN2_BTN.press           (down && DOWN2_BTN.contains(pixel_x, pixel_y));
    UP3_BTN.press             (down && UP3_BTN.contains(pixel_x, pixel_y));
    DOWN3_BTN.press           (down && DOWN3_BTN.contains(pixel_x, pixel_y));
    UP4_BTN.press             (down && UP4_BTN.contains(pixel_x, pixel_y));
    DOWN4_BTN.press           (down && DOWN4_BTN.contains(pixel_x, pixel_y));
    UP5_BTN.press             (down && UP5_BTN.contains(pixel_x, pixel_y));
    DOWN5_BTN.press           (down && DOWN5_BTN.contains(pixel_x, pixel_y));
    UP6_BTN.press             (down && UP6_BTN.contains(pixel_x, pixel_y));
    DOWN6_BTN.press           (down && DOWN6_BTN.contains(pixel_x, pixel_y));
    SAVE4_BTN.press     	  (down && SAVE4_BTN.contains(pixel_x, pixel_y));


    if (UP1_BTN.justReleased())             UP1_BTN.drawButton();
    if (DOWN1_BTN.justReleased())           DOWN1_BTN.drawButton();
    if (UP2_BTN.justReleased())             UP2_BTN.drawButton();  
    if (DOWN2_BTN.justReleased())           DOWN2_BTN.drawButton();
    if (UP3_BTN.justReleased())             UP3_BTN.drawButton();
    if (DOWN3_BTN.justReleased())           DOWN3_BTN.drawButton();
    if (UP4_BTN.justReleased())             UP4_BTN.drawButton();
    if (DOWN4_BTN.justReleased())           DOWN4_BTN.drawButton();
    if (UP5_BTN.justReleased())             UP5_BTN.drawButton();
    if (DOWN5_BTN.justReleased())           DOWN5_BTN.drawButton();
    if (UP6_BTN.justReleased())             UP6_BTN.drawButton();
    if (DOWN6_BTN.justReleased())           DOWN6_BTN.drawButton();
    if (SAVE4_BTN.justReleased())     		SAVE4_BTN.drawButton();
    }


// Print Date and Time on serial console
void PrintTimeToSerial(byte _type, int _year, byte _month, byte _date, byte _hour, byte _minute, byte _second, byte _dow, bool _endType)   {
	// _type 0: time
	// _type 1: date time
	// _type 2: date time DoW

	// _endType 0: Serial.print(F("|"));
	// _endType 1: Serial.println("");

	if (_type > 0) Serial.print(F("DateTime: "));
	else Serial.print(F("Time:"));

	if (_type > 0) {
		Serial.print(_year);
		Serial.print(F("-"));
		if (_month < 10) Serial.print(F("0"));
		Serial.print(_month);
		Serial.print(F("-"));
		if (_date < 10) Serial.print(F("0"));
		Serial.print(_date);
		Serial.print(F(" "));
	}
		if (_hour < 10) Serial.print(F("0"));
		Serial.print(_hour);
		Serial.print(F(":"));
		if (_minute < 10) Serial.print(F("0"));
		Serial.print(_minute);
		Serial.print(F(":"));
		if (_second < 10) Serial.print(F("0"));
		Serial.print(_second);

	if (_type == 2) {
		char buf[15];
		const String day = dayAsString(_dow);
		snprintf(buf, sizeof(buf), " %s", day.c_str());
		Serial.print(buf);
	}

	if (_type > 2) {
		Serial.print(F("bad _type on PrintTimeToSerial()"));
	}

	if (_endType) {
		Serial.println("");
	} else {
		Serial.print(F("|"));
	}
}
