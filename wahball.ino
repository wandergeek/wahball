#include "accelerometer.h"
#include "expressionout.h"
#include "leds.h"
#include "pots.h"
#include "oscillator.h"

#define MODE_SELECT_PIN 3
#define MODE_WAHBALL 1
#define MODE_OSCILLATOR 2
#define MODE_TESTER 3
#define NUM_MODES 3 //I hate this, but itll do for now

byte curMode;
byte exp_vals[] = {0, 0, 0};
boolean DEBUG_MAP = false;
boolean DEBUG_POTS = false;

Accelerometer accel;
ExpressionOut expression;
Leds leds;
Pots pots;
Oscillator osc[NUM_OSCILLATORS];

void setup() {
  Serial.begin(115200);
  expression.setup();
  accel.setup();
  leds.setup();
  pots.setup();

  pinMode(MODE_SELECT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(MODE_SELECT_PIN), advanceMode, CHANGE);
  curMode = MODE_WAHBALL;
}

void loop() {
  accel.update();
  pots.update();

  if (curMode == MODE_WAHBALL) {
    byte hue = map(accel.x(), -2000, 2000, 0, 255);
    leds.setAll(CHSV(hue, 255, 100));
    exp_vals[0] = map(accel.x(), -2000, 2000, 0, 255);
    exp_vals[1] = map(accel.y(), -2000, 2000, 0, 255);
    exp_vals[2] = map(accel.z(), -2000, 2000, 0, 255);
    if (DEBUG_MAP == true)
    {
      printExpressionValues();
    }
    expression.update(exp_vals);


  } else if (curMode == MODE_OSCILLATOR) {
    for(int i=0; i<NUM_OSCILLATORS; i++) {
      osc[i].setFrequency(map(pots.pot_vals[i], 0, 1024, MIN_FREQUENCY, MAX_FREQUENCY));
      osc[i].setAmplitude(map(pots.pot_vals[i+3], 0, 1024, MIN_AMPLITUDE, MAX_AMPLITUDE));
      exp_vals[i] = osc[i].getVal();
    }
    expression.update(exp_vals);
    leds.setIndicatorsBrightness(exp_vals);


  } else if (curMode == MODE_TESTER) {
    exp_vals[0] = map(pots.pot_vals[0], 0, 1024, 0, 255);
    exp_vals[1] = map(pots.pot_vals[1], 0, 1024, 0, 255);
    exp_vals[2] = map(pots.pot_vals[2], 0, 1024, 0, 255);
    expression.update(exp_vals);
    leds.setIndicatorsBrightness(exp_vals);
    if (DEBUG_POTS == true) {
      pots.print();
      delay(100);
    }
  }
}

void printExpressionValues() {
  for (byte i = 0; i < 3; i++) {
    Serial.print("E");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(exp_vals[i]);
    Serial.println("\t");
  }
}

void advanceMode() {
  curMode++;
  if (curMode > NUM_MODES)
  {
    curMode = 1;
  }
  Serial.print("switching to mode ");
  Serial.println(curMode);
}


