#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>

class Utility
{
public:
	static void _8Bit(std::string& data);

	static void _16Bit(std::string& data);

	static int _8bit_2sc(int num);

	static int _set_bits_count(int num);

	static void _8Bit_Normalization(int& num);//function to reset all bits after 8th bit
};


class Error
{
public:
	static void Throw(const std::string& e, const int line_number);
};


class Converter
{
public:
	static int HexToDec(std::string number);

	static int HexToDec(char number);

	static std::string DecToHex(int number, int type = 8);
};

//Memory_Start
extern std::vector<int> Memory;

void SetMemory(std::vector<std::pair<std::string, int>> v);

//Memory_END

class Register
{
public:
	static std::map<char, int> Main;
	static int SP, PC;
	class Flag
	{
	public:
		static bool SF, ZF, AC, PF, CY;
	};

	static bool isValid(char reg);

	static int HL();

	static int BC();

	static int DE();

	static void UpdateFlags(int aux);
};



class Instruction
{
public:
	std::string mnemonic;
	std::pair<std::string, std::string> operands;
};

class Program
{
	static std::vector<Instruction> program;
public:
	static std::map<std::string, int> Loop;

	static void Read(std::string program_file_name = "test_program.txt");

	static void Run();
};


class Mnemonic
{
public:
	static std::map<std::string, void (*)(const std::pair<std::string, std::string>&)> Execute;

	static void LoadInsctructionSet();
	

	static bool isValid(const std::string mnemonic);

	static void MOV(const std::pair<std::string, std::string>& operands);

	static void MVI(const std::pair<std::string, std::string>& operands);

	static void LDA(const std::pair<std::string, std::string>& operands);

	static void STA(const std::pair<std::string, std::string>& operands);

	static void LHLD(const std::pair<std::string, std::string>& operands);

	static void SHLD(const std::pair<std::string, std::string>& operands);

	static void HLT(const std::pair<std::string, std::string>& operands);

	static void LXI(const std::pair<std::string, std::string>& operands);

	static void LDAX(const std::pair<std::string, std::string>& operands);

	static void STAX(const std::pair<std::string, std::string>& operands);

	static void XCHG(const std::pair<std::string, std::string>& operands);

	//@Airthmatic Instrunction
	static void ADD(const std::pair<std::string, std::string>& operands);

	static void ADC(const std::pair<std::string, std::string>& operands);

	static void ADI(const std::pair<std::string, std::string>& operands);


	static void ACI(const std::pair<std::string, std::string>& operands);

	static void SUB(const std::pair<std::string, std::string>& operands);

	static void SBB(const std::pair<std::string, std::string>& operands);//Not sure about flags

	static void SUI(const std::pair<std::string, std::string>& operands);


	static void SBI(const std::pair<std::string, std::string>& operands);

	static void INR(const std::pair<std::string, std::string>& operands);//CY is not affected

	static void INX(const std::pair<std::string, std::string>& operands);//No flags are affected during the execution

	static void DCR(const std::pair<std::string, std::string>& operands);//CY is not affected
	

	static void DCX(const std::pair<std::string, std::string>& operands);//No flags are affected during the execution


	static void DAD(const std::pair<std::string, std::string>& operands);//only affect CY
	
	//@Logical Instructions

	static void ANA(const std::pair<std::string, std::string>& operands);

	static void ANI(const std::pair<std::string, std::string>& operands);

	static void ORA(const std::pair<std::string, std::string>& operands);

	static void ORI(const std::pair<std::string, std::string>& operands);

	static void XRA(const std::pair<std::string, std::string>& operands);

	static void XRI(const std::pair<std::string, std::string>& operands);

	static void CMA(const std::pair<std::string, std::string>& operands);//Flags are not affected by this instruction

	static void RLC(const std::pair<std::string, std::string>& operands);

	static void RAL(const std::pair<std::string, std::string>& operands);

	static void RRC(const std::pair<std::string, std::string>& operands);

	static void RAR(const std::pair<std::string, std::string>& operands);

	static void STC(const std::pair<std::string, std::string>& operands);

	static void CMC(const std::pair<std::string, std::string>& operands);

	static void CMP(const std::pair<std::string, std::string>& operands);

	static void CPI(const std::pair<std::string, std::string>& operands);

	//@Branching Instructions
	static void JMP(const std::pair<std::string, std::string>& operands);

	static void JC(const std::pair<std::string, std::string>& operands);

	static void JNC(const std::pair<std::string, std::string>& operands);

	static void JZ(const std::pair<std::string, std::string>& operands);

	static void JNZ(const std::pair<std::string, std::string>& operands);

	static void JPE(const std::pair<std::string, std::string>& operands);

	static void JPO(const std::pair<std::string, std::string>& operands);

	static void JM(const std::pair<std::string, std::string>& operands);

	static void JP(const std::pair<std::string, std::string>& operands);
};



void Init8085();
