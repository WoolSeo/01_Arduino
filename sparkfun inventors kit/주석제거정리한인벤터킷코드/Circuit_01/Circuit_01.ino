void setup()
{
  pinMode(13, OUTPUT); //13번 핀을 LED를 제어하기 위해 OUTPUT모드로 설정
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}

