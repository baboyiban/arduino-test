#include <SoftwareSerial.h>

#define TXD 2
#define RXD 3
#define LED 13

SoftwareSerial mySerial(TXD, RXD);

void ledControl(int pin, int count);

int ledCount = 0;

void setup() {
  mySerial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (mySerial.available()) {
    byte input = mySerial.read();

    switch(input) {
      case 1:
      ledCount++;
      ledControl(LED, ledCount);
      break;
    }
  }
}

void ledControl(int pin, int count) {
  if (count % 2 == 1) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}
