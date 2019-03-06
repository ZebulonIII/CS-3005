#ifndef _JULIA_SET_H_
#define _JULIA_SET_H_

#include "NumberGrid.h"

class JuliaSet : public NumberGrid
{
public:
	JuliaSet();
	JuliaSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b);
	virtual ~JuliaSet();
	double getMinX() const;
	double getMaxX() const;
	double getMinY() const;
	double getMaxY() const;
	double getA() const;
	double getB() const;
	virtual void setGridSize(const int& height, const int& width);
	void setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y);
	void setParameters(const double& a, const double& b);
	double getDeltaX() const;
	double getDeltaY() const;
	void setDeltas(const double& delta_x, const double& delta_y);
	double calculateDeltaX() const;
	double calculateDeltaY() const;
	double calculatePlaneYFromPixelRow(const int& row) const;
	double calculatePlaneXFromPixelColumn(const int& column) const;
	void calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const;
	virtual void calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const;
	int calculatePlaneEscapeCount(const double& x0, const double& y0) const;
	virtual int calculateNumber(const int& row, const int& column) const;
private:
	double min_x, min_y, max_x, max_y;
	double delta_x, delta_y;
	double a, b;
	
	template<class T>
	bool betweenTwos(const T& value) const
	{
		return value >= -2.0 and value <= 2.0;
	}
};

#endif // _JULIA_SET_H_