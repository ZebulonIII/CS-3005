#ifndef _THREADED_GRID_H_
#define _THREADED_GRID_H_

#include "NumberGrid.h"
#include "ThreadedVector.h"

class ThreadedGrid : public NumberGrid
{
public:
	ThreadedGrid();
	ThreadedGrid(const int& height, const int& width);
	virtual ~ThreadedGrid();
	virtual void calculateAllNumbers();
	virtual void worker();
private:
	ThreadedVector<int> mWorkQueue;
};

#endif