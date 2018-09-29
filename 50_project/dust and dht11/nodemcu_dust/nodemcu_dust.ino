
#include "SPI.h"


#include <ESP8266WiFi.h>
#include <time.h>


const char* ssid = "";  // AP SSID
const char* password = ""; // AP password
const int httpPort = 80;

#define APIKEY    "DJQaZyjekaA%3D%3D"
#define VERSION    "&ver=1.3"
const char* SERVER = "openapi.airkorea.or.kr";
WiFiClient client;

void Requesthttp(){
 if (client.connect(SERVER, httpPort)) {
    Serial.println("\nSuccessed connection, and request http protocol");

    client.print(String("GET /openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?stationName=용산구&dataTerm=daily&pageNo=1&numOfRows=10&ServiceKey="));
    client.print(String(APIKEY) + String(VERSION));
    client.print(String(" HTTP/1.1\r\n"));
    client.print(String("Host: openapi.airkorea.or.kr\r\n"));
    client.print(String("Connection: close\r\n"));
    client.print(String("\r\n\r\n"));
  }else{
    Serial.println("\nfailed connection");

  }
}

void setup(void) {
  Serial.begin(115200);

  Serial.printf("start start   \r\n");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
//  Requesthttp();


}

void loop() {

  String a[3];
  int i=0;
  String temp;
  String wfEn;
  String reh;
  String tmp_str;
  static int IntervalReq=60;

  if(IntervalReq++>1000) {IntervalReq=0; Requesthttp();};


  delay(50);
  while(client.available()){

    String line = client.readStringUntil('\n');
    i= line.indexOf("</dataTime>");
      Serial.println(line); 

    if(i>0){
      tmp_str="<dataTime>";
      temp = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
      Serial.println(temp); 

    }

    i= line.indexOf("</pm10Value>");

    if(i>0){
      tmp_str="<pm10Value>";
      wfEn = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
      Serial.println(wfEn);  
    }

    i= line.indexOf("</pm25Value>");

    if(i>0){
      tmp_str="<pm25Value>";
      reh = line.substring(line.indexOf(tmp_str)+tmp_str.length(),i);
      Serial.println(reh);  
      client.stop();
        break;
    }
  }

  delay(1000);
}
