#include <SPI.h>
#include "WizFi250.h"

char ssid[] = "SSID";    // your network SSID (name)
char pass[] = "PASS";          // your network password
int status = WL_IDLE_STATUS;       // the Wifi radio's status

//Ubidots information
#define APIKEY    "APIKEY"
#define CITY    "CITY"
#define VERSION    "1.3"

char server[] = "openapi.airkorea.or.kr";

unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 60000L; // delay between updates, in milliseconds

boolean getIsConnected = false;

String rcvbuf;


String pm25;

// Initialize the Ethernet client object
WiFiClient client;

void httpRequest();
void printWifiStatus();

void setup()
{
  // initialize serial for debugging
  Serial.begin(115200);
  Serial.println(F("\r\nSerial Init"));

  WiFi.init();

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");

  printWifiStatus();
}

void loop() {
  // if there's incoming data from the net connection send it out the serial port
  // this is for debugging purposes only
  while (client.available()) {
    char c = client.read();
    if ( c != NULL ) {
      if (rcvbuf.length() > 50)
        rcvbuf = "";
      rcvbuf += c;
      Serial.write(c);
    }
  }

  // if 10 seconds have passed since your last connection,
  // then connect again and send data
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }
  rcvbuf = "";
}

// this method makes a HTTP connection to the server
void httpRequest() {
  Serial.println();

  // close any connection before send a new request
  // this will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection
  if (client.connect(server, 80)) {
    Serial.println("Connecting...");

    // send the HTTP PUT request
    client.print(F("GET /openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?stationName="));
    client.print(CITY);
    client.print(F("&dataTerm=daily&pageNo=1&numOfRows=10&ServiceKey="));
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
  }
  else {
    // if you couldn't make a connection
    Serial.println("Connection failed");
    getIsConnected = false;
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
