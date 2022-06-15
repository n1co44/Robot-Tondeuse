
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

// Options - uncomment if using ...
#define NODELAY_SERIALCOM 	// Uncomment if using serial communication without delay() function
#define AVG_CAL_VALUES		// Uncomment if using Averaging and Calibration of values
#define WHEELAMPSENS		// Uncomment if using wheel amp sensor
//#define DRILLAMPSENS		// Uncomment if using drill amp sensor
#define CYCLETIMEMEAS		// Uncomnent if using measuring of loop() cycle time

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

#include <SoftwareSerial.h>


SoftwareSerial mySerial(10, 11);  // RX, TX

#if defined(NODELAY_SERIALCOM)
#include "SerialCom_non_blocking.h"
SerialCom myChannel (mySerial, 40);
#endif // -(NODELAY_SERIALCOM)-

// Sensor Variables.
int RawValueAmp= 0;
int RawValueVolt = 0;
int RawWheelAmp = 0;
int RawDrillAmp = 0;
int RawValueRain = 0;
int Raining = 5;
int Charging = 0;

#if defined(AVG_CAL_VALUES)
// Variables for averaging Volt/Amp/Rain
int AmpSum=0;
int VoltSum=0;
int RainSum=0;
int WheelSum=0;
int DrillSum=0;

// Calibration values
const int RawValueAmpOffset = 12; 	// change calibration value to see right value on display
const int RawWheelAmpOffset = 0; 	// change calibration value to see right value on display
const int RawDrillAmpOffset = 0; 	// change calibration value to see right value on display
const int RawValueVoltOffset = 0;	// change calibration value to see right value on display

const int NrOfMeasForAvg_AmpVolt = 50; // number of measuring for averaging of value
const int NrOfMeasForAvg_WheelDrill = 10; // number of measuring for averaging of value
#endif

// Transmission of the raw sensor values to the Arduino MEGA
float AmpsTX;
float VoltsTX;
float WheelAmpsTX;
float DrillAmpsTX;
bool  Test;
int   Wheel_Blocked;
int   Drill_Blocked;
float AmpLimit = 1.0;
float AmpLimit_Drill = 6.5;

#if defined(CYCLETIMEMEAS)
signed long resultCTime;
signed long startCTime;
#endif //-(CYCLETIMEMEAS)-

void setup(){
#if not defined(NODELAY_SERIALCOM)
 Serial.begin(9600);
 mySerial.begin(1200);
#else
 Serial.begin(115200);  // this speed save 80ms
 mySerial.begin(57600); // this speed save 40ms
#endif
#if defined(NODELAY_SERIALCOM)
 myChannel.begin ();
#endif
 Test = 0;



 pinMode(A1, INPUT);   // Amps Sensor
 pinMode(A2, INPUT);   // Volts Sensor
 pinMode(A3, INPUT);   // Rain Sensor
 pinMode(A6, INPUT);   // Wheel Amps Sensor
 pinMode(A7, INPUT);   // Drill Amp Sensor

 if (Test == 1) {
  RawValueAmp = 510;
  RawValueVolt = 500;
 }
}

