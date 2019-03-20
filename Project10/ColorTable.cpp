#include <vector>
#include <cstdlib>
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
	if (i < 0 || i >= mColors.size())
	{
		static Color ec(-1, -1, -1);
		static Color c(-1, -1, -1);
		c = ec;
		return c;
	}
	else
	{
		return mColors[i];
	}
}
Color& ColorTable::operator[] (const int& i)
{
	if (i < 0 || i >= mColors.size())
	{
		static Color ec(-1, -1, -1);
		static Color c(-1, -1, -1);
		c = ec;
		return c;
	}
	else
	{
		return mColors[i];
	}
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
		int pos_diff = position2 - position1;
		double red_delta = (color2.getRed() - color1.getRed()) / pos_diff;
		double green_delta  = (color2.getGreen() - color1.getGreen()) / pos_diff;
		double blue_delta = (color2.getBlue() - color1.getBlue()) / pos_diff;

		for (int i = 0; i <= pos_diff; i++)
		{
			Color& color = mColors[position1 + i];
			color.setRed(color1.getRed() + (red_delta * i));
			color.setGreen(color1.getGreen() + (green_delta * i));
			color.setBlue(color1.getBlue() + (blue_delta * i));

			/*mColors[position1 + i].setRed(color1.getRed() + (red_delta * i));
			mColors[position1 + i].setGreen(color1.getGreen() + (green_delta * i));
			mColors[position1 + i].setBlue(color1.getBlue() + (blue_delta * i));*/

		}
	}
}
int ColorTable::getMaxChannelValue() const
{
	int max_color = 0;
	for (size_t i = 0; i < mColors.size(); i++)
	{
		const Color& color = mColors[i];
		for (int k = 0; k < 3; k++)
			if (color.getChannel(k) > max_color)
				max_color = color.getChannel(k);
	}
	return max_color;
}
