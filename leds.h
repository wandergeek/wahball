#include <FastLED.h>

#define NUM_TOTAL_LEDS 9
#define LED_PIN 2
#define BRIGHTNESS 64
#define NUM_INDICATOR_LEDS 3
#define NUM_BALL_LEDS 3

class Leds
{
private:
  CRGB currentRGBIndicatorColor;
  CHSV currentHSVIndicatorColor;
  CRGB leds[NUM_TOTAL_LEDS];

public:
  void setup() {
    FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_TOTAL_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    setAll(CRGB::Green);
    delay(500);
    setAll(CRGB::Black);
    setIndicatorsColor(CRGB::Red);
  }

  void setAll(CRGB c) {
    for (int i = 0; i < NUM_TOTAL_LEDS; i++)
    {
      leds[i] = c;
    }
    FastLED.show();
  }

  void setIndicatorsBrightness(byte vals[]) {
    for(int i=0; i<NUM_INDICATOR_LEDS; i++) {
      CHSV c = currentHSVIndicatorColor;
      c.val = vals[i];
      leds[i] = c;
    }
     FastLED.show();
  }

  void setIndicatorsColor(CRGB c) {
    currentRGBIndicatorColor = c;
    currentHSVIndicatorColor = rgb2hsv_approximate(c);
  }
};