#pragma once
#include<vector>
#include<string>
#include"validator.h"
#include"converter.h"
#include"error_handler.h"

class MemoryManager
{
public:
	static std::vector<int> Memory;
	static bool SetMemory(const std::string&, const std::string&);
};

std::vector<int> MemoryManager::Memory(1 << 16, 0);


bool MemoryManager::SetMemory(const std::string& location, const std::string& data)
{
	bool OK = true;
	OK &= Validator::IsValidHex(location) && Validator::IsValidHex(data);
	int address = Converter::HexToDec(location), value = Converter::HexToDec(data);
	OK &= (address >= 0x0000 && address <= 0xffff) && (value >= 0x00 && value <= 0xff);

	if (OK)
	{
		Memory[address] = value;
	}
	else
	{
		return Error::Throw(ERROR_TYPE::INVALID_DATA);
	}

	return true;
}