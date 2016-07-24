// RGB LED 아두이노 한글시계 만들기
// 제작 : wool@wool.pe.kr
// 
//
// 참고
// - adafruit strandtest example
// - 대디스랩 한글시계
// - 코코아팹 한글시계 만들기 프로젝트

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <Wire.h> 

#define DS3231_I2C_ADDRESS 104
#define PIN 12


Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, PIN, NEO_GRB + NEO_KHZ800);
uint32_t color = strip.Color(255, 255, 255);

int  seconds, minutes, hours, day, date, month, year;
String weekDay;


void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  Serial.begin(9600);
  Wire.begin();

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  //////clock DS3231 관련
  getDate();
  // display time and date
  Serial.print(month);
  Serial.print("/");
  Serial.print(day);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  
  
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127,   0,   0), 50); // Red
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  //rainbow(20);
  //rainbowCycle(20);
  //theaterChaseRainbow(50);

  /*for(int i=0;i<25;i++){
    //strip.setPixelColor(i,255,255,255);
    strip.setPixelColor(i-1,50,50,50);
    strip.setPixelColor(i-2,0,0,0);
    strip.show();
    delay(300);
  }
  ledReset();*/
   
  if((minutes%5)==0 && seconds ==0){ 
    ledReset();
  }


  hoursFilter(hours,minutes); // 시(hour) LED 출력
  minutesFilter(minutes); // 분(minute) LED 출력
  strip.show();
}
///////// clock 함수들

void getDate()
{
  // Send request to DS3231 to receive the date
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x00);  // start at register 00h (seconds)
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);   // Request 7 bytes (00h - 006h)

  while(Wire.available())
  {
    seconds = Wire.read();
    minutes = Wire.read();
    hours = Wire.read();
    day = Wire.read();
    date = Wire.read();
    month = Wire.read();
    year = Wire.read();
    
    // convert BCD to decimal 
    seconds = (((seconds >> 4) * 10) + (seconds & B00001111)); 
    minutes = (((minutes >> 4) * 10) + (minutes & B00001111)); 
    hours = ((((hours & B00110000) >> 4) * 10) + (hours & B00001111)); 
    day = (day & B00000111); 
    month = ((((month & B00010000) >> 4) * 10) + (month & B00001111)); 
    date = ((((date & B00110000)>> 4) * 10) + (date & B00001111));  
    year = (((year >> 4) * 10) + (year & B00001111)); 
  }
   switch (day)  {
    case 1:
      weekDay = "Sun";
      break;
    case 2:
      weekDay = "Mon";
      break;
    case 3:
      weekDay = "Tue";
      break;
    case 4:
      weekDay = "Wed";
      break;
    case 5:
      weekDay = "Thu";
      break;
    case 6:
      weekDay = "Fri";
      break;
  
    default: break;
  }
 
 
}

void setDate(byte seconds, byte minutes, byte hours, byte day, byte date, byte month, byte year)
{
  // convert DEC to BCD
  seconds = (seconds % 10) + ((seconds / 10) << 4); 
  minutes = (minutes % 10) + ((minutes / 10) << 4);
  hours = (hours % 10) + ((hours / 10) << 4);
  date = (date % 10) + ((date / 10) << 4);
  month = (month % 10) + ((month / 10) << 4);
  year = (year % 10) + ((year / 10) << 4);

  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.write(seconds);
  Wire.write(minutes);
  Wire.write(hours);
  Wire.write(day);
  Wire.write(date);
  Wire.write(month);
  Wire.write(year);
  Wire.endTransmission();

}


///// 시각에 맞춰 LED 켜는 함수
/////////////////////////////////////////////////////

