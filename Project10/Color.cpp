#include <ostream>
#include "Color.h"

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
		case 0: mRed = value; break;
		case 1: mGreen = value; break;
		case 2: mBlue = value; break;
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
std::ostream& operator<<(std::ostream& os, const Color& color)
{
	os << color.getRed() << ':' << color.getGreen() << ':' << color.getBlue();
	return os;
}