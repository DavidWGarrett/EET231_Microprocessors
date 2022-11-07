int motorIn1 = 4;
int motorIn2 = 5;
int hBridgeEn = 3;
int speedPin = A0;
int echo = 11;
int trig = 10;
int echoVal;


int rate = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //forward(rate);
  //off();
  //backward(rate);
  //off();

  //speedPot();


  boom();

}

void forward(int rate) {
  digitalWrite(hBridgeEn, LOW);
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  analogWrite(hBridgeEn, rate);
  delay(900);
}

void backward(int rate) {
  digitalWrite(hBridgeEn, LOW);
  digitalWrite(motorIn2, HIGH);
  digitalWrite(motorIn1, LOW);
  analogWrite(hBridgeEn, rate);
  delay(900);
}

void off() {
  digitalWrite(hBridgeEn, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn1, LOW);
  analogWrite(hBridgeEn, HIGH);
  delay(900);
}

void speed() {
  int motorSpeed = (analogRead(speedPin)); 
  motorSpeed = map(motorSpeed, 0, 1023, 0, 255);
}

void speedPot() {
  int motorControl = analogRead(speedPin);
  
  if (motorControl > 520) {
    motorControl = map(motorControl, 521, 1023, 0, 255);
    forward(motorControl);
  }
  else if (motorControl < 500) {
    motorControl = map(motorControl, 499, 0, 0, 255);
    backward(motorControl);
  }
  else {
    off();
  }
}

void trigger() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
}

void boom() {
  int distance = ping();
  Serial.println(distance);
  delay(20);
}

int ping() {
  long pingTime;
  trigger();
  pingTime = pulseIn(echo, HIGH);
  return ((pingTime / 29) / 2);  // returns value apprx in centermeter
  // I have no idea what the conversion is, but the speed of sound is 
  // 343 m/s and or 34.3 cm/ms
  // measures
  // https://lastminuteengineers.com/arduino-sr04-ultrasonic-sensor-tutorial/
  
}
