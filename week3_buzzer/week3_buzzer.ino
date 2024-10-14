const int BUZ = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // pinMode(BUZ, OUTPUT);
  // analogWrite(APIN, 25);
  delay(2000);
  tone(BUZ, 262); // c 음
  delay(3000);
  noTone(BUZ);
  Serial.println("setup");
}

void loop() {
  // put your main code here, to run repeatedly:

  // int aValue = analogRead(APIN);
  // analogWrite(BUZ, aValue/4);
  // Serial.println(aValue);
}
