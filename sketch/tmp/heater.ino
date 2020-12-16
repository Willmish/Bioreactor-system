
#include <stdio.h>
#include <string.h>

#define NO_READINGS 30
// These define which pins are connected to what device on the virtual bioreactor
//
const byte lightgatePin  = 2;
const byte stirrerPin    = 5;
const byte heaterPin     = 6;
const byte thermistorPin = A0;
const byte pHPin         = A1;
int target ;
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
String msg1 ="Good Day Sir";
String msg2="What temperature would you like to set your bio-reactor to?";
Serial.println(msg1);
Serial.println(msg2);
while(!Serial.available());


Serial.setTimeout(3000);
target=Serial.parseInt();
Serial.println(target);   
}

 void loop(){
 
float tempVal;
float Temperature = 0;
float error;
float errorsum=0;
float pwm;

 
 
  //Find Temperature from Thermistor.
  // get 10 readings and average it
  for (int i = 0; i<NO_READINGS; ++i)
  {
    tempVal=analogRead(thermistorPin);
    Temperature += (tempVal-782.86)/-10.678;
    delay(2);
  }
  Temperature /= NO_READINGS;
 
  Serial.print(" Temperature=");
   Serial.print(Temperature);
   Serial.print("C");
   Serial.print(" Kelvin: ");
   Serial.print(Temperature+273.15);
   Serial.print("K ");
   
   
//calculate error and error sum
error=target-Temperature;
Serial.print("error=");
   Serial.print(error);
while(error>=0){
  errorsum+=error;
  error-=1;
}
 
 error=target-Temperature;
   Serial.print(" errorsum=");
     Serial.println(errorsum);
 
 // calculate pwm
  pwm=(5*error)+(2*errorsum)+((-0.001748*(double) pow(target,4))+(0.2249*(double) pow(target,3))-(10.97*(double) pow(target,2))+(244.4*(double) target)-2069);

//Don't let pwm go over 255 or under 0
  if(pwm<0){
  pwm=0;
  }
  if(pwm>255){
  pwm=255;
  }
    analogWrite(heaterPin, pwm);
    Serial.print("pwm=");
   Serial.println(pwm);
   Serial.println("");
   delay(10000);
}
