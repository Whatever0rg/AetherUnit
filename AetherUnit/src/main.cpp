#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_CCS811.h>
#include <Adafruit_BME280.h>

Adafruit_CCS811 ccs;
Adafruit_BME280 bme;

const int ledPin = 9;//the number of the LED pin
const int chipSelect = 10; // telling the Board where the microSD card is


File testFile;


void setup()
{
Serial.begin(9600);
SPI.begin();
  //Initializing the microSD card                          
  Serial.print("Initializing SD card..."); 
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    return;
  }
Serial.println("initialization done.");

testFile = SD.open("test.txt", FILE_WRITE);

  if (testFile) {
    Serial.print("Writing to test.txt...");
    testFile.println("testing 1, 2, 3.");
    testFile.close();
    Serial.println("done.");
} else {
    Serial.println("error opening test.txt");
}
testFile = SD.open("test.txt");

if (testFile) {
    Serial.println("test.txt:");
    while (testFile.available()) {
      Serial.write(testFile.read());
    }
    testFile.close();
} else {
    Serial.println("error opening test.txt");
}

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
pinMode(ledPin,OUTPUT);

}

//the loop routine runs over and over again forever

void loop()
{
  digitalWrite(ledPin,HIGH);//turn the LED on 

 
  delay(500);               //wait

  if(ccs.available()){
    if(!ccs.readData()){
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }

  auto temperature = String(bme.readTemperature()) + " °C";
  auto pressure = String(bme.readPressure() / 100.0) + " hPa";
  auto humidity = String(bme.readHumidity()) + " %";

  String bmeMeasurements = temperature + ", " + pressure + ", " + humidity;
  Serial.println(bmeMeasurements);

  digitalWrite(ledPin,LOW); //turn the LED off

 
  delay(500);               //wait

}
