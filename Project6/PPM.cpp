#include "PPM.h"
#include <cstring>
#include <algorithm>

// The default constructor. A default PPM has 0 height, 0 width, and max color value of 0.
PPM::PPM() : image(std::vector<byte>()), height(0), width(0), max_color_value(0) {}
// A constructor with parameters for the height and width. The max color value should be set to 0.
PPM::PPM(const int& height, const int& width) : height(height), width(width), max_color_value(0)
{
	initializeImage();
}
PPM::PPM(const PPM& copy)
{
	setHeight(copy.getHeight());
	setWidth(copy.getWidth());
	setMaxColorValue(copy.getMaxColorValue());
	
	for (int i = 0; i < getHeight(); i++)
		for (int j = 0; j < getWidth(); j++)
			for (int k = 0; k < 3; k++)
				setChannel(i, j, k, copy.getChannel(i, j, k));
}
// Returns amount of memory needed to store the image
size_t PPM::sizeOfImage() const
{
	return height * width * num_channels * sizeof(byte);
}
size_t PPM::numPixels() const
{
	return height * width;
}
void PPM::initializeImage()
{
	image = std::vector<byte>(sizeOfImage(), 0);
}
// Checks if row, column and channel are all within the legal limits. Returns true if they all are, and false otherwise.
bool PPM::indexValid(const int& row, const int& column, const int& channel) const
{
	return row >= 0 && row < height && column >= 0 && column < width && channel >= 0 && channel < num_channels;
}
// Returns the index into the channels data for the color channel in the pixel at row, column.
int PPM::index(const int& row, const int& column, const int& channel) const
{
	return channel + column * num_channels + row * width * num_channels;
}
// Checks if value is a legal color value for this image. Returns true if it is legal, false otherwise.
bool PPM::valueValid(const int& value) const
{
	std::cout << value << std::endl;
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
	if (!indexValid(row, column, channel))
	    return -1;
	else
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
		initializeImage();
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
		initializeImage();
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
		image[index(row, column, channel)] = (byte) value;
}
// Set all three channels for the specified pixel. Should use setChannel to do the work.
void PPM::setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue)
{
	setChannel(row, column, 0, red);
	setChannel(row, column, 1, green);
	setChannel(row, column, 2, blue);
}
// Set all three channels for the specified pixel to the same value (used for grayscale)
void PPM::setPixel(const int& row, const int& column, const int& value)
{
	for (int k = 0; k < num_channels; k++)
		setChannel(row, column, k, value);
}
/* Sets dst to have the same meta-data as *this. Sets every pixel in dst to have all channels (Red, Green and Blue) set to
   the value taken from the src_channel of the pixel at the same position of *this. Channel is the channel index (0, 1 or 2)*/
