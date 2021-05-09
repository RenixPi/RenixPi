#include "CurrentMon.h"

MAX417CurrentMon :: MAX417CurrentMon(int pin) 
  : CurrentMon(),
    m_pin(pin) 
{
    pinMode(m_pin, INPUT);
}

float MAX417CurrentMon :: getCurrentDraw() {
   float i;
    
    // 10-bit ADC resolution = 3.3 / 1024 = 3.22mV
    i = 3.22 * (float)analogRead(m_pin);

    return i;
}


INA260CurrentMon :: INA260CurrentMon()
: CurrentMon(),
  ina260(Adafruit_INA260()) {

}

float INA260CurrentMon :: getCurrentDraw() {
    ina260.begin();
    return ina260.readCurrent();
}
