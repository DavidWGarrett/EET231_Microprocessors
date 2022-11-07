int potIn = A4;
int ledPin = 3;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = (analogRead(potIn));
  potValue = map(potValue, 0, 1023, 0, 255);
  Serial.print("The potentiometer reads: ");
  Serial.println(potValue);
  analogWrite(ledPin, potValue);
  delay(30);

}
