const int trigPin = 13;
const int echoPin = 12;

int duration, distance;

void setup() {
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    if (Serial.available() > 0) {
      char inputdata = Serial.read();
      if(inputdata == 's') {
        for(int i = 0; i< 3000; i++) {
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
          
          Serial.print(millis());
          Serial.print(",");
          Serial.println(pulseIn(echoPin, HIGH)/(float)58);
        }
        Serial.println("Done");
        Serial.println();
      }
    }  
}
