#include "./ph.h"


float change, optimum = 5.0;
Moderator *phmod = moderator(1.0, 0.0, 0.0, optimum);


static void turn_on(byte reg) {
  write16(reg, 0x0002);
  write16(reg + 2, 0x0003);
}


static void turn_off(byte reg) {
  write16(reg, 0x0000);
  write16(reg + 2, 0x0000);
}


float ph_read() {
  int vout = analogRead(ph_probe);
  return 7.0 + ((-vstd + vout)*F*0.001)/(R*T*ln10);
}


void ph_setup() {
  pinMode(ph_probe, INPUT);
  write8(mode_reg, AUTOINC);
  moderator_clear(phmod);
  //turn_on(acid_reg);
  //delay(350);
  //turn_off(acid_reg);
  //Serial.println(ph_read());
}


void ph_set_target(float value) {
  moderator_goal(phmod, value);
}

void ph_set_temperature(float temp_kelvin) {
    T = temp_kelvin;
}


float ph_get_current() {
  return ph_read();
}


void ph_loop() {
  turn_off(acid_reg);
  turn_off(base_reg);

  change = moderate(phmod, ph_read());

  if (change > 0.5) {
    turn_on(base_reg);
  } 

  else if (change < -0.5) {
    turn_on(acid_reg);
  }
}

