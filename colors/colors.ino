#include <FastLED.h>

#define NUM_LEDS 5
#define DATA_PIN 2
#define BRIGHTNESS 55

CRGB leds[NUM_LEDS];

void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(  BRIGHTNESS );
}

void loop() { 

  leds[0] = CRGB(255,0,0);
  leds[1] = CRGB(0,255,0);
  leds[2] = CRGB(0,0,255);
  leds[3] = CRGB(219,35,232);
  leds[4] = CRGB(245,245,15);


  FastLED.show();
}