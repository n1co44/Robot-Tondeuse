
void Motor_Action_Go_Mowing_Speed() {

  // No Mag speed adjustment active just go full speed
  if (MAG_Speed_Adjustment == 0) Motor_Action_Go_Full_Speed();

  // Adjust wheel speed according to the MAG level
  if (MAG_Speed_Adjustment == 1) {
    if (MAG_Now >= Slow_Speed_MAG) {
      Motor_Action_Go_Full_Speed();
    }

    if (MAG_Now < Slow_Speed_MAG)  {
      Motor_Action_Go_Slow_Speed();
    }
  }
}

void Motor_Action_Go_Full_Speed()     {

  // Full straighgt speed no motr speed ramp up.
  if (Ramp_Motor_ON == 0) {
#if defined(ROBOT_MOWER)
    if (Wheels_Activate) {
    analogWrite(ENAPin, PWM_MaxSpeed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
    analogWrite(ENBPin, PWM_MaxSpeed_LH);                       // Anaolgwirte sends PWM signals Speed = 0-255  (255 is max speed)
    }
#endif


#if defined(ROBOT_AERATOR)
    analogWrite(ENAPin, PWM_MaxSpeed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
    analogWrite(ENBPin, PWM_MaxSpeed_LH);
    analogWrite(ENCPin, PWM_MaxSpeed_RH);
    analogWrite(ENDPin, PWM_MaxSpeed_LH);
#endif

    Wheel_Status_Value = 1;
    Serial.print(F("Wheel:FULL|"));
  }

  // If Ramp up is achieved just go full speed
  if ((Ramp_Motor_ON == 1) && (Full_Speed_Achieved == 1)) {

#if defined(ROBOT_MOWER)
    if (Wheels_Activate) {
    analogWrite(ENAPin, PWM_MaxSpeed_RH);                              // Ramp up the motor speed
    analogWrite(ENBPin, PWM_MaxSpeed_LH);                              // Ramp up the motor speed
    }
#endif

#if defined(ROBOT_AERATOR)
    analogWrite(ENAPin, PWM_MaxSpeed_RH);                              // Ramp up the motor speed
    analogWrite(ENBPin, PWM_MaxSpeed_LH);
    analogWrite(ENCPin, PWM_MaxSpeed_RH);
    analogWrite(ENDPin, PWM_MaxSpeed_LH);
#endif

    Wheel_Status_Value = 2;
    Serial.print(F("Wheel:R-FULL|"));
  }

  // Ramp motor option
  if ((Ramp_Motor_ON == 1) && (Full_Speed_Achieved == 0)) {

    Serial.print(F("|WRamp: "));
    int Motor_Step = 150;

    while (Motor_Step > 1) {

#if defined(ROBOT_MOWER)
	  if (Wheels_Activate) {
      analogWrite(ENAPin, (PWM_MaxSpeed_RH - Motor_Step));                       // Ramp up the motor speed
      analogWrite(ENBPin, (PWM_MaxSpeed_LH - Motor_Step));                       // Ramp up the motor speed
	  }
#endif

#if defined(ROBOT_AERATOR)
      analogWrite(ENAPin, (PWM_MaxSpeed_RH - Motor_Step));                       // Ramp up the motor speed
      analogWrite(ENBPin, (PWM_MaxSpeed_LH - Motor_Step));                       // Ramp up the motor speed
      analogWrite(ENCPin, (PWM_MaxSpeed_RH  - Motor_Step));
      analogWrite(ENDPin, (PWM_MaxSpeed_LH  - Motor_Step));
#endif

      delay(60);
      //Serial.print(F("Step: "));
      //Serial.println(Motor_Step);
      Motor_Step = Motor_Step - 10;
    }

    Wheel_Status_Value = 3;
    Serial.print(F("Wheel:S-FULL|"));
    Full_Speed_Achieved = 1;
  }


}

void Motor_Action_Go_Slow_Speed()     {
#if defined(ROBOT_MOWER)
  if (Wheels_Activate) {
  analogWrite(ENAPin,  PWM_Slow_Speed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
  analogWrite(ENBPin,  PWM_Slow_Speed_LH);                       // Anaolgwirte sends PWM signals Speed = 0-255  (255 is max speed)
  }
#endif


#if defined(ROBOT_AERATOR)
  analogWrite(ENAPin,  PWM_Slow_Speed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
  analogWrite(ENBPin,  PWM_Slow_Speed_LH);                       // Anaolgwirte sends PWM signals Speed = 0-255  (255 is max speed)
  analogWrite(ENCPin,  PWM_Slow_Speed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
  analogWrite(ENDPin,  PWM_Slow_Speed_LH);
#endif

  Wheel_Status_Value = 4;
  Serial.print(F("Wheel:SLOW|"));
}

void Motor_Action_GoFullSpeed_Out_Garage()     {
  //Speeds can be changed to give the mower a slight curve when exiting the Garage.

  PWM_MaxSpeed_LH = PWM_MaxSpeed_LH + 20;
  if (PWM_MaxSpeed_LH > 255)  PWM_MaxSpeed_LH = 255;
  if (PWM_MaxSpeed_RH > 255)  PWM_MaxSpeed_RH = 255;

#if defined(ROBOT_MOWER)
  if (Wheels_Activate) {
  analogWrite(ENAPin, PWM_MaxSpeed_RH);                                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
  analogWrite(ENBPin, PWM_MaxSpeed_LH);
  }
#endif

#if defined(ROBOT_AERATOR)
  analogWrite(ENAPin, PWM_MaxSpeed_RH);                                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
  analogWrite(ENBPin, PWM_MaxSpeed_LH);
  analogWrite(ENCPin, PWM_MaxSpeed_RH);                       // Speed = 0-255  (255 is max speed). Speed is set in the settings
  analogWrite(ENDPin, PWM_MaxSpeed_LH);
#endif

  Wheel_Status_Value = 1;
  Serial.print(F("Wheel:FULL|"));
}


void SetPins_ToGoForwards()     {                                 // Motor Bridge pins are set for both motors to move forwards.

#if defined(ROBOT_MOWER)
  digitalWrite(IN1Pin, LOW);                                      // Motor Birdge pins are set to high or low to set the direction of movement
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
#endif

#if defined(ROBOT_AERATOR)
  digitalWrite(IN1Pin, LOW);                                      //
  digitalWrite(IN2Pin, HIGH);

  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);

  digitalWrite(IN5Pin, LOW);
  digitalWrite(IN6Pin, HIGH);

  digitalWrite(IN7Pin, LOW);
  digitalWrite(IN8Pin, HIGH);
#endif

  Wheel_Status_Value = 5;
  Serial.print(F("|Wheel:For|"));
}


void SetPins_ToGoBackwards()      {                               // Motor Bridge pins are set for both motors to move Backwards
#if defined(ROBOT_MOWER)
  digitalWrite(IN1Pin, HIGH);                                     // Motor 1
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);                                     // Motor 2
  digitalWrite(IN4Pin, LOW);
#endif

#if defined(ROBOT_AERATOR)
  digitalWrite(IN1Pin, HIGH);                                     // Motor 1
  digitalWrite(IN2Pin, LOW);

  digitalWrite(IN3Pin, HIGH);                                     // Motor 2
  digitalWrite(IN4Pin, LOW);

  digitalWrite(IN5Pin, HIGH);
  digitalWrite(IN6Pin, LOW);

  digitalWrite(IN7Pin, HIGH);
  digitalWrite(IN8Pin, LOW);
#endif

  Wheel_Status_Value = 6;
  Serial.print(F("|Wheel:Rev|"));
#if not defined(NODELAY_BACKWARD)
  delay(20);
#endif
}


void Motor_Action_Stop_Motors()  {                                     // Motor Bridge pins are set for both motors to stop
#if defined(ROBOT_MOWER)
  digitalWrite(ENAPin, 0);
  digitalWrite(IN1Pin, LOW);                                    //Motor 1
  digitalWrite(IN2Pin, LOW);
  digitalWrite(ENBPin, 0);                                      //Motor 2
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);
#endif

#if defined(ROBOT_AERATOR)
  digitalWrite(ENAPin, 0);
  digitalWrite(IN1Pin, LOW);                                    //Motor 1
  digitalWrite(IN2Pin, LOW);
  digitalWrite(ENBPin, 0);                                      //Motor 2
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);
  digitalWrite(ENCPin, 0);
  digitalWrite(IN5Pin, LOW);
  digitalWrite(IN6Pin, LOW);
  digitalWrite(ENDPin, 0);
  digitalWrite(IN7Pin, LOW);
  digitalWrite(IN8Pin, LOW);
#endif

  Wheel_Status_Value = 7;
  Serial.print(F("Wheel:0FF|"));

  Full_Speed_Achieved = 0;
}


void SetPins_ToTurnLeft()       {                              // Pins are set so that Motors drive in opposite directions
#if defined(ROBOT_MOWER)
  digitalWrite(IN1Pin, LOW);                                   // Motor 1
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, HIGH);                                  // Motor 2
  digitalWrite(IN4Pin, LOW);
#endif

#if defined(ROBOT_AERATOR)
  digitalWrite(IN1Pin, HIGH);                                   // Motor 1
  digitalWrite(IN2Pin, LOW);

  digitalWrite(IN3Pin, LOW);                                  // Motor 2
  digitalWrite(IN4Pin, HIGH);

  digitalWrite(IN5Pin, LOW);
  digitalWrite(IN6Pin, HIGH);

  digitalWrite(IN7Pin, HIGH);
  digitalWrite(IN8Pin, LOW);
#endif

  Wheel_Status_Value = 8;
  Serial.print(F("Wheel:TL_|"));
}


