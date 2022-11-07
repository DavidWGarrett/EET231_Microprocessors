// David Garrett
// Ch 5 - Lab - Servo + Ping = Awesome!
// 10-20-21

#include <Servo.h>  // includes servo header

// declarations/pin values for servo
int servoPin = 12;
int pause = 10;
Servo myServo; // creates object myServo

// declaration/pin values for ping sensor
int echo = 11;
int trig = 10;
int echoVal;

void setup() { // Setup servo, ping sensor, serial communication
  myServo.attach(servoPin);
  myServo.write(90);  // centers servo
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);


}

void loop() { // loops i80spin function
  i80spin();

}

void i80spin() {  // Spings servo 180 degrees back and forth
  for (int i = 0; i <= 179; i+=1) {  // Each number i represents a degree the servo can sping
    myServo.write(i);
    boom(); // prints out distance from ping sensor
    delay(pause);
  }

  for ( int i = 179; i >= 0; i -= 1) { // Each number i represents a degree the servo can sping
    myServo.write(i);
    boom(); // prints out distance from ping sensor
    delay(pause);
  }
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
