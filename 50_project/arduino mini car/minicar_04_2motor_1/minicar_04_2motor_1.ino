const int L_motor = 9;
const int R_motor = 10;

void setup() {
  pinMode(L_motor, OUTPUT);
  pinMode(R_motor, OUTPUT);
  
  digitalWrite(L_motor, HIGH);
  digitalWrite(R_motor, HIGH);
  delay(1000);

  digitalWrite(L_motor, LOW);
  digitalWrite(R_motor, LOW);
}

void loop() {
}
