#include <algorithm>
#include <fstream>
#include <vector>
#include "NumberGrid.h"
#include "PPM.h"
#include "HSVColorTable.h"

NumberGrid::NumberGrid() : mHeight(300), mWidth(400), mMaxNumber(255)
{
	number_grid = std::vector<int>(300 * 400, 0);
}
NumberGrid::NumberGrid(const int& height, const int& width) : mHeight(height), mWidth(width), mMaxNumber(255)
{
	number_grid = std::vector<int>(height * width, 0);
}
NumberGrid::~NumberGrid() {}
int NumberGrid::getHeight() const
{
	return mHeight;
}
int NumberGrid::getWidth() const
{
	return mWidth;
}
int NumberGrid::getMaxNumber() const
{
	return mMaxNumber;
}
void NumberGrid::setGridSize(const int& height, const int& width)
{
	if (height >= 2 && width >= 2)
	{
		mHeight = height;
		mWidth = width;
		number_grid.resize(height * width);
	}
}
void NumberGrid::setMaxNumber(const int& number)
{
	if (number >= 0)
		mMaxNumber = number;
}
const std::vector<int>& NumberGrid::getNumbers() const
{
	return number_grid;
}
int NumberGrid::index(const int& row, const int& column) const
{
	return row * mWidth + column;
}
bool NumberGrid::indexValid(const int& row, const int& column) const
{
	return row >= 0 && row < mHeight && column >= 0 && column < mWidth;
}
bool NumberGrid::numberValid(const int& number) const
{
	return number >= 0 && number <= mMaxNumber;
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
void NumberGrid::setPPM(PPM& ppm)
{
	ppm.setHeight(mHeight);
	ppm.setWidth(mWidth);
	ppm.setMaxColorValue(63);
	for (int i = 0; i < mHeight; i++)
		for (int j = 0; j < mWidth; j++)
		{
			int number = getNumber(i, j);
			int r, g, b;

			if (number == 0)
			{
				r = g = b = 0;
			}
			else if (number == mMaxNumber)
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
void NumberGrid::calculateAllNumbers()
{
	for (int i = 0; i < mHeight; i++)
		for (int j = 0; j < mWidth; j++)
			setNumber(i, j, calculateNumber(i, j));
}
void NumberGrid::setPPM(PPM& ppm, const ColorTable& colors)
{
	if (colors.getNumberOfColors() >= 3)
	{
		ppm.setHeight(mHeight);
		ppm.setWidth(mWidth);
		ppm.setMaxColorValue(colors.getMaxChannelValue());

		for (int i = 0; i < mHeight; i++)
			for (int j = 0; j < mWidth; j++)
			{
				int number = getNumber(i, j);
				int color_table_index;
				if (number == mMaxNumber)
					color_table_index = colors.getNumberOfColors() - 1;
				else if (number == 0)
					color_table_index = colors.getNumberOfColors() - 2;
				else
					color_table_index = number % (colors.getNumberOfColors() - 2);

				for (int k = 0; k < 3; k++)
					ppm.setChannel(i, j, k, colors[color_table_index].getChannel(k));
			}
	}
}
int NumberGrid::getMaximumNumber() const // custom
{
	return *std::max_element(number_grid.begin(), number_grid.end());
}
void NumberGrid::setPPM(PPM& dst, const HSVColorTable& colors) // custom
{
	setPPM(dst, colors.toColorTable());
}
