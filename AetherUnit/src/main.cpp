#include <Arduino.h>


const int ledPin = 9;//the number of the LED pin

/************************************************/

void setup()

{

 
pinMode(ledPin,OUTPUT);//initialize the digital pin as an output

}

//************************************************

//the loop routine runs over and over again forever

void loop()

{

 
digitalWrite(ledPin,HIGH);//turn the LED on 

 
delay(500);               //wait


 
digitalWrite(ledPin,LOW); //turn the LED off

 
delay(500);               //wait


}

/*************************************************/