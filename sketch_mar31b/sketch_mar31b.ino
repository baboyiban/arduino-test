#include <SoftwareSerial.h>
#include <DHT.h>

#define TXD 2
#define RXD 3
#define INPUT_PULSE 4
#define DHTPIN 7
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

  mySerial.print(humidity, 1);
  mySerial.print("%\t");
  mySerial.print(temperature, 1);
  mySerial.print("C\t");
  mySerial.print(avgDustDensity, 1);
  mySerial.println("ug/m3");
}
