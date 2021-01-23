#pragma once
class Utility
{
public:

	static void _8Bit(std::string& data);

	static void _16Bit(std::string& data);

	static int _8bit_2sc(int num);

	static int _set_bits_count(int num);

	static void _8Bit_Normalization(int& num);//function to reset all bits after 8th bit

	static void _16Bit_Normalization(int& num);
};




void Utility::_8Bit(std::string& data)
{
	data = std::string(2 - data.length(), '0') + data;
}

void Utility::_16Bit(std::string& data)
{
	data = std::string(4 - data.length(), '0') + data;
}

int Utility::_8bit_2sc(int num)
{
	for (int i = 0; i < 8; ++i)
	{
		num ^= (1 << i);
	}

	num += 0x01;
	_8Bit_Normalization(num);
	return num;
}

int Utility::_set_bits_count(int num)
{
	int set_bits = 0;
	for (int i = 0; i < 8; ++i)
	{
		set_bits += bool(num & (1 << i));
	}

	return set_bits;
}

void Utility::_8Bit_Normalization(int& num)//function to reset all bits after 8th bit
{
	for (int i = 8; i < 32; ++i)
	{
		num &= ~(1 << i);
	}
}

void Utility::_16Bit_Normalization(int& num)
{
	for (int i = 16; i < 32; ++i)
	{
		num &= ~(1 << i);
	}
}
