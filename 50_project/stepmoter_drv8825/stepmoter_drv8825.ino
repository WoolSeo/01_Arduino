int steps=10;
int dir =11;
int stepTime=100;



void setup() {
  
  pinMode(steps, OUTPUT);
  pinMode(dir, OUTPUT);
}


void loop() {
  digitalWrite(dir, HIGH);
  digitalWrite(steps, HIGH);   
  delay(stepTime);                      
  digitalWrite(steps, LOW);    
  delay(stepTime);                       
}
