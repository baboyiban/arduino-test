#define MAGNETIC 7

void setup() {
  pinMode(MAGNETIC, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int value = digitalRead(MAGNETIC);
  Serial.println(value);
  delay(1000);
}
