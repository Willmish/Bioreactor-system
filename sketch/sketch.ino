#include "./ph.h"


void setup() {
  Serial.begin(9600);
  ph_setup();
  // heat_setup();
  // stirr_setup();
}


void loop() {
  ph_loop();
  // heat_loop();
  // stirr_loop();
  delay(1000);
}
