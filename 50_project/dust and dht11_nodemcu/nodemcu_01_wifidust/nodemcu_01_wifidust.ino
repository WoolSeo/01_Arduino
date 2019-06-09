#include <ESP8266WiFi.h>

const char* ssid = "wool2";
const char* password = "1q3e5t7u!";

const char* server = "openapi.airkorea.or.kr";

#define APIKEY    "nESF1DreNeshOI7Q6zdswaS7wzLtVFLILOfnpEs%2B2QIUSVhqQoZ6udu8Eil%2FNLlWOP4UfsTvE%2B4DJQaZyjekaA%3D%3D"
#define CITY    "종로구"//"신풍동"
#define VERSION    "1.3"

const int reconnect_wifi_Interval = 3; // 10 minutes
const long refresh_lcd_Interval = 20L * 1000L; // 20 seconds

String tft_datatime = "";
String tft_pm10value = "";
String tft_pm25value = "";

int pm10 = 0;
int pm25 = 0;

int time_h = 0;
int time_m = 0;
int time_h_temp = 0;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}

void loop() {  
  Serial.print("connecting to ");
  Serial.println(server);

  if (!client.connect(server, 80)) {
    Serial.println("connection failed");
    return;
  }
    
  client.print(String("GET /openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?stationName="));
  client.print(String(CITY));
  client.print(String("&dataTerm=daily&pageNo=1&numOfRows=1&ServiceKey="));
  client.print(String(APIKEY));
  client.print(String("&ver="));
  client.print(String(VERSION));
  client.print(String(" HTTP/1.1\r\n"));
  client.println(String("Host: openapi.airkorea.or.kr"));
  client.println(String("Connection: close"));
  client.println();
  
  while(!client.connected()) {  
  }

  int i = 0;
  while (client.connected()) {
    i++;
    String line = client.readStringUntil('\n');
    Serial.println(line);
    
    /*int datatime= line.indexOf("</dataTime>");
    
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
      //count++;
      //Serial.println(count);
      tft_pm25value = wt_pm25value;
    }*/
    //delay(10);
  }
  
  delay(10000);
  Serial.println("closing connection");
}