void Calculate_Volt_Amp() {


// Calculate Amp Value from Charging Pins
 int mVperAmp = 185;
 int ACSoffset = 2500;
 double VoltageAmp = 0;
 double Amps = 0;


 // Calibrating raw values by adding of offset value
#if defined(AVG_CAL_VALUES)
 RawValueAmp  = RawValueAmp  + RawValueAmpOffset;
 RawWheelAmp =  RawWheelAmp  + RawWheelAmpOffset;
 RawDrillAmp  = RawDrillAmp  + RawDrillAmpOffset;
 RawValueVolt = RawValueVolt + RawValueVoltOffset;
#endif

 // Charging Amps
 VoltageAmp = (RawValueAmp / 1024.0) * 5000; // Gets you mV
 AmpsTX =  ((VoltageAmp - ACSoffset) / mVperAmp);

 // Wheel Amps
#if defined(WHEELAMPSENS)
 VoltageAmp = (RawWheelAmp / 1024.0) * 5000; // Gets you mV
 WheelAmpsTX =  ((VoltageAmp - ACSoffset) / mVperAmp);
#endif // -(WHEELAMPSENS)-

 // Drill Amps
#if defined(DRILLAMPSENS)
 VoltageAmp = (RawDrillAmp / 1024.0) * 5000; // Gets you mV
 DrillAmpsTX =  ((VoltageAmp - ACSoffset) / mVperAmp);
#endif // -(DRILLAMPSENS)-

// Calculate Voltage Sensor Value from Battery

 float vout = 0.0;
 float R1 = 30000;      // 30000 Mower 2    Mower 1 30000
 float R2 = 7500;       // 7300 Mower 2     Mower 1 7500
 vout = (RawValueVolt * 5.0) / 1024.0; // see text
 VoltsTX = vout / (R2/(R1+R2));

}


void TX_Volts()  {
  mySerial.print(VoltsTX);
  mySerial.println("\j");
  Serial.print("VoltsTX = ");
  Serial.print(VoltsTX);
  Serial.print("|");
}

void TX_Raw_Value_Volts()  {
  mySerial.print(RawValueVolt);
  mySerial.println("\j");
}

void TX_Charge()  {
  mySerial.print(Charging);
  mySerial.println("\q");
  }

void TX_Raw_Value_Charge()  {
  mySerial.print(RawValueAmp);
  mySerial.println("\q");
  }

void TX_Raining()  {
  mySerial.print(Raining);
  mySerial.println("\w");
  }

void TX_Wheel_Blocked()  {
  mySerial.print(RawWheelAmp);
  mySerial.println("\s");
  }

void TX_Drill_Blocked()  {
  mySerial.print(RawDrillAmp);
  mySerial.println("\z");
  }


// function for measuring of loop cycle time, for usage just call it
void RuntimeMeasuring() {
#if defined(CYCLETIMEMEAS)
	resultCTime = (signed long)millis() - startCTime;
	Serial.print(F("CT:")); Serial.print(resultCTime);
	startCTime = (signed long)millis();
#endif // -(CYCLETIMEMEAS)-
}

