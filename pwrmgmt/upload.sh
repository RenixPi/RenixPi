/usr/share/arduino/hardware/tools/avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -patmega328p -carduino -P/dev/ttyS0 -b57600 -D -Uflash:w:.pio/fio/firmware.hex:i 

