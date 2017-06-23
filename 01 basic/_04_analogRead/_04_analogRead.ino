const int potPin = A0;
int potVal = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  potVal = analogRead(potPin);
  
  Serial.print("potVal : ");
  Serial.println(potVal);
  
  delay(500);
}
