#include "./ph.h"


static void turn_on(byte reg) {
  write16(reg, 0x0002);
  write16(reg + 2, 0x000F);
}


static void turn_off(byte reg) {
  write16(reg, 0x0000);
  write16(reg + 2, 0x0000);
}


float ph_read() {
  int vout = analogRead(ph_probe);
  float ln = log(10)/log(2.71828);

  return 7.0 + ((vstd - vout)*F*0.001)/(R*T*ln);
}


void ph_setup() {
  pinMode(ph_probe, INPUT);
  write8(mode_reg, AUTOINC);
}


void ph_loop() {

}
