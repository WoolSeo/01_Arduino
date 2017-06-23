int led = 12;
int sw = 7;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT);
}
void loop() {
 int state = digitalRead(sw);
  
  if (state == HIGH) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}
