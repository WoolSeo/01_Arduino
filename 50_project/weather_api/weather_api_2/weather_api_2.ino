#include <ESP8266WiFi.h>

// 와이파이 ssid을 입력해주세요.
const char* ssid     = "";
//와이파이 비밀번호를 입력해주세요.
const char* password = "";

const char* host = "www.kma.go.kr";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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

  String url = "/wid/queryDFSRSS.jsp?zone=1162058500";

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

  while(client.available()){
    i++;
//라인을 기준으로 문자열을 저장한다.
    String line = client.readStringUntil('\n');

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
}
