// All the Transmitted informtion functions


void Transmit_Blynk_Data_to_Mega() {
    i = transmit_blynk_code + 10;           // Transmits the code and adds 10 to the number
      NodeMCU.print(i);
      NodeMCU.println("\p");
      delay(30);
      SerialDebug.print("TX_Code_to_MEGA:");
      SerialDebug.print(i);
      SerialDebug.print("");
      delay(20);
      }


void Transmit_Web_Data_to_Mega(byte transmit_web_code) {
  #if defined(WEBSERVER)
	int i = transmit_web_code + 10;           // Transmits the code and adds 10 to the number
	NodeMCU.print(i);
	NodeMCU.println("\p");
	delay(30);
	SerialDebug.print("TX_Code_to_MEGA:");
	SerialDebug.print(i);
	SerialDebug.print("");
	delay(20);
  #endif //-(WEBSERVER)-
}
