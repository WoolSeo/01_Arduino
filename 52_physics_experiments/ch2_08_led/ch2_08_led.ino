int inputdata = 0;
void setup() {
  Serial.begin(9600);
  pinMode(13, HIGH);
}
void loop() {
  if (Serial.available() > 0) {
    inputdata = Serial.read();
    if( inputdata == 97 ) {
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
    }
    Serial.print("I received: ");
    Serial.println(inputdata);
  }
}
