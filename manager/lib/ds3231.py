import time
from ustruct import pack, unpack


REG_TIME_SECONDS = 0x00
REG_TIME_MINUTES = 0x01
REG_TIME_HOURS = 0x02
REG_TIME_DAY = 0x03
REG_TIME_DATE = 0x04
REG_TIME_MONTHS = 0x05
REG_TIME_YEARS = 0x06



MASK_SECONDS = 0x7F
MASK_MINUTES = 0x7F
MASK_HOURS = 0x3F
MASK_DAY = 0x07
MASK_DATE = 0x3F
MASK_MONTHS = 0x1F
MASK_YEARS = 0xFF


def bcd2bin(value):
    # ((value & 0x70) >> 4) * 10 + (value & 0x0F)
    return value - 6 * (value >> 4)

def bin2bcd(value):
    # (value // 10) << 4 + value & 0x0F
    return value + 6 * (value // 10)


class DS3231:

    def __init__(self, _address, _i2c):
        self.address = _address
        self.i2c = _i2c

    def get_byte(self, register):
        val = self.i2c.readfrom_mem(self.address, register, 1)
        return unpack(">B", val)[0] # int.from_bytes(val, "big")

    def set_byte(self, register, value):
        val = pack(">B", value)
        self.i2c.writeto_mem(self.address, register, val)

    def get_bit(self, register, bit):
        val = self.get_byte(register)
        res = (val >> bit) & 0x01
        return res

    def is_mode24(self):
        return self.get_bit(REG_TIME_HOURS, 6)

    def get_seconds(self):
        return bcd2bin(self.get_byte(REG_TIME_SECONDS) & MASK_SECONDS)

    def set_seconds(self, value):
        self.set_byte(REG_TIME_SECONDS, bin2bcd(value))

    def get_minutes(self):
        return bcd2bin(self.get_byte(REG_TIME_MINUTES) & MASK_MINUTES)

    def set_minutes(self, value):
        self.set_byte(REG_TIME_MINUTES, bin2bcd(value))

    def get_hours(self):
        return bcd2bin(self.get_byte(REG_TIME_HOURS) & MASK_HOURS)

    def set_hours(self, value):
        self.set_byte(REG_TIME_HOURS, bin2bcd(value))

    def get_date(self):
        return bcd2bin(self.get_byte(REG_TIME_DATE) & MASK_DATE)

    def set_date(self, value):
        self.set_byte(REG_TIME_DATE, bin2bcd(value))

    def get_months(self):
        return bcd2bin(self.get_byte(REG_TIME_MONTHS) & MASK_MONTHS)

    def set_months(self, value):
        self.set_byte(REG_TIME_MONTHS, bin2bcd(value))

    def get_years(self):
        return bcd2bin(self.get_byte(REG_TIME_YEARS) & MASK_YEARS) + 2000

    def set_years(self, value):
        self.set_byte(REG_TIME_YEARS, bin2bcd(value - 2000))
    
    def get_datetime(self):
        return (
            self.get_years(),
            self.get_months(),
            self.get_date(),
            self.get_hours(),
            self.get_minutes(),
            self.get_seconds(),
            0,
            0,
            None
        )


