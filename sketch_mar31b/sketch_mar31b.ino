#include <DHT.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <U8glib.h>

// Pin Definitions
#define TXD 2
#define RXD 3
#define DHTPIN 4
#define SERVO 5
#define DC_MOTOR 6
#define PULSE 7
#define PIR 8
#define PIEZO 9
#define DOOR_LED 10
#define MAGNETIC 11
#define ROOM_LED 12
#define LIVINGROOM_LED 13
#define OUTPUT_VOLTAGE A0
#define GAS_OUT A1
#define DHTTYPE DHT11

// Hardware Initialization
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(TXD, RXD);
Servo myservo;

// Global Variables
int LivingroomLedCount = 0;
int roomLedCount = 0;
byte motorStep = 0;
float preVoltage = 0;
float voltage = 0;
float dustDensity = 0;
float sumDustDensity = 0;
float avgDustDensity = 0;
bool gasAlertActive = false; // 추가: 가스 경고 상태 추적

void setup() {
  // Sensor Initialization
  dht.begin();
  myservo.attach(SERVO);
  myservo.write(80);

  // Communication Setup
  Serial.begin(9600);
  mySerial.begin(9600);

  // Pin Modes
  pinMode(DC_MOTOR, OUTPUT);
  pinMode(PULSE, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(DOOR_LED, OUTPUT);
  pinMode(MAGNETIC, INPUT_PULLUP);
  pinMode(ROOM_LED, OUTPUT);
  pinMode(LIVINGROOM_LED, OUTPUT);
  pinMode(OUTPUT_VOLTAGE, INPUT);
  pinMode(GAS_OUT, INPUT);

  digitalWrite(PULSE, LOW); // 미세먼지 센서 초기 상태 설정
}

void loop() {
  // 1. Safety Checks
  checkGasLeak();
  checkIntrusion();

  // 2. Environmental Monitoring
  measureEnvironment();

  // 3. Display Data
  updateDisplay();

  // 4. Bluetooth Control
  processBluetoothCommands();

  delay(1000); // 메인 루프 딜레이
}

// === 기능별 함수 분리 === //

void checkGasLeak() {
  int gasValue = analogRead(GAS_OUT);
  Serial.print("Gas: ");
  Serial.println(gasValue);

  if (gasValue >= 250 && !gasAlertActive) {
    gasAlertActive = true;
    triggerAlarm(2093, 1567, 5); // 고주파 경고음
    myservo.write(constrain(170, 0, 180));
    delay(200);
  } else if (gasValue < 200 && gasAlertActive) {
    gasAlertActive = false;
    myservo.write(80);
  }
}

void checkIntrusion() {
  int pirValue = digitalRead(PIR);
  int magneticValue = digitalRead(MAGNETIC);

  digitalWrite(DOOR_LED, pirValue == HIGH ? HIGH : LOW);

  if (magneticValue == 1 && pirValue == LOW) {
    triggerAlarm(6271, 4186, 2); // 저주파 알림음
  }
}

void measureEnvironment() {
  // DHT 측정
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) {
    Serial.println("DHT Error");
    return;
  }

  // 미세먼지 측정 (30회 평균)
  sumDustDensity = 0;
  for (int i = 0; i < 30; i++) {
    digitalWrite(PULSE, LOW);
    delayMicroseconds(280);
    preVoltage = analogRead(OUTPUT_VOLTAGE);
    delayMicroseconds(40);
    digitalWrite(PULSE, HIGH);
    delayMicroseconds(9680);

    voltage = preVoltage * 5.0 / 1024.0;
    dustDensity = max(0, (voltage - 0.3) / 0.005); // 음수 값 방지
    sumDustDensity += dustDensity;
    delay(10);
  }
  avgDustDensity = sumDustDensity / 30.0;
}

void updateDisplay() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_fub14);

    // 온도 표시
    u8g.setPrintPos(5, 20);
    u8g.print(dht.readTemperature(), 1);
    u8g.print("\xb0"
              "C");

    // 습도 표시
    u8g.setPrintPos(70, 20);
    u8g.print(dht.readHumidity(), 1);
    u8g.print("%");

    // 미세먼지 표시
    u8g.setFont(u8g_font_fub20);
    u8g.setPrintPos(40, 55);
    u8g.print(avgDustDensity, 1);

    // 가스 경고 표시 (추가)
    if (gasAlertActive) {
      u8g.setFont(u8g_font_fub11);
      u8g.setPrintPos(5, 40);
      u8g.print("GAS LEAK!");
    }
  } while (u8g.nextPage());
}

void processBluetoothCommands() {
  if (mySerial.available()) {
    byte input = mySerial.read();
    Serial.print("BT CMD: ");
    Serial.println(input);

    if (input >= 30) {
      motorStep = input % 10;
      input = input / 10;
    }

    switch (input) {
    case 1:
      LivingroomLedCount++;
      ledControl(LIVINGROOM_LED, LivingroomLedCount);
      break;
    case 2:
      roomLedCount++;
      ledControl(ROOM_LED, roomLedCount);
      break;
    case 3:
      motor_Control(motorStep);
      break;
    default:
      mySerial.println("Invalid CMD");
      break;
    }
  }
}

void ledControl(int pin, int count) {
  static bool ledState = false; // 상태 유지를 위해 static 변수 사용
  if (count % 2 == 1) {
    ledState = !ledState;
    digitalWrite(pin, ledState);
  }
}

void motor_Control(byte dcStep) {
  // 8단계 속도 제어 (0-7)
  int speed = map(dcStep, 0, 7, 0, 255);
  analogWrite(DC_MOTOR, constrain(speed, 0, 255));
}

void triggerAlarm(int freq1, int freq2, int cycles) {
  for (int i = 0; i < cycles; i++) {
    tone(PIEZO, freq1, 150);
    delay(200);
    tone(PIEZO, freq2, 150);
    delay(200);
  }
}
