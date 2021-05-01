#ifndef RENIXPOWER_H
#define RENIXPOWER_H

#include "Arduino.h"
#include <Wire.h>
#include <LowPower.h>
#include <PCF8523.h>
#include <TimeLib.h>


class RenixPowerClass : public PCF8523 , public LowPowerClass {

    public:

        void enableRenixPower(bool enable);
        void enableOpenDshPower(bool enable);

        bool isRenixRunning();
        bool isOpenDshRunning();

        bool isRenixPoweredOn();
        bool isOpenDshPoweredOn();

        void shutdownRenix();
        void shutdownOpenDsh();

        RenixPowerClass(bool x);

    private:
    
        float getRenixCurrent(void);
        float getOpenDshCurrent(void);

};

extern RenixPowerClass RenixPower;

#endif  //RENIXPOWER_H
