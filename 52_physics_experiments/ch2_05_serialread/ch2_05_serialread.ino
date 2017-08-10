int inputdata = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    inputdata = Serial.read();
    Serial.print("I received: ");
    Serial.println(inputdata);
  }
}
