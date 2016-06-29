int ledPins[] = {2,3,4,5,6,7,8,9};

void setup()
{
  int index;
  for(index = 0; index <= 7; index++)
  {
    pinMode(ledPins[index],OUTPUT);
  }
}

void loop()
{
  oneAfterAnotherNoLoop();
}

void oneAfterAnotherNoLoop()
{
  int delayTime = 100;
  digitalWrite(ledPins[0], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[1], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[2], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[3], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[4], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[5], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[6], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[7], HIGH);
  delay(delayTime);

  digitalWrite(ledPins[7], LOW);
  delay(delayTime);
  digitalWrite(ledPins[6], LOW);
  delay(delayTime);
  digitalWrite(ledPins[5], LOW);
  delay(delayTime);
  digitalWrite(ledPins[4], LOW);
  delay(delayTime);
  digitalWrite(ledPins[3], LOW);
  delay(delayTime);
  digitalWrite(ledPins[2], LOW);
  delay(delayTime);
  digitalWrite(ledPins[1], LOW);
  delay(delayTime);
  digitalWrite(ledPins[0], LOW);
  delay(delayTime);
}

void oneAfterAnotherLoop()
{
  int index;
  int delayTime = 100;
  
  for(index = 0; index <= 7; index++)
  {
    digitalWrite(ledPins[index], HIGH);
    delay(delayTime);                
  }                                  

  for(index = 7; index >= 0; index--)
  {
    digitalWrite(ledPins[index], LOW);
    delay(delayTime);
  }               
}

void oneOnAtATime()
{
  int index;
  int delayTime = 100;
  
  for(index = 0; index <= 7; index++)
  {
    digitalWrite(ledPins[index], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[index], LOW);
  }
}

void pingPong()
{
  int index;
  int delayTime = 100;
  
  for(index = 0; index <= 7; index++)
  {
    digitalWrite(ledPins[index], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[index], LOW);
  }
  
  for(index = 7; index >= 0; index--)
  {
    digitalWrite(ledPins[index], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[index], LOW);
  }
}

void marquee()
{
  int index;
  int delayTime = 200;

  for(index = 0; index <= 3; index++)
  {
    digitalWrite(ledPins[index], HIGH);
    digitalWrite(ledPins[index+4], HIGH);
    delay(delayTime);
    digitalWrite(ledPins[index], LOW);
    digitalWrite(ledPins[index+4], LOW);
  }
}

void randomLED()
{
  int index;
  int delayTime;
  
  index = random(8);
  delayTime = 100;
	
  digitalWrite(ledPins[index], HIGH);
  delay(delayTime);
  digitalWrite(ledPins[index], LOW);
}
