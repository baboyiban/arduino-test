#include <SoftwareSerial.h>

// HC-06 RX 핀을 아두이노 디지털 핀 2에 연결
// HC-06 TX 핀을 아두이노 디지털 핀 3에 연결
SoftwareSerial bluetoothSerial(2, 3); // RX, TX

// LED를 연결할 아두이노 디지털 핀
const int ledPin = 13;

void setup() {
  // 아두이노 기본 시리얼 통신 설정 (디버깅 용)
  Serial.begin(9600);
  Serial.println("Bluetooth 통신 시작");

  // Bluetooth 시리얼 통신 설정
  bluetoothSerial.begin(9600);

  // LED 핀을 출력으로 설정
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // 초기 상태는 LED 꺼짐
}

void loop() {
  // Bluetooth로부터 데이터가 수신되었는지 확인
  if (bluetoothSerial.available()) {
    char receivedChar = bluetoothSerial.read();
    Serial.print("수신된 데이터: ");
    Serial.println(receivedChar);

    // 수신된 문자에 따라 LED 제어
    if (receivedChar == '1') {
      digitalWrite(ledPin, HIGH); // LED 켜기
      bluetoothSerial.println("LED ON");
    } else if (receivedChar == '0') {
      digitalWrite(ledPin, LOW);  // LED 끄기
      bluetoothSerial.println("LED OFF");
    } else {
      bluetoothSerial.println("명령어 오류: '1' 또는 '0'을 보내세요.");
    }
  }

  // (선택 사항) 아두이노에서 맥북으로 데이터 전송 예시
  String messageToSend = "아두이노 데이터: " + String(analogRead(A0));
  bluetoothSerial.println(messageToSend);
  delay(1000);
}
