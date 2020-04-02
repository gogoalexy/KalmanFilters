#ifndef GENERATOR_H
#define GENERATOR_H

#include <Arduino.h>
#include "Gaussian.h"

class SimpleSignalGenerator
{
public:
    void setNoiseLevel(float noise_level);
    void setNoiseLevel(float noise_mean, float noise_std);
    SimpleSignalGenerator(float x, float dx, float ddx, float dt, float noise_level, int seed=26);
    SimpleSignalGenerator(float x, float dx, float ddx, float dt, float noise_mean, float noise_std, int seed=26);
    float getNextSignal();
    void resetDynamic(float x, float dx, float ddx);
private:
    float x;
    float dx;
    float ddx;
    float dt;
    
    float noiseBorder;
    float noiseScale;
    
    Gaussian noiseGauss;
    const bool useGaussianNoise;
};

#endif
