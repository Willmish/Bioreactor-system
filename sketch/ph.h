#pragma once

#include <stdio.h>
#include <math.h>
#include "./pca9685.h"
#include "./moderator.h"

#define acid_reg 0x06
#define base_reg 0x0A
#define ph_probe A1

#define F 9.6485309E+4 // Faraday
#define R 8.314510 // gas constant
#define vstd 500.0 // voltage at pH-7
#define ln10 2.3025850929940456840179914546843642076011014886287729760333279009
double T = 295.0;// room temperature

static void turn_on(byte);
static void turn_off(byte);
float ph_read();
void ph_setup();
void ph_loop();
float ph_get_current();
void ph_set_target(float);
void ph_set_temperature(float temp_kelvin);

