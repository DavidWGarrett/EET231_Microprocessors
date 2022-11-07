//...............JehanKandy........................
//...........www.jehankandy.com....................
//........www.github.com/JehanKandy................

//include liquidCrystal_I2C.h 
//Tools -> Manage Libraries and type liquidCrystal_I2C

#include <LiquidCrystal_I2C.h>

//define I2C address......
LiquidCrystal_I2C lcd(0x27,16,2);


void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(2,0);
  lcd.print("Hello World");

  lcd.setCursor(2,1);
  

}

void loop() {
  coordinates();

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
