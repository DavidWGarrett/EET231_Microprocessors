// SER -- TAKES THE SERIAL INPUT
// RCLOCK LATCHES THE OUTPUT
// SRCLOCK FOR THE CLOCK

#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))

const int SER = 13; // PIN 14 ON SHIFT REGISTER
const int LATCH = 12; // PIN 12 ON SHIFT REGISTER
const int CLK = 11; // PIN 11 ON SHIFT REGISTER

const int trig = 10;
const int echo = 9;

int shiftRegister[] = {SER, LATCH, CLK};

int seq[14] = {1,2,4,8,16,32,64,128,64,32,16,8,4,2};

const int DIST =0; //Distance Sensor on Analog Pin 0
//Possible LED settings
int vals[9] = {0,1,3,7,15,31,63,127,255};

void setup() {
  // put your setup code here, to run once:

  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

  //shiftLatch(255);
  

}

void loop() {
  //count255();
  bookPing();
  //blink();

}

void blink() {
  for (int i = 0; i < ArrayLength(seq); i++) {
    digitalWrite(LATCH, LOW); //Latch Low - start sending
    shiftOut(SER, CLK, MSBFIRST, seq[i]); //Shift Most Sig. Bit First
    digitalWrite(LATCH, HIGH); //Latch High - stop sending
    delay(100);
  }
}

void shiftLatch(int var) { 
  digitalWrite(LATCH, LOW);
  shiftOut(SER, CLK, MSBFIRST, var);
  digitalWrite(LATCH, HIGH); 
}


int ping() { // function converts value from ping sensor to distance in centimeter
  long pingTime;
  trigger(); // triggers ping
  pingTime = pulseIn(echo, HIGH);  // value from the ping
  return pingTime; // returns value apprx in centermeter 
  // 343 m/s and or 34.3 cm/ms -- speed of sound
  // ping sensor measures echo, time for echo return equals the amount of distance
}

void trigger() {  // triggers the ping sensor
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
}

void bookPing() {
  int distance = ping();
  Serial.println(distance);
  distance = constrain(distance,0,12000);
  distance = map(distance, 0, 1200, 0, 255);
  distance = constrain(distance,0,255);
  digitalWrite(LATCH, LOW); //Latch low - start sending
  shiftOut(SER, CLK, MSBFIRST, distance); //Send data, MSB first
  digitalWrite(LATCH, HIGH); //Latch high - stop sending
  delay(100);
}

void count255() {
  for (int i=0; i<255; i++) {
    shiftLatch(i);
    delay(100);
  }
}
