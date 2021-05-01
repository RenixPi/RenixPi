
// State machine variables
#define FLIP_LIGHT_SWITCH 1
#include <SleepyPi2.h>
#include <states.h>

// Transition callback functions

void on_trans_light_on_light_off()
{
  Serial.println("Transitioning from LIGHT_ON to LIGHT_OFF");
}

void on_trans_light_off_light_on()
{
  Serial.println("Transitioning from LIGHT_OFF to LIGHT_ON");
}


Fsm fsm(&state_light_off);


// standard arduino functions
void setup()
{
  Serial.begin(9600);

  fsm.add_transition(&state_light_on, &state_light_off,
                     FLIP_LIGHT_SWITCH,
                     &on_trans_light_on_light_off);
  fsm.add_transition(&state_light_off, &state_light_on,
                     FLIP_LIGHT_SWITCH,
                     &on_trans_light_off_light_on);
}

void loop()
{
  // fsm.run_machine();
  // delay(2000);
  // fsm.trigger(FLIP_LIGHT_SWITCH);
  // delay(2000);
  // fsm.trigger(FLIP_LIGHT_SWITCH);
}