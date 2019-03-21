#include <vector>
#include "HSVColor.h"

class HSVColorTable
{
public:
	HSVColorTable(const size_t& num_color);
	size_t getNumberOfColors() const;
	void setNumberOfColors(const size_t& num_color);
	const HSVColor& operator[] (const int& i) const;
	HSVColor& operator[] (const int& i);
	void setRandomColor(const int& max_color_value, const size_t& position);
	void insertGradient(const HSVColor& color1, const HSVColor& color2, const size_t& position1, const size_t& position2);
	int getMaxChannelValue() const;
private:
	std::vector<HSVColor> mColors;
};
