
const int BzPIN = 10;
const int BtPIN = 2;

int buzzer_state = LOW;
bool buzzer_state_changed = false;

void buttonPressed()
{
  buzzer_state = (buzzer_state == LOW) ? HIGH:LOW;
  buzzer_state_changed = true;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BzPIN, OUTPUT);
  pinMode(BtPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BtPIN), buttonPressed, RISING);
  Serial.println("Setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (buzzer_state_changed)
  {
    buzzer_state_changed = false;
    digitalWrite(BzPIN, buzzer_state);
    Serial.println(buzzer_state);
    // delay(50);
  }
}
