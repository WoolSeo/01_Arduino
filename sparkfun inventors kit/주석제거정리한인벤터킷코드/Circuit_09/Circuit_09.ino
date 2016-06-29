#include <Servo.h> 
Servo servo1;
const int flexpin = 0; 

void setup() 
{ 
  Serial.begin(9600);
  servo1.attach(9);
} 

void loop() 
{ 
  int flexposition;
  int servoposition;
  
  flexposition = analogRead(flexpin);
  
  servoposition = map(flexposition, 600, 900, 0, 180);
  servoposition = constrain(servoposition, 0, 180);

  servo1.write(servoposition);
  
  Serial.print("sensor: ");
  Serial.print(flexposition);
  Serial.print("  servo: ");
  Serial.println(servoposition);
  
  delay(20);
} 


