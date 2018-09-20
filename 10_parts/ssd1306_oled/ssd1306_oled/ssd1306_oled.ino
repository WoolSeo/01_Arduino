#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
 
void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("<em>HELLO WORLD</em>");
  display.display();
  delay(10000);
}
