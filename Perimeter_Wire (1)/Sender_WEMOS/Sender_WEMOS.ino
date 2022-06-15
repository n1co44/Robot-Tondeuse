#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "****";

char ssid[] = "****";
char pass[] = "*****";
char server[] = "192.168.*.*";  // The local IP address of your Local Server device.

BlynkTimer timer;
#define LED D4      // on various NODEMCU boards the LED Pin is different.....
#define PIN D5

void myTimerEvent()  {

}

void setup() {
  // put your setup code here, to run once:

pinMode(PIN,OUTPUT);
digitalWrite(PIN, LOW);
delay(1000);
digitalWrite(PIN, HIGH);
delay(1000);
digitalWrite(PIN, LOW);
delay(1000);
digitalWrite(PIN, HIGH);
delay(1000);
Serial.begin (9600);
WIFI_Connect();                                   // Connect to the WIFI
}

void WIFI_Connect() {
  
  int mytimeout = millis() / 1000;
  Serial.println();
  Serial.println("*********************************************");
  Blynk.begin(auth, ssid, pass, server, 8080); //9443   IPAddress(192,168,1,58), 9443
  
  
  while (Blynk.connected() != WL_CONNECTED) {
    delay(500);
      if((millis() / 1000) > mytimeout + 3){                      // try for less than 4 seconds to connect to WiFi router
      break;
    }
  }
  
  if(!Blynk.connected()) {
    digitalWrite(LED, HIGH);
    Serial.println("NODEMCU Disconnected");
    Serial.println("Reconnecting . . . . . . ");
    WIFI_Connect();

    }
  else {
    digitalWrite(LED, LOW);
    Serial.println("Connected. . . . . .");
    // Setup a function to be called every second
    timer.setInterval(1000L, myTimerEvent);
    }
  }


BLYNK_WRITE(V1) {
  switch (param.asInt())
  {
    case 1: {                        // WIRE ON
    digitalWrite(PIN, HIGH);
    Serial.println("Relay ON");
    Blynk.virtualWrite(V2, 1023);    // Mow LED 
    Blynk.virtualWrite(V3, 0);    // Mow LED 
    break;
    }
    case 2: {                       // WIRE OFF
    digitalWrite(PIN, LOW);
    Serial.println("Relay OFF");
    Blynk.virtualWrite(V2, 0);    // Mow LED
    Blynk.virtualWrite(V3, 1023);    // Mow LED
    break;
    }
  }
}


void loop()  {

  
  if(!Blynk.connected()) {
    Blynk.run();
    timer.run();  
    digitalWrite(LED, HIGH);
    Serial.println("------------------------");
    Serial.println("NODEMCU Disconnected");
    Serial.println("Reconnecting ... ");
    WIFI_Connect() ;
    }
  else {
    Blynk.run();
    timer.run();  
    //Serial.println("");     // new line serial monitor
    //Serial.println("Switch Running");
    
  }


}
