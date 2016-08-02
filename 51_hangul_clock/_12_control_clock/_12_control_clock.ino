// RGB LED 아두이노 한글시계 만들기
// 02 시계 모듈 제어 - DS3231
// 제작 : wool@wool.pe.kr
// 
// include the library code:

#include <Wire.h> 
#define DS3231_I2C_ADDRESS 104 //핀 연결 SDA-A4, SCL-A5

int  seconds, minutes, hours, day, date, month, year;
String weekDay;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();

  // to set hour and date use the following steps
  // 1.- Uncomment the instruction
  // 2.- Set time and date
  // 3.- Upload the sketch
  // 4.- Comment and upload again to prevent a reset time
  // setDate(seconds(0-59), minutes(0-59), hours(0-23), day(1-7), date(0-31), month(1-12), year(0-99))
  setDate(00, 23, 10, 4, 28, 6, 16); // 시간 설정할때만, 그 외에는 주석처리
}

void loop() 
{

  // get date from DS3231
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
