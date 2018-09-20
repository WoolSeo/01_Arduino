//ref
//https://microcontrollerelectronics.com/ssd1306-oled-displays/
//http://arduino-er.blogspot.com/2015/05/temperature-humidity-monitor-using.html
//http://www.hardcopyworld.com/ngine/aduino/index.php/archives/190

#include <DHT11.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

int pin=2;    // dht11 pin
DHT11 dht11(pin); 

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup()
{
   Serial.begin(9600);
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
 
void loop()
{
  int err;
  float temp, humi;
  int t, h;
  
  if((err=dht11.read(humi, temp))==0)
  {
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
    t = int(temp);
    h = int(humi);
    
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(t);
    display.print("*C, ");
    display.print(h);
    display.println("%");
    display.display();
  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();    
  }
  delay(DHT11_RETRY_DELAY); //delay for reread
}
