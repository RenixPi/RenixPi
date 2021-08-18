from machine import Pin
from ina260 import INA260

MIN_IDLE_POWER = 2.75

class RaspberryPiException(Exception):
    pass

class RaspberryPi:

    def __init__(self, _enbl, _sdn, _run, _cm_address, _i2c):
        self.enbl = Pin(_enbl, mode=Pin.OUT)
        self.sdn = Pin(_sdn, mode=Pin.OUT)
        self.run = Pin(_run, mode=Pin.IN)
        self.cm = INA260(_cm_address, _i2c)

    def power_off(self):
        self.enbl.value(0)
    
    def power_on(self):
        self.enbl.value(1)

    def get_power(self):
        if not self.is_powered_on():
            raise RaspberryPiException("Not running")
        return self.cm.get_current() * self.cm.get_voltage()

    def is_powered_on(self):
        return self.enbl.value() == 1

    def is_shutdown(self):
        return self.get_power() < MIN_IDLE_POWER
    
    