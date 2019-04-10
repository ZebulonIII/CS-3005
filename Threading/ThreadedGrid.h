#ifndef _THREADED_GRID_H_
#define _THREADED_GRID_H_

#include "NumberGrid.h"
#include "ThreadedVector.h"
#include "ColorTable.h"
#include "PPM.h"
#include "HSVColorTable.h"

class ThreadedGrid : public NumberGrid
{
public:
	ThreadedGrid();
	ThreadedGrid(const int& height, const int& width);
	virtual ~ThreadedGrid();
	virtual void calculateAllNumbers();
	virtual void worker();
	virtual void setPPM(PPM& ppm) const;
	virtual void ppm_worker();
	virtual void setPPM(PPM& ppm, const ColorTable& colors) const;
	virtual void ppm_color_worker();
	virtual void setPPM(PPM& dst, const HSVColorTable& colors) const;
private:
	ThreadedVector<int> mWorkQueue;
};

#endif