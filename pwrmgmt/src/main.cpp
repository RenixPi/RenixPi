
#include <PinChangeInt.h>
#include <RenixPower.h>
#include <PiDevice.h>
#include <states.h>

#define TIME__WAIT_BEFORE_SHUTDOWN (2*6*1000)
#define TIME__WAIT_BEFORE_POWER_OFF (30*1000)
#define IGNITION_PIN 15

PiDevice renix(RENIX_PWR_PIN, RENIX_SHUTDOWN_PIN, RENIX_RUNNING_PIN, RENIX_I_PIN);
PiDevice opendsh(OPENDSH_PWR_PIN, OPENDSH_SHUTDOWN_PIN, OPENDSH_RUNNING_PIN, OPENDSH_I_PIN);

Fsm renix_fsm(&pi_off, &renix);
Fsm opendsh_fsm(&pi_off, &opendsh);

// standard arduino functions
void setup()
{
  Serial.begin(9600);

  // use the ignition power to wake up the sleepypi
  pinMode(IGNITION_PIN, INPUT);
  PCintPort::attachInterrupt(IGNITION_PIN, &on_wakeup, RISING);


  renix_fsm.add_transition(&pi_off, &pi_on, TRIGGER__IGN_ON, NULL);

  renix_fsm.add_transition(&pi_on, &hold, TRIGGER__IGN_OFF, NULL);

  renix_fsm.add_timed_transition(&hold, &start_shutdown, TIME__WAIT_BEFORE_SHUTDOWN, NULL);
  renix_fsm.add_transition(&hold, &pi_on, TRIGGER__IGN_ON, NULL);
  
  renix_fsm.add_timed_transition(&start_shutdown, &pi_off, TIME__WAIT_BEFORE_POWER_OFF, NULL);
  renix_fsm.add_transition(&start_shutdown, &pi_not_running, TRIGGER__NOT_RUNNING, NULL);
  
  renix_fsm.add_transition(&pi_not_running, &pi_off, TRIGGER__NOT_POWERED, NULL);

}

void loop()
{

  renix_fsm.run_machine();
  if(digitalRead(IGNITION_PIN) > 0) {
    renix_fsm.trigger(TRIGGER__IGN_ON);
  }

  if(!RenixPower.isRenixRunning()) {
    renix_fsm.trigger(TRIGGER__NOT_RUNNING);
  }

  if(!RenixPower.isRenixPoweredOn()) {
    renix_fsm.trigger(TRIGGER__NOT_POWERED);
  }

}