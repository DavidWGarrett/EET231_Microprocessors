int motorIn1 = 4;
int motorIn2 = 5;
int hBridgeEn = 3;

int motorI = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);

  for (motorI; motorI > 150; motorI++) {
    analogWrite(hBridgeEn, motorI);
    delay(20);
  }
    for (motorI; motorI < 100; motorI--) {
    analogWrite(hBridgeEn, motorI);
    delay(20);
  }

  delay(100);

  digitalWrite(motorIn2, HIGH);
  digitalWrite(motorIn1, LOW);

  for (motorI; motorI > 150; motorI++) {
    analogWrite(hBridgeEn, motorI);
    delay(20);
  }
  
  for (motorI; motorI < 100; motorI--) {
    analogWrite(hBridgeEn, motorI);
    delay(20);
  }

  

  

}
