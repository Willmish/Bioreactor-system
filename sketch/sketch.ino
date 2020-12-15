#include <stdio.h>
#include <string.h>
#include "stiring.h"

#define NO_SUBSYSTEMS 3

// These define which pins are connected to what device on the virtual bioreactor
//
const byte lightgatePin	= 2;
const byte stirrerPin		= 5;
const byte heaterPin		 = 6;
const byte thermistorPin = A0;
const byte pHPin				 = A1;

int intCount = 0;
int noRevolutionsForReading = 100;
long long startTime = -1;
long long prevTime = -1;
long long lastMsgSent = -1;

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

    lastMsgSent = millis();
    rpm_target = 1000;
    temperature_target = 25;
    ph_target = 5;
	}

void split_values(char values[], float* target[])
{
    // split input into float array 
    int i = 0;
    char* split = strtok(values, " ");
    while (split != NULL)
    {
        (*target)[i] = atof(split);
        split = strtok(NULL, " ");
        ++i;
    }
}

void write_values()
{
    if(millis()-lastMsgSent >= 500)
    {
        Serial.flush();
        Serial.print(temperature);
        Serial.print(" ");
        Serial.print(rpm);
        Serial.print(" ");
        Serial.print(ph);
        Serial.println();
        lastMsgSent = millis();
    }
}

void serialEvent()
{
    if(Serial.available())
    {
        char values[1024];
        Serial.readBytesUntil('\n', values, 1024);
        Serial.flush();
        float* subsystem_values = malloc(sizeof(float)* NO_SUBSYSTEMS); // Heating, stiring, ph
        split_values(values, &subsystem_values);
        temperature_target = subsystem_values[0];
        rpm_target = subsystem_values[1];
        ph_target = subsystem_values[2];
        free(subsystem_values);
    }
}

 
void loop() { 
	analogWrite(stirrerPin, rpm_target/12.183);
    if(intCount == noRevolutionsForReading)
    {
         prevTime = startTime;
         startTime = millis();
         rpm = (noRevolutionsForReading/2)/((double)(millis()-prevTime)/1000);
         rpm *= 60;
         intCount = 0;
    }
    write_values();
}

void rotate()
{
	 intCount += 1; 
}



