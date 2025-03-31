#define A_OUT A0
#define PIEZO 6

void setup() {
  pinMode(A0, INPUT);
  pinMode(PIEZO, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(A0);

  if (value >= 250) {
    for (int i = 0; i < 5; i++) {
      tone(PIEZO, 2093, 250);
      delay(200);
      tone(PIEZO, 1567, 250);
      delay(200);
    }
  }
  Serial.print("Gas data : ");
  Serial.println(value);
  delay(1000);
}
