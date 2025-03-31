#define MAGNETIC 7
#define PIR 8
#define GREEN_PIN 12
#define RED_PIN 13

bool occupied = false;

void setup() {
  pinMode(MAGNETIC, INPUT_PULLUP);
  pinMode(PIR, INPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int magneticValue = digitalRead(MAGNETIC);
  int pirValue = digitalRead(PIR);
  Serial.print("magnetic State: ");
  Serial.println(magneticValue);
  Serial.print("pir State : ");
  Serial.println(pirValue);

  if (magneticValue == 0 && pirValue == 1) {
    occupied = true;
  } else if (magneticValue == 1 && pirValue == 1) {
    occupied = false;
  }
  if (occupied == true) {
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
  } else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
  }
}
