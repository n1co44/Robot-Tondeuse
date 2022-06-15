
// Menu GPS
//*********************************



void Print_GPS_Menu() {

    tft.fillScreen(BLACK);
    //if (Draw_Pictures == 1)   bmpDraw("Compass.bmp", 300, 120);      //Draw the mower picture
    delay(100);


    // Framework for the buttons - setting the start position of the Quick start button wil automatically then space the other buttons

    Pos_X1 = 100;
    Pos_Y1 = 80;
    int Menu_Btn_Space = 100;          // Space between the adjacent buttons
    int Button_W = 160;                // width of the button
    int Button_H = 60;                // height of the button
    int Button_Spacing = 5;

    int Menu_Spacing = 10;            // Distance between the Menu Items (bottom of the last button to the label of the next item)
    int Txt_Size_Main_Menu = 2;
    int Column_Spacing = 200;
    int Offset_Btn = 25;



    // Main Menu Title
    tft.setTextSize(Txt_Size_Main_Menu);
    tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
    tft.setCursor(20, 10);            // Text Coordinates X, Y
    tft.print(F("GPS Setup Menu"));



    //GPS ON OFF

    int Button_X = Pos_X1;
    int Button_Y = Pos_Y1;

    if (GPS_Enabled == 1) OPTION_A_BTN.initButton(&tft, Pos_X1, Pos_Y1, Button_W, Button_H, WHITE, GREEN, BLACK, "GPS ON", 2);
    if (GPS_Enabled == 0) OPTION_A_BTN.initButton(&tft, Pos_X1, Pos_Y1, Button_W, Button_H, WHITE, RED, WHITE, "GPS OFF", 2);

    OPTION_A_BTN.drawButton(false);

    //ReP AL GPS Setup

    Pos_X2 = Pos_X1;
    Pos_Y2 = Pos_Y1 + (Button_H + Menu_Spacing);


    if (GPS_Type == 1) {
      OPTION_B_BTN.initButton(&tft, Pos_X2, Pos_Y2, Button_W, Button_H, RED, GREEN, BLACK, "ReP SETUP", 2);
      OPTION_B_BTN.drawButton(false);
      }



    //GPS Type Setting
    //------------------------------------------------------------

    Pos_X3 = 30;
    Pos_Y3 = Pos_Y2 + (Button_H + Menu_Spacing);

    tft.setTextSize(Txt_Size_Main_Menu);
    tft.setTextColor(YELLOW, BLACK);      //Text Colour/ Background Colour
    tft.setCursor(Pos_X3, Pos_Y3);            // Text Coordinates X, Y
    tft.print(F("GPS Setup Type"));

    Pos_X4 = Pos_X1;
    Pos_Y4 = Pos_Y3 + Offset_Btn + (0.5 * Button_H);



    if (GPS_Type == 1) OPTION_E_BTN.initButton(&tft, Pos_X4, Pos_Y4, Button_W, Button_H, WHITE, RED, WHITE, "ReP_AL", 2);
    if (GPS_Type == 2) OPTION_E_BTN.initButton(&tft, Pos_X4, Pos_Y4, Button_W, Button_H, WHITE, YELLOW, BLACK, "PIXHAWK", 2);
    if (GPS_Type == 3) OPTION_E_BTN.initButton(&tft, Pos_X4, Pos_Y4, Button_W, Button_H, WHITE, BLUE, WHITE, "Spare", 2);

    OPTION_E_BTN.drawButton(false);



// Done_GPS Button

    Done_GPS_btn.initButton(&tft, 425, 278, 80, 40, WHITE, CYAN, BLACK, "Save", 2);
    Done_GPS_btn.drawButton(false);

}


