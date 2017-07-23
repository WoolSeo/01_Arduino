const int L_motor = 9;
const int R_motor = 10;

const int trigPin = 5;
const int echoPin = 6;

int duration, distance;

void setup() {
  Serial.begin (9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(L_motor, OUTPUT);
  pinMode(R_motor, OUTPUT);
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
  }
  else {
    digitalWrite(L_motor, LOW);
    digitalWrite(R_motor, LOW);
  }
 
  Serial.print(distance);
  Serial.println("cm");
  delay(10);
}
