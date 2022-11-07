// David Garrett
// Ch 9 - Lab - Binary Counting with Shift Registers 
// 11-3-21

const int SER = 13; // PIN 14 ON SHIFT REGISTER
const int LATCH = 12; // PIN 12 ON SHIFT REGISTER
const int CLK = 11; // PIN 11 ON SHIFT REGISTER

void setup() {
  // Output pins for 74HC595 shift register 
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);

}

void loop() {
  count255();

}

void shiftLatch(int var) { 

  // latches a certain value on 74HC595 shift register
  
  digitalWrite(LATCH, LOW);
  shiftOut(SER, CLK, MSBFIRST, var);
  digitalWrite(LATCH, HIGH); 
}

void count255() {

  // creates value that iterates up by one till equals (2^8 - 1)
  // 255 (or 11111111 binary) is the highest value that 74HC595 can output
  
  for (int i=0; i<255; i++) {
    shiftLatch(i); // lights LEDs
    delay(50);
  }
}
