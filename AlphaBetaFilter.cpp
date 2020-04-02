#include "AlphaBetaFilter.h"

using namespace BLA;

AlphaFilter::AlphaFilter(Matrix<1> x0, float dt, float Alpha) :
x(x0(0)), dt(dt), alpha(Alpha)
{}

Matrix<1> AlphaFilter::update(float z)
{
    y = z - x;
    x += y * alpha;
    this->z = z;
    return Matrix<1>{x};
}


AlphaBetaFilter::AlphaBetaFilter(Matrix<2> x0, float dt, float Alpha, float Beta) :
AlphaFilter{x0.Submatrix(Slice<0,1>(), Slice<0,1>()), dt, Alpha}, dx(x0(1)), beta(Beta)
{}

Matrix<2> AlphaBetaFilter::update(float z)
{
    x = x + dx*dt;
    y = z - x;
    x += y * alpha;
    dx = dx + (beta/dt)*y;
    this->z = z;
    return Matrix<2>{x, dx};
}


AlphaBetaGammaFilter::AlphaBetaGammaFilter(Matrix<3> x0, float dt, float Alpha, float Beta, float Gamma) :
AlphaBetaFilter{x0.Submatrix(Slice<0,2>(), Slice<0,1>()), dt, Alpha, Beta}, ddx(x0(2)), gamma(Gamma)
{}

Matrix<3> AlphaBetaGammaFilter::update(float z)
{
    dx = dx + ddx*dt;
    x = x + dx*dt;
    y = z - x;
    x += y * alpha;
    dx = dx + (beta/dt)*y;
    ddx = ddx + (2*gamma/dt)*y;
    this->z = z;
    return Matrix<3>{x, dx, ddx};
}

