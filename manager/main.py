import pycom

import pins
import address
from raspberrypi import RaspberryPi

from fsm import power_mgr


pycom.heartbeat(False)
pycom.rgbled(0xFF0000)  # Red

# rnx_pi = RaspberryPi(pins.RNX_ENBL, pins.RNX_SDN, pins.RNX_RUN, address.RNX_CM, i2c)
# odsh_pi = RaspberryPi(pins.ODSH_ENBL, pins.ODSH_SDN, pins.ODSH_RUN, address.ODSH_CM, i2c)

power_mgr.initialize()


def init_pin_handler():
    pass


async def pin_handler(pin):
    # disable the callback
    pin.callback = None
    lvl = pin_in()
    print("pin state is: {}".format(lvl)
    await uasyncio.sleep_ms(100)
    lvl = pin_in()
    print("pin state is: {}".format(lvl)
    return lvl


async def main():
    p_in = Pin('P', mode=Pin.IN)
    p_in.callback(Pin.IRQ_FALLING | Pin.IRQ_RISING, pin_handler)

    while True:
        await asyncio.sleep_ms(10)
    
uasyncio.run(main())
