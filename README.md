>>> # create virtual serial port
>>> socat -d -d pty,raw,echo=0 pty,raw,echo=0

>>> # run ansible to set up user and ssh config
>>> ansible-playbook -i hosts raspi.yml

>>> # run ansible to set up renix dependencies
>>> ansible-playbook -i hosts renix.yml



>>> # run electron app on raspberry pi
>>> export DISPLAY=:0
>>> npm run prod


>> # rotate screen
>> DISPLAY=:0 xrandr --output HDMI-1 --rotate left
