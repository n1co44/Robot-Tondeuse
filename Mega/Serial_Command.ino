void Check_Serial_Input() {
  
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    int Command_Last = Command;
    Command = Serial.read();
    if (Command == 10) Command = Command_Last;

    // Print Comamnd to Serial Monitor
    if (Command != 0) {
        Serial.print(F(""));
        Serial.print(F(""));
        Serial.println(Command);
        }
  }

Execute_Serial_Command();
}


void Execute_Serial_Command() {
// Rotate 20 degrees CCW

if (Command == 104) {                   // letter h
    Command = 0;
    Serial.println(F("  "));
    Serial.println(F("  "));
    Serial.println(F("      ReP_AL Mower  HELP MENU"));
    Serial.println(F("  "));
    Serial.println(F("      Enter the following letter"));
    Serial.println(F("  ------------------------------------"));
    Serial.println(F("  a = "));           //97
    Serial.println(F("  b = "));       //98
    Serial.println(F("  c = Goto Charging Station")); //99
    Serial.println(F("  d = Set to Docked"));         //100                
    Serial.println(F("  e = Exit dock"));             //101
    Serial.println(F("  f = Set Mower Mode to PIXHAK/ReP_AL"));           //102
    Serial.println(F("  g = "));  //103
    Serial.println(F("  h = Help Menu"));             //104
    Serial.println(F("  i = Drill ON/OFF"));          //105
    Serial.println(F("  j"));
    Serial.println(F("  k = Test Drill Cycle"));      //107
    Serial.println(F("  l = Spikes Down"));           //108
    Serial.println(F("  m = Manuel Mode"));
    Serial.println(F("  n"));
    Serial.println(F("  o = Spikes UP"));             //111
    Serial.println(F("  p = Pause/Park Mower"));      //112
    Serial.println(F("  q = Quick Start Mower"));     //113
    Serial.println(F("  r = Rain Sensor ON/OFF"));    //114
    Serial.println(F("  s = "));      //115
    Serial.println(F("  t = "));           //116
    Serial.println(F("  u = "));     //117
    Serial.println(F("  v = Fake Voltage of 12.6V"));       //118
    Serial.println(F("  w = Fake Wire Signal ON/OFF"));		//119
    Serial.println(F("  x = Mission start Pixhawk"));       //120
    Serial.println(F("  y = Fake Wheel_Blocked_Count=4"));  //121
    Serial.println(F("  z = Fake All Volts, Wheel Amps "));	//122"));
    Serial.println(F("  "));
    Serial.println(F("  "));

        
    delay(7000);   
    }

if (Command == 96) {                   // letter c
    Command = 0;
    analogWrite(PWM_1, 255);
    }


if (Command == 99) {                   // letter c
    Command = 0;
    Manouver_Go_To_Charging_Station();
    }

if (Command == 100) {                   // letter d
    Command = 0;
    Mower_Docked = 1 ;
    Mower_Parked = 0 ;
    }

if (Command == 101) {                   // letter e
    Command = 0;
    Alarm_Start_Exit_Zone_2();
    }

if (Command == 102) {                   // letter f
    Command = 0;
    Serial.println("");
    Serial.println(F("Mower set to PIXHAWK Mode"));
    Serial.println("");
    Mower_Docked = 0;
    Mower_PIXHAWK = 1;
    }



if (Command == 105) {                   // letter i
    Command = 0;
    int Skip = 0;

    
    if (Drill_ON == 0) {
      Serial.println(F(""));
      Serial.println(F("Drill = ON"));
      Turn_On_Relay();
      delay(1000);
      Motor_Action_Spin_Drill();
      Drill_ON = 1;
      Skip = 1;
      }
    
    
    if ((Drill_ON == 1) && (Skip == 0)) {
      Serial.println(F(""));
      Serial.println(F("Drill = OFF"));
      Motor_Action_Stop_Drill();
      Turn_Off_Relay();
      Drill_ON = 0;
      
      
      }
    

    }

//Test FULL Drill Cycle
// press 'Space Bar' and 'Return' to Stop Cycle

//###########################
if (Command == 107) {                   // letter k
    Command = 0;
    Initiate_Drill_Cycle();
    Turn_Off_Relay();  
    }





// Go UP Spikes
if (Command == 111) {                   // letter o
    Command = 0;
    Setup_Microswitches();
    int cycles = 0;
    bool Stop = 0;
    Turn_On_Relay();
    delay(2000);
    Check_End_Stops();

  
   while ((End_Stop_Upper == false) && (cycles < 13000) && (Stop == 0)) {
      Spikes_Up();      
      Check_End_Stops();
      cycles ++;
      Serial.print("Cycles:");
      Serial.println(cycles);
      Check_Serial_Input();
      if (Command == 32) Stop = 1;
      }
    
    Command = 0;
    Motor_Action_Stop_Spikes();
    Turn_Off_Relay();
    }


// Go DOWN Spikes
if (Command == 108) {                   // letter l
    Command = 0;
    Setup_Microswitches();
    
    int cycles = 0;
    bool Stop = 0;
    
    Turn_On_Relay();
    delay(2000);
    Check_End_Stops();

    while ((End_Stop_Lower == false) && (cycles < 12000) && (Stop == 0)) {
      Spikes_Down();      
      Check_End_Stops();
      cycles ++;
      Serial.print("Cycles:");
      Serial.println(cycles);
      Check_Serial_Input();
      if (Command == 32) Stop = 1;
      }
    
    Command = 0;
    Motor_Action_Stop_Spikes();
    Turn_Off_Relay();
    }


if (Command == 109) {                   // letter m  
    Command = 0;
    Manouver_Park_The_Mower(); 
    delay(100);
    Manouver_Manuel_Mode(); 
    Turn_On_Relay();
    }

if (Command == 112) {                   // letter p  
    Command = 0;
    Manouver_Park_The_Mower();
    }

if (Command == 113) {                   // letter q  
    Command = 0;
    if (Mower_Docked == 1) {
      Serial.println(F("Overriding Docked Status - Starting Mower"));
      delay(2000);
      Mower_Docked = 0;
      }
    Alarm_Start_Quick_Go();
    }


if (Command == 114) {                   // letter r
    Command = 0;
    if (Rain_Sensor_Installed == 0) {
      Rain_Sensor_Installed = 1;
      Serial.println(F("Rain Sensor Enabled = ON"));
      }
    if (Rain_Sensor_Installed == 1) {
      Rain_Sensor_Installed = 0;
      Serial.println(F("Rain Sensor Enabled = OFF"));
      }
    }


if (Command == 118) {                   // letter v  
    Command = 0;
    }

if (Command == 119) {                   // letter w
    Command = 0;
    bool Skip = 0;
    if (Fake_Wire == 0) {
      Fake_Wire = 1;
      Serial.println(F("Fake_Wire Signal Enabled = ON"));
      Skip = 1;
      }
    if ((Fake_Wire == 1) && (Skip == 0)) {
      Fake_Wire = 0;
      Serial.println(F("Fake_Wire Signal Enabled = OFF"));
      }
    }


if (Command == 120) {                   // letter x  
    Command = 0;
    if (Mower_Docked == 1) {
      Serial.println(F("PIXHAWK Mission Start"));
      delay(2000);
      Mower_Docked = 0;
      }
    //Command_long_Mission_Start();
    }


if (Command == 121) {                   // letter x
	Command = 0;

    if (!Fake_WheelAmp) {
    	Fake_WheelAmp = 1;
    	Serial.println(F("Fake_WheelAmp Signal Enabled = ON"));
      }
    else if (Fake_WheelAmp) {
    	Fake_WheelAmp = 0;
    	Serial.println(F("Fake_WheelAmp Signal Enabled = OFF"));
    }
}

if (Command == 122) {                   // letter v
    Command = 0;
    int Skip = 0;

    
    if (Fake_All_Settings == 0) {
      Serial.println(F(""));
      
      Wheel_Amp_Sensor_ON = 0;      
      Fake_All_Settings = 1;     

      Serial.println(F(""));
      Serial.println(F("Fake Volts Enabled = ON"));
      Serial.println(F("Wheel Amp Sensor Disabled"));
      Serial.println(F("Fake Settings ON !!!"));
      Serial.println(F(""));
      Skip = 1;
      }
    
    
    if ((Fake_All_Settings == 1) && (Skip == 0)) {
      Serial.println(F(""));
      
      Perimeter_Wire_Enabled = 1;
      Wheel_Amp_Sensor_ON = 1;
      Fake_All_Settings = 0;
      
      Serial.println(F(""));
      Serial.println(F("All Sensors normal status"));
      Serial.println(F(""));
      }
    

    }

// Blocking bit for quick enable/ disable function when program run to detect which function consume big time
// For using add bit to the logic
// if (F_EN[14] && Mower_Parked == 1) Running_Test_for_Boundary_Wire();

// add this line to setup to enable all options during start up
// for(int i=0; i<33; i++) { F_EN[i] = true; }

if (Command == 63) { for(int i=0; i<33; i++) { F_EN[i] = false; } } // letter ?
if (Command == 64) { for(int i=0; i<33; i++) { F_EN[i] = true; } } // letter @
if (Command == 65) { F_EN[0] = false; } // letter A
if (Command == 66) { F_EN[1] = false; } // letter B
if (Command == 67) { F_EN[2] = false; } // letter C
if (Command == 68) { F_EN[3] = false; } // letter D
if (Command == 69) { F_EN[4] = false; } // letter E
if (Command == 70) { F_EN[5] = false; } // letter F
if (Command == 71) { F_EN[6] = false; } // letter G
if (Command == 72) { F_EN[7] = false; } // letter H
if (Command == 73) { F_EN[8] = false; } // letter I
if (Command == 74) { F_EN[9] = false; } // letter J
if (Command == 75) { F_EN[10] = false; } // letter K
if (Command == 76) { F_EN[11] = false; } // letter L
if (Command == 77) { F_EN[12] = false; } // letter M x
if (Command == 78) { F_EN[13] = false; } // letter N
if (Command == 79) { F_EN[14] = false; } // letter O
if (Command == 80) { F_EN[15] = false; } // letter P

if (Command == 81) { F_EN[16] = false; } // letter Q
if (Command == 82) { F_EN[17] = false; } // letter R
if (Command == 83) { F_EN[18] = false; } // letter S
if (Command == 84) { F_EN[19] = false; } // letter T
if (Command == 85) { F_EN[20] = false; } // letter U
if (Command == 86) { F_EN[21] = false; } // letter V
if (Command == 87) { F_EN[22] = false; } // letter W
if (Command == 88) { F_EN[23] = false; } // letter X
if (Command == 89) { F_EN[24] = false; } // letter Y
if (Command == 90) { F_EN[25] = false; } // letter Z
if (Command == 91) { F_EN[26] = false; } // letter [
if (Command == 93) { F_EN[27] = false; } // letter ] X
if (Command == 48) { F_EN[28] = false; } // letter 0
if (Command == 49) { F_EN[29] = false; } // letter 1
if (Command == 50) { F_EN[30] = false; } // letter 2
if (Command == 51) { F_EN[31] = false; } // letter 3

if (Command == 57) { F_EN[32] = false; } // letter 9 x


}





void Check_Mower_Status() {
      Serial.println("");
      Serial.print(F("Mower Status:  "));
      Serial.print(F("Running ="));
	  Serial.print(Mower_Running);
      Serial.print(F("Parked ="));
      Serial.print(Mower_Parked);
      Serial.print(F(" | Docked = "));
      Serial.print(Mower_Docked);
      Serial.print(F(" | Tracking = "));
      Serial.print(Tracking_Wire);
      Serial.print(F(" |  Exit Dock = "));
      Serial.print(Exiting_Dock);
      Serial.print(F(" |  Error Value = "));
      Serial.print(Mower_Error_Value);
      Serial.println("");
      } 
