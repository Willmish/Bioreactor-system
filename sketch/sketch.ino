#include "ph.h"
#include "pca9685.h"
#include "moderator.h"


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



