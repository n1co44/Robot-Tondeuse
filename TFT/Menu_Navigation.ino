
// Menu Navigation
//*********************************



void Print_Navigation_Menu() {

    tft.fillScreen(BLACK);
    //if (Draw_Pictures == 1)   bmpDraw("Compass.bmp", 250, 150);      //Draw the mower picture
    delay(100); 

    
    // Framework for the buttons - setting the start position of the Quick start button wil automatically then space the other buttons

    Pos_X1 = 100;
    Pos_Y1 = 80;
    int Menu_Btn_Space = 100;          // Space between the adjacent buttons
    int Button_W = 160;                // width of the button
    int Button_H = 60;                // height of the button
    int Button_Spacing = 5;

    int Menu_Spacing = 15;            // Distance between the Menu Items (bottom of the last button to the label of the next item)
    int Txt_Size_Main_Menu = 2;
    int Column_Spacing = 200; 
    int Offset_Btn = 25;



    // Main Menu Title
    tft.setTextSize(Txt_Size_Main_Menu); 
    tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
    tft.setCursor(20, 10);            // Text Coordinates X, Y
    tft.print(F("Navigation / Guidance Menu"));  
    
    
    
    //Menu Navigation
    //------------------------------------------------------------
    
    // GPS Settings
    int Button_X = Pos_X1;
    int Button_Y = Pos_Y1;
   
    OPTION1_BTN.initButton(&tft, Pos_X1, Pos_Y1, Button_W, Button_H, YELLOW, YELLOW, BLACK, "GPS >", 2);
    OPTION1_BTN.drawButton(false);


    //Compass Settings
    
    Pos_X2 = Pos_X1;
    Pos_Y2 = Pos_Y1 + (Button_H + Menu_Spacing) + 15;    
    
    OPTION2_BTN.initButton(&tft, Pos_X2, Pos_Y2, Button_W, Button_H, YELLOW, BLUE, WHITE, "Compass >", 2);
    OPTION2_BTN.drawButton(false);



    //GYRO Settings
    
    Pos_X3 = Pos_X1;
    Pos_Y3 = Pos_Y2 + (Button_H + Menu_Spacing) + 15;    
    
    OPTION3_BTN.initButton(&tft, Pos_X3, Pos_Y3, Button_W, Button_H, YELLOW, WHITE, BLACK, "GYRO >", 2);
    OPTION3_BTN.drawButton(false);

// Done_Navigation Button

    DONE2_BTN.initButton(&tft, 425, 278, 80, 40, WHITE, CYAN, BLACK, "Back", 2);
    DONE2_BTN.drawButton(false);
  
}


void React_to_Button_Press_Navigation() {

    // Action if GPS is pressed
    if (OPTION1_BTN.justPressed()) {
          Menu_Complete_GPS = false;
          tft.fillScreen(BLACK);
          Serial.println(F("GPS Menu Selected"));
          Menu_Active = 32;
          Send_Menu_Selected_To_Mower_MEGA();         // Tell the Mower MEGA which menu on the TFT is selected
          delay(Receive_Values_Delay + 600);
          Receive_GPS_Data();        
          if ((GPS_Type != 1) && (GPS_Type != 2) && (GPS_Type != 3))  GPS_Type = 1;
          Print_GPS_Menu();
          
          // Sense for the settings buttons until the saved button is pressed.
          while (Menu_Complete_GPS == false) {
            Sense_Button_Press_GPS();
            React_to_Button_Press_GPS();
            }
    }


    // Action if Compass is pressed
    if (OPTION2_BTN.justPressed()) {
          Menu_Complete_Compass = false;
          tft.fillScreen(BLACK);
          Serial.println(F("Compass Screen Selected"));
          Menu_Active = 27;
          Send_Menu_Selected_To_Mower_MEGA();         // Tell the Mower MEGA which menu on the TFT is selected
          delay(Receive_Values_Delay + 900);
          Receive_Compass_Data(); 
          Print_Compass_Menu();
          
          // Sense for the settings buttons until the saved button is pressed.
          while (Menu_Complete_Compass == false) {
            Sense_Button_Press_Compass();
            React_to_Button_Press_Compass();
            }
    }

    // Action if GYRO is pressed
    if (OPTION3_BTN.justPressed()) {
          Menu_Complete_GYRO = false;
          tft.fillScreen(BLACK);
          Serial.println(F("GYRO Screen Selected"));
          Menu_Active = 28;
          Send_Menu_Selected_To_Mower_MEGA();         // Tell the Mower MEGA which menu on the TFT is selected
          Serial.println("GYRO Data");
          delay(Receive_Values_Delay + 600);
          Receive_GYRO_Data(); 
          Print_GYRO_Menu();
          
          // Sense for the settings buttons until the saved button is pressed.
          while (Menu_Complete_GYRO == false) {
            Sense_Button_Press_GYRO();
            React_to_Button_Press_GYRO();
            }
    }

    




 // Action if Done is pressed
 if (DONE2_BTN.justPressed()) {
         Menu_Complete_Navigation = true;
         Menu_Active = 99;
         Send_Menu_Selected_To_Mower_MEGA();   
         tft.fillScreen(BLACK);
         Print_Settings_Menu();
         delay(200);
         }
}
    




void Sense_Button_Press_Navigation() {
    down = Touch_getXY();
    OPTION1_BTN.press             (down && OPTION1_BTN.contains(pixel_x, pixel_y));   // GPS
    OPTION2_BTN.press             (down && OPTION2_BTN.contains(pixel_x, pixel_y));
    OPTION3_BTN.press             (down && OPTION3_BTN.contains(pixel_x, pixel_y));
    DONE2_BTN.press               (down && DONE2_BTN.contains(pixel_x, pixel_y));

    if (OPTION1_BTN.justReleased())       OPTION1_BTN.drawButton();
    if (OPTION2_BTN.justReleased())       OPTION2_BTN.drawButton();
    if (OPTION3_BTN.justReleased())       OPTION3_BTN.drawButton();
    if (DONE2_BTN.justReleased())         DONE2_BTN.drawButton();

}
