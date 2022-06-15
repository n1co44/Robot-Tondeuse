//https://www.benripley.com/diy/arduino/three-ways-to-read-a-pwm-signal-with-arduino/





void Check_PIXHAWK_PWM() {

  Pixhawk_Motor_Test_Initiate = 1;
    
  if (Calibration_Done == 0) {
    Check_Motor_PWM_LH();
    Calibrate_Initial_PWM_LH();
    Check_Motor_PWM_RH();
    Calibrate_Initial_PWM_RH();

    Serial.print("LH Calib | Min =");
    Serial.print(Motor_C_PWM_Min);
    Serial.print("  Max =");
    Serial.print(Motor_C_PWM_Max);
    
    Serial.print(" RH Calib | Min =");
    Serial.print(Motor_D_PWM_Min);
    Serial.print("  Max =");
    Serial.println(Motor_D_PWM_Max);
    Calibration_Done = 1;
    }

  Calibration_Done = 1;

  int Wheel_ON_PWM = 20;

  Serial.print(  "Motor_C(LH)= ");

  Check_Motor_PWM_LH();
  Calculate_PWM_Arduino_Output_LH();
  
  if (PWM_Arduino_LH >= Wheel_ON_PWM) { 
    Serial.print("ON | PWM_Pix = ");
    Serial.print(PIXHAWK_PWM_Value_LH);
    Calculate_PWM_Arduino_Output_LH();
    Serial.print(" | PWM_Ard = ");
    Serial.print(PWM_Arduino_LH);    
  }
  if (PWM_Arduino_LH  < Wheel_ON_PWM) {
    Serial.print("OFF | PWM_Pix=");
    Serial.print(PIXHAWK_PWM_Value_LH);
    Calculate_PWM_Arduino_Output_LH();
    Serial.print(" | PWM_Ard=");
    Serial.print(PWM_Arduino_LH);    
  }

  Serial.print("    Motor_D(RH = ");

  Check_Motor_PWM_RH();
  Calculate_PWM_Arduino_Output_RH();

  if (PWM_Arduino_RH  >= Wheel_ON_PWM) {
    Serial.print(" ON | PWM_Pix = ");
    Serial.print(PIXHAWK_PWM_Value_RH);
    Calculate_PWM_Arduino_Output_RH();
    Serial.print(" | PWM_Ard = ");
    Serial.print(PWM_Arduino_RH);    
  }
  if (PWM_Arduino_RH < Wheel_ON_PWM) {
    Serial.print(" OFF | PWM_Pix = ");
    Serial.print(PIXHAWK_PWM_Value_RH);
    Calculate_PWM_Arduino_Output_RH();
    Serial.print(" | PWM_Ard = ");
    Serial.print(PWM_Arduino_RH);    
  }

  Serial.print("  |  ");
  PWM_Left = PWM_Arduino_LH;
  PWM_Right = PWM_Arduino_RH;
  Motor_Action_Dynamic_PWM_Steering();
  //Serial.println("");
}

 


void Check_Motor_PWM_LH() {
  PIXHAWK_PWM_Value_LH = pulseIn(PIXHAWK_LH_PWM, HIGH);
  delay(10);
  }

void Check_Motor_PWM_RH() {  
  PIXHAWK_PWM_Value_RH = pulseIn(PIXHAWK_RH_PWM, HIGH);
  delay(10);
}


 

void Calculate_PWM_Arduino_Output_LH() {
  int PWM_Range =   (Motor_C_PWM_Max - Motor_C_PWM_Min) / 255;
  PWM_Arduino_LH = (PIXHAWK_PWM_Value_LH - Motor_C_PWM_Min) / PWM_Range;
  if (PWM_Arduino_LH > 255) PWM_Arduino_LH = 255;
  if (PWM_Arduino_LH < 20) PWM_Arduino_LH = 0;
}

void Calculate_PWM_Arduino_Output_RH() {
  int PWM_Range =   (Motor_D_PWM_Max - Motor_D_PWM_Min) / 255;
  PWM_Arduino_RH = (PIXHAWK_PWM_Value_RH - Motor_D_PWM_Min) / PWM_Range;
  if (PWM_Arduino_RH > 255) PWM_Arduino_RH = 255;
  if (PWM_Arduino_RH < 20) PWM_Arduino_RH = 0;
}


void Calibrate_Initial_PWM_LH() {
    Motor_C_PWM_Min = PIXHAWK_PWM_Value_LH;
    Motor_C_PWM_Max = PIXHAWK_PWM_Value_LH + 305;
    }
  

void Calibrate_Initial_PWM_RH() {
    Motor_D_PWM_Min = PIXHAWK_PWM_Value_RH;
    Motor_D_PWM_Max = PIXHAWK_PWM_Value_RH + 305;
    }
