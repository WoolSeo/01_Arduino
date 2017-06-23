#define E1 10  // Enable Pin for motor 1
#define E2 11  // Enable Pin for motor 2
 
#define I1 8  // Control pin 1 for motor 1
#define I2 9  // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2


const int trigPin = 5;
const int echoPin = 6;

int duration, distance;


void setup() {
 
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
 
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);

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
    delay(10);
    
    if(distance > 20) {
      analogWrite(E1, 255); // Run in half speed
      analogWrite(E2, 255); // Run in full speed
 
      digitalWrite(I1, HIGH);
      digitalWrite(I2, LOW);
      digitalWrite(I3, HIGH);
      digitalWrite(I4, LOW);
    }
    else {
      digitalWrite(E1, LOW);
      digitalWrite(E2, LOW); 
    }


}
