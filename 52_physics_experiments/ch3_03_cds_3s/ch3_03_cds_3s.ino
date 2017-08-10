int t0, t;
void setup() {
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    if( Serial.read() == 'a') {
       t0 = millis();
       do {
          t = millis() - t0;
          Serial.print(t);
          Serial.print(", ");
          Serial.println(analogRead(A0));
       }while (t < 3000);
    }
  }
}
