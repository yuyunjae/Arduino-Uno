
const int TPIN = 11;
const int EPIN = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(TPIN, OUTPUT);
  pinMode(EPIN, INPUT);
  delay(2000);
  // attachInterrupt(digitalPinToInterrupt(BtPIN), buttonPressed, RISING);
  // Serial.println("Setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TPIN, LOW);

  long duration = pulseIn(EPIN, HIGH);
  long distance = duration / 58;

  Serial.print(distance);
  Serial.println("cm");
  // delay(10);
  // if (buzzer_state_changed)
  // {
  //   buzzer_state_changed = false;
  //   digitalWrite(BzPIN, buzzer_state);
  //   Serial.println(buzzer_state);
  //   // delay(50);
  // }
}
