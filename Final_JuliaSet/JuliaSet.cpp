#include <cmath>
#include "JuliaSet.h"
#include "ComplexFractal.h"

JuliaSet::JuliaSet() : ComplexFractal(), a(-.650492), b(-.478235) {}
JuliaSet::JuliaSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b)
	: ComplexFractal(height, width, min_x, max_x, min_y, max_y), a(a), b(b) {}
JuliaSet::~JuliaSet() {}
double JuliaSet::getA() const
{
	return a;
}
double JuliaSet::getB() const
{
	return b;
}
void JuliaSet::setParameters(const double& a, const double& b)
{
	if (betweenTwos(a) && betweenTwos(b))
	{
		this->a = a;
		this->b = b;
	}
}
void JuliaSet::calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const
{
	x1 = x0 * x0 - y0 * y0 + a;
	y1 = 2.0 * x0 * y0 + b;
}
int JuliaSet::calculatePlaneEscapeCount(const double& x, const double& y) const
{
	int count = 0;
	double x0 = x, y0 = y, x1 = 0.0, y1 = 0.0;
	while (count < mMaxNumber && distanceFromOriginSquared(x0, y0) <= 4)
	{
		calculateNextPoint(x0, y0, x1, y1);
		x0 = x1;
		y0 = y1;
		count++;
	}
	return count;
}
int JuliaSet::calculateNumber(const int& row, const int& column) const
{
	if (row < 0 || row >= mHeight || column < 0 || column >= mWidth)
		return -1;

	return calculatePlaneEscapeCount(calculatePlaneXFromPixelColumn(column), calculatePlaneYFromPixelRow(row));
}

// JuliaSetFive
JuliaSetFive::JuliaSetFive() : JuliaSet() {}
JuliaSetFive::~JuliaSetFive() {}
void JuliaSetFive::calculateNextPoint(const double& x0, const double& y0, double& x1, double& y1) const {
  double r = std::sqrt(x0 * x0 + y0 * y0);
	double theta = std::atan2(y0, x0);
	double power = std::pow(r, 5);
	x1 = power * std::cos(5 * theta) + a;
	y1 = power * std::sin(5 * theta) + b;
}
