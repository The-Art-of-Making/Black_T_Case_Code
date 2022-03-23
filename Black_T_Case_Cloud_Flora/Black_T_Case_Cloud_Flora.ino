
// LightShow
//
// Cycles through 5 different functions that demonstrate various illumination effects with NeoPixels:
// colorWipe, theaterChase, rainbow, rainbowCycle, theaterChaseRainbow
//
// Last update: v2.1 11-6-2020 J Samosky  Added comments.
// Updated      v2   10-24-2019 J Samosky



#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, 6, NEO_GRB + NEO_KHZ800); // Declares a NeoPixel strip of length 2 on Flora Pin 6

Adafruit_NeoPixel strip_onboard = Adafruit_NeoPixel(1, 8, NEO_GRB + NEO_KHZ800);  // Declares a NeoPixel strip of length 1 on
                                                                                  // Flora "Pin 8" --> This is the built-in NeoPixel
int showType = 0;

void setup() {
  strip_onboard.begin(); // The begin() function prepares the data pin associated with the NeoPixel
                         // object for serial Neopixel output. The "NeoPixel object" here is strip_onboard, and
                         // the associated data pin is Flora Pin 8, the built-in NeoPixel, as set in the
                         // strip_onboard = Adafruit_NeoPixel(1, 8, NEO_GRB + NEO_KHZ800) declaration above.
  strip_onboard.show();  // Initialize the onboard neopixel to 'off'. If show() is called before
                         // a setPixelColor command has been called, it sets R = G = B = 0
  
  strip.begin(); // Sets up the data pin associated with the external 2-neopixel strip for NeoPixel output.
                 // Here, that's Flora Pin 6, as set in the strip = Adafruit_NeoPixel(2, 6, NEO_GRB + NEO_KHZ800)
                 // declaration above.
  strip.setBrightness(255);  // Sets the maximum brightness. Range is 0 to 255. Call function once in setup().
  strip.show(); // Initialize the two external neopixels to 'off'

}

void loop() {   // Loop through several different functions that create different NeoPixel color patterns.

      theaterChaseRainbow(50);
}

// colorWipe: Fills the NeoPixels one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// rainbow: Generates various colors.
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

// rainbowCycle: Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*3; j++) { // 3 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//theaterChase: Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<3; j++) {  //do 3 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//theaterChaseRainbow: Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 128; j++) {     // Cycle through the first 128 colors in the wheel. (Make the loop limit for j 256 to cycle through all colors.)
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
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
