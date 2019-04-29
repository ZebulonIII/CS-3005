#include <vector>
#include <cstdlib>
#include <ostream>
#include <cmath>
#include "ColorTable.h"

// Color
Color::Color() : mRed(0), mGreen(0), mBlue(0) {}
Color::Color(const int& red, const int& green, const int& blue) : mRed(red), mGreen(green), mBlue(blue) {}
int Color::getRed() const
{
	return mRed;
}
int Color::getGreen() const
{
	return mGreen;
}
int Color::getBlue() const
{
	return mBlue;
}
int Color::getChannel(const int& channel) const
{
	switch (channel)
	{
		case 0: return mRed;
		case 1: return mGreen;
		case 2: return mBlue;
		default: return -1;
	}
}
void Color::setRed(const int& value)
{
	if (value >= 0)
		mRed = value;
}
void Color::setGreen(const int& value)
{
	if (value >= 0)
		mGreen = value;
}
void Color::setBlue(const int& value)
{
	if (value >= 0)
		mBlue = value;
}
void Color::setChannel(const int& channel, const int& value)
{
	if (value >= 0)
		switch (channel)
		{
			case 0: setRed(value); break;
			case 1: setGreen(value); break;
			case 2: setBlue(value); break;
			default: break;
		}
}
void Color::invert(const int& max_color_value)
{
	if (max_color_value >= mRed && max_color_value >= mGreen && max_color_value >= mBlue)
	{
		mRed = max_color_value - mRed;
		mGreen = max_color_value - mGreen;
		mBlue = max_color_value - mBlue;
	}
}
bool Color::operator== (const Color& rhs) const
{
	return mRed == rhs.getRed() && mGreen == rhs.getGreen() && mBlue == rhs.getBlue();
}
int Color::getMaxColorValue() const // custom
{
	int max = (mRed > mGreen) ? mRed : mGreen;
	return (mBlue > max) ? mBlue : max;
}
void Color::setFromHSV(const double& hue, const double& saturation, const double& value) {
	double C = value * saturation;
	double m = value - C;
	double H = hue / 60;
	double X = C * (1 - std::abs(std::fmod(H, 2) - 1));
	double r, g, b;

	if (H >= 0 && H <= 1) {
		r = C; g = X; b = 0;
	}
	else if (H > 1 && H <= 2) {
		r = X; g = C; b = 0;
	}
	else if (H > 2 && H <= 3) {
		r = 0; g = C; b = X;
	}
	else if (H > 3 && H <= 4) {
		r = 0; g = X; b = C;
	}
	else if (H > 4 && H <= 5) {
		r = X; g = 0; b = C;
	}
	else if (H > 5 && H <= 6) {
		r = C; g = 0; b = X;
	}
	else {
		r = g = b = 0;
	}

	mRed = (r + m) * 255;
	mGreen = (g + m) * 255;
	mBlue = (b + m) * 255;
}
std::ostream& operator<<(std::ostream& os, const Color& color)
{
	os << color.getRed() << ':' << color.getGreen() << ':' << color.getBlue();
	return os;
}

// ColorTable
ColorTable::ColorTable(const size_t& num_color)
{
	mColors = std::vector<Color>(num_color);
}
ColorTable::~ColorTable() {}
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
	if (position < mColors.size() && max_color_value >= 0)
	{
		Color& color = mColors[position];
		for (int i = 0; i < 3; i++)
			color.setChannel(i, std::rand() % (max_color_value + 1));
	}
}
void ColorTable::insertGradient(const Color& color1, const Color& color2, const size_t& position1, const size_t& position2)
{
	if (position2 > position1 &&position1 < getNumberOfColors() && position2 < getNumberOfColors())
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
void ColorTable::insertHSVGradient(const double& h1, const double& s1, const double& v1, const double& h2, const double& s2, const double& v2, const size_t& position1, const size_t& position2) {
	Color color1;
	color1.setFromHSV(h1, s1, v1);
	Color color2;
	color2.setFromHSV(h2, s2, v2);

	insertGradient(color1, color2, position1, position2);
}
