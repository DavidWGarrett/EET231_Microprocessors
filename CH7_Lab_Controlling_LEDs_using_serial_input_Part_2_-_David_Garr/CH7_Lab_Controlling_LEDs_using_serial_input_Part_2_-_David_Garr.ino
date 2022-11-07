// David Garrett
// 10-27-21
// CH7 Lab Controlling LEDs using serial input Part 2

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))  // returns the size of array

//Sending Multiple Variables at Once
//Send Data in this format: <0-100>,<0-100>,<0,100)>\n
//Where the three numbers represent percentage brightness of R, G, B.
//Define LED Pins
const int RED = 9;
const int GREEN = 10;
const int BLUE = 11;

// array for pins
int ledPins[] = {RED, GREEN, BLUE};

void setup() {
  Serial.begin(9600); //Serial Port at 9600 baud
  Serial.setTimeout(10); //Serial timeout to wait for for int
  
  //Set pins as outputs
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  //Turn on the LEDs
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
}
void loop() {
  //Read data when it's available in the buffer
  if (Serial.available() > 0) {
    
    //Expect to receive 3 integers over serial
    //parseInt will "block" until a valid integer is received
    //parseInt knows full integer was received once a comma or newline is seen
    //parseInt only removes invalid characters before the found int, not after
    
    int val1 = Serial.parseInt();
    int val2 = Serial.parseInt();
    int val3 = Serial.parseInt();
    
    //Throw out anything that remains in the buffer after integers are read
    while (Serial.available()) {
      Serial.read();
  }
  
  //Constrain the received values to be only from -1 to 100
  int val1c = constrain(val1,-1,100);
  int val2c = constrain(val2,-1,100);
  int val3c = constrain(val3,-1,100);

  ////////////////////////////////////////////////////////
  // Three if statements
  // Changes the brightness of each LEDs if input value isn't negative

  // map the brightness value from 0-100 to 0-255
  // analogwrite the brightness of each LED
  // prints out percentage brightness
  
  
  if (val1c > -1) {
    int rval = map(val1c,0,100,0,255); //first valid integer
    analogWrite(RED, rval);
    Serial.println("Red: " + String(val1c) + "%");
  } 

  
  if (val2c > -1) {
    int gval = map(val2c,0,100,0,255); //second valid integer
    analogWrite(GREEN, gval);
    Serial.println("Green: " + String(val2c) + "%");
  }

  
  if (val3c > -1) {
    int bval = map(val3c,0,100,0,255); //third valid integer
    analogWrite(BLUE, bval);
    Serial.println("Blue: " + String(val3c) + "%\n");
  }
  ///////////////////////////////////////////////

  //////////////////////////////////////////////
  // Blinking the lights
  // If -1 gets inputed, the LED blinks off and then back on for that specific color
  // uses for loop/array to iterate through each possible -1 value
  // First for loop turns off LED, 10 second delay, Second for loop turns LED back on

  int valc[] = {val1c, val2c, val3c};
  
  for (int i=0; i < ArrayLength(ledPins); i++) {  // turns off -1 value LEDs
    if (valc[i] == -1) {
      digitalWrite(ledPins[i], !digitalRead(ledPins[i]));
    }
  }
  
  delay(1000);
  
  for (int i=0; i < ArrayLength(ledPins); i++) {  // turns back on -1 value LEDs
    if (valc[i] == -1) {
      digitalWrite(ledPins[i], !digitalRead(ledPins[i]));
    }
  }
  }
}
