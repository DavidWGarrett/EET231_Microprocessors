// SERVO --- RED 5V, ORANGE SIG, BROWN GND

#include <Servo.h>  // includes servo header

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))

//////////////////////////////////
//FRONT IN1/IN2 ---- Front Right Tire
//When IN2 HIGH/IN4 LOW --- Forward

//FRONT IN3/IN4 --- Front Left Tire
//When IN3 HIGH/IN4 LOW - Forward

//Back IN1 IN2 ---- Back Right Tire
//IN1 High IN2 Low --- Forward

//Back IN3/IN Back Right Tire
//When IN4 High, IN3 Low -- Forward


///// IN1/2  === RIGHT SIDE
///// IN3/4  === LEFT SIDE
///////////////////////////////////////


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
int rate = 150;

int motorArray[] = {motorIn1Front, motorIn2Front, motorIn3Front, motorIn4Front,
                    motorIn1Back, motorIn2Back, motorIn3Back, motorIn4Back
                   };

int hBridgeEn[] = {hBridgeEnRight, hBridgeEnLeft};

// declarations/pin values for servo
int servoPin = 5;
int pause = 11;
Servo myServo; // creates object myServo

// declaration/pin values for ping sensor
int echo = 12;
int trig = 13;
int echoVal;

int avoidPin = 4;


void setup() {
  for (int i = 0; i < ArrayLength(motorArray); i++) {
    pinMode(motorArray[i], OUTPUT);
  }

  myServo.attach(5);
  myServo.write(90);  // centers servo
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(avoidPin, INPUT);


  Serial.begin(9600);
}

void loop() {
  //forward4(rate);
  //i80spin();
  
  Serial.print("AvoidPin: ");
  Serial.println(digitalRead(avoidPin));

  //pingStop()
  //Serial.println("END OF LOOP");

  //i80spin();
  delay(100);

}

void pingStop() {
  int cmDist = ping();
  int forMapFunction = cmDist;
  if ( forMapFunction > 400 ) {
    forMapFunction = 400;
  }
  rate = map(forMapFunction, 30, 400, 135, 200);
//  Serial.print("ping stop: ");
//  Serial.println(cmDist);
  if (cmDist > 40 ) {
    forward4(rate);
  } else {
    off();
    delay(50);
    int PingVal = i80spinNoSpin();
    if (PingVal == 1) {
      rightBack(rate);
    } else {
      leftBack(rate);
    }
    delay(300);
    forward4(rate);
    
  }
}

void i80spin() {  // Spings servo 180 degrees back and forth
  for (int i = 90; i <= 110; i += 5) { // Each number i represents a degree the servo can sping
    myServo.write(i);
    pingStop();
  }

  for ( int i = 110; i >= 70; i -= 5) { // Each number i represents a degree the servo can sping
    myServo.write(i);
    pingStop();
  }
    for (int i = 70; i <= 90; i += 5) { // Each number i represents a degree the servo can sping
    myServo.write(i);
    pingStop();
  }
}

int i80spinNoSpin() {  // Spings servo 180 degrees back and forth

  off();
  int cmDistLeftHighestVal = 0;
  int cmDistRightHighestVal = 0;
  
  for (int i = 120; i <= 179; i += 1) { // Each number i represents a degree the servo can sping
    myServo.write(i);
    int cmDistLeft = ping();
    if (cmDistLeft > cmDistLeftHighestVal) {
      cmDistLeftHighestVal = cmDistLeft;
    }
    delay(10);
  }
  Serial.print("Left ping: ");
  Serial.println(cmDistLeftHighestVal);
  myServo.write(90);
  delay(10);

  for ( int i = 60; i >= 0; i -= 1) { // Each number i represents a degree the servo can sping
    myServo.write(i);
    int cmDistRight = ping();
    if (cmDistRight > cmDistRightHighestVal) {
      cmDistRightHighestVal = cmDistRight;
    }
    delay(10);
  }
  Serial.print("Right ping: ");
  Serial.println(cmDistRightHighestVal);
  myServo.write(90);
  delay(1);

  if ( cmDistLeftHighestVal > cmDistRightHighestVal ) {
    return 0;
  } else {
    return 1;
  }
}

void rightBack(int rate) {
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    digitalWrite(hBridgeEn[i], LOW);
  }
  for (int i = 0; i < ArrayLength(motorArray); i = i + 4) {
    digitalWrite(motorArray[i], LOW);
    digitalWrite(motorArray[i + 1], HIGH);
  }
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    analogWrite(hBridgeEn[i], rate);
  }
  delay(500);
}


void leftBack(int rate) {
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    digitalWrite(hBridgeEn[i], LOW);
  }
  for (int i = 2; i < ArrayLength(motorArray); i = i + 4) {
    digitalWrite(motorArray[i], LOW);
    digitalWrite(motorArray[i + 1], HIGH);
  }
  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
    analogWrite(hBridgeEn[i], rate);
  }
  delay(500);
}

//void forward5(int rate) {
//  digitalWrite(hBridgeEnFront, LOW);
//
//}

void forward4(int rate) {
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

//void forward3(int rate) {
//  digitalWrite(hBridgeEnBack, LOW);
//  digitalWrite(motorIn3Back, HIGH);
//  digitalWrite(motorIn4Back, LOW);
//  delay(20);
//  analogWrite(hBridgeEnBack, rate);
//  delay(900);
//}

//void forward2(int rate) {
//  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
//    digitalWrite(hBridgeEn[i], LOW);
//  }
//  for (int i = 0; i < ArrayLength(motorArray); i + 2) {
//    digitalWrite(motorArray[i], HIGH);
//  }
//  for (int i = 1; i < ArrayLength(motorArray); i + 2) {
//    digitalWrite(motorArray[i], LOW);
//  }
//  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
//    analogWrite(hBridgeEn[i], rate);
//  }
//  delay(900);
//}

//void forward(int rate) {
//  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
//    digitalWrite(hBridgeEn[i], LOW);
//  }
//  for (int i = 0; i < ArrayLength(motorArray); i + 2) {
//    digitalWrite(motorArray[i], HIGH);
//  }
//  for (int i = 1; i < ArrayLength(motorArray); i + 2) {
//    digitalWrite(motorArray[i], LOW);
//  }
//  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
//    analogWrite(hBridgeEn[i], rate);
//  }
//  delay(900);
//}

//void backward(int rate) {
//  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
//    digitalWrite(hBridgeEn[i], LOW);
//  }
//  for (int i = 0; i < ArrayLength(motorArray); i = i + 2) {
//    digitalWrite(motorArray[i], LOW);
//    digitalWrite(motorArray[i], HIGH);
//  }
//  for (int i = 0; i < ArrayLength(hBridgeEn); i++) {
//    analogWrite(hBridgeEn[i], rate);
//  }
//  delay(900);
//}

void off() {
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


//void i80spin() {  // Spings servo 180 degrees back and forth
//  for (int i = 0; i <= 179; i += 1) { // Each number i represents a degree the servo can sping
//    myServo.write(i);
//    pingStop();
//    delay(3);
//  }
//
//  for ( int i = 179; i >= 0; i -= 1) { // Each number i represents a degree the servo can sping
//    myServo.write(i);
//    pingStop();
//    delay(3);
//  }
//}

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