void React_to_Button_Press_GPS() {


    // Action if Compass ONOFF is pressed
    if (OPTION_A_BTN.justPressed()) {

        bool Changed = 0;
        int Button_W = 160;
        int Button_H = 60;
        int Menu_Spacing = 20;
        int Column_Spacing = 200;

        int Button_X = Pos_X1;
        int Button_Y = Pos_Y1;

        if ((GPS_Enabled == 1) && (Changed == 0))  {
          GPS_Enabled  = 0;
          Changed = 1;
          OPTION_A_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, WHITE, RED, WHITE, "GPS OFF", 2);
          OPTION_A_BTN.drawButton(false);
          }

        if ((GPS_Enabled  == 0) && (Changed == 0)) {
          GPS_Enabled  = 1;
          Changed = 1;
          OPTION_A_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, BLACK, GREEN, BLACK, "GPS ON", 2);
          OPTION_A_BTN.drawButton(false);
          }

    }


    if (OPTION_B_BTN.justPressed()) {
          Menu_Complete_GPS = false;
          tft.fillScreen(BLACK);
          Serial.println(F("GPS Screen Selected"));
          Menu_Active = 15;
          Send_Menu_Selected_To_GPS_NodeMCU();         // Tell the Mower MEGA which menu on the TFT is selected
          Serial.println("RX GPS Values");
          delay(100);
          Serial.println("");
          Receive_GPS_Settings_Data();
          Print_GPS_Menu_Settings();

          // Sense for the settings buttons until the saved button is pressed.
          while (Menu_Complete_GPS == false) {
            Sense_Button_Press_GPS_Settings();
            React_to_Button_Press_GPS_Settings();
            }
    }



 // If GPS Mode Button is pressed
 if (OPTION_E_BTN.justPressed() ) {

        int Button_W = 160;                // width of the button
        int Button_H = 60;                // height of the button
        bool Changed = 0;
        if (GPS_Type == 0) GPS_Type = 1;

        if (( GPS_Type == 3) && (Changed ==0 )) {
          GPS_Type = 1;
          Changed = 1;
          OPTION_E_BTN.initButton(&tft, Pos_X4, Pos_Y4, Button_W, Button_H, WHITE, RED, WHITE, "ReP_AL", 2);
          OPTION_E_BTN.drawButton(false);
          Print_GPS_Menu();
          }

        if (( GPS_Type == 1) && (Changed ==0 ))  {
          GPS_Type = 2;
          Changed = 1;
          OPTION_E_BTN.initButton(&tft, Pos_X4, Pos_Y4, Button_W, Button_H, WHITE, YELLOW, BLACK, "PIXHAWK", 2);
          OPTION_E_BTN.drawButton(false);
          Print_GPS_Menu();
          }


        if (( GPS_Type == 2) && (Changed ==0 )) {
          GPS_Type = 3;
          Changed = 1;
          OPTION_E_BTN.initButton(&tft, Pos_X4, Pos_Y4, Button_W, Button_H, WHITE, BLUE, WHITE, "SPARE", 2);
          OPTION_E_BTN.drawButton(false);
          }

 delay(200);
 }



 // Action if Done is pressed
 if (Done_GPS_btn.justPressed()) {
         Menu_Complete_GPS = true;
         Menu_Active = 927;
         Send_Menu_Selected_To_Mower_MEGA();
         Transmit_GPS_Menu_Values();
         tft.fillScreen(BLACK);
         Print_Navigation_Menu();
         delay(200);
         }

}




void Sense_Button_Press_GPS() {
    down = Touch_getXY();
    OPTION_A_BTN.press            (down && OPTION_A_BTN.contains(pixel_x, pixel_y));
    OPTION_B_BTN.press            (down && OPTION_B_BTN.contains(pixel_x, pixel_y));
    OPTION_E_BTN.press            (down && OPTION_E_BTN.contains(pixel_x, pixel_y));
    Done_GPS_btn.press            (down && Done_GPS_btn.contains(pixel_x, pixel_y));



    if (OPTION_A_BTN.justReleased())         OPTION_A_BTN.drawButton();
    if (OPTION_B_BTN.justReleased())         OPTION_B_BTN.drawButton();
    if (OPTION_E_BTN.justReleased())         OPTION_E_BTN.drawButton();
    if (Done_GPS_btn.justReleased())         Done_GPS_btn.drawButton();

}
