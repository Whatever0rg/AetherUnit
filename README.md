esptool.py --port /dev/ttyUSB0 erase_flash #Erased the existing Firmware
esptool.py --port /dev/ttyUSB0 --baud 1000000 write_flash --flash_size=4MB -fm dio 0 /home/bennet/school/Projekt_Luft/FIRMWARE.bin #Installed new Firmware on Board
--

