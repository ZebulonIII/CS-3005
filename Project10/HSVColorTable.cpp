#include <vector>
#include "HSVColorTable.h"
#include "HSVColor.h"

HSVColorTable::HSVColorTable(const size_t& num_color) : mColors(std::vector<HSVColor>(num_color)) {}
size_t HSVColorTable::getNumberOfColors() const
{
	return mColors.size();
}
void HSVColorTable::setNumberOfColors(const size_t& num_color)
{
	mColors.resize(num_color);
}
const HSVColor& HSVColorTable::operator[] (const int& i) const
{
	if (i < 0 || i >= mColors.size())
	{
		static HSVColor ec(-1, -1, -1);
		static HSVColor c(-1, -1, -1);
		c = ec;
		return c;
	}
	else
		return mColors[i];
}
HSVColor& HSVColorTable::operator[] (const int& i)
{
	if (i < 0 || i >= mColors.size())
	{
		static HSVColor ec(-1, -1, -1);
		static HSVColor c(-1, -1, -1);
		c = ec;
		return c;
	}
	else
		return mColors[i];
}
void HSVColorTable::setRandomColor(const int& max_color_value, const size_t& position)
{
	if (position >= 0 && position < mColors.size() && max_color_value >= 0)
	{
		HSVColor& color = mColors[position];
		for (int i = 0; i < 3; i++)
			color.setChannel(i, std::rand() % (max_color_value + 1));
	}
}
void HSVColorTable::insertGradient(const HSVColor& color1, const HSVColor& color2, const size_t& position1, const size_t& position2)
{
	if (position2 > position1 && position1 >= 0 && position1 < getNumberOfColors() && position2 >= 0 && position2 < getNumberOfColors())
	{
		int pos_diff = position2 - position1;
		double hue_delta = (color2.getHue() - color1.getHue()) / pos_diff;
		double saturation_delta = (color2.getSaturation() - color1.getSaturation()) / pos_diff;
		double value_delta = (color2.getValue() - color1.getValue()) / pos_diff;

		for (int i = 0; i <= pos_diff; i++)
		{
			HSVColor& color = mColors[position1 + i];
			color.setHue(color1.getHue() + (hue_delta * i));
			color.setSaturation(color1.getSaturation() + (saturation_delta * i));
			color.setValue(color1.getValue() + (value_delta * i));
		}
	}
}
int HSVColorTable::getMaxChannelValue() const
{
	int max_color = 0;
	for (size_t i = 0; i < mColors.size(); i++)
	{
		const HSVColor& color = mColors[i];
		for (int k = 0; k < 3; k++)
			if (color.getChannel(k) > max_color)
				max_color = color.getChannel(k);
	}
	return max_color;
}
