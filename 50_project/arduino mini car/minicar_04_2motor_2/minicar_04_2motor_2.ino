const int L_motor = 10;
const int R_motor = 11;

void setup() {
  analogWrite(L_motor, 230);
  analogWrite(R_motor, 230);
  delay(1000);

  analogWrite(L_motor, 0);
  analogWrite(R_motor, 0);
}

void loop() {
}
