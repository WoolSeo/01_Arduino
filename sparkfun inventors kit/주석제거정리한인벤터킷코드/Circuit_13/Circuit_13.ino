const int relayPin = 2;
const int timeDelay = 1000;

void setup()
{
  pinMode(relayPin, OUTPUT);
}


void loop()                    
{
  digitalWrite(relayPin, HIGH);
  
  delay(timeDelay);
  
  digitalWrite(relayPin, LOW);
  
  delay(timeDelay);
} 

