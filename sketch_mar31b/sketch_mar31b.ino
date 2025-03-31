#define PIR_PIN 7
#define LED_PIN 6

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int value = digitalRead(PIR_PIN);
  if (value == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    delay(9000);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
