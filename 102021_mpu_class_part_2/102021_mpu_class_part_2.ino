int redLed = 9;
int greenLed = 10;
int blueLed = 11;

const char rgb[] = "rgb";

void setup() {
  // put your setup code here, to run once:
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //chooseRgb();
  //Serial.print("hello");
  processInt();
  delay(300);

  //checkBuffer();

}

void chooseRgb() {

  if (Serial.available() > 0) {
    char dataIn = Serial.read();

    if (dataIn == rgb[0]) {
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
      digitalWrite(blueLed, LOW);
    }
    else if (dataIn == rgb[1]) {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
      digitalWrite(blueLed, LOW);
    }
    else if (dataIn == rgb[2]) {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, LOW);
      digitalWrite(blueLed, HIGH);
    }
    else if (dataIn = 't') {
      /// TOGGLE digitalWrite(redLed, !digitalRead(redLed));
    }
    else {
      Serial.println("Invalid Data");
    }
  }
}

void checkBuffer() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    Serial.print(data);
    delay(20);
  }
}

void processInt() {
  if (Serial.available() > 0) {
    int blueValue = Serial.parseInt();

    // if (blueValue > -1) {
    blueValue = constrain(blueValue, 0, 255);

    if (blueValue > -1 && blueValue < 256) {
      analogWrite(blueLed, blueValue);
    }
    /// abs(bluevalue) --- turns value positive
    Serial.println(blueValue);
  }
  
  //while (Serial.available()) {
}
