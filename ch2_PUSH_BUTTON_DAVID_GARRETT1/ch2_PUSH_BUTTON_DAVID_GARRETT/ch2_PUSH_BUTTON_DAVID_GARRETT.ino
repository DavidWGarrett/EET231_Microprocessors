//CHAPTER 2 PUSH BUTTON
//David Garrett

// Delcare and initialize button and green LED
const int button = 6;
const int greenLed = 7;

void setup() {  // Setup green LED as output, button as input
  pinMode(greenLed, OUTPUT);
  pinMode(button, INPUT);

}

void loop() {
  if (digitalRead(button) == LOW) { // Input reads high when button isn't pressed
    // When button is pressed, if statement execute
    digitalWrite(greenLed, !digitalRead(greenLed)); // reads state of LED and toggles to opposite state
  }
  delay(200); // Creates delay, avoids multiple inputs when button is pressed
}
