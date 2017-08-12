#include <Servo.h>

Servo myservo;
 
int pos, duration, distance;
const int trigPin = 13;
const int echoPin = 12;

void setup() {
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    myservo.attach(6);
    myservo.write(0);
    delay(2000);
}

void loop() {
    for (pos = 0; pos <= 180; pos += 1) {
        myservo.write(pos);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
          
        Serial.print(pos);
        Serial.print(",");
        Serial.println(pulseIn(echoPin, HIGH)/(float)58);
        delay(100);
    }
    delay(20000);
}
