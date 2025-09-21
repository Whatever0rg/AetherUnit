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


const int buttonPin = A0;
int buttonState = LOW;
int reading = 0;
int oldButtonState = LOW;
bool toggle = false;
long lastMillis;
bool flip = true;
int sensorData[4];
int decimalPosition[4] = {1,1,-1,-1}; 
int buttonPresses = 0;
long lastInterval = 0;
long interval = 1000;

void setup() {
    Serial.begin(9600);
    byte numDigits = 4; 
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    bool resistorsOnSegments = 0; 
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(10);

    pinMode(buttonPin, INPUT);



    // CCS811 Startup

    Serial.println("CCS811 test");

    if(!ccs.begin()){
        Serial.println("Failed to start sensor! Please check your wiring.");
    }

    // Wait for the sensor to be ready
    while(!ccs.available());

    // BME Setup
    bool status;
    status = bme.begin(0x76);  
        if (!status) {
            Serial.println("Could not find a valid BME280 sensor, check wiring!");
        }

    // LED Setup
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    delay(5000);    // letting all sensors startup
    Serial.println("initialization done.");
}


void buttonflip() {
    if (reading != oldButtonState) {
        lastMillis = millis();
    }
    if ((millis() - lastMillis) > 50 && reading != buttonState) {
        buttonState = reading;
        if (buttonState == HIGH){
            buttonPresses = buttonPresses + 1;
            updatedisplay();
        }
    }
    oldButtonState = reading;

}

int readsensors() {
    if (ccs.available()){
        if(!ccs.readData()){
        sensorData[0] = bme.readTemperature() * 10;
        sensorData[1] = bme.readHumidity() * 10;
        sensorData[2] = ccs.geteCO2();
        sensorData[3] = ccs.getTVOC();
        }
    } else {
        sensorData[2] = 8888;
        sensorData[3] = 8888;
        }
}

void updatedisplay() {
    sevseg.setNumber(sensorData[(buttonPresses) % 4], decimalPosition[buttonPresses % 4]);

}

void loop(){
    if ((millis() - lastInterval) >= interval){
        lastInterval = millis();
        readsensors();
        updatedisplay();
    }
    reading = digitalRead(buttonPin);
    buttonflip();
    sevseg.refreshDisplay(); // Must run repeatedly
}
