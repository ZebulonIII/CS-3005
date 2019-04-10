#include <thread>
#include "ThreadedGrid.h"
#include "ThreadedVector.h"

ThreadedGrid::ThreadedGrid() : NumberGrid() {}
ThreadedGrid::ThreadedGrid(const int& height, const int& width) : NumberGrid(height, width) {}
ThreadedGrid::~ThreadedGrid() {}
void ThreadedGrid::calculateAllNumbers()
{
	// Create workload
	for (int i = 0; i < height; i++)
		mWorkQueue.push_back(i);

	unsigned int num_threads = std::thread::hardware_concurrency();
	std::thread threads[num_threads];

	for (unsigned int i = 0; i < num_threads; i++)
		threads[i] = std::thread(&ThreadedGrid::worker, this);

	for (unsigned int i = 0; i < num_threads; i++)
		threads[i].join();
}
void ThreadedGrid::worker()
{
	std::vector<int> value;
	while (!mWorkQueue.empty())
	{
		//value.clear();
		mWorkQueue.pop_back(value, 1);
		int i = value[0];
		for (int j = 0; j < getWidth(); j++)
			setNumber(i, j, calculateNumber(i, j));
		value.clear();
	}
}
