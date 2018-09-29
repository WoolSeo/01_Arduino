//https://www.kocoafab.cc/make/view/709
//http://ilikesan.com/561

#include <SPI.h>
#include <WiFi101.h>

#define APIKEY    "Z6udu8Eil%2FNLlWOP4UfsTvE%2B4DJQaZyjekaA%3D%3D"
#define CITY    "신풍동"//"신풍동"
#define VERSION    "1.3"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "";        // your network SSID (name)
char pass[] = "";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

unsigned long refresh_time = 120000;//3600000;
unsigned long current_time = 0;
unsigned long past_time = 0;


int status = WL_IDLE_STATUS;

char server[] = "openapi.airkorea.or.kr";

unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 60000L; // delay between updates, in milliseconds

boolean getIsConnected = false;

String rcvbuf;

int pm10 = 0;
int pm25 = 0;

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  
}

void loop() {

  
  current_time = millis();
  
  if(current_time - refresh_time - past_time > 0) {
    //connect airkorea
    
    //Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
    
    if (client.connect(server, 80)) {
      Serial.println("Connecting...");
  
      // send the HTTP PUT request
      client.print(F("GET /openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?stationName="));
      client.print(CITY);
      client.print(F("&dataTerm=daily&pageNo=1&numOfRows=1&ServiceKey="));
      client.print(APIKEY);
      client.print(F("&ver="));
      client.print(VERSION);
      client.print(F(" HTTP/1.1\r\n"));
      //client.print(F("Host: openapi.gbis.go.kr\r\n"));
      client.print(F("Host: openapi.airkorea.or.kr\r\n"));
      client.print(F("Connection: close\r\n"));
      client.print(F("\r\n\r\n"));
  
      // note the time that the connection was made
      lastConnectionTime = millis();
      getIsConnected = true;

       int i = 0;
      // if there are incoming bytes available
      // from the server, read them and print them:
      while (client.available()) {
        //char c = client.read();
        //Serial.write(c);
    
        i++;
        String line = client.readStringUntil('\n');
        //int temp33= line.indexOf("seq=\"1\"");
        //if(temp33>0){
        //  break;
        //}
    
        int datatime= line.indexOf("</dataTime>");
        if(datatime>0){
          String tmp_str="<dataTime>";
          String wt_datatime = line.substring(line.indexOf(tmp_str)+tmp_str.length(),datatime);
          Serial.print("datetime : ");
          Serial.println(wt_datatime);
        }
        
        int pm10value= line.indexOf("</pm10Value>");
        if(pm10value>0){
          String tmp_str="<pm10Value>";
          String wt_pm10value = line.substring(line.indexOf(tmp_str)+tmp_str.length(),pm10value);
          Serial.print("pm10 value : ");
          Serial.println(wt_pm10value);
        }
    
        int pm25value= line.indexOf("</pm25Value>");
        if(pm25value>0){
          String tmp_str="<pm25Value>";
          String wt_pm25value = line.substring(line.indexOf(tmp_str)+tmp_str.length(),pm25value);
          Serial.print("pm25 value : ");
          Serial.println(wt_pm25value);  
        }
  
      }
  
      
      if (!client.connected()) {
        Serial.println();
        Serial.println("disconnecting from server.");
        client.stop();
    
        // do nothing forevermore:
        //while (true);
      }
     }
      else {
        // if you couldn't make a connection
        Serial.println("Connection failed");
        getIsConnected = false;
      }

    
    
    past_time = current_time;
  }
  else {
    //dht11
    
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





