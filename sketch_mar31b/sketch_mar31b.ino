#define A_OUT A0

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(A0);
  Serial.print("Gas data : ");
  Serial.println(value);
  delay(1000);
}
