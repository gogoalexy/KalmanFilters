#ifndef ALPHA_BETA_FILTER_H
#define ALPHA_BETA_FILTER_H

#include "BasicLinearAlgebra.h"

class AlphaFilter
{
public:
    AlphaFilter(BLA::Matrix<1> x0, float dt, float Alpha);
    BLA::Matrix<1> update(float z);
protected:
    float x;
    float z = 0.0;
    float y = 0.0;
    float dt;
    float alpha;
};


class AlphaBetaFilter : public AlphaFilter
{
public:
    AlphaBetaFilter(BLA::Matrix<2> x0, float dt, float Alpha, float Beta);
    BLA::Matrix<2> update(float z);
protected:
    float dx;
    float beta;

};


class AlphaBetaGammaFilter : public AlphaBetaFilter
{
public:
    AlphaBetaGammaFilter(BLA::Matrix<3> x0, float dt, float Alpha, float Beta, float Gamma);
    BLA::Matrix<3> update(float z);
protected:
    float ddx;
    float gamma;
};


#endif
