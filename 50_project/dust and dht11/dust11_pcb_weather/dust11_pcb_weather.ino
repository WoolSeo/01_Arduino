#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#include <RTCZero.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <DHT.h>
#include <Wire.h>

RTCZero rtc;
WiFiClient client;

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "wool2";        // your network SSID (name)
char pass[] = "1q3e5t7u!";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

/////// air dust information
char AIRserver[] = "openapi.airkorea.or.kr";
#define APIKEY    "nESF1DreNeshOI7Q6zdswaS7wzLtVFLILOfnpEs%2B2QIUSVhqQoZ6udu8Eil%2FNLlWOP4UfsTvE%2B4DJQaZyjekaA%3D%3D"
#define CITY    "신풍동"//"신풍동"
#define VERSION    "1.3"

//////// weather information
//// serching city name https://openweathermap.org/weathermap?basemap=map&cities=true&layer=temperature&lat=37.5380&lon=127.1544&zoom=10
char Weatherserver[] = "api.openweathermap.org";    // name address for Google (using DNS)
#define VARID      "711aa399f1dd69c891a37275335df134"
#define WeatherCITY    "Suigen"//수원
String rcvbuf;


const int reconnect_wifi_Interval = 3; // 10 minutes
const long refresh_lcd_Interval = 20L * 1000L; // 20 seconds

const int GMT = 9; //change this to adapt it to your time zone

long count = 0;

// For MKR1000
#define TFT_MISO 10 // SDO/MISO
#define TFT_CLK 9 // SCK
#define TFT_MOSI 8 // SDI/MOSI
#define TFT_DC 7 // DC/RS
#define TFT_CS 6 // CS 
#define TFT_RST 5 // RESET
//LED - vcc(3.3V)

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define DHTPIN 4    
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

#define PiezoPin 3

#define SW1Pin 13
#define SW2Pin 14

String tft_datatime = "";
String tft_pm10value = "";
String tft_pm25value = "";
String tft_temp = "";
String tft_temp_min = "";
String tft_temp_max = "";
String tft_weather = "";

int pm10 = 0;
int pm25 = 0;
int dustLevel = 0;
int predustLevel = 0;

int time_h = 0;
int time_m = 0;
int time_h_temp = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  pinMode(SW1Pin, INPUT_PULLUP);
  pinMode(SW2Pin, INPUT_PULLUP);
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  rtc.begin();
  
  wificonnent();

  dustRequest();

  WeatherRequest();
  
  /////// tft lcd ///////////////////
  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  
  Serial.println(F("Benchmark                Time (microseconds)"));
  delay(10);
  Serial.println(F("Screen fill              "));
  //Serial.println(testFillScreen());
  delay(500);

  
  
  tone(PiezoPin, 2000);
  delay(3000);
  noTone(PiezoPin);
  delay(10);
  
  
}

void loop() {

  time_h = rtc.getHours() + GMT;
  time_m = rtc.getMinutes();

  if(time_h >24){
    time_h = time_h - 24;
  }
  Serial.print(time_h);
  Serial.print(":");
  Serial.println(time_m);

  if(time_m % reconnect_wifi_Interval == 0) {
        
    wificonnent();

    dustRequest();

    delay(30000);
    
    WeatherRequest();
  }
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  pm10 = tft_pm10value.toInt();
  pm25 = tft_pm25value.toInt();

  if(pm10 > 100 || pm25 > 50) {
    tft.fillScreen(ILI9341_RED);
    dustLevel = 3;
  }
  else if(pm10 > 50 || pm25 > 25) {
    tft.fillScreen(ILI9341_ORANGE);
    dustLevel = 2;
  }
  else if(pm10 > 30 || pm25 > 15) {
    tft.fillScreen(ILI9341_GREEN);
    dustLevel = 1;
  }
  else {
    tft.fillScreen(ILI9341_BLUE);
    dustLevel = 0;
  }

  if(predustLevel != dustLevel) {
    tone(PiezoPin, 1000);
    delay(3000);
    noTone(PiezoPin);
    delay(10);
    predustLevel = dustLevel;
  }
  
  tft.setRotation(0); //0~3
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);

  tft.setTextSize(2);
  tft.println(" ");
  
  tft.setTextSize(6);
  tft.print(" ");
  if(time_h < 10) {
    tft.print("0");
  }
  tft.print(time_h);
  tft.print(":");
  if(time_m < 10) {
    tft.print("0");
  }
  tft.println(time_m);

  tft.setTextSize(2);
  tft.println(" ");
  
  tft.setTextSize(3);
  tft.println("<-INSIDE->");
  tft.print("H:");
  tft.print(int(h));
  tft.println("%");
  tft.print("T:");
  tft.print(int(t));
  tft.println("'C ");

  tft.setTextSize(2);
  tft.println(" ");
  
  tft.setTextSize(3);
  tft.println("<-OUTSIDE->");
  tft.println(tft_weather);
  tft.print("T:");
  tft.print(tft_temp.toInt());
  tft.print("'C(");
  tft.print(tft_temp_min.toInt());
  tft.print("/");
  tft.print(tft_temp_max.toInt());
  tft.println(")");
  
  tft.print("pm10:");
  tft.println(pm10);
  tft.print("pm2.5:");
  tft.println(pm25);

  tft.setTextSize(1);
  tft.print("update: ");
  tft.println(tft_datatime);

  tft.print("refresh count: ");
  tft.println(count);
  tft.print(" made by wool");

  //end and disconnect wifi
  client.stop();
  WiFi.end();

  status = WiFi.status();
    
  delay(refresh_lcd_Interval);

  int SW2Val = digitalRead(SW1Pin);
  if( SW2Val == LOW) {
    tone(PiezoPin, 500, 500);
    delay(500);
  }
  
  

  Serial.println("--------------------------------------");

}

