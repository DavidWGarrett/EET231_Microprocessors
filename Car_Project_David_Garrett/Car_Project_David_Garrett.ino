// David Garrett
// 12-15-21
// Car Project

// Goal: Car drives forward and avoids obstacles
// What the car does: Drives forward. Stops when gets too close to object. Reverse/Turn. Drives forward and repeats cycle.
// Arduino Enables two h-bridges which drives two motors/tires each. Also chooses if tires spin forward, backwards, or stop
// Ping Sensor measures distance in front of car. 
// Servo motor turns the ping sensor. Determines if objects are close on left and right side of car



#include <Servo.h>  // includes servo header

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))  // Determines the length of arrow

//////////////////////////////////
//FRONT IN1/IN2 ---- Front Right Tire
//When IN1 HIGH/IN2 LOW --- Forward

//FRONT IN3/IN4 --- Front Left Tire
//When IN3 HIGH/IN4 LOW - Forward

//Back IN1 IN2 ---- Back Right Tire
//IN1 High IN2 Low --- Forward

//Back IN3/IN Back Right Tire
//When IN4 High, IN3 Low -- Forward

///// IN1/2  === RIGHT SIDE
///// IN3/4  === LEFT SIDE
///////////////////////////////////////

// pins for the h-bridge
int motorIn1Front = A5;
int motorIn2Front = A4;
int motorIn3Front = A3;
int motorIn4Front = A2;
int hBridgeEnRight = 6;
int motorIn1Back = 7;
int motorIn2Back = 8;
int motorIn3Back = 9;
int motorIn4Back = 10;
int hBridgeEnLeft = 11;
int rate = 150; // step of motor


// Array for motor pins
int motorArray[] = {motorIn1Front, motorIn2Front, motorIn3Front, motorIn4Front,
                    motorIn1Back, motorIn2Back, motorIn3Back, motorIn4Back
                   };
// Array for EN pin for right and left side of tires
int hBridgeEn[] = {hBridgeEnRight, hBridgeEnLeft};

// declarations/pin values for servo
int servoPin = 5;
int pause = 11;
Servo myServo; // creates object myServo
// SERVO --- RED 5V, ORANGE SIG, BROWN GND

// declaration/pin values for ping sensor
int echo = 12;
int trig = 13;
int echoVal;


void setup() {

  // set pinmode to output for all the motor pins
  for (int i = 0; i < ArrayLength(motorArray); i++) {
    pinMode(motorArray[i], OUTPUT);
  }

  myServo.attach(servoPin); // servo pin
  myServo.write(90);  // centers servo

  // Ping Sensor Pins
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  forward4(255); // makes the motors work properly, needs to be high speed before going slow

  delay(50);

}

void loop() {
  forward4(rate); // drives forward
  i80spin(); // spins servo, pings, stops if ping sensor too close to object
  

}

void i80spin() {  // Spins servo 60 degrees back and forth
  for (int i = 90; i <= 145; i += 4) { // Each number i represents a degree the servo can spin
    // left spin
    myServo.write(i); // turn servo
    pingStop(); // ping sensor
  }

  for ( int i = 110; i >= 45; i -= 4) { // Each number i represents a degree the servo can spin
    // right spin
    myServo.write(i); // tern servo
    pingStop(); // ping sensor
  }
    for (int i = 45; i <= 90; i += 4) { // Each number i represents a degree the servo can spin
    // back to middle
    myServo.write(i); // tern servo
    pingStop(); // ping sensor
  }
}

void pingStop() {
  int cmDist = ping(); // figures out the distance in centimeter
  int forMapFunction = cmDist; // new value for map function
  if ( forMapFunction > 400 ) { // map function doesn't work without this if statement
    forMapFunction = 400;       // maximum value is 400. Car won't run if value goes above 400 with map function
  }
  rate = map(forMapFunction, 30, 400, 75, 200); // 30cm = only 75 speed, 400cm = 200 speed

  if (cmDist > 35 ) { // if distance greater than 40cm, go forward
    forward4(rate);
  } else { // below 40 cm
    off(); // turn off
    delay(50);
    int PingVal = i80spinNoSpin(); // figure out if object is closer to left or right side of car
    if (PingVal == 1) { // if left, turn right. If right, turn left
      rightBack(rate);
    } else {
      leftBack(rate);
    }
    delay(300);
    forward4(rate); // go forward again
    
  }
}



