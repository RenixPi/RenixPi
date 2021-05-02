#ifndef PIDEVICE_H
#define PIDEVICE_H

#include <LowPower.h>

#define RENIX_PWR_PIN	    16				// PC2;OUT 
#define OPENDSH_PWR_PIN	    13				// LED;OUT
#define RENIX_SHUTDOWN_PIN          17				// PC3;OUT
#define RENIX_RUNNING_PIN    		7				// PD7:IN
#define OPENDSH_SHUTDOWN_PIN        5              // Pxx:OUT
#define OPENDSH_RUNNING_PIN         6              // Pxx:IN
#define V_SUPPLY_PIN        		A6				// IN
#define RENIX_I_PIN 		        A7				// IN
#define OPENDSH_I_PIN               A0              // IN

#define MIN_POWER_DRAW 100

class PiDevice : public LowPowerClass {

    public:
        PiDevice(int pwr_pin, int shutdown_pin, int running_pin, int current_draw_pin);

        void enablePower();
        void disablePower();
        bool isRunning();
        bool isPoweredOn();
        void shutdown();

    private:
        int m_pwr_pin;
        int m_shutdown_pin;
        int m_running_pin;
        int m_current_draw_pin;

        float getCurrentDraw();

};

#endif
