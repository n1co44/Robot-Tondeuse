void Check_Serial_Input_PIXHAWK() {

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

Execute_Serial_Command_PIXHAWK();
}


void Execute_Serial_Command_PIXHAWK() {

if (Command == 104) {                   // letter h
    Command = 0;
    Serial.println(F("  "));
    Serial.println(F("  "));
    Serial.println(F("      PIXHAWK HELP MENU"));
    Serial.println(F("      Enter the following letter"));
    Serial.println(F("  -----------------------------"));
    Serial.println(F("  a = ARM"));           //97
    Serial.println(F("  b = AUTO MODE"));       //98
    Serial.println(F("  c = ")); //99
    Serial.println(F("  d = DIS-ARM"));         //100
    Serial.println(F("  e = "));             //101
    Serial.println(F("  f = Follow Mode"));           //102
    Serial.println(F("  g = Guided Mode"));
    Serial.println(F("  h = "));             //104
    Serial.println(F("  i = "));          //105
    Serial.println(F("  j = "));
    Serial.println(F("  k = "));      //107
    Serial.println(F("  l = "));           //108
    Serial.println(F("  m = MANUAL Mode"));
    Serial.println(F("  n = ACRO Mode"));
    Serial.println(F("  o = "));             //111
    Serial.println(F("  p = "));      //112
    Serial.println(F("  q = Quit PIXHAWK Mode"));     //113
    Serial.println(F("  r = "));    //114
    Serial.println(F("  s = "));      //115
    Serial.println(F("  t = "));
    Serial.println(F("  u = "));
    Serial.println(F("  v = "));       //118
    Serial.println(F("  w = "));     //119
    Serial.println(F("  x = "));       //120
    Serial.println(F("  y = "));
    Serial.println(F("  z = "));    //122"));
    Serial.println(F("  "));
    Serial.println(F("  "));


    delay(7000);
    }

if (Command == 97) {                   // letter a
    Command = 0;
    Serial.println("");
    Serial.println("ARMED");
    Serial.println("");
    Command_long_ARM();
    }

if (Command == 100) {                   // letter d
    Command = 0;
    Serial.println("");
    Serial.println("DIS-ARM");
    Serial.println("");
    Command_long_Disarm();
    }

if (Command == 98) {                   // letter b
    Command = 0;
    Serial.println("");
    Serial.println("AUTO MODE");
    Serial.println("");
    Auto_Mode();
    }

if (Command == 102) {                   // letter f
    Command = 0;
    Serial.println("");
    Serial.println("Follow MODE");
    Serial.println("");
    Follow_Mode();
    }

if (Command == 103) {                   // letter f
    Command = 0;
    Serial.println("");
    Serial.println("Guided MODE");
    Serial.println("");
    Guided_Mode();
    }

if (Command == 109) {                   // letter m
    Command = 0;
    Serial.println("");
    Serial.println("Manual MODE");
    Serial.println("");
    Manual_Mode();
    }

if (Command == 110) {                   // letter n
    Command = 0;
    Serial.println("");
    Serial.println("ACRO Mode");
    Serial.println("");
    Acro_Mode();
    }

if (Command == 113) {                   // letter q
    Command = 0;
      Serial.println("");
      Serial.println("Mower set to ReP_AL Mode");
      Serial.println("");
      Mower_Docked = 1;
      Mower_PIXHAWK = 0;
      }

}
