#define PIR_PIN 7
#define PIEZO 6

// 회전목마 멜로디 (도레미파솔라시도 기준, 4분음표=250ms)
int melody[] = {
  523, 587, 659, 698, 784, 880, 988, 1047,  // 도레미파솔라시도
  784, 659, 784, 880, 659, 587, 523,         // 솔미솔라미레도
  587, 659, 698, 784, 880, 988, 1047,        // 레미파솔라시도
  784, 880, 988, 1047, 880, 784, 659         // 솔라시도라솔미
};

// 각 음의 지속 시간 (4분음표=250ms, 2분음표=500ms)
int noteDurations[] = {
  250, 250, 250, 250, 250, 250, 250, 250,
  500, 250, 250, 500, 250, 250, 500,
  250, 250, 250, 250, 250, 250, 250,
  250, 250, 250, 500, 250, 250, 500
};

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(PIEZO, OUTPUT);
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {
    playMelody();
    delay(1000); // 연주 후 1초 대기 (재생 반복 방지)
  }
}

void playMelody() {
  for (int i = 0; i < sizeof(melody) / sizeof(int); i++) {
    tone(PIEZO, melody[i], noteDurations[i]);
    delay(noteDurations[i] * 1.3); // 음 간 간격 추가
  }
  noTone(PIEZO); // 연주 종료
}
