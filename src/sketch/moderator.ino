// moderator.ino, implements a basic PID controller. Note that P, PI and PD are
// also implicitly supported by setting p, i or d to 0.


#include <stdlib.h>
#include "./moderator.h"


Moderator *moderator(float p, float i, float d, float goal) {
  Moderator *this = (Moderator *) malloc(sizeof(Moderator));
  *this = (Moderator) {p, i, d, goal, 0.0, 0.0};

  return this;
}


void moderator_clear(Moderator *this) {
  this->esum = 0.0;
  this->error = 0.0;
}


void moderator_set_goal(Moderator *this, float goal) {
  this->goal = goal;
}


float moderator_tick(Moderator *this, float input) {
  float err = this->goal - input;
  float prev = this->error;
  this->esum += err;

  return (this->p * err) + (this->i * this->esum) + (this->d * (err - prev));
}
