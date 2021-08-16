from ustruct import unpack

class INA260:

    REG_CONFIG = const(0x00)  # CONFIGURATION REGISTER (R/W)
    REG_CURRENT = const(0x01)  # SHUNT VOLTAGE REGISTER (R)
    REG_BUSVOLTAGE = const(0x02)  # BUS VOLTAGE REGISTER (R)
    REG_POWER = const(0x03)  # POWER REGISTER (R)
    REG_MASK_ENABLE = const(0x06)  # MASK ENABLE REGISTER (R/W)
    REG_ALERT_LIMIT = const(0x07)  # ALERT LIMIT REGISTER (R/W)
    REG_MFG_UID = const(0xFE)  # MANUFACTURER UNIQUE ID REGISTER (R)
    REG_DIE_UID = const(0xFF)  # DIE UNIQUE ID REGISTER (R)

    MV_PER_BIT = 1.25
    MA_PER_BIT = 1.25

    def __init__(self, _address, _i2c):
        self.address = _address
        self.i2c = _i2c


    def get_voltage(self):

        val = self.i2c.readfrom_mem(self.address, self.REG_BUSVOLTAGE, 2)
        val = int.from_bytes(val, "big")  # unpack(">H", val)[0]
        return (self.MV_PER_BIT * val) / 1000

    def get_current(self):

        val = self.i2c.readfrom_mem(self.address, self.REG_CURRENT, 2)
        val = unpack(">h", val)[0]
        return (self.MA_PER_BIT * val) / 1000

