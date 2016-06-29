#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,4);
void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char c;
  if(mySerial.available()){
    c = mySerial.read();
    Serial.println(c);
  }
}
