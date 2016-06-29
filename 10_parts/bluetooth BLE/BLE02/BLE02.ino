#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,4);
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  char c;
  if(mySerial.available()){
    c = mySerial.read();
    Serial.println(c);
    if ( c == 'a' )
      digitalWrite(13, HIGH);
    else
      digitalWrite(13, LOW);
    delay(1000);
  }
  //else
  //{
    //Serial.println("not connect");
    //delay(1000);
  //}
}
