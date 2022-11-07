// David Garrett
// EET231 EXAM 1
// 10-13-21

// parameterized macro used to figure out length of an array
#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))  

int blueLed = 6;
int greenLed = 7;
int redLed = 8;

// Creates an array of all the pin numbers
int ledPins[] = {blueLed, greenLed, redLed};


// If Statement not needed for randomly flashing LED
// Created randomLedToFlash function that returns a value 0 through 2
// Set up the array ledPins[] that contains the pin values of each led
// Blue LED = 0, Green LED = 1, Red LED = 2
// The value returned by randomLedToFlash function is passed to blink function is passed to blink function
// Blink function selects random LED based on ledPins[randomLedToFlash()]

void setup() {
  randomSeed(analogRead(A0)); // Sets up random number generator

  // for loop goes through each pin in the array and sets up pinmode to output
  // ArrayLength(ledpins) figures out the length of array
  // first value in for loop is starting value, next is the exit condition
  // last value is the step value
  for (int i=0; i < ArrayLength(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  blink(randomLedToFlash(), randomDurationTime());

}


// Use to Flash the LED
// Random time and random LED value passed to function
// Turns LED on, delay, Turns LED off, delay
void blink(int randomLed, int randomTime) {

  digitalWrite(ledPins[randomLed], HIGH);
  delay(randomTime);
  digitalWrite(ledPins[randomLed], LOW);
  delay(randomTime);
}


// Function returns a random time to flash the LED
int randomDurationTime() {
  int randomTime = random(50, 500); // Time range from 50 milliseconds to 500 milliseconds
  return randomTime;
}


// Function returns a random number used to flash the different color LEDs
int randomLedToFlash() {
  int randomLed = random(0, ArrayLength(ledPins)); // Values range from 0 to the length of array
  return randomLed;
}
