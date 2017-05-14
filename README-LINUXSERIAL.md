Linux Serial provides a simple wrapper of the Arduino Streams library that can be used as a replacement
for Arduino's Serial[1..3] when testing/developing code within a *NIX environment.


Usage:

- For simulation purposes setup a tunnel using socat (see examples in socat.sh)
- Check tunnel names in socat.sh and linux-serial.h
- Start the tunnel; run the process; and write to it from a separate process (both device special and unix sockets supported)


CHANGE HISTORY

14/May/2017 - Updated termios settings to be raw (ignore CR)
