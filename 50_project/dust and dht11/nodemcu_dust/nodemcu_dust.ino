
#include "SPI.h"


#include <ESP8266WiFi.h>
#include <time.h>


const char* ssid = "wool2";  // AP SSID
const char* password = "1q3e5t7u!"; // AP password
const int httpPort = 80;

#define APIKEY    "nESF1DreNeshOI7Q6zdswaS7wzLtVFLILOfnpEs%2B2QIUSVhqQoZ6udu8Eil%2FNLlWOP4UfsTvE%2B4DJQaZyjekaA%3D%3D"
#define VERSION    "&ver=1.3"
#define CITY    "종로구"//"신풍동"

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
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


}

void loop() {
  //Requesthttp();

  dustRequest();
  
}

void dustRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(SERVER, httpPort)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print(F("GET /openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?stationName="));
    client.print(CITY);
    client.print(F("&dataTerm=month&pageNo=1&numOfRows=1&ServiceKey="));
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
    Serial.println(line);delay(100);
  }
    /*int datatime= line.indexOf("</dataTime>");
    
    if(datatime>0){
      Serial.println("-----------------------------");
      String tmp_str="<dataTime>";
      String wt_datatime = line.substring(line.indexOf(tmp_str)+tmp_str.length(),datatime);
      Serial.print("datetime : ");
      Serial.println(wt_datatime);

    }
    delay(500);
    int pm10value= line.indexOf("</pm10Value>");
    
    if(pm10value>0){
      String tmp_str="<pm10Value>";
      String wt_pm10value = line.substring(line.indexOf(tmp_str)+tmp_str.length(),pm10value);
      Serial.print("pm10 value : ");
      Serial.println(wt_pm10value);

    }
    delay(500);
    
    int pm25value= line.indexOf("</pm25Value>");
    
    if(pm25value>0){
      String tmp_str="<pm25Value>";
      String wt_pm25value = line.substring(line.indexOf(tmp_str)+tmp_str.length(),pm25value);
      Serial.print("pm25 value : ");
      Serial.println(wt_pm25value);


    }
    delay(500);*/
  //}
  delay(60000);
  Serial.println("-----------------------------------------");
  Serial.println();
  Serial.println();
  Serial.println();
}
