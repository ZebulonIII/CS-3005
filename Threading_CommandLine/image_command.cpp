#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <exception>
#include "image_command.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"

#define ERRORFUNC printf("Error in %s\n", __func__)

// Input parsing
void readUntilChar(std::stringstream& ss, std::string& dest, char delimiter = ' ') {
	std::getline(ss, dest, delimiter);
}

// PPM options
int readImage1(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string filename;

	try {
		readUntilChar(ss, filename);
		std::ifstream ifs(filename);
		ifs >> data.input_image1;
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int readImage2(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string filename;

	try {
		readUntilChar(ss, filename);
		std::ifstream ifs(filename);
		ifs >> data.input_image2;
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int writeImage(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string filename;

	try {
		readUntilChar(ss, filename);
		std::ofstream ofs(filename);
		ofs << data.output_image;
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}

// PPM filter options
int filterCopy(CommandData& data) {
	try {
		data.output_image = data.input_image1;
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int filterRedGray(CommandData& data) {
	try {
		data.input_image1.grayFromRed(data.output_image);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int filterGreenGray(CommandData& data) {
	try {
		data.input_image1.grayFromGreen(data.output_image);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int filterBlueGray(CommandData& data) {
	try {
		data.input_image1.grayFromBlue(data.output_image);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int filterLinearGray(CommandData& data) {
	try {
		data.input_image1.grayFromLinearColorimetric(data.output_image);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int filterPlus(CommandData& data) {
	try {
		data.output_image = data.input_image1 + data.input_image2;
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int filterPlusEquals(CommandData& data) {
	try {
		data.input_image1 += data.input_image2;
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int filterMinus(CommandData& data) {
	try {
		data.output_image = data.input_image1 - data.input_image2;
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int filterMinusEquals(CommandData& data) {
	try {
		data.input_image1 -= data.input_image2;
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
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
		ERRORFUNC;
		return 1;
	}
}
int filterTimesEquals(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;

	try {
		readUntilChar(ss, str);
		double value = std::stod(str);

		data.input_image1 *= value;
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int filterDivide(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;

	try {
		readUntilChar(ss, str);
		double value = std::stod(str);

		data.output_image = data.input_image1 / value;
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
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
		ERRORFUNC;
		return 1;
	}
}
int filterAction(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string command;
	
	try {
		readUntilChar(ss, command, ':');
		data.argument.erase(data.argument.begin(), data.argument.begin() + command.size() + 1);
		return data.filter_actions[command](data);
	}
	catch (std::string error) {
		data.os << error;
		return 1;
	}
	catch (...) {
		ERRORFUNC;
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
		readUntilChar(ss, str);		
		data.input_image1.setWidth(std::stoi(str));

		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int drawMax(CommandData& data) {
	std::string str;
	std::stringstream ss(data.argument); 
	try {
		readUntilChar(ss, str);
		data.input_image1.setMaxColorValue(std::stoi(str));
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int drawChannel(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	int row, col, chan, value;

	try {
		readUntilChar(ss, str, ',');
		row = std::stoi(str);
		readUntilChar(ss, str, ',');
		col = std::stoi(str);
		readUntilChar(ss, str, ',');
		chan = std::stoi(str);
		readUntilChar(ss, str);
		value = std::stoi(str);

		data.input_image1.setChannel(row, col, chan, value);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int drawPixel(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str; 
	int row, col, r, g, b;
	
	try {
		readUntilChar(ss, str, ',');
		row = std::stoi(str);
		readUntilChar(ss, str, ',');
		col = std::stoi(str);
		readUntilChar(ss, str, ',');
		r = std::stoi(str);
		readUntilChar(ss, str, ',');
		g = std::stoi(str);
		readUntilChar(ss, str);
		b = std::stoi(str);

		data.input_image1.setPixel(row, col, r, g, b);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int drawClear(CommandData& data) {
	try {
		data.input_image1.clear();
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int drawDiamond(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	int row, col, size, r, g, b;

	try {
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
		readUntilChar(ss, str);
		b = std::stoi(str);

		data.input_image1.drawDiamond(row, col, size, r, g, b);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int drawCircle(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	int row, col, radius, r, g, b;

	try {		
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
		readUntilChar(ss, str);
		b = std::stoi(str);

		data.input_image1.drawCircle(row, col, radius, r, g, b);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int drawBox(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	int tr, lc, br, rc, r, g, b;

	try {
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
		readUntilChar(ss, str);
		b = std::stoi(str); 
		
		data.input_image1.drawBox(tr, lc, br, rc, r, g, b);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int drawAction(CommandData& data) {
	std::stringstream ss(data.argument);;
	std::string command;
	
	try {
		readUntilChar(ss, command, ':');
		data.argument.erase(data.argument.begin(), data.argument.begin() + command.size() + 1);
		data.filter_actions[command](data);
		return 0;
	}
	catch (std::string error) {
		data.os << error;
		return 1;
	}
	catch (...) {
		ERRORFUNC;
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
	std::stringstream ss(data.argument);;
	std::string str;
	int height, width;

	try {
		readUntilChar(ss, str, ',');
		height = stoi(str);
		readUntilChar(ss, str);
		width = stoi(str);

		data.grid->setGridSize(height, width);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int gridSetMaxNumber(CommandData& data) {
	std::stringstream ss(data.argument);;
	std::string str;
	int max;

	try {
		readUntilChar(ss, str);
		max = stoi(str);

		data.grid->setMaxNumber(max);		
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int gridSetNumber(CommandData& data) {
	std::stringstream ss(data.argument);;
	std::string str;
	int row, column, value;

	try {
		readUntilChar(ss, str, ',');
		row = stoi(str);
		readUntilChar(ss, str, ':');
		column = stoi(str);
		readUntilChar(ss, str);
		value = stoi(str);
		data.grid->setNumber(row, column, value);
		return 0;
	}
	catch (std::invalid_argument arg) {
		std::cout << "Invalid Argument: " << str << ". ";
		ERRORFUNC;
		return 1;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int gridCalculate(CommandData& data) {
	try {
		std::cout << "Here\n";
		data.grid->calculateAllNumbers();
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int gridApply(CommandData& data) {
	try {
		data.grid->setPPM(data.output_image);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int gridApplyColor(CommandData& data) {
	try {
		data.grid->setPPM(data.output_image, data.table);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int gridAction(CommandData& data) {
	std::stringstream ss(data.argument);;
	std::string command;	

	try {
		readUntilChar(ss, command, ':');
		data.argument.erase(data.argument.begin(), data.argument.begin() + command.size() + 1);
		data.grid_actions[command](data);
		return 0;
	}
	catch (std::string error) {
		data.os << error;
		return 1;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
void makeGridActionMap(std::map< std::string, ActionFunctionType >& actions) {
	actions["set"] = gridSetNumber;
	actions["calculate"] = gridCalculate;
	actions["apply"] = gridApply;
	actions["apply-color"] = gridApplyColor;
}

// ComplexFractal functions
int setPlaneSize(CommandData& data) {
	std::stringstream ss(data.argument);;
	std::string str;
	double minx, maxx, miny, maxy;
	ComplexFractal* cf;

	try {
		readUntilChar(ss, str, ':');
		minx = std::stod(str);
		readUntilChar(ss, str, ',');
		maxx = std::stod(str);
		readUntilChar(ss, str, ':');
		miny = std::stod(str);
		readUntilChar(ss, str);
		maxy = std::stod(str);

		cf = dynamic_cast<ComplexFractal*>(data.grid);

		if (cf != nullptr)
			cf->setPlaneSize(minx, maxx, miny, maxy);
		else
			throw "Not a ComplexFractal object. Can't set plane size. ";
		return 0;
	}
	catch (std::string error) {
		data.os << error;
		ERRORFUNC;
		return 1;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}

// Julia functions
int setJuliaFractal(CommandData& data) {
	try {
		if (data.grid != nullptr)
			delete data.grid;

		data.grid = new JuliaSet();
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int setJuliaParameters(CommandData& data) {
	std::stringstream ss(data.argument);;
	std::string str;
	double a, b;
	JuliaSet* js;
	
	try {
		readUntilChar(ss, str, ',');
		a = std::stod(str);
		readUntilChar(ss, str);
		b = std::stod(str);

		js = dynamic_cast<JuliaSet*>(data.grid);

		if (js != nullptr)
			js->setParameters(a, b);
		else
			throw "Not a JuliaSet object. Can't set parameters.";
		return 0;
	}
	catch (std::string error) {
		data.os << error;
		return 1;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}

// Mandelbrot functions
int setMandelbrotFractal(CommandData& data) {
	try {
		if (data.grid != nullptr)
			delete data.grid;

		data.grid = new MandelbrotSet();
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}

// ColorTable functions
int setColorTableSize(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	int num;

	try {
		readUntilChar(ss, str);
		num = std::stoi(str);

		data.table.setNumberOfColors(num);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int setColor(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	int p, r, g, b;

	try {
		readUntilChar(ss, str, ',');
		p = std::stoi(str);
		readUntilChar(ss, str, ',');
		r = std::stoi(str);
		readUntilChar(ss, str, ',');
		g = std::stoi(str);
		readUntilChar(ss, str);
		b = std::stoi(str);

		data.table[p] = Color(r, g, b);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int setRandomColor(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	int p;

	try {
		readUntilChar(ss, str);
		p = std::stoi(str);

		data.table.setRandomColor(data.table.getMaxChannelValue(), p);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int setColorGradient(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string str;
	int p1, r1, g1, b1, p2, r2, g2, b2;

	try {
		readUntilChar(ss, str, ',');
		p1 = std::stoi(str);
		readUntilChar(ss, str, ',');
		r1 = std::stoi(str);
		readUntilChar(ss, str, ',');
		g1 = std::stoi(str);
		readUntilChar(ss, str, ',');
		b1 = std::stoi(str);
		readUntilChar(ss, str, ',');
		p2 = std::stoi(str);
		readUntilChar(ss, str, ',');
		r2 = std::stoi(str);
		readUntilChar(ss, str, ',');
		g2 = std::stoi(str);
		readUntilChar(ss, str);
		b2 = std::stoi(str);

		data.table.insertGradient(Color(r1, g1, b1), Color(r2, g2, b2), p1, p2);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
int colorAction(CommandData& data) {
	std::stringstream ss(data.argument);
	std::string command, new_argument;

	try {
		readUntilChar(ss, command, ':');
		data.argument.erase(data.argument.begin(), data.argument.begin() + command.size() + 1);
		data.color_actions[command](data);
		return 0;
	}
	catch (...) {
		ERRORFUNC;
		return 1;
	}
}
void makeColorActionMap(std::map< std::string, ActionFunctionType >& actions) {
	actions["number"] = setColorTableSize;
	actions["set"] = setColor;
	actions["random"] = setRandomColor;
	actions["gradient"] = setColorGradient;
}

// meta functions
int helpFunction(CommandData& data) {
	data.os <<
		"Options:\n\n"
		"PPM options:\n"
		"-1 filename                            // Read file into input image 1.\n"
		"-2 filename                            // Read file into input image 2.\n"
		"-w filename                            // Write output image to file.\n\n"
		"PPM filter options:\n"
		"-f copy                                // Copy input image 1 to output image.\n"
		"-f red-gray                            // Set output image from input image 1's grayscale from red.\n"
		"-f green-gray                          // Set output image from input image 1's grayscale from green.\n"
		"-f blue-gray                           // Set output image from input image 1's grayscale from blue.\n"
		"-f linear-gray                         // Set output image from input image 1's grayscale from linear colorimetric.\n"
		"-f +                                   // Set output image from sum of input image 1 and input image 2.\n"
		"-f +=                                  // Set input image 1 by adding in input image 2.\n"
		"-f -                                   // Set output image from difference of input image 1 and input image 2.\n"
		"-f -=                                  // Set input image 1 by subtracting input image 2.\n"
		"-f *:number                            // Set output image from input image 1 multiplied by number.\n"
		"-f *=: number                          // Set input image 1 by multiplying by number.\n"
		"-f /: number                           // Set output image from input image 1 divided by number.\n"
		"-f /=: number                          // Set input image 1 by dividing by number.\n\n"
		"Draw options:\n"
		"-d size:height,width                   // Set the size of input image 1.\n"
		"-d max:max                             // Set the max color value of input image 1.\n"
		"-d channel:row,col,chan,value          // Set a channel value in input image 1.\n"
		"-d pixel:row,col,r,g,b                 // Set a pixel's 3 values in input image 1.\n"
		"-d clear                               // Set all pixels to 0,0,0 in input image 1.\n"
		"-d diamond:row,col,size,r,g,b          // Draw a diamond shape in input image 1.\n"
		"-d circle:row,col,radius,r,g,b         // Draw a circle shape in input image 1.\n"
		"-d box:tr,lc,br,rc,r,g,b               // Draw a box shape in input image 1.\n\n"
		"NumberGrid options:\n"
		"-p height,width                        // Assign the grid size.\n"
		"-m max                                 // Assign grid max number.\n"
		"-g set:row,column:value                // Set a single value in the grid.\n"
		"-g calculate                           // Calculate all numbers in the grid.\n"
		"-g apply                               // Use the grid values to set colors in the output image.\n"
		"-g apply-color                         // Use the grid values to set colors in the output image using the color table.\n\n"
		"ComplexFractal options:\n"
		"-r minx:maxx,miny:maxy                 // Set the dimensions of the grid in the complex plane.\n\n"
		"Julia options:\n"
		"-J                                     // Choose a Julia image.\n"
		"-a a,b                                 // Set the parameters of the Julia Set function.\n\n"
		"Mandelbrot options:\n"
		"-M                                     // Choose a Mandelbrot image.\n\n"
		"ColorTable options:\n"
		"-T number                              // Change the number of slots in the color table.\n"
		"-C set:p,r,g,b                         // Set the RGB values for one slot in the color table.\n"
		"-C random:p                            // Randomly set the RGB values for one slot in the color table.\n"
		"-C gradient:p1,r1,g1,b1,p2,r2,g2,b2    // Smoothly set the RGB values for a range of slots in the color table.\n\n"
		"Help options:\n"
		"-h                                     // Display this message.\n";
	return 0;
}
int errorFunction(CommandData& data) {
	data.os << "ERROR! optopt: " << optopt << "\n\n";
	helpFunction(data);
	return 1;
}
void makeOptionMap(std::map< int, ActionFunctionType >& actions) {	
	actions['?'] = errorFunction;
	// PPM
	actions['1'] = readImage1;
	actions['2'] = readImage2;
	actions['w'] = writeImage;
	// PPM filter
	actions['f'] = filterAction;
	// Draw
	actions['d'] = drawAction;
	// NumberGrid
	actions['p'] = gridSetSize;
	actions['m'] = gridSetMaxNumber;
	actions['g'] = gridAction;
	// ComplexFractal
	actions['r'] = setPlaneSize;
	// Julia
	actions['J'] = setJuliaFractal;
	actions['a'] = setJuliaParameters;
	// Mandelbrot
	actions['M'] = setMandelbrotFractal;
	// ColorTable
	actions['T'] = setColorTableSize;
	actions['C'] = colorAction;
	// Help
	actions['h'] = helpFunction;
}
int imageCommand(int argc, char* argv[], std::istream& is, std::ostream& os) {
	CommandData data { 100, is, os };
	std::map<int, ActionFunctionType> options;

	makeFilterActionMap(data.filter_actions);
	makeDrawActionMap(data.draw_actions);
	makeGridActionMap(data.grid_actions);
	makeColorActionMap(data.color_actions);
	makeOptionMap(options);

	int c, code;
	try {		
		while ((c = getopt(argc, argv, "1:2:w:f:d:p:m:g:r:Ja:b:MT:C:h")) != -1) {
			data.argument = (optarg == 0) ? "" : optarg;
			os << "Opt: " << (char)c << " Argument: '" << data.argument << '\'' << std::endl;
			if (options.find(c) != options.end()) {
				code = options[c](data);
				if (code != 0)
					return code;
			}
			else
				return errorFunction(data);
		}
	}
	catch (...) {
		os << ERRORFUNC;
		return 1;
	}

	return 0;
}
