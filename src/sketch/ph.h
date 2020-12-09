#pragma once
#define acid_on_reg 0x06
#define acid_off_reg 0x08
#define base_on_reg 0x0A
#define base_off_reg 0x0C
#define ph_probe A1
#define optimum 5.0

#define F 9.6485309E+4 // Faraday's constant
#define R 8.31450 // universal gas constant
#define T 295.0 // room temperature in Kelvin
#define vmax 5000.0 
#define vs -2500.0


float read_ph();
