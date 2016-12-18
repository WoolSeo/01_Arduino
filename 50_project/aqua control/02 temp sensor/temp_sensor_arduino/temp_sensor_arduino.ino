#include <AdafruitSensor.h>
#include <DHT.h>
#include <OneWire.h> 

#define DHTPIN 2
#define DHTTYPE DHT22

int DS18S20_Pin1 = 3; //DS18S20 Signal pin on digital 2
int DS18S20_Pin2 = 4;

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
OneWire ds1(DS18S20_Pin1);
OneWire ds2(DS18S20_Pin2);


void setup() {
  Serial.begin(9600);
  dht.begin();
  
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
          digitalWrite(ledpin1, HIGH);          
          //digitalWrite(ledpin1, HIGH);
          ledstate1 = 1;
        }
        else if( led == 1 && button == OFF ) {
          digitalWrite(ledpin1, LOW);
          ledstate1 = 0;
        }

        if( led == 2 && button == ON ) {
          
          digitalWrite(ledpin2, HIGH);
          ledstate2 = 1;
        }
        else if( led == 2 && button == OFF ) {
          digitalWrite(ledpin2, LOW);
          ledstate2 = 0;
        }
      }
    }
    delay(50);

  }
  send_state();
}

void send_state() {
    temp1 = getTemp1();
    temp2 = getTemp2();

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
    Serial.print(",");
    Serial.println();
}

float getTemp1(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds1.search(addr)) {
      //no more sensors on chain, reset search
      ds1.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }
  ds1.reset();
  ds1.select(addr);
  ds1.write(0x44,1); // start conversion, with parasite power on at the end
  delay(750); // Wait for temperature conversion to complete
  byte present = ds1.reset();
  ds1.select(addr);    
  ds1.write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds1.read();
  }
  ds1.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;
}

float getTemp2(){
  //returns the temperature from one DS18S20 in DEG Celsius
  byte data[12];
  byte addr[8];

  if ( !ds2.search(addr)) {
      //no more sensors on chain, reset search
      ds2.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }
  ds2.reset();
  ds2.select(addr);
  ds2.write(0x44,1); // start conversion, with parasite power on at the end  

  delay(750); // Wait for temperature conversion to complete

  byte present = ds2.reset();

  ds2.select(addr);    
  ds2.write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds2.read();
  }
  
  ds2.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];
  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
}
