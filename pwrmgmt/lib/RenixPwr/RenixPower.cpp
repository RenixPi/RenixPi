#include "RenixPower.h"

#define ENABLE_RENIX_PWR_PIN	    16				// PC2;OUT 
#define ENABLE_OPENDSH_PWR_PIN	    13				// LED;OUT
#define RENIX_SHUTDOWN_PIN          17				// PC3;OUT
#define RENIX_RUNNING_PIN    		7				// PD7:IN
#define OPENDSH_SHUTDOWN_PIN        5              // Pxx:OUT
#define OPENDSH_RUNNING_PIN         6              // Pxx:IN
#define V_SUPPLY_PIN        		A6				// IN
#define I_RENIX_PIN 		        A7				// IN
#define I_OPENDSH_PIN               A0              // IN

#define RENIX_MIN_CURRENT_DRAW      100
#define OPENDSH_MIN_CURRENT_DRAW    100

RenixPowerClass::RenixPowerClass() {

    pinMode(ENABLE_RENIX_PWR_PIN, OUTPUT);
    pinMode(ENABLE_OPENDSH_PWR_PIN, OUTPUT);

    pinMode(RENIX_RUNNING_PIN, INPUT);
    pinMode(OPENDSH_RUNNING_PIN, INPUT);

    pinMode(RENIX_SHUTDOWN_PIN, OUTPUT);
    pinMode(OPENDSH_SHUTDOWN_PIN, OUTPUT);

    RenixPowerClass::enableRenixPower(false);
    RenixPowerClass::enableOpenDshPower(false);

}

void RenixPowerClass::enableRenixPower(bool enable) {
        digitalWrite(RENIX_SHUTDOWN_PIN, LOW);
        digitalWrite(ENABLE_RENIX_PWR_PIN, HIGH);
}

void RenixPowerClass::enableOpenDshPower(bool enable) {
        digitalWrite(OPENDSH_SHUTDOWN_PIN, LOW);
        digitalWrite(ENABLE_OPENDSH_PWR_PIN, HIGH);
}

bool RenixPowerClass::isRenixRunning() {
    return digitalRead(RENIX_RUNNING_PIN) > 0;
}

bool RenixPowerClass::isOpenDshRunning() {
    return digitalRead(OPENDSH_RUNNING_PIN) > 0;
}

bool RenixPowerClass::isRenixPoweredOn(void) {
    float renix_current = 0.0;

    renix_current = RenixPowerClass::getRenixCurrent();

    return renix_current > RENIX_MIN_CURRENT_DRAW;
}

bool RenixPowerClass::isOpenDshPoweredOn(void) {
    float opendsh_current = 0.0;

    opendsh_current = RenixPowerClass::getOpenDshCurrent();

    return opendsh_current > OPENDSH_MIN_CURRENT_DRAW;
}

void RenixPowerClass::shutdownOpenDsh() {
    digitalWrite(OPENDSH_SHUTDOWN_PIN, HIGH);
}

void RenixPowerClass::shutdownRenix() {
    digitalWrite(RENIX_SHUTDOWN_PIN, HIGH);
}

float RenixPowerClass::getRenixCurrent() {
    return analogRead(I_RENIX_PIN);
}

float RenixPowerClass::getOpenDshCurrent() {
    return analogRead(I_OPENDSH_PIN);
}

RenixPowerClass RenixPower;
