#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "image_menu.h"
#include "PPM.h"

// Project 1
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
// Project 2
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
// Project 3
std::string getChoice(std::istream& is, std::ostream& os)
{
	return getString(is, os, "Choice? ");
}
void commentLine(std::istream& is)
{
	char* buffer = new char[1];
	while (is.read(buffer, 1) && buffer[0] != '\n');
	delete[] buffer;
}
void setSize(std::istream& is, std::ostream& os, PPM& src)
{
	src.setHeight(getInteger(is, os, "Height? "));
	src.setWidth(getInteger(is, os, "Width? "));
}
void setMaxColorValue(std::istream& is, std::ostream& os, PPM& src)
{
	src.setMaxColorValue(getInteger(is, os, "Max color value? "));
}
void setChannel(std::istream& is, std::ostream& os, PPM& src)
{
	int row = getInteger(is, os, "Row? ");
	int col = getInteger(is, os, "Column? ");
	int channel = getInteger(is, os, "Channel? ");
	int value = getInteger(is, os, "Value? ");

	src.setChannel(row, col, channel, value);
}
void setPixel(std::istream& is, std::ostream& os, PPM& src)
{
	int row = getInteger(is, os, "Row? ");
	int col = getInteger(is, os, "Column? ");
	int red = getInteger(is, os, "Red? ");
	int green = getInteger(is, os, "Green? ");
	int blue = getInteger(is, os, "Blue? ");

	src.setPixel(row, col, red, green, blue);
}
void clearAll(PPM& src)
{
	for (int i = 0; i < src.getHeight(); i++)
		for (int j = 0; j < src.getWidth(); j++)
			src.setPixel(i, j, 0, 0, 0);
}
void drawDiamond(std::istream& is, std::ostream& os, PPM& src)
{
	int center_row = getInteger(is, os, "Center Row? ");
	int center_col = getInteger(is, os, "Center Column? ");
	int size = getInteger(is, os, "Size? ");
	int red = getInteger(is, os, "Red? ");
	int green = getInteger(is, os, "Green? ");
	int blue = getInteger(is, os, "Blue? ");

	int lower_i = (center_row - size < 0 ? 0 : center_row - size);
	int upper_i = (center_row + size >= src.getHeight() ? src.getHeight() - 1 : center_row + size);
	int lower_j = (center_col - size < 0 ? 0 : center_col - size);
	int upper_j = (center_col + size >= src.getWidth() ? src.getWidth() - 1 : center_col + size);

	for (int i = lower_i; i <= upper_i; i++)
		for (int j = lower_j; j <= upper_j; j++)
			if (std::abs(i - center_row) + std::abs(j - center_col) <= size)
				src.setPixel(i, j, red, green, blue);
}
void drawCircle(std::istream& is, std::ostream& os, PPM& src)
{
	int center_row = getInteger(is, os, "Center Row? ");
	int center_col = getInteger(is, os, "Center Column? ");
	int radius = getInteger(is, os, "Radius? ");
	int red = getInteger(is, os, "Red? ");
	int green = getInteger(is, os, "Green? ");
	int blue = getInteger(is, os, "Blue? ");

	int lower_i = (center_row - radius < 0 ? 0 : center_row - radius);
	int upper_i = (center_row + radius >= src.getHeight() ? src.getHeight() - 1 : center_row + radius);
	int lower_j = (center_col - radius < 0 ? 0 : center_col - radius);
	int upper_j = (center_col + radius >= src.getWidth() ? src.getWidth() - 1 : center_col + radius);

	for (int i = lower_i; i <= upper_i; i++)
		for (int j = lower_j; j <= upper_j; j++)
			if (std::sqrt(std::pow(i - center_row, 2) + std::pow(j - center_col, 2)) <= radius)
				src.setPixel(i, j, red, green, blue);
}
void drawBox(std::istream& is, std::ostream& os, PPM& src)
{
	int top_row = getInteger(is, os, "Top Row? ");
	int left_col = getInteger(is, os, "Left Column? ");
	int bot_row = getInteger(is, os, "Bottom Row? ");
	int right_col = getInteger(is, os, "Right Column? ");
	int red = getInteger(is, os, "Red? ");
	int green = getInteger(is, os, "Green? ");
	int blue = getInteger(is, os, "Blue? ");

	for (int i = top_row; i <= bot_row; i++)
		for (int j = left_col; j <= right_col; j++)
			src.setPixel(i, j, red, green, blue);
}
int imageMenu(std::istream& is, std::ostream& os)
{
	PPM input_image1 = PPM();
	PPM input_image2 = PPM();
	PPM output_image = PPM();
	std::string choice;
	std::stringstream ss;
	bool quiet = false;

	do {
		if (quiet) {
			choice = getChoice(is, ss);
			takeAction(is, ss, choice, input_image1, input_image2, output_image);
		}
		else {
			showMenu(os);
			choice = getChoice(is, os);
			takeAction(is, os, choice, input_image1, input_image2, output_image);
		}		

		if (choice == "quiet")
			quiet = !quiet;
	} while (choice != "quit");
	return 0;
}
// Project 4
void readUserImage(std::istream& is, std::ostream& os, PPM& ppm)
{
	std::string filename = getString(is, os, "Input filename? ");
	std::ifstream ifs(filename);
	ifs >> ppm;
	ifs.close();
}
// Project 5
void showMenu(std::ostream& os)
{
	os << "\nActions available:\n\n"
		"read1) Read file into input image 1.\n"
		"read2) Read file into input image 2.\n"
		"write) Write output image to file.\n"
		"copy) Copy input image 1 to output image.\n"
		"red-gray) Set output image from input image 1's grayscale from red.\n"
		"green-gray) Set output image from input image 1's grayscale from green.\n"
		"blue-gray) Set output image from input image 1's grayscale from blue.\n"
		"linear-gray) Set output image from input image 1's grayscale from linear colorimetric.\n"
		"+) Set output image from sum of input image 1 and input image 2\n"
		"+=) Set input image 1 by adding in input image 2\n"
		"-) Set output image from difference of input image 1 and input image 2\n"
		"-=) Set input image 1 by subtracting input image 2\n"
		"*) Set output image from input image 1 multiplied by a number\n"
		"*=) Set input image 1 by multiplying by a number\n"
		"/) Set output image from input image 1 divided by a number\n"
		"/=) Set input image 1 by dividing by a number\n"
		"# Comment to end of line\n"
		"size) Set the size of input image 1\n"
		"max) Set the max color value of input image 1\n"
		"channel) Set a channel value in input image 1\n"
		"pixel) Set a pixel's 3 values in input image 1\n"
		"clear) Set all pixels to 0,0,0 in input image 1\n"
		"diamond) Draw a diamond shape in input image 1\n"
		"circle) Draw a circle shape in input image 1\n"
		"box) Draw a box shape in input image 1\n"
		"v-edge) Set output image from input image 1's vertical edge detection.\n"
		"h-edge) Set output image from input image 1's horizontal edge detection.\n"
		"quiet) Toggle output quieting.\n"
		"run) Run commands from another file.\n"
		"quit) Quit\n\n";
}
void takeAction(std::istream& is, std::ostream& os, const std::string& choice, PPM& input_image1, PPM& input_image2, PPM& output_image)
{
	if (choice == "read1")
		readUserImage(is, os, input_image1);
	else if (choice == "read2")
		readUserImage(is, os, input_image2);
	else if (choice == "write")
		writeUserImage(is, os, output_image);
	else if (choice == "copy")
		output_image = input_image1;
	else if (choice == "red-gray")
		input_image1.grayFromRed(output_image);
	else if (choice == "green-gray")
		input_image1.grayFromGreen(output_image);
	else if (choice == "blue-gray")
		input_image1.grayFromBlue(output_image);
	else if (choice == "linear-gray")
		input_image1.grayFromLinearColorimetric(output_image);
	else if (choice == "invert") // custom
		input_image1.invert(output_image);
	else if (choice == "motionblur") // custom
		input_image1.motionBlur(getInteger(is, os, "How much blur? "), output_image);
	/*else if (choice == "equals") // custom
		os << (input_image1.equals(input_image2) ? "Equal\n" : "Not Equal\n");*/
	else if (choice == "+")
		plus(is, os, input_image1, input_image2, output_image);
	else if (choice == "+=")
		plusEquals(is, os, input_image1, input_image2);
	else if (choice == "-")
		minus(is, os, input_image1, input_image2, output_image);
	else if (choice == "-=")
		minusEquals(is, os, input_image1, input_image2);
	else if (choice == "*")
		times(is, os, input_image1, output_image);
	else if (choice == "*=")
		timesEquals(is, os, input_image1);
	else if (choice == "/")
		divide(is, os, input_image1, output_image);
	else if (choice == "/=")
		divideEquals(is, os, input_image1);
	else if (choice[0] == '#')
		commentLine(is);
	else if (choice == "size")
		setSize(is, os, input_image1);
	else if (choice == "max")
		setMaxColorValue(is, os, input_image1);
	else if (choice == "channel")
		setChannel(is, os, input_image1);
	else if (choice == "pixel")
		setPixel(is, os, input_image1);
	else if (choice == "clear")
		clearAll(input_image1);
	else if (choice == "diamond")
		drawDiamond(is, os, input_image1);
	else if (choice == "circle")
		drawCircle(is, os, input_image1);
	else if (choice == "box")
		drawBox(is, os, input_image1);
	else if (choice == "v-edge")
		input_image1.findVerticalEdges(output_image);
	else if (choice == "h-edge")
		input_image1.findHorizontalEdges(output_image);
	else if (choice == "quiet")
		return;
	else if (choice == "run")
		runFile(is, os, input_image1, input_image2, output_image);
	else if (choice == "quit")
		return;
	else
		os << "Unkown action '" << choice << "'.\n";
}
void plus(std::istream& is, std::ostream& os, const PPM& src1, const PPM& src2, PPM& dst)
{
	(void) is;
	(void) os;
	dst = (src1 + src2);
}
void plusEquals(std::istream& is, std::ostream& os, PPM& src1, const PPM& src2 )
{
	(void) is;
	(void) os;
	src1 += src2;
}
void minus(std::istream& is, std::ostream& os, const PPM& src1, const PPM& src2, PPM& dst)
{
	(void) is;
	(void) os;
	dst = (src1 - src2);
}
void minusEquals(std::istream& is, std::ostream& os, PPM& src1, const PPM& src2)
{
	(void) is;
	(void) os;
	src1 -= src2;
}
void times(std::istream& is, std::ostream& os, const PPM& src, PPM& dst)
{
	dst = src * getDouble(is, os, "Factor? ");
}
void timesEquals(std::istream& is, std::ostream& os, PPM& src)
{
	src *= getDouble(is, os, "Factor? ");
}
void divide(std::istream& is, std::ostream& os, const PPM& src, PPM& dst)
{
	dst = src / getDouble(is, os, "Factor? ");
}
void divideEquals(std::istream& is, std::ostream& os, PPM& src)
{
	src /= getDouble(is, os, "Factor? ");
}
// Project 6
int runFile(std::istream& is, std::ostream& os, PPM& input_image1, PPM& input_image2, PPM& output_image) {
	std::ifstream ifs(getString(is, os, "File? "));
	std::stringstream ss;
	std::string choice = "";

	while (choice != "quit" && ifs.good()) {
		choice = getChoice(ifs, ss);
		takeAction(ifs, ss, choice, input_image1, input_image2, output_image);
	}
	return 0;
}
