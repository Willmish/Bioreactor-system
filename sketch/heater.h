#pragma once
#include <stdio.h>
#include "moderator.h"

#define NO_READINGS_HEATING 30
#define heater_pin 6
#define thermistor_pin A0

//double temperature = 0;
Moderator *htmod = moderator(155, 50, 0, 30);

void ht_setup();
void ht_set_target(float target);
double ht_get_current();
float get_pwm(float temp);
void ht_loop();
