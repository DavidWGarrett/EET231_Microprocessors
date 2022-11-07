// David Garrett
// CH9 Sequentially Blinking LEDs Knight Rider
// 11=3=21

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))  // Macro gives length of an array

const int SER = 13; // PIN 14 ON SHIFT REGISTER
const int LATCH = 12; // PIN 12 ON SHIFT REGISTER
const int CLK = 11; // PIN 11 ON SHIFT REGISTER

int seq[8] = {1,2,4,8,16,32,64,128}; // values that displays a singular LED

void setup() {
  // Output pins for 74HC595 shift register 
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);

}

void loop() {
  blinkKnightRider();

}


void blinkWithArray(int pinArray[], int arrayIndex) {
  
    // latches a certain value on 74HC595 shift register
    
    digitalWrite(LATCH, LOW); // Latch Low - start sending
    shiftOut(SER, CLK, MSBFIRST, pinArray[arrayIndex]); // Shift Most Sig. Bit First
    digitalWrite(LATCH, HIGH); // Latch High - stop sending
    delay(100);
}


void blinkKnightRider() {

  // creates value that iterates up by one till equal the size of an array
  // then value iterates down by 1 till equal 0
  
  // for loop iterates up through each LED till last one
  for (int i = 0; i < ArrayLength(seq); i++) {
    blinkWithArray(seq, i);
    if (i==7) { // when last LED lights up, if statement triggers
      delay(100); // extra delay when the LED lights reach an end point
      for (i; i>-1; i--) { // iterates down through each LED till last one
         blinkWithArray(seq, i);
      }
      delay(100); // extra delay when the LED lights reach an end point
    }
  }
}
