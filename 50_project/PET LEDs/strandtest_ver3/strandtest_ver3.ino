#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN1 2
#define PIN2 3
#define PIN3 4
#define PIN4 5
#define PIN5 6
#define PIN6 7
#define PIN7 8
#define PIN8 9
#define PIN9 10
#define PIN10 11
#define PIN11 12


Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(6, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(6, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(6, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(6, PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(6, PIN5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(6, PIN6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(6, PIN7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(6, PIN8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(6, PIN9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip10 = Adafruit_NeoPixel(6, PIN10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip11 = Adafruit_NeoPixel(6, PIN11, NEO_GRB + NEO_KHZ800);


void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif


  strip1.begin(); strip1.show(); 
  strip2.begin(); strip2.show(); 
  strip3.begin(); strip3.show(); 
  strip4.begin(); strip4.show();
  strip5.begin(); strip5.show(); 
  strip6.begin(); strip6.show();
  strip7.begin(); strip7.show(); 
  strip8.begin(); strip8.show();
  strip9.begin(); strip9.show(); 
  strip10.begin(); strip10.show();
  strip11.begin(); strip11.show(); 
  //strip12.begin(); strip12.show();
}

void loop() {
  
  rainbow1(20);
  rainbow2(20);
  rainbow3(20);
  rainbow4(20);
  rainbow5(20);
  rainbow6(20);
  rainbow7(20);
  rainbow8(20);
  rainbow9(20);
  rainbow10(20);
  rainbow11(20);
  //rainbow12(20);


}

///////////////1


void rainbow(uint8_t wait1, Adafruit_NeoPixel stripTemp) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<stripTemp.numPixels(); i++) {
      stripTemp.setPixelColor(i, Wheel1(i+j, stripTemp) & 255));
    }
    stripTemp.show();
    delay(wait1);
  }
}


uint32_t Wheel(byte WheelPos, Adafruit_NeoPixel stripTemp) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return stripTemp.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return stripTemp.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return stripTemp.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


void rainbow1(uint8_t wait1) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel1((i+j) & 255));
    }
    strip1.show();
    delay(wait1);
  }
}


void rainbow1(uint8_t wait1) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel1((i+j) & 255));
    }
    strip1.show();
    delay(wait1);
  }
}

uint32_t Wheel1(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

///////////// 2
void rainbow2(uint8_t wait2) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip2.numPixels(); i++) {
      strip2.setPixelColor(i, Wheel2((i+j) & 255));
    }
    strip2.show();
    delay(wait2);
  }
}

uint32_t Wheel2(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip2.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip2.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip2.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

///////////// 3
void rainbow3(uint8_t wait3) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip3.numPixels(); i++) {
      strip3.setPixelColor(i, Wheel3((i+j) & 255));
    }
    strip3.show();
    delay(wait3);
  }
}

uint32_t Wheel3(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip3.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip3.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip3.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

//////////////////// 4
void rainbow4(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip4.numPixels(); i++) {
      strip4.setPixelColor(i, Wheel4((i+j) & 255));
    }
    strip4.show();
    delay(wait);
  }
}

uint32_t Wheel4(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip4.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip4.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip4.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


//////////////////// 5
void rainbow5(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip5.numPixels(); i++) {
      strip5.setPixelColor(i, Wheel5((i+j) & 255));
    }
    strip5.show();
    delay(wait);
  }
}

uint32_t Wheel5(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip5.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip5.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip5.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

//////////////////// 6
void rainbow6(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip6.numPixels(); i++) {
      strip6.setPixelColor(i, Wheel6((i+j) & 255));
    }
    strip6.show();
    delay(wait);
  }
}

uint32_t Wheel6(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip6.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip6.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip6.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

//////////////////// 7
void rainbow7(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip7.numPixels(); i++) {
      strip7.setPixelColor(i, Wheel7((i+j) & 255));
    }
    strip7.show();
    delay(wait);
  }
}

uint32_t Wheel7(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip7.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip7.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip7.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

//////////////////// 8
void rainbow8(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip8.numPixels(); i++) {
      strip8.setPixelColor(i, Wheel8((i+j) & 255));
    }
    strip8.show();
    delay(wait);
  }
}

uint32_t Wheel8(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip8.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip8.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip8.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

//////////////////// 9
void rainbow9(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip9.numPixels(); i++) {
      strip9.setPixelColor(i, Wheel9((i+j) & 255));
    }
    strip9.show();
    delay(wait);
  }
}

uint32_t Wheel9(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip9.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip9.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip9.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

//////////////////// 10
void rainbow10(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip10.numPixels(); i++) {
      strip10.setPixelColor(i, Wheel10((i+j) & 255));
    }
    strip10.show();
    delay(wait);
  }
}

uint32_t Wheel10(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip10.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip10.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip10.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

//////////////////// 11
void rainbow11(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip11.numPixels(); i++) {
      strip11.setPixelColor(i, Wheel11((i+j) & 255));
    }
    strip11.show();
    delay(wait);
  }
}

uint32_t Wheel11(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip11.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip11.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip11.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

//////////////////// 12
/*
void rainbow12(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip12.numPixels(); i++) {
      strip12.setPixelColor(i, Wheel12((i+j) & 255));
    }
    strip12.show();
    delay(wait);
  }
}

uint32_t Wheel12(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip12.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip12.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip12.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
*/
