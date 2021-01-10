#pragma once
#include <string>

namespace ERROR_TYPE
{
	const std::string SYNTAX = "Syntax Error";
	const std::string INVALID_OPERANDS = "Invalid Operand";
	const std::string INVALID_MEMORY_LOCATION = "Invalid Memory Location";
	const std::string INVALID_REGISTER = "Invalid Register";
	const std::string INVALID_REGISTER_PAIR = "Invalid Register Pair";
	const std::string EXPECTED_8BIT_DATA = "Expected 8Bit data";
	const std::string NEVER_REACHED_HLT = "Program Control Flow Never Reached 'HLT'.";
	const std::string INVALID_MNEMONIC = "Invalid Mnemonic";
	const std::string INVALID_HEX = "Invalid Hexadecimal Value";
	const std::string INVALID_DATA = "Invalid Data Provided";
	const std::string EMPTY_FIELD = "Empty Field Is Not Allowed";
	const std::string EMPTY_FILE = "Empty File Found";
	const std::string NO_SUCH_LABEL = "No Such Label Exist";
	const std::string INVALID_LABEL= "Invalid Label";
	const std::string RETURN_WITHOUT_CALL = "Control Reached Return Statement When There Exist No Subroutine Call";
	const std::string INFINITE_LOOP_OR_RECURSIVE_CALL = "There May Be An Infinite Loop Or A Never Ending Recursion";
}

namespace PATH
{
	const std::string ABOUT_HTML_FILE = "ABOUT.html";
	const std::string HELP_HTML_FILE = "HELP.html";
}

namespace MNEMONIC
{
	const std::string MOV = "MOV";
	const std::string MVI = "MVI";
	const std::string LDA = "LDA";
	const std::string STA = "STA";
	const std::string LHLD = "LHLD";
	const std::string SHLD = "SHLD";
	const std::string HLT = "HLT";
	const std::string LXI = "LXI";
	const std::string LDAX = "LDAX";
	const std::string STAX = "STAX";
	const std::string XCHG = "XCHG";
	const std::string ADD = "ADD";
	const std::string ADI = "ADI";
	const std::string ADC = "ADC";
	const std::string ACI = "ACI";
	const std::string SUB = "SUB";
	const std::string SBB = "SBB";
	const std::string SUI = "SUI";
	const std::string SBI = "SBI";
	const std::string DAA = "DAA";
	const std::string INR = "INR";
	const std::string INX = "INX";
	const std::string DCR = "DCR";
	const std::string DCX = "DCX";
	const std::string DAD = "DAD";
	const std::string ANA = "ANA";
	const std::string ANI = "ANI";
	const std::string ORA = "ORA";
	const std::string ORI = "ORI";
	const std::string XRA = "XRA";
	const std::string XRI = "XRI";
	const std::string CMA = "CMA";
	const std::string RLC = "RLC";
	const std::string RAL = "RAL";
	const std::string RRC = "RRC";
	const std::string RAR = "RAR";
	const std::string STC = "STC";
	const std::string CMC = "CMC";
	const std::string CMP = "CMP";
	const std::string CPI = "CPI";
	const std::string JMP = "JMP";
	const std::string JC = "JC";
	const std::string JNC = "JNC";
	const std::string JZ = "JZ";
	const std::string JNZ = "JNZ";
	const std::string JPE = "JPE";
	const std::string JPO = "JPO";
	const std::string JM = "JM";
	const std::string JP = "JP";
	const std::string CALL = "CALL";
	const std::string CNC = "CNC";
	const std::string CC = "CC";
	const std::string CNZ = "CNZ";
	const std::string CZ = "CZ";
	const std::string CPE = "CPE";
	const std::string CPO = "CPO";
	const std::string CP = "CP";
	const std::string CM = "CM";
	const std::string RET = "RET";
	const std::string RNC = "RNC";
	const std::string RC = "RC";
	const std::string RNZ = "RNZ";
	const std::string RZ = "RZ";
	const std::string RPE = "RPE";
	const std::string RPO = "RPO";
	const std::string RP = "RP";
	const std::string RM = "RM";
	const std::string NOP = "NOP";
}

namespace REGISTER
{
	const std::string A = "A";
	const std::string B = "B";
	const std::string C = "C";
	const std::string D = "D";
	const std::string E = "E";
	const std::string H = "H";
	const std::string L = "L";
	const std::string M = "M"; // Not a register but don't want to make a separate namespace for a single variable

}

namespace MESSAGE
{
	const std::string SUCCESSFUL_EXECUTION = "Program Executed Successfully.";
}

namespace DIALOG
{
	const std::string ABOUT = "ABOUT";
	const std::string HELP = "HELP";
	const std::string EXECUTION_STOPPED = "EXECUTION STOPPED";
	const std::string ERROR_OCCURRED = "ERROR";
}

namespace PANEL
{
	const std::string REGISTER = "REGISTERS";
	const std::string FLAG_REGISTER = "FLAG REGISTER";
	const std::string MEMORY_INITIALIZER = "MEMORY INITIALIZER";
	const std::string MEMORY_VIEWER = "MEMORY VIEWER";
	const std::string DEBUGGER = "DEBUGGER";
}

namespace BUTTON
{
	const std::string VIEW = "VIEW";
	const std::string SET = "SET";
	const std::string EXECUTE = "EXECUTE";
	const std::string DEBUG = "DEBUG";
	const std::string STOP = "STOP";
}