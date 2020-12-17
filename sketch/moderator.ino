// moderator.ino, implements a basic PID controller
#include "moderator.h"


Moderator *moderator(float p, float i, float d, float goal) {
  Moderator *self = malloc(sizeof(Moderator));
  *self = (Moderator) {p, i, d, goal};

  return self;
}


void moderator_clear(Moderator *self) {
  self->sum = 0.0;
  self->error = 0.0;
}


void moderator_goal(Moderator *self, float goal) {
  self->goal = goal;
}


float moderate(Moderator *self, float input) {
  float e = self->goal - input;
  //float d = e - self->error;
  moderator_clear(self);
  self->error = e;
  //while (e > 0)
  //{
  //  self->sum += e;
  //  --e;
  //}
  //e = self->goal - input;

  //if (e < 0)
  //{
  //  self->sum *= -1;
  //}

  return (self->p * e); //+ (self->i * self->sum) + (self->d * d);
}

void moderator_cleanup(Moderator* self)
{
    free(self);
}
