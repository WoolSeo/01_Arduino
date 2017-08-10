int num = 0;
void setup() {
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    num = Serial.read()-48;
    for(int i = 1; i < 10; i++) {
      Serial.print(num);
      Serial.print(" x ");
      Serial.print(i);
      Serial.print(" = ");
      Serial.println( num * i);
    }
  }
}