void loop(){

 //Read Amp and Volt Raw Number Sensor Values
 if (Test == 0) {
#if not defined(AVG_CAL_VALUES)
 RawValueAmp = analogRead(A1);
 RawValueVolt = analogRead(A2);
 Raining = analogRead(A3);
#if defined(WHEELAMPSENS)
 RawWheelAmp = analogRead(A6);
#endif //-(WHEELAMPSENS)-
#if defined(DRILLAMPSENS)
 RawDrillAmp = analogRead(A7);
#endif // -(DRILLAMPSENS)-

#else

 AmpSum = 0;
 for (int i=0; i<NrOfMeasForAvg_AmpVolt; i++) {
	 AmpSum = AmpSum + analogRead(A1);
 }
 RawValueAmp = AmpSum / NrOfMeasForAvg_AmpVolt;

 VoltSum = 0;
 for (int i=0; i<NrOfMeasForAvg_AmpVolt; i++) {
	 VoltSum = VoltSum + analogRead(A2);
 }
 RawValueVolt = VoltSum / NrOfMeasForAvg_AmpVolt;

 RainSum = 0 ;
 for (int i=0; i<NrOfMeasForAvg_AmpVolt; i++) {
	 RainSum = RainSum + analogRead(A3);
 }
 RawValueRain = RainSum / NrOfMeasForAvg_AmpVolt;
 Raining = RawValueRain;

#if defined(WHEELAMPSENS)
 WheelSum = 0 ;
 for (int i=0; i<NrOfMeasForAvg_WheelDrill; i++) {
	 WheelSum = WheelSum + analogRead(A6);
 }
 RawWheelAmp = WheelSum / NrOfMeasForAvg_WheelDrill;
#endif // -(WHEELAMPSENS)-

 #if defined(DRILLAMPSENS)
 DrillSum = 0 ;
 for (int i=0; i<NrOfMeasForAvg_WheelDrill; i++) {
	 DrillSum = DrillSum + analogRead(A7);
 }
 RawDrillAmp = DrillSum / NrOfMeasForAvg_WheelDrill;
 #endif // -(DRILLAMPSENS)-

#endif // -(AVG_CAL_VALUES)-
 }

  if (Test == 1 )   {
 RawValueAmp = RawValueAmp + 1;
 if (RawValueAmp > 550) RawValueAmp = 500;
 RawValueVolt = RawValueVolt + 1;
 if (RawValueVolt > 550) RawValueVolt = 500;
  }


 Serial.print("VoltsTX Raw = ");
 Serial.print(RawValueVolt);
 Serial.print("|");
 Serial.print("AmpsTX Raw = ");
 Serial.print (RawValueAmp);
 Serial.print("|");
#if defined(WHEELAMPSENS)
 Serial.print("Wheel Raw = ");
 Serial.print (RawWheelAmp);
 Serial.print("|");
#endif // -(WHEELAMPSENS)-
#if defined(DRILLAMPSENS)
 Serial.print("Drill Raw = ");
 Serial.print (RawDrillAmp);
 Serial.print("|");
#endif // -(DRILLAMPSENS)-


 Calculate_Volt_Amp();

 Serial.print("VoltsTX = ");
 Serial.print(VoltsTX);
 Serial.print("|");

 if (AmpsTX < 0.25) Charging = 0;
 if (AmpsTX > 0.25) Charging = 4;
 Serial.print("Charging = ");
 Serial.print(Charging);
 Serial.print("|");

 Serial.print("AmpsTX = ");
 Serial.print (AmpsTX);
 Serial.print("|");

 Serial.print("Rain Sensor Raw = ");
 Serial.print (Raining);
 Serial.print("|");

if (Raining < 100) Raining = 0;
if (Raining >= 100) Raining = 1;

Serial.print( "Raining = ");
Serial.print(Raining);
Serial.print("|");

#if defined(WHEELAMPSENS)
Serial.print( "Wheel Amps = ");
Serial.print(WheelAmpsTX);
Serial.print("|");

if (WheelAmpsTX > AmpLimit) {
  Serial.print ("!! Wheel Blocked !!");
  Wheel_Blocked = 4;
  }
if (WheelAmpsTX <= AmpLimit) {
  Wheel_Blocked = 0;
  }
#endif // -(WHEELAMPSENS)-

#if defined(DRILLAMPSENS)
Serial.print( "Drill Amps = ");
Serial.print(DrillAmpsTX);
Serial.print("|");

if (DrillAmpsTX > AmpLimit_Drill) {
  Serial.print ("!! Drill Blocked !!");
  Drill_Blocked = 4;
  }
if (DrillAmpsTX <= AmpLimit_Drill) {
  Drill_Blocked = 0;
  }
#endif // -(DRILLAMPSENS)-

#if defined(CYCLETIMEMEAS)
 RuntimeMeasuring(); // loop cycle time measuring
#endif // -(CYCLETIMEMEAS)-

 Serial.println("");

#if not defined(NODELAY_SERIALCOM)
 TX_Raw_Value_Charge();
 delay(5);
 TX_Raw_Value_Volts();
 delay(5);
 TX_Raining();
 delay(5);
 TX_Wheel_Blocked();
 delay(5);
 TX_Drill_Blocked();
#else
	byte data[10];
	data[0]=RawValueAmp;
	data[1]=RawValueAmp >> 8;

	data[2]=RawValueVolt;
	data[3]=RawValueVolt >> 8;

	data[4]=Raining;
	data[5]=Raining >> 8;

	data[6]=RawWheelAmp;
	data[7]=RawWheelAmp >> 8;

	data[8]=RawDrillAmp;
	data[9]=RawDrillAmp >> 8;

	myChannel.sendMsg (data, sizeof (data));
#endif

}
