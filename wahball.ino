#include "accelerometer.h"
#include "expressionout.h"
#include "leds.h"
#include "pots.h"

#define MODE_SELECT_PIN 3
#define MODE_WAHBALL 1
#define MODE_OSCILLATOR 2
#define MODE_TESTER 3
#define NUM_MODES 3 //I hate this, but itll do for now
byte curMode;

byte expression_values[] = {0,0,0};
boolean DEBUG_MAP = false;
boolean DEBUG_POTS = false;

Accelerometer accel;
ExpressionOut expression;
Leds leds;
Pots pots;

void setup(void) {
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
  

  if(curMode == MODE_WAHBALL) {
    byte hue = map(accel.x(), -2000,2000,0, 255);
    leds.setAll(CHSV(hue,255,100));
    expression_values[0] = map(accel.x(), -2000,2000,0, 255);
    expression_values[1] = map(accel.y(), -2000,2000,0, 255);
    expression_values[2] = map(accel.z(), -2000,2000,0, 255);
    if(DEBUG_MAP == true) { printExpressionValues(); }  
    expression.update(expression_values);

  } else if(curMode == MODE_OSCILLATOR) {
    Serial.println("woo im oscillating!");
    delay(100);

   } else if(curMode == MODE_TESTER) {
     expression_values[0] = map(pots.potValues[0], 0,1024,0, 255);
     expression_values[1] = map(pots.potValues[1], 0,1024,0, 255);
     expression_values[2] = map(pots.potValues[2], 0,1024,0, 255);
     expression.update(expression_values);
     if(DEBUG_POTS == true) { pots.print(); delay(100); }  
  }


  
}

void printExpressionValues() {
    for(byte i=0; i<3; i++) {
      Serial.print("E");
      Serial.print(i); 
      Serial.print(": "); 
      Serial.print(expression_values[i]); 
      Serial.println("\t");
    } 
}

void advanceMode() {
    curMode++;
    if(curMode > NUM_MODES) {
        curMode = 1;
    }
    Serial.print("switching to mode ");Serial.println(curMode);
}
