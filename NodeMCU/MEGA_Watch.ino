

void Check_MEGA_Status() {
  if (Mower_Running == 1) {
       
    // Check the readings coming from the MEGA
    
    Check_MEGA = (Check_MEGA + 1);

    SerialDebug.print("Check MEGA:");
    SerialDebug.print(Check_MEGA);

    if (Check_MEGA == 1) {
      Loop_Cycle_Mowing_Check_1 = Loop_Cycle_Mowing;
      val_VoltNow_Check_1 = val_VoltNow;
      }

    if (Check_MEGA == 2) {
      Loop_Cycle_Mowing_Check_2 = Loop_Cycle_Mowing;
      val_VoltNow_Check_2 = val_VoltNow;
      Check_MEGA = 0;
      } 
      
    // Test to see if the values are the same and therefore maybe indicate a hung MEGA..
    if (Loop_Cycle_Mowing_Check_1 == Loop_Cycle_Mowing_Check_2)   Error_Loop = Error_Loop + 1;
    if (val_VoltNow_Check_1 == val_VoltNow_Check_2)               Error_Volt = Error_Volt + 1;

    if (Loop_Cycle_Mowing_Check_1 != Loop_Cycle_Mowing_Check_2)   Error_Loop = 0;
    if (val_VoltNow_Check_1 != val_VoltNow_Check_2)               Error_Volt = 0;

    
    Total_Error = Error_Loop + Error_Volt;
    

    SerialDebug.print("|L1:");
    SerialDebug.print(Loop_Cycle_Mowing_Check_1);
    SerialDebug.print("|L2:");
    SerialDebug.print(Loop_Cycle_Mowing_Check_1);
    SerialDebug.print("|ErrL:");
    SerialDebug.print(Error_Loop);
    
    SerialDebug.print("|V1:");
    SerialDebug.print(val_VoltNow_Check_1);
    SerialDebug.print("|V2:");
    SerialDebug.print(val_VoltNow_Check_2);
    SerialDebug.print("|ErrV:");
    SerialDebug.print(Error_Volt);
    
    SerialDebug.print("|Tot Error:");
    SerialDebug.print(Total_Error);


    if (Total_Error < Max_Error) SerialDebug.print("|MEGA OK");
    if (Total_Error >= Max_Error) {
      SerialDebug.print("|MEGA ERROR");
      Blynk.virtualWrite(V11, 1023);
      digitalWrite(D5, HIGH); 
      digitalWrite(D5, LOW);
      delay(1000);
      digitalWrite(D5, HIGH); 
      delay(2000);
      Total_Error = 0;
      Error_Loop = 0;
      Error_Volt = 0;
      
    }
       
  }
}
