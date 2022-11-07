// David Garrett
// 10-28-21
// CH7 Lab Controlling LEDs using serial input Part 1

// LED pins declared and initialized
int redLed = 9;
int greenLed = 10;
int blueLed = 11;


void setup() {
  // Set LED pins to out; set up serial communications
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  Serial.begin(9600);

}

void loop() {
    // Sees if serial receive buffer has room
    if (Serial.available() > 0) {  
      char dataIn = Serial.read();  // reads serial input from serial monitor
  
      if (dataIn == 'r') { // if user inputs 'r', toggles red LED
        digitalWrite(redLed, !digitalRead(redLed));
      }
      else if (dataIn == 'g') {  // if user inputs 'g', toggles green LED
        digitalWrite(greenLed, !digitalRead(greenLed));
      }
      else if (dataIn == 'b') {  // if user inputs 'b', toggles blue LED
        digitalWrite(blueLed, !digitalRead(blueLed));    
      }
   }
}