void SetPins_ToTurnRight() {                                    // Pins are set so that Motors drive in opposite directions
#if defined(ROBOT_MOWER)
  digitalWrite(IN1Pin, HIGH);                                   // Motor 1
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, LOW);                                    //Motor 2
  digitalWrite(IN4Pin, HIGH);
#endif

#if defined(ROBOT_AERATOR)
  digitalWrite(IN1Pin, LOW);                                   // Motor 1
  digitalWrite(IN2Pin, HIGH);

  digitalWrite(IN3Pin, HIGH);                                    //Motor 2
  digitalWrite(IN4Pin, LOW);

  digitalWrite(IN5Pin, HIGH);
  digitalWrite(IN6Pin, LOW);

  digitalWrite(IN7Pin, LOW);
  digitalWrite(IN8Pin, HIGH);
#endif

  Wheel_Status_Value = 9;
  Serial.print(F("Wheel:TR_|"));
}


// USed to turn the mower at a set speed.
void Motor_Action_Turn_Speed() {
#if defined(ROBOT_MOWER)
  if (Wheels_Activate) {
  analogWrite(ENAPin, (PWM_MaxSpeed_RH - Turn_Adjust) );                                  // Change the 0 value to 10 or 20 to recuce the speed
  analogWrite(ENBPin, (PWM_MaxSpeed_LH - Turn_Adjust) );                                  // Change the 0 value to 10 or 20 to recuce the speed
  }
#endif

#if defined(ROBOT_AERATOR)
  analogWrite(ENAPin, (PWM_MaxSpeed_RH - Turn_Adjust) );                                  // Change the 0 value to 10 or 20 to recuce the speed
  analogWrite(ENBPin, (PWM_MaxSpeed_LH - Turn_Adjust) );                                  // Change the 0 value to 10 or 20 to recuce the speed
  analogWrite(ENCPin, (PWM_MaxSpeed_LH - Turn_Adjust) );                                  // Change the 0 value to 10 or 20 to recuce the speed
  analogWrite(ENDPin, (PWM_MaxSpeed_RH - Turn_Adjust) );                                  // Change the 0 value to 10 or 20 to recuce the speed
#endif
}


