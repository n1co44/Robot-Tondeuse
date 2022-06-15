void Read_Serial1_Nano() {

  if (Mower_PIXHAWK == 0) {
  
#if not defined(NODELAY_SERIALCOM_NANO)
  String Serial1_RX_Value  = "";                                              // changed to string

  while (Serial1.available() > 0) {
    
    char recieved = Serial1.read();
    if ( recieved != '\q' && recieved != '\j' && recieved != '\w' && recieved != '\s' && recieved != '\z' ) {   
      Serial1_RX_Value = Serial1_RX_Value +  (char)recieved;          // hack to joining chars in correct way to Serial1_Rx_Value
      } 
      else if (recieved == '\q') {
      RawValueAmp = Serial1_RX_Value.toInt();                                 // if end of value found, set AmpsTX and clear Serial1_Rx_Value temp var Serial1_Rx_Value used for holding value until \q or \j
      Serial1_RX_Value = ""; // changed to string
      } 
      else if (recieved == '\j') {
      RawValueVolt = Serial1_RX_Value.toInt();                                // same as upper but for VoltsTX, 
      Serial1_RX_Value = "";
      } 
      else if (recieved == '\w') {
      Rain_Detected = Serial1_RX_Value.toInt();                               // same as upper but for VoltsTX
      Serial1_RX_Value = "";
      } 
      else if (recieved == '\s') {
      RawWheelAmp = Serial1_RX_Value.toInt();                               // same as upper but for VoltsTX
      Serial1_RX_Value = "";
      } 
      else if (recieved == '\z') {
      RawDrillAmp = Serial1_RX_Value.toInt();                               // same as upper but for VoltsTX
      Serial1_RX_Value = "";
      } 
    else Serial.print(F("No Data Received|"));
  }
#else
	byte recvBuff [10] = {0};

	if (SerialCom1.update ())
	{
	  byte length = SerialCom1.getLength ();
	  if (length > sizeof (recvBuff)) length = sizeof (recvBuff);
	  memcpy (&recvBuff, SerialCom1.getData (), length);

      RawValueAmp =   recvBuff[0] | recvBuff[1] << 8;
      RawValueVolt =  recvBuff[2] | recvBuff[3] << 8;
      Rain_Detected = recvBuff[4] | recvBuff[5] << 8;
      RawWheelAmp =   recvBuff[6] | recvBuff[7] << 8;
      RawDrillAmp =   recvBuff[8] | recvBuff[9] << 8;
	}  // end if something received

#endif
  //Serial.print("WAmpRaw: ");
  //Serial.print(RawWheelAmp);
  //Serial.print(" |");

  //Serial.print("DAMpRaw: ");
  //Serial.print(RawDrillAmp);
  //Serial.print(" |");

  Calculate_Volt_Amp_Charge();

  }
}