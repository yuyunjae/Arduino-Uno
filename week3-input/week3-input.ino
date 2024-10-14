const int LED = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  // analogWrite(LED, 25);
  delay(2000); // 처음 보드에 전기가 들어갈 때, 꺼졌다가 다시 켜지는 경우도 있어서 "setup"이 2번찍히고나 안찍히는 경우가 존재. => delay로 해결
  Serial.println("setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    char  userInput = Serial.read();
    Serial.println(userInput);
    switch(userInput){
      case 'n' :
        digitalWrite(LED, HIGH);
        break;
      case 'f' :
        digitalWrite(LED, LOW);
          break;
      default : 
        break;
    }
  }
}
