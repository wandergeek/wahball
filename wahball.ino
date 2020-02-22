#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <FastLED.h>
#include <SPI.h>

#include "accelerometer.h"

#define NUM_LEDS 6
#define LED_PIN 2
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 64

byte expression_a_val = 0;
byte expression_b_val = 0;
byte expression_c_val = 0;
byte EXP_A_PIN = 10;
byte EXP_B_PIN = 9;
byte EXP_C_PIN = 8;
byte address = 0x00;

boolean DEBUG_MAP = true;

Accelerometer accel;

void setup(void) {
  Serial.begin(115200);

  pinMode(EXP_A_PIN, OUTPUT);
  pinMode(EXP_B_PIN, OUTPUT);
  pinMode(EXP_C_PIN, OUTPUT);
  SPI.begin();
  
  while (!Serial) delay(10);
  
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
  
  expression_a_val = map(accel.x(), -2000,2000,0, 255);
  expression_b_val = map(accel.y(), -2000,2000,0, 255);
  expression_c_val = map(accel.z(), -2000,2000,0, 255);

  if(DEBUG_MAP == true) {
    Serial.print("A:"); Serial.print(expression_a_val);
    Serial.print("\tB:"); Serial.print(expression_b_val);
    Serial.print("\tC:"); Serial.println(expression_c_val);
    delay(100);
  }

  digitalPotWrite(expression_a_val,EXP_A_PIN);
  digitalPotWrite(expression_b_val,EXP_B_PIN);
  digitalPotWrite(expression_c_val,EXP_C_PIN);

}

void setStripColor(CRGB c){
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = c;
  }
  FastLED.show();
}

int digitalPotWrite(byte value, byte pin) {
  digitalWrite(pin, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(pin, HIGH);
}
