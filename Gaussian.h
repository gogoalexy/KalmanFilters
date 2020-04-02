#ifndef GAUSSIAN_H
#define GAUSSIAN_H

#include <Arduino.h>
#include <math.h>

class Gaussian : public Printable
{
public:
    Gaussian(float Mean, float Variance);
    float mean;
    float variance;
    
    Gaussian& operator=(const Gaussian& b);
    Gaussian operator+(const Gaussian& b);
    Gaussian operator-(const Gaussian& b);
    Gaussian operator*(const Gaussian& b);
    Gaussian& operator+=(const Gaussian& b);
    Gaussian& operator-=(const Gaussian& b);
    Gaussian& operator*=(const Gaussian& b);
    void shift(float c);
    void scale(float c);
    
    float random(String algorithm="MarsagliaPolar");
    
    size_t printTo(Print& p) const override;
protected:
    static const float two_pi = 6.28318530718;
    float BoxMuller();
    float MarsagliaPolar();
};

#endif
