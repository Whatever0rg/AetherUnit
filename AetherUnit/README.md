# AetherUnit
## Description
TBA
## Setup Guide
Use:
<<<<<<< HEAD:AetherUnit/README.md
> esptool.py --port /dev/ttyUSB0 erase_flash 

To erase any existing data that might be installed on the D1 Mini or similar Board.

Then use:

> esptool.py --port /dev/ttyUSB0 --baud 1000000 write_flash --flash_size=4MB -fm dio 0 /home/user/filepath/FIRMWARE.bin  
=======
> esptool.py --port /dev/ttyUSB0 erase_flash

To erase any existing data that might be installed on the D1 Mini or similar Board.  

Then use:

> esptool.py --port /dev/ttyUSB0 --baud 1000000 write_flash --flash_size=4MB -fm dio 0 /home/user/filepath/FIRMWARE.bin
>>>>>>> 203ac4a745e1a6199248e677533474e208d76a3f:README.md

To flash the new Firmware onto the Board.  

Then you'll need to install ***ampy***, you can do this [here](https://github.com/scientifichackers/ampy).  

Now you can use ***ampy*** to port all files onto the board.  

## This can be Ignored
--
screen /dev... # To get onto the Board
>>> led = Pin(2, Pin.OUT) # Tying the connection
>>> led(1)
>>> led(0)
--
Installed so I can import files onto board
--
ampy --port /dev/ttyUSB0 put main.py 
<<<<<<< HEAD:AetherUnit/README.md
downloaded pyboard.py 
=======
downloaded pyboard.py 
>>>>>>> 203ac4a745e1a6199248e677533474e208d76a3f:README.md
