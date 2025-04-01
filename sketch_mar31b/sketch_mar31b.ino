#include <SoftwareSerial.h>

#define TXD 2
#define RXD 3

SoftwareSerial mySerial(TXD, RXD);

void setup() {
  mySerial.begin(9600);
}

void loop() {}
