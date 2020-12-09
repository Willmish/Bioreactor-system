#include <stdio.h>
#include "pca9685.h"


#define acid_on_reg 0x06
#define acid_off_reg 0x08
#define base_on_reg 0x0A
#define base_off_reg 0x0C
#define mode_reg 0x00
#define ph_probe A1
#define optimum 5.0


void setup() {
  Serial.begin(9600);
  pinMode(ph_probe, INPUT);
  write8(mode_reg, AUTOINC);

  write16(acid_on_reg, 0x0199);
  write16(acid_off_reg, 0x04CC);

  write16(base_on_reg, 0x0000);
  write16(base_off_reg, 0x0000);
}


void loop() { 

}



