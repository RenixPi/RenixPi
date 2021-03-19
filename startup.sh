#!/bin/sh
DISPLAY=:0 xrandr --output HDMI-1 --rotate left
DISPLAY=:0 xset -dpms     # disable DPMS (Energy Star) features.
DISPLAY=:0 xset s off     # disable screen saver
DISPLAY=:0 xset s noblank # don't blank the video device
matchbox-window-manager -use_titlebar no &
unclutter &    # hide X mouse cursor unless mouse activated
## chromium-browser --display=:0 --kiosk --incognito --window-position=0,0 http://reelyactive.github.io/diy/pi-kiosk/