// David Garrett
// 11-17-21
// Ch 12 - Lab - LCD output with special characters

// The goal of this lab is to gain familiarity with the LCD panel by sending programmed messages out to the panel and then generating a special character.

// Procedure:

   // Connect LCD panel as described in the class text
   // Output a message to line one of the display
   // Use line two to display a series of animated special characters which you designed
   // Use at least three special characters to see the animation
   // See the attached sketch for an example

// Demonstrate and turn in sketch to Sakai

#include <LiquidCrystal.h> // Includes liquidcrystal header to use functions for LCD
LiquidCrystal lcd(2,3,4,5,6,7); // CREATES LCD OBJECT
// RS, E, D4, D5, D6, D7

// Three Arrays to demostrate an ugly looking pacman on an LCD screen

byte pac1[] = { 
                  B00111, 
                  B01110, 
                  B11100, 
                  B11000, 
                  B11100, 
                  B01110, 
                  B00111, 
                  B00000 };


byte pac2[] = { 
                  B00110, 
                  B01111, 
                  B11110, 
                  B11100, 
                  B11110, 
                  B01111, 
                  B00110, 
                  B00000 };

byte pac3[] = { 
                  B00100, 
                  B01110, 
                  B11111,
                  B11111, 
                  B11111, 
                  B01110, 
                  B00100, 
                  B00000 };

// empty space                  
byte blank[] = {
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B00000,
};

void setup() {
  // CREATECHAR BEFORE BEGIN  
  lcd.createChar(1, pac1); // PUTS PAC1 ARRAY IN REGISTER 1
  lcd.createChar(2, pac2); // PUTS PAC1 ARRAY IN REGISTER 2
  lcd.createChar(3, pac3); // PUTS PAC3 ARRAY IN REGISTER 3
  lcd.createChar(4, blank); // PUTS BLANK ARRAY IN REGISTER 4

  lcd.begin(16,2); // what's the layout of panel? 16 col, 2 row
  lcd.print("UGLY PACMAN!! (<"); // words get printed on first row of LCD
}

void loop() {
  pacAttack(); // loops pacAttack

}

void pacAttack() {
  lcd.setCursor(0,1); // sets cursor to left side bottom row of LCD
  for (int i=0; i<16; i++) { // LCD 16 spaces wide, for loop stops at i reaches 16
    lcd.write(1); // writes first pacman image
    delaySetWrite4(i); // clears image
    i++; // increase i value by 1
    lcd.write(2); // writes second pacman image
    delaySetWrite4(i);  // clears image
    i++; // increase i value by 1
    lcd.write(3); // writes third pacman image
    delaySetWrite4(i); // clears image
  }
}

void delaySetWrite4(int i) { // Function includes delay, reposition the cursor on screen
  // function writes blank space where the pacman previous was at so the screen isn't filled with pacmans
  delay(400);
  lcd.setCursor(i,1);
  lcd.write(4);
}