int i80spinNoSpin() {  // Spings servo 180 degrees back and forth and pings

  off(); // makes the car stop moving
  int cmDistLeftHighestVal = 0;
  int cmDistRightHighestVal = 0;

  //////////////////////
  // Figures out which way to turn.
  // measure the ping on left and right side of car
  
  // turn ping sensor left
  
  for (int i = 120; i <= 179; i += 1) { // Each number i represents a degree the servo can sping
    myServo.write(i);
    int cmDistLeft = ping();
    if (cmDistLeft > cmDistLeftHighestVal) {
      cmDistLeftHighestVal = cmDistLeft;
    }
    delay(10);
  }
  
  myServo.write(90);
  delay(10);

  // turns ping sensor right and pings

  for ( int i = 60; i >= 0; i -= 1) { // Each number i represents a degree the servo can sping
    myServo.write(i);
    int cmDistRight = ping();
    if (cmDistRight > cmDistRightHighestVal) {
      cmDistRightHighestVal = cmDistRight;
    }
    delay(10);
  }

  ///////////////////

  myServo.write(90);
  delay(1);

  // highest ping on both right and left side gets compared
  // based on the highest ping, it'll either turn left or right
  
  if ( cmDistLeftHighestVal > cmDistRightHighestVal ) { 
    return 0;
  } else {
    return 1;
  }
}

void rightBack(int rate) { // makes the car turn right, only spins the left tires
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    digitalWrite(hBridgeEn[i], LOW);
  }
  for (int i = 0; i < ArrayLength(motorArray); i = i + 4) { // only writes to left tires
    digitalWrite(motorArray[i], LOW);
    digitalWrite(motorArray[i + 1], HIGH);
  }
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    analogWrite(hBridgeEn[i], 220
    );
  }
  delay(700);
}


void leftBack(int rate) { // makes the car turn left, only spins the right tires
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    digitalWrite(hBridgeEn[i], LOW);
  }
  for (int i = 2; i < ArrayLength(motorArray); i = i + 4) { // only writes to right tires
    digitalWrite(motorArray[i], LOW);
    digitalWrite(motorArray[i + 1], HIGH);
  }
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    analogWrite(hBridgeEn[i], 220);
  }
  delay(700);
}

void forward4(int rate) { // makes all the tires go forward
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    digitalWrite(hBridgeEn[i], LOW);
  }
  for (int i = 0; i < ArrayLength(motorArray); i = i + 2) {
    digitalWrite(motorArray[i], HIGH);
    digitalWrite(motorArray[i + 1], LOW);
  }
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    analogWrite(hBridgeEn[i], rate);
  }
  delay(60);
}

void off() { // Shuts off all the tires
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    digitalWrite(hBridgeEn[i], LOW);
  }
  for (int i = 0; i < ArrayLength(motorArray); i = i + 2) {
    digitalWrite(motorArray[i], LOW);
    digitalWrite(motorArray[i], LOW);
  }
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    digitalWrite(hBridgeEn[i], HIGH);
  }
  delay(50);
}


void boom() {  // Function prints out the distance of ping sensor
  int distance = ping();
  Serial.print("\nThe Distance is ");
  Serial.print(distance);
  Serial.print(" centimeters.");
}

int ping() { // function converts value from ping sensor to distance in centimeter
  long pingTime;
  trigger(); // triggers ping
  pingTime = pulseIn(echo, HIGH);  // value from the ping
  return ((pingTime / 29) / 2);  // returns value apprx in centermeter
  // 343 m/s and or 34.3 cm/ms -- speed of sound
  // ping sensor measures echo, time for echo return equals the amount of distance
}

void trigger() {  // triggers the ping sensor
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig, LOW);
}
