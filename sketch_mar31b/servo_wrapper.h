#ifdef __cplusplus
extern "C" {
#endif

void *Servo_create();
void Servo_attach(void *servo, int pin);
void Servo_write(void *servo, int angle);
void Servo_destroy(void *servo);

#ifdef __cplusplus
}
#endif
