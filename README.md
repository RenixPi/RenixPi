>>> # create virtual serial port
>>> socat -d -d pty,raw,echo=0 pty,raw,echo=0

>>> # run ansible to set up user and ssh config
>>> ansible-playbook -i hosts raspi.yml

>>> # run ansible to set up renix dependencies
>>> ansible-playbook -i hosts renix.yml



>>> # run electron app on raspberry pi
>>> export DISPLAY=:0
>>> npm run prod
# Renix History

A declining economy coupled with the soaring energy prices of the 1970s, American Motor Corporation (AMC)
struggled in 1980. Their vehicle lineup wasn't able to keep pace with General Motors, Chrysler and Ford. And
Japanese imports were now being produced domestically in highly efficient assembly plants.

Not able to secure loans from traditional sources, Renault provided funding to keep AMC going and eventually
acquired more than 50% of the company by 1982. The company turned focus to its Jeep brand with down-sized versions
of other models; the Wagoneer and Cherokee -- launched in 1983 -- created an entirely new sports utility vehicle
class of cars.

Initially, these vehicles had a carbureted 2.5L AMC engine or a GM-made 2.8L V6. In 1987, Jeep and Renault
designed an inline, 6-cylinder engine. Drawing from another Renault joint venture with aerospace company Bendix,
they outfitted this engine with an electronic fuel injection system. Renault-Bendix was shortened to Renix.

When Chysler acquired Jeep in 1991, they replaced the engine management system with their own ECU. However, 
during just those four years of production, Jeep sold nearly *seven-hundred thousand* vehicles with
the Renix system.

# Engine management protocols

While the On Board Diagnostic standard was established by [SAE in 1979](https://www.sae.org/standards/content/j1979_201202/),
most car companies only partially implemented this protocol until 1994 when California emission regulations mandated its inclusion
in all vehicles.

Renix, however, did not; they used a proprietary format.

# Reverse engineering of the Renix protocol

While some commercially available diagnostic tools were made for mechanics, the protocol was never published. In 2012,
a video by [Phil Andrews of the RenixPower forum](https://www.youtube.com/watch?v=AUqQrLLVdZ8) demonstrated his
hard work in decoding the protocol. Following that, [NickInTimeDesign](nickintimedesign.com) started developing
an open-source [Renix Engine Monitor](https://nickintimedesign.com/product/renix-engine-monitor-ii/) in 2016.

This project is an extension of their tremendous efforts and would not be possible without them.

# Sources

- [Automotive History Preservation Society](http://wildaboutcarsonline.com/cgi-bin/pub9990262549620.cgi?itemid=9990287331811&action=viewad&categoryid=9990279027328&page=1&placeonpage=6&totaldisplayed=50)
- [Renix Wikipedia](https://en.wikipedia.org/wiki/Renix)
- [OBD Wikipedia](https://en.wikipedia.org/wiki/On-board_diagnostics)
- [Origins by NickInTimeDesign](https://nickintimedesign.com/where-it-all-began/)