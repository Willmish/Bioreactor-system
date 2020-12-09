#include <stdio.h>
#include "pca9685.h"
#include "ph.h"


float read_ph() {
  int sensor = analogRead(ph_probe);
  float vx = (sensor / 1024.0) * vmax;
  float ph = 7.0 + (F * (vs - vx)) / (R * T * ln(10.0));
  
  return ph;
}




