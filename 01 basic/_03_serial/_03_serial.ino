int led = 12;
int sw = 7;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT);

  Serial.begin(9600);
}
void loop() {
  int state = digitalRead(sw);
  Serial.println(state);
  
  if (state == HIGH) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }

  delay(500);
}
