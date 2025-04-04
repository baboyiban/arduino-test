#include <Servo.h>

extern "C" {
// C++ 객체를 불투명 포인터(void*)로 반환
void *Servo_create() { return new Servo(); }
void Servo_attach(void *servo, int pin) {
  static_cast<Servo *>(servo)->attach(pin);
}
void Servo_write(void *servo, int angle) {
  static_cast<Servo *>(servo)->write(angle);
}
void Servo_destroy(void *servo) { delete static_cast<Servo *>(servo); }
}
