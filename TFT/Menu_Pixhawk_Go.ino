
// PIXHAWK GO
//*********************************

void Print_PIXHAWK_Go_Menu() {
    tft.fillScreen(BLACK);
      // Framework for the buttons - setting the start position of the Quick start button wil automatically then space the other buttons

    int Start_X = 90;
    int Start_Y = 80;
    int Menu_Btn_Space = 100;          // Space between the adjacent buttons
    int Button_W = 130;                // width of the button
    int Button_H = 60;                // height of the button

    int Menu_Spacing = 20;            // Distance between the Menu Items (bottom of the last button to the label of the next item)
    int Txt_Size_Main_Menu = 2;
    int Column_Spacing = 160;



    // Main Menu Title
    tft.setTextSize(Txt_Size_Main_Menu);
    tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
    tft.setCursor(20, 10);            // Text Coordinates X, Y
    tft.print(F("PIXHAWK Control Menu"));



    //Pixhawk Options Menu
    //------------------------------------------------------------


    int Button_X = Start_X;
    int Button_Y = Start_Y;

    OPTION_A_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, YELLOW, YELLOW, BLACK, "ARM >", 2);
    OPTION_A_BTN.drawButton(false);

    //Sensors Options

    Button_X = Start_X;
    Button_Y = Button_Y + (Button_H + Menu_Spacing);

    OPTION_B_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, WHITE, WHITE, BLACK, "DIS-ARM >", 2);
    OPTION_B_BTN.drawButton(false);

    //Motion Options

    Button_X = Start_X;
    Button_Y = Button_Y + (Button_H + Menu_Spacing);

    OPTION_C_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, WHITE, RED, WHITE, "Guided >", 2);
    OPTION_C_BTN.drawButton(false);

    //Tracking Options

    Button_X = Start_X + (Button_W + Column_Spacing) ;
    Button_Y = Start_Y;

    OPTION_D_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, WHITE, MAGENTA, WHITE, "Auto >", 2);
    OPTION_D_BTN.drawButton(false);

    //Navigation Options

    Button_X = Button_X;
    Button_Y = Start_Y + (Button_H + Menu_Spacing);

    OPTION_E_BTN.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, BLUE, GREY, BLACK, "Acro >", 2);
    OPTION_E_BTN.drawButton(false);

    //More Options

    Button_X = Button_X;
    Button_Y = Button_Y + (Button_H + Menu_Spacing);

    Next_btn.initButton(&tft, Button_X, Button_Y, Button_W, Button_H, BLUE, BLUE, WHITE, "Next >", 2);
    Next_btn.drawButton(false);

// Done Button

    DONE_BTN.initButton(&tft, 230, 278, 80, 40, WHITE, CYAN, BLACK, "EXIT", 2);
    DONE_BTN.drawButton(false);

}


