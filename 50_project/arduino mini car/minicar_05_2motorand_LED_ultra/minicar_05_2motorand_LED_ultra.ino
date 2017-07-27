const int L_motor = 9;
const int R_motor = 10;
const int L_led = 12;
const int R_led = 13;
const int echoPin = 5;
const int trigPin = 6;

int duration, distance;

void setup() {
  pinMode(L_motor, OUTPUT);
  pinMode(R_motor, OUTPUT);
  pinMode(L_led, OUTPUT);
  pinMode(R_led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
          
  duration = pulseIn(echoPin, HIGH);
          
  distance = duration / 58;

  if(distance > 30) {
    digitalWrite(L_motor, HIGH);
    digitalWrite(R_motor, HIGH);
    digitalWrite(L_led, HIGH);
    digitalWrite(R_led, HIGH);
  }
  else {
    digitalWrite(L_motor, LOW);
    digitalWrite(R_motor, LOW);
    digitalWrite(L_led, LOW);
    digitalWrite(R_led, LOW);
  }
  
  delay(10);
}
