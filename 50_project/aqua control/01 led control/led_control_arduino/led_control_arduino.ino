const int ledpin1 = 6;
const int ledpin2 = 7;

int ledstate1 = 0;
int ledstate2 = 0;

void setup() {
  Serial.begin(9600);

  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);

  digitalWrite(ledpin1, LOW);
  digitalWrite(ledpin2, LOW);
}

void loop() {
  char leddata;

  if(Serial.available()){
    
    leddata = Serial.read();

    if(leddata == 'a') {
      if(ledstate1 == 0) {
        digitalWrite(ledpin1, HIGH);
        ledstate1 = 1;
      }
      else {
        digitalWrite(ledpin1, LOW);
        ledstate1 = 0;
      }
    }
    else if(leddata == 'b') {
      if(ledstate2 == 0) {
        digitalWrite(ledpin2, HIGH);
        ledstate2 = 1;
      }
      else {
        digitalWrite(ledpin2, LOW);
        ledstate2 = 0;
      }
    }
    delay(50);
  }
}
