#include <Adafruit_MSA301.h>

class Accelerometer{
private:
    Adafruit_MSA301 msa;

public:
    boolean DEBUG_MSA = false;

    void setup() {
        if (! msa.begin()) { 
            Serial.println("Failed to find MSA301 chip"); 
        }

        Serial.println("MSA301 Found.");

        if(DEBUG_MSA == true) { 
            printMSASettings(); 
        }
    };

    void update() {
        msa.read();
        if(DEBUG_MSA == true) {
            Serial.print("X:  "); Serial.print(msa.x); 
            Serial.print("  \tY:  "); Serial.print(msa.y); 
            Serial.print("  \tZ:  "); Serial.print(msa.z); 
        }
    };

    int x() {
        return msa.x;
    }

    int y() {
        return msa.y;
    }

    int z() {
        return msa.z;
    }

    void printMSASettings() {
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
    };


};
