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

char server[] = "openapi.airkorea.or.kr";

#define APIKEY    "nESF1DreNeshOI7Q6zdswaS7wzLtVFLILOfnpEs%2B2QIUSVhqQoZ6udu8Eil%2FNLlWOP4UfsTvE%2B4DJQaZyjekaA%3D%3D"
#define CITY    "신풍동"//"신풍동"
#define VERSION    "1.3"

const int reconnect_wifi_Interval = 10; // 10 minutes
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


#define PiezoPIN 3 



String tft_datatime = "";
String tft_pm10value = "";
String tft_pm25value = "";

int pm10 = 0;
int pm25 = 0;
int dustLevel = 0;
int predustLevel = 0;


int time_h = 0;
int time_m = 0;




void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  rtc.begin();
  
  wificonnent();

  dustRequest();
  
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

  tone(PiezoPIN, 2000);
  delay(3000);
  noTone(PiezoPIN);
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
    tone(PiezoPIN, 1000);
    delay(3000);
    noTone(PiezoPIN);
    delay(10);
    predustLevel = dustLevel;
  }
  
  tft.setRotation(0); //0~3
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);

  tft.setTextSize(2);
  tft.println(" ");
  
  tft.setTextSize(8);
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
  
  tft.setTextSize(5);
  
  tft.print("H: ");
  tft.print(int(h));
  tft.println("%");
  tft.print("T: ");
  tft.print(int(t));
  tft.println("*C ");

  tft.setTextSize(2);
  tft.println(" ");
  
  tft.setTextSize(4);
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

  get_time();
  
}


// this method makes a HTTP connection to the server:
void dustRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
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
    Serial.println("connection failed");
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
