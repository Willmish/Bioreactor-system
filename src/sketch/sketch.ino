#include <stdio.h>
#include "moderator.h"
#include "ph.h"

#define optimum 5.0


void setup() {
  Serial.begin(9600);
  Serial.println("Hello World");
  pinMode(ph_probe, INPUT);
}


Moderator *mod = moderator(1, 1, 1, optimum);
moderator_clear(mod);


float input, output;

void loop() { 
  input = measure_ph();
  output = moderator_tick(mod, input);
  
  // pump acid or alkeli based on PID output
}



