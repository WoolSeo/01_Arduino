const int button1Pin = 2;
const int button2Pin = 3;
const int ledPin =  13;

void setup()
{
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  pinMode(ledPin, OUTPUT);      
}


void loop()
{
  int button1State, button2State;

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  if ((button1State == HIGH) && (button2State == HIGH)) 
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}
