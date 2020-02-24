#define NUM_POTS 6

class Pots {
private:
    byte potPins[NUM_POTS] = { A7,A6,A3,A2,A1,A0 };

public:
    short pot_vals[NUM_POTS];

    void setup() {
        for(int i=0; i<NUM_POTS; i++) {
            pinMode(potPins[i], INPUT);    
        }
    }

    void update() {
        for(int i=0; i<NUM_POTS; i++) {
            pot_vals[i] = 1024 - analogRead(potPins[i]);    
        }
    }

    void print() {
        for(int i=0; i<NUM_POTS; i++) {
            Serial.print("A"); Serial.print(i); Serial.print(": "); Serial.print(pot_vals[i]); Serial.print(" "); 
        }
        Serial.println();
    }



};