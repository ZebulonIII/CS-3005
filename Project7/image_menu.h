#ifndef _IMAGE_MENU_H_
#define _IMAGE_MENU_H_

#include <string>
#include <iostream>
#include "PPM.h"
#include "NumberGrid.h"

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
void takeAction(std::istream& is, std::ostream& os, const std::string& choice, PPM& input_image1, PPM& input_image2, PPM& output_image, NumberGrid& grid);
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
void configureGrid(std::istream& is, std::ostream& os, NumberGrid& grid);
void setGrid(std::istream& is, std::ostream& os, NumberGrid& grid);
void applyGrid(std::istream& is, std::ostream& os, NumberGrid& grid, PPM& dst);

#endif // _IMAGE_MENU_H_