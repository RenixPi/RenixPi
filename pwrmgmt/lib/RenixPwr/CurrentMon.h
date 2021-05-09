#ifndef CURRENTMON_H
#define CURRENTMON_H

#include <Adafruit_INA260.h>

class CurrentMon {
    public:
        virtual float getCurrentDraw() {
            return -1;
        };

};

class MAX417CurrentMon : public CurrentMon {
    public:
        MAX417CurrentMon(int pin);
        float getCurrentDraw();
    private:
        int m_pin;
};

class INA260CurrentMon : public CurrentMon {
    public:
        INA260CurrentMon();
        float getCurrentDraw();
    private:
        Adafruit_INA260 ina260;
};

#endif