void React_to_Button_Press_PIXHAWK_Go() {

int Text1_Start_X = 200;
int Text1_Start_Y = 100;
int Text2_Start_X = 200;
int Text2_Start_Y = Text1_Start_Y + 30;

int Txt_Size_Main_Menu = 2;

    // ARM PIXHAWK
    if (OPTION_A_BTN.justPressed()) {
         Menu_Active = 75;
         Send_Menu_Selected_To_Mower_MEGA_No_RX();
         PIXHAWK_Armed = 1;

         tft.setTextSize(Txt_Size_Main_Menu);
         tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour
         tft.setCursor(Text1_Start_X, Text1_Start_Y);            // Text Coordinates X, Y
         tft.print(F("DIS-ARMED"));
         tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
         tft.setCursor(Text1_Start_X, Text1_Start_Y);            // Text Coordinates X, Y
         tft.print(F("ARMED"));
         }


    // DISARM
    if (OPTION_B_BTN.justPressed()) {
         Menu_Active = 74;
         Send_Menu_Selected_To_Mower_MEGA_No_RX();
         PIXHAWK_Armed = 0;

         tft.setTextSize(Txt_Size_Main_Menu);
         tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour
         tft.setCursor(Text1_Start_X, Text1_Start_Y);            // Text Coordinates X, Y
         tft.print(F("ARMED"));
          tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
         tft.setCursor(Text1_Start_X, Text1_Start_Y);            // Text Coordinates X, Y
         tft.print(F("DIS-ARMED"));
         }


    // Guided
    if (OPTION_C_BTN.justPressed()) {
         Menu_Active = 76;
         Send_Menu_Selected_To_Mower_MEGA_No_RX();

         tft.setTextSize(Txt_Size_Main_Menu);
         tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour
         tft.setCursor(Text2_Start_X, Text2_Start_Y);            // Text Coordinates X, Y
         tft.print(F("88888888"));
         tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
         tft.setCursor(Text2_Start_X, Text2_Start_Y);            // Text Coordinates X, Y
         tft.print(F("GUIDED"));
         }


    // Auto
    if (OPTION_D_BTN.justPressed()) {
         Menu_Active = 77;
         Send_Menu_Selected_To_Mower_MEGA_No_RX();

         tft.setTextSize(Txt_Size_Main_Menu);
         tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour
         tft.setCursor(Text2_Start_X, Text2_Start_Y);            // Text Coordinates X, Y
         tft.print(F("88888888"));
         tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
         tft.setCursor(Text2_Start_X, Text2_Start_Y);            // Text Coordinates X, Y
         tft.print(F("Auto"));
         }


    // Acro
    if (OPTION_E_BTN.justPressed()) {
         Menu_Active = 78;
         Send_Menu_Selected_To_Mower_MEGA_No_RX();

         tft.setTextSize(Txt_Size_Main_Menu);
         tft.setTextColor(BLACK, BLACK);      //Text Colour/ Background Colour
         tft.setCursor(Text2_Start_X, Text2_Start_Y);            // Text Coordinates X, Y
         tft.print(F("88888888"));
         tft.setTextColor(GREEN, BLACK);      //Text Colour/ Background Colour
         tft.setCursor(Text2_Start_X, Text2_Start_Y);            // Text Coordinates X, Y
         tft.print(F("Acro"));

         }

    // Action if More is pressed
    if (Next_btn.justPressed()) {
          Menu_Complete_Settings_2 = false;
          tft.fillScreen(BLACK);
          Serial.println(F("TFT Settings 2/2 Screen Selected"));
          Print_Settings_2_Menu();

          // Sense for the settings buttons until the saved button is pressed.
          while (Menu_Complete_Settings_2 == false) {
            Sense_Button_Press_Settings_2();
            React_to_Button_Press_Settings_2();
            }
    }


 // Action if Done is pressed
 if (DONE_BTN.justPressed()) {
         Menu_Complete_Settings = true;
         tft.fillScreen(BLACK);

         Menu_Active = 79;
         Send_Menu_Selected_To_Mower_MEGA_No_RX();

          Serial.println(F("Main Screen Selected"));
          Menu_Active = 1;
          Send_Menu_Selected_To_Mower_MEGA();         // Tell the Mower MEGA which menu on the TFT is selected
          Serial.print(F("Mower Status ="));
          Serial.println(Robot_Status_Value);
          if ((Robot_Status_Value == 0) ||(Robot_Status_Value == 1) || (Robot_Status_Value == 2)) {              // 1 = Docked  2 = Parked
            tft.fillScreen(BLACK);


            if (Draw_Pictures == 1) bmpDraw("mower1.bmp", 150, 90);      //Draw the mower picture
            delay(100);
            Print_Main_Menu_Graphic();
            Check_For_Active_Alarms();
            }
         if (Robot_Status_Value == 5) Print_Stop_Menu_Graphic();  // 2 = Parked
        }
}



void Sense_Button_Press_PIXHAWK_Go() {
    down = Touch_getXY();
    OPTION_A_BTN.press          (down && OPTION_A_BTN.contains(pixel_x, pixel_y));
    OPTION_B_BTN.press       (down && OPTION_B_BTN.contains(pixel_x, pixel_y));   // Sensors
    OPTION_C_BTN.press        (down && OPTION_C_BTN.contains(pixel_x, pixel_y));    // Motion
    OPTION_D_BTN.press      (down && OPTION_D_BTN.contains(pixel_x, pixel_y));    // Traking
    OPTION_E_BTN.press    (down && OPTION_E_BTN.contains(pixel_x, pixel_y));
    Next_btn.press          (down && Next_btn.contains(pixel_x, pixel_y));
    DONE_BTN.press          (down && DONE_BTN.contains(pixel_x, pixel_y));

    if (OPTION_A_BTN.justReleased())        OPTION_A_BTN.drawButton();
    if (OPTION_B_BTN.justReleased())     OPTION_B_BTN.drawButton();
    if (OPTION_C_BTN.justReleased())      OPTION_C_BTN.drawButton();
    if (OPTION_D_BTN.justReleased())    OPTION_D_BTN.drawButton();
    if (OPTION_E_BTN.justReleased())  OPTION_E_BTN.drawButton();
    if (Next_btn.justReleased())        Next_btn.drawButton();
    if (DONE_BTN.justReleased())        DONE_BTN.drawButton();

}
