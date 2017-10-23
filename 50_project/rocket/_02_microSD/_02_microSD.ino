#include <SD.h>
const int chipSelect = 4;

void setup()
{
   Serial.begin(9600);
   Serial.print("Initializing SD card...");

   pinMode(11, OUTPUT);
   if (!SD.begin(chipSelect)) {
     Serial.println("Card failed, or not present");
     return;
   }
   Serial.println("card initialized.");
}
void loop() {
    String dataString = "";

    dataString += String(millis());
    dataString += ",";
    

    int sensor = analogRead(A0);
    dataString += String(sensor);

    File dataFile = SD.open("datalog.txt", FILE_WRITE);
   
    if (dataFile) {
       dataFile.println(dataString);
       dataFile.close();
       Serial.println(dataString);
    }
    else {
      Serial.println("error opening datalog.txt");
    }
    
    delay(1000);
}
