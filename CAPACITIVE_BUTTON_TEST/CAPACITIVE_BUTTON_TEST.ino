int button = A0;
int red = 9;

void setup() {
  pinMode(button, INPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int touch = analogRead(button);
  Serial.println(touch);
  if (touch == 1023) {
    digitalWrite(red, HIGH);
  } else {
    digitalWrite(red, LOW);
  }

}
