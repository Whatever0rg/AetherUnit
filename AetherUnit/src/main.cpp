#include <Arduino.h>

<<<<<<< HEAD
//Blinking_LED

//turn on the LED for half a second,then off for half a second,repeatedly

//info@primerobotics.in

//www.primerobotics.in

/************************************************/
=======
>>>>>>> 203ac4a745e1a6199248e677533474e208d76a3f

const int ledPin = 9;//the number of the LED pin

/************************************************/

void setup()

{

 
pinMode(ledPin,OUTPUT);//initialize the digital pin as an output

}

<<<<<<< HEAD
/************************************************/
=======
//************************************************
>>>>>>> 203ac4a745e1a6199248e677533474e208d76a3f

//the loop routine runs over and over again forever

void loop()

{

 
digitalWrite(ledPin,HIGH);//turn the LED on 

 
<<<<<<< HEAD
delay(1000);               //wait
//for half a second
=======
delay(500);               //wait

>>>>>>> 203ac4a745e1a6199248e677533474e208d76a3f

 
digitalWrite(ledPin,LOW); //turn the LED off

 
delay(500);               //wait
<<<<<<< HEAD
//for half a second
=======

>>>>>>> 203ac4a745e1a6199248e677533474e208d76a3f

}

/*************************************************/