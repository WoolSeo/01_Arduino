int potPin = A0;
void setup() {
  Serial.begin(9600);
}
void loop() {
  Serial.println(analogRead(A0)/1023.0*5.0);
  delay(100);
}
