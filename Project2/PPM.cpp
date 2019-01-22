#include "PPM.h"

size_t PPM::sizeOfImage()
{
	return height * width * num_channels * sizeof(byte);
}

PPM::PPM() : height(0), width(0), max_color_value(0) {}
PPM::PPM(const int& height, const int& width) : height(height), width(width), max_color_value(0)
{
	image = new byte[sizeOfImage()];
}
bool PPM::indexValid(const int& row, const int& column, const int& channel) const
{
	return row >= 0 && row < height && column >= 0 && column < width && channel >= 0 && channel < 3;
}
int PPM::index(const int& row, const int& column, const int& channel) const
{
	return channel + column * num_channels + row * width * num_channels;
	//return channel + (row * width * num_channels + column * num_channels);
}
bool PPM::valueValid(const int& value) const
{
	return value <= max_color_value && value >= 0;
}
int PPM::getHeight() const
{
	return height;
}
int PPM::getWidth() const
{
	return width;
}
int PPM::getMaxColorValue() const
{
	return max_color_value;
}
int PPM::getChannel(const int& row, const int& column, const int& channel) const
{
	return (int) image[index(row, column, channel)];
}
void PPM::setHeight(const int& height)
{
	if (height >= 0)
	{
		this->height = height;
		delete image;
		image = new byte[sizeOfImage()];
	}
}
void PPM::setWidth(const int& width)
{
	if (width >= 0)
	{
		this->width = width;
		delete image;
		image = new byte[sizeOfImage()];
	}
}
void PPM::setMaxColorValue(const int& max_color_value)
{
	if (max_color_value >= 0 && max_color_value <= 255)
		this->max_color_value = max_color_value;
}
void PPM::setChannel(const int& row, const int& column, const int& channel, const int& value)
{
	if (valueValid(value) && indexValid(row, column, channel))
		image[index(row, column, channel)] = value;
}
void PPM::setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue)
{
	setChannel(row, column, 0, red);
	setChannel(row, column, 1, green);
	setChannel(row, column, 2, blue);
}
int PPM::size()
{
	return height * width;
}
std::ostream& operator<<(std::ostream& os, const PPM& rhs)
{
	os << "P6 " << rhs.getWidth() << ' ' << rhs.getHeight() << ' ' << rhs.getMaxColorValue() << std::endl;
	for (int i = 0; i < rhs.getHeight(); i++)
		for (int j = 0; j < rhs.getWidth(); j++)
			for (int k = 0; k < 3; k++)
				os << (byte) rhs.getChannel(i, j, k);
	return os;
}
