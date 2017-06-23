const int LED_Pin = 11;
const int CdS_Pin = A0;
int CdS_value = 0;
int light_value = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  CdS_value = analogRead(CdS_Pin);
  light_value = map(CdS_value, 0, 1023, 0, 255);

  Serial.print("CdS Value : ");
  Serial.print(CdS_value);
  Serial.print(", light Value : ");
  Serial.println(light_value);   
  
  analogWrite(LED_Pin, light_value);
  delay(500);
}
