
// LightShow
//
// Cycles through 5 different functions that demonstrate various illumination effects with NeoPixels:
// colorWipe, theaterChase, rainbow, rainbowCycle, theaterChaseRainbow
//
// Last update: v2.1 11-6-2020 J Samosky  Added comments.
// Updated      v2   10-24-2019 J Samosky



#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(79, 6, NEO_GRB + NEO_KHZ800); 

int maxLightLen = 30;

void setup() {

  strip.begin(); // Sets up the data pin associated with the external 2-neopixel strip for NeoPixel output.
                 // Here, that's Flora Pin 6, as set in the strip = Adafruit_NeoPixel(2, 6, NEO_GRB + NEO_KHZ800)
                 // declaration above.
  strip.setBrightness(255);  // Sets the maximum brightness. Range is 0 to 255. Call function once in setup().
  strip.show(); // Initialize the two external neopixels to 'off'

}


void loop() {
  for (uint16_t i=0; i<=4; i++) {
    rainbowchaseComplex();
  }
  //burst(10);
}

static void fadeOut() {
  for (uint16_t i=255; i>=0; i--) {
    strip.setBrightness(i);
    strip.show();
    delay(5);
  }
}

static void fadeIn() {
  for (uint16_t i=0; i<=255; i++) {
    strip.setBrightness(i);
    strip.show();
    delay(5);
  }
}

static void burst(uint8_t wait) {
  uint16_t pixelcolor = 0;
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    uint16_t j = 0;
    if (i%2 == 0) {
      j = random(0, 255);
      pixelcolor = Wheel((i+j) & 255);
    }
    else {
      pixelcolor = 0;
    }
    j = random(0, 255);
    strip.setPixelColor(i, pixelcolor);
  }
  strip.show();
  fadeOut();
  fadeIn();
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    uint16_t j = 0;
    if (i%2 != 0) {
      j = random(0, 255);
      pixelcolor = Wheel((i+j) & 255);
    }
    else {
      pixelcolor = 0;
    }
    strip.setPixelColor(i, pixelcolor);
  }
  strip.show();
  fadeOut();
  fadeIn();
}


static void rainbowchase() {
  uint16_t j = 0;
  for(uint16_t i=0; i<strip.numPixels()+10; i++) {
      j = random(0, 255);
      strip.setPixelColor(i, Wheel((i+j) & 255));
      strip.setPixelColor(i-10, 0); // Erase pixel a few steps back
      
      strip.show();
      delay(25);
  }
}

static void rainbowchaseComplex() {
  uint16_t j = 0;
  uint16_t len1 = 0;
  uint16_t mid12 = 10;
  uint16_t len2 = 0;
  uint16_t mid23 = 20;
  uint16_t len3 = 0;
  uint16_t streamlen = 0;
   uint8_t wait = 0;

  for (uint16_t numStreaks=0; numStreaks<4; numStreaks++) {
   
    wait = random(5, 30);              //Speed Of Current Run
    len1 = random(0,maxLightLen/2);      //Length of first streak
    len2 = random(0,maxLightLen/2);      //Length of second streak
    len3 = maxLightLen - len1 - len2;  //Length of third streak

    if (len3 <= 0) {
      len1 = 5;
      len2 = 5;
      len3 = 5;
    }
    
    if (len1 < len2) {
      uint16_t lenhold = len1;
      len1 = len2;
      len2 = lenhold;
    }
    
    if (len1 < len3) {
      uint16_t lenhold = len1;
      len1 = len3;
      len3 = lenhold;
    }
    
    streamlen = len1 + mid12 + len2  + mid23 + len3;

    
    for(uint16_t i=0; i<strip.numPixels()+streamlen; i++) {
      
      j = random(0, 255);

      if (i < strip.numPixels()+len1) {
          strip.setPixelColor(i, Wheel((i+j) & 255));
          strip.setPixelColor(i-len1, 0); // Erase pixel a few steps back
      }

      if (i < strip.numPixels()+len1+mid12+len2) {
      strip.setPixelColor(i-len1-mid12, Wheel((i+j) & 255));
      strip.setPixelColor(i-len1-mid12-len2, 0); // Erase pixel a few steps back
      }

      
      if (i < strip.numPixels()+len1+len2+len3+10+20) {
      strip.setPixelColor(i-len1-mid12-len2-mid23, Wheel((i+j) & 255));
      strip.setPixelColor(i-len1-mid12-len2-mid23-len3, 0); // Erase pixel a few steps back
      }

      strip.show();
      
      delay(wait);
    }
    
  }
}


// rainbow: Generates various colors.
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels()+10; i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
      strip.setPixelColor(i-10, 0); // Erase pixel a few steps back
    }
    strip.show();
    delay(wait);
  }
}

// rainbowCycle: Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  
  for(j=0; j<256*3; j++) { // 3 cycles of all colors on wheel
    for(i=0; i< strip.numPixels()+10; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      strip.setPixelColor(i-10, 0); // Erase pixel a few steps back
    }
    strip.show();
    delay(wait);
  }
}

// Wheel: returns one of 256 colors on a spectrum from r to g to b.
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
