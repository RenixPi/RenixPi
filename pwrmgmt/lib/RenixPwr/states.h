#ifndef STATES_H
#define STATES_H

#include <Fsm.h>
#include <Arduino.h>

// Transition callback functions
void on_light_on_enter()
{
  Serial.println("Entering LIGHT_ON");
}

void on_light_on_exit()
{
  Serial.println("Exiting LIGHT_ON");
}

void on_light_off_enter()
{
  Serial.println("Entering LIGHT_OFF");
}

void on_light_off_exit()
{
  Serial.println("Exiting LIGHT_OFF");
}


State state_light_on(&on_light_on_enter, NULL, &on_light_on_exit);
State state_light_off(&on_light_off_enter, NULL, &on_light_off_exit);



#endif
