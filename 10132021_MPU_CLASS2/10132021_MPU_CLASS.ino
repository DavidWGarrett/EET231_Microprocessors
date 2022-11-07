#include <Servo.h>
#include <Stepper.h>

int servoPin = 12;
int pause = 80;
int potPin = A0;

int in1 = 8;
int in2 = 9;
int in3 = 10;
int in4 = 11;
int stepsPerRev = 64; // for our stepper motor - 64 steps per rev

Stepper myStepper(stepsPerRev, in1, in2, in3, in4);

Servo myServo;


void setup() {
  // put your setup code here, to run once:
  //myServo.attach(servoPin);
  //myServo.write(0);

  myStepper.setSpeed(350); // 60 RPMS

}

void loop() {
  steppera();

}


void i80spin() {
  //put your main code here, to run repeatedly:
  for (int i = 0; i <= 179; i+=1) {
    myServo.write(i);
    delay(pause);
  }

  for ( int i = 179; i >= 0; i -= 1) {
    myServo.write(i);
    delay(pause);
  }

}


void potspin() {
  
  int potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1023, 0, 179);
  myServo.write(potValue);
  delay(50);
}


/// PING SENSOR MOUNTED ONTO SERVO HW (MAYBE LED??)


void steppera() {

  myStepper.step(stepsPerRev*32);
  delay(500);

  myStepper.step(-stepsPerRev*32);
  delay(500);
}
