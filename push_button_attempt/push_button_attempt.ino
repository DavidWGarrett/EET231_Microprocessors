int button = 7;
int red = 9;

void setup() {
  pinMode(button, INPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600);
  Serial.println("hello");

  digitalWrite(red, LOW);

}

void loop() {
  int touch = digitalRead(button);
  Serial.println(touch);
  if (touch == HIGH) {
    digitalWrite(red, HIGH);
  } else {
    digitalWrite(red, LOW);
  }
  delay(50);

}
