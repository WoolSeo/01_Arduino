// RGB LED 아두이노 한글시계 만들기
// 03 NEO PIXEL LED  + 시계 제어하기
// 제작 : wool@wool.pe.kr  (16044 백윤기)
// 
//
// 참고
// - adafruit strandtest example
// - 대디스랩 한글시계
// - 코코아팹 한글시계 만들기 프로젝트

#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define DS3231_I2C_ADDRESS 104

int  seconds, minutes, hours, day, date, month, year;
String weekDay;

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, PIN, NEO_GRB + NEO_KHZ800);
uint32_t color1 = strip.Color(255, 0, 0);
uint32_t color2 = strip.Color(255, 255, 0);
uint32_t color3 = strip.Color(0, 255, 0);
uint32_t color4 = strip.Color(0, 0, 255);
uint32_t color5 = strip.Color(255, 0, 255);

void setup() {
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show();
  //while (!Serial) ; // 시리얼 통신이 가능할 때까지 대기한다.
  delay(200);
  Wire.begin();
  
  
  //setDate(00, 50, 19, 11, 5, 8, 16);
}

void loop() {
  
    getDate();
   
    // 시, 분, 초 출력
    Serial.print(hours);
    Serial.print("\t");
    Serial.print(minutes);
    Serial.print("\t");
    Serial.println(seconds);

  
    // 5분에 한번씩 led 초기화
    if((minutes%5)==0 && seconds ==0){ 
      ledReset();
    }


    hoursFilter(hours,minutes); // 시(hour) LED 출력
    minutesFilter(minutes); // 분(minute) LED 출력
    strip.show();

  delay(1000);
}

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
void hoursFilter(int hours,int minutes){
  if(hours == 0 && minutes < 5){  //00:00
    strip.setPixelColor(15,color4);
    strip.setPixelColor(16,color4);}
  else if(hours == 12 && minutes < 5){
    strip.setPixelColor(16,color4);
    strip.setPixelColor(21,color5);}
  else if(hours == 1 || hours == 13){
    strip.setPixelColor(1,color1);
    strip.setPixelColor(14,color3);}
  else if(hours == 2 || hours == 14){
    strip.setPixelColor(5,color2);
    strip.setPixelColor(14,color3);}
  else if(hours == 3 || hours == 15){
    strip.setPixelColor(3,color1);
    strip.setPixelColor(14,color3);}
  else if(hours == 4 || hours == 16){
    strip.setPixelColor(4,color1);
    strip.setPixelColor(14,color3);}    
  else if(hours == 5 || hours == 17){
    strip.setPixelColor(2,color1);
    strip.setPixelColor(7,color2);
    strip.setPixelColor(14,color3);}  
  else if(hours == 6 || hours == 18){
    strip.setPixelColor(6,color2);
    strip.setPixelColor(7,color2);
    strip.setPixelColor(14,color3);} 
  else if(hours == 7 || hours == 19){
    strip.setPixelColor(8,color2);
    strip.setPixelColor(9,color2);
    strip.setPixelColor(14,color3);}   
  else if(hours == 8 || hours == 20){
    strip.setPixelColor(10,color3);
    strip.setPixelColor(11,color3);
    strip.setPixelColor(14,color3);}
  else if(hours == 9 || hours == 21){
    strip.setPixelColor(12,color3);
    strip.setPixelColor(13,color3);
    strip.setPixelColor(14,color3);}     
  else if(hours == 10 || hours == 22){
    strip.setPixelColor(0,color1);
    strip.setPixelColor(14,color3);} 
  else if(hours == 11 || hours == 23){
    strip.setPixelColor(0,color1);
    strip.setPixelColor(1,color1);
    strip.setPixelColor(14,color3);} 
  else if(hours%12==0){
    if(minutes>=5){
    strip.setPixelColor(0,color1);
    strip.setPixelColor(5,color2);
    strip.setPixelColor(14,color3);}
  }
  else ;      
}

void minutesFilter(int minutes){
 if(minutes>4 && minutes<10){
    strip.setPixelColor(21,color5);
    strip.setPixelColor(24,color5);}
 else if(minutes>9 && minutes<15){
    strip.setPixelColor(19,color4);
    strip.setPixelColor(24,color5);}
 else if(minutes>14 && minutes<20){
    strip.setPixelColor(22,color5);
    strip.setPixelColor(23,color5);
    strip.setPixelColor(24,color5);}
 else if(minutes>19 && minutes<25){
    strip.setPixelColor(17,color4);
    strip.setPixelColor(22,color5);
    strip.setPixelColor(24,color5);}
 else if(minutes>24 && minutes<30){
    strip.setPixelColor(17,color4);
    strip.setPixelColor(22,color5);
    strip.setPixelColor(23,color5);
    strip.setPixelColor(24,color5);}
 else if(minutes>29 && minutes<35){
    strip.setPixelColor(19,color4);
    strip.setPixelColor(18,color4);
    strip.setPixelColor(24,color5);}
 else if(minutes>34 && minutes<40){
    strip.setPixelColor(19,color4);
    strip.setPixelColor(18,color4);
    strip.setPixelColor(23,color5);
    strip.setPixelColor(24,color5);}
 else if(minutes>39 && minutes<45){
    strip.setPixelColor(20,color5);
    strip.setPixelColor(22,color5);
    strip.setPixelColor(24,color5);}
 else if(minutes>44 && minutes<50){
    strip.setPixelColor(20,color5);
    strip.setPixelColor(22,color5);
    strip.setPixelColor(23,color5);
    strip.setPixelColor(24,color5);}
else if(minutes>49 && minutes<55){
    strip.setPixelColor(21,color5);
    strip.setPixelColor(22,color5);
    strip.setPixelColor(24,color5);}
else if(minutes>54 && minutes<60){
    strip.setPixelColor(21,color5);
    strip.setPixelColor(22,color5);
    strip.setPixelColor(23,color5);
    strip.setPixelColor(24,color5);}
else;
}

void ledReset(){
for(int i=0;i<25;i++){
    strip.setPixelColor(i,0,0,0);
    strip.show();
  }
}

