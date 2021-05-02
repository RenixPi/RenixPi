#ifndef PIFSM_H
#define PIFSM_H

#include <Fsm.h>
#include <PiDevice.h>

class PiFSM : public Fsm {
    public: 
        PiFSM(State* initial_state, PiDevice* device);
    private:
        PiDevice* m_device;
        State pi_off;
        State pi_on;
        State hold;
        State start_shutdown;
        State pi_not_running;
};


#endif