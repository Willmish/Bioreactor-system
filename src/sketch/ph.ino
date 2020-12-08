#include <math.h>
#include <Wire.h>
#include "moderator.h"
#include "ph.h"


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
