// Three LEDs blink one after another
// David Garrett
// 

int but = 0; // button
int red1 = 8; // first red led
int yl = 10; // yellow led
int red2 = 12; // second red led

void setup() {
  // put your setup code here, to run once:
  pinMode(red1, OUTPUT);
  pinMode(yl, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(but, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  for(int i = 50; i <=1000; i+=50) {
    digitalWrite(red1, HIGH);
    delay(i);
    digitalWrite(red1, LOW);
    delay(i);
  }
  digitalWrite(yl, HIGH);


}
