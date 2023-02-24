int OUTPUT_pin=7;	
int LM_Pin=A0;

int hearingClap_prev;
int hearingClap_curr;
long clapTime_prev = 0;	
long clapTime_curr = 0;	
long changeTime = 0;
int LED_light = LOW;	

void setup() {
  pinMode(OUTPUT_pin, OUTPUT);
  pinMode(LM_Pin, INPUT);
  Serial.begin (9600);
}

void loop() {
  int sound = analogRead(LM_Pin);

  if(sound < 100){	
    hearingClap_curr = 1; 
    Serial.println(sound);
  } else {
    hearingClap_curr = 0;	
    
  }
  clapTime_curr = millis(); 

  if (hearingClap_curr == 1) { 

    if (
      (clapTime_curr > clapTime_prev + 200) && // 이전 박수 0.2초 후에 박수소리가 들린거면
      (hearingClap_prev == 0) &&  // 이전에 박수소리가 없었으면(큰소리가 계속 들리는경우 불이 켜지지 않음)
      (clapTime_curr < clapTime_prev + 800)&& // 0.8초 이전에 박수소리가 들린거면
      (clapTime_curr > changeTime + 1000) // 전등 상태가 달라진지 1초 이후(박수를 세번쳤을때 반응이 없도록)
    ) {

      LED_light = !LED_light; 
      digitalWrite(OUTPUT_pin, LED_light); 
      changeTime = clapTime_curr;
     }

     clapTime_prev = clapTime_curr; 
  }

  hearingClap_prev = hearingClap_curr; 
}



// void setup () 
// {
//   Serial.begin (9600); // 시리얼 모니터 시작
// }

// void loop () 
// {
//   sound_value = analogRead (sound_pin); // 소리값을 읽어서 sound_value 변수에 저장
//   Serial.print ("amplitude : "); 
//   Serial.println(sound_value);  // 소리값을 시리얼모니터에 출력
//   delay(1000);
// }