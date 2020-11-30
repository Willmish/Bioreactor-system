typedef struct {
  float p, i, d, goal;
  float error, esum;
} Moderator;


Moderator *moderator(float, float, float, float);
void moderator_clear(Moderator *);
void moderator_set_goal(Moderator *, float);
float moderator_tick(Moderator *, float);
