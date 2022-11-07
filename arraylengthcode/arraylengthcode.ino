#define ArrayLength(x) (sizeof(x) / sizeof(x[0]))

int ledPins[] = {2,3,4,5,6}; // Creates an array of all the pin numbers

void setup() {
  // put your setup code here, to run once:

    for (int i=0; i < ArrayLength(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:

}

for (int i=0; i < ArrayLength(ledPins); i++) {
