// David Garrett
// Ch 13 - Interrupts everywhere! 
// 12-1-21


// Goal:
// The goal of this lab is to demonstrate hardware and software interrupts working simultaneously.  You will be wiring a circuit similar to the one used in Listing 13-1 and Listing 13-2 examples in the book.
// Instructions:
//  •  Wire one pushbutton switch to pin 2 (or 3) on your Arduino 
//    o You don't need to debounce the switch like the do in the book
//  • Wire 4 LEDs to your Arduino, one to its own output pin 
//    o One of the LEDs will be used with the Timer interrupt
//    o The other 3 will be used with the hardware interrupt lab
//  • Modify Listing 13-1 from the book to support your 3 LED configuration 
//    o You'll just do the "normal" code which assumes that the Arduino is driving the LEDs
//    o The code in the example current sinks the LEDs to make them work
//  • If you haven't installed TimerOne, follow the instructions in the book to install the library
//  • Use the TimerOne library and the example in the book to configure the software interrupt
//  • A correctly operating project should 
//    o Have one of the 3 LEDs slowly brightening and then darkening
//    o Pressing the pushbutton should change to the next of the 3 LEDs
//    o The fourth LED should flash according to the Timer period
// Turn-in:
// Code for the project
// Demonstration video or demonstrate working project to your instructor


#include <TimerOne.h> // Includes Timerone header file
#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))  // Determines Length of Array

//////////// IO PINS
int red = 3; 
int green = 5;
int yellow = 6;
int intPin = 0; // Pin 2 on arduino - for the button
int blinkBlue = 11; // TimerOne LED, Blinks every ten seconds
////////////

int ledPins[] = {red,green,yellow}; 

volatile int selectedLed = red; // starting out with red
// volatile ram can be read and wrote during interrupt
// use if you need value while interrupting


void setup() {
  for (int i=0; i < ArrayLength(ledPins); i++) { // Sets up LED pins as outputs/LOW
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  } 

  //attachInterrupt(intPin, swap, RISING);
  attachInterrupt(digitalPinToInterrupt(2), swap, RISING);
  // PIN OF INTERRUPT, THE FUNCTION, and pin going from low to high
  
  Timer1.initialize(2000000); // IN MICROSECONDS -- MILLISECONDS CAN'T BE COUNTED NATIVELY
  Timer1.attachInterrupt(toggleLed); // Timer1 triggers toggleLed functione very two seconds
}

void loop() {
  updown();
  

}

void updown() {

  // SELECTED LED BRIGHTNESS GOES UP AND DOWN
  
  Serial.println("hello?");
  for (int i = 0; i < 255; i++) {
    analogWrite(selectedLed, i);
    delay(10);
    Serial.println(i);
  }
  for (int i=255; i>0; i--) {
    analogWrite(selectedLed, i);
    delay(10);
    Serial.println(i);
  }
}

void swap() { 

  // WHEN BUTTON TRIGGERS INTERRUPT, THIS FUNCTION TRIGGERS
  // THIS SWAPS THE LEDS LIGHTS ON RED > GREEN > YELLOW > RED
  
  digitalWrite(selectedLed, LOW);
  if (selectedLed == red) {
    selectedLed = green;
  } else if (selectedLed == green) {
    selectedLed = yellow;
  } else {
    selectedLed = red;
  }
}


void toggleLed () { // timer interrupt function
  // toggles blinkBlue/Blue LED specificially
  digitalWrite(blinkBlue, !digitalRead(blinkBlue));
}
