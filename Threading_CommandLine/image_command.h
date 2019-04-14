#ifndef _IMAGE_COMMAND_H_
#define _IMAGE_COMMAND_H_

#include <sstream>
#include <istream>
#include <ostream>
#include <map>
#include <string>
#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"

struct CommandData;

typedef int (*ActionFunctionType)(CommandData& data);

struct CommandData {
	CommandData(int n, std::istream& i, std::ostream& o);
	PPM input_image1;
	PPM input_image2;
	PPM output_image;
	NumberGrid* grid;
	ColorTable table;
	std::istream& is;
	std::ostream& os;
	std::string argument;
	std::map<std::string, ActionFunctionType> filter_actions;
	std::map<std::string, ActionFunctionType> draw_actions;
	std::map<std::string, ActionFunctionType> grid_actions;
	std::map<std::string, ActionFunctionType> color_actions;
};

// Input parsing
void readUntilChar(std::stringstream&& ss, std::string& dest, char delimiter);

// PPM options
int readImage1(CommandData& data);
int readImage2(CommandData& data);
int writeImage(CommandData& data);

// PPM filter options
int filterCopy(CommandData& data);
int filterRedGray(CommandData& data);
int filterGreenGray(CommandData& data);
int filterBlueGray(CommandData& data);
int filterLinearGray(CommandData& data);
int filterPlus(CommandData& data);
int filterPlusEquals(CommandData& data);
int filterMinus(CommandData& data);
int filterMinusEquals(CommandData& data);
int filterTimes(CommandData& data);
int filterTimesEquals(CommandData& data);
int filterDivide(CommandData& data);
int filterDivideEquals(CommandData& data);
int filterAction(CommandData& data);
void makeFilterActionMap(std::map<std::string, ActionFunctionType>& actions);

// Draw options
int drawSize(CommandData& data);
int drawMax(CommandData& data);
int drawChannel(CommandData& data);
int drawPixel(CommandData& data);
int drawClear(CommandData& data);
int drawDiamond(CommandData& data);
int drawCircle(CommandData& data);
int drawBox(CommandData& data);
int drawAction(CommandData& data);
void makeDrawActionMap(std::map< std::string, ActionFunctionType >& actions);

// NumberGrid functions
int gridSetSize(CommandData& data);
int gridSetMaxNumber(CommandData& data);
int gridSetNumber(CommandData& data);
int gridCalculate(CommandData& data);
int gridApply(CommandData& data);
int gridApplyColor(CommandData& data);
int gridAction(CommandData& data);
void makeGridActionMap(std::map< std::string, ActionFunctionType >& actions);

// ComplexFractal functions
int setPlaneSize(CommandData& data);

// Julia functions
int setJuliaFractal(CommandData& data);
int setJuliaParameters(CommandData& data);

// Mandelbrot functions
int setMandelbrotFractal(CommandData& data);

// ColorTable functions
int setColorTableSize(CommandData& data);
int setColor(CommandData& data);
int setRandomColor(CommandData& data);
int setColorGradient(CommandData& data);
int colorAction(CommandData& data);
void makeColorActionMap(std::map< std::string, ActionFunctionType >& actions);

// meta functions
int helpFunction(CommandData& data);
int errorFunction(CommandData& data);
void makeOptionMap(std::map< int, ActionFunctionType >& actions);
int imageCommand(int argc, char* argv[], std::istream& is, std::ostream& os);

#endif