// Turns the mowing blades on
void Motor_Action_Spin_Blades()  {

  if (Robot_Type == 1) {
    if (Cutting_Blades_Activate == 1) {                                       // Blades are turn ON in settings and will spin!

	#if defined(ROBOT_MOWER)
	  digitalWrite(Relay_Blades_Brake_Resistor, LOW);
		if (!Blade_flagRun) {                // added delay only for first start up of blades because of spikes when relay switched on - reason of stop button interrupt activation
			analogWrite(RPWM, 0);
			delay(100);
			Blade_flagRun = true;
		}
	#endif // -(ROBOT_MOWER)-
      //delay(20); //LOOP_OPTIMIZE disabled
      digitalWrite(R_EN, HIGH);
      digitalWrite(L_EN, HIGH);
      //delay(20); //LOOP_OPTIMIZE disabled
      analogWrite(RPWM, PWM_Blade_Speed);
      //delay(20); //LOOP_OPTIMIZE disabled
      Serial.print(F("Blades:ON_|"));
    }

    if (Cutting_Blades_Activate == 0) {                                     // Blades are turn off in settings and will not spin!
      void StopSpinBlades();

    }
  }
}


void Motor_Action_Stop_Spin_Blades()  {

  if (Robot_Type == 1) {
    //delay(20); //LOOP_OPTIMIZE disabled
    digitalWrite(R_EN, LOW);
    digitalWrite(L_EN, LOW);
    //delay(20); //LOOP_OPTIMIZE disabled
  #if defined(ROBOT_MOWER)
    digitalWrite(Relay_Blades_Brake_Resistor, HIGH);
    Blade_flagRun = false;
  #endif // -(ROBOT_MOWER)-
    Serial.print(F("Blades:0FF|"));
  }
}


