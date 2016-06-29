#include <Servo.h>
Servo servo1;

void setup()
{
  servo1.attach(9);
}

void loop()
{
  int position;
  servo1.write(90);
  delay(1000);
  servo1.write(180);
  delay(1000);
  servo1.write(0);
  delay(1000);
  
  for(position = 0; position < 180; position += 2)
  {
    servo1.write(position);
    delay(20);
  }

  for(position = 180; position >= 0; position -= 1)
  {                                
    servo1.write(position);
    delay(20);
  }
}

