#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include <SleepyPi2.h>
#include <RenixPower.h>

void pi_off__enter(PiDevice* device) {
    // turn pi power off
    device->disablePower();
    RenixPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    Serial.println(device->getName() + ": powering down, take a nap sleepypi");
}

void pi_on__enter(PiDevice* device) {
    // turn pi power on
    device->enablePower();
    Serial.println(device->getName() + " turning renix on");
}

void start_shutdown__enter(PiDevice* device) {
    //begin shutdown sequence
    device->shutdown();
    Serial.println(device->getName() + " starting shutdown sequence");
}

#endif
