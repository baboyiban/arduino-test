#define PIR_PIN 7
#define PIEZO 6

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(PIEZO, OUTPUT);
}

void loop() {
  int value = digitalRead(PIR_PIN);
  if (value == HIGH) {
    for (int i = 0; i < 20; i++) {
      tone(PIEZO, 523, 250);
      delay(200);
      tone(PIEZO, 783, 250);
      delay(200);
    }
  }
}
