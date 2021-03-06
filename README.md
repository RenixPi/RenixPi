# Getting Started

> TODO
> Create an `.img` that be used to create SD Card with the [RaspberryPi Imager](https://www.raspberrypi.org/software/).

![](<docs/renixpi.png>)

# Renix History

A declining economy coupled with the soaring energy prices of the 1970s, American Motor Corporation (AMC)
struggled in 1980. Their vehicle lineup wasn't able to keep pace with General Motors, Chrysler and Ford. And
Japanese imports were now being produced domestically in highly efficient assembly plants.

Not able to secure loans from traditional sources, Renault provided funding to keep AMC going and eventually
acquired more than 50% of the company by 1982. The company turned focus to its Jeep brand with down-sized versions
of other models; the Wagoneer and Cherokee -- launched in 1983 -- created an entirely new sports utility vehicle
class of cars.  

Initially, these vehicles had a 2.5L inline-4 AMC engine or a GM-made 2.8L V6, both naturally aspirated with
a carburetor. In 1987, Jeep and Renault designed an inline, 6-cylinder engine. Drawing from another Renault joint
venture with aerospace company Bendix, they outfitted both the 2.5L and 4L engine with an electronic fuel injection
system. Renault-Bendix was shortened to Renix.

When Chysler acquired Jeep in 1991, they replaced the engine management system with their own ECU. However, 
during just those four years of production, Jeep sold a combined *1.1 million* Wagoneers, 
Cherokees (XJ) and Comanches (MJ) with the Renix system.

## Engine management protocols

While the On Board Diagnostic (OBD) protocol was established by [SAE in 1979](https://www.sae.org/standards/content/j1979_201202/),
it wasn't until 1994, when California emissions regulations mandated it be included on all vehicles, that it became the
industry standard now known as OBD-II.

Between 1979 and 1994, most companies used some portion of the OBD standard. Renix did not, charting their
own path with a proprietary format.

## Reverse engineering of the Renix protocol

While some commercially available diagnostic tools were made for mechanics, the protocol was never published. In 2012, a video by
[Phil Andrews of the RenixPower forum](https://www.youtube.com/watch?v=AUqQrLLVdZ8) demonstrated his hard work in decoding the protocol.

Following that, [Nick Grisley of NickInTimeDesign](http://nickintimedesign.com) started developing the
[Renix Engine Monitor](https://nickintimedesign.com/product/renix-engine-monitor-ii/) in 2016 and has been generous to
share the source code as an open source project. There are several videos on his website that show the extensive sleuthing
that was needed to arrive in his latest iteration. I've purchased one and I've been very impressed, it works great!

This project is an extension of both Phil and Nick's *tremendous* efforts and would not have been possible without them.

### Sources

- [Automotive History Preservation Society](http://wildaboutcarsonline.com/cgi-bin/pub9990262549620.cgi?itemid=9990287331811&action=viewad&categoryid=9990279027328&page=1&placeonpage=6&totaldisplayed=50)
- [Renix Wikipedia](https://en.wikipedia.org/wiki/Renix)
- [OBD Wikipedia](https://en.wikipedia.org/wiki/On-board_diagnostics)
- [Origins by NickInTimeDesign](https://nickintimedesign.com/where-it-all-began/)

# Electronics

The ECU serial data connection is a fairly standard interface (open-collector to ground)
which isn't dependent on the voltage of the connected electronics. Parts that are needed

- raspberry pi ~$35
- display (minimum 480x320 resolution) ~$20
- transistor (eg 2N2309) < $1
- resistors (eg 4 x 1K ohm) < $1
- power supply (see notes)  ~$4
- diagnostic connector ~$5
- wire

![](<docs/schematic.png>)


## ECU Diagnostic Connector

The diagnostic connector in the vehicle is a standard 15-pin Molex connector; receptacle with female 0.093" pins. To connect, you'll
need the [plug](<docs/molex-plug.jpeg>) (top right) with [male pins](<docs/molex-pin.jpeg>) (bottom left).

![](<docs/molex.jpeg>)

## Power supply

The RaspberryPi requires a 5V supply but its input pins are limited to 3.3V so the UART connection
needs this lower Vdd pull-up voltage.

**Option 1** Use Vdd from the power pins of the Raspberry Pi and level shift
the UART using a zener diode (1N4619) and a 100 ohm resistor.

![](<docs/schematic-levelshift.png>)

**Option 2** Amazon or Ebay (among others) have dc-to-dc step down converters based on the
LM2596 and cost about $12 for a pack of 6. One should be adjusted to 5V and the other
to 3.3V.

**Option 3** The RaspberryPi can be powered by a USB charging port (5V) from a cigarette lighter
adapter supplying at least 2A. While the 3.3V regulator on the RaspberryPi isn't easily accessible
through the GPIO header, it might be possible to get the right voltage by configuring an output pin
and setting it to '1'. The max current is only 17 mA but, in theory, that should be enough
to activate the 2N2309 transistor.

# Software

![](<docs/renixpi-arch.png>)

## Install

Assumes that you are using a RaspberryPI Desktop OS image that already has `git` and `python3` installed. From either a 
terminal window or command prompt via ssh:

1. clone [RenixPi](https://github.com/RenixPi/RenixPi.git)
1. install `ansible` with `pip3 install ansible`
1. `cd RenixPi/config` and run `ansible-playbook renix.yml` which will clone 
   [RenixMonitor](https://github.com/RenixPi/RenixMonitor.git) and [RenixDisplay](https://github.com/RenixPi/RenixDisplay.git)
   along with installing their dependencies.
1. `cd RenixMonitor`
1. `python3 main.py --baudrate 62500 --interface /dev/ttyAMA1 &`
1. `cd ../RenixDisplay`
1. `npm run prod` (or `npm run build` followed by `npm run launch`)

Note: on the RaspberryPi 4, there are more than two uarts so you may need to adjust the interface depending on your configuration. 

## RenixMonitor

Decodes serial data stream from Renix ECU. Python. Supports both python3 and micropython.

https://github.com/RenixPi/RenixMonitor

## RenixDisplay

Electron app built with React, Redux and RxJS. Javascript. Displays information coming from RenixMonitor and any other
MQTT source.

https://github.com/RenixPi/RenixDisplay

# Configuration

### Ethernet

No configuration necessary.

### Wireless

In the base directory of the SD card, rename `wpa_supplicant.txt` to `wpa_supplicant.conf` and change the SSID and wifi password.

### SSH

> TODO

`ssh pi@renix.local`

### Display

- size
- orientation

> TODO

### Engine Type

Currently, only 4L M/T is supported.

*Like to see this implemented? Request with a github issue!*

> TODO

#### UART

> TODO

#### TPMS (optional)

> TODO

#### Other (optional)

> TODO


# References

```
>>> # create virtual serial port
>>> socat -d -d pty,raw,echo=0 pty,raw,echo=0
```

```
>>> # run ansible to set up user and ssh config
>>> ansible-playbook -i hosts raspi.yml
```

```
>>> # run ansible to set up renix dependencies
>>> ansible-playbook -i hosts renix.yml
```

```
>>> # run electron app on raspberry pi
>>> export DISPLAY=:0
>>> npm run prod
```

```
>> # rotate screen
>> DISPLAY=:0 xrandr --output HDMI-1 --rotate left
```

```
>> # turn on display that's sleeping
>> DISPLAY=:0 xset s on s 60
>> DISPLAY=:0 xset s activate

```

references: 
https://reelyactive.github.io/diy/pi-kiosk/

## Renix Protocol

The UART-based serial protocol used by the Renix

| Byte # | 4L value                  | 2.5L value |
| ------ | ------------------------- | ---------- |
| \-2    | 0xFF                      | 0xFF       |
| \-1    | 0x00                      | 0x00       |
| 0      | software version          |            |
| 1      | prom                      |            |
| 2      | status                    |            |
| 3      | mass absolute pressure    |            |
| 4      | coolant temp sensor       |            |
| 5      | intake air temp           |            |
| 6      | battery voltage           |            |
| 7      | O2 sensor                 |            |
| 8      | spark timing (lower byte) |            |
| 9      | spark timing (upper byte) |            |
| 10     | injector short            |            |
| 11     | injector open             |            |
| 12     | throttle position sensor  |            |
| 13     | spark advance             |            |
| 14     | idle air control          |            |
| 15     |                           |            |
| 16     | atmospheric pressure      |            |
| 17     |                           |            |
| 18     |                           |            |
| 19     | injector pulse            |            |
| 20     |                           |            |
| 21     |                           |            |
| 22     |                           |            |
| 23     |                           |            |
| 24     | short fuel                |            |
| 25     |                           |            |
| 26     | long fuel                 |            |
| 27     | knock                     |            |
| 28     |                           |            |
| 29     |                           |            |
| 30     | error codes               |            |

## A/T Transmission Protocol

*Like to see this implemented? Request with a github issue!*

## ABS Protocol

*Like to see this implemented? Request with a github issue!*

