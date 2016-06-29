#include <Servo.h>

Servo myServo;

int angle = 0;
int count = 0;

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
  myServo.write(0);
  delay(2000);
  Serial.begin(9600);
  Serial.println("start position");

}

void loop() {
  
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(A0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
  // put your main code here, to run repeatedly:
  
  
  
  //int micVal;
  //int sum = 0;
  /*for(int i = 0; i <50; i++)
  {
    data = analogRead(A0);
    sum = sum + data;
    delay(10);
  }
  */
 
 
  //micVal = analogRead(A0);
  //micVal = constrain(abs(micVal - 512)-25,0,512);
  Serial.println(volts);
  if(volts > 3.24)
  {
    angle = angle + 2;
    myServo.write(angle);
    count++;
    
    
    
  }
  //angle = map(data, 100, 800, 0, 179);
  if(angle > 175)
  {
    //tone(11, 800);
    delay(3000);
    noTone(11);
    myServo.write(0);
    delay(2000);
    angle = 0;
  }
  /* if( micVal != 0)
  {
    Serial.println(micVal);
  }*/
  delay(500);
}
