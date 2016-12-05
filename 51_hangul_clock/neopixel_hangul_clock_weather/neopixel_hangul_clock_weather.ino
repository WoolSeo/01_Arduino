// RGB LED 아두이노 한글시계 만들기(mkr1000)
// NEO PIXEL LED  + 시계 제어하기 + 날씨/기온 디스플레이
// 제작 : wool@wool.pe.kr
//
// 참고
// - http://www.kocoafab.cc/tutorial/view/595
// - adafruit strandtest example
// - 대디스랩 한글시계
// - 코코아팹 한글시계 만들기 프로젝트

#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#include <SPI.h>
#include <WiFi101.h>

#define DS3231_I2C_ADDRESS 104

#define PIN 6 // neopixel pin - mkr : 6, nano : 12

char ssid[] = "phyphy";       //와이파이 SSID
char pass[] = "1q3e5t7u";   //와이파이 password 

int  seconds, minutes, hours, day, date, month, year;
String weekDay;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, PIN, NEO_GRB + NEO_KHZ800);


int colors_r = 255;
int colors_g = 255;
int colors_b = 255;
int brightness = 255;
int weather_state = 1;




WiFiServer server(80);
WiFiClient client;

IPAddress hostIp;
uint8_t ret;

int temp = 0;

String weather_str="";
String wt_temp="";
String wt_wfKor="";
String wt_wfEn="";
String wt_reh="";
String wt_hour="";
String wt_twfEn="";
String wt_sky="";
String wt_pty="";

int lasttemp;
int lasthour;
int lastreh;
int lastsky;
int lastpty;
String lasttwfEn="";

int count=0;


