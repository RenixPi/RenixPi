
#include <PinChangeInt.h>
#define DEBUG

#include <PiDevice.h>
#include <states.h>
#include <transitions.h>
#include <triggers.h>
#include <SleepyPi2.h>
#include <Adafruit_INA260.h>

#define TIME__WAIT_BEFORE_SHUTDOWN (6*1000)
#define TIME__WAIT_BEFORE_POWER_OFF (30*1000)

Adafruit_INA260 ina260 = Adafruit_INA260();

void initial__enter() {
  #ifdef DEBUG
  Serial.println("initial state");
  #endif
  //pis should start off
  RenixPi.disablePower();
  OpenDshPi.disablePower();
}
State initial(&initial__enter, NULL, NULL);
Fsm powermgr(&initial);

void pi_off__enter() {
  Serial.println("pis are off");

  //should already be off, just in case
  RenixPi.disablePower();
  OpenDshPi.disablePower();
}

void pi_off__actions() {
  if(digitalRead(IGNITION_PIN) > 0) {
    powermgr.trigger(TRIGGER__IGN_ON);
  } else {
    powermgr.trigger(TRIGGER__IGN_OFF);
  }
}

void sleep__enter() {
  #ifdef DEBUG
  Serial.println("taking a nap");
  // Serial.println(SleepyPi.supplyVoltage());
  // Serial.println(SleepyPi.rpiCurrent());
  // Serial.println(RenixPi.getCurrentDraw());
  // Serial.println(OpenDshPi.getCurrentDraw());
  #endif
  delay(500);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

void pi_on__enter() {
    // turn pi power on
    RenixPi.enablePower();
    OpenDshPi.enablePower();
    #ifdef DEBUG
    Serial.println("turning on");
    #endif
    delay(100);
    if (!ina260.begin()) {
      Serial.println("Couldn't find INA260 chip");
    } else {
      Serial.println("Found INA260 chip");
    }
}

void hold__enter() {
    #ifdef DEBUG
    Serial.println("entering hold ");
    Serial.print(RenixPi.getCurrentDraw());
    Serial.print("\t\t");
    Serial.println(OpenDshPi.getCurrentDraw());
    #endif
}

void start_shutdown__enter() {
    //begin shutdown sequence
    RenixPi.shutdown();
    OpenDshPi.shutdown();
    #ifdef DEBUG
    Serial.println("starting shutdown sequence");
    #endif
}

void start_shutdown__actions() {
  if(!RenixPi.isRunning() && !OpenDshPi.isRunning()) {
    #ifdef DEBUG
    Serial.println("both pis are not running");
    #endif
    powermgr.trigger(TRIGGER__NOT_RUNNING);
  }
}

void not_running__enter() {
  #ifdef DEBUG
  Serial.println("not running");
  #endif
}

void not_running__actions() {
  #ifdef DEBUG
    // Serial.println("not running");
    // Serial.print(RenixPi.getCurrentDraw());
    // Serial.print("\t\t");
    // Serial.println(OpenDshPi.getCurrentDraw());
    // delay(500);
  #endif

  if(!RenixPi.isPoweredOn() && !OpenDshPi.isPoweredOn()) {
    #ifdef DEBUG
    Serial.println("both pis are powered off");
    #endif
    powermgr.trigger(TRIGGER__NOT_POWERED);
  }
}

void not_powered__enter() {
  #ifdef DEBUG
  Serial.println("not powered, turning power off");
  #endif
  RenixPi.disablePower();
  OpenDshPi.disablePower();
}

void not_responsive() {
  #ifdef DEBUG
  Serial.println("not responsive, turn off");
  #endif
}

void on_wakeup() {
    // when sleepypi wakes from its nap
    #ifdef DEBUG
    // Serial.println("waking up");
    #endif
}

State pi_off(&pi_off__enter, &pi_off__actions, NULL);
State sleep(&sleep__enter, NULL, NULL);
State pi_on(&pi_on__enter, NULL, NULL);
State hold(&hold__enter, NULL, NULL);
State start_shutdown(&start_shutdown__enter, &start_shutdown__actions, NULL);
State not_running(&not_running__enter, &not_running__actions, NULL);
State not_powered(&not_powered__enter, NULL, NULL);



// initial configuration
void setup()
{
  Serial.begin(9600);
  Serial.println("starting...");

  // use the ignition power to wake up the sleepypi
  pinMode(IGNITION_PIN, INPUT);
  PCintPort::attachInterrupt(IGNITION_PIN, &on_wakeup, RISING);

  //state: initial
  powermgr.add_timed_transition(&initial, &pi_off, 1, NULL);

  //state: pi_off
  powermgr.add_transition(&pi_off, &sleep, TRIGGER__IGN_OFF, NULL);
  powermgr.add_transition(&pi_off, &pi_on, TRIGGER__IGN_ON, NULL);

  //state: sleep
  powermgr.add_transition(&sleep, &pi_on, TRIGGER__IGN_ON, NULL);

  //state: pi_on
  powermgr.add_transition(&pi_on, &hold, TRIGGER__IGN_OFF, NULL);

  //state: hold
  powermgr.add_timed_transition(&hold, &start_shutdown, TIME__WAIT_BEFORE_SHUTDOWN, NULL);
  powermgr.add_transition(&hold, &pi_on, TRIGGER__IGN_ON, NULL);
  
  //state: start shutdown
  powermgr.add_transition(&start_shutdown, &not_running, TRIGGER__NOT_RUNNING, NULL);
  powermgr.add_timed_transition(&start_shutdown, &pi_off, TIME__WAIT_BEFORE_POWER_OFF, &not_responsive);
  
  //state: not running
  powermgr.add_transition(&not_running, &not_powered, TRIGGER__NOT_POWERED, NULL);
  powermgr.add_timed_transition(&not_running, &pi_off, TIME__WAIT_BEFORE_POWER_OFF, &not_responsive);

  //state: not powered
  powermgr.add_timed_transition(&not_powered, &pi_off, 500, NULL);

}

void loop()
{

  // check timed transitions, execute any in-state callbacks
  powermgr.run_machine();

  // if ignition is on, send trigger
  if(digitalRead(IGNITION_PIN) > 0) {
    powermgr.trigger(TRIGGER__IGN_ON);
  } else {
    powermgr.trigger(TRIGGER__IGN_OFF);
  }

  if(OpenDshPi.isRunning()) {
    Serial.println("opendsh now running");
  }

  delay(1000);
}
