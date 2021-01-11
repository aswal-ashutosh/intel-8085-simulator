#pragma once
#include<string>
#include"constants.h"

class Validator
{
public:
	static bool IsValidHex(const std::string&);

	static bool IsValidInt(const std::string&);

	static bool ValidOperandCount(const std::pair<std::string, std::string>&, int);

	static bool IsValidRegister(const std::string&);

	static bool IsValidLabel(const std::string&);
};



bool Validator::IsValidInt(const std::string& data)
{
	for (const char& x : data)
	{
		if (x >= '0' && x <= '9')
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Validator::IsValidHex(const std::string& hex)
{
	for (const char& x : hex)
	{
		if ((x >= '0' && x <= '9') || (x >= 'A' && x <= 'F') || (x >= 'a' && x <= 'f'))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Validator::ValidOperandCount(const std::pair<std::string, std::string>& operands, int expected_operand_count)
{
	if (expected_operand_count == 0)
	{
		return operands.first.empty() && operands.second.empty();
	}
	else if (expected_operand_count == 1)
	{
		return !operands.first.empty() && operands.second.empty();
	}
	else
	{
		return !operands.first.empty() && !operands.second.empty();
	}
}

bool Validator::IsValidRegister(const std::string& expected_register)
{
	if ((int)expected_register.size() != 1)
	{
		return false;
	}
	return (expected_register == REGISTER::A || expected_register == REGISTER::B || expected_register == REGISTER::C || expected_register == REGISTER::D || expected_register == REGISTER::E || expected_register == REGISTER::H || expected_register == REGISTER::L);
}