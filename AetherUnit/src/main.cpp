#include <Arduino.h>
#include <SPI.h>
#include <SD.h>



const int ledPin = 9;//the number of the LED pin
const int chipSelect = 10; // telling the Board where the microSD card is


File testFile;


void setup()

{
Serial.begin(9600);                             //Initializing the microSD card
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

pinMode(ledPin,OUTPUT);//initialize the digital pin as an output


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
}
//the loop routine runs over and over again forever

void loop()

{

 
digitalWrite(ledPin,HIGH);//turn the LED on 

 
delay(500);               //wait


 
digitalWrite(ledPin,LOW); //turn the LED off

 
delay(500);               //wait

}