void wificonnent() {
  
  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the status:
  printWiFiStatus();

  /*if(time_h == 15 && time_m >=30 ){
    get_time();
  }*/
  if(count == 0) {
    get_time();
  }
  
  if(time_h_temp != time_h){
    get_time();
    time_h_temp = time_h;
  }
  
}


// this method makes a HTTP connection to the server:
void dustRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(AIRserver, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print(F("GET /openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?stationName="));
    client.print(CITY);
    client.print(F("&dataTerm=daily&pageNo=1&numOfRows=1&ServiceKey="));
    client.print(APIKEY);
    client.print(F("&ver="));
    client.print(VERSION);
    client.print(F(" HTTP/1.1\r\n"));
    client.println("Host: openapi.airkorea.or.kr");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    //lastConnectionTime = millis();
  }
  else {
    // if you couldn't make a connection:
    Serial.println("dust connection failed");
  }

  while(!client.available()) {
  }

  int i = 0;
  while (client.available()) {
    i++;
    String line = client.readStringUntil('\n');

    int datatime= line.indexOf("</dataTime>");
    
    if(datatime>0){
      Serial.println("-----------------------------");
      String tmp_str="<dataTime>";
      String wt_datatime = line.substring(line.indexOf(tmp_str)+tmp_str.length(),datatime);
      Serial.print("datetime : ");
      Serial.println(wt_datatime);
      tft_datatime = wt_datatime;
    }
    
    int pm10value= line.indexOf("</pm10Value>");
    
    if(pm10value>0){
      String tmp_str="<pm10Value>";
      String wt_pm10value = line.substring(line.indexOf(tmp_str)+tmp_str.length(),pm10value);
      Serial.print("pm10 value : ");
      Serial.println(wt_pm10value);
      tft_pm10value = wt_pm10value;
    }

    int pm25value= line.indexOf("</pm25Value>");
    
    if(pm25value>0){
      String tmp_str="<pm25Value>";
      String wt_pm25value = line.substring(line.indexOf(tmp_str)+tmp_str.length(),pm25value);
      Serial.print("pm25 value : ");
      Serial.println(wt_pm25value);
      count++;
      Serial.println(count);
      tft_pm25value = wt_pm25value;
    }
    
  }
}

//////weather request
void WeatherRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  boolean readingVal;
  boolean getIsConnected = false; 
  String valString;
  float tempVal;
  
  // if there's a successful connection:
  if (client.connect(Weatherserver, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print("GET /data/2.5/weather?q=");
    client.print(WeatherCITY);
    client.print(",kr&appid=");
    //client.print("GET /data/2.5/weather?q=Seoul,kr&appid=");
    client.print(VARID);
    client.println(" HTTP/1.1");
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();
    getIsConnected = true;
  }
  else {
    // if you couldn't make a connection:
    Serial.println("weather connection failed");
    getIsConnected = false;
  }

  while(!client.available()) {
  }


  while (client.available()) {
    //i++;
    String line = client.readStringUntil('\n');
    
    //Serial.println(line);

    int temp_weather= line.indexOf("\",\"description\":");

    if(temp_weather>0) {
      String tmp_str="\"main\":\"";
      String wt_weather = line.substring(line.indexOf(tmp_str)+tmp_str.length(),temp_weather);
      Serial.print("weather : ");
      Serial.println(wt_weather);
      tft_weather = wt_weather;
     
    }

    
    int temp= line.indexOf(",\"pressure\":");

    if(temp>0) {
      String tmp_str="\"temp\":";
      String wt_temp = line.substring(line.indexOf(tmp_str)+tmp_str.length(),temp);
      Serial.print("temp : ");
      Serial.println(wt_temp);
      tft_temp = String(wt_temp.toFloat() - 273.15);
     
    }

    int temp_min= line.indexOf(",\"temp_max\":");

    if(temp_min>0) {
      String tmp_str="\"temp_min\":";
      String wt_temp_min = line.substring(line.indexOf(tmp_str)+tmp_str.length(),temp_min);
      Serial.print("temp_min : ");
      Serial.println(wt_temp_min);
      tft_temp_min = String(wt_temp_min.toFloat() - 273.15);
     
    }

    int temp_max= line.indexOf("\},\"visibility\":");

    if(temp_max>0) {
      String tmp_str="\"temp_max\":";
      String wt_temp_max = line.substring(line.indexOf(tmp_str)+tmp_str.length(),temp_max);
      Serial.print("temp_max : ");
      Serial.println(wt_temp_max);
      tft_temp_max = String(wt_temp_max.toFloat() - 273.15);
     
    }
    
    
  
    
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void get_time() {
  
  unsigned long epoch;
  int numberOfTries = 0, maxTries = 6;
  do {
    epoch = WiFi.getTime();
    numberOfTries++;
  }
  while ((epoch == 0) && (numberOfTries < maxTries));

  if (numberOfTries > maxTries) {
    Serial.print("NTP unreachable!!");
    while (1);
  }
  else {
    Serial.print("Epoch received: ");
    Serial.println(epoch);
    rtc.setEpoch(epoch);

    Serial.println();
  }
}
