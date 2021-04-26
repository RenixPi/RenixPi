#include "RenixPower.h"

#define ENABLE_RENIX_PWR_PIN	    16				// PC2;OUT 
#define ENABLE_OPENDSH_PWR_PIN	    4				// PD4;OUT
#define RENIX_SHUTDOWN_PIN          17				// PC3;OUT
#define RENIX_RUNNING_PIN    		7				// PD7:IN
#define OPENDSH_SHUTDOWN_PIN        00              // Pxx:OUT
#define OPENDSH_RUNNING_PIN         00              // Pxx:IN
#define V_SUPPLY_PIN        		A6				// IN
#define I_RENIX_PIN 		        A7				// IN
#define I_OPENDSH_PIN               A0              // IN

#define RENIX_MIN_CURRENT_DRAW      100
#define OPENDSH_MIN_CURRENT_DRAW    100

RenixPowerClass::RenixPowerClass() {

    isRenixRunning = false;
    isOpenDshRunning = false;


    pinMode(ENABLE_RENIX_PWR_PIN, OUTPUT);
    pinMode(ENABLE_OPENDSH_PWR_PIN, OUTPUT);

    RenixPowerClass::enableRenixPower(false);
    RenixPowerClass::enableOpenDshPower(false);

}

void RenixPowerClass::enableRenixPower(bool enable) {
    if(enable == true) {
        digitalWrite(ENABLE_RENIX_PWR_PIN, HIGH);
        return;
    }

    digitalWrite(ENABLE_RENIX_PWR_PIN, LOW);
    return;
}

void RenixPowerClass::enableOpenDshPower(bool enable) {
    if(enable == true) {
        digitalWrite(ENABLE_OPENDSH_PWR_PIN, HIGH);
        return;
    }

    digitalWrite(ENABLE_OPENDSH_PWR_PIN, LOW);
}

bool RenixPowerClass::checkRenixRunning(void) {
    int handshake;

    handshake = digitalRead(RENIX_RUNNING_PIN);

    if(handshake > 0) {
        return true;
    }

    return false;
}

bool RenixPowerClass::checkOpenDshRunning(void) {
    int handshake;

    handshake = digitalRead(OPENDSH_RUNNING_PIN);

    if(handshake > 0) {
        return true;
    }

    return false;
}

bool RenixPowerClass::checkRenixPower(void) {
    float renix_current = 0.0;

    renix_current = RenixPowerClass::getRenixCurrent();

    return renix_current > RENIX_MIN_CURRENT_DRAW;
}

bool RenixPowerClass::checkOpenDshPower(void) {
    float opendsh_current = 0.0;

    opendsh_current = RenixPowerClass::getOpenDshCurrent();

    return opendsh_current > OPENDSH_MIN_CURRENT_DRAW;
}




