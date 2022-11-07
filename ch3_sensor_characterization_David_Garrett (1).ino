// constants won't change. They're used here to set pin numbers:
const int buttonPin = 12;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int switchValue = 0;
//const char* sensor[] = {"Touch Sensor", "Temperature Sensor", "Tilt Sensor", "Photoresistor Sensor"};

int touch = A0;
int temp = A1;
int tilt = A2;
int photo = A3;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
  Serial.begin(9600);
}

void loop() {
  //////////////////
  //debounce///////
  /////////////////
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

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
}
