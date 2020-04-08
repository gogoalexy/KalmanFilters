#include "SignalGenerator.h"

SimpleSignalGenerator gaussian{0.0, 0.0, 0.0, 1.0, 0.0, 3.0, 88};
SimpleSignalGenerator uniform{0.0, 0.0, 0.0, 1.0, 10.0, 88};

void setup() {
    Serial.begin(9600);
}

void loop() {
    float gaussianPoint = gaussian.getNextSignal();
    float uniformPoint = uniform.getNextSignal();
    String packet = String(gaussianPoint) + ',' + String(uniformPoint);
    Serial.println(packet);
    delay(50);
}

