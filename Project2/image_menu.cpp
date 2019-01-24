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
void writeUserImage(std::istream& is, std::ostream& os, const PPM& p)
{
	std::string filename = getString(is, os, "Output filename? ");
	std::ofstream output(filename);
	output << p;
	output.close();
}
int assignment2(std::istream& is, std::ostream& os)
{
	int height = getInteger(is, os, "Image height? ");	
	int width = getInteger(is, os, "Image width? ");

	PPM ppm = PPM(height, width);
	ppm.setMaxColorValue((height + width) / 3);

	// create image
	int mid_height = height / 2;
	int mid_width = width / 2;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			ppm.setChannel(i, j, 0, i < mid_height ? 0 : ppm.getMaxColorValue());	// r
			ppm.setChannel(i, j, 1, (i + j) % (ppm.getMaxColorValue() + 1));		// g
			ppm.setChannel(i, j, 2, j < mid_width ? 0 : ppm.getMaxColorValue());	// b
		}
	
	writeUserImage(is, os, ppm);
	return 0;
}
