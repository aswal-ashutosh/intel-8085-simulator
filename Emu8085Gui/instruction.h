#pragma once
#include<string>

class Instruction
{
public:
	int line_number;
	std::string mnemonic;
	std::pair<std::string, std::string> operands;
	std::string label;
};
