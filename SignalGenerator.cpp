#include "SignalGenerator.h"

SimpleSignalGenerator::SimpleSignalGenerator(float x, float dx, float ddx, float dt, float noise_level, int seed) :
x(x), dx(dx), ddx(ddx), dt(dt), noiseGauss{0.0, 0.0}, useGaussianNoise(false)
{
    randomSeed(seed);
    setNoiseLevel(noise_level);
}

SimpleSignalGenerator::SimpleSignalGenerator(float x, float dx, float ddx, float dt, float noise_mean, float noise_std, int seed) :
x(x), dx(dx), ddx(ddx), dt(dt), noiseBorder(0), noiseScale(1.0), noiseGauss{noise_mean, noise_std}, useGaussianNoise(true)
{
    randomSeed(seed);
}

float SimpleSignalGenerator::getNextSignal()
{
    float noisy_x;
    dx += dt*ddx;
    x += dt*dx;
    if(useGaussianNoise)
        noisy_x = x + noiseGauss.random();
    else
        noisy_x = x + random(-noiseBorder, noiseBorder)/noiseScale;
    return noisy_x;
}

void SimpleSignalGenerator::resetDynamic(float x, float dx, float ddx)
{
    this->x = x;
    this->dx = dx;
    this->ddx = ddx;
}

void SimpleSignalGenerator::setNoiseLevel(float noise_level)
{
    if(noise_level >= 1.0)
    {
        noiseBorder = noise_level*1000;
        noiseScale = 1000.0;
    }
    else
    {
        noiseBorder = 1000.0/noise_level;
        noiseScale = noiseBorder;
    }
}

void SimpleSignalGenerator::setNoiseLevel(float noise_mean, float noise_std)
{
    noiseGauss = Gaussian(noise_mean, noise_std);
}
