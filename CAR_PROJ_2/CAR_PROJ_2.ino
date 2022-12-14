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

void setup();
void loop();
void i80spin();
void pingStop();
void wheelSpeed();
int i80spinNoSpin();
void rightBack(int rateBackFunc);
void leftBack(int rateBackFunc);
void forward4(int rateRightFunc, int rateLeftFunc);
void off();
int ping();
int threePing();
void trigger();
int pingHighVal();

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

int ping1 = 200;
int ping2 = 200;
int ping3 = 200;
int ping4 = 200; 

int stopCmDist = 20;

int rate = 150; // step of motor
int rateLeft = 150;
int rateRight = 150;
int rateBack = 255;

int mapFuncCmMin = 20;
int mapFuncCmMax = 50;
int mapFuncLowSpeed = 160;
int mapFuncHighSpeed = 255;

int backSpinDelay = 350;

int cmLeft = 30;
int cmRight = 30;
int cmForward = 30;

int center = 90;
int iLeft = 120;
int iLeftMax = 145;
int iRight = 60;
int iRightMax = 35;
int i180spinSpeed = 1;
int i80spinDelay = 10;
int i80spinDelayForward = 150;

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

  int forward4(255, 255); // makes the motors work properly, needs to be high speed before going slow

  delay(50);

  Serial.begin(9600);

}

void loop() {
  forward4(rateRight, rateLeft); // drives forward
  i80spin(); // spins servo, pings, stops if ping sensor too close to object
  

}


void i80spin() {  // Spins servo 60 degrees back and forth

    cmForward = threePing();
    delay(i80spinDelayForward);
    myServo.write(iLeft);
    delay(i80spinDelay);

  for (int i = iLeft; i <= iLeftMax; i += i180spinSpeed) { // Each number i represents a degree the servo can spin
    // left spin
    myServo.write(i); // turn servo
    cmLeft = threePing();
    wheelSpeed();
    pingStop(); // ping sensor
  }
  myServo.write(center);
  delay(i80spinDelayForward);
  cmForward = threePing();
  delay(i80spinDelay);
  myServo.write(iRight);
  delay(i80spinDelay);

  for ( int i = iRight; i >= iRightMax; i -= i180spinSpeed) { // Each number i represents a degree the servo can spin
    // right spin
    myServo.write(i); // tern servo
    cmRight = threePing();
    wheelSpeed();
    pingStop(); // ping sensor
  }
    myServo.write(center);
    delay(i80spinDelayForward);
    cmForward = threePing();
    pingStop();
}

void pingStop() {
  int cmDist = threePing(); // figures out the distance in centimeter
  Serial.print("cmDist = ");
  Serial.println(cmDist);
  int forMapFunction = cmDist; // new value for map function
  if ( forMapFunction > mapFuncHighSpeed ) { // map function doesn't work without this if statement
    forMapFunction = mapFuncHighSpeed;       // maximum value is 400. Car won't run if value goes above 400 with map function
  }

  if (cmDist >stopCmDist ) { // if distance greater than 40cm, go forward
    forward4(rateRight, rateLeft);
  } else { // below 40 cm
    off(); // turn off
    delay(10);
    int PingVal = i80spinNoSpin(); // figure out if object is closer to left or right side of car
    if (PingVal == 1) { // if left, turn right. If right, turn left
      rightBack(rateBack);
    } else {
      leftBack(rateBack);
    }
    //delay(100);
    forward4(rateRight, rateLeft); // go forward again

  }
}

void wheelSpeed() {
    rateLeft = map(cmLeft, mapFuncCmMin, mapFuncCmMax, mapFuncLowSpeed, mapFuncHighSpeed);
    rateRight = map(cmRight, mapFuncCmMin, mapFuncCmMax, mapFuncLowSpeed, mapFuncHighSpeed);
}



int i80spinNoSpin() {  // Spings servo 180 degrees back and forth and pings

  off(); // makes the car stop moving
  int cmDistLeftHighestVal = 0;
  int cmDistRightHighestVal = 0;

  //////////////////////
  // Figures out which way to turn.
  // measure the ping on left and right side of car
  
  // turn ping sensor left
  
  for (int i = 150; i <= 179; i += 3) { // Each number i represents a degree the servo can sping
    myServo.write(i);
    delay(30);
    int cmDistLeft = threePing();
    if (cmDistLeft > cmDistLeftHighestVal) {
      cmDistLeftHighestVal = cmDistLeft;
    }
    delay(10);
  }

  
  myServo.write(90);
  delay(40);

  // turns ping sensor right and pings
   for ( int i = 30; i >= 0; i -= 3) { // Each number i represents a degree the servo can sping/    
    myServo.write(i);
    delay(30);
    int cmDistRight = threePing();
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

void rightBack(int rateBackFunc) { // makes the car turn right, only spins the left tires
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    digitalWrite(hBridgeEn[i], LOW);
  }
  for (int i = 0; i < ArrayLength(motorArray); i = i + 4) { // only writes to left tires
    digitalWrite(motorArray[i], LOW);
    digitalWrite(motorArray[i + 1], HIGH);
    digitalWrite(motorArray[i + 2], HIGH);
    digitalWrite(motorArray[i + 3], LOW);
  }
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    analogWrite(hBridgeEn[i], rateBackFunc);
  }
  delay(backSpinDelay);
}


void leftBack(int rateBackFunc) { // makes the car turn left, only spins the right tires
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    digitalWrite(hBridgeEn[i], LOW);
  }
  for (int i = 0; i < ArrayLength(motorArray); i = i + 4) { // only writes to right tires
    digitalWrite(motorArray[i], HIGH);
    digitalWrite(motorArray[i + 1], LOW);
    digitalWrite(motorArray[i + 2], LOW);
    digitalWrite(motorArray[i + 3], HIGH);
  }
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    analogWrite(hBridgeEn[i], rateBackFunc);
  }
  delay(backSpinDelay);
}

void forward4(int rateRightFunc, int rateLeftFunc) { // makes all the tires go forward
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    digitalWrite(hBridgeEn[i], LOW);
  }
  for (int i = 0; i < ArrayLength(motorArray); i = i + 2) {
    digitalWrite(motorArray[i], HIGH);
    digitalWrite(motorArray[i + 1], LOW);
  }
  //for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    //analogWrite(hBridgeEn[i], rate);
  //}
  analogWrite(hBridgeEnRight, rateRightFunc);
  analogWrite(hBridgeEnLeft, rateLeftFunc);
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
}

int ping() { // function converts value from ping sensor to distance in centimeter
  long pingTime;
  trigger(); // triggers ping
  pingTime = pulseIn(echo, HIGH);  // value from the ping
  return ((pingTime / 29) / 2);  // returns value apprx in centermeter
  // 343 m/s and or 34.3 cm/ms -- speed of sound
  // ping sensor measures echo, time for echo return equals the amount of distance
}

int threePing() {
  ping4 = ping3;
  ping3 = ping2;
  ping2 = ping1;
  ping1 = ping();

  if ( ping3 < stopCmDist && ping2 < stopCmDist && ping1 < stopCmDist && ping4 < stopCmDist ) {
    return ping1;
  } else if ( ping2 > ping3 && ping2 > ping3) {
    return ping2;
  } else if ( ping3 > ping4 ) {
    return ping3;
  } else {
    return ping4;
  }

  
}

void trigger() {  // triggers the ping sensor
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig, LOW);
}

//int pingHighVal() {
//  int cmDistFunc = threePing();
//  int cmDistHighestVal
//  if (cmDistFunc > cmDistHighestVal) {
//    cmDistHighestVal = cmDistFunc;
//  }
//}
  
