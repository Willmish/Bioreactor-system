#include "./ph.h"


void setup() {
  Serial.begin(9600);
  ph_setup();
  ph_set_target(5.0);
  // heat_setup();
  // stirr_setup();
}


void loop() {
  ph_loop();
  Serial.println(ph_get_current());
  // heat_loop();
  // stirr_loop();
  delay(1000);
}
