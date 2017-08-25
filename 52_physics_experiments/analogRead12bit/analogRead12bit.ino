int t0, t;
void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
}
void loop() {
  if (Serial.available() > 0) {
    if( Serial.read() == 'a') {
       t0 = micros();
       do {
          t = micros() - t0;
          Serial.print(t);
          Serial.print(", ");
          Serial.println(analogRead(A0));
          delayMicroseconds(10);
       }while (t < 2000000);
    }
  }
}
