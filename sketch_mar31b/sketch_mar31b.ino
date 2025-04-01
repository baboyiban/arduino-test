#include <SoftwareSerial.h>
#include <DHT.h>

#define TXD 2
#define RXD 3
#define INPUT_PULSE 4
#define MOTOR 6
#define DHTPIN 7
#define LED 8
#define DHTTYPE DHT11
#define OUTPUT_VOLTAGE A0

SoftwareSerial mySerial(TXD, RXD);
DHT dht(DHTPIN, DHTTYPE);

float preVoltage = 0;
float voltage = 0;
float dustDensity = 0;
float sumDustDensity = 0;
float avgDustDensity = 0;

void setup() {
  mySerial.begin(9600);
  dht.begin();
  pinMode(INPUT_PULSE, OUTPUT);
  pinMode(OUTPUT_VOLTAGE, INPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  sumDustDensity = 0;

  for (int i = 0; i < 30; i++) {
    digitalWrite(INPUT_PULSE, LOW);
    delayMicroseconds(280);
    preVoltage = analogRead(OUTPUT_VOLTAGE);
    delayMicroseconds(40);
    digitalWrite(INPUT_PULSE, HIGH);
    delayMicroseconds(9680);
    voltage = preVoltage * 5.0 / 1024.0;
    dustDensity = (voltage - 0.3) / 0.005;
    sumDustDensity += dustDensity;
    delay(10);
  }

  avgDustDensity = sumDustDensity / 30.0;

  if (isnan(humidity) || isnan(temperature)) {
    return;
  }

  if (mySerial.available()) {
    char input = (char) mySerial.read();

    switch(input) {
      case '1':
        digitalWrite(LED, HIGH);
        break;
      case '2':
        digitalWrite(LED, LOW);
        break;
      case '3':
        digitalWrite(MOTOR, 64);
        break;
      case '4':
        digitalWrite(MOTOR, 128);
        break;
      case '5':
        digitalWrite(MOTOR, 192);
        break;
      case '6':
        digitalWrite(MOTOR, 0);
        break;
    }
  }

  mySerial.println(String(humidity) + "%, " + String(temperature) + "C, " + String(avgDustDensity) + "ug/m3");
}
