const int servoPin = 9; // 서보모터 핀 번호
volatile int pulseWidth = 0; // PWM 신호의 On 상태 시간 변수
int servoPos = 0; // 서보모터 위치 변수

void setup() {
  pinMode(servoPin, OUTPUT); // 서보모터 핀을 출력 모드로 설정
  TCCR1A = 0; // Timer1 모드를 Fast PWM으로 설정
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 20000; // Timer1 주기 설정 (20ms 기준)
  TCCR1B |= (1 << WGM12); // Timer1 모드를 Fast PWM으로 설정
  TCCR1B |= (1 << CS11); // Timer1 분주비 설정 (8분주)
  TIMSK1 |= (1 << OCIE1A); // Timer1 Compare Match A 인터럽트 활성화
}

void loop() {
  servoPos = 0; // 서보모터 위치 초기화
  pulseWidth = 1000; // 서보모터 최소 위치에 해당하는 PWM 신호 출력 (단위: 마이크로초)
  delay(1000); // 1초 대기
  servoPos = 90; // 서보모터 중앙 위치로 이동 (90도)
  pulseWidth = 1500; // 서보모터 위치에 해당하는 PWM 신호 출력 (단위: 마이크로초)
  delay(1000); // 1초 대기
  servoPos = 180; // 서보모터 최대 위치로 이동 (180도)
  pulseWidth = 2000; // 서보모터 위치에 해당하는 PWM 신호 출력 (단위: 마이크로초)
  delay(1000); // 1초 대기
}

ISR(TIMER1_COMPA_vect) { // Timer1 Compare Match A 인터럽트 함수
  digitalWrite(servoPin, HIGH); // PWM 신호 On
  delayMicroseconds(pulseWidth); // On 상태 시간 지정
  digitalWrite(servoPin, LOW); // PWM 신호 Off
  delayMicroseconds(20000 - pulseWidth); // Off 상태 시간 지정
  pulseWidth = map(servoPos, 0, 180, 1000, 2000); // 서보모터 위치에 해당하는 PWM 신호 계산
}
