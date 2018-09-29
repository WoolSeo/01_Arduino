/*

 This example connects to an unencrypted Wifi network.
 Then it prints the  MAC address of the Wifi shield,
 the IP address obtained, and other network details.

 Circuit:
 * WiFi shield attached

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "";     //  your network SSID (name)
char pass[] = "";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

const char* host = "www.kma.go.kr";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();

}

int value = 0;

void loop() {
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  //http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=1162058500

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  //zone을 일종의 지역 정보입니다.
   // http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4111159100
  String url = "www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4111159100";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  String weather_str="";

  //온도
  String wt_temp="";
  //오늘의날씨
  String wt_wfKor="";
  String wt_wfEn="";
  //습도
  String wt_reh="";
  int i=0;

  if(client.available()){
    Serial.println("client available");
  }
  else {
    Serial.println("client not available");
  }
  while(client.available()){
    i++;
//라인을 기준으로 문자열을 저장한다.
    String line = client.readStringUntil('\n');
    Serial.println(line);
    int temp33= line.indexOf("seq=\"1\"");
    if(temp33>0)
    {
      break;
    }

//온도 xml 에서 파싱
    int temp= line.indexOf("</temp>");
    if(temp>0)
    {

      String tmp_str="<temp>";
      String wt_temp = line.substring(line.indexOf(tmp_str)+tmp_str.length(),temp);
      Serial.println(wt_temp);
    }

//날씨 정보 영문으로 가져오기
    int wfEn= line.indexOf("</wfEn>");
    if(wfEn>0)
    {

      String tmp_str="<wfEn>";
      String wt_twfEn = line.substring(line.indexOf(tmp_str)+tmp_str.length(),wfEn);
      Serial.println(wt_twfEn);
    }

//날씨 정보 으로 가져오기
    int wfKor= line.indexOf("</wfKor>");
    if(wfKor>0)
    {
      String tmp_str="<wfKor>";
      String wt_wfKor = line.substring(line.indexOf(tmp_str)+tmp_str.length(),wfKor);
      Serial.println(wt_wfKor);
    }

    int reh= line.indexOf("</reh>");
    if(reh>0)
    {
      String tmp_str="<reh>";
      String wt_reh = line.substring(line.indexOf(tmp_str)+tmp_str.length(),reh);
      Serial.println(wt_reh);
    }

  }

  //int ln_num= weather_str.indexOf("\n");


  Serial.println();
  Serial.println("closing connection");
  delay(20000);
  
  // check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

