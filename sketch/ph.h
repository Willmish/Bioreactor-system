
#pragma once

#include <stdio.h>
#include <math.h>
#include "./pca9685.h"
#include "./moderator.h"
#include "./ph.h"

#define acid_reg 0x06
#define base_reg 0x0A
#define ph_probe A1
#define optimum 5.0

#define F 9.6485309E+4 // Faraday
#define R 8.314510 // gas constant
#define T 295.0 // room temperature
#define vstd 500.0 // voltage at pH-7

static void turn_on(byte);
static void turn_off(byte);
float ph_read();
void ph_setup();
void ph_loop();
