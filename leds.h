#include <FastLED.h>

#define NUM_LEDS 6
#define LED_PIN 2
#define BRIGHTNESS 64

class Leds{
private:
    CRGB leds[NUM_LEDS];

public:

void setup() {
    FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(  BRIGHTNESS );
    setAll(CRGB::Green);
    delay(500);
    setAll(CRGB::Black);
}

void setAll(CRGB c){
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = c;
  }
  FastLED.show();
}

};