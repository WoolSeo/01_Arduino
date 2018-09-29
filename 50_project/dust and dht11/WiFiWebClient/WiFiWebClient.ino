#include <SPI.h>
#include <WiFi101.h>

//// 아래 3줄을 추가하고 API키값은 공공데이터포털에 값을 복사해서 붙여넣기
//// 이 APIKEY는 작동하지 않는 키 값임
#define APIKEY    "ZyjekaA%3D%3D"
#define CITY    "종로구"
#define VERSION    "1.3"

char ssid[] = "";        // your network SSID (name)
char pass[] = "";
int keyIndex = 0; 

int status = WL_IDLE_STATUS;

///// 서버 주소를 airkorea로 변경
char server[] = "openapi.airkorea.or.kr";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");

  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    
    // 아래 11줄을 해당 위치에 바꿔 넣는다 
    client.print(F("GET /openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?stationName="));
    client.print(CITY);
    client.print(F("&dataTerm=daily&pageNo=1&numOfRows=1&ServiceKey="));
    client.print(APIKEY);
    client.print(F("&ver="));
    client.print(VERSION);
    client.print(F(" HTTP/1.1\r\n"));
    client.println("Host: openapi.airkorea.or.kr");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  }
}

void loop() {
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    while (true);
  }
}


void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}





