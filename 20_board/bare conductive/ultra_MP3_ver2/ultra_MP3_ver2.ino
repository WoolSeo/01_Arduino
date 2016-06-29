
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

const int trigPin1 = 10;
const int echoPin1 = 9;
const int trigPin2 = 8;
const int echoPin2 = 7;

boolean bs1 = LOW;
boolean bs2 = LOW;

boolean br1;
boolean br2;



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

   //pinMode(trigPin2, OUTPUT);
   //pinMode(echoPin2, INPUT);
   
   
   //MP3player.playTrack(1); 
   MP3player.stopTrack();
   //MP3player.playTrack(0); 
}

void loop(){
  //readTouchInputs();
  
    int duration1, distance1;
    
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(50);
    digitalWrite(trigPin1, LOW);
    
    duration1 = pulseIn(echoPin1, HIGH);
    
    distance1 = duration1 / 58;

    Serial.print(distance1);
    Serial.print(" cm, ");

/*
    int duration2, distance2;
    
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    
    duration2 = pulseIn(echoPin2, HIGH);
    
    distance2 = duration2 / 58;

    Serial.print(distance2);
    Serial.println(" cm, ");

*/
    /*
    if ( distance1 > 5 && distance1 < 10 ) {
      br1 = HIGH;
    }
    else
      br1 = LOW;

    if ( distance2 > 5 && distance2 < 10 ) {
      br2 = HIGH;
    }
    else
      br2 = LOW;  

    if( !bs1 && !br1 ){
      MP3player.playTrack(1); 
      MP3player.stopTrack();
      bs1 = HIGH;
    }
    else if( bs1 && br1 ) {
      MP3player.stopTrack();
      bs1 = LOW;
    }

    if( !bs2 && !br2 ){
      MP3player.playTrack(2); 
      MP3player.stopTrack();
      bs2 = HIGH;
    }
    else if( bs2 && br2 ) {
      MP3player.stopTrack();
      bs2 = LOW;
    }
    */
    
    /*if (distance > 20 || distance < 5)
        Serial.println("out of range");
    else if( distance < 10 ){
      MP3player.playTrack(2); 
      MP3player.stopTrack();
    }
    else if( distance < 20 ){
      MP3player.playTrack(1); 
      MP3player.stopTrack();
    }
    else {
      MP3player.stopTrack();
        
    }*/
    delay(500);
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
