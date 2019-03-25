#include <vector>
#include "HSVColorTable.h"

// HSVColor
HSVColor::HSVColor() : mHue(0.0), mSaturation(0.0), mValue(0.0) {}
HSVColor::HSVColor(const int& hue, const double& saturation, const double& value)
	: mHue(hue), mSaturation(saturation), mValue(value) {}
HSVColor::HSVColor(const Color& color)
{
	HSVColor hsv = RGBtoHSV(color);
	mHue = hsv.getHue();
	mSaturation = hsv.getSaturation();
	mValue = hsv.getValue();
}
int HSVColor::getHue() const
{
	return mHue;
}
double HSVColor::getSaturation() const
{
	return mSaturation;
}
double HSVColor::getValue() const
{
	return mValue;
}
double HSVColor::getChannel(const int& channel) const
{
	switch (channel)
	{
		case 0: return getHue();
		case 1: return getSaturation();
		case 2: return getValue();
		default: return 0.0;
	}
}
void HSVColor::setHue(const int& hue)
{
	if (hue >= 0 && hue <= 360)
		mHue = hue;
}
void HSVColor::setSaturation(const double& saturation)
{
	if (saturation >= 0.0 && saturation <= 1.0)
		mSaturation = saturation;
}
void HSVColor::setValue(const double& value)
{
	if (value >= 0.0 && value <= 1.0)
		mValue = value;
}
void HSVColor::setChannel(const int& channel, const double& amount)
{
	switch (channel)
	{
		case 0: setHue(amount); break;
		case 1: setSaturation(amount); break;
		case 2: setValue(amount); break;
		default: break;
	}
}
void HSVColor::invert()
{
	Color rgb = toRGB();
	rgb.invert(255);
	HSVColor hsv = RGBtoHSV(rgb);
	mHue = hsv.getHue();
	mSaturation = hsv.getSaturation();
	mValue = hsv.getValue();
}
Color HSVColor::toRGB() const
{
	return HSVtoRGB(mHue, mSaturation, mValue);
}
Color HSVColor::HSVtoRGB(const int& hue, const double& saturation, const double& value)
{
	double C = value * saturation;
	double X = C * (1 - std::abs(((hue / 60) % 2) - 1));
	double m = value - C;

	double r, g, b;
	if (hue < 60) {
		r = C; g = X, b = 0;
	}
	else if (hue < 120) {
		r = X, g = C, b = 0;
	}
	else if (hue < 180) {
		r = 0; g = C; b = X;
	}
	else if (hue < 240) {
		r = 0; g = X; b = C;
	}
	else if (hue < 300) {
		r = X, g = 0; b = C;
	}
	else {
		r = C; g = 0; b = X;
	}

	int red = (r + m) * 255;
	int green = (g + m) * 255;
	int blue = (b + m) * 255;

	return Color(red, green, blue);
}
HSVColor HSVColor::RGBtoHSV(const int& red, const int& green, const int& blue)
{
	double r = red / 255.;
	double g = green / 255.;
	double b = blue / 255.;

	double Cmax = maximum<double>(r, g, b);
	double Cmin = minimum<double>(r, g, b);
	double delta = Cmax - Cmin;

	double hue;
	if (delta == 0.0)
		hue = 0.0;
	else if (Cmax == r)
		hue = 60 * ((int)((g - b) / delta) % 6);
	else if (Cmax == g)
		hue = 60 * ((b - r) / delta + 2);
	else if (Cmax == b)
		hue = 60 * ((r - g) / delta + 4);
	else
		hue = -1;
	double saturation = (Cmax == 0) ? 0 : delta / Cmax;
	double value = Cmax;

	return HSVColor(hue, saturation, value);
}
HSVColor HSVColor::RGBtoHSV(const Color& color)
{
	return RGBtoHSV(color.getRed(), color.getBlue(), color.getBlue());
}
bool HSVColor::operator== (const HSVColor& color) const
{
	return mHue == color.getHue() && mSaturation == color.getSaturation() && mValue == color.getValue();
}
bool HSVColor::operator== (const Color& color) const
{
	return color == toRGB();
}
std::ostream& operator<< (std::ostream& os, const HSVColor& color)
{
	//std::setprecision(3);
	os << color.getHue() << ':' << color.getSaturation() << ':' << color.getValue();
	return os;
}

// HSVColorTable
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
	if (i < 0 || i >= (int)mColors.size())
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
	if (i < 0 || i >= (int)mColors.size())
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
