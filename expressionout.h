#include <SPI.h>

#define NUM_EXP_OUT 3

class ExpressionOut {

private:
    byte EXP_OUT_PINS[NUM_EXP_OUT] = {10,9,8};
    byte address = 0x00;

public:
    
    void setup() {
        SPI.begin();
        for(byte i=0; i<NUM_EXP_OUT; i++) {
            pinMode(EXP_OUT_PINS[i], OUTPUT);
        }
    }

    void update(byte value,byte id) {
        digitalPotWrite(value, EXP_OUT_PINS[id]);
    }

    void update(byte values[]) {
        for(int i=0; i<NUM_EXP_OUT; i++) {
            update(values[i], i);
        }
    }

    void digitalPotWrite(byte value, int pin) {
        digitalWrite(pin, LOW);
        SPI.transfer(address);
        SPI.transfer(value);
        digitalWrite(pin, HIGH);
    }

};