#ifndef STATES_H
#define STATES_H

#include <Fsm.h>
#include "triggers.h"
#include "transitions.h"

State pi_off(&pi_off__enter, NULL, NULL);
State pi_on(&pi_on__enter, NULL, NULL);
State hold(NULL, NULL, NULL);
State start_shutdown(&start_shutdown__enter, NULL, NULL);
State pi_not_running(NULL, NULL, NULL);

#endif
