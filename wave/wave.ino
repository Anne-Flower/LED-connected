#include <FastLED.h>

#define NUM_LEDS 5
#define DATA_PIN 2
#define BRIGHTNESS 55

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(gHue + i * 30, 255, 255);
    FastLED.show();
    delay(150);
    leds[i] = CRGB::Black;
  }
  gHue += 10;
}
