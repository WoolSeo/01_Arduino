void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(5000);

  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(2000);
}
