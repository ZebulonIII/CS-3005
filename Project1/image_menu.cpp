#include <string>
#include <iostream>
#include "image_menu.h"

std::string getString( std::istream& is, std::ostream& os, const std::string& prompt )
{
	os << prompt;
	std::string line;
	//std::getline(is, line);
	is >> line;
	return line;
}
int getInteger( std::istream& is, std::ostream& os, const std::string& prompt )
{
	os << prompt;
	std::string line;
	//std::getline(is, line);
	is >> line;
	return std::stoi(line);
}
double getDouble( std::istream& is, std::ostream& os, const std::string& prompt )
{
	os << prompt;
	std::string line;
	//getline(is, line);
	is >> line;
	return std::stod(line);
}
int assignment1( std::istream& is, std::ostream& os )
{
	std::string s = getString(is, os, "What's your favorite color? ");
	int integer = getInteger(is, os, "What's your favorite integer? ");
	double d = getDouble(is, os, "What's your favorite double? ");
	for (int i = 1; i <= integer; i++)
		os << i << ' ' << s << ' ' << d << std::endl;
	return 1;
}
