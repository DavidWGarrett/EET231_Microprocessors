// Lab - Ch2 - Sequentially Blink LED's - Part 1 
// David Garrett
// 

int shortYellow = 8; // short yellow led
int red = 9; // red led
int green = 10; // GREEN led
int blue = 11; // blue LED
int tallYellow = 12; // tall yellow LED

int led[5] = {shortYellow, red, green, blue, tallYellow}; // Creates an array of all the LEDs

void setup() {  // Sets all five LED pins to output

  for (int i=0; i<5; i++) {  // Use for loop to iterate through each LED
    pinMode(led[i], OUTPUT);
  }
}

void loop() {  // Each LED gets flashed one at a time. Cycle repeats after last LED
  // Use for loop to iterate through each LED
  for (int i=0; i<5; i++) {
    digitalWrite(led[i], HIGH);
    delay(100);
    digitalWrite(led[i], LOW);
    delay(100);
  }
}
