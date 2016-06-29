#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  
  matrix.begin(0x70);
}

void loop() {
  
  matrix.clear();      // clear display
  matrix.drawPixel(3, 7, LED_ON);  //x, y
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  matrix.clear();
  matrix.drawLine(0,0, 7,7, LED_ON); // start x, y final x, y
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  matrix.clear();
  matrix.drawRect(1,0, 3,5, LED_ON); // start x, y, size x, y
  //matrix.fillRect(1,2, 5,4, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  matrix.clear();
  //matrix.drawCircle(5,5, 2, LED_ON); // point x, y, size z
  matrix.fillCircle(5,5, 2, LED_ON); // point x, y, size z
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  
  
}
