#include <TimerOne.h>
// sketch -> include library -> TimerOne

const int BUZZERPIN = 10;
const int melody[] = {262, 294, 330, 349, 393, 449, 494, 523};

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize();
  Timer1.pwm(BUZZERPIN, 0);
  Timer1.setPwmDuty(BUZZERPIN, 100);
  // Timer1.setPeriod(1000000); // 1초에 1번 (1Hz)
  // Timer1.setPeriod(1000000 / 10); // 1초에 10번 (10Hz)
  // Timer1.setPeriod(1000000 / 50); // 1초에 50번 (50Hz) => 육안으로는 계속 켜져있는것처럼 보임.
  for (int note = 0; note < 8; note++)
  {
    Timer1.setPeriod(1000000/melody[note]);
    delay(500);
  }
  Timer1.setPwmDuty(BUZZERPIN, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
}
