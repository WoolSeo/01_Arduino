int datapin = 2; 
int clockpin = 3;
int latchpin = 4;

byte data = 0;

void setup()
{
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
}

void loop()
{
  oneAfterAnother();
}

void shiftWrite(int desiredPin, boolean desiredState)
{
  bitWrite(data,desiredPin,desiredState);
  shiftOut(datapin, clockpin, MSBFIRST, data);
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}

void oneAfterAnother()
{
  int index;
  int delayTime = 100;
  
  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH);
    delay(delayTime);                
  }
 
  for(index = 7; index >= 0; index--)
  {
    shiftWrite(index, LOW);
    delay(delayTime);
  }
}

void oneOnAtATime()
{
  int index;
  int delayTime = 100;
  
  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH);
    delay(delayTime);
    shiftWrite(index, LOW);
  }
}

void pingPong()
{
  int index;
  int delayTime = 100;

  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH);
    delay(delayTime);
    shiftWrite(index, LOW);
  }

  // step through the LEDs, from 7 to 0
  
  for(index = 7; index >= 0; index--)
  {
    shiftWrite(index, HIGH);
    delay(delayTime);
    shiftWrite(index, LOW);
  }
}

void randomLED()
{
  int index;
  int delayTime = 100;
  
  index = random(8);
  
  shiftWrite(index, HIGH);
  delay(delayTime);
  shiftWrite(index, LOW);
}

void marquee()
{
  int index;
  int delayTime = 200;
  
  for(index = 0; index <= 3; index++)
  {
    shiftWrite(index, HIGH);
    shiftWrite(index+4, HIGH);
    delay(delayTime);
    shiftWrite(index, LOW);
    shiftWrite(index+4, LOW);
  }
}

void binaryCount()
{
  int delayTime = 1000;

  shiftOut(datapin, clockpin, MSBFIRST, data);

  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
  
  data++;

  delay(delayTime);
}
