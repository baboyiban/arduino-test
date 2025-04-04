#include <Servo.h>

Servo myservo;

void setup() { myservo.attach(6); }

void loop() {
  for (pos = 0; pos <= 120; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 120; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}
