#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, PIN, NEO_GRB + NEO_KHZ800);
uint32_t color = strip.Color(232, 101, 12);

void setup() {
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show();
  while (!Serial) ; // 시리얼 통신이 가능할 때까지 대기한다.
  delay(200);
}

void loop() {
  tmElements_t tm; // RTC 객체 선언

  if (RTC.read(tm)) { //RTC 모듈로 부터 데이터가 들어온다면
    
    int hours = tm.Hour; //시(hour) 데이터를 hours 변수에 담는다.
    int minutes = tm.Minute; //분(minute) 데이터를 minutes 변수에 담는다.
    int seconds = tm.Second; //초(second) 데이터를 seconds 변수에 담는다.

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
  }
  else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } 
    else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

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

void ledReset(){
for(int i=0;i<25;i++){
    strip.setPixelColor(i,0,0,0);
    strip.show();
  }
}
