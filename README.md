# Reaction Game

## Datasheet
Arriny24A: <a href="https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny24A-44A-84A-DataSheet-DS40002269A.pdf">ATtiny24A-44A-84A-DataSheet.pdf</a>

## Removing 8 clock prescaler
`avrdude -p t24a -c avrisp -P /dev/ttyUSB0 -b 19200 -U lfuse:w:0b11100010:m`

## Current
Voltage 3V
led voltage drop = 1V 
V = IR
I = V/R
I = 2/220
I = 0.009A
I = 9mA

# Flash
I am using Arduino Uno as ISP (in system programmer) </br>
To flash code to the board connect Arduino Uno and the 6 pin header (from left top going clockwise)
Arduino Uno | 6 pin header
----------- | ------------
13          | SCK
10          | Reset
11          | MOSI
5V          | VCC
GND         | GND
12          | MISO

`make flash`

# Components
Name                            | Net   | Cost
------------------------------- | ----- | ----
Attiny24A-U                     | 1x    | x
12mm push button                | 1x    | x
74HC595                         | 1x    | x
7 segments 4 digits SH5461AS    | 1x    | x
1206 220Ohm SMD resistor        | 7x    | x
Switch SS12F47                  | 1x    | x
Battery holder                  | 1x    | x
=                               |       | 
Total                           | 13    | x
