const int L_motor = 9;
const int R_motor = 10;
const int L_led = 12;
const int R_led = 13;

void setup() {
  pinMode(L_motor, OUTPUT);
  pinMode(R_motor, OUTPUT);
  pinMode(L_led, OUTPUT);
  pinMode(R_led, OUTPUT);
}

void loop() {
  digitalWrite(L_motor, HIGH);
  digitalWrite(R_motor, HIGH);
  digitalWrite(L_led, HIGH);
  digitalWrite(R_led, HIGH);
  delay(1000);

  digitalWrite(L_motor, LOW);
  digitalWrite(R_motor, LOW);
  digitalWrite(L_led, LOW);
  digitalWrite(R_led, LOW);
  delay(1000);
}
