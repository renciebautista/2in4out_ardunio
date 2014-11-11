/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */


#include <SimpleTimer.h>
// the timer object
SimpleTimer timer;


// constants won't change. They're used here to 
// set pin numbers:
const int sensorIn = 4;     // the number of the pushbutton pin
const int sensorOut = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int exitCar = LOW;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(sensorIn, INPUT);     
  pinMode(sensorOut, INPUT);    
  
  
}

void loop(){
  // read the state of the pushbutton value:
  sensor(sensorIn,sensorOut);
  sensor(sensorOut,sensorIn);
}


void sensor(int sensor1,int sensor2){

  buttonState = digitalRead(sensor1);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == LOW) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    passingCar(sensor2);
    digitalWrite(ledPin, LOW); 
  } 
}

void passingCar(int buttonPin){
  exitCar = LOW;
  int cnt = 0;
  // Variables will change:
  int ledState = LOW;         // the current state of the output pin
  int sensorState;             // the current reading from the input pin
  int lastButtonState = LOW;   // the previous reading from the input pin

  // the following variables are long's because the time, measured in miliseconds,
  // will quickly become a bigger number than can be stored in an int.
  long lastDebounceTime = 0;  // the last time the output pin was toggled
  long debounceDelay = 50;    // the debounce time; increase if the output flickers
  
  long startTime = 0;  // the last time the output pin was toggled
  startTime = millis();
  while(exitCar == LOW){
    if ((millis() - startTime) > 10000){
      exitCar = HIGH;
    }
    
    // read the state of the switch into a local variable:
    int reading = digitalRead(buttonPin);

    // check to see if you just pressed the button 
    // (i.e. the input went from LOW to HIGH),  and you've waited 
    // long enough since the last press to ignore any noise:  

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
      // reset the debouncing timer
      lastDebounceTime = millis();
    } 

    if ((millis() - lastDebounceTime) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading != sensorState) {
        sensorState = reading;

        // only toggle the LED if the new button state is HIGH
        if (sensorState == HIGH) {
          ledState = !ledState;
          if(ledState == LOW){
            exitCar = HIGH;
          }
        }
      }
    }
    // save the reading.  Next time through the loop,
    // it'll be the lastButtonState:
    lastButtonState = reading;
  }
}
