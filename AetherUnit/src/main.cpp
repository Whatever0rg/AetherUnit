#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_CCS811.h>
#include <Adafruit_BME280.h>
#include <time.h>

Adafruit_CCS811 ccs;
Adafruit_BME280 bme;

const int ledPin = 9;//the number of the LED pin
const int chipSelect = 10; // telling the Board where the microSD card is
unsigned long previousMillis = 0;
const unsigned long interval = 15 * 60 * 1000; // 15 minutes in milliseconds

unsigned long startTime;
unsigned long simulatedSeconds = 0;

// generating file
File dataFile;
long randomNumber = random(100000, 999999);
String fileExtension = ".csv";
String fileName = String(randomNumber) + fileExtension;

void setup()
{
// Simulated time
startTime = millis();

Serial.begin(9600);
SPI.begin();
  //Initializing the microSD card                          
  Serial.print("Initializing SD card..."); 
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    return;
  }
Serial.println("initialization done.");


dataFile = SD.open(fileName.c_str(), FILE_WRITE);

  if (dataFile) {
    Serial.print("Writing ...");
    dataFile.println("Time, Temperature in °C, Pressure in hPa, Humidity in %, Co2 in ppm, TVOC in");
    dataFile.close();
    Serial.println("done.");
} else {
    Serial.println("error opening file");
}
dataFile = SD.open(fileName.c_str());

if (dataFile) {
    Serial.println("test.txt:");
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
} else {
    Serial.println("error opening file");
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


// Defining Functions


void saveToSd(char currentTime){
dataFile = SD.open(fileName.c_str(), FILE_WRITE);
if (dataFile) {
    Serial.print("Writing ...");
    String dataString = currentTime+ "," + String(bme.readTemperature()) + "," + String(bme.readPressure()) + "," + String(bme.readHumidity()) + "," + String(ccs.geteCO2()) + "," + String(ccs.getTVOC());
    dataFile.println(dataString);
    dataFile.close();
    Serial.println("done.");
} else {
    Serial.println("error opening file");
}
}

//the loop routine runs over and over again forever

void loop()
{
  digitalWrite(ledPin,HIGH);//turn the LED on 

 
  delay(500);               //wait

  unsigned long currentMillis = millis();
  unsigned long elapsedTime = (currentMillis - startTime) / 1000;

  int hours = (elapsedTime / 3600) % 24;
  int minutes = (elapsedTime / 60) % 60;
  int seconds = elapsedTime % 60;

  // Create a formatted string for the simulated time
  char currentTime[20];
  sprintf(currentTime, "%02d:%02d:%02d", hours, minutes, seconds);

  
  saveToSd(char(currentTime));
  



 
  delay(500);               //wait

}