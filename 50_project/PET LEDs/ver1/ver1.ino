#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define LEDPIN1 3
#define LEDPIN2 4
#define LEDPIN3 5
#define LEDPIN4 6
#define LEDPIN5 7

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(1, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(1, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(1, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(1, PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(1, PIN5, NEO_GRB + NEO_KHZ800);



// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  strip1.begin();
  strip1.show();
  
  strip2.begin();
  strip2.show();
  
  strip3.begin();
  strip3.show();

  strip4.begin();
  strip4.show();
  
  strip5.begin();
  strip5.show();
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe1(strip1.Color(255, 0, 0), 50); // Red
  colorWipe1(strip1.Color(0, 255, 0), 50); // Green
  colorWipe1(strip1.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  theaterChase1(strip1.Color(127, 127, 127), 50); // White
  theaterChase1(strip1.Color(127,   0,   0), 50); // Red
  theaterChase1(strip1.Color(  0,   0, 127), 50); // Blue

  rainbow1(20);
  rainbowCycle1(20);
  theaterChaseRainbow1(50);
}

///////////////////////////////////////////////////////////
// 스트립1 함수들 
///////////////////////////////////////////////////////////

// Fill the dots one after the other with a color
void colorWipe1(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, c);
      strip1.show();
      delay(wait);
  }
}

void rainbow1(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel1((i+j) & 255));
    }
    strip1.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle1(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel1(((i * 256 / strip1.numPixels()) + j) & 255));
    }
    strip1.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase1(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip1.show();
     
      delay(wait);
     
      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow1(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip1.numPixels(); i=i+3) {
          strip1.setPixelColor(i+q, Wheel1( (i+j) % 255));    //turn every third pixel on
        }
        strip1.show();
       
        delay(wait);
       
        for (int i=0; i < strip1.numPixels(); i=i+3) {
          strip1.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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


///////////////////////////////////////////////////////////
// 스트립2 함수들 
///////////////////////////////////////////////////////////

// Fill the dots one after the other with a color
void colorWipe2(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip2.numPixels(); i++) {
      strip2.setPixelColor(i, c);
      strip2.show();
      delay(wait);
  }
}

void rainbow2(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip2.numPixels(); i++) {
      strip2.setPixelColor(i, Wheel2((i+j) & 255));
    }
    strip2.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle2(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip2.numPixels(); i++) {
      strip2.setPixelColor(i, Wheel2(((i * 256 / strip2.numPixels()) + j) & 255));
    }
    strip2.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase2(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip2.numPixels(); i=i+3) {
        strip2.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip2.show();
     
      delay(wait);
     
      for (int i=0; i < strip2.numPixels(); i=i+3) {
        strip2.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow2(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip2.numPixels(); i=i+3) {
          strip2.setPixelColor(i+q, Wheel2( (i+j) % 255));    //turn every third pixel on
        }
        strip2.show();
       
        delay(wait);
       
        for (int i=0; i < strip2.numPixels(); i=i+3) {
          strip2.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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



///////////////////////////////////////////////////////////
// 스트립3 함수들 
///////////////////////////////////////////////////////////

// Fill the dots one after the other with a color
void colorWipe3(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip3.numPixels(); i++) {
      strip3.setPixelColor(i, c);
      strip3.show();
      delay(wait);
  }
}

void rainbow3(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip3.numPixels(); i++) {
      strip3.setPixelColor(i, Wheel3((i+j) & 255));
    }
    strip3.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle3(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip3.numPixels(); i++) {
      strip3.setPixelColor(i, Wheel3(((i * 256 / strip3.numPixels()) + j) & 255));
    }
    strip3.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase3(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip3.numPixels(); i=i+3) {
        strip3.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip3.show();
     
      delay(wait);
     
      for (int i=0; i < strip3.numPixels(); i=i+3) {
        strip3.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow3(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip3.numPixels(); i=i+3) {
          strip3.setPixelColor(i+q, Wheel3( (i+j) % 255));    //turn every third pixel on
        }
        strip3.show();
       
        delay(wait);
       
        for (int i=0; i < strip3.numPixels(); i=i+3) {
          strip3.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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



///////////////////////////////////////////////////////////
// 스트립4 함수들 
///////////////////////////////////////////////////////////

// Fill the dots one after the other with a color
void colorWipe4(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip4.numPixels(); i++) {
      strip4.setPixelColor(i, c);
      strip4.show();
      delay(wait);
  }
}

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

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle4(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip4.numPixels(); i++) {
      strip4.setPixelColor(i, Wheel4(((i * 256 / strip4.numPixels()) + j) & 255));
    }
    strip4.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase4(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip4.numPixels(); i=i+3) {
        strip4.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip4.show();
     
      delay(wait);
     
      for (int i=0; i < strip4.numPixels(); i=i+3) {
        strip4.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow4(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip4.numPixels(); i=i+3) {
          strip4.setPixelColor(i+q, Wheel4( (i+j) % 255));    //turn every third pixel on
        }
        strip4.show();
       
        delay(wait);
       
        for (int i=0; i < strip4.numPixels(); i=i+3) {
          strip4.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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



///////////////////////////////////////////////////////////
// 스트립5 함수들 
///////////////////////////////////////////////////////////

// Fill the dots one after the other with a color
void colorWipe5(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip5.numPixels(); i++) {
      strip5.setPixelColor(i, c);
      strip5.show();
      delay(wait);
  }
}

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

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle5(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip5.numPixels(); i++) {
      strip5.setPixelColor(i, Wheel5(((i * 256 / strip5.numPixels()) + j) & 255));
    }
    strip5.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase5(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip5.numPixels(); i=i+3) {
        strip5.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip5.show();
     
      delay(wait);
     
      for (int i=0; i < strip5.numPixels(); i=i+3) {
        strip5.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow5(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip5.numPixels(); i=i+3) {
          strip5.setPixelColor(i+q, Wheel5( (i+j) % 255));    //turn every third pixel on
        }
        strip5.show();
       
        delay(wait);
       
        for (int i=0; i < strip5.numPixels(); i=i+3) {
          strip5.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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



