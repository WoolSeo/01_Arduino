int sum;
int i;
void setup() {
  // open a serial connection
  Serial.begin(9600); 
  
  
}

void loop() {
  if (Serial.available() > 0) {
    if( Serial.read() == 'a') {
       for(i = 0; i <100; i++) {
        analogReadResolution(12);
        sum += analogRead(A1);
        delay(50);
      }
      Serial.println(sum/100);
      sum = 0;
    }
  }
  
}
