int trimPotPin = A0;

const int numReadings = 20;

int trimPotRawVal[numReadings];

int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int trimPotMin = 679;
int trimPotMax = 0;
int mappedVal = 0;

int constrainMaxVal = 700; // 700 for 3.3v and 1023 for 5v vcc

const int calibIndicationPin = 13;



#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 4); // RX, TX

void setup() {

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    trimPotRawVal[thisReading] = 0;
  }

  // calibrate the sensor during the first five seconds
  calibrateSensor();

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //Serial.begin(9600);
  mySerial.begin(9600);
}

int prevVal = 0;

void loop() {
  doAverage(trimPotPin);
  mappedVal = map(average, trimPotMin, trimPotMax, 0, 255);
  //Send data only if the values have changed. 
  if (mappedVal != prevVal) {
  mySerial.println(127);
  }
  prevVal = mappedVal;
  delay(500);
}

void doAverage(int sensorPin) {
  // subtract the last reading:
  total = total - trimPotRawVal[readIndex];
  // read from the sensor:
  trimPotRawVal[readIndex] = constrain(analogRead(sensorPin), 0, 700);
  // add the reading to the total:
  total = total + trimPotRawVal[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;
  delay(5);
}

void calibrateSensor() {
  pinMode(calibIndicationPin, OUTPUT);
  digitalWrite(calibIndicationPin, HIGH);

  while (millis() < 10000) {
    doAverage(trimPotPin); // this will return average sensor result
    //here we'll use that for calibration

    // record the maximum sensor value
    if (average > trimPotMax) {
      trimPotMax = average;
    }

    // record the minimum sensor value
    if (average < trimPotMin) {
      trimPotMin = average;
    }
  }
  // signal the end of the calibration period
  digitalWrite(calibIndicationPin, LOW);
}
