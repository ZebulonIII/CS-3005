#include <algorithm>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include "NumberGrid.h"
#include "PPM.h"
#include "HSVColorTable.h"

NumberGrid::NumberGrid() : height(300), width(400), max_number(255)
{
	number_grid = std::vector<int>(300 * 400, 0);
}
NumberGrid::NumberGrid(const int& height, const int& width) : height(height), width(width), max_number(255)
{
	number_grid = std::vector<int>(height * width, 0);
}
NumberGrid::~NumberGrid() {}
int NumberGrid::getHeight() const
{
	return height;
}
int NumberGrid::getWidth() const
{
	return width;
}
int NumberGrid::getMaxNumber() const
{
	return max_number;
}
void NumberGrid::setGridSize(const int& height, const int& width)
{
	if (height >= 2 && width >= 2)
	{
		this->height = height;
		this->width = width;
		number_grid.resize(height * width);
	}
}
void NumberGrid::setMaxNumber(const int& number)
{
	if (number >= 0)
		max_number = number;
}
const std::vector<int>& NumberGrid::getNumbers() const
{
	return number_grid;
}
int NumberGrid::index(const int& row, const int& column) const
{
	return row * width + column;
}
bool NumberGrid::indexValid(const int& row, const int& column) const
{
	return row >= 0 && row < height && column >= 0 && column < width;
}
bool NumberGrid::numberValid(const int& number) const
{
	return number >= 0 && number <= max_number;
}
int NumberGrid::getNumber(const int& row, const int& column) const
{
	return (indexValid(row, column) ? (int) number_grid[index(row, column)] : -1);
}
void NumberGrid::setNumber(const int& row, const int& column, const int& number)
{
	if (indexValid(row, column) && numberValid(number))
		number_grid[index(row, column)] = number;
}
void NumberGrid::setPPM(PPM& ppm) const
{
	ppm.setHeight(height);
	ppm.setWidth(width);
	ppm.setMaxColorValue(63);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			int number = getNumber(i, j);
			int r, g, b;

			if (number == 0)
			{
				r = g = b = 0;
			}
			else if (number == max_number)
			{
				r = 63;
				g = b = 31;
			}
			else
			{
				switch(number % 8)
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
}
void calculate_all_numbers_worker(NumberGrid& grid, int start, int num_threads)
{
	for (int i = start; i < grid.getHeight(); i += num_threads)
		for (int j = 0; j < grid.getWidth(); j++)
			grid.setNumber(i, j, grid.calculateNumber(i, j));
}
void NumberGrid::calculateAllNumbers()
{
	std::vector<std::thread> threads;
	unsigned int num_threads = std::thread::hardware_concurrency();
	std::ofstream time_output("time.txt", std::ios::app);

	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

	for (unsigned int i = 0; i < num_threads; i++)
		threads.push_back(std::thread(calculate_all_numbers_worker, std::ref(*this), i, num_threads));

	for (unsigned int i = 0; i < num_threads; i++)
		threads[i].join();

	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	std::chrono::duration< double > time_span =
		std::chrono::duration_cast<std::chrono::duration< double >>(t2 - t1);

	time_output << "Num threads: " << num_threads << "\nIt took me " << time_span.count() << " seconds to complete the threaded workload.\n";


	/*auto t1 = std::chrono::steady_clock::now();

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			setNumber(i, j, calculateNumber(i, j));

	auto t2 = std::chrono::steady_clock::now();
	auto time_span = std::chrono::duration_cast<std::chrono::duration< double >>(t2 - t1);

	time_output << "It took me " << time_span.count() << " seconds to complete the normal workload.\n";*/
	time_output.close();
}
void set_ppm_colortable_worker(NumberGrid& grid, PPM& ppm, const ColorTable& colors, int start, int offset)
{
	for (int i = start; i < ppm.getHeight(); i += offset)
		for (int j = 0; j < ppm.getWidth(); j++)
		{
			int number = grid.getNumber(i, j);
			int color_table_index;
			if (number == grid.getMaxNumber())
				color_table_index = colors.getNumberOfColors() - 1;
			else if (number == 0)
				color_table_index = colors.getNumberOfColors() - 2;
			else
				color_table_index = number % (colors.getNumberOfColors() - 2);

			for (int k = 0; k < 3; k++)
				ppm.setChannel(i, j, k, colors[color_table_index].getChannel(k));
		}
}
void NumberGrid::setPPM(PPM& ppm, const ColorTable& colors) const
{
	if (colors.getNumberOfColors() >= 3)
	{
		ppm.setHeight(height);
		ppm.setWidth(width);
		ppm.setMaxColorValue(colors.getMaxChannelValue());

		unsigned int num_threads = std::thread::hardware_concurrency();
		std::thread threads[num_threads];		

		for (unsigned int i = 0; i < num_threads; i++)
			threads[i] = std::thread(set_ppm_colortable_worker, std::ref(*this), std::ref(ppm), std::ref(colors), i, num_threads);

		for (unsigned int i = 0; i < num_threads; i++)
			threads[i].join();
	}
}
int NumberGrid::getMaximumNumber() const // custom
{
	return *std::max_element(number_grid.begin(), number_grid.end());
}
void NumberGrid::setPPM(PPM& dst, const HSVColorTable& colors) const // custom
{
	setPPM(dst, colors.toColorTable());
}