void PPM::grayFromChannel(PPM& dst, const int& src_channel) const
{
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max_color_value);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			dst.setPixel(i, j, getChannel(i, j, src_channel));
}
void PPM::grayFromRed(PPM& dst) const
{
	grayFromChannel(dst, 0);
}
void PPM::grayFromGreen(PPM& dst) const
{
	grayFromChannel(dst, 1);
}
void PPM::grayFromBlue(PPM& dst) const
{
	grayFromChannel(dst, 2);
}
double PPM::linearColorimetricPixelValue(const int& row, const int& column) const
{
	int r, g, b;
	r = getChannel(row, column, 0);
	g = getChannel(row, column, 1);
	b = getChannel(row, column, 2);
	return .2126 * r + .7152 * g + .0722 * b;
}
void PPM::grayFromLinearColorimetric(PPM& dst) const
{
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max_color_value);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			dst.setPixel(i, j, (int)linearColorimetricPixelValue(i, j));
}
void PPM::invert(PPM& dst) const // custom
{
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max_color_value);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < num_channels; k++)
				dst.setChannel(i, j, k, max_color_value - getChannel(i, j, k));
}
// Blur length must be > 0
void PPM::motionBlur(const int& blur_length, PPM& dst) const // custom
{
	if (blur_length < 0)
		return;

	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max_color_value);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			int numPixelsToRight = std::min(width - j, blur_length);
			int r = 0, g = 0, b = 0;
			for (int a = 0; a < numPixelsToRight; a++)
			{
				r += getChannel(i, j + a, 0);
				g += getChannel(i, j + a, 1);
				b += getChannel(i, j + a, 2);
			}
			r /= numPixelsToRight;
			g /= numPixelsToRight;
			b /= numPixelsToRight;

			dst.setPixel(i, j, r, g, b);
		}
}
/*bool PPM::equals(const PPM& rhs) const
{
	if (height != rhs.getHeight()) return false;
	else if (width != rhs.getWidth()) return false;
	else if (max_color_value != rhs.getMaxColorValue()) return false;
	else return std::memcmp(image, rhs.image, sizeOfImage()) == 0;
}*/
PPM& PPM::operator=(const PPM& rhs)
{
	//this->height = rhs.height;
	//this->width = rhs.width;
	//this->max_color_value = rhs.max_color_value;
	//delete[] image;
	//this->image = new byte[sizeOfImage()];
	setHeight(rhs.getHeight());
	setWidth(rhs.getWidth());
	setMaxColorValue(rhs.getMaxColorValue());
	this->image = std::vector<byte>(rhs.image);
	return *this;
}
PPM PPM::operator+ (const PPM& rhs) const
{
	/*PPM temp(height, width);
	temp.setMaxColorValue(max_color_value);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < num_channels; k++)
			{
				int new_value = getChannel(i, j, k) + rhs.getChannel(i, j, k);
				if (new_value > max_color_value)
					new_value = max_color_value;
				temp.setChannel(i, j, k, new_value);
			}
	return temp;*/

	PPM temp;
	temp = *this;
	temp += rhs;
	return temp;
}
PPM& PPM::operator+= (const PPM& rhs)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < num_channels; k++)
			{
				int new_value = getChannel(i, j, k) + rhs.getChannel(i, j, k);
				if (new_value > max_color_value)
					new_value = max_color_value;
				setChannel(i, j, k, new_value);
			}
	return *this;
	/*for (size_t i = 0; i < sizeOfImage(); i++)
	{
		int new_value = image[i] + rhs.image[i];
		if (new_value > max_color_value)
			new_value = max_color_value;
		image[i] = new_value;
	}
	return *this;*/
}
PPM PPM::operator- (const PPM& rhs) const
{
	PPM temp;
	temp = *this;
	temp -= rhs;
	return temp;
}
PPM& PPM::operator-= (const PPM& rhs)
{
	/*for (size_t i = 0; i < sizeOfImage(); i++)
	{
		int new_value = image[i] - rhs.image[i];
		if (new_value < 0)
			new_value = 0;
		image[i] = new_value;
	}
	return *this;*/
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < num_channels; k++)
			{
				int new_value = getChannel(i, j, k) - rhs.getChannel(i, j, k);
				if (new_value < 0)
					new_value = 0;
				setChannel(i, j, k, new_value);
			}
	return *this;
}
// The operator to multiply the values of a PPM object by a double, creating a new PPM object. e.g. ppm3 = ppm1 * 0.67;
PPM PPM::operator* (const double& value) const
{
	PPM ppm;
	ppm = *this;
	ppm *= value;
	return ppm;
}
PPM& PPM::operator*= (const double& value)
{
	/*for (size_t i = 0; i < sizeOfImage(); i++)
	{
		int new_value = image[i] * value;
		if (new_value > max_color_value) new_value = max_color_value;
		else if (new_value < 0) new_value = 0;
		image[i] = new_value;
	}
	return *this;*/
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < num_channels; k++)
			{
				double new_value = getChannel(i, j, k) * value;
				if (new_value > max_color_value) new_value = max_color_value;
				else if (new_value < 0) new_value = 0;
				setChannel(i, j, k, (int)new_value);
			}
	return *this;
}
// The operator to divide the values of a PPM object by a double, creating a new PPM object. e.g. ppm3 = ppm1 / 0.25;
PPM PPM::operator/ (const double& value) const
{
	return *this * (1 / value);
}
/* The operator to divide a PPM object by a double. e.g. ppm1 /= 0.33.
   This operation will cause each channel (red, green, blue) of each pixel to be divided by the number, then converted back to integer.
   If any channel would exceed the maximum color value, set it to the maximum color value. If any channel would become less than 0, set it to 0.*/
