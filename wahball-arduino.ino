// Basic demo for accelerometer readings from Adafruit MSA301

#include <Wire.h>
#include <Adafruit_MSA301.h>
#include <Adafruit_Sensor.h>
#include <FastLED.h>
#include <SPI.h>

byte address = 0x00;
byte POT1 = 10;
byte POT2 = 9;
byte POT3 = 8;

#define NUM_LEDS 5
#define DATA_PIN 9
CRGB leds[NUM_LEDS];

Adafruit_MSA301 msa;

byte expression_a_val = 0;
byte expression_b_val = 128;
byte expression_c_val = 255;

void setup(void) {
  Serial.begin(115200);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(  64 );

  pinMode (POT1, OUTPUT);
  pinMode (POT2, OUTPUT);
  pinMode (POT3, OUTPUT);
  
  SPI.begin();

  return(0);
  
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MSA301 test!");
  
  // Try to initialize!
  if (! msa.begin()) {
    Serial.println("Failed to find MSA301 chip");
    while (1) { delay(10); }
  }
  Serial.println("MSA301 Found!");

  //msa.setDataRate(MSA301_DATARATE_31_25_HZ);
  Serial.print("Data rate set to: ");
  switch (msa.getDataRate()) {
    case MSA301_DATARATE_1_HZ: Serial.println("1 Hz"); break;
    case MSA301_DATARATE_1_95_HZ: Serial.println("1.95 Hz"); break;
    case MSA301_DATARATE_3_9_HZ: Serial.println("3.9 Hz"); break;
    case MSA301_DATARATE_7_81_HZ: Serial.println("7.81 Hz"); break;
    case MSA301_DATARATE_15_63_HZ: Serial.println("15.63 Hz"); break;
    case MSA301_DATARATE_31_25_HZ: Serial.println("31.25 Hz"); break;
    case MSA301_DATARATE_62_5_HZ: Serial.println("62.5 Hz"); break;
    case MSA301_DATARATE_125_HZ: Serial.println("125 Hz"); break;
    case MSA301_DATARATE_250_HZ: Serial.println("250 Hz"); break;
    case MSA301_DATARATE_500_HZ: Serial.println("500 Hz"); break;
    case MSA301_DATARATE_1000_HZ: Serial.println("1000 Hz"); break;
  }

  //msa.setPowerMode(MSA301_SUSPENDMODE);
  Serial.print("Power mode set to: ");
  switch (msa.getPowerMode()) {
    case MSA301_NORMALMODE: Serial.println("Normal"); break;
    case MSA301_LOWPOWERMODE: Serial.println("Low Power"); break;
    case MSA301_SUSPENDMODE: Serial.println("Suspend"); break;
  }

  //msa.setBandwidth(MSA301_BANDWIDTH_31_25_HZ);
  Serial.print("Bandwidth set to: ");
  switch (msa.getBandwidth()) {
    case MSA301_BANDWIDTH_1_95_HZ: Serial.println("1.95 Hz"); break;
    case MSA301_BANDWIDTH_3_9_HZ: Serial.println("3.9 Hz"); break;
    case MSA301_BANDWIDTH_7_81_HZ: Serial.println("7.81 Hz"); break;
    case MSA301_BANDWIDTH_15_63_HZ: Serial.println("15.63 Hz"); break;
    case MSA301_BANDWIDTH_31_25_HZ: Serial.println("31.25 Hz"); break;
    case MSA301_BANDWIDTH_62_5_HZ: Serial.println("62.5 Hz"); break;
    case MSA301_BANDWIDTH_125_HZ: Serial.println("125 Hz"); break;
    case MSA301_BANDWIDTH_250_HZ: Serial.println("250 Hz"); break;
    case MSA301_BANDWIDTH_500_HZ: Serial.println("500 Hz"); break;
  }

  //msa.setRange(MSA301_RANGE_2_G);
  Serial.print("Range set to: ");
  switch (msa.getRange()) {
    case MSA301_RANGE_2_G: Serial.println("+-2G"); break;
    case MSA301_RANGE_4_G: Serial.println("+-4G"); break;
    case MSA301_RANGE_8_G: Serial.println("+-8G"); break;
    case MSA301_RANGE_16_G: Serial.println("+-16G"); break;
  }

  //msa.setResolution(MSA301_RESOLUTION_14 );
  Serial.print("Resolution set to: ");
  switch (msa.getResolution()) {
    case MSA301_RESOLUTION_14: Serial.println("14 bits"); break;
    case MSA301_RESOLUTION_12: Serial.println("12 bits"); break;
    case MSA301_RESOLUTION_10: Serial.println("10 bits"); break;
    case MSA301_RESOLUTION_8: Serial.println("8 bits"); break;
  }

  setStripColor(CRGB::Green);
  delay(500);
  setStripColor(CRGB::Black);
}

void loop() {
  msa.read();      // get X Y and Z data at once
  // Then print out the raw data
  Serial.print("X:  "); Serial.print(msa.x); 
  Serial.print("  \tY:  "); Serial.print(msa.y); 
  Serial.print("  \tZ:  "); Serial.print(msa.z); 
  
  
  byte hue = map(msa.x, -2000,2000,0, 255);
  byte saturation = map(msa.y, -2000,2000,0, 255);
  setStripColor(CHSV(hue,255,100));
  
  // byte expression_a_val = map(msa.x, -2000,2000,0, 255);
  expression_a_val++;
  expression_b_val++;
  expression_c_val++;
//  byte expression_b_val = map(msa.y, -2000,2000,0, 255);

   digitalPotWrite(expression_a_val,POT1);
   digitalPotWrite(expression_b_val,POT2);
   digitalPotWrite(expression_c_val,POT3);

  Serial.print("  \tA out:  "); Serial.print(expression_a_val); 
//  Serial.print("  \tB out:  "); Serial.print(expression_b_val); 
  
  Serial.println();
  delay(100); 
}

void setStripColor(CRGB c){
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = c;
  }
  FastLED.show();
}

int digitalPotWrite(byte value, byte pin)
{
digitalWrite(pin, LOW);
SPI.transfer(address);
SPI.transfer(value);
digitalWrite(pin, HIGH);
}
