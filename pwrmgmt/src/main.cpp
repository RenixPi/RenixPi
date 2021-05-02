
#include <PinChangeInt.h>
#include <RenixPower.h>
#include <states.h>

#define TIME__WAIT_BEFORE_SHUTDOWN (2*6*1000)
#define TIME__WAIT_BEFORE_POWER_OFF (30*1000)
#define IGNITION_PIN 15

// standard arduino functions
void setup()
{
  Serial.begin(9600);

  // use the ignition power to wake up the sleepypi
  pinMode(IGNITION_PIN, INPUT);
  PCintPort::attachInterrupt(IGNITION_PIN, &on_wakeup, RISING);


  power_fsm.add_transition(&pi_off, &pi_on, TRIGGER__IGN_ON, NULL);

  power_fsm.add_transition(&pi_on, &hold, TRIGGER__IGN_OFF, NULL);

  power_fsm.add_timed_transition(&hold, &start_shutdown, TIME__WAIT_BEFORE_SHUTDOWN, NULL);
  power_fsm.add_transition(&hold, &pi_on, TRIGGER__IGN_ON, NULL);
  
  power_fsm.add_timed_transition(&start_shutdown, &pi_off, TIME__WAIT_BEFORE_POWER_OFF, NULL);
  power_fsm.add_transition(&start_shutdown, &pi_not_running, TRIGGER__NOT_RUNNING, NULL);
  
  power_fsm.add_transition(&pi_not_running, &pi_off, TRIGGER__NOT_POWERED, NULL);

}

void loop()
{

  power_fsm.run_machine();
  if(digitalRead(IGNITION_PIN) > 0) {
    power_fsm.trigger(TRIGGER__IGN_ON);
  }

  if(!RenixPower.isRenixRunning()) {
    power_fsm.trigger(TRIGGER__NOT_RUNNING);
  }

  if(!RenixPower.isRenixPoweredOn()) {
    power_fsm.trigger(TRIGGER__NOT_POWERED);
  }

}