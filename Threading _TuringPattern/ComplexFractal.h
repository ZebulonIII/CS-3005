#ifndef _COMPLEX_FRACTAL_H_
#define _COMPLEX_FRACTAL_H_

#include "NumberGrid.h"
#include "ThreadedGrid.h"

class ComplexFractal : public ThreadedGrid
{
public:
	ComplexFractal();
	ComplexFractal(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y);
	virtual ~ComplexFractal();
	double getMinX() const;
	double getMaxX() const;
	double getMinY() const;
	double getMaxY() const;
	virtual void setGridSize(const int& height, const int& width);
	void setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y);
	double getDeltaX() const;
	double getDeltaY() const;
	void setDeltas(const double& delta_x, const double& delta_y);
	double calculateDeltaX() const;
	double calculateDeltaY() const;
	double calculatePlaneYFromPixelRow(const int& row) const;
	double calculatePlaneXFromPixelColumn(const int& column) const;
	void calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const;
	void zoom(const double& factor);  // custom
	void translatePlaneLeft(const double& factor); // custom
	void translatePlaneRight(const double& factor); // custom
	void translatePlaneUp(const double& factor); // custom
	void translatePlaneDown(const double& factor); // custom
protected:
	double min_x, max_x, min_y, max_y;
	double delta_x, delta_y;
	bool betweenTwos(const double& value) const;
	double distanceFromOriginSquared(const double& x, const double& y) const;
};

#endif // _COMPLEX_FRACTAL_H_
