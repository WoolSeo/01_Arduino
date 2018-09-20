int steps=9;
int dir =8;
int stepTime=190;



void setup() {
  //pinMode(13, OUTPUT);
  pinMode(steps, OUTPUT);
  pinMode(dir, OUTPUT);
  digitalWrite(dir, HIGH);
  //digitalWrite(13, HIGH);
}


void loop() {
  
  digitalWrite(steps, HIGH);   
  delayMicroseconds(stepTime);                      
  digitalWrite(steps, LOW);    
  delayMicroseconds(1000);                       
}
