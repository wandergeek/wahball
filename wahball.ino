#include "accelerometer.h"
#include "expressionout.h"
#include "leds.h"
#include "pots.h"

byte expression_values[] = {0,0,0};
boolean DEBUG_MAP = false;

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
}

void loop() {
  accel.update();
  pots.update();

  byte hue = map(accel.x(), -2000,2000,0, 255);
  leds.setAll(CHSV(hue,255,100));
  
  expression_values[0] = map(accel.x(), -2000,2000,0, 255);
  expression_values[1] = map(accel.y(), -2000,2000,0, 255);
  expression_values[2] = map(accel.z(), -2000,2000,0, 255);

  if(DEBUG_MAP == true) {
    printExpressionValues();
  }

  expression.update(expression_values);
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


