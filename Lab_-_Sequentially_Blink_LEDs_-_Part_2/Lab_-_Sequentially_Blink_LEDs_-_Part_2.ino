// Lab - Sequentially Blink LED's - Part 2
// David Garrett
// 9-29-21

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))
// parameterized macro used to figure out length of an array

int ledpins[] = {2,3,4,5,6}; // Creates an array of all the pin numbers
int i = 0;


void setup() {
  for (int i=0; i < ArrayLength(ledpins); i++) {
    pinMode(ledpins[i], OUTPUT);
    // for loop goes through each pin in the array and sets up pinmode to output
    // ArrayLength(ledpins) figures out the length of array
    // first value in for loop is starting value, next is the exit condition
    // last value is the step value
  }
  }

void loop() {

  // two for loops
  // first one is designed to blink all LEDs left to right besides last one
  // second one is designed to blink all LEDs right to left besides first one
  // Design this way to prevent the end LEDs from double blinking
  
  for (i; i < ArrayLength(ledpins)-1; i++) {
    // for loop blinks all LEDs besides the last one
    digitalWrite(ledpins[i], HIGH); // LED turns on
    delay(200);
    digitalWrite(ledpins[i], LOW); // LED turns off
    if (i == ArrayLength(ledpins)-2) {
      // if statement triggers right before last LED
      for (i+=1; i > 0; i--) {
        // for loop designed to blink all LEDs in the other direction besides
        // the first LED.
        // i is incrimented by 1 so the last LED blinks.
        // the exit condition stops blinking right before the first LED
        // i is decreased by 1 each loop
        digitalWrite(ledpins[i], HIGH);  // LED turns on
        delay(200);
        digitalWrite(ledpins[i], LOW);  // LED turns off
      }
      i = -1; // resets the i value
      // makes it so when the first for loop gets triggered after second one
      // the first LED starts blinking
    }
  }
}
