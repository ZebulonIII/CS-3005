#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "image_menu.h"
#include "PPM.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include "ColorTable.h"
#include "TuringPattern.h"

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
	/* srand with seeds at 100 mirocsecond (us) resolution */
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration   dur = now.time_since_epoch();
	std::chrono::microseconds us = std::chrono::duration_cast<std::chrono::microseconds> (dur);
	std::srand(us.count() / 100);

	PPM input_image1 = PPM();
	PPM input_image2 = PPM();
	PPM output_image = PPM();
	NumberGrid* gptr = new JuliaSet();
	ColorTable table = ColorTable(16);
	table.insertGradient(Color(0, 255, 0), Color(255, 0, 255), 0, 15);
	std::string choice;

	do {
		showMenu(os);
		choice = getChoice(is, os);
		takeAction(is, os, choice, input_image1, input_image2, output_image, *gptr, table);
		if (choice == "julia")
			setJuliaFractal(is, os, gptr);
		else if (choice == "mandelbrot")
			setMandelbrotFractal(is, os, gptr);
		else if (choice == "turing")
			setTuringPattern(is, os, gptr);
		else if (choice == "julia-five")
			setJuliaSetFiveFractal(is, os, gptr);
	} while (choice != "quit");

	if (gptr != nullptr)
		delete gptr;

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
		"invert) Set output image from inverted input image 1.\n"
		"motionblur) Set output image from motionblurred input image 1.\n"
		"horizontal-edges) Set output image from edge detection of input image 1.\n"
		"vertical-edges) Set output image from edge detection of input image 1.\n"
		"equals) Determine if input image 1 and input image 2 contain the same data.\n"
		"+) Set output image from sum of input image 1 and input image 2\n"
		"+=) Set input image 1 by adding in input image 2\n"
		"-) Set output image from difference of input image 1 and input image 2\n"
		"-=) Set input image 1 by subtracting input image 2\n"
		"*) Set output image from input image 1 multiplied by a number\n"
		"*=) Set input image 1 by multiplying by a number\n"
		"/) Set output image from input image 1 divided by a number\n"
		"/=) Set input image 1 by dividing by a number\n"
		"grid) Configure the grid.\n"
		"grid-set) Set a single value in the grid.\n"
		"grid-apply) Use the grid values to set colors in the output image.\n"
		"grid-circle) Set values in the grid in the shape of a circle.\n"
		"grid-diamond) Set values in the grid in the shape of a diamond.\n"
		"grid-box) Set values in the grid in the shape of a box.\n"
		"julia) Choose to make a Julia set.\n"
		"mandelbrot) Choose to make a Mandelbrot set.\n"
		"fractal-plane-size) Set the dimensions of the grid in the complex plane.\n"
		"fractal-calculate) Calculate the escape values for the fractal.\n"
		"julia-parameters) Set the parameters of the Julia Set function.\n"
		"zoom) Zoom on center of Complex Fractal plane (< 1 zoom in, > 1 zoom out).\n"
		"left) Translate Complex Fractal plane to the left.\n"
		"right) Translate Complex Fractal plane to the right.\n"
		"up) Translate Complex Fractal plane up.\n"
		"down) Translate Complex Fractal plane down.\n"
		"grid-apply-color-table) Use the grid values to set colors in the output image using the color table.\n"
		"set-color-table-size) Change the number of slots in the color table.\n"
		"set-color) Set the RGB values for one slot in the color table.\n"
		"set-random-color) Randomly set the RGB values for one slot in the color table.\n"
		"set-color-gradient) Smoothly set the RGB values for a range ofn  slots in the color table.\n"
		"fractal-calculate-single-thread) Calculate fractal with only a single thread.\n"
		"turing) Choose to make a Turing pattern.\n"
		"turing-parameters) Set the parameters of the Turing pattern.\n"
		"turing-randomize) Randomize the chemical species concentrations.\n"
		"turing-update) Update the chemical species concentrations.\n"
		"turing-calculate) Calculate the grid numbers for Turing pattern.\n"
		"threads) Set the number of threads to use.\n"
		"set-hsv-color-gradient) Smoothly set the values for a range of slots in the color table, using HSV input values.\n"
		"julia-five) Choose to make a Julia set with the fifth power function.\n"
		"# Comment to end of line\n"
		"size) Set the size of input image 1\n"
		"max) Set the max color value of input image 1\n"
		"channel) Set a channel value in input image 1\n"
		"pixel) Set a pixel's 3 values in input image 1\n"
		"clear) Set all pixels to 0,0,0 in input image 1\n"
		"diamond) Draw a diamond shape in input image 1\n"
		"circle) Draw a circle shape in input image 1\n"
		"box) Draw a box shape in input image 1\n"
		"quit) Quit\n\n";
}
void takeAction(std::istream& is, std::ostream& os, const std::string& choice, PPM& input_image1, PPM& input_image2, PPM& output_image, NumberGrid& grid, ColorTable& table)
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
	else if (choice == "equals") // custom
		os << (input_image1.equals(input_image2) ? "Equal\n" : "Not Equal\n");
	else if (choice == "horizontal-edges") // custom
		horizontalEdges(input_image1, output_image);
	else if (choice == "vertical-edges") //custom
		verticalEdges(input_image1, output_image);
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
	else if (choice == "grid")
		configureGrid(is, os, grid);
	else if (choice == "grid-set")
		setGrid(is, os, grid);
	else if (choice == "grid-apply")
		applyGrid(is, os, grid, output_image);
	else if (choice == "grid-circle")
		drawCircle(is, os, grid);
	else if (choice == "grid-diamond")
		drawDiamond(is, os, grid);
	else if (choice == "grid-box")
		drawBox(is, os, grid);
	else if (choice == "julia")
		return;
	else if (choice == "mandelbrot")
		return;
	else if (choice == "fractal-plane-size")
		setFractalPlaneSize(is, os, grid);
	else if (choice == "fractal-calculate")
		calculateFractal(is, os, grid);
	else if (choice == "julia-parameters")
		setJuliaParameters(is, os, grid);
	else if (choice == "zoom")
		zoom(is, os, grid);
	else if (choice == "left")
		left(is, os, grid);
	else if (choice == "right")
		right(is, os, grid);
	else if (choice == "up")
		up(is, os, grid);
	else if (choice == "down")
		down(is, os, grid);
	else if (choice == "grid-apply-color-table")
		applyGridColorTable(is, os, grid, table, output_image);
	else if (choice == "set-color-table-size")
		setColorTableSize(is, os, table);
	else if (choice == "set-color")
		setColor(is, os, table);
	else if (choice == "set-random-color")
		setRandomColor(is, os, table);
	else if (choice == "set-color-gradient")
		setColorGradient(is, os, table);
	else if (choice == "fractal-calculate-single-thread")
		calculateFractalSingleThread(is, os, grid);
	else if (choice == "turing")
		return;
	else if (choice == "turing-parameters")
		setTuringParameters(is, os, grid);
	else if (choice == "turing-randomize")
		randomizeTuringValues(is, os, grid);
	else if (choice == "turing-update")
		updateTuringValues(is, os, grid);
	else if (choice == "turing-calculate")
		calculateTuring(is, os, grid);
	else if (choice == "threads")
		setNumberThreads(is, os, grid);
	else if (choice == "set-hsv-color-gradient")
		setHSVColorGradient(is, os, table);
	else if (choice == "julia-five")
		return;
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
// Project 7
void configureGrid(std::istream& is, std::ostream& os, NumberGrid& grid)
{
	int height = getInteger(is, os, "Grid Height? ");
	int width = getInteger(is, os, "Grid Width? ");
	int max_value = getInteger(is, os, "Grid Max Value? ");

	grid.setGridSize(height, width);
	grid.setMaxNumber(max_value);
}
void setGrid(std::istream& is, std::ostream& os, NumberGrid& grid)
{
	int row = getInteger(is, os, "Grid Row? ");
        int column = getInteger(is, os, "Grid Column? ");
        int value = getInteger(is, os, "Grid Value? ");

	grid.setNumber(row, column, value);
}
void applyGrid(std::istream& is, std::ostream& os, NumberGrid& grid, PPM& dst)
{
	(void)is;
	(void)os;

	grid.setPPM(dst);
}
void drawCircle(std::istream& is, std::ostream& os, NumberGrid& grid)
{
	int center_row = getInteger(is, os, "Center Row? ");
	int center_col = getInteger(is, os, "Center Column? ");
	int radius = getInteger(is, os, "Radius? ");
	int number = getInteger(is, os, "Number? ");

	int lower_i = (center_row - radius < 0 ? 0 : center_row - radius);
	int upper_i = (center_row + radius >= grid.getHeight() ? grid.getHeight() - 1 : center_row + radius);
	int lower_j = (center_col - radius < 0 ? 0 : center_col - radius);
	int upper_j = (center_col + radius >= grid.getWidth() ? grid.getWidth() - 1 : center_col + radius);

	for (int i = lower_i; i <= upper_i; i++)
		for (int j = lower_j; j <= upper_j; j++)
			if (std::sqrt(std::pow(i - center_row, 2) + std::pow(j - center_col, 2)) <= radius)
				grid.setNumber(i, j, number);
}
void drawDiamond(std::istream& is, std::ostream& os, NumberGrid& grid)
{
	int center_row = getInteger(is, os, "Center Row? ");
	int center_col = getInteger(is, os, "Center Column? ");
	int size = getInteger(is, os, "Size? ");
	int number = getInteger(is, os, "Number? ");

	int lower_i = (center_row - size < 0 ? 0 : center_row - size);
	int upper_i = (center_row + size >= grid.getHeight() ? grid.getHeight() - 1 : center_row + size);
	int lower_j = (center_col - size < 0 ? 0 : center_col - size);
	int upper_j = (center_col + size >= grid.getWidth() ? grid.getWidth() - 1 : center_col + size);

	for (int i = lower_i; i <= upper_i; i++)
		for (int j = lower_j; j <= upper_j; j++)
			if (std::abs(i - center_row) + std::abs(j - center_col) <= size)
				grid.setNumber(i, j, number);
}
void drawBox(std::istream& is, std::ostream& os, NumberGrid& grid)
{
	int top_row = getInteger(is, os, "Top Row? ");
	int left_col = getInteger(is, os, "Left Column? ");
	int bot_row = getInteger(is, os, "Bottom Row? ");
	int right_col = getInteger(is, os, "Right Column? ");
	int number = getInteger(is, os, "Number? ");

	for (int i = top_row; i <= bot_row; i++)
		for (int j = left_col; j <= right_col; j++)
			grid.setNumber(i, j, number);
}
void horizontalEdges(const PPM& input_image1, PPM& output_image) // custom
{
	output_image = PPM(input_image1.getHeight(), input_image1.getWidth());
	output_image.setMaxColorValue(input_image1.getMaxColorValue());

	for (int i = 1; i < input_image1.getHeight(); i++)
		for (int j = 0; j < input_image1.getWidth(); j++)
		{
			double v2 = input_image1.linearColorimetricPixelValue(i, j);
			double v1 = input_image1.linearColorimetricPixelValue(i - 1, j);
			if (std::abs(v1 - v2) > (input_image1.getMaxColorValue() * 0.1))
				output_image.setPixel(i, j, input_image1.getMaxColorValue());
			else
				output_image.setPixel(i, j, 0);
		}
}
void verticalEdges(const PPM& input_image1, PPM& output_image) // custom
{
	output_image = PPM(input_image1.getHeight(), input_image1.getWidth());
	output_image.setMaxColorValue(input_image1.getMaxColorValue());

	for (int i = 0; i < input_image1.getHeight(); i++)
		for (int j = 1; j < input_image1.getWidth(); j++)
		{
			double v2 = input_image1.linearColorimetricPixelValue(i, j);
			double v1 = input_image1.linearColorimetricPixelValue(i, j - 1);
			if (std::abs(v1 - v2) > (input_image1.getMaxColorValue() * 0.1))
				output_image.setPixel(i, j, input_image1.getMaxColorValue());
			else
				output_image.setPixel(i, j, 0);
		}
}
// Project 8
void setFractalPlaneSize(std::istream& is, std::ostream& os, NumberGrid& grid)
{
	double min_x = getDouble(is, os, "Min X? ");
	double max_x = getDouble(is, os, "Max X? ");
	double min_y = getDouble(is, os, "Min Y? ");
	double max_y = getDouble(is, os, "Max Y? ");

	ComplexFractal* cf = dynamic_cast<ComplexFractal*>(&grid);

	if (cf != nullptr)
		cf->setPlaneSize(min_x, max_x, min_y, max_y);
	else
		os << "Not a ComplexFractal object. Can't set plane size.";
}
void calculateFractal(std::istream& is, std::ostream& os, NumberGrid& grid)
{
	(void)is;
	(void)os;

	grid.calculateAllNumbers();
}
void setJuliaParameters(std::istream& is, std::ostream& os, NumberGrid& grid)
{
	double a = getDouble(is, os, "Parameter a? ");
	double b = getDouble(is, os, "Parameter b? ");

	JuliaSet* js = dynamic_cast<JuliaSet*>(&grid);

	if (js != nullptr)
		js->setParameters(a, b);
	else
		os << "Not a JuliaSet object. Can't set parameters.";
}
void zoom(std::istream& is, std::ostream& os, NumberGrid& grid) // custom
{
	double percentage = getDouble(is, os, "Zoom by what factor? ");
	ComplexFractal* cf = dynamic_cast<ComplexFractal*>(&grid);

	if (cf != nullptr)
		cf->zoom(percentage);
}
void left(std::istream& is, std::ostream& os, NumberGrid& grid) // custom
{
	double factor = getDouble(is, os, "Shift by? ");
	ComplexFractal* cf = dynamic_cast<ComplexFractal*>(&grid);

	if (cf != nullptr)
		cf->translatePlaneLeft(factor);
}
void right(std::istream& is, std::ostream& os, NumberGrid& grid) // custom
{
	double factor = getDouble(is, os, "Shift by? ");
	ComplexFractal* cf = dynamic_cast<ComplexFractal*>(&grid);

	if (cf != nullptr)
		cf->translatePlaneRight(factor);
}
void up(std::istream& is, std::ostream& os, NumberGrid& grid) // custom
{
	double factor = getDouble(is, os, "Shift by? ");
	ComplexFractal* cf = dynamic_cast<ComplexFractal*>(&grid);

	if (cf != nullptr)
		cf->translatePlaneUp(factor);
}
void down(std::istream& is, std::ostream& os, NumberGrid& grid) // custom
{
	double factor = getDouble(is, os, "Shift by? ");
	ComplexFractal* cf = dynamic_cast<ComplexFractal*>(&grid);

	if (cf != nullptr)
		cf->translatePlaneDown(factor);
}
// Project 9
void setJuliaFractal(std::istream& is, std::ostream& os, NumberGrid*& grid)
{
	(void)is;
	(void)os;

	if (grid != nullptr)
		delete grid;

	grid = new JuliaSet();
}
void setMandelbrotFractal(std::istream& is, std::ostream& os, NumberGrid*& grid)
{
	(void)is;
	(void)os;

	if (grid != nullptr)
		delete grid;

	grid = new MandelbrotSet();
}
// Project 10
void applyGridColorTable(std::istream& is, std::ostream& os, NumberGrid& grid, ColorTable& table, PPM& dst)
{
	(void)is;
	(void)os;

	grid.setPPM(dst, table);
}
void setColorTableSize(std::istream& is, std::ostream& os, ColorTable& table)
{
	int size = getInteger(is, os, "Size? ");
	table.setNumberOfColors(size);
}
void setColor(std::istream& is, std::ostream& os, ColorTable& table)
{
	int pos = getInteger(is, os, "Position? ");
	int red = getInteger(is, os, "Red? ");
	int gre = getInteger(is, os, "Green? ");
	int blu = getInteger(is, os, "Blue? ");

	Color& color = table[pos];
	color.setRed(red);
	color.setGreen(gre);
	color.setBlue(blu);
}
void setRandomColor(std::istream& is, std::ostream& os, ColorTable& table)
{
	int position = getInteger(is, os, "Position? ");
	table.setRandomColor(table.getMaxChannelValue(), position);
}
void setColorGradient(std::istream& is, std::ostream& os, ColorTable& table)
{
	int fir_pos = getInteger(is, os, "First position? ");
	int fir_red = getInteger(is, os, "First red? ");
	int fir_gre = getInteger(is, os, "First green? ");
	int fir_blu = getInteger(is, os, "First blue? ");
	int sec_pos = getInteger(is, os, "Second position? ");
	int sec_red = getInteger(is, os, "Second red? ");
	int sec_gre = getInteger(is, os, "Second green? ");
	int sec_blu = getInteger(is, os, "Second blue? ");

	Color color1(fir_red, fir_gre, fir_blu);
	Color color2(sec_red, sec_gre, sec_blu);
	table.insertGradient(color1, color2, fir_pos, sec_pos);
}
// Project 11
void calculateFractalSingleThread(std::istream& is, std::ostream& os, NumberGrid& grid)
{
	(void)is;
	(void)os;

	grid.NumberGrid::calculateAllNumbers();
}
// Project 12
void setTuringParameters(std::istream& is, std::ostream& os, NumberGrid& grid) {
	TuringPattern* tp = dynamic_cast<TuringPattern*>(&grid);

	if (tp != nullptr) {
		double dx = getDouble(is, os, "Parameter dx? ");
		double dt = getDouble(is, os, "Parameter dt? ");
		double al = getDouble(is, os, "Parameter alpha? ");
		double be = getDouble(is, os, "Parameter beta? ");
		double Da = getDouble(is, os, "Parameter Da? ");
		double Db = getDouble(is, os, "Parameter Db? ");

		tp->setParameters(dx, dt, al, be, Da, Db);
	}
	else
		os << "Grid object is not a Turing object\n";
}
void randomizeTuringValues(std::istream& is, std::ostream& os, NumberGrid& grid) {
	TuringPattern* tp = dynamic_cast<TuringPattern*>(&grid);

	if (tp != nullptr) {
		tp->randomizeValues();
	}
	else
		os << "Grid object is not a Turing object.\n";
}
void updateTuringValues(std::istream& is, std::ostream& os, NumberGrid& grid) {
	TuringPattern* tp = dynamic_cast<TuringPattern*>(&grid);

	if (tp != nullptr) {
		int steps = getInteger(is, os, "Steps? ");
		/*std::ofstream output("file.txt", std::ios::app);
		output << "steps: " << steps << std::endl;
		output.close();*/
		tp->updateValues(steps);
	}
	else
		os << "Grid object is not a Turing object.\n";

}
void calculateTuring(std::istream& is, std::ostream& os, NumberGrid& grid) {
	TuringPattern* tp = dynamic_cast<TuringPattern*>(&grid);

	if (tp != nullptr) {
		tp->calculateAllNumbers();
	}
	else
		os << "Grid object is not a Turing object.\n";
}
void setTuringPattern(std::istream& is, std::ostream& os, NumberGrid*& grid) {
	(void)is;
	(void)os;

	if (grid != nullptr)
		delete grid;

	grid = new TuringPattern();
}
void setNumberThreads(std::istream& is, std::ostream& os, NumberGrid& grid) {
	TuringPattern* tp = dynamic_cast<TuringPattern*>(&grid);

	if (tp != nullptr) {
		int num_threads = getInteger(is, os, "Number of threads? ");
		tp->setNumThreads(num_threads);
	}
	else
		os << "Grid object is not a Turing object.\n";
}
void setHSVColorGradient(std::istream& is, std::ostream& os, ColorTable& table) {
	int fir_pos = getInteger(is, os, "First position? ");
	int sec_pos = getInteger(is, os, "Second position? ");
	double fir_hue = getDouble(is, os, "First hue? ");
	double fir_sat = getDouble(is, os, "First saturation? ");
	double fir_val = getDouble(is, os, "First value? ");
	double sec_hue = getDouble(is, os, "Second hue? ");
	double sec_sat = getDouble(is, os, "Second saturation? ");
	double sec_val = getDouble(is, os, "Second value? ");

	table.insertHSVColorGradient(fir_hue, fir_sat, fir_val, sec_hue, sec_sat, sec_val, fir_pos, sec_pos);
}
void setJuliaSetFiveFractal(std::istream& is, std::ostream& os, NumberGrid*& grid) {
	if (grid != nullptr)
		delete grid;

	grid = new JuliaSetFive();
}
