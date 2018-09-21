// 참고
// - http://www.kocoafab.cc/tutorial/view/595

#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "wool2";       //와이파이 SSID
char pass[] = "";   //와이파이 password 

WiFiServer server(80);
WiFiClient client;

IPAddress hostIp;
uint8_t ret;

int temp = 0;

String weather_str="";
String wt_temp="";
String wt_wfKor="";
String wt_wfEn="";
String wt_reh="";
String wt_hour="";
String wt_twfEn="";

String lasttemp;
String lasthour;
String lastreh;
String lasttwfEn;

int count=0;

void setup() {
  //각 변수에 정해진 공간 할당
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

void loop() {
  if (client.connected()) {
    while (client.available()) {
      //라인을 기준으로 문자열을 저장한다.
      String line = client.readStringUntil('\n');
      //Serial.println(line);
      
      //시간
      int temp11= line.indexOf("</hour>");
      if(temp11>0) {
        String tmp_str="<hour>";
        String wt_hour = line.substring(line.indexOf(tmp_str)+tmp_str.length(),temp11);
        lasthour = wt_hour;  
      }
      
      //온도
      int temp= line.indexOf("</temp>");
      if(temp>0) {
        String tmp_str="<temp>";
        String wt_temp = line.substring(line.indexOf(tmp_str)+tmp_str.length(),temp);
        lasttemp = wt_temp;  
      }
      
      //날씨 정보
      int wfEn= line.indexOf("</wfEn>");
      if(wfEn>0) {
        String tmp_str="<wfEn>";
        String wt_twfEn = line.substring(line.indexOf(tmp_str)+tmp_str.length(),wfEn);
        lasttwfEn = wt_twfEn;
      }
      
      //습도
      int reh= line.indexOf("</reh>");
      if(reh>0) {
        String tmp_str="<reh>";
        String wt_reh = line.substring(line.indexOf(tmp_str)+tmp_str.length(),reh);
        lastreh = wt_reh;
      }
    }   
  }
  Serial.println(count);
  Serial.print("hour is "); 
  Serial.println(lasthour);
  Serial.print("temperature is "); 
  Serial.println(lasttemp);
  Serial.print("weather is ");
  Serial.println(lasttwfEn); 
  Serial.print("Humidity is ");
  Serial.println(lastreh);
  delay(10000);
  count++;
}

//서버와 연결
void connectToServer() {
  Serial.println("connecting to server...");
  String content = "";
  if (client.connect(hostIp, 80)) {
    Serial.println("Connected! Making HTTP request to www.kma.go.kr");
    //Serial.println("GET /data/2.5/weather?q="+location+"&mode=xml");
    client.println("GET /wid/queryDFSRSS.jsp?zone=4111159100 HTTP/1.1"); 
    //위에 지정된 주소와 연결한다.
    client.print("HOST: www.kma.go.kr\n");
    client.println("User-Agent: launchpad-wifi");
    client.println("Connection: close");
    
    client.println();
    Serial.println("Weather information for ");
  }
  //마지막으로 연결에 성공한 시간을 기록
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
  
  ret = WiFi.hostByName("www.kma.go.kr", hostIp);
  
  Serial.print("ret: ");
  Serial.println(ret);
  
  Serial.print("Host IP: ");
  Serial.println(hostIp);
  Serial.println("");
}

int getInt(String input){
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


