#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <FastLED.h>


#include "accelerometer.h"
#include "expressionout.h"

#define NUM_LEDS 6
#define LED_PIN 2
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 64

byte expression_values[] = {0,0,0};



boolean DEBUG_MAP = false;

Accelerometer accel;
ExpressionOut expression;

void setup(void) {
  Serial.begin(115200);

  expression.setup();
  accel.setup();

  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  setStripColor(CRGB::Green);
  delay(500);
  setStripColor(CRGB::Black);
}

void loop() {

  accel.update();

  byte hue = map(accel.x(), -2000,2000,0, 255);
  byte saturation = map(accel.y(), -2000,2000,0, 255);
  setStripColor(CHSV(hue,255,100));
  
  expression_values[0] = map(accel.x(), -2000,2000,0, 255);
  expression_values[1] = map(accel.y(), -2000,2000,0, 255);
  expression_values[2] = map(accel.z(), -2000,2000,0, 255);

  if(DEBUG_MAP == true) {
    for(byte i=0; i<3; i++) {
      Serial.print(i); Serial.print(": "); Serial.print(expression_values[i]); Serial.println("\t");
    }
  }

  expression.update(expression_values);
}

void setStripColor(CRGB c){
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = c;
  }
  FastLED.show();
}


