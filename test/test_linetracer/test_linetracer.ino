int line_r = 7;
int line_l = 8;        // 라인트레이서 센서을 9번 핀에 연결
int Buzzer = 9;        // Buzzer를 7번 핀에 연결
void setup(){
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);  // Buzzer는 '출력' 
  pinMode(line_r, INPUT);   // 라인트레이서 센서는 '입력'
  pinMode(line_l, INPUT);   // 라인트레이서 센서는 '입력'
}
void loop(){
  int val_L = digitalRead(line_l);  // 센서 값을 읽어와서
  int val_R = digitalRead(line_r);  // 센서 값을 읽어와서
  Serial.println(val_L);
  Serial.println(val_R);
  
  if (val_R == LOW && val_L == LOW){
    tone(Buzzer, 393);
    delay(500);
  }
  
  if (val_R == LOW){     // 우회전
   tone(Buzzer, 262);          
   delay(500);
  }
  else if (val_L == LOW){ // 좌회전
    tone(Buzzer, 131); 
    delay(500);
  } 
  else{               // 검정색 주행선을 벗어나면
   noTone(Buzzer);        // Buzzer에서 소리가 난다
   delay(500);
  }
}   