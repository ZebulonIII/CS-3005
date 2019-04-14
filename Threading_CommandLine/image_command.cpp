#include <string>
#include <sstream>
#include <exception>
#include "image_command.h"
#include "image_menu.h"

std::string ERROR(std::string func) {
	std::stringstream ss;
	ss << "Error in " << func << std::endl;
	return ss.str();
}

// Input parsing
void readUntilChar(std::stringstream& ss, std::string& dest, char delimiter = ' ') {
	std::getline(ss, dest, delimiter);
}

// PPM options
int readImage1(CommandData& data) {
	readUserImage(data.is, data.os, data.input_image1);
	return 0;
}
int readImage2(CommandData& data) {
	readUserImage(data.is, data.os, data.input_image2);
	return 0;
}
int writeImage(CommandData& data) {
	writeUserImage(data.is, data.os, data.output_image);
	return 0;
}

// PPM filter options
int filterCopy(CommandData& data) {
	return 1;
}
int filterRedGray(CommandData& data) {
	try {
		data.input_image1.grayFromRed(data.output_image);
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterGreenGray(CommandData& data) {
	try {
		data.input_image1.grayFromGreen(data.output_image);
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterBlueGray(CommandData& data) {
	try {
		data.input_image1.grayFromBlue(data.output_image);
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterLinearGray(CommandData& data) {
	try {
		data.input_image1.grayFromLinearColorimetric(data.output_image);
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterPlus(CommandData& data) {
	try {
		data.output_image = data.input_image1 + data.input_image2;
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterPlusEquals(CommandData& data) {
	try {
		data.input_image1 += data.input_image2;
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterMinus(CommandData& data) {
	try {
		data.output_image = data.input_image1 - data.input_image2;
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterMinusEquals(CommandData& data) {
	try {
		data.input_image1 -= data.input_image2;
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterTimes(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	try {
		readUntilChar(ss, str);
		double value = std::stod(str);

		data.output_image = data.input_image1 * value;
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterTimesEquals(CommandData& data) {
	std::string str;
	std::stringstream ss(data.argument);
	try {
		readUntilChar(ss, str);
		double value = std::stod(str);

		data.input_image1 *= value;
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterDivide(CommandData& data) {
	std::string str;
	std::stringstream ss(data.argument);
	try {
		readUntilChar(ss, str);
		double value = std::stod(str);

		data.output_image = data.input_image1 / value;
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterDivideEquals(CommandData& data) {
	std::string str;
	std::stringstream ss(data.argument);
	try {
		readUntilChar(ss, str);
		double value = std::stod(str);

		data.input_image1 /= value;
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int filterAction(CommandData& data) {
	std::stringstream ss;
	std::string command;
	ss << data.argument;
	readUntilChar(ss, command, ':');
	try {
		return data.filter_actions[command](data);
	}
	catch (std::string error) {
		data.os << error;
		return 1;
	}
	catch (...) {
		data.os << ERROR(__func__);
		return 1;
	}
}
void makeFilterActionMap(std::map<std::string, ActionFunctionType>& actions) {
	actions["copy"] = filterCopy;
	actions["red-gray"] = filterRedGray;
	actions["green-gray"] = filterGreenGray;
	actions["blue-gray"] = filterBlueGray;
	actions["linear-gray"] = filterLinearGray;
	actions["+"] = filterPlus;
	actions["+="] = filterPlusEquals;
	actions["-"] = filterMinus;
	actions["-="] = filterMinusEquals;
	actions["*"] = filterTimes;
	actions["*="] = filterTimesEquals;
	actions["/"] = filterDivide;
	actions["/="] = filterDivideEquals;
}

// Draw options
int drawSize(CommandData& data) {
	std::string str;
	std::stringstream ss(data.argument);
	try {
		readUntilChar(ss, str, ',');
		data.input_image1.setHeight(std::stoi(str));
		readUntilChar(ss, str, ',');		
		data.input_image1.setWidth(std::stoi(str));

		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int drawMax(CommandData& data) {
	std::string str;
	std::stringstream ss(data.argument); 
	try {
		readUntilChar(ss, str, ',');
		data.input_image1.setMaxColorValue(std::stoi(str));
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int drawChannel(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	try {
		int row, col, chan, value;

		readUntilChar(ss, str, ',');
		row = std::stoi(str);
		readUntilChar(ss, str, ',');
		col = std::stoi(str);
		readUntilChar(ss, str, ',');
		chan = std::stoi(str);
		readUntilChar(ss, str, ',');
		value = std::stoi(str);

		data.input_image1.setChannel(row, col, chan, value);
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int drawPixel(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str; 
	try {
		int row, col, r, g, b;

		readUntilChar(ss, str, ',');
		row = std::stoi(str);
		readUntilChar(ss, str, ',');
		col = std::stoi(str);
		readUntilChar(ss, str, ',');
		r = std::stoi(str);
		readUntilChar(ss, str, ',');
		g = std::stoi(str);
		readUntilChar(ss, str, ',');
		b = std::stoi(str);

		data.input_image1.setPixel(row, col, r, g, b);
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int drawClear(CommandData& data) {
	try {
		clearAll(data.input_image1);
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int drawDiamond(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	try {
		int row, col, size, r, g, b;

		readUntilChar(ss, str, ',');
		row = std::stoi(str);
		readUntilChar(ss, str, ',');
		col = std::stoi(str);
		readUntilChar(ss, str, ',');
		size = std::stoi(str);
		readUntilChar(ss, str, ',');
		r = std::stoi(str);
		readUntilChar(ss, str, ',');
		g = std::stoi(str);
		readUntilChar(ss, str, ',');
		b = std::stoi(str);

		data.input_image1.drawDiamond(row, col, size, r, g, b);
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int drawCircle(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	try {
		int row, col, radius, r, g, b;

		readUntilChar(ss, str, ',');
		row = std::stoi(str);
		readUntilChar(ss, str, ',');
		col = std::stoi(str);
		readUntilChar(ss, str, ',');
		radius = std::stoi(str);
		readUntilChar(ss, str, ',');
		r = std::stoi(str);
		readUntilChar(ss, str, ',');
		g = std::stoi(str);
		readUntilChar(ss, str, ',');
		b = std::stoi(str);

		data.input_image1.drawCircle(row, col, radius, r, g, b);
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int drawBox(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str; 
	try {
		int tr, lc, br, rc, r, g, b;

		readUntilChar(ss, str, ',');
		tr = std::stoi(str);
		readUntilChar(ss, str, ',');
		lc = std::stoi(str);
		readUntilChar(ss, str, ',');
		br = std::stoi(str);
		readUntilChar(ss, str, ',');
		rc = std::stoi(str);
		readUntilChar(ss, str, ',');
		r = std::stoi(str);
		readUntilChar(ss, str, ',');
		g = std::stoi(str);
		readUntilChar(ss, str, ',');
		b = std::stoi(str); 
		
		data.input_image1.drawBox(tr, lc, br, rc, r, g, b);
		return 0;
	}
	catch (...) {
		throw ERROR(__func__);
	}
}
int drawAction(CommandData& data) {
	std::stringstream ss;
	std::string command;
	ss << data.argument;
	readUntilChar(ss, command, ':');
	try {
		data.filter_actions[command](data);
		return 0;
	}
	catch (std::string error) {
		data.os << error;
		return 1;
	}
	catch (...) {
		data.os << ERROR(__func__);
		return 1;
	}
}
void makeDrawActionMap(std::map< std::string, ActionFunctionType >& actions) {
	actions["size"] = drawSize;
	actions["max"] = drawMax;
	actions["channel"] = drawChannel;
	actions["pixel"] = drawPixel;
	actions["clear"] = drawClear;
	actions["diamond"] = drawDiamond;
	actions["circle"] = drawCircle;
	actions["box"] = drawBox;
}

// NumberGrid functions
int gridSetSize(CommandData& data) {
	return 1;
}
int gridSetMaxNumber(CommandData& data) {
	return 1;
}
int gridSetNumber(CommandData& data) {
	return 1;
}
int gridCalculate(CommandData& data) {
	return 1;
}
int gridApply(CommandData& data) {
	return 1;
}
int gridApplyColor(CommandData& data) {
	return 1;
}
int gridAction(CommandData& data) {
	return 1;
}
void makeGridActionMap(std::map< std::string, ActionFunctionType >& actions) {}

// ComplexFractal functions
int setPlaneSize(CommandData& data) {
	return 1;
}

// Julia functions
int setJuliaFractal(CommandData& data) {
	return 1;
}
int setJuliaParameters(CommandData& data) {
	return 1;
}

// Mandelbrot functions
int setMandelbrotFractal(CommandData& data) {
	return 1;
}

// ColorTable functions
int setColorTableSize(CommandData& data) {
	return 1;
}
int setColor(CommandData& data) {
	return 1;
}
int setRandomColor(CommandData& data) {
	return 1;
}
int setColorGradient(CommandData& data) {
	return 1;
}
int colorAction(CommandData& data) {
	return 1;
}
void makeColorActionMap(std::map< std::string, ActionFunctionType >& actions) {}

// meta functions
int helpFunction(CommandData& data) {
	data.os <<
		"Options:\n\n"
		"PPM options:\n"
		"-1 filename							// Read file into input image 1.\n"
		"-2 filename							// Read file into input image 2.\n"
		"-w filename						    // Write output image to file.\n\n"
		"PPM filter options:\n"
		"-f copy								// Copy input image 1 to output image."
		"-f red-gray							// Set output image from input image 1's grayscale from red.\n"
		"-f green-gray							// Set output image from input image 1's grayscale from green.\n"
		"-f blue-gray							// Set output image from input image 1's grayscale from blue.\n"
		"-f linear-gray							// Set output image from input image 1's grayscale from linear colorimetric.\n"
		"-f +									// Set output image from sum of input image 1 and input image 2.\n"
		"-f +=									// Set input image 1 by adding in input image 2.\n"
		"-f -									// Set output image from difference of input image 1 and input image 2.\n"
		"-f -=									// Set input image 1 by subtracting input image 2.\n"
		"-f *:number							// Set output image from input image 1 multiplied by number.\n"
		"-f *=: number							// Set input image 1 by multiplying by number.\n"
		"-f /: number							// Set output image from input image 1 divided by number.\n"
		"-f /=: number							// Set input image 1 by dividing by number.\n\n"
		"Draw options:\n"
		"-d size:height,width					// Set the size of input image 1.\n"
		"-d max:max								// Set the max color value of input image 1.\n"
		"-d channel:row,col,chan,value			// Set a channel value in input image 1.\n"
		"-d pixel:row,col,r,g,b					// Set a pixel's 3 values in input image 1.\n"
		"-d clear								// Set all pixels to 0,0,0 in input image 1.\n"
		"-d diamond:row,col,size,r,g,b			// Draw a diamond shape in input image 1.\n"
		"-d circle:row,col,radius,r,g,b			// Draw a circle shape in input image 1.\n"
		"-d box:tr,lc,br,rc,r,g,b				// Draw a box shape in input image 1.\n\n"
		"NumberGrid options:\n"
		"-p height,width						// Assign the grid size.\n"
		"-m max									// Assign grid max number.\n"
		"-g set:row,column:value				// Set a single value in the grid.\n"
		"-g calculate							// Calculate all numbers in the grid.\n"
		"-g apply								// Use the grid values to set colors in the output image.\n"
		"-g apply-color							// Use the grid values to set colors in the output image using the color table.\n"
		"ComplexFractal options:\n"
		"-r minx:maxx,miny:maxy					// Set the dimensions of the grid in the complex plane.\n\n"
		"Julia options:\n"
		"-J										// Choose a Julia image.\n"
		"-a a,b									// Set the parameters of the Julia Set function.\n\n"
		"Mandelbrot options:"
		"-M										// Choose a Mandelbrot image.\n\n"
		"ColorTable options:"
		"-T number								// Change the number of slots in the color table.\n"
		"-C set:p,r,g,b							// Set the RGB values for one slot in the color table.\n"
		"-C random:p						    // Randomly set the RGB values for one slot in the color table.\n"
		"-C gradient:p1,r1,g1,b1,p2,r2,g2,b2	// Smoothly set the RGB values for a range of slots in the color table.\n\n"
		"Help options:\n"
		"-h							            // Display this message.\n";
	return 1;
}
int ErrorFunction(CommandData& data) {
	return 1;
}
void makeOptionMap(std::map< int, ActionFunctionType >& actions) {
	
}
int imageCommand(int argc, char* argv[], std::istream& is, std::ostream& os) {
	/*CommandData command_data;
	makeFilterActionMap(command_data.filter_actions);
	makeDrawActionMap(command_data.draw_actions);
	makeGridActionMap(command_data.grid_actions);
	makeColorActionMap(command_data.color_actions);*/

	return 1;
}
