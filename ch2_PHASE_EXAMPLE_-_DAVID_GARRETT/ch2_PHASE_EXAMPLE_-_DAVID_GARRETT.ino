// Three LEDs blink one after another
// David Garrett
// 

int but = 0; // button
int red1 = 5; // first red led
int yl = 9; // yellow led
int red2 = 11; // second red led

void setup() {
  // put your setup code here, to run once:
  pinMode(red1, OUTPUT);
  pinMode(yl, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(but, INPUT);

}

void loop() {
  // put your main code here, to run r
  epeatedly:

  for(int i = 0; i <=255; i++) {
    analogWrite(red1, i);
    delay(25);
  }
  digitalWrite(yl, HIGH);


}
