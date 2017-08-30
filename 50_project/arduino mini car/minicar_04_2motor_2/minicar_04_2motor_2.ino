const int L_motor = 9;
const int R_motor = 10;

void setup() {
  analogWrite(L_motor, 200);
  analogWrite(R_motor, 200);
  delay(1000);

  analogWrite(L_motor, 0);
  analogWrite(R_motor, 0);
}

void loop() {
}
