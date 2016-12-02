const int motor1_PWM = 9;
const int motor1_DIR = 8;

void setup() {
  pinMode(motor1_DIR, OUTPUT);
  //pinMode(motor1_PWM, OUTPUT);

}

void loop() {
  digitalWrite(motor1_DIR, HIGH);
  for(int i = 0; i<256;i++) {
    analogWrite(motor1_PWM, i); 
    delay(50); 
  }
  delay(2000);
  for(int i = 255; i>0;i--) {
    analogWrite(motor1_PWM, i);  
    delay(50);
  }
  digitalWrite(motor1_DIR, LOW);
  for(int i = 0; i<256;i++) {
    analogWrite(motor1_PWM, i); 
    delay(50); 
  }
  delay(2000);
  for(int i = 255; i>0;i--) {
    analogWrite(motor1_PWM, i);  
    delay(50);
  }

  analogWrite(motor1_PWM, 0);
  delay(2000);
  
}
