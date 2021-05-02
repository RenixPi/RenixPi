#ifndef STATES_H
#define STATES_H

#include <Fsm.h>
#include "triggers.h"
#include "transitions.h"




State pi_off(&pi_off_actions, NULL, NULL);
State pi_on(&pi_on_actions, NULL, NULL);
State hold(NULL, NULL, NULL);
State start_shutdown(&start_shutdown_actions, NULL, NULL);
State pi_not_running(NULL, NULL, NULL);

Fsm power_fsm(&pi_off);

#endif
