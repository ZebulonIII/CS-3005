#include "ComplexFractal.h"
#include "NumberGrid.h"

ComplexFractal::ComplexFractal()
{
	NumberGrid::setGridSize(200, 300);
	NumberGrid::setMaxNumber(255);
	delta_x = delta_y = .01;
	min_x = -1.5;
	max_x = 1.5;
	min_y = -1;
	max_y = 1;
}
ComplexFractal::ComplexFractal(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y)
	: min_x(min_x), max_x(max_x), min_y(min_y), max_y(max_y)
{
	setGridSize(height, width);
}
ComplexFractal::~ComplexFractal() {}
bool ComplexFractal::betweenTwos(const double& value) const
{
	return value >= -2.0 && value <= 2.0;
}
double ComplexFractal::distanceFromOriginSquared(const double& x, const double& y) const
{
	return x*x + y*y;
}
double ComplexFractal::getMinX() const
{
	return min_x;
}
double ComplexFractal::getMaxX() const
{
	return max_x;
}
double ComplexFractal::getMinY() const
{
	return min_y;
}
double ComplexFractal::getMaxY() const
{
	return max_y;
}
void ComplexFractal::setGridSize(const int& height, const int& width)
{
	if (height >= 2 && width >= 2)
	{
		NumberGrid::setGridSize(height, width);
		setDeltas(calculateDeltaX(), calculateDeltaY());
	}
}
void ComplexFractal::setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y)
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
double ComplexFractal::getDeltaX() const
{
	return delta_x;
}
double ComplexFractal::getDeltaY() const
{
	return delta_y;
}
void ComplexFractal::setDeltas(const double& delta_x, const double& delta_y)
{
	if (delta_x > 0 && delta_y > 0)
	{
		this->delta_x = delta_x;
		this->delta_y = delta_y;
	}
}
double ComplexFractal::calculateDeltaX() const
{
	return (max_x - min_x) / (width - 1);
}
double ComplexFractal::calculateDeltaY() const
{
	return (max_y - min_y) / (height - 1);
}
double ComplexFractal::calculatePlaneYFromPixelRow(const int& row) const
{
	if (row < 0 || row >= height)
		return 0.0;

	return max_y - delta_y * row;
}
double ComplexFractal::calculatePlaneXFromPixelColumn(const int& column) const
{
	if (column < 0 || column >= width)
		return 0.0;

	return delta_x * column + min_x;
}
void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const
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
void ComplexFractal::zoom(const double& factor) // custom
{
	setPlaneSize(min_x * factor, max_x * factor, min_y * factor, max_y * factor);
}
void ComplexFractal::translatePlaneLeft(const double& factor) // custom
{
	if (factor >= 0)
	{
		double new_factor = (min_x - factor <= -2.0 ? 2.0 + min_x : factor);
		setPlaneSize(min_x - new_factor, max_x - new_factor, min_y, max_y);
	}
	else
		translatePlaneRight(factor * -1.0);
}
void ComplexFractal::translatePlaneRight(const double& factor) // custom
{
	if (factor >= 0)
	{
		double new_factor = (max_x + factor >= 2.0 ? 2.0 - max_x : factor);
		setPlaneSize(min_x + new_factor, max_x + new_factor, min_y, max_y);
	}
	else
		translatePlaneLeft(factor * -1.0);
}
void ComplexFractal::translatePlaneDown(const double& factor) // custom
{
	if (factor >= 0)
	{
		double new_factor = (min_y - factor <= -2.0 ? 2.0 + min_y : factor);
		setPlaneSize(min_x, max_x, min_y - new_factor, max_y - new_factor);
	}
	else
		translatePlaneUp(factor * -1.0);
}
void ComplexFractal::translatePlaneUp(const double& factor) // custom
{
	if (factor >= 0)
	{
		double new_factor = (max_y + factor >= 2.0 ? 2.0 - max_y : factor);
		setPlaneSize(min_x, max_x, min_y + new_factor, max_y + new_factor);
	}
	else
		translatePlaneDown(factor * -1.0);
}
