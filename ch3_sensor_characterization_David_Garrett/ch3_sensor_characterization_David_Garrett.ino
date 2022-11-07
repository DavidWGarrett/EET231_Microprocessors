<<<<<<< Updated upstream
// constants won't change. They're used here to set pin numbers:
=======
// David Garrett
// CH3 Sensor Characterization
// 9-22-21


>>>>>>> Stashed changes
const int buttonPin = 12;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
<<<<<<< Updated upstream
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int switchValue = 0;
//const char* sensor[] = {"Touch Sensor", "Temperature Sensor", "Tilt Sensor", "Photoresistor Sensor"};

int touch = A0;
=======
int reading;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int switchValue = 1; // Value used to cycle through the cases in the switch statement

int touch = A0;  // Sets the analog input pins
>>>>>>> Stashed changes
int temp = A1;
int tilt = A2;
int photo = A3;

<<<<<<< Updated upstream
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
  Serial.begin(9600);
}

void loop() {
=======
int redLed = 4;  // Sets the pins for the 4 pin RGB LED
int greenLed = 7;
int blueLed = 8;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Button use to iterate through each sensor case in switch statement
  pinMode(ledPin, OUTPUT);  // Output #13 pin, shows when button toggles
  pinMode(redLed, OUTPUT);  // Output for RGB LED
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  Serial.begin(9600);  // Serial communication for print statements
}

void loop() {
  debounce();  // function that debounces button
  // Debounce functions contains the statements that increases the switchValue variable by 1

  // set the LED on pin 13
  digitalWrite(ledPin, ledState);  // Toggles LED #13 when button pushes
  delay(100);

  switch(switchValue) {  // Four cases for each sensor
    case 1: {  // Capacitive Touch Sensor
      digitalWrite(redLed, HIGH); // Sets LED to red
      digitalWrite(greenLed, LOW);
      digitalWrite(blueLed, LOW);
      int touchValue = (analogRead(touch)); // stores value of touch sensor analog input
      Serial.print("Touch Value: ");
      Serial.println(touchValue); // prints values
      delay(30);
      break;} // breaks out of switch statement 
    case 2: { // Thermistor sensor case
      digitalWrite(blueLed, HIGH); // Sets LED to blue
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, LOW);
      Serial.print("Temperature Value: ");
      int tempValue = (analogRead(temp)); // stores value of temps sensor analog input
      Serial.println(tempValue); // prints values
      delay(30);
      break;} // breaks out of switch statement
    case 3: {  // Tilt sensor case
      digitalWrite(greenLed, HIGH); // Sets LED to green
      digitalWrite(redLed, LOW);
      digitalWrite(blueLed, LOW);
      Serial.print("Tilt Value: ");
      int tiltValue = (analogRead(tilt)); // stores value of tilt sensor analog input
      Serial.println(tiltValue); // prints values
      delay(30);
      break;} // breaks out of switch statement
    case 4: {  // Photoresistor case
      digitalWrite(blueLed, HIGH); // Sets LED to purple
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, HIGH);
      Serial.print("Photoresistor Value: ");
      int photoValue = (analogRead(photo)); // stores value of photo sensor analog input
      Serial.println(photoValue); // prints values
      delay(30);
      break;} // breaks out of switch statement
    default: {  // Resets the switch value back to 1
      switchValue = 1;
      break; // breaks out of switch statement
    }    
  }
}

void debounce() { 
>>>>>>> Stashed changes
  //////////////////
  //debounce///////
  /////////////////
  // read the state of the switch into a local variable:
<<<<<<< Updated upstream
  int reading = digitalRead(buttonPin);
=======
  reading = digitalRead(buttonPin);
>>>>>>> Stashed changes

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
<<<<<<< Updated upstream
        switchValue += 1;
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  Serial.print("The switch value: ");
  Serial.println(switchValue);
  delay(100);

  switch(switchValue) {
    case 1: {
      Serial.print("The switch value: ");
      Serial.println(switchValue);
      int touchValue = (analogRead(touch));
      Serial.print("Touch Value: ");
      Serial.println(touchValue);
      delay(30);
      break; }
    case 2: {
      Serial.print("The switch value: ");
      Serial.println(switchValue);
      Serial.print("Temperature Value: ");
      int tempValue = (analogRead(temp));
      Serial.println(tempValue);
      delay(30);
      break; }
    case 3: {
      Serial.print("The switch value: ");
      Serial.println(switchValue);
      Serial.print("Tilt Value: ");
      int tiltValue = (analogRead(tilt));
      Serial.println(tiltValue);
      delay(30);
      break; }
    case 4: {
      Serial.print("The switch value: ");
      Serial.println(switchValue);
      Serial.print("Photoresistor Value: ");
      int photoValue = (analogRead(photo));
      Serial.println(photoValue);
      delay(30);
      break; }
    default: {
      Serial.print("Hello why is this not working?");
      switchValue = 1;
      break;
    }
      
  }
=======
        switchValue += 1;  // increases the switchValue variable by 1
      }
    }
  }
  lastButtonState = reading;
>>>>>>> Stashed changes
}
