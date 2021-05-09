#ifndef PIDEVICE_H
#define PIDEVICE_H

#include <LowPower.h>
#include <Fsm.h>
#include <Adafruit_INA260.h>


// in mA
#define MIN_POWER_DRAW 300

class PiDevice : public LowPowerClass {

    public:
        PiDevice(String name, int pwr_pin, int shutdown_pin, int running_pin, int current_draw_pin);

        void enablePower();
        void disablePower();
        bool isRunning();
        bool isPoweredOn();
        void shutdown();

        String getName();

        float getCurrentDraw();

    private:
        String m_name;
        int m_pwr_pin;
        int m_shutdown_pin;
        int m_running_pin;
        int m_current_draw_pin;
        Adafruit_INA260 m_ina260;
};


extern PiDevice RenixPi;
extern PiDevice OpenDshPi;
extern Fsm powermgr;



#endif
