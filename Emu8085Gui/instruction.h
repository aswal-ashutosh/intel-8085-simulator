#pragma once
#include<string>

class Instruction
{
public:
	std::string label;
	std::string mnemonic;
	std::pair<std::string, std::string> operands;
	int line_number;
	int loading_address;
};
