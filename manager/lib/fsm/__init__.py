from pysm import StateMachine
from .states import *

power_mgr = StateMachine('root_machine')

pi_off_state = PiOff('PI_OFF')
pi_on_state = PiOn('PI_ON')
sleep_state = Sleep('SLEEP')
hold_state = Hold('HOLD')
start_shutdown_state = StartShutdown('START_SDN')
wait_for_shutdown_state = WaitForShutdown('WAIT4SDN')
shutdown_confirm_state = ShutdownConfirmed('SDN_CONFIRM')


power_mgr.add_state(pi_off_state, initial=True)
power_mgr.add_state(sleep_state)
power_mgr.add_state(pi_on_state)
power_mgr.add_state(hold_state)
power_mgr.add_state(wait_for_shutdown_state)
power_mgr.add_state(shutdown_confirm_state)


power_mgr.add_transition(pi_off_state,   sleep_state,     events=['ign_off', ])
power_mgr.add_transition(pi_off_state,   pi_on_state,     events=['ign_on', ])
power_mgr.add_transition(sleep_state,    pi_on_state,     events=['ign_on', ])



