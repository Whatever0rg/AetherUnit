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

File dataFile;
String fileName;

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  // Simulated time
  startTime = millis();


  randomSeed(analogRead(0));  // Use an unconnected analog pin for randomness

  // Generating a random filename
  long randomNumber = random(100000, 999999);
  String fileExtension = ".csv";
  fileName = String(randomNumber) + fileExtension;


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

delay(10000); // letting all sensors startup

}


// Defining Functions



void saveToSd(String currentTime, float co2, float tvoc){
dataFile = SD.open(fileName.c_str(), FILE_WRITE);
if (dataFile) {
    Serial.print("Writing ...");
    Serial.println(String(ccs.geteCO2()) + String(ccs.getTVOC()));
    String dataString = currentTime + "," + String(bme.readTemperature()) + "," + String(bme.readPressure()) + "," + String(bme.readHumidity()) + "," + String(co2) + "," + String(tvoc);
    dataFile.println(dataString);
    dataFile.close();
    Serial.println("done.");
} else {
    Serial.println("error opening file");
}
}

void every15Minutes(String runtime){
  // reading ccs data
  if(ccs.available()){
    if(!ccs.readData()){
      float co2 = ccs.geteCO2();
      float tvoc = ccs.getTVOC();
      saveToSd(runtime, co2, tvoc);
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  
}

//the loop routine runs over and over again forever

void loop()
{
  // creating Time for data logging. Be advised this is simulated!!!
  unsigned long currentMillis = millis();

  unsigned long totalMinutes = currentMillis / 60000; 
  unsigned long days = totalMinutes / 1440; 
  unsigned long hours = (totalMinutes % 1440) / 60; 
  unsigned long minutes = totalMinutes % 60; 

  // Create a formatted string
  String runtime = String(days) + ":" + String(hours) + ":" + String(minutes);

  // Print the formatted string to the Serial Monitor
  Serial.println("Runtime: " + runtime);

  digitalWrite(ledPin,HIGH);//turn the LED on 
  delay(500);               //wait

  
  
 every15Minutes(runtime);
  
  delay(500);


  digitalWrite(ledPin,LOW); //turn the LED off
  delay(500);               //wait

}