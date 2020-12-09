#pragma once

typedef struct {
  float p, i, d, goal;
  float error, sum;
} Moderator;


Moderator *moderator(float, float, float, float);
void moderator_clear(Moderator *);
void moderator_goal(Moderator *, float);
float moderate(Moderator *, float);
