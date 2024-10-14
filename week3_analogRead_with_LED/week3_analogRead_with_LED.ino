const int APIN = A0;
const int LPIN = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LPIN, OUTPUT);
  // analogWrite(APIN, 25);
  delay(2000);
  Serial.println("setup");
}

void loop() {
  // put your main code here, to run repeatedly:

  int aValue = analogRead(APIN);
  analogWrite(LPIN, aValue/4);
  Serial.println(aValue);
}
