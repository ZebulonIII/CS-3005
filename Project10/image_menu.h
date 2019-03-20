#ifndef _IMAGE_MENU_H_
#define _IMAGE_MENU_H_

#include <string>
#include <iostream>
#include "PPM.h"
#include "NumberGrid.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include "ColorTable.h"

// Project 1
std::string getString(std::istream& is, std::ostream& os, const std::string& prompt);
int getInteger(std::istream& is, std::ostream& os, const std::string& prompt);
double getDouble(std::istream& is, std::ostream& os, const std::string& prompt);
int assignment1(std::istream& is, std::ostream& os);
// Project 2
void writeUserImage(std::istream& is, std::ostream& os, const PPM& p);
int assignment2(std::istream& is, std::ostream& os);
// Project 3
void showMenu(std::ostream& os);
std::string getChoice(std::istream& is, std::ostream& os);
void commentLine(std::istream& is);
void setSize(std::istream& is, std::ostream& os, PPM& src);
void setMaxColorValue(std::istream& is, std::ostream& os, PPM& src);
void setChannel(std::istream& is, std::ostream& os, PPM& src);
void setPixel(std::istream& is, std::ostream& os, PPM& src);
void clearAll(PPM& src);
void drawDiamond(std::istream& is, std::ostream& os, PPM& src);
void drawCircle(std::istream& is, std::ostream& os, PPM& src);
void drawBox(std::istream& is, std::ostream& os, PPM& src);
void takeAction(std::istream& is, std::ostream& os, const std::string& choice, PPM& input_image1, PPM& input_image2, PPM& output_image, NumberGrid& grid, ColorTable& table);
int imageMenu(std::istream& is, std::ostream& os);
// Project 4
void readUserImage(std::istream& is, std::ostream& os, PPM& ppm);
// Project5
void plus(std::istream& is, std::ostream& os, const PPM& src1, const PPM& src2, PPM& dst);
void plusEquals(std::istream& is, std::ostream& os, PPM& src1, const PPM& src2);
void minus(std::istream& is, std::ostream& os, const PPM& src1, const PPM& src2, PPM& dst);
void minusEquals(std::istream& is, std::ostream& os, PPM& src1, const PPM& src2);
void times(std::istream& is, std::ostream& os, const PPM& src, PPM& dst);
void timesEquals(std::istream& is, std::ostream& os, PPM& src);
void divide(std::istream& is, std::ostream& os, const PPM& src, PPM& dst);
void divideEquals(std::istream& is, std::ostream& os, PPM& src);
// Project 7
void configureGrid(std::istream& is, std::ostream& os, NumberGrid& grid);
void setGrid(std::istream& is, std::ostream& os, NumberGrid& grid);
void applyGrid(std::istream& is, std::ostream& os, NumberGrid& grid, PPM& dst);
void drawCircle(std::istream& is, std::ostream& os, NumberGrid& grid);
void drawDiamond(std::istream& is, std::ostream& os, NumberGrid& grid);
void drawBox(std::istream& is, std::ostream& os, NumberGrid& grid);
// Project 8
void setFractalPlaneSize(std::istream& is, std::ostream& os, NumberGrid& grid);
void calculateFractal(std::istream& is, std::ostream& os, NumberGrid& grid);
void setJuliaParameters(std::istream& is, std::ostream& os, NumberGrid& grid);
void zoom(std::istream& is, std::ostream& os, NumberGrid& grid); // custom
void left(std::istream& is, std::ostream& os, NumberGrid& grid); // custom
void right(std::istream& is, std::ostream& os, NumberGrid& grid); // custom
void up(std::istream& is, std::ostream& os, NumberGrid& grid); // custom
void down(std::istream& is, std::ostream& os, NumberGrid& grid); // custom
// Project 9
void setJuliaFractal(std::istream& is, std::ostream& os, NumberGrid*& grid);
void setMandelbrotFractal(std::istream& is, std::ostream& os, NumberGrid*& grid);
// Project 10
void applyGridColorTable(std::istream& is, std::ostream& os, NumberGrid& grid, ColorTable& table, PPM& dst);
void setColorTableSize(std::istream& is, std::ostream& os, ColorTable& table);
void setColor(std::istream& is, std::ostream& os, ColorTable& table);
void setRandomColor(std::istream& is, std::ostream& os, ColorTable& table);
void setColorGradient(std::istream& is, std::ostream& os, ColorTable& table);
void horizontalEdges(const PPM& input_image1, PPM& dst);
void verticalEdges(const PPM& input_image1, PPM& dst);

#endif // _IMAGE_MENU_H_
