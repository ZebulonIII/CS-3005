#ifndef _PPM_H_
#define _PPM_H_

#include <iostream>
#include <sstream>

using byte = unsigned char;

class PPM
{
private:
	byte* image;
	int height, width, max_color_value;
	const int num_channels = 3;

public:
	PPM();
	PPM(const int& height, const int& width);
	~PPM();
	size_t sizeOfImage();
	bool indexValid(const int& row, const int& column, const int& channel) const;
	int index(const int& row, const int& column, const int& channel) const;
	bool valueValid(const int& value) const;
	int getHeight() const;
	int getWidth() const;
	int getMaxColorValue() const;
	int getChannel(const int& row, const int& column, const int& channel) const;
	void setHeight(const int& height);
	void setWidth(const int& width);
	void setMaxColorValue(const int& max_color_value);
	void setChannel(const int& row, const int& column, const int& channel, const int& value);
	void setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue);
	void setPixel(const int& row, const int& column, const int& value);
	void grayFromChannel(PPM& dst, const int& src_channel) const;
	void grayFromRed(PPM& dst) const;
	void grayFromGreen(PPM& dst) const;
	void grayFromBlue(PPM& dst) const;
	double linearColorimetricPixelValue(const int& row, const int& column) const;
	void grayFromLinearColorimetric(PPM& dst) const;
	void invert(PPM& dst) const; // custom
	void motionBlur(const int& blur_length, PPM& dst) const; // custom
	PPM& operator= (const PPM& rhs);
	PPM operator+ (const PPM& ppm_object) const;
	PPM& operator+= (const PPM& ppm_object);
	PPM operator- (const PPM& ppm_object) const;
	PPM& operator-= (const PPM& ppm_object);	
	PPM operator* (const double& value) const;
	PPM& operator*= (const double& value);
	PPM operator/ (const double& value) const;
	PPM& operator/= (const double& value);
	bool operator== (const PPM& ppm_object) const;
	bool operator!= (const PPM& ppm_object) const;	
};

std::ostream& operator<< (std::ostream& os, const PPM& rhs);
std::istream& operator>> (std::istream& is, PPM& rhs);

#endif // _PPM_H_
