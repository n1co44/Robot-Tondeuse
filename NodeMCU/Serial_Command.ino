void Check_Serial_Input() {
  
  // send data only when you receive data:
  if (SerialDebug.available() > 0) {
    // read the incoming byte:
    int Command_Last = Command;
    Command = SerialDebug.read();
    if (Command == 10) Command = Command_Last;

    // Print Comamnd to Serial Monitor
    if (Command != 0) {
        SerialDebug.print(F(""));
        SerialDebug.print(F(""));
        SerialDebug.println(Command);
        }
  }

Execute_Serial_Command();
}


void Execute_Serial_Command() {

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
	if (Command == 77) { F_EN[12] = false; } // letter M
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
	if (Command == 93) { F_EN[27] = false; } // letter ]
	if (Command == 48) { F_EN[28] = false; } // letter 0
	if (Command == 49) { F_EN[29] = false; } // letter 1
	if (Command == 50) { F_EN[30] = false; } // letter 2
	if (Command == 51) { F_EN[31] = false; } // letter 3

	if (Command == 57) { F_EN[32] = false; } // letter 9
}


