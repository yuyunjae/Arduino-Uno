const int LED = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  // analogWrite(LED, 25);
  Serial.println("setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("loop");
  // Serial.println(78);
  // Serial.println(1.23456);
  // Serial.println('N');
  // Serial.println("Hello world");
  for(int bright = 0; bright < 255; bright++)
  {
    // digitalWrite(LED, HIGH);
    // delay(bright);
    // digitalWrite(LED, LOW);
    // delay(25 - bright);
    analogWrite(LED, bright);
    delay(4);
  }
}
