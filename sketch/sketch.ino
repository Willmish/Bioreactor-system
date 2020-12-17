#include <stdio.h>
#include <string.h>
#include <math.h>
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
int phReadingCount = 0;
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
        // PH target changed, set phCounter back to 0
        phReadingCount = 0;
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
// ----------------------------------------------------

// ------------------- PH SUBSYSTEM -------------------
    // Update temperature from the heating subsystem
    ph_set_temperature(temperature + ZERO_CELSIUS);
    if (phReadingCount < 3)
    {
        if (abs(ph_target-ph)<0.1)
        {
            ph = ph_get_current();
            ++phReadingCount;
        }
        else{ 
        ph_loop();
        phReadingCount = 0;
        ph = ph_get_current();
        }
    }
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

