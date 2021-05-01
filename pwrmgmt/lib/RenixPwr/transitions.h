#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include <SleepyPi2.h>

void pi_off_actions() {
    // turn pi power off
    SleepyPi.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

void pi_on_actions() {
    // turn pi power on
}





#endif