#ifndef _THREADED_GRID_H_
#define _THREADED_GRID_H_

#include "NumberGrid.h"
#include "ThreadedVector.h"
#include "ColorTable.h"
#include "PPM.h"

class ThreadedGrid : public NumberGrid
{
public:
	ThreadedGrid();
	ThreadedGrid(const int& height, const int& width);
	ThreadedGrid(const int& height, const int& width, const unsigned int& n);
	virtual ~ThreadedGrid();
	unsigned int getNumThreads() const;
	void setNumThreads(unsigned int n);
	virtual void calculateAllNumbers();
	virtual void worker();
	//virtual void setPPM(PPM& ppm);
	//virtual void ppm_worker(PPM& ppm);
	//virtual void setPPM(PPM& ppm, const ColorTable& colors);
	//virtual void ppm_color_worker(PPM& ppm, const ColorTable& colors);
	//virtual void setPPM(PPM& dst, const HSVColorTable& colors);
protected:
	ThreadedVector<int> mWorkQueue;
	unsigned int mNumThreads;
};

#endif
