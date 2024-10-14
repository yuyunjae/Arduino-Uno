#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned int row = 1;

  lcd.setCursor(0, (++row % 2));
  char str[] = "Hello, world!";
  for (int i = 0; i < sizeof(str) - 1; i++)
  {
    lcd.print(str[i]);
    delay(50);
  }
  delay(1000);
  lcd.clear();
}
