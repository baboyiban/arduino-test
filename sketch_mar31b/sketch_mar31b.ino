#define PIEZO 6
#define MAGNETIC 7
#define PIR 8

void setup() {
  pinMode(PIEZO, OUTPUT);
  pinMode(MAGNETIC, INPUT_PULLUP);
  pinMode(PIR, INPUT);
  Serial.begin(9600);
}

void loop() {
  int magneticValue = digitalRead(MAGNETIC);
  int pirValue = digitalRead(PIR);
  Serial.print("magnetic State : ");
  Serial.println(magneticValue);
  Serial.print("pir State : ");
  Serial.println(pirValue);

  if (magneticValue == 1 && pirValue == 0) {
    for (int i = 0; i < 2; i++) {
      tone(PIEZO, 6271, 150);
      delay(200);
      tone(PIEZO, 4186, 150);
      delay(200);
    }
  }
  delay(1000);
}
