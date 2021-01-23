#pragma once
#include<string>
#include<sstream>
#include"utility.h"

class Converter
{
public:

	static int HexToDec(std::string number);

	static std::string DecToHex(int number, int type = 8);

	static void ToUpperString(std::string& s);
};



int Converter::HexToDec(std::string number)
{
	std::stringstream ss;
	ss << number;
	int decimal_number;
	ss >> std::hex >> decimal_number;
	return decimal_number;
}



std::string Converter::DecToHex(int number, int type)
{
	std::stringstream ss;
	ss << std::hex << number;
	std::string hex_number = ss.str();
	ToUpperString(hex_number);
	if (type == 8)
	{
		Utility::_8Bit(hex_number);
	}
	else
	{
		Utility::_16Bit(hex_number);
	}
	return hex_number;
}

void Converter::ToUpperString(std::string& s)
{
	for (char& c : s)
	{
		c = toupper(c);
	}
}

