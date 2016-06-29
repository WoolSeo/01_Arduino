#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("hello, JJo!");
}

void loop()
{
  lcd.setCursor(0,2);
  lcd.print(millis()/1000);
}

