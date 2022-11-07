// David Garrett
// 10-27-21
// CH7 Lab Controlling LEDs using serial input Part 2

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))

// LED pins declared and initialized
int redLed = 9;
int greenLed = 10;
int blueLed = 11;
int dataIn;
int ledBrightness = 255;
int redVal, greenVal, blueVal = 255;

int ledPins[] = {redLed, greenLed, blueLed};
int leddBrightness[] = {redVal, greenVal, blueVal};

void setup() {
  // Set LED pins to out; set up serial communications
  for (int i=0; i < ArrayLength(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);
  }
  
  Serial.begin(9600);
  Serial.setTimeout(100000);

  Serial.println("Input value 1-100 to control brightness of LED");
  Serial.println("Input negative value to flash the LED");

}

void loop() {
    // Sees if serial receive buffer has room
    if (Serial.available() > 0) {  
      dataIn = Serial.parseInt();  // reads serial input from serial monitor
      dataIn = constrain(dataIn, -1, 100);
      Serial.println("BEGINNING OF LOOP HIT");
      Serial.println(dataIn);
  
      if (dataIn == -1) { 
        for (int i=0; i < ArrayLength(ledPins); i++) {
          digitalWrite(ledPins[i], !digitalRead(ledPins[i]));
        }
        delay(500);
        for (int i=0; i < ArrayLength(ledPins); i++) {
          digitalWrite(ledPins[i], !digitalRead(ledPins[i]));
        }
        delay(500);
        for (int i=0; i < ArrayLength(ledPins); i++) {
          analogWrite(ledPins[i], ledBrightness);
        delay(100);
        }
      } //if ((dataIn > -1) && (dataIn < 101)) 
      else { 
        //int ledBrightness = constrain(dataIn, 0, 100);
        ledBrightness = map(dataIn, 0, 100, 0, 255);
        Serial.println("ELSE IF HIT");
        Serial.println(dataIn);
        
        for (int i=0; i < ArrayLength(ledPins); i++) {
          analogWrite(ledPins[i], ledBrightness);
        delay(100);
        }
      }
   }
}
