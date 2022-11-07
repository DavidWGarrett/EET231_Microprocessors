// David Garrett
// 11-17-21
// Ch 12 - Homework - LCD I/O 

// Combine input and processing with output on the LCD panel

// Procedure:

    // Connect the LCD and test that it is working
    // Connect your photo resistor for input
    // Display messages like Dark, Normal and Bright on the screen
    // Connect the distance sensor
    // Display the distance in centimeters
    // Have both inputs displayed simultaneously

#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);  // CREATES LCD OBJECT
                                 // RS, E, D4, D5, D6, D7
    
int photo = A0;                  // Analog pin for photoresistor

int echo = 13;                   // declaration/pin values for ping sensor
int trig = 12;
int echoVal;

void setup() {
  lcd.begin(16,2);               // what's the layout of panel? 16 col, 2 row

  pinMode(trig, OUTPUT);         // Sets trig pin on ping sensor as output
  pinMode(echo, INPUT);          // Sets echo pin on ping sensor as input
  
  Serial.begin(9600);

}

void loop() {
  displayBrightness();           // Display brightness level in row 1
  displayDistance();             // Display distance in cm in row 2
  delay(100);
  lcd.clear();                   // clear the screen
}

void displayBrightness() {

  // Displays brightness on the LCD screen

  // Bright    < 100
  // Normal    100-250
  // Dark      > 250

  
  int photoValue = (analogRead(photo)); // stores value of photo sensor analog input
  lcd.setCursor(0,0); // Displays brightness value on row 1 of LCD
  lcd.print("BRIGHTNESS: ");
  
  if (photoValue < 100) {
    lcd.print("HIGH");
  } else if (photoValue > 250) {
    lcd.print("LOW");
  } else {
    lcd.print("MED");
  }
}

void displayDistance() {

  // Display distance in centimeter on the LCD screen

  lcd.setCursor(0,1); // Displays distane value on row 2 of LCD
  lcd.print("DISTANCE: ");
  int dist = ping();  // ping() returns a value that equals the amount of cm
  lcd.print(dist);
  lcd.print("cm");
  
}

int ping() { // function converts value from ping sensor to distance in centimeter
  int pingTime;
  trigger(); // triggers ping
  pingTime = pulseIn(echo, HIGH);  // value from the ping
  Serial.print("Ping Time: ");
  Serial.println(pingTime);
  return ((pingTime / 29) / 2);  // returns value apprx in centermeter 
  // 343 m/s and or 34.3 cm/ms -- speed of sound
  // ping sensor measures echo, time for echo return equals the amount of distance
}

void trigger() {  // triggers the ping sensor
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
}
