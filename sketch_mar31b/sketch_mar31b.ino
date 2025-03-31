#include <Servo.h>

#define GAS_OUT A0
#define PIEZO 6
#define SERVO 5

Servo myservo;

void setup() {
  pinMode(GAS_OUT, INPUT);
  pinMode(PIEZO, OUTPUT);
  myservo.attach(SERVO);
  myservo.write(15);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(GAS_OUT);

  if (value >= 250) {
    for (int i = 0; i < 5; i++) {
      tone(PIEZO, 2093, 250);
      delay(200);
      tone(PIEZO, 1567, 250);
      delay(200);
    }
    myservo.write(90);
    delay(200);
    myservo.detach();
  }
  Serial.print("Gas data : ");
  Serial.println(value);
  delay(1000);
}
