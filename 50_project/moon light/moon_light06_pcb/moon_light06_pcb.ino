//control led bright using potentiometer
//chage led color using push button

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define led_PIN 7
#define SW1Pin 5
#define SW2Pin 3

int poten_PIN = A0; 

int b_value = 0; //brightness
int led_bright = 0;
int c_mode = 0; //color mode
int on_mode = 1;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16,  led_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  Serial.begin(9600);
  
  pinMode(SW1Pin, INPUT_PULLUP);
  pinMode(SW2Pin, INPUT_PULLUP);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  
  

  int SW1Val = digitalRead(SW1Pin);
  int SW2Val = digitalRead(SW2Pin);

  //turnoff LEDs
  if (SW2Val == HIGH) {
    on_mode = on_mode * (-1);
    Serial.println("change");
    delay(1000);
  }
  
  
  // pull-up pushbutton
  // HIGH when it's open, and LOW when it's pressed
  if (SW1Val == HIGH) {
    c_mode = c_mode + 1;
    if(c_mode == 5) {
      c_mode = 0;
    }
    delay(500);
  } 

  Serial.println(led_bright);
  
  if( on_mode == 1) {
    //read potentialmeter value and convert proper led brightness
    int b_temp;
    //read A0
    b_temp = (int)(analogRead(poten_PIN)/100);
    //b_temp = 1000;
    Serial.println(b_temp);
  
   if(b_value != b_temp){
     b_value = b_temp;
    }

    led_bright = map(b_value, 0, 12, 0, 255);
    
    //white
    if( c_mode == 0 ) {
      colorWipe(strip.Color(led_bright, led_bright, led_bright), 5);
    }
    //yellow
    else if( c_mode == 1 ) {
      colorWipe(strip.Color(led_bright, led_bright, 0), 5);
    }
    //red
    else if( c_mode == 2 ) {
      colorWipe(strip.Color(led_bright, 0, 0), 5);
    }
    else if( c_mode == 3 ) {
      rainbow(100);
    }
    else if( c_mode == 4 ) {
      theaterChaseRainbow(50);
    }
  }
  else {
    while( on_mode == (-1) ){
      
      
      if( c_mode == 0 ) {
        colorWipe(strip.Color(led_bright, led_bright, led_bright), 5);
      }
      //yellow
      else if( c_mode == 1 ) {
        colorWipe(strip.Color(led_bright, led_bright, 0), 5);
      }
      //red
      else if( c_mode == 2 ) {
        colorWipe(strip.Color(led_bright, 0, 0), 5);
      }
      else if( c_mode == 3 ) {
        rainbow(100);
      }
      else if( c_mode == 4 ) {
        theaterChaseRainbow(50);
      }

      if( led_bright <= 0 ) {
        led_bright = 0;
        break;
      }
      else {
        led_bright = led_bright - 1;
      }
      delay(6000);
      
    }
  }
  
  
  
  
  
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 127), 50); // Blue

  //rainbow(20);
  //rainbowCycle(20);
  //theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
