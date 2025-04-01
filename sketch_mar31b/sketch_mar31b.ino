#include <SoftwareSerial.h>           // 소프트웨어 시리얼 라이브러리 불러오기

#define TXD 2
#define RXD 3

SoftwareSerial mySerial(TXD, RXD);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
