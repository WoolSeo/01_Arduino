#define SW1Pin 5
#define SW2Pin 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SW1Pin, INPUT_PULLUP);
  pinMode(SW2Pin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int SW1Val = digitalRead(SW1Pin);
  if( SW1Val == HIGH) {
    Serial.println("SW1 pressed");
  }
  
  int SW2Val = digitalRead(SW2Pin);
  if( SW2Val == HIGH) {
    Serial.println("SW2 pressed");
  }
  
  delay(500);
  //Serial.println(analogRead(A0));
}
