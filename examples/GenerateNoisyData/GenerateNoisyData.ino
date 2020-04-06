#include "SignalGenerator.h"

#define USE_GAUSSIAN

SimpleSignalGenerator gaussian{0.0, 0.0, 0.0, 1.0, 0.0, 3.0, 88};
SimpleSignalGenerator uniform{0.0, 0.0, 0.0, 1.0, 10.0, 88};

void setup() {
    Serial.begin(9600);
}

void loop() {
    #ifdef USE_GAUSSIAN
        float noisySignal = gaussian.getNextSignal();
    #else
        float noisySignal = uniform.getNextSignal();
    #endif
    Serial.println(noisySignal);
    delay(50);
}

