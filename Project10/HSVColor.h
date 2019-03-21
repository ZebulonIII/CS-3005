#ifndef _HSV_COLOR_H_
#define _HSV_COLOR_H_

#include <ostream>
#include "Color.h"

class HSVColor
{
public:
	HSVColor();
	HSVColor(const int& hue, const double& saturation, const double& value);
	HSVColor(const Color& color);
	int getHue() const;
	double getSaturation() const;
	double getValue() const;
	double getChannel(const int& channel) const;
	void setHue(const int& hue);
	void setSaturation(const double& saturation);
	void setValue(const double& value);
	void setChannel(const int& channel, const double& amount);
	void invert();
	Color toRGB() const;
	static Color HSVtoRGB(const int& hue, const double& saturation, const double& value);
	static HSVColor RGBtoHSV(const int& red, const int& green, const int& blue);
	static HSVColor RGBtoHSV(const Color& color);
	bool operator== (const HSVColor& rhs) const;
	bool operator== (const Color& rhs) const;
private:
	int mHue;
	double mSaturation, mValue;

	template<class T>
	static T maximum(const T& a, const T& b, const T& c)
	{
		T max = (a < b) ? b : a;
		return ((max < c) ? c : max);
	}
	template<class T>
	static T minimum(const T& a, const T& b, const T& c)
	{
		T min = (a < b) ? a : b;
		return ((min < c) ? min : c);
	}
};

std::ostream& operator<< (std::ostream&, const HSVColor&);

#endif // _HSV_COLOR_H_
