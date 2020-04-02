#include "Gaussian.h"

Gaussian::Gaussian(float Mean, float Variance) :
mean(Mean), variance(Variance)
{}

Gaussian& Gaussian::operator=(const Gaussian& b)
{
    this->mean = b.mean;
    this->variance = b.variance;
    return *this;
}

Gaussian Gaussian::operator+(const Gaussian& b)
{
    Gaussian result{0.0, 0.0};
    result.mean = this->mean + b.mean;
    result.variance = this->variance + b.variance;
    return result;
}

Gaussian Gaussian::operator-(const Gaussian& b)
{
    Gaussian result{0.0, 0.0};
    result.mean = this->mean - b.mean;
    result.variance = this->variance + b.variance;
    return result;
}

Gaussian Gaussian::operator*(const Gaussian& b)
{
    Gaussian result{0.0, 0.0};
    result.mean = (this->mean*b.variance) + (b.mean*this->variance);
    float denominator = this->variance + b.variance;
    if(denominator != 0)
        result.variance = (this->variance*b.variance) / denominator;
    else
        result.variance = 0;
    return result;
}

Gaussian& Gaussian::operator+=(const Gaussian& b)
{
    this->mean += b.mean;
    this->variance += b.variance;
    return *this;
}

Gaussian& Gaussian::operator-=(const Gaussian& b)
{
    this->mean -= b.mean;
    this->variance += b.variance;
    return *this;
}

Gaussian& Gaussian::operator*=(const Gaussian& b)
{
    this->mean = (this->mean*b.variance) + (b.mean*this->variance);
    this->variance = (this->variance*b.variance) / (this->variance+b.variance);
    return *this;
}

void Gaussian::shift(float c)
{
    this->mean += c;
}

void Gaussian::scale(float c)
{
    this->mean *= c;
    this->variance *= c;
}

float Gaussian::random(String algorithm)
{
    if(algorithm == "MarsagliaPolar")
        return MarsagliaPolar();
    else
        return BoxMuller();
}

float Gaussian::BoxMuller()
{
    float u1, u2, z0;
    u1 = ::random(1, 1025)/1024.0; //(0, 1)
    u2 = ::random(1, 1025)/1024.0;
    z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
    return z0 * variance + mean;
}

float Gaussian::MarsagliaPolar()
{
    float u1, u2, s;
    do
    {
        u1 = ::random(1, 1025)/512.0 - 1.0; //(0, 1)
        u2 = ::random(1, 1025)/512.0 - 1.0;
        s = sq(u1) + sq(u2);
    }
    while(s == 0.0 || s >= 1.0);
    s = sqrt(-2.0 * log(s) / s);
    return u1 * s * variance + mean;
}

size_t Gaussian::printTo(Print& p) const
{
    String outstr = "N(" + String(mean) + ',' + String(variance) + ')';
    return p.print(outstr);
}
