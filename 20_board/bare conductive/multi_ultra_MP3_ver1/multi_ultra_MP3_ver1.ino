
// compiler error handling
#include "Compiler_Errors.h"

// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

// mp3 includes
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>

// mp3 variables
SFEMP3Shield MP3player;
byte result;
int lastPlayed = 0;

// touch behaviour definitions
#define firstPin 0
#define lastPin 11

// sd card instantiation
SdFat sd;

// define LED_BUILTIN for older versions of Arduino
#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

const int trigPin1 = 2;
const int echoPin1 = 3;

const int trigPin2 = 4;
const int echoPin2 = 5;

const int trigPin3 = 6;
const int echoPin3 = 7;

const int trigPin4 = 8;
const int echoPin4 = 9;

void setup(){  
    Serial.begin(57600);
    
    pinMode(LED_BUILTIN, OUTPUT);
     
    //while (!Serial) ; {} //uncomment when using the serial monitor 
    Serial.println("Bare Conductive Touch MP3 player");
  
    if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  
    if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
    MPR121.setInterruptPin(MPR121_INT);
  
    MPR121.setTouchThreshold(40);
    MPR121.setReleaseThreshold(20);
  
    result = MP3player.begin();
    MP3player.setVolume(10,10);
   
    if(result != 0) {
      Serial.print("Error code: ");
      Serial.print(result);
      Serial.println(" when trying to start MP3 player");
     }
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT); 
    
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);

    pinMode(trigPin4, OUTPUT);
    pinMode(echoPin4, INPUT);
   
   
   //MP3player.playTrack(1); 
   MP3player.stopTrack();
   //MP3player.playTrack(0); 
}

void loop(){
  //readTouchInputs();
  
    int distance1;
    int distance2;
    int distance3;
    int distance4;
    
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    distance1 = pulseIn(echoPin1, HIGH) / 58;
    delay(10);

    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    distance2 = pulseIn(echoPin2, HIGH) / 58;
    delay(10);

    digitalWrite(trigPin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin3, LOW);
    distance3 = pulseIn(echoPin3, HIGH) / 58;
    delay(10);

    digitalWrite(trigPin4, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin4, LOW);
    distance4 = pulseIn(echoPin4, HIGH) / 58;
    delay(10);
    
    if (distance > 200 || distance < 0)
        Serial.println("out of range");
    else {
        Serial.print(distance);
        Serial.println(" cm");
    }
    delay(1000);
    
}


void readTouchInputs(){
  if(MPR121.touchStatusChanged()){
    
    MPR121.updateTouchData();

    // only make an action if we have one or fewer pins touched
    // ignore multiple touches
    
    if(MPR121.getNumTouches()<=1){
      for (int i=0; i < 12; i++){  // Check which electrodes were pressed
        if(MPR121.isNewTouch(i)){
        
            //pin i was just touched
            Serial.print("pin ");
            Serial.print(i);
            Serial.println(" was just touched");
            digitalWrite(LED_BUILTIN, HIGH);
            
            if(i<=lastPin && i>=firstPin){
              if(MP3player.isPlaying()){
                if(lastPlayed==i){
                  // if we're already playing the requested track, stop it
                  MP3player.stopTrack();
                  Serial.print("stopping track ");
                  Serial.println(i-firstPin);
                } else {
                  // if we're already playing a different track, stop that 
                  // one and play the newly requested one
                  MP3player.stopTrack();
                  MP3player.playTrack(i-firstPin);
                  Serial.print("playing track ");
                  Serial.println(i-firstPin);
                  
                  // don't forget to update lastPlayed - without it we don't
                  // have a history
                  lastPlayed = i;
                }
              } else {
                // if we're playing nothing, play the requested track 
                // and update lastplayed
                MP3player.playTrack(i-firstPin);
                Serial.print("playing track ");
                Serial.println(i-firstPin);
                lastPlayed = i;
              }
            }     
        }else{
          if(MPR121.isNewRelease(i)){
            Serial.print("pin ");
            Serial.print(i);
            Serial.println(" is no longer being touched");
            digitalWrite(LED_BUILTIN, LOW);
         } 
        }
      }
    }
  }
}
