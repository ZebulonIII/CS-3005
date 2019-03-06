#include "NumberGrid.h"
#include "PPM.h"

NumberGrid::NumberGrid() : max_number(255)
{
	setGridSize(300, 400);
}
NumberGrid::NumberGrid(const int& height, const int& width) :  max_number(255)
{
	setGridSize(height, width);
}
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
		number_grid = std::vector<int>(height * width, 0);
	}
}
void NumberGrid::setMaxNumber(const int& number)
{
	if (number >= 0)
	{
		max_number = number;
	}
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
	{
		number_grid[index(row, column)] = number;
	}
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
