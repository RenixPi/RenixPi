#include "PiDevice.h"
#include "pins.h"
#include "states.h"



PiDevice::PiDevice(String name, int pwr_pin, int shutdown_pin, int running_pin, int current_draw_pin) :
m_name(name),
m_pwr_pin(pwr_pin),
m_shutdown_pin(shutdown_pin),
m_running_pin(running_pin),
m_current_draw_pin(current_draw_pin)
{
    pinMode(m_pwr_pin, OUTPUT);
    pinMode(m_shutdown_pin, OUTPUT);
    pinMode(m_running_pin, INPUT);
    pinMode(m_current_draw_pin, INPUT);

    disablePower();
}

void PiDevice::enablePower() {
    digitalWrite(m_shutdown_pin, LOW);
    digitalWrite(m_pwr_pin, HIGH);
}

void PiDevice::disablePower() {
    digitalWrite(m_pwr_pin, LOW);
}

bool PiDevice::isRunning() {
    return digitalRead(m_running_pin) > 0;
}

bool PiDevice::isPoweredOn() {
    return analogRead(m_current_draw_pin) > MIN_POWER_DRAW;
}

void PiDevice::shutdown() {
    digitalWrite(m_shutdown_pin, HIGH);
}

String PiDevice::getName() {
    return m_name;
}

PiDevice RenixPi("renix", RENIX_PWR_PIN, RENIX_SHUTDOWN_PIN, RENIX_RUNNING_PIN, RENIX_I_PIN);
PiDevice OpenDshPi("opendsh", OPENDSH_PWR_PIN, OPENDSH_SHUTDOWN_PIN, OPENDSH_RUNNING_PIN, OPENDSH_I_PIN);


