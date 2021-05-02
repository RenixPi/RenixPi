#ifndef PIFSM_H
#define PIFSM_H

#include <Fsm.h>
#include <PiDevice.h>


class PiFSM : public Fsm<PiDevice> {
    public: 
        PiFSM(PiDevice* device);

        State<PiDevice> pi_off;
        State<PiDevice> pi_on;
        State<PiDevice> hold;
        State<PiDevice> start_shutdown;
        State<PiDevice> pi_not_running;

};


#endif