#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,4); //RX-4, TX-2
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
}
void loop() {
  char c;
  if(mySerial.available()){
    c = mySerial.read();
    Serial.println(c);
  }
}
