from machine import Pin
import pycom
from machine import I2C
from time import sleep

from ina260 import INA260
from ds3231 import DS3231

pwr = Pin('P23', mode=Pin.OUT)
pycom.heartbeat(False)
pycom.rgbled(0xFF0000)  # Red



i2c = I2C(0, I2C.MASTER, baudrate=100000)

ina = INA260(64, i2c)
ds = DS3231(104, i2c)

# devices = i2c.scan()

# for device in devices:
#     print(device)

pwr.value(1)
sleep(0.5)
# mfg_id = i2c.readfrom_mem(64, _REG_MFG_UID, 2)


    