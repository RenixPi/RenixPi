#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include <SleepyPi2.h>
#include <RenixPower.h>

void pi_off__enter(PiDevice* device) {
    // turn pi power off
    RenixPower.enableRenixPower(false);
    RenixPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    Serial.println("powering down renix");
}

void pi_on__enter(PiDevice* device) {
    // turn pi power on
    RenixPower.enableRenixPower(true);
    Serial.println("turning renix on");
}

void start_shutdown__enter(PiDevice* device) {
    //begin shutdown sequence
    RenixPower.shutdownRenix();
}

void on_wakeup() {
    // when sleepypi wakes from its nap
    Serial.println("waking up");
}

#endif