void setup() {
  Serial.begin(115200);  
  
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show();
  //while (!Serial) ; // 시리얼 통신이 가능할 때까지 대기한다.
  delay(200);
  Wire.begin();
  
  //pinMode(10, INPUT);
  //pinMode(11, INPUT);
  //setDate(11, 34, 17, 11, 5, 8, 16);

  delay(10);
  //WiFi연결 시도
  Serial.println("Connecting to WiFi....");  
  WiFi.begin(ssid, pass);  //WiFi가 패스워드를 사용한다면 매개변수에 password도 작성
  
  server.begin();
  Serial.println("Connect success!");
  Serial.println("Waiting for DHCP address");
  //DHCP주소를 기다린다
  while(WiFi.localIP() == INADDR_NONE) {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\n");
  printWifiData();
  connectToServer();
  getWeather();
  strip.setBrightness(255);

}

void loop() {

  //getWeather();
  //Serial.println(count);
  //Serial.print("hour is "); 
  //Serial.println(lasthour);
  Serial.print("temperature is "); 
  Serial.println(lasttemp);
  //Serial.print("weather is ");
  //Serial.println(lasttwfEn); 
  Serial.print("Humidity is ");
  Serial.println(lastreh);
  Serial.print("Sky is ");
  Serial.println(lastsky); // 1 맑음 2 구름조금 3 구름많음 4 흐림
  Serial.print("pty is ");
  Serial.println(lastpty); // 0 없음 1 비 2 비눈 3 눈비 4 
  //delay(10000);
  //count++;

  
  Serial.println("");
    
    getDate();
   
    // 시, 분, 초 출력
    Serial.print("Time ");
    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print(":");
    Serial.println(seconds);

    /*if(digitalRead(11) == HIGH)
    {
      hours++;
      setDate(seconds, minutes, hours, day, date, month, year);
      ledReset();
      Serial.println("button11");
      delay(100);
    }
    if(digitalRead(10) == HIGH)
    {
      minutes = minutes + 5;
      if(minutes >= 60) minutes = 0;
      
      setDate(seconds, minutes, hours, day, date, month, year);
      ledReset();
      Serial.println("button10");
      delay(100);
    }*/
    // 5분에 한번씩 led 초기화
    if((minutes%5)==0 && seconds ==0){ 
      ledReset();
    }
    else if(seconds > 20) {
      ledReset();
      hoursFilter(hours,minutes); // 시(hour) LED 출력
      minutesFilter(minutes); // 분(minute) LED 출력
      strip.show();
    }
    else {
      getWeather();
      if(lastsky == 1 && lastpty == 0)
      {
        weather_state = 1;
      }
      //비
      else if(lastpty == 1)
      {
        weather_state = 2;
      }
      //눈
      else if(lastpty == 2 || lastpty == 3 || lastpty == 4)
      {
        weather_state = 3;
      }
      //흐림
      else if(lastpty == 2 || lastpty == 3 || lastpty == 4)
      {
        weather_state = 4;
      }
      
      if(lasttemp > 20) {
        colors_r = 255;
        colors_g = 0;
        colors_b = 0;
        Serial.print("temp is hot");
      }
      else if(lasttemp > 5) {
        colors_r = 0;
        colors_g = 255;
        colors_b = 0;
        Serial.print("temp is warm");
      }
      else {
        colors_r = 0;
        colors_g = 0;
        colors_b = 255;
        Serial.print("temp is cold");
      }
      ledReset();
      show_weather(weather_state); // 시(hour) LED 출력
      strip.show();

    }
    delay(5000);
}
void show_weather(int x) {
  if(x == 1) {
    strip.setPixelColor(2,255, 255, 0,brightness);
    strip.setPixelColor(6,255, 255, 0,brightness);
    strip.setPixelColor(7,255, 255, 0,brightness);
    strip.setPixelColor(8,255, 255, 0,brightness);
    strip.setPixelColor(10,255, 255, 0,brightness);
    strip.setPixelColor(11,255, 255, 0,brightness);
    strip.setPixelColor(12,255, 255, 0,brightness);
    strip.setPixelColor(13,255, 255, 0,brightness);
    strip.setPixelColor(14,255, 255, 0,brightness);
    strip.setPixelColor(16,255, 255, 0,brightness);
    strip.setPixelColor(17,255, 255, 0,brightness);
    strip.setPixelColor(18,255, 255, 0,brightness);
    strip.setPixelColor(22,255, 255, 0,brightness);
  }
  else if(x == 2) {
    strip.setPixelColor(7,127, 127, 127,brightness);
    strip.setPixelColor(8,127, 127, 127,brightness);
    strip.setPixelColor(11,127, 127, 127,brightness);
    strip.setPixelColor(12,127, 127, 127,brightness);
    strip.setPixelColor(13,127, 127, 127,brightness);
    strip.setPixelColor(15,127, 127, 127,brightness);
    strip.setPixelColor(16,127, 127, 127,brightness);
    strip.setPixelColor(17,127, 127, 127,brightness);
    strip.setPixelColor(18,127, 127, 127,brightness);
    strip.setPixelColor(19,127, 127, 127,brightness);
    
    
  }
  else if(x == 3) {
    strip.setPixelColor(1,0, 0, 255,brightness);
    strip.setPixelColor(2,0, 0, 255,brightness);
    strip.setPixelColor(3,0, 0, 255,brightness);
    strip.setPixelColor(5,0, 0, 255,brightness);
    strip.setPixelColor(6,0, 0, 255,brightness);
    strip.setPixelColor(7,0, 0, 255,brightness);
    strip.setPixelColor(8,0, 0, 255,brightness);
    strip.setPixelColor(9,0, 0, 255,brightness);
    strip.setPixelColor(15,0, 0, 255,brightness);
    strip.setPixelColor(17,0, 0, 255,brightness);
    strip.setPixelColor(19,0, 0, 255,brightness);
    strip.setPixelColor(20,0, 0, 255,brightness);
    strip.setPixelColor(22,0, 0, 255,brightness);
    strip.setPixelColor(24,0, 0, 255,brightness);
    
  }
  else {
    strip.setPixelColor(1,0, 0, 255,brightness);
    strip.setPixelColor(2,0, 0, 255,brightness);
    strip.setPixelColor(3,0, 0, 255,brightness);
    strip.setPixelColor(5,0, 0, 255,brightness);
    strip.setPixelColor(6,0, 0, 255,brightness);
    strip.setPixelColor(7,0, 0, 255,brightness);
    strip.setPixelColor(8,0, 0, 255,brightness);
    strip.setPixelColor(9,0, 0, 255,brightness);
    strip.setPixelColor(15,0, 0, 255,brightness);
    strip.setPixelColor(17,0, 0, 255,brightness);
    strip.setPixelColor(19,0, 0, 255,brightness);
    strip.setPixelColor(20,0, 0, 255,brightness);
    strip.setPixelColor(22,0, 0, 255,brightness);
    strip.setPixelColor(24,0, 0, 255,brightness);
    
  }
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
    strip.setPixelColor(15,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(16,colors_r, colors_g, colors_b,brightness);}
  else if(hours == 12 && minutes < 5){
    strip.setPixelColor(16,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(21,colors_r, colors_g, colors_b,brightness);}
  else if(hours == 1 || hours == 13){
    strip.setPixelColor(1,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);}
  else if(hours == 2 || hours == 14){
    strip.setPixelColor(5,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);}
  else if(hours == 3 || hours == 15){
    strip.setPixelColor(3,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);}
  else if(hours == 4 || hours == 16){
    strip.setPixelColor(4,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);}    
  else if(hours == 5 || hours == 17){
    strip.setPixelColor(2,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(7,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);}  
  else if(hours == 6 || hours == 18){
    strip.setPixelColor(6,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(7,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);} 
  else if(hours == 7 || hours == 19){
    strip.setPixelColor(8,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(9,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);}   
  else if(hours == 8 || hours == 20){
    strip.setPixelColor(10,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(11,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);}
  else if(hours == 9 || hours == 21){
    strip.setPixelColor(12,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(13,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);}     
  else if(hours == 10 || hours == 22){
    strip.setPixelColor(0,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);} 
  else if(hours == 11 || hours == 23){
    strip.setPixelColor(0,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(1,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);} 
  else if(hours%12==0){
    if(minutes>=5){
    strip.setPixelColor(0,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(5,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(14,colors_r, colors_g, colors_b,brightness);}
  }
  else ;      
}

void minutesFilter(int minutes){
 if(minutes>4 && minutes<10){
    strip.setPixelColor(21,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
 else if(minutes>9 && minutes<15){
    strip.setPixelColor(19,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
 else if(minutes>14 && minutes<20){
    strip.setPixelColor(22,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(23,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
 else if(minutes>19 && minutes<25){
    strip.setPixelColor(17,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(22,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
 else if(minutes>24 && minutes<30){
    strip.setPixelColor(17,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(22,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(23,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
 else if(minutes>29 && minutes<35){
    strip.setPixelColor(19,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(18,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
 else if(minutes>34 && minutes<40){
    strip.setPixelColor(19,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(18,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(23,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
 else if(minutes>39 && minutes<45){
    strip.setPixelColor(20,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(22,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
 else if(minutes>44 && minutes<50){
    strip.setPixelColor(20,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(22,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(23,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
else if(minutes>49 && minutes<55){
    strip.setPixelColor(21,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(22,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
else if(minutes>54 && minutes<60){
    strip.setPixelColor(21,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(22,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(23,colors_r, colors_g, colors_b,brightness);
    strip.setPixelColor(24,colors_r, colors_g, colors_b,brightness);}
else;
}

void ledReset(){
for(int i=0;i<25;i++){
    strip.setPixelColor(i,0,0,0);
    strip.show();
  }
}

void connectToServer() {
  Serial.println("connecting to server...");
  String content = "";
  if (client.connect(hostIp, 80)) {
    Serial.println("Connected! Making HTTP request to www.kma.go.kr");
    //Serial.println("GET /data/2.5/weather?q="+location+"&mode=xml");
    client.println("GET /wid/queryDFSRSS.jsp?zone=4111159100 HTTP/1.1"); 
    //위에 지정된 주소와 연결한다.
    client.print("HOST: www.kma.go.kr\n");
    client.println("User-Agent: launchpad-wifi");
    client.println("Connection: close");
    
    client.println();
    Serial.println("Weather information for ");
  }
  //마지막으로 연결에 성공한 시간을 기록
}


void printHex(int num, int precision) {
  char tmp[16];
  char format[128];
  
  sprintf(format, "%%.%dX", precision);
  
  sprintf(tmp, format, num);
  Serial.print(tmp);
}

void printWifiData() {
  // Wifi쉴드의 IP주소를 출력
  Serial.println();
  Serial.println("IP Address Information:");  
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  //MAC address출력
  byte mac[6];  
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printHex(mac[5], 2);
  Serial.print(":");
  printHex(mac[4], 2);
  Serial.print(":");
  printHex(mac[3], 2);
  Serial.print(":");
  printHex(mac[2], 2);
  Serial.print(":");
  printHex(mac[1], 2);
  Serial.print(":");
  printHex(mac[0], 2);
  Serial.println();
  //서브넷 마스크 출력
  IPAddress subnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(subnet);
  
  //게이트웨이 주소 출력
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(gateway);
  
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  ret = WiFi.hostByName("www.kma.go.kr", hostIp);
  
  Serial.print("ret: ");
  Serial.println(ret);
  
  Serial.print("Host IP: ");
  Serial.println(hostIp);
  Serial.println("");
}

int getInt(String input){
  int i = 2;
  
  while(input[i] != '"'){
    i++;
  }
  input = input.substring(2,i);
  char carray[20];
  //Serial.println(input);
  input.toCharArray(carray, sizeof(carray));
  //Serial.println(carray);
  temp = atoi(carray);
  //Serial.println(temp);
  return temp;
}

void getWeather() {
  if (client.connected()) {
    while (client.available()) {
      //라인을 기준으로 문자열을 저장한다.
      String line = client.readStringUntil('\n');
      //Serial.println(line);
      
      //시간
      int temp11= line.indexOf("</hour>");
      if(temp11>0) {
        String tmp_str="<hour>";
        String wt_hour = line.substring(line.indexOf(tmp_str)+tmp_str.length(),temp11);
        lasthour = wt_hour.toInt();  
      }
      
      //온도
      int temp= line.indexOf("</temp>");
      if(temp>0) {
        String tmp_str="<temp>";
        String wt_temp = line.substring(line.indexOf(tmp_str)+tmp_str.length(),temp);
        lasttemp = wt_temp.toInt();  
      }
      
      //날씨 정보
      int wfEn= line.indexOf("</wfEn>");
      if(wfEn>0) {
        String tmp_str="<wfEn>";
        String wt_twfEn = line.substring(line.indexOf(tmp_str)+tmp_str.length(),wfEn);
        lasttwfEn = wt_twfEn;
      }

      int sky= line.indexOf("</sky>");
      if(sky>0) {
        String tmp_str="<sky>";
        String wt_sky = line.substring(line.indexOf(tmp_str)+tmp_str.length(),sky);
        lastsky = wt_sky.toInt();;
      }
      
      int pty= line.indexOf("</pty>");
      if(pty>0) {
        String tmp_str="<pty>";
        String wt_pty = line.substring(line.indexOf(tmp_str)+tmp_str.length(),pty);
        lastpty = wt_pty.toInt();;
      }
      
      //습도
      int reh= line.indexOf("</reh>");
      if(reh>0) {
        String tmp_str="<reh>";
        String wt_reh = line.substring(line.indexOf(tmp_str)+tmp_str.length(),reh);
        lastreh = wt_reh.toInt();
      }
      //Serial.print("what1");
      //Serial.println(wt_twfEn);
    }   
  }
}


