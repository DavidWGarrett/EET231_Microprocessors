// David Garrett
// Lab 4 Motor Control
// 10-13-21

// I/O Pins
int motorIn1 = 4;
int motorIn2 = 5;
int hBridgeEn = 3;
int speedPin = A0;

// Sets initial rate
int rate = 255;

void setup() {
  // Sets digital outputs
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);

}

void loop() { 
  // loops speedpot function
  speedPot();

}

void speedPot() {
  // The motor is controlled based on the position of the pot
  // Potentiometer connected to Analog In Pin
  // If reading below 500, motor spins backwards
  // If reading above 520, motor spins forward
  // Else, motor stops
  
  int motorControl = analogRead(speedPin); // pot value
  
  if (motorControl > 520) {

    //remaps analog input to create new value for analog output
    motorControl = map(motorControl, 521, 1023, 0, 255);
    forward(motorControl); // value passed to forward function
  }
  else if (motorControl < 500) {

    //remaps analog input to create new value for analog output
    motorControl = map(motorControl, 499, 0, 0, 255);
    backward(motorControl);  // value passed to backwards function
  }
  else {

    // motor stops if analog input value fall between 500 and 520
    off();
  }
}

void forward(int rate) {
  digitalWrite(hBridgeEn, LOW); // Shuts h bridge off before writing new value
  digitalWrite(motorIn1, HIGH);  // Sets motor to forward
  digitalWrite(motorIn2, LOW);
  analogWrite(hBridgeEn, rate);  // Sets speed of motor
  delay(900);
}

void backward(int rate) {
  digitalWrite(hBridgeEn, LOW); // Shuts h bridge off before writing new value
  digitalWrite(motorIn2, HIGH);  // Sets motor to backwards
  digitalWrite(motorIn1, LOW);
  analogWrite(hBridgeEn, rate);  // Sets speed of motor
  delay(900);
}

void off() {  // Turns motor off
  digitalWrite(hBridgeEn, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn1, LOW);
  analogWrite(hBridgeEn, HIGH);
  delay(900);
}
