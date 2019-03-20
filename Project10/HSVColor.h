#ifndef _HSV_COLOR_H_
#define _HSV_COLOR_H_

#include <ostream>
#include "Color.h"

class HSVColor
{
public:
	HSVColor();
	HSVColor(const double&, const double&, const double&);
	HSVColor(const Color&);
	double getHue() const;
	double getSaturation() const;
	double getValue() const;
	void setHue(const double&);
	void setSaturation(const double&);
	void setValue(const double&);
	void setChannel(const int&, const double&);
	void invert();
	Color toRGB() const;
	static Color toRGB(const double&, const double&, const double&);
	bool operator== (const HSVColor&) const;
	bool operator== (const Color&) const;
private:
	double hue, saturation, value;
};

std::ostream& operator<< (std::ostream&, const HSVColor&);

#endif // _HSV_COLOR_H_
