int inputPin = 8;
void setup() {
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
}
void loop() {
  Serial.println(digitalRead(inputPin));
  delay(200);
}
