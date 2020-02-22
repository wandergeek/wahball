#define NUM_POTS 6

class Pots{
private:
    byte potPins[NUM_POTS] = { A3,A6,A7,A0,A1,A2 };

public:
    short potValues[NUM_POTS];

    void setup() {
        for(int i=0; i<NUM_POTS; i++) {
            pinMode(potPins[i], INPUT);    
        }
    }

    void update() {
        for(int i=0; i<NUM_POTS; i++) {
            potValues[i] = analogRead(potPins[i]);    
        }
    }

    void print() {
        for(int i=0; i<NUM_POTS; i++) {
            Serial.print("A"); Serial.print(i); Serial.print(": "); Serial.print(potValues[i]); Serial.print(" "); 
        }
        Serial.println();
    }



};