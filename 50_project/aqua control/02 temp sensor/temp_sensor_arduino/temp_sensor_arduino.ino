#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

const char HEADER = 'H';
const int TOTAL_BYTES = 6;

const char LED_TAG = 'L';
const int ON = 1;
const int OFF = 0;

const int ledpin1 = 6;
const int ledpin2 = 7;

int ledstate1 = 0;
int ledstate2 = 0;

int temp0;
int humi0;

int temp1;
int temp2;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(13, OUTPUT);
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);

  digitalWrite(ledpin1, LOW);
  digitalWrite(ledpin2, LOW);
}

void loop() {
  
  humi0 = dht.readHumidity();
  temp0 = dht.readTemperature();
  
  if(Serial.available() >= TOTAL_BYTES){
    if(Serial.read() == HEADER) {
      char tag = Serial.read();
      
      if(tag == LED_TAG) {
        
        int led = Serial.read();
        led = led + Serial.read();
        int button = Serial.read();
        button = button + Serial.read();
        
        if( led == 1 && button == ON ) {
          digitalWrite(13, HIGH);
          delay(1000);
          digitalWrite(13, LOW);
          
          //digitalWrite(ledpin1, HIGH);
          ledstate1 = 1;
        }
        else if( led == 1 && button == OFF ) {
          
          //digitalWrite(ledpin1, LOW);
          ledstate1 = 0;
        }
        
        if( led == 2 && button == ON ) {
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13, LOW);
          delay(500);
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13, LOW);
          delay(500);
          
          //digitalWrite(ledpin2, HIGH);
          ledstate2 = 1;
        }
        else if( led == 2 && button == OFF ) {
          
          //digitalWrite(ledpin2, LOW);
          ledstate2 = 0;
        }
      }
    }
    delay(50);
    
  }
  send_state();
}

void send_state() {
    int temp0;
    int temp1;
    int temp2;
    temp0 = analogRead(A0);
    temp1 = analogRead(A1);
    temp2 = analogRead(A2);
    
    Serial.print(HEADER);
    Serial.print(",");
    Serial.print(ledstate1,DEC);
    Serial.print(",");
    Serial.print(ledstate2,DEC);
    Serial.print(",");
    Serial.print(temp0,DEC);
    Serial.print(",");
    Serial.print(temp1,DEC);
    Serial.print(",");
    Serial.print(temp2,DEC);
    Serial.print(",");
    Serial.print(humi0,DEC);
    Serial.println();
}

