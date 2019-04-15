#include <thread>
#include <fstream>
#include "ThreadedGrid.h"
#include "ThreadedVector.h"
#include "PPM.h"
#include "ColorTable.h"
#include "HSVColorTable.h"

ThreadedGrid::ThreadedGrid() : NumberGrid() {}
ThreadedGrid::ThreadedGrid(const int& height, const int& width) : NumberGrid(height, width) {}
ThreadedGrid::~ThreadedGrid() {}
void ThreadedGrid::calculateAllNumbers()
{
	// Create workload
	mWorkQueue.clear();
	for (int i = 0; i < getHeight(); i++)
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
		mWorkQueue.pop_back(value, 1);
		int i = value[0];
		for (int j = 0; j < getWidth(); j++)
			setNumber(i, j, calculateNumber(i, j));
		value.clear();
	}
}
void ThreadedGrid::setPPM(PPM& ppm)
{
	ppm.setHeight(getHeight());
	ppm.setWidth(getWidth());
	ppm.setMaxColorValue(63);

	// Create workload
	mWorkQueue.clear();
	for (int i = 0; i < getHeight(); i++)
		mWorkQueue.push_back(i);

	unsigned int num_threads = std::thread::hardware_concurrency();
	std::thread threads[num_threads];

	for (unsigned int i = 0; i < num_threads; i++)
		threads[i] = std::thread(&ThreadedGrid::ppm_worker, this, std::ref(ppm));

	for (unsigned int i = 0; i < num_threads; i++)
		threads[i].join();
}
void ThreadedGrid::ppm_worker(PPM& ppm)
{
	std::vector<int> value;
	while (!mWorkQueue.empty())
	{
		mWorkQueue.pop_back(value, 1);
		int i = value[0];
		for (int j = 0; j < getWidth(); j++)
		{
			int number = getNumber(i, j);
			int r, g, b;

			if (number == 0)
			{
				r = g = b = 0;
			}
			else if (number == getMaxNumber())
			{
				r = 63;
				g = b = 31;
			}
			else
			{
				switch (number % 8)
				{
				case 0: r = g = b = 63; break;
				case 1: r = 63;	g = b = 31; break;
				case 2: r = g = 63; b = 31; break;
				case 3: r = b = 31; g = 63; break;
				case 4: r = g = b = 0; break;
				case 5: r = 31; g = b = 63; break;
				case 6: r = g = 31; b = 63; break;
				case 7: r = b = 63; g = 31; break;
				}
			}
			ppm.setPixel(i, j, r, g, b);
		}
		value.clear();
	}
}
void ThreadedGrid::setPPM(PPM& ppm, const ColorTable& colors)
{
	if (colors.getNumberOfColors() >= 3)
	{
		ppm.setHeight(getHeight());
		ppm.setWidth(getWidth());
		ppm.setMaxColorValue(colors.getMaxChannelValue());

		// Create workload
		mWorkQueue.clear();
		for (int i = 0; i < getHeight(); i++)
			mWorkQueue.push_back(i);

		unsigned int num_threads = std::thread::hardware_concurrency();
		std::thread threads[num_threads];

		for (unsigned int i = 0; i < num_threads; i++)
			threads[i] = std::thread(&ThreadedGrid::ppm_color_worker, this, std::ref(ppm), std::ref(colors));

		for (unsigned int i = 0; i < num_threads; i++)
			threads[i].join();
	}
}
void ThreadedGrid::ppm_color_worker(PPM& ppm, const ColorTable& colors)
{
	std::vector<int> value;
	while (!mWorkQueue.empty())
	{
		mWorkQueue.pop_back(value, 1);
		int i = value[0];
		for (int j = 0; j < getWidth(); j++)
		{
			int number = getNumber(i, j);
			int color_table_index;
			if (number == getMaxNumber())
				color_table_index = colors.getNumberOfColors() - 1;
			else if (number == 0)
				color_table_index = colors.getNumberOfColors() - 2;
			else
				color_table_index = number % (colors.getNumberOfColors() - 2);

			for (int k = 0; k < 3; k++)
				ppm.setChannel(i, j, k, colors[color_table_index].getChannel(k));
		}
		value.clear();
	}
}
void ThreadedGrid::setPPM(PPM& ppm, const HSVColorTable& colors)
{
	setPPM(ppm, colors.toColorTable());
}
