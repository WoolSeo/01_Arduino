#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  matrix.begin(0x70);
}

void loop() {
  
  matrix.setTextSize(1);
  matrix.setTextWrap(true);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  for(int i = 9; i>=0; i--)
  {
    matrix.clear();
    matrix.setCursor(1,0);
    matrix.print(i);
    matrix.writeDisplay();
    delay(1000);
  }
  
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  
  for (int8_t x=0; x>=-36; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("WOOL");
    matrix.writeDisplay();
    delay(100);
  }
  
  matrix.setRotation(3);
  for (int8_t x=7; x>=-36; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("World");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(0);
}
