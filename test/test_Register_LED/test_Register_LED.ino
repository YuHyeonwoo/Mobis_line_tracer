void setup() {
  // put your setup code here, to run once:
  DDRD |= (1 << 7); // 7번 포트를 OUTPUT으로
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTD |= (1 << 7); // 7번 포트에 전압 인가
  delay(3000);
  PORTD &= ~(1 << 7); // 7번 포트 전압 해제
  delay(3000);
}
