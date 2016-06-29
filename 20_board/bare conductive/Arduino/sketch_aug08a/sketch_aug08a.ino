int incomingByte = 0;
void setup() {
  Serial.begin(9600);
  pinMode(13, HIGH);
}
void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if( incomingByte == 65) {
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
    }
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}