//Steers the Mower depending on the PID input from the Algorythm
void Motor_Action_Dynamic_PWM_Steering() {
#if defined(ROBOT_MOWER)
  if (Wheels_Activate) {
  analogWrite(ENAPin, PWM_Right);                             // ENA low = Right Swerve   ENB low = Left Swerve
  analogWrite(ENBPin, PWM_Left);
  }
#endif

#if defined(ROBOT_AERATOR)
  analogWrite(ENAPin, PWM_Right);                             // ENA low = Right Swerve   ENB low = Left Swerve
  analogWrite(ENBPin, PWM_Left);
  analogWrite(ENCPin, PWM_Right);                              // ENA low = Right Swerve   ENB low = Left Swerve
  analogWrite(ENDPin, PWM_Left);
#endif

  Serial.print(F("PWM_L:"));
  Serial.print(PWM_Left);
  Serial.print(F("|"));
  Serial.print(F("PWM_R:"));
  Serial.print(PWM_Right);
  Serial.print(F("|"));

}


void Stop_Button_Pressed() {
  #if defined(STOP_BTN)
	if  (Mower_Running == 1) {
		Motor_Action_Stop_Spin_Blades();
		Motor_Action_Stop_Motors();
		Stop_Button_Activated = true;
	}
  #endif // -(STOP_BTN)-
}


void Stop_Button_Action() {
  #if defined(STOP_BTN)
	// All communication commands should be out of function called by interrupt
	if (Stop_Button_Activated) {
		Manouver_Park_The_Mower();
		Print_LCD_Stop_Btn();
		Serial.println(F(""));
		Serial.println(F("!!! STOP button pressed !!!"));
		Stop_Button_Activated = false;
	}
  #endif // -(STOP_BTN)-
}


void Set_Mower_Forwards_Right() {
  digitalWrite(IN1Pin, LOW);                                      // Motor Birdge pins are set to high or low to set the direction of movement
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);
  }


void Set_Mower_Forwards_Left() {
  digitalWrite(IN1Pin, LOW);                                      // Motor Birdge pins are set to high or low to set the direction of movement
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
  }

void Set_Mower_Backwards_Right() {
  digitalWrite(IN1Pin, HIGH);                                      // Motor Birdge pins are set to high or low to set the direction of movement
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);
  }


void Set_Mower_Backwards_Left() {
  digitalWrite(IN1Pin, LOW);                                      // Motor Birdge pins are set to high or low to set the direction of movement
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  }


void Set_Mecanum_Forwards_Left_Front() {
  #if defined(ROBOT_AERATOR)
  digitalWrite(IN7Pin, LOW);                                      //
  digitalWrite(IN8Pin, HIGH);
  #endif
  }

void Set_Mecanum_Backwards_Left_Front() {
  #if defined(ROBOT_AERATOR)
  digitalWrite(IN7Pin, HIGH);                                      //
  digitalWrite(IN8Pin, LOW);
  #endif
  }

