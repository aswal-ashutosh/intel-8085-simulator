#pragma once
#include<string>
#include"constants.h"

class Error
{
public:
	static bool Throw(const std::string& e, const int line_number);
};

bool Error::Throw(const std::string& e, const int line_number = -1)
{
	std::string error;
	if (line_number != -1)
	{
		error = "Error: " + e + " [Line Number: " + std::to_string(line_number) + "]";
	}
	else
	{
		error = "Error: " + e;
	}

	wxMessageBox(error, DIALOG::ERROR_OCCURRED);
	return false;
}
