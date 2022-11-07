#include <TimerOne.h>

// INTERRPUT PINS ARE 2 AND 3 ON ARDUINO
// INTERRUPT PINS ARE CALLED 0 (2) AND 1 (3) 
// INSTALL THE TIMER1 LIBRARY

// SOFTWARE INTERRUPT HAS TO USE PIN 9 AND 10
// THREE DIFFERENT THINGS - MAIN LOOP, HARDWARE INTERRUPT, SOFTWARE INTERRUPT



#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))

int blue = 9;
int green = 10;
int red = 11;
volatile int selectedLed = red; // starting out with red
// volatile ram can be read and wrote during interrupt
// use if you need value while interrupting

int intPin = 1; // Pin 3 on arduino

int ledPins[] = {red,green,blue}; 
int blinkPin = 12;

// instal

void setup() {
  for (int i=0; i < ArrayLength(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  } 

  //attachInterrupt(intPin, swap, RISING);
  //attachInterrupt(digitalPinToInterrupt(intPin), swap, CHANGE);
  // PIN OF INTERRUPT, THE FUNCTION, and pin going from low to high

  
  pinMode(blinkPin, OUTPUT);
  //Timer1.initialize(1000000); // IN MICROSECONDS -- MILLISECONDS CAN'T BE COUNTED NATIVELY
  //Timer1.attachInterrupt(swap);
}

void loop() {
  updown();
  

}

void updown() {

  // SELECTED LED BRIGHTNESS GOES UP AND DOWN
  
  Serial.print("hello?");
  for (int i = 0; i < 255; i++) {
    analogWrite(selectedLed, i);
    delay(10);
    Serial.print(i);
  }
  for (int i=255; i>0; i--) {
    analogWrite(selectedLed, i);
    delay(10);
  }
}

void swap() { 

  // WHEN INTERRUPT HAPPENS, THIS FUNCTION TRIGGERS
  // THIS SWAPS THE LEDS LIGHTS ON RED > GREEN > BLUE > RED

  Serial.println("please workd");
  
  digitalWrite(selectedLed, LOW);
  if (selectedLed == red) {
    selectedLed = green;
  } else if (selectedLed == green) {
    selectedLed = blue;
  } else {
    selectedLed = red;
  }
}


void toggleLed () { // timer interrupt function
  // toggles blinkPin specificially
  digitalWrite(blinkPin, !digitalRead(blinkPin));
}
