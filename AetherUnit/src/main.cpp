#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_CCS811.h>
#include <Adafruit_BME280.h>
#include <time.h>
#include "SevSeg.h"

Adafruit_CCS811 ccs;
Adafruit_BME280 bme;
SevSeg sevseg;


File dataFile;
String fileName;

void setup()
{
byte numDigits = 4; 
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = 0; 
  // variable above indicates that 4 resistors were placed on the digit pins.
  // set variable to 1 if you want to use 8 resistors on the segment pins.
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);




// CCS811 Startup

  Serial.println("CCS811 test");

  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  // Wait for the sensor to be ready
  while(!ccs.available());

// BME Setup
bool status;
status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);}

// LED Setup
pinMode(LED_BUILTIN,OUTPUT);
digitalWrite(LED_BUILTIN,HIGH);

delay(5000); // letting all sensors startup
Serial.println("initialization done.");
}


void loop()
{
  static unsigned long timer = millis();
  static int iterator = 0;

  if (millis() - timer >= 1000) {
    timer += 1000;
    iterator ++;
    if (iterator % 2){
      sevseg.setNumber(bme.readTemperature());
    }
    else{sevseg.setNumber(bme.readHumidity());
  }}
  sevseg.refreshDisplay(); // Must run repeatedly

}