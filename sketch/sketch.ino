#include <stdio.h>
#include <string.h>
#include "ph.h"
#include "heater.h"

#define NO_SUBSYSTEMS 3
#define ZERO_CELSIUS 273.15 // zero celsius in kelvin

// These define which pins are connected to what device on the virtual bioreactor
//
const byte lightgatePin	= 2;
const byte stirrerPin		= 5;
const byte heaterPin		 = 6;
const byte thermistorPin = A0;
const byte pHPin				 = A1;

int intCount = 0;
int noRevolutionsForReading = 50;
long long startTime = -1;
long long prevTime = -1;
long long startTime_temp = -1;

// CURRENT READING VALUES
double temperature= 0;
double rpm = 0;
double ph = 0;
// TARGET VALUES
double temperature_target;
double rpm_target;
double ph_target;

// The PCA9685 is connected to the default I2C connections. There is no need
// to set these explicitly.


void setup() {
	Serial.begin(9600);
	pinMode(lightgatePin,	INPUT);
	pinMode(stirrerPin,		OUTPUT);
	pinMode(heaterPin,		 OUTPUT);
	pinMode(thermistorPin, INPUT);
	pinMode(pHPin,				 INPUT);
	attachInterrupt(digitalPinToInterrupt(lightgatePin), rotate, RISING);
    // delay to close picocom and connect to controller
	startTime = millis();

    rpm_target = 1000;
    temperature_target = 30;
    ph_target = 5;
    ph_setup();
    ht_setup();
    ph_set_target(ph_target);
    ht_set_target(temperature_target);
	}

void write_values()
{
    Serial.print("MESSAGE: ");
    Serial.println(get_pwm(temperature));
    Serial.print(temperature);
    Serial.print(" ");
    Serial.print(rpm);
    Serial.print(" ");
    Serial.print(ph);
    Serial.println();
}

void serialEvent()
{
    char msg[1024];
    Serial.readBytesUntil('\n', msg, 1024);
    Serial.flush();
    //Serial.println("Something got sent!");
    //Serial.println(msg);
    if (strncmp(msg, "get current", 11) == 0) // get around random ph target getting sent when rpm under 1000?
    {
        //Serial.println("Current requested!");
        write_values();
    }
    else{
        float subsystem_values[NO_SUBSYSTEMS];
        // split into 3 vals
        int i = 0;
        char* split = strtok(msg, " ");
        while (split != NULL)
        {
            subsystem_values[i] = atof(split);
            split = strtok(NULL, " ");
            ++i;
        }
        free(split);
        // end split
        temperature_target = subsystem_values[0];
        rpm_target = subsystem_values[1];
        ph_target = subsystem_values[2];
        ph_set_target(ph_target);
        ht_set_target(temperature_target);
        //Serial.println(temperature_target);
        //Serial.println(rpm_target);
        //Serial.println(ph_target);
    }
}

 
void loop() { 
// ---------------- STIRING SUBSYSTEM -----------------
	analogWrite(stirrerPin, rpm_target/12.183);
// ----------------------------------------------------

// ---------------- HEATING SUBSYSTEM -----------------
    ht_loop();
    temperature = ht_get_current();

    //Serial.print("Temp: ");
    //Serial.println(temperature);
    //float error = 0;
    //float errorsum = 0;
    //float pwm;
    ////Find Temperature from Thermistor.
    //// get 10 readings and average it
    //temperature = 0;
    //int i = 0;
    //startTime_temp = millis();
    //while (i<NO_READINGS_HEATING)
    //{
    //    if (millis() - startTime_temp >= 2)
    //    {
    //        temperature += (analogRead(thermistorPin)-782.86)/-10.678;
    //        ++i;
    //        startTime_temp = millis();
    //    }
    //}
    //temperature /= NO_READINGS_HEATING;
    //
    //error=temperature_target-temperature;
    //while(error>=0){
    //  errorsum+=error;
    //  error-=1;
    //}
    //error=temperature_target-temperature;
    //// calculate pwm
    //pwm=(15*error)+(5*errorsum)+((-0.001748*(double) pow(temperature_target,4))+(0.2249*(double) pow(temperature_target,3))-(10.97*(double) pow(temperature_target,2))+(244.4*(double) temperature_target)-2069);

    ////Don't let pwm go over 255 or under 0
    //if(pwm<0){
    //pwm=0;
    //}
    //if(pwm>255){
    //pwm=255;
    //}
    //analogWrite(heaterPin, pwm);
// ----------------------------------------------------

// ------------------- PH SUBSYSTEM -------------------
    // Update temperature from the heating subsystem
    ph_set_temperature(temperature + ZERO_CELSIUS);
    ph_loop();
    ph = ph_get_current();
    //Serial.println(ph);
// ----------------------------------------------------
}

void rotate()
{
    intCount += 1; 
    if(intCount >= noRevolutionsForReading)
        {
             prevTime = startTime;
             startTime = millis();
             rpm = (noRevolutionsForReading/2)/((double)(millis()-prevTime)/1000);
             rpm *= 60;
             intCount = 0;
        }
}

