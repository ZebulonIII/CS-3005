#include "PPM.h"
#include "ThreadedVector.h"
#include <cstring>
#include <algorithm>
#include <cmath>
#include <thread>

// The default constructor. A default PPM has 0 height, 0 width, and max color value of 0.
PPM::PPM() :
	image(std::vector<byte>()), height(0), width(0), max_color_value(0), mNumThreads(std::thread::hardware_concurrency() - 1) {}
// A constructor with parameters for the height and width. The max color value should be set to 0.
PPM::PPM(const int& height, const int& width) :
	height(height), width(width), max_color_value(0), mNumThreads(std::thread::hardware_concurrency() - 1)
{
	initializeImage();
}
PPM::PPM(const PPM& copy)
{
	image = copy.image;
	height = copy.height;
	width = copy.width;
	max_color_value = copy.max_color_value;
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
int PPM::edgePixelValue(const int& row1, const int& column1, const int& row2, const int& column2) const
{
	double v1 = linearColorimetricPixelValue(row1, column1);
	double v2 = linearColorimetricPixelValue(row2, column2);
	if (std::abs(v1 - v2) > (max_color_value * 0.1))
		return max_color_value;
	else
		return 0;
}
void PPM::findHorizontalEdges(PPM& dst) const
{
	dst = PPM(getHeight(), getWidth());
	dst.setMaxColorValue(getMaxColorValue());

	for (int i = 1; i < getHeight() - 1; i++)
		for (int j = 0; j < getWidth() - 1; j++)
			dst.setPixel(i, j, edgePixelValue(i, j, i + 1, j + 1));
}
void PPM::findVerticalEdges(PPM& dst) const
{
	dst = PPM(getHeight(), getWidth());
	dst.setMaxColorValue(getMaxColorValue());

	for (int i = 0; i < getHeight(); i++)
		for (int j = 1; j < getWidth(); j++)
			dst.setPixel(i, j, edgePixelValue(i, j, i + 1, j + 1));
}
void PPM::drawDiamond(const int& row, const int& col, const int& size, const int& r, const int& g, const int& b)
{
	int lower_i = (row - size < 0 ? 0 : row - size);
	int upper_i = (row + size >= getHeight() ? getHeight() - 1 : row + size);
	int lower_j = (col - size < 0 ? 0 : col - size);
	int upper_j = (col + size >= getWidth() ? getWidth() - 1 : col + size);

	for (int i = lower_i; i <= upper_i; i++)
		for (int j = lower_j; j <= upper_j; j++)
			if (std::abs(i - row) + std::abs(j - col) <= size)
				setPixel(i, j, r, g, b);
}
void PPM::drawCircle(const int& row, const int& col, const int& radius, const int& r, const int& g, const int& b)
{
	int lower_i = (row - radius < 0 ? 0 : row - radius);
	int upper_i = (row + radius >= getHeight() ? getHeight() - 1 : row + radius);
	int lower_j = (col - radius < 0 ? 0 : col - radius);
	int upper_j = (col + radius >= getWidth() ? getWidth() - 1 : col + radius);

	for (int i = lower_i; i <= upper_i; i++)
		for (int j = lower_j; j <= upper_j; j++)
			if (std::sqrt(std::pow(i - row, 2) + std::pow(j - col, 2)) <= radius)
				setPixel(i, j, r, g, b);
}
void PPM::drawBox(const int& tr, const int& lc, const int& br, const int& rc, const int& r, const int& g, const int& b)
{
	for (int i = tr; i <= br; i++)
		for (int j = lc; j <= rc; j++)
			setPixel(i, j, r, g, b);
}
void PPM::invert(PPM& dst) // custom
{
	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max_color_value);

	mWorkQueue.resize(height);
	for (int i = 0; i < height; i++)
		mWorkQueue.push_back(i);

	std::thread threads[mNumThreads];
	for (unsigned int i = 0; i < mNumThreads; i++)
		threads[i] = std::thread(&PPM::worker_invert, this, std::ref(dst));

	for (unsigned int i = 0; i < mNumThreads; i++)
		threads[i].join();
}
void PPM::worker_invert(PPM& dst)
{
	std::vector<int> work(1);
	while (!mWorkQueue.empty())
	{
		mWorkQueue.pop_back(work, 1);
		int i = work[0];
		for (int j = 0; j < width; j++)
			for (int k = 0; k < num_channels; k++)
				dst.setChannel(i, j, k, max_color_value - getChannel(i, j, k));
		work.clear();
	}
}
// Blur length must be > 0
void PPM::motionBlur(const int& blur_length, PPM& dst) // custom
{
	if (blur_length < 0)
		return;

	dst.setHeight(height);
	dst.setWidth(width);
	dst.setMaxColorValue(max_color_value);

	mWorkQueue.resize(height);
	for (int i = 0; i < height; i++)
		mWorkQueue.push_back(i);

	std::thread threads[mNumThreads];
	for (unsigned int i = 0; i < mNumThreads; i++)
		threads[i] = std::thread(&PPM::worker_motionblur, this, std::ref(blur_length), std::ref(dst));

	for (unsigned int i = 0; i < mNumThreads; i++)
		threads[i].join();
}
void PPM::worker_motionblur(const int& blur_length, PPM& dst)
{
	std::vector<int> work(1);
	while (!mWorkQueue.empty())
	{
		mWorkQueue.pop_back(work, 1);
		int i = work[0];
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
		work.clear();
	}
}
bool PPM::equals(const PPM& rhs) const
{
	if (height != rhs.getHeight()) return false;
	else if (width != rhs.getWidth()) return false;
	else if (max_color_value != rhs.getMaxColorValue()) return false;
	else return image == rhs.image;
}
PPM& PPM::operator=(const PPM& rhs)
{
	setHeight(rhs.getHeight());
	setWidth(rhs.getWidth());
	setMaxColorValue(rhs.getMaxColorValue());
	this->image = std::vector<byte>(rhs.image);
	return *this;
}
PPM PPM::operator+ (const PPM& rhs) const
{
	PPM temp;
	temp = *this;
	temp += rhs;
	return temp;
}
PPM& PPM::operator+= (const PPM& rhs)
{
	mWorkQueue.resize(height);
	for (int i = 0; i < height; i++)
		mWorkQueue.push_back(i);

	std::thread threads[mNumThreads];
	for (unsigned int i = 0; i < mNumThreads; i++)
		threads[i] = std::thread(&PPM::workerPE, this, std::ref(rhs));

	for (unsigned int i = 0; i < mNumThreads; i++)
		threads[i].join();

	return *this;
}
void PPM::workerPE(const PPM& rhs)
{
	std::vector<int> work(1);
	while (!mWorkQueue.empty())
	{
		mWorkQueue.pop_back(work, 1);
		int i = work[0];
		for (int j = 0; j < width; j++)
			for (int k = 0; k < num_channels; k++)
			{
				int new_value = getChannel(i, j, k) + rhs.getChannel(i, j, k);
				if (new_value > max_color_value)
					new_value = max_color_value;
				setChannel(i, j, k, new_value);
			}
		work.clear();
	}
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
	mWorkQueue.resize(height);
	for (int i = 0; i < height; i++)
		mWorkQueue.push_back(i);

	std::thread threads[mNumThreads];
	for (unsigned int i = 0; i < mNumThreads; i++)
		threads[i] = std::thread(&PPM::workerME, this, std::ref(rhs));

	for (unsigned int i = 0; i < mNumThreads; i++)
		threads[i].join();

	return *this;
}
void PPM::workerME(const PPM& rhs)
{
	std::vector<int> work;
	while (!mWorkQueue.empty())
	{
		mWorkQueue.pop_back(work, 1);
		int i = work[0];
		for (int j = 0; j < width; j++)
			for (int k = 0; k < num_channels; k++)
			{
				int new_value = getChannel(i, j, k) - rhs.getChannel(i, j, k);
				if (new_value < 0)
					new_value = 0;
				setChannel(i, j, k, new_value);
			}
		work.clear();
	}
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
	mWorkQueue.resize(height);
	for (int i = 0; i < height; i++)
		mWorkQueue.push_back(i);

	std::thread threads[mNumThreads];
	for (unsigned int i = 0; i < mNumThreads; i++)
		threads[i] = std::thread(&PPM::workerTE, this, std::ref(value));
	
	for (unsigned int i = 0; i < mNumThreads; i++)
		threads[i].join();
	
	return *this;
}
void PPM::workerTE(const double& value)
{
	std::vector<int> work(1);
	while (!mWorkQueue.empty())
	{
		mWorkQueue.pop_back(work, 1);
		int i = work[0];
		for (int j = 0; j < width; j++)
			for (int k = 0; k < num_channels; k++)
			{
				double new_value = getChannel(i, j, k) * value;
				if (new_value > max_color_value) new_value = max_color_value;
				else if (new_value < 0) new_value = 0;
				setChannel(i, j, k, (int)new_value);
			}
		work.clear();
	}
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
