#include "PPM.h"

// Returns amount of memory needed to store the image
size_t PPM::sizeOfImage()
{
	return height * width * num_channels * sizeof(byte);
}
// The default constructor. A default PPM has 0 height, 0 width, and max color value of 0.
PPM::PPM() : height(0), width(0), max_color_value(0), image(NULL) {}
// A constructor with parameters for the height and width. The max color value should be set to 0.
PPM::PPM(const int& height, const int& width) : height(height), width(width), max_color_value(0)
{
	image = new byte[sizeOfImage()];
}
PPM::~PPM()
{
	if (image != NULL)
		delete image;
}
// Checks if row, column and channel are all within the legal limits. Returns true if they all are, and false otherwise.
bool PPM::indexValid(const int& row, const int& column, const int& channel) const
{
	return row >= 0 && row < height && column >= 0 && column < width && channel >= 0 && channel < 3;
}
// Returns the index into the channels data for the color channel in the pixel at row, column.
int PPM::index(const int& row, const int& column, const int& channel) const
{
	return channel + column * num_channels + row * width * num_channels;
	//return channel + (row * width * num_channels + column * num_channels);
}
// Checks if value is a legal color value for this image. Returns true if it is legal, false otherwise.
bool PPM::valueValid(const int& value) const
{
	return value <= max_color_value && value >= 0;
}
// Returns the height of the PPM.
int PPM::getHeight() const
{
	return height;
}
// Returns the width of the PPM.
int PPM::getWidth() const
{
	return width;
}
// Returns the maximum color value of the PPM.
int PPM::getMaxColorValue() const
{
	return max_color_value;
}
// Returns an int representation of the color channel and pixel specified. Returns -1 if the channel or pixel is not valid.
int PPM::getChannel(const int& row, const int& column, const int& channel) const
{
	return (int) image[index(row, column, channel)];
}
/* Change the height of the PPM. The state of any new or existing pixels after this call is undetermined.
   Only non-negative values should be accepted. If the value is not accepted, make no changes.
   If a change is made, be sure to resize the channel vector. */
void PPM::setHeight(const int& height)
{
	if (height >= 0)
	{
		this->height = height;
		delete image;
		image = new byte[sizeOfImage()];
	}
}
/* Change the width of the PPM. The state of any new or existing pixels after this call is undetermined.
   Only non-negative values should be accepted. If the value is not accepted, make no changes.
   If a change is made, be sure to resize the channel vector. */
void PPM::setWidth(const int& width)
{
	if (width >= 0)
	{
		this->width = width;
		delete image;
		image = new byte[sizeOfImage()];
	}
}
/* Change the maximum color value of the PPM. Only values 0 to 255, inclusive should be accepted.
   If the value is not accepted, make no changes. */
void PPM::setMaxColorValue(const int& max_color_value)
{
	if (max_color_value >= 0 && max_color_value <= 255)
		this->max_color_value = max_color_value;
}
/* Change the value of the specified pixel and channel. Only valid pixel, channel and values should be accepted.
   If any of these is not valid, no changes should be made.*/
void PPM::setChannel(const int& row, const int& column, const int& channel, const int& value)
{
	if (valueValid(value) && indexValid(row, column, channel))
		image[index(row, column, channel)] = value;
}
// Set all three channels for the specified pixel. Should use setChannel to do the work.
void PPM::setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue)
{
	setChannel(row, column, 0, red);
	setChannel(row, column, 1, green);
	setChannel(row, column, 2, blue);
}
// Return number of pixels in image
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
