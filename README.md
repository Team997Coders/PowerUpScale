# PowerUpScale

This project contains the firmware for the FMS Powerup Scale control unit.  It sends plate ownership commands to the faux FMS server located in the PowerUpFMSServer project and controls LEDs for each plate on the scale.  We used magnetic reed switches to detect when a plate was owned.

We used the Arduino IDE 1.8.5 to develop and build this project on Mac OSX 10.12.5.  The board targeted was an Arduino UNO R3 with an Ethernet shield.  The parts list follows.

The firmware can acquire an IP address using DHCP, or via a jumper on the board (see comments in program code) use a static IP hardcoded in the application.  It registers itself to the server application so that the server can send commands back (like randomizing the field, setting the state to play the game, safe, and staff-safe LED states).

There is also a jumper setting that defines which alliance is the "field left" alliance (red or blue).  This orients the field so that the field string can be generated correctly.
