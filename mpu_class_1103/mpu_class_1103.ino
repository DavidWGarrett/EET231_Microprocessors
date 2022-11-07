// I2C - BUS STYLE CONNECTOR
// USB UNIVERSAL SERIAL BUS
// SDA/SCL - CAN CONTROL A COLLECTION OF PERIPHERALS
// INPUT AND OUTPUT PERIPHERALS
// SDA - DATA; SCL - CLOCK
// I2C SLAVE, I2C MASTER (ARDUINO)
// SPEC SHEET SPECIFY ADDRESS OF I2C SLAVE

//  Wire.begin(); // join i2c bus (address optional for master)
//Wire.beginTransmission(44); // transmit to device #44 (0x2c)
// device address is specified in datasheet
//Wire.write(byte(0x00));            // sends instruction byte
//Wire.write(val);             // sends potentiometer value byte
//Wire.endTransmission();     // stop transmitting
//Wire.requestFrom(112, 2); // address, bytes

// SPI BUS SIMILAR TO I2C
// MOSI AND MISO
// MOSI MASTER OUTPUT SLAVE INPUT  -- MISO MASTER INPUT SLAVE OUTPUT
// NO ADDRESS, USES ANOTHER PIN CALLED SS^-(ACTIVE LOW) SLAVE SELECT
// ARDUINO NEEDS A PIN FOR EACH SLAVE SELECT

// SPI.begin();
// send in the address and value via SPI:
// SPI.transfer(address);
// SPI.transfer(value);

// ARDUINO HAS DUAL PURPOSE PINS
// A4 & A5 FOR I2C COMMUNICATION
// SPI PIN 11 MOSI 12 MISO




// David Garrett
// CH9 Sequentially Blinking LEDs Knight Rider
// 11-10-21

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))  // Macro gives length of an array

const int SER = 13; // PIN 14 ON SHIFT REGISTER
const int LATCH = 12; // PIN 12 ON SHIFT REGISTER
const int CLK = 11; // PIN 11 ON SHIFT REGISTER

int num0 = 63; // 0 = ABCDEF = 63
int num1 = 6; // 1 = BC = 6
int num2 = 91;// 2 = ABDEG = 91
int num3 = 79; // 3 = ABCDG = 79
int num4 = 102;// 4 = BCFG = 102
int num5 = 109; // 5 = ACDFG = 109
int num6 = 124; // 6 = CDEFG = 124
int num7 = 7; // 7 = ABC = 7
int num8 =127; // 8 = ABCDEFG = 127
int num9 =103; // 9 = ABCFG = 103

// array of all the number values for the digits on 7-segment LED
int numList[10] = { num0, num1, num2, num3, num4, num5, num6, num7, num8, num9 };

void setup() {
  // Output pins for 74HC595 shift register 
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);

}
void loop() {
  blink7segment();

}

void blinkWithArray(int pinArray[], int arrayIndex) {
  
    // latches a certain value on 74HC595 shift register
    
    digitalWrite(LATCH, LOW); // Latch Low - start sending
    shiftOut(SER, CLK, MSBFIRST, pinArray[arrayIndex]); // Shift Most Sig. Bit First
    digitalWrite(LATCH, HIGH); // Latch High - stop sending
    delay(300);
}


void blink7segment() {

  // function counts up from 0 to 9, then down from 9 to 0

  // creates value that iterates up by one till equal the size of an array
  // then value iterates down by 1 till equal 0
  
  for (int i = 0; i < ArrayLength(numList); i++) {
    blinkWithArray(numList, i);
    if (i==ArrayLength(numList)-1) { // when #9 lights up, if statement triggers
      delay(200); // extra delay when the LED lights reach an end point
      for (i; i>-1; i--) { // iterates down through each number on 7 segment LED till #0
         blinkWithArray(numList, i);
      }
      delay(200); // extra delay when the LED lights reach an end point
    }
  }
}

//BATTERY, ARDUINO, PING, AND H BRIDGE
