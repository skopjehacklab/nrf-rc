nrf-rc
======

NRF remote control. One master, multiple slaves to control 220V relays.

Depends on RF24 library for arduino by @maniacbug:

    git clone git://github.com/maniacbug/RF24.git /home/damjan/Arduino/libraries/RF24

Logic of operation
======

There will be one master node that will have a constant listening pipe. The other (slave) nodes will use this pipe as their writing pipe. The master node will receive an address and a state from the PC via serial. The address will be added to a fixed base address and that will used as the real writing address.

TODO
=====

== Hardware ==

* Test the 220AC-to-5DC adapters
* Make a *slave* board



== Software ==
* Make a *ping* utility to test the loss of packets between two nodes

= slave: =

* Pong back the received state
* Add external switches for setting the address offset

= master: =

* Implement a reliable serial communication
