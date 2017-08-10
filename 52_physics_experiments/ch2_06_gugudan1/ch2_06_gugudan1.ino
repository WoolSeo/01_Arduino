int num = 2;
void setup() {
  Serial.begin(9600);
  for(int i = 1; i < 10; i++) {
      Serial.print(num);
      Serial.print(" x ");
      Serial.print(i);
      Serial.print(" = ");
      Serial.println( num * i);
  }
}
void loop() {
}
