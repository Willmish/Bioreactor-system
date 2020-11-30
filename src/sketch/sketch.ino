/*
 sketch.ino

 Stephen Hailes, Oct 2020

 This is a template sketch for the testboard simduino
  
 */

#include <stdio.h>
#include <string.h>

// These define which pins are connected to what device on the virtual bioreactor
//
const byte lightgatePin  = 2;
const byte stirrerPin    = 5;
const byte heaterPin     = 6;
const byte thermistorPin = A0;
const byte pHPin         = A1;

int rotPerSec = 0;
long long startTime = -1;

// The PCA9685 is connected to the default I2C connections. There is no need
// to set these explicitly.


void setup() {
  Serial.begin(9600);
  Serial.println("Hello World");

  pinMode(lightgatePin,  INPUT);
  pinMode(stirrerPin,    OUTPUT);
  pinMode(heaterPin,     OUTPUT);
  pinMode(thermistorPin, INPUT);
  pinMode(pHPin,         INPUT);

  // More setup...
  }

 
void loop() { 
    analogWrite(heaterPin, 255);
    delay(1500);
    Serial.print("thermistor voltage: ");
    Serial.println(analogRead(thermistorPin));
/*
    // STIRRING
    digitalWrite(stirrerPin, HIGH);
    int lighgateVal = digitalRead(lightgatePin);
    Serial.println(lighgateVal);
    rotPerSec += digitalRead(lightgatePin);
    if (startTime == -1)
    {
        startTime = millis();    
    }
    if (millis()-startTime >= 10000)
    {
        Serial.print("RPM: ");
        Serial.println(rotPerSec*6);
        startTime=millis();
    }*/
}



