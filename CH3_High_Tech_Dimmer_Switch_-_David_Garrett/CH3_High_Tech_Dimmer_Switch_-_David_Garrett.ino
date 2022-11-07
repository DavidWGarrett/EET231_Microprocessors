// David Garrett
// CH3 High Tech Dimmer Switch
// 9-22-21

int potIn = A4;  // declarations and initialize pin variables
int ledPin = 3;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);  // Sets led pin to output
  Serial.begin(9600); // Begins serial communication for print statement

}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = (analogRead(potIn)); 
  // Creates variable to read the voltage of the potentiometer
  
  potValue = map(potValue, 0, 1023, 0, 255);
  // map function, converts the range of values from 0-1023 to 0-255
  
  Serial.print("The potentiometer reads: ");
  Serial.println(potValue); // Prints potentiometer value to the serial monitor
  analogWrite(ledPin, potValue); // Sets Brightness of LED
  delay(30);

}
