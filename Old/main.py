
# Complete project details at https://RandomNerdTutorials.com

from machine import SoftSPI, Pin, I2C
from time import sleep
import BME280
import CCS811
import sdcard, uos


# ESP32 - Pin assignment
# i2c = I2C(scl=Pin(22), sda=Pin(21), freq=10000)
# ESP8266 - Pin assignment
i2c = I2C(scl=Pin(4), sda=Pin(5), freq=10000)
s = CCS811.CCS811(i2c=i2c, addr=90)
sleep(1)

spi = SoftSPI(sck=Pin(12), miso=Pin(15), mosi=Pin(13))
cs = Pin(14)
sd = sdcard.SDCard(spi, cs)

led = Pin(2, Pin.OUT)

uos.mount(sd, '/sd')
print(uos.listdir('/sd'))

# while(True):       #This is a test that can be used to determin if the board is functioning
#   led(0)
#   sleep(0.5)
#   led(1)
#   sleep(0.5)

while True:
  led(0)
  bme = BME280.BME280(i2c=i2c)
  temp = bme.temperature
  hum = bme.humidity
  pres = bme.pressure
  # uncomment for temperature in Fahrenheit
  #temp = (bme.read_temperature()/100) * (9/5) + 32
  #temp = str(round(temp, 2)) + 'F'
  print('Temperature: ', temp)
  print('Humidity: ', hum)
  print('Pressure: ', pres)
  sleep(0.5)
  led(1)
  if s.data_ready():
            print('eCO2: %d ppm, TVOC: %d ppb' % (s.eCO2, s.tVOC))
  sleep(5)
