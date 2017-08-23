const int trigPin = 5;
const int echoPin = 6;

int duration, distance;

void setup() {
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
          
  duration = pulseIn(echoPin, HIGH);
          
  distance = duration / 58;

  Serial.print(distance);
  Serial.println("cm");

  delay(1000);
}