void hoursFilter(int hours,int minutes){
  if(hours == 0 && minutes == 0){  //00:00
    strip.setPixelColor(18,color);
    strip.setPixelColor(19,color);}
  else if(hours == 12 && minutes ==0){
    strip.setPixelColor(18,color);
    strip.setPixelColor(21,color);}
  else if(hours == 1 || hours == 13){
    strip.setPixelColor(1,color);
    strip.setPixelColor(14,color);}
  else if(hours == 2 || hours == 14){
    strip.setPixelColor(9,color);
    strip.setPixelColor(14,color);}
  else if(hours == 3 || hours == 15){
    strip.setPixelColor(3,color);
    strip.setPixelColor(14,color);}
  else if(hours == 4 || hours == 16){
    strip.setPixelColor(4,color);
    strip.setPixelColor(14,color);}    
  else if(hours == 5 || hours == 17){
    strip.setPixelColor(2,color);
    strip.setPixelColor(7,color);
    strip.setPixelColor(14,color);}  
  else if(hours == 6 || hours == 18){
    strip.setPixelColor(7,color);
    strip.setPixelColor(8,color);
    strip.setPixelColor(14,color);} 
  else if(hours == 7 || hours == 19){
    strip.setPixelColor(5,color);
    strip.setPixelColor(6,color);
    strip.setPixelColor(14,color);}   
  else if(hours == 8 || hours == 20){
    strip.setPixelColor(10,color);
    strip.setPixelColor(11,color);
    strip.setPixelColor(14,color);}
  else if(hours == 9 || hours == 21){
    strip.setPixelColor(12,color);
    strip.setPixelColor(13,color);
    strip.setPixelColor(14,color);}     
  else if(hours == 10 || hours == 22){
    strip.setPixelColor(0,color);
    strip.setPixelColor(14,color);} 
  else if(hours == 11 || hours == 23){
    strip.setPixelColor(0,color);
    strip.setPixelColor(1,color);
    strip.setPixelColor(14,color);} 
  else if(hours == 12 || hours == 24){
    if(minutes>0){
    strip.setPixelColor(0,color);
    strip.setPixelColor(9,color);
    strip.setPixelColor(14,color);}
  }
  else ;      
}

void minutesFilter(int minutes){
 if(minutes>4 && minutes<10){
    strip.setPixelColor(21,color);
    strip.setPixelColor(24,color);}
 else if(minutes>9 && minutes<15){
    strip.setPixelColor(22,color);
    strip.setPixelColor(24,color);}
 else if(minutes>14 && minutes<20){
    strip.setPixelColor(22,color);
    strip.setPixelColor(23,color);
    strip.setPixelColor(24,color);}
 else if(minutes>19 && minutes<25){
    strip.setPixelColor(17,color);
    strip.setPixelColor(22,color);
    strip.setPixelColor(24,color);}
 else if(minutes>24 && minutes<30){
    strip.setPixelColor(17,color);
    strip.setPixelColor(22,color);
    strip.setPixelColor(23,color);
    strip.setPixelColor(24,color);}
 else if(minutes>29 && minutes<35){
    strip.setPixelColor(15,color);
    strip.setPixelColor(16,color);
    strip.setPixelColor(24,color);}
 else if(minutes>34 && minutes<40){
    strip.setPixelColor(15,color);
    strip.setPixelColor(16,color);
    strip.setPixelColor(23,color);
    strip.setPixelColor(24,color);}
 else if(minutes>39 && minutes<45){
    strip.setPixelColor(20,color);
    strip.setPixelColor(22,color);
    strip.setPixelColor(24,color);}
 else if(minutes>44 && minutes<50){
    strip.setPixelColor(20,color);
    strip.setPixelColor(22,color);
    strip.setPixelColor(23,color);
    strip.setPixelColor(24,color);}
else if(minutes>49 && minutes<55){
    strip.setPixelColor(21,color);
    strip.setPixelColor(22,color);
    strip.setPixelColor(24,color);}
else if(minutes>54 && minutes<60){
    strip.setPixelColor(21,color);
    strip.setPixelColor(22,color);
    strip.setPixelColor(23,color);
    strip.setPixelColor(24,color);}
else;
}

/////  RGB LED 함수들
///////////////////////////////////////////////////////////////////////////
void ledReset(){
  for(int i=0;i<25;i++){
    strip.setPixelColor(i,0,0,0);
    strip.show();
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

