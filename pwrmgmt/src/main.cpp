
#include <states.h>

#define HOLD_BEFORE_SHUTDOWN 2*60*1000

// standard arduino functions
void setup()
{
  Serial.begin(9600);

  power_fsm.add_transition(&pi_off, &pi_on, IGN_ON, NULL);

  power_fsm.add_transition(&pi_on, &hold, IGN_OFF, NULL);

  power_fsm.add_timed_transition(&hold, &start_shutdown, HOLD_BEFORE_SHUTDOWN, NULL);
  power_fsm.add_transition(&hold, &pi_on, IGN_ON, NULL);
  
  power_fsm.add_timed_transition(&start_shutdown, &pi_off, 30*1000, NULL);
  power_fsm.add_transition(&start_shutdown, &pi_not_running, NOT_RUNNING, NULL);
  
  power_fsm.add_transition(&pi_not_running, &pi_off, NOT_POWERED, NULL);

}

void loop()
{
  // fsm.run_machine();
  // delay(2000);
  // fsm.trigger(FLIP_LIGHT_SWITCH);
  // delay(2000);
  // fsm.trigger(FLIP_LIGHT_SWITCH);
}