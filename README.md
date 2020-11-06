# JSN-SR04T-Arduino
Arduino demo sketch to capture distance using JSN-SR04T ultrasonic distance sensor in *serial* (not GPIO) mode.

I'm using JSN-SR04T v3 board - make sure to solder "M2" jumper to enable the serial mode, where Arduino sending 0x55 causes the sensor to measure distance and return a reading (4 bytes).

Returned distance is 0xFF MSB_DISTANCE LSB_DISTANCE CHECKSUM where CHECKSUM == (0xFF + MSB_DISTANCE + LSB_DISTANCE) & 0xFF. Distance in mm == MSB_DISTANCE * 256 + LSB_DISTANCE.

Tested with Arduino Nano.
