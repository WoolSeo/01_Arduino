void setup() {
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  delay(1000);                     
  digitalWrite(4, LOW); 
  digitalWrite(3, HIGH);   
  delay(1000);                
}
