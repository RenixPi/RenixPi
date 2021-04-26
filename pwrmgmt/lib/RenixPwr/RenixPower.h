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

        bool checkRenixRunning(void);
        bool checkOpenDshRunning(void);

        bool checkRenixPower(void);
        bool checkOpenDshPower(void);

        bool shutdownRenix(void);
        bool shutdownOpenDsh(void);

        RenixPowerClass();

    private:
        bool isRenixRunning;
        bool isOpenDshRunning;

        float getRenixCurrent(void);
        float getOpenDshCurrent(void);

};


#endif  //RENIXPOWER_H
