#include "JuliaSet.h"

JuliaSet::JuliaSet()
{
	a = -.650492;
	b = -.478235;
	NumberGrid::setGridSize(200, 300);
	NumberGrid::setMaxNumber(255);
	delta_x = delta_y = .01;
	min_x = -1.5;
	max_x = 1.5;
	min_y = -1;
	max_y = 1;
}
JuliaSet::JuliaSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b)
: min_x(min_x), max_x(max_x), min_y(min_y), max_y(max_y), a(a), b(b)
{
	setGridSize(height, width);
}
JuliaSet::~JuliaSet() {}
bool JuliaSet::betweenTwos(const double& value) const
{
	return value >= -2.0 && value <= 2.0;
}
double JuliaSet::getMinX() const
{
	return min_x;
}
double JuliaSet::getMaxX() const
{
	return max_x;
}
double JuliaSet::getMinY() const
{
	return min_y;
}
double JuliaSet::getMaxY() const
{
	return max_y;
}
double JuliaSet::getA() const
{
	return a;
}
double JuliaSet::getB() const
{
	return b;
}
void JuliaSet::setGridSize(const int& height, const int& width)
{
	if (height >= 2 && width >= 2)
	{
		NumberGrid::setGridSize(height, width);
		setDeltas(calculateDeltaX(), calculateDeltaY());
	}
}
void JuliaSet::setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y)
{
	if (betweenTwos(min_x) && betweenTwos(max_x) && betweenTwos(min_y) && betweenTwos(max_y) &&
		min_x != max_x && min_y != max_y)
	{
		if (min_x > max_x)
		{
			this->min_x = max_x;
			this->max_x = min_x;
		}
		else
		{
			this->min_x = min_x;
			this->max_x = max_x;
		}
		if (min_y > max_y)
		{
			this->min_y = max_y;
			this->max_y = min_y;
		}
		else
		{
			this->min_y = min_y;
			this->max_y = max_y;
		}
		setDeltas(calculateDeltaX(), calculateDeltaY());
	}
}
void JuliaSet::setParameters(const double& a, const double& b)
{
	if (betweenTwos(a) && betweenTwos(b))
	{
		this->a = a;
		this->b = b;
	}
}
double JuliaSet::getDeltaX() const
{
	return delta_x;
}
double JuliaSet::getDeltaY() const
{
	return delta_y;
}
void JuliaSet::setDeltas(const double& delta_x, const double& delta_y)
{
	if (delta_x > 0 && delta_y > 0)
	{
		this->delta_x = delta_x;
		this->delta_y = delta_y;
	}
}
double JuliaSet::calculateDeltaX() const
{
	return ( max_x - min_x ) / ( width - 1 );
}
double JuliaSet::calculateDeltaY() const
{
	return ( max_y - min_y ) / (height - 1);
}
double JuliaSet::calculatePlaneYFromPixelRow(const int& row) const
{
	if (row < 0 || row >= height)
		return 0.0;

	return max_y - delta_y * row;
}
double JuliaSet::calculatePlaneXFromPixelColumn(const int& column) const
{
	if (column < 0 || column >= width)
		return 0.0;

	return delta_x * column + min_x;
}
void JuliaSet::calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const
{
	if (row < 0 || row >= height || column < 0 || column >= width)
	{
		x = 0.0;
		y = 0.0;
	}
	else
	{
		x = calculatePlaneXFromPixelColumn(column);
		y = calculatePlaneYFromPixelRow(row);
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
	while (count < max_number && (x0 * x0 + y0 * y0 <= 4))
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
	if (row < 0 || row >= height || column < 0 || column >= width)
		return -1;

	return calculatePlaneEscapeCount(calculatePlaneXFromPixelColumn(column), calculatePlaneYFromPixelRow(row));
}
