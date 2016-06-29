const int sensorPin = 0;
const int ledPin = 9;
int lightLevel, high = 0, low = 1023;
  
void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  lightLevel = analogRead(sensorPin);
  manualTune();
  analogWrite(ledPin, lightLevel);
}


void manualTune()
{
  lightLevel=map(lightLevel,0,1023,0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
} 

void autoTune()
{
  if (lightLevel < low)
  {
    low = lightLevel;
  }
  if (lightLevel > high)
  {
    high = lightLevel;
  }
  
  lightLevel=map(lightLevel,low+30, high-30, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);  
}

