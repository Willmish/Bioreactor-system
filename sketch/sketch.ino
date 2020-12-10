#include "./ph.h"


void setup() {
  Serial.begin(9600);
  pinMode(ph_probe, INPUT);
  ph_setup();
}


void loop() {
  Serial.println(ph_read());
  delay(2500);
}



