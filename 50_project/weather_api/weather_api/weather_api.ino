//http://kocoafab.cc/make/view/359

#include "SPI.h"
#include "WiFi.h"

char ssid[] = "Wool iphone6 2nd";       //와이파이 SSID
char pass[] = "";   //와이파이 password 
String location = "Gangnam"; //날씨정보를 보고싶은 지역


//인스턴스 변수 초기화
WiFiServer server(80);
WiFiClient client;

const unsigned long requestInterval = 60000;  // 요구 시간 딜레이(1 min)

IPAddress hostIp;
uint8_t ret;
unsigned long lastAttemptTime = 0;            // 마지막으로 서버에서 데이터를 전송받은 시간
String currentLine = "";          // 서버에서 전송된 데이터 String저장
String tempString = "";           // 온도 저장 변수
String humString = "";            // 습도 저장 변수
String timeString = "";           // 시간 정보 변수
String pressureString = "";       // 압력 정보 변수
boolean readingTemp = false;      //온도 데이터가 있는지 여부 판단
boolean readingHum = false;       //습도 데이터가 있는지 여부 판단
boolean readingTime = false;      //시간 데이터가 있는지 여부 판단
boolean readingPressure = false;  //압력 데이터가 있는지 여부 판단
int temp = 0;

void setup() {
  //각 변수에 정해진 공간 할당
  currentLine.reserve(100);
  tempString.reserve(10);
  humString.reserve(10);
  timeString.reserve(20);
  Serial.begin(115200);    

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

}

void loop()
{
  if (client.connected()) {
    while (client.available()) {
      //전송된 데이터가 있을 경우 데이터를 읽어들인다.
      char inChar = client.read();
      // 읽어온 데이터를 inChar에 저장한다.
      currentLine += inChar; 
      
      //Serial.print(currentLine);
      //inChar에 저장된 Char변수는 currentLine이라는 String변수에 쌓이게 된다.
      
      //라인피드(줄바꿈)문자열이 전송되면 데이터를 보내지 않는다.
      if (inChar == '\n') {
        //Serial.print("clientReadLine = ");
        //Serial.println(currentLine);
        currentLine = "";
      } 
      
      //온도 데이터가 전송되었는지 확인
      if ( currentLine.endsWith("<temperature value=")) {
        //현재 스트링이 "<temperature value="로 끝났다면 온도데이터를 받을 준비를 한다.
        readingTemp = true; 
        tempString = "";
      }      

      //<temperature value=뒤에 오는 문자열을 tempString에 저장한다.
      if (readingTemp) {
        if (inChar != 'm') { //전송될 문자가 'm'이 올때까지 온도값으로 인식
          tempString += inChar;
        } 
        else { //전송된 문자가 'm'이라면 온도데이터를 그만 저장하고 온도값 출력
          readingTemp = false;

          Serial.print("-  Temperature: ");
          Serial.print(getInt(tempString)-273);
          Serial.println((char)176);    //degree symbol
        }
      }

      if ( currentLine.endsWith("<humidity value=")) {
        //현재 스트링이 "<humidity value ="로 끝났다면 습도 데이터를 받을 준비를 한다.
        readingHum = true; 
        humString = "";
      }

      if (readingHum) { 
        if (inChar != 'u') {//전송될 문자열이 'u'가 아니라면 계속 습도값을 받게 된다.
          humString += inChar;
        } 
        else { //다음에 전송된 문자열이 'u'라면 습도값을 그만 받고 값을 출력한다.
          readingHum = false;
          Serial.print("-  Humidity: ");
          Serial.print(getInt(humString));
          Serial.println((char)37);
        }
      }

      if ( currentLine.endsWith("<lastupdate value=")) {
        // 현재 스트링이 "<lastupdata value="로 끝났다면 마지막 업데이트 시간 데이터를 받을 준비를 한다.
        readingTime = true; 
        timeString = "";
      }

      if (readingTime) {
        if (inChar != '/') { //다음 전송될 문자가 '/'가 아니라면 계속적으로 시간데이터를 받는다
          timeString += inChar;
        } 
        else {
          readingTime = false;
          Serial.print("-  Last update: ");
          Serial.println(timeString.substring(2,timeString.length()-1));
        }
      }

      if ( currentLine.endsWith("<pressure value=")) {
        // 현재 스트링이 "<pressure value="로 끝났다면 기압 데이터를 받을 준비를 한다.
        readingPressure = true; 
        pressureString = "";
      }      

      if (readingPressure) {
        if (inChar != 'u') { //다음 전송될 문자가 'u'가 아니라면 계속 기압데이터를 받는다.
          pressureString += inChar;
        } 
        else { //다음 전송된 문자가 'u'라면 기압데이터를 출력한다.
          readingPressure = false;

          Serial.print("-  Pressure: ");
          Serial.print(getInt(pressureString));
          Serial.println("hPa"); 
        }

      }

      if ( currentLine.endsWith("</current>")) { //현재 스트링이 </current>로 끝났다면 연결을 끊고 다시 서버와 연결을 준비한다.
        delay(10000); //10초뒤에 서버와 연결을 끊고 재연결을 시도한다.
        client.stop(); 
        connectToServer();
        //Serial.println("Disconnected from Server.\n");
      }
    }   

  }
  else if (millis() - lastAttemptTime > requestInterval) {
    //연결을 실패했다면 requestInterval(60초)이후에 다시 연결을 시도한다.
    connectToServer();
  }  
}

//서버와 연결
void connectToServer() {
  Serial.println("connecting to server...");
  String content = "";
  if (client.connect(hostIp, 80)) {
    Serial.println("Connected! Making HTTP request to api.openweathermap.org for "+location+"...");
    //Serial.println("GET /data/2.5/weather?q="+location+"&mode=xml");
    client.println("GET /data/2.5/weather?q="+location+"&mode=xml"); 
    //위에 지정된 주소와 연결한다.
    client.print("HOST: api.openweathermap.org\n");
    client.println("User-Agent: launchpad-wifi");
    client.println("Connection: close");

    client.println();
    Serial.println("Weather information for "+location);
  }
  //마지막으로 연결에 성공한 시간을 기록
  lastAttemptTime = millis();
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

  ret = WiFi.hostByName("api.openweathermap.org", hostIp);

  Serial.print("ret: ");
  Serial.println(ret);

  Serial.print("Host IP: ");
  Serial.println(hostIp);
  Serial.println("");
}

int getInt(String input){  //String데이터를 intger형으로 변환하는 함수
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
