#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet() : ComplexFractal() {}
MandelbrotSet::MandelbrotSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y)
	: ComplexFractal(height, width, min_x, max_x, min_y, max_y) {}
MandelbrotSet::~MandelbrotSet() {}
void MandelbrotSet::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const
{
	x1 = x0*x0 - y0*y0 + a;
	y1 = 2*x0*y0 + b;
}
int MandelbrotSet::calculatePlaneEscapeCount(const double& a, const double& b) const
{
	double x0 = 0.0, y0 = 0.0, x1, y1;
	int count = 0;

	while (count < max_number && (x0*x0 + y0*y0 <= 4))
	{
		calculateNextPoint(x0, y0, a, b, x1, y1);
		x0 = x1;
		y0 = y1;
		count++;
	}

	return count;
}
int MandelbrotSet::calculateNumber(const int& row, const int& column) const
{
	if (row < 0 || row >= height || column < 0 || column >= width)
		return -1;

	return calculatePlaneEscapeCount(calculatePlaneXFromPixelColumn(column), calculatePlaneYFromPixelRow(row));
}
