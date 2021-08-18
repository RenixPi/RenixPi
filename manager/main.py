import pycom
from machine import I2C

import pins
import address
from raspberrypi import RaspberryPi

# from ds3231 import DS3231


pycom.heartbeat(False)
pycom.rgbled(0xFF0000)  # Red

i2c = I2C(0, I2C.MASTER, baudrate=100000)

rnx_pi = RaspberryPi(pins.RNX_ENBL, pins.RNX_SDN, pins.RNX_RUN, address.RNX_CM, i2c)
odsh_pi = RaspberryPi(pins.ODSH_ENBL, pins.ODSH_SDN, pins.ODSH_RUN, address.ODSH_CM, i2c)






# ina = INA260(64, i2c)
# ds = DS3231(104, i2c)

# from fsm import power_mgr

# power_mgr.initialize()



# state_machine.add_state(state_off, initial=True)
# state_machine.add_state(state_on)
# state_machine.add_state(state_standby)

# state_machine.add_transition(state_on, state_off, events=['off'])
# state_machine.add_transition(state_off, state_on, events=['on'])
# state_machine.add_transition(state_on, state_standby, condition=standby_condition, events=['event1', 'event2'])
# state_machine.add_transition(state_standby, state_on, events=[''])
# state_machine.add_transition(state_standby, state_on, events=['on'])

# state_machine.initialize()
# state_machine.dispatch(Event('on'))
# state_machine.dispatch(Event('event1', item='cargo2'))

