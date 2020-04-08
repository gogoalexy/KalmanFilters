#include <BasicLinearAlgebra.h>
#include <SignalGenerator.h>
#include <AlphaBetaFilter.h>

SimpleSignalGenerator vehicle{0.0, 0.5, 0.0, 1.0, 0.0, 2.0, 88};
AlphaFilter a_filter{BLA::Matrix<1> {0.0}, 1.0, 0.2};
AlphaBetaFilter ab_filter{BLA::Matrix<2> {0.0, 0.5}, 1.0, 0.2, 0.01};
AlphaBetaGammaFilter abc_filter{BLA::Matrix<3> {0.0, 0.5, 0.0}, 1.0, 0.6, 0.02, 0.01};

void setup() {
    Serial.begin(9600);
}

void loop() {
    float position = vehicle.getNextSignal();
    BLA::Matrix<1> a_estimate = a_filter.update(position);
    BLA::Matrix<2> ab_estimate = ab_filter.update(position);
    BLA::Matrix<3> abc_estimate = abc_filter.update(position);
    String packet = String(position) + ',' + String(a_estimate(0)) + ',' + String(ab_estimate(0)) + ',' + String(abc_estimate(0));
    Serial.println(packet);
    delay(300);
}
