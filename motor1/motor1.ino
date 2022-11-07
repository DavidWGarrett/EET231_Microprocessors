int motorIn1 = 4;
int motorIn2 = 5;
int hBridgeEn = 3;

int motorI = 124;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);

  delay(1000);

  analogWrite(hBridgeEn, motorI);

  delay(1000);

  analogWrite(hBridgeEn, 0);

  delay(1000);

  digitalWrite(motorIn2, HIGH);
  digitalWrite(motorIn1, LOW);

  delay(100);

  analogWrite(hBridgeEn, motorI);

  delay(1000);

  analogWrite(hBridgeEn, 0);

  delay(1000);

  

}
