#pragma once
#include "heater.h"
#include "moderator.h"
#include <stdio.h>

void ht_setup()
{
    moderator_clear(htmod);
}

void ht_set_target(float target)
{
  moderator_goal(htmod, target);
}

double ht_get_current()
{
    int i = 0;
    startTime_temp = millis();
    while (i<NO_READINGS_HEATING)
    {
        if (millis() - startTime_temp >= 2)
        {
            temperature += (analogRead(thermistor_pin)-782.86)/-10.678;
            ++i;
            startTime_temp = millis();
        }
    }
    temperature /= NO_READINGS_HEATING;
    return temperature;
}
void ht_loop()
{
    float pwm = moderate(htmod, ht_get_current());
    if(pwm<0){
    pwm=0;
    }
    if(pwm>255){
    pwm=255;
    }
    analogWrite(heater_pin, pwm);
}

