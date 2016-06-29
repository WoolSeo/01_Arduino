const int motorPin = 9;

void setup()
{
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
     serialSpeed();
}

void motorOnThenOff()
{
  int onTime = 3000;
  int offTime = 3000;
  
  digitalWrite(motorPin, HIGH);
  delay(onTime);
  digitalWrite(motorPin, LOW);
  delay(offTime);
}

void motorOnThenOffWithSpeed()
{
  int Speed1 = 200;
  int Time1 = 3000;
  
  int Speed2 = 50;
  int Time2 = 3000;
  
  analogWrite(motorPin, Speed1);
  delay(Time1);
  analogWrite(motorPin, Speed2);
  delay(Time2);
}

void motorAcceleration()
{
  int speed;
  int delayTime = 20;
  
  for(speed = 0; speed <= 255; speed++)
  {
    analogWrite(motorPin,speed);
    delay(delayTime);
  }
  
  for(speed = 255; speed >= 0; speed--)
  {
    analogWrite(motorPin,speed);
    delay(delayTime);
  }
}

void serialSpeed()
{
  int speed;
  
  Serial.println("Type a speed (0-255) into the box above,");
  Serial.println("then click [send] or press [return]");
  Serial.println();

  while(true)
  {
    while (Serial.available() > 0)
    {
      speed = Serial.parseInt();
      speed = constrain(speed, 0, 255);
      Serial.print("Setting speed to ");
      Serial.println(speed);
      analogWrite(motorPin, speed);
    }
  }
}



