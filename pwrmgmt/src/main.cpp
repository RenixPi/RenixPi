
#include <PinChangeInt.h>

#include <PiDevice.h>
#include <PiFSM.h>
#include <triggers.h>

#define IGNITION_PIN 15

PiDevice renix("renix", RENIX_PWR_PIN, RENIX_SHUTDOWN_PIN, RENIX_RUNNING_PIN, RENIX_I_PIN);
PiDevice opendsh("opendsh", OPENDSH_PWR_PIN, OPENDSH_SHUTDOWN_PIN, OPENDSH_RUNNING_PIN, OPENDSH_I_PIN);

PiFSM renix_fsm(&renix);
PiFSM opendsh_fsm(&opendsh);

void on_wakeup() {
    // when sleepypi wakes from its nap
    Serial.println("waking up");
}

// standard arduino functions
void setup()
{
  Serial.begin(9600);

  // use the ignition power to wake up the sleepypi
  pinMode(IGNITION_PIN, INPUT);
  PCintPort::attachInterrupt(IGNITION_PIN, &on_wakeup, RISING);
}

void loop()
{

  // check timed transitions, execute any in-state callbacks
  renix_fsm.run_machine();
  opendsh_fsm.run_machine();

  // if ignition is on, send trigger
  if(digitalRead(IGNITION_PIN) > 0) {
    renix_fsm.trigger(TRIGGER__IGN_ON);
    opendsh_fsm.trigger(TRIGGER__IGN_ON);
  }

  // if pis are not running, send trigger
  if(!renix.isRunning()) renix_fsm.trigger(TRIGGER__NOT_RUNNING);
  if(!opendsh.isRunning()) opendsh_fsm.trigger(TRIGGER__NOT_RUNNING);

  // if pis are powered off, send trigger
  if(!renix.isPoweredOn()) renix_fsm.trigger(TRIGGER__NOT_POWERED);
  if(!opendsh.isPoweredOn()) opendsh_fsm.trigger(TRIGGER__NOT_POWERED);

}
