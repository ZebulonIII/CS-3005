#ifndef _PPM_H_
#define _PPM_H_

#include <iostream>
#include <sstream>

class PPM
{
private:
	char* image;
	int height, width, max_color_value;
	const int num_channels = 3;

public:
	PPM();
	PPM(const int& height, const int& width);
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
};

std::ostream& operator<<(std::ostream& os, const PPM& rhs);

#endif // _PPM_H_