#ifndef PIDEVICE_H
#define PIDEVICE_H

#include <LowPower.h>
#include <Fsm.h>



#define MIN_POWER_DRAW 200

class PiDevice : public LowPowerClass {

    public:
        PiDevice(String name, int pwr_pin, int shutdown_pin, int running_pin, int current_draw_pin);

        void enablePower();
        void disablePower();
        bool isRunning();
        bool isPoweredOn();
        void shutdown();

        String getName();

    private:
        String m_name;
        int m_pwr_pin;
        int m_shutdown_pin;
        int m_running_pin;
        int m_current_draw_pin;
};


extern PiDevice RenixPi;
extern PiDevice OpenDshPi;
extern Fsm powermgr;



#endif
