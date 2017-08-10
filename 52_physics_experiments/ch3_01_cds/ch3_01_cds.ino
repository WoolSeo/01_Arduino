void setup() {
  Serial.begin(9600);
  for(int i = 0; i<1000; i++) {
    Serial.print(millis());
    Serial.print(", ");
    Serial.println(analogRead(A0));
    delay(10);
  }
}
void loop() {
}
