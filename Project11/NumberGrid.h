#ifndef _NUMBERGRID_H_
#define _NUMBERGRID_H_

#include <vector>
#include <mutex>
#include <thread>
#include "PPM.h"
#include "ColorTable.h"
#include "HSVColorTable.h"

class NumberGrid
{
public:
	NumberGrid();
	NumberGrid(const int& height, const int& width);
	virtual ~NumberGrid();
	int getHeight() const;
	int getWidth() const;
	int getMaxNumber() const;
	virtual void setGridSize( const int& height, const int& width);
	void setMaxNumber(const int& number);
	const std::vector<int>& getNumbers() const;
	int index(const int& row, const int& column) const;
	bool indexValid(const int& row, const int& column) const;
	bool numberValid(const int& number) const;
	int getNumber(const int& row, const int& column) const;
	void setNumber(const int& row, const int& column, const int& number);
	void setPPM(PPM& ppm) const;
	virtual int calculateNumber(const int& row, const int& column) const = 0;
	virtual void calculateAllNumbers();
	void setPPM(PPM& ppm, const ColorTable& colors) const;
	int getMaximumNumber() const; // custom
	void setPPM(PPM& dst, const HSVColorTable& colors) const; // custom
protected:
	std::vector<int> number_grid;
	int height, width, max_number;
};

#endif // _NUMBERGRID_H_
