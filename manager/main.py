# from machine import Pin
# import pycom
# from machine import I2C
# from time import sleep

# from ina260 import INA260
# from ds3231 import DS3231

# pwr = Pin('P23', mode=Pin.OUT)
# pycom.heartbeat(False)
# pycom.rgbled(0xFF0000)  # Red



# i2c = I2C(0, I2C.MASTER, baudrate=100000)

# ina = INA260(64, i2c)
# ds = DS3231(104, i2c)

# # devices = i2c.scan()

# # for device in devices:
# #     print(device)

# pwr.value(1)
# sleep(0.5)
# # mfg_id = i2c.readfrom_mem(64, _REG_MFG_UID, 2)

from fsm import power_mgr

power_mgr.initialize()



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

