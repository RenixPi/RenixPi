from pysm import StateMachine
from .states import InitialPowerUp

power_mgr = StateMachine('root_machine')

initial_power_up = InitialPowerUp('InitialPowerUp')

power_mgr.add_state(initial_power_up, initial=True)

