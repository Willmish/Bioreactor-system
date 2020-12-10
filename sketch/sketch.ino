#include "./ph.h"


void setup() {
  Serial.begin(9600);
  ph_setup();
  // heat_setup();
  // stirr_setup();
}


void loop() {
  Serial.println(ph_read());
  delay(2500);
}
