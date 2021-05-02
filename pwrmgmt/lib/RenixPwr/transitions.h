#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include <LowPower.h>

void pi_off__enter(PiDevice* device) {
    // turn pi power off
    device->disablePower();
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    #ifdef DEBUG
    Serial.println(device->getName() + ": powering down, take a nap sleepypi");
    #endif
}

void pi_on__enter(PiDevice* device) {
    // turn pi power on
    device->enablePower();
    #ifdef DEBUG
    Serial.println(device->getName() + " turning renix on");
    #endif
}

void start_shutdown__enter(PiDevice* device) {
    //begin shutdown sequence
    device->shutdown();
    #ifdef DEBUG
    Serial.println(device->getName() + " starting shutdown sequence");
    #endif
}

#endif
