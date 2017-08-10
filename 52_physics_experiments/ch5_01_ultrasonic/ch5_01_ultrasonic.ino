const int trigPin = 13;
const int echoPin = 12;

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
         
  Serial.println(duration);

  delay(1000);
}
