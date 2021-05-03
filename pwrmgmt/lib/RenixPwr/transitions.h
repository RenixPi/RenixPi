#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include <LowPower.h>

#define DEBUG

void startup__enter(PiDevice* device) {
    Serial.println("initial state");
}

void pi_off__enter(PiDevice* device) {
    // turn pi power off
    device->disablePower();
    #ifdef DEBUG
    Serial.println(device->getName() + ": powering down, take a nap sleepypi");
    #endif
    delay(1000);


    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

}

void pi_on__enter(PiDevice* device) {
    // turn pi power on
    device->enablePower();
    #ifdef DEBUG
    Serial.println(device->getName() + ": turning on");
    #endif
}

void hold__enter(PiDevice* device) {
    #ifdef DEBUG
    Serial.println(device->getName() + ": entering hold ");
    #endif
}

void start_shutdown__enter(PiDevice* device) {
    //begin shutdown sequence
    device->shutdown();
    #ifdef DEBUG
    Serial.println(device->getName() + ": starting shutdown sequence");
    #endif
}

#endif
