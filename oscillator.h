#define VERTICAL_SHIFT 128
#define NUM_OSCILLATORS 3
#define MIN_FREQUENCY 0.1
#define MAX_FREQUENCY 20
#define MIN_AMPLITUDE 1
#define MAX_AMPLITUDE 255

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
      return amplitude*sin(frequency*(millis()/1000)) + VERTICAL_SHIFT;
  }


};