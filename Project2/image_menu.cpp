#include <string>
#include <iostream>
#include <fstream>
#include "image_menu.h"
#include "PPM.h"

std::string getString(std::istream& is, std::ostream& os, const std::string& prompt)
{
	os << prompt;
	std::string line;
	is >> line;
	return line;
}
int getInteger(std::istream& is, std::ostream& os, const std::string& prompt)
{
	os << prompt;
	int line;
	is >> line;
	return line;
}
double getDouble(std::istream& is, std::ostream& os, const std::string& prompt)
{
	os << prompt;
	double line;
	is >> line;
	return line;
}
int assignment1(std::istream& is, std::ostream& os)
{
	std::string s = getString(is, os, "What's your favorite color? ");
	int integer = getInteger(is, os, "What's your favorite integer? ");
	double d = getDouble(is, os, "What's your favorite number? ");
	for (int i = 1; i <= integer; i++)
		os << i << ' ' << s << ' ' << d << std::endl;
	return integer;
}
int assignment2(std::istream& is, std::ostream& os)
{
	int height = getInteger(is, os, "Image height? ");
	int width = getInteger(is, os, "Image width? ");
	std::string filename = getString(is, os, "Image filename? ");

	PPM ppm = PPM(height, width);
	int max_color_value = (height + width) / 3;
	ppm.setMaxColorValue(max_color_value);

	// initialize pixels
	int channel = 0;
	int mid_height = height / 2;
	int mid_width = width / 2;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			for (int k = 0; k < 3; k++)
			{
				ppm.setChannel(i, j, k, i <= mid_height ? 0 : max_color_value);
				ppm.setChannel(i, j, k, j <= mid_width ? 0 : max_color_value);
				ppm.setChannel(i, j, k, (i + j) % (max_color_value + 1));
			}

	std::ofstream output(filename);
	output << ppm;
	output.close();

	return width * height;
}