PPM& PPM::operator/= (const double& value)
{
	return *this *= (1 / value);
}
// Returns true if *this has the same number of pixels as rhs. Otherwise returns false.
bool PPM::operator== (const PPM& rhs) const
{
	return numPixels() == rhs.numPixels();
}
// Returns true if *this has a different number of pixels than rhs. Otherwise returns false.
bool PPM::operator!= (const PPM& rhs) const
{
	return !(*this == rhs);
}
bool PPM::operator< (const PPM& rhs) const
{
	return numPixels() < rhs.numPixels();
}
bool PPM::operator<= (const PPM& rhs) const
{
	return numPixels() <= rhs.numPixels();
}
bool PPM::operator> (const PPM& rhs) const
{
	return !(*this <= rhs);
}
bool PPM::operator>= (const PPM& rhs) const
{
	return !(*this < rhs);
}
std::ostream& operator<< (std::ostream& os, const PPM& rhs)
{
	os << "P6 " << rhs.getWidth() << ' ' << rhs.getHeight() << ' ' << rhs.getMaxColorValue() << std::endl;
	for (int i = 0; i < rhs.getHeight(); i++)
		for (int j = 0; j < rhs.getWidth(); j++)
			for (int k = 0; k < 3; k++)
				os << (byte) rhs.getChannel(i, j, k);
	return os;
}
std::istream& operator>> (std::istream& is, PPM& rhs)
{
	std::string p6;
	int height, width, max_color_value;
	byte* pixel = new byte[3];

	is >> p6 >> width >> height >> max_color_value;
	is.ignore(); //ignore newline

	rhs.setHeight(height);
	rhs.setWidth(width);
	rhs.setMaxColorValue(max_color_value);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			is.read((char*)pixel, 3);
			rhs.setPixel(i, j, pixel[0], pixel[1], pixel[2]);
		}

	delete[] pixel;
	return is;
}
// Project 6
int PPM::edgePixelValue(const int& row1, const int& column1, const int& row2, const int& column2) const {
	double value1 = linearColorimetricPixelValue(row1, column1);
	double value2 = linearColorimetricPixelValue(row2, column2);

	return (std::abs(value1 - value2) > (.1 * getMaxColorValue())) ? getMaxColorValue() : 0;
}
void PPM::findVerticalEdges(PPM& dst) const {
	dst.setHeight(getHeight());
	dst.setWidth(getWidth());
	dst.setMaxColorValue(getMaxColorValue());

	for (int i = 0; i < getHeight(); i++)
		dst.setPixel(i, 0, 0);

	for (int i = 1; i < getHeight(); i++)
		for (int j = 0; j < getWidth(); j++)
			dst.setPixel(i, j, edgePixelValue(i, j, i - 1, j));
}
void PPM::findHorizontalEdges(PPM& dst) const {
	dst.setHeight(getHeight());
	dst.setWidth(getWidth());
	dst.setMaxColorValue(getMaxColorValue());

	for (int j = 0; j < getWidth(); j++)
		dst.setPixel(0, j, 0);

	for (int i = 0; i < getHeight(); i++)
		for (int j = 1; j < getWidth(); j++)
			dst.setPixel(i, j, edgePixelValue(i, j, i, j - 1));
}
