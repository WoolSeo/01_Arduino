const int DM_SPEED_PIN = 5; // 스피트 관련 핀
const int DM_DRIVE_PIN = 3; // 전진 핀
const int DM_BACK_PIN = 2;

void setup() {
  pinMode(DM_SPEED_PIN, OUTPUT);
  pinMode(DM_DRIVE_PIN, OUTPUT);
  //pinMode(DM_BACK_PIN, OUTPUT);
}

void loop() {
  digitalWrite(DM_DRIVE_PIN, HIGH);
  //digitalWrite(DM_BACK_PIN, LOW);
  analogWrite(DM_SPEED_PIN, 250);
  delay(1000);
  digitalWrite(DM_DRIVE_PIN, LOW);
  //digitalWrite(DM_BACK_PIN, LOW);
  delay(1000);
  //while( 1 );
}
