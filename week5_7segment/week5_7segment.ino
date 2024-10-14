// #include <PinChangeInterrupt.h>
// #include <PinChangeInterruptBoards.h>
// #include <PinChangeInterruptPins.h>
// #include <PinChangeInterruptSettings.h>


const int APIN1 = 2;
const int APIN2 = 3;
const int APIN3 = 4;
const int APIN4 = 5;
const int APIN5 = 6;
const int APIN6 = 7;
const int APIN7 = 8;

// unsigned long echo_duration = 0;

// void echoISR()
// {
//   static unsigned echo_begin = 0;
//   static unsigned echo_end = 0;

//   unsigned int echo_pin_state = digitalRead(EPIN);
//   if (echo_pin_state == HIGH)
//     echo_begin = micros(); //current arduino time usec
//   else
//   {
//     echo_end = micros();
//     echo_duration = echo_end - echo_begin;
//   }
// }

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(115200);
  pinMode(APIN1, OUTPUT);
  pinMode(APIN2, OUTPUT);
  pinMode(APIN3, OUTPUT);
  pinMode(APIN4, OUTPUT);
  pinMode(APIN5, OUTPUT);
  pinMode(APIN6, OUTPUT);
  pinMode(APIN7, OUTPUT);

  digitalWrite(APIN1, HIGH);
  digitalWrite(APIN2, HIGH);
  digitalWrite(APIN3, HIGH);
  digitalWrite(APIN4, HIGH);
  digitalWrite(APIN5, HIGH);
  digitalWrite(APIN6, HIGH);
  digitalWrite(APIN7, HIGH);
  // pinMode(EPIN, INPUT);
  // delay(2000);
  // attachPCINT(digitalPinToPCINT(EPIN), echoISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(BtPIN), buttonPressed, RISING);
  // Serial.println("Setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  // if (echo_duration == 0)
  // {
  //   digitalWrite(TPIN, LOW);
  //   delayMicroseconds(2);
  //   digitalWrite(TPIN, HIGH);
  //   delayMicroseconds(10);
  //   digitalWrite(TPIN, LOW);
  // }
  // else
  // {
  //   long distance = echo_duration / 58;
  //   Serial.print(distance);
  //   Serial.println(" cm");
  //   echo_duration = 0;
  // }
}
