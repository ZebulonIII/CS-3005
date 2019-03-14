#ifndef _COLOR_TABLE_H_
#define _COLOR_TABLE_H_

#include <vector>
#include "Color.h"

class ColorTable
{
public:
	ColorTable(const size_t& num_color);
	size_t getNumberOfColors() const;
	void setNumberOfColors(const size_t& num_color);
	const Color& operator[] (const int& i) const;
	Color& operator[] (const int& i);
	void setRandomColor(const int& max_color_value, const size_t& position);
	void insertGradient(const Color& color1, const Color& color2, const size_t& position1, const size_t& position2);
	int getMaxChannelValue() const;
private:
	std::vector<Color> mColors;
};

#endif // _COLOR_TABLE_H_
