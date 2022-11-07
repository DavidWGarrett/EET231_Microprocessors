// 11-10-21 NOTES
// FOR ASSIGNMENTS, USE PHOTO RESISTOR CONNECTED TO GROUND, 10K RESISTOR CONNECTED TO GROUND, BETWEEN TWO RESISTOR CONNECTED TO ANALOG PIN
// EACH CELL IS 5 PIXEL ACROSS, 8 PIXELS UP AND DOWN

byte smile[] = { 
                  B00000, 
                  B11011, 
                  B11011, 
                  B00100, 
                  B00000, 
                  B10001, 
                  B01010, 
                  B00100 };

byte frown[] = { 
                  B00000, 
                  B11011, 
                  B11011, 
                  B00100, 
                  B00010, 
                  B00101, 
                  B01010, 
                  B10100 };

byte pac[] = { 
                  B00110, 
                  B01111, 
                  B11110, 
                  B11100, 
                  B11110, 
                  B01111, 
                  B00110, 
                  B00000 };


#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7); // CREATES LCD OBJECT
// RS, E, D4, D5, D6, D7
// DON'T CARE ABOUT PINS AFTER OBJECT IS MADE

void setup() {
  // put your setup code here, to run once:
  // CREATECHAR BEFORE BEGIN  
  lcd.createChar(2, pac); // PUTS SMILEY ARRAY IN REGISTER 0
  lcd.createChar(1, frown);
  lcd.begin(16,2); // what's the layout of panel? 16 col, 2 row
  //lcd.autoscroll();
  //lcd.setCursor(0,2);
  lcd.print("hello?");
  lcd.print("MAH DUDE");
  //lcd.createChar(0, smile); // PUTS SMILEY ARRAY IN REGISTER 0
  lcd.write(2); // DISPLAY COTENTS OF REGISTER 0
  lcd.write(1);
  // IF YOU USE REGISTER 0, THE WRITE COMMAND NEEDS byte(0) 
}

void loop() {
  //coordinates();

}


void coordinates() {
  for (int i=0; i<101; i++) {
    lcd.setCursor(0,1);
    lcd.print(i);
    delay(50);
  }
  lcd.setCursor(0,1);  // THREE SPACES CLEAR NUMBER, THE ZERO STAYS IF IT ISN'T CLEARED BY SPACES
  lcd.print("   ");
}
