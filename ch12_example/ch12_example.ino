/* Created by:  Mike Kwiatkowski
 *    Purpose:  To demonstrate how to make animation
 *              in an LCD cell
 *       Date:  November 6, 2019
 */

#include <LiquidCrystal.h>

byte balloon1[8] = {
  B00100,
  B01010,
  B10001,
  B10001,
  B01010,
  B00100,
  B00100,
  B00100
};

byte balloon2[8] = {
  B00000,
  B00100,
  B01010,
  B10001,
  B10001,
  B01010,
  B00100,
  B00100
};

byte balloon3[8] = {
  B00000,
  B00000,
  B00100,
  B01010,
  B10001,
  B10001,
  B01010,
  B00100
};

byte balloon4[8] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B01010,
  B10001,
  B10001,
  B01010
};

byte balloon5[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01010,
  B10001,
  B10001
};

LiquidCrystal lcd(2,3,4,5,6,7);


void setup() {
  lcd.begin(16,2);
  lcd.print("My great LCD!");
  lcd.createChar(0, balloon1);
  lcd.createChar(1, balloon2);
  lcd.createChar(2, balloon3);
  lcd.createChar(3, balloon4);
  lcd.createChar(4, balloon5);


}

void loop() {
  for(byte i=0; i < 5; i++){
    lcd.setCursor(0,1);
    lcd.write(i);
    delay(500);
  }
}
