#include <math.h>
#include <Wire.h>
#include "moderator.h"

#define F 9.6485309E+4 // Faraday's constant
#define R 8.31450 // universal gas constant
#define T 295.0 // room temperature in Kelvin
#define vmax 5000.0 
#define vs -2500.0


// I2C addresses for our pumps

#define acid 0b1000000
#define alkaline 0b1000001


// register numbers: https://moodle.ucl.ac.uk/pluginfile.php/3568654/mod_resource/content/1/PCA9685.pdf (page 9)

#define LED0_ON_L 6
#define LED1_ON_L 10
#define MODE 0
#define ENABLE_INCREMENT 0b0010000 // enable autoincrement
#define MAX_ON_TIME 4095 // we can have a maximum of 4095 asserted PWM steps 


void prepare_pca9685() {
  Wire.beginTransmission(0);
  Wire.write(MODE);
  Wire.write(ENABLE_INCREMENT);
  Wire.endTransmission();
}


void pump_solute(int on_time, byte from) {
  int off_time = MAX_ON_TIME - on_time;
  int start = from == acid ? LED0_ON_L : LED1_ON_L;
  
  Wire.beginTransmission(from);
  Wire.write(start);
  Wire.write(on_time & 0x00ff);
  Wire.write(on_time & 0xff00);
  Wire.write(off_time & 0x00ff);
  Wire.write(off_time & 0xff00);
  Wire.endTransmission();
}


float measure_ph() {
  int sensor = analogRead(ph_probe);
  float vx = (sensor / 1024.0) * vmax;
  float ph = 7.0 + (F * (vs - vx)) / (R * T * ln(10.0));
  
  return ph;
}
