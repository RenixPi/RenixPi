#include <PiFSM.h>
#include <triggers.h>
#include <transitions.h>


#define TIME__WAIT_BEFORE_SHUTDOWN (2*6*1000)
#define TIME__WAIT_BEFORE_POWER_OFF (30*1000)

PiFSM::PiFSM(PiDevice* device)
:   pi_off(&pi_off__enter, NULL, NULL),
    pi_on(&pi_on__enter, NULL, NULL),
    hold(NULL, NULL, NULL),
    start_shutdown(&start_shutdown__enter, NULL, NULL),
    pi_not_running(NULL, NULL, NULL),
    Fsm<PiDevice>(&pi_off, device)
 {
  add_transition(&pi_off, &pi_on, TRIGGER__IGN_ON, NULL);

  add_transition(&pi_on, &hold, TRIGGER__IGN_OFF, NULL);

  add_timed_transition(&hold, &start_shutdown, TIME__WAIT_BEFORE_SHUTDOWN, NULL);
  add_transition(&hold, &pi_on, TRIGGER__IGN_ON, NULL);
  
  add_timed_transition(&start_shutdown, &pi_off, TIME__WAIT_BEFORE_POWER_OFF, NULL);
  add_transition(&start_shutdown, &pi_not_running, TRIGGER__NOT_RUNNING, NULL);
  
  add_transition(&pi_not_running, &pi_off, TRIGGER__NOT_POWERED, NULL);
}