void Set_Mecanum_Forwards_Right_Front() {
  #if defined(ROBOT_AERATOR)
  digitalWrite(IN5Pin, LOW);                                      //
  digitalWrite(IN6Pin, HIGH);
  #endif
  }

void Set_Mecanum_Backwards_Right_Front() {
  #if defined(ROBOT_AERATOR)
  digitalWrite(IN5Pin, HIGH);                                      //
  digitalWrite(IN6Pin, LOW);
  #endif
  }


void Set_Mecanum_Forwards_Left_Rear() {
  #if defined(ROBOT_AERATOR)
  digitalWrite(IN1Pin, LOW);                                      //
  digitalWrite(IN2Pin, HIGH);
  #endif
  }

void Set_Mecanum_Backwards_Left_Rear() {
  #if defined(ROBOT_AERATOR)
  digitalWrite(IN1Pin, HIGH);                                      //
  digitalWrite(IN2Pin, LOW);
  #endif
  }

void Set_Mecanum_Forwards_Right_Rear() {
  #if defined(ROBOT_AERATOR)
  digitalWrite(IN3Pin, LOW);                                      //
  digitalWrite(IN4Pin, HIGH);
  #endif
  }

void Set_Mecanum_Backwards_Right_Rear() {
  #if defined(ROBOT_AERATOR)
  digitalWrite(IN3Pin, HIGH);                                      //
  digitalWrite(IN4Pin, LOW);
  #endif
  }

void Full_Speed_Mecanum_Left_Rear() {
  #if defined(ROBOT_AERATOR)
  analogWrite(ENAPin, PWM_MaxSpeed_RH); 
  #endif
  }

void Full_Speed_Mecanum_Right_Rear() {
  #if defined(ROBOT_AERATOR)
  analogWrite(ENBPin, PWM_MaxSpeed_RH); 
  #endif
  }

void Full_Speed_Mecanum_Left_Front() {
  #if defined(ROBOT_AERATOR)
  analogWrite(ENDPin, PWM_MaxSpeed_RH); 
  #endif
  }

void Full_Speed_Mecanum_Right_Front() {
  #if defined(ROBOT_AERATOR)
  analogWrite(ENCPin, PWM_MaxSpeed_RH); 
  #endif
  }

void Mecanum_Side_Movement_Left() {
  #if defined(ROBOT_AERATOR)
  Set_Mecanum_Backwards_Left_Front();
  Set_Mecanum_Forwards_Right_Front();
  Set_Mecanum_Forwards_Left_Rear();
  Set_Mecanum_Backwards_Right_Rear();
  #endif
  }


void Mecanum_Side_Movement_Right() {
  #if defined(ROBOT_AERATOR)
  Set_Mecanum_Forwards_Left_Front();
  Set_Mecanum_Backwards_Right_Front();
  Set_Mecanum_Backwards_Left_Rear();
  Set_Mecanum_Forwards_Right_Rear();
  #endif
  }

void Mecanum_Diagonal_Movement_Left() {
  #if defined(ROBOT_AERATOR)
  Motor_Action_Stop_Motors();
  Set_Mecanum_Forwards_Right_Front();
  Set_Mecanum_Forwards_Left_Rear();
  #endif
  }


void Mecanum_Diagonal_Movement_Right() {
  #if defined(ROBOT_AERATOR)
  Motor_Action_Stop_Motors();
  Set_Mecanum_Forwards_Left_Front();
  Set_Mecanum_Forwards_Right_Rear();
  #endif
  }

void Mecanum_Rear_Steer_Right() {
  #if defined(ROBOT_AERATOR)
  Motor_Action_Stop_Motors();
  Set_Mecanum_Forwards_Left_Front();
  Set_Mecanum_Backwards_Right_Front();
  #endif
  }


void Mecanum_Rear_Steer_Left() {
  #if defined(ROBOT_AERATOR)
  Motor_Action_Stop_Motors();
  Set_Mecanum_Backwards_Left_Front();
  Set_Mecanum_Forwards_Right_Front();
  #endif
  }
