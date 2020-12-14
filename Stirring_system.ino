

#include <stdio.h>
#include <string.h>

// These define which pins are connected to what device on the virtual bioreactor
//
const byte lightgatePin  = 2;
const byte stirrerPin    = 5;
const byte heaterPin     = 6;
const byte thermistorPin = A0;
const byte pHPin         = A1;

int intCount = 0;
int noRevolutionsForReading = 100;
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

  attachInterrupt(digitalPinToInterrupt(lightgatePin), rotate, RISING);
  // More setup...
  startTime = millis();

  Serial.println("Enter rpm val: ");
  while(!Serial.available());
  Serial.setTimeout(2500);
  int val = Serial.parseInt();
  float pwm=(val)/12.183;
  Serial.println(val);
  Serial.println("Begin!");
  analogWrite(stirrerPin, pwm);
  }

 
void loop() { 
if(intCount == noRevolutionsForReading)
{
   long long prevTime = startTime;
   startTime = millis();
   Serial.print("RPM = ");
   double rpm = (noRevolutionsForReading/2)/((double)(millis()-prevTime)/1000);
   rpm *= 60;
   Serial.println(rpm);
   intCount = 0;
}
}

void rotate()
{
   intCount += 1; 
}
 
 
