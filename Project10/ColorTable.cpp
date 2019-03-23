#include <vector>
#include <cstdlib>
#include <cmath>
#include "ColorTable.h"
#include "Color.h"

ColorTable::ColorTable(const size_t& num_color)
{
	mColors = std::vector<Color>(num_color);
}
size_t ColorTable::getNumberOfColors() const
{
	return mColors.size();
}
void ColorTable::setNumberOfColors(const size_t& num_color)
{
	mColors.resize(num_color);
}
const Color& ColorTable::operator[] (const int& i) const
{
	if (i < 0 || i >= (int)mColors.size())
	{
		static Color ec(-1, -1, -1);
		static Color c(-1, -1, -1);
		c = ec;
		return c;
	}
	else
		return mColors[i];
}
Color& ColorTable::operator[] (const int& i)
{
	if (i < 0 || i >= (int)mColors.size())
	{
		static Color ec(-1, -1, -1);
		static Color c(-1, -1, -1);
		c = ec;
		return c;
	}
	else
		return mColors[i];
}
void ColorTable::setRandomColor(const int& max_color_value, const size_t& position)
{
	if (position >= 0 && position < mColors.size() && max_color_value >= 0)
	{
		Color& color = mColors[position];
		for (int i = 0; i < 3; i++)
			color.setChannel(i, std::rand() % (max_color_value + 1));
	}
}
void ColorTable::insertGradient(const Color& color1, const Color& color2, const size_t& position1, const size_t& position2)
{
	if (position2 > position1 && position1 >= 0 && position1 < getNumberOfColors() && position2 >= 0 && position2 < getNumberOfColors())
	{
		int n = position2 - position1;
		double red_step = (double)(color2.getRed() - color1.getRed()) / n;
		double green_step  = (double)(color2.getGreen() - color1.getGreen()) / n;
		double blue_step = (double)(color2.getBlue() - color1.getBlue()) / n;

		for (int i = 0; i <= n; i++)
		{
			int red = color1.getRed() + red_step * i;
			int green = color1.getGreen() + green_step * i;
			int blue = color1.getBlue() + blue_step * i;

			Color& color = mColors[position1 + i];
			color.setRed(red);
			color.setGreen(green);
			color.setBlue(blue);
		}
	}
}
int ColorTable::getMaxChannelValue() const
{
	int max_color = 0;
	for (size_t i = 0; i < mColors.size(); i++)
	{
		int max = mColors[i].getMaxColorValue();
		if (max > max_color)
			max_color = max;
	}
	return max_color;
}
