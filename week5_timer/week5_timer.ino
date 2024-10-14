#include <TimerOne.h>
// sketch -> include library -> TimerOne

const int LEDPIN = 10;

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize();
  Timer1.pwm(LEDPIN, 0);
  // Timer1.setPeriod(1000000); // 1초에 1번 (1Hz)
  // Timer1.setPeriod(1000000 / 10); // 1초에 10번 (10Hz)
  // Timer1.setPeriod(1000000 / 50); // 1초에 50번 (50Hz) => 육안으로는 계속 켜져있는것처럼 보임.
  Timer1.setPeriod(1000000 / 1000);
  Timer1.setPwmDuty(LEDPIN, 511); // 1023 / 2 = 511
  // Timer1.setPwmDuty(LEDPIN, 100); // 10%
  // Timer1.setPwmDuty(LEDPIN, 900); // 90%
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int high = 0; high < 1024; high++)
  {
    Timer1.setPwmDuty(LEDPIN, high); // 0 ~ 1023
    delay(1);
  }
}
