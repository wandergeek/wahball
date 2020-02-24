#define VERTICAL_SHIFT 128
#define NUM_OSCILLATORS 3
#define MAX_FREQUENCY 20
#define MIN_AMPLITUDE 5
#define MAX_AMPLITUDE 128
#define MIN_FREQUENCY 1
float TIME_SCALE_FACTOR = 5000.0;

class Oscillator {

private:
    byte frequency;
    byte amplitude;

public:

  Oscillator() {
    setFrequency(1);
  }

  void setFrequency(byte f) {
      frequency = f;
  }

  void setAmplitude(byte a) {
      amplitude = a;
  }

  byte getVal() {
       return amplitude * (sin( millis()/TIME_SCALE_FACTOR * frequency * PI  ) + 1);
  }

  void print() {
    Serial.print("frequency: "); Serial.print(frequency);
    Serial.print(" amplitude: "); Serial.println(amplitude);
    Serial.print(" value: "); Serial.println(getVal());
  }